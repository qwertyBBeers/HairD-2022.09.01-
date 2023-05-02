///////////////////////
// main.cpp
// Publisher, Subscrive action added
#include <geometry_msgs/Twist.h>

#include "md_robot_node/global.hpp"
#include "md_robot_node/main.hpp"
#include "md_robot_node/com.hpp"
#include "md/Pose.h"
#include <ros/ros.h>

ros::Publisher robot_pose_pub;
md::Pose robot_pose;

ROBOT_PARAMETER_t robotParamData;

SETTINNG_PARAM_STEP_t byCntInitStep;
volatile uint16_t appTick;
volatile uint16_t req_pid_pnd_main_data_count;
uint16_t byCntComStep;
uint32_t velCmdUpdateCount;
uint32_t velCmdRcvCount;

static uint8_t byCntCmdVel;
static uint8_t fgSendCmdVel;

static uint8_t byCntCase[10];
static uint8_t byFglIO;
INIT_SETTING_STATE_t fgInitsetting;

double goal_cmd_speed;             // m/sec
double goal_cmd_ang_speed;         // radian/sec
bool reset_odom_flag;
bool reset_alarm_flag;

extern PID_PNT_MAIN_DATA_t curr_pid_pnt_main_data;
extern PID_ROBOT_MONITOR2_t curr_pid_robot_monitor2;
extern PID_PNT_IO_MONITOR_t curr_pid_pnt_io_monitor;
extern PID_ROBOT_MONITOR_t curr_pid_robot_monitor;

extern int InitSerialComm(void);
extern int16_t * RobotSpeedToRPMSpeed(double linear, double angular);
extern void ResetOdom(void);

void AppTickTimerCallback(const ros:: TimerEvent&)
{
    appTick++;
}

void VelCmdRcvTimeoutCallback(const ros:: TimerEvent&)
{
    static uint32_t old_velCmdRcvCount;

    if(velCmdRcvCount == velCmdRcvCount) {
        goal_cmd_speed = 0;
        goal_cmd_ang_speed = 0;
    }

    old_velCmdRcvCount = velCmdRcvCount;
}

void Req_PID_PNT_MAIN_DATA_Callback(const ros:: TimerEvent&)
{
    req_pid_pnd_main_data_count++;
}

void InitMotorParameter(void)
{
    switch(byCntInitStep)
    {
        case SETTING_PARAM_STEP_PID_PNT_VEL_CMD:
        {
            PID_PNT_VEL_CMD_t cmd_data, *p;

#if 0
            ROS_INFO("SET PID_PNT_VEL_CMD(%d)", PID_PNT_VEL_CMD);
            ROS_INFO("size of PID_PNT_VEL_CMD_t: %ld", sizeof(PID_PNT_VEL_CMD_t));
#endif

            p = &cmd_data;
            p->enable_id1 = 1;
            p->rpm_id1 = 0;
            p->enable_id2 = 1;
            p->rpm_id2 = 0;
            p->req_monitor_id = REQUEST_PNT_MAIN_DATA;
            PutMdData(PID_PNT_VEL_CMD, robotParamData.nRMID, (const uint8_t *)p, sizeof(cmd_data)); // 207

            byCntInitStep = SETTING_PARAM_STEP_PID_ROBOT_PARAM;
            break;
        }

        case SETTING_PARAM_STEP_PID_ROBOT_PARAM:
        {
            if(robotParamData.use_MDUI == 1) {  // If using MDUI
                if(robotParamData.nRMID == robotParamData.nIDMDUI) 
                {
                    PID_ROBOT_PARAM_t cmd_data, *p;

    #if 0
                    ROS_INFO("SETTING_PARAM_STEP_PID_ROBOT_PARAMv(%d)", SETTING_PARAM_STEP_PID_ROBOT_PARAM);
                    ROS_INFO("size of PID_ROBOT_PARAM_t: %ld", sizeof(c));
    #endif
                    p = &cmd_data;
                    p->nDiameter = (uint16_t)robotParamData.nDiameter;
                    p->nWheelLength = (uint16_t)robotParamData.nWheelLength * 1000;                 // m unit --> mm unit
                    p->nGearRatio = (uint16_t)robotParamData.nGearRatio;
                    PutMdData(PID_ROBOT_PARAM, MID_MDUI, (const uint8_t *)p, sizeof(cmd_data));     // 247

                    byCntInitStep = SETTING_PARAM_STEP_PID_POSI_RESET;
                }
                else {
                    ROS_INFO("err.mismatch ID(RMID(%d), MDUI(%d))", robotParamData.nRMID, robotParamData.nIDMDUI);
                    fgInitsetting = INIT_SETTING_STATE_ERROR;
                }
            }
            else {
                byCntInitStep = SETTING_PARAM_STEP_PID_POSI_RESET;
            }
            break;
        }

        case SETTING_PARAM_STEP_PID_POSI_RESET:
        {
#if 0
            ROS_INFO("PID_POSI_RESET(%d)", PID_POSI_RESET);
#endif

            PutMdData(PID_POSI_RESET, robotParamData.nRMID, NULL, 0);

            ResetOdom();

            byCntInitStep = SETTING_PARAM_STEP_PID_SLOW_START;
            break;
        }

        case SETTING_PARAM_STEP_PID_SLOW_START:
        {
            PID_SLOW_START_t cmd_data, *p;

#if 0
            ROS_INFO("PID_SLOW_START(%d)", PID_SLOW_START);
            ROS_INFO("size of PID_SLOW_START_t: %ld", sizeof(PID_SLOW_START_t));
#endif

            p = &cmd_data;
            p->value = robotParamData.nSlowstart;

            PutMdData(PID_SLOW_START, robotParamData.nRMID, (const uint8_t *)p, sizeof(cmd_data));

            byCntInitStep = SETTING_PARAM_STEP_PID_SLOW_DOWN;
            break;
        }

        case SETTING_PARAM_STEP_PID_SLOW_DOWN:
        {
            PID_SLOW_DOWN_t cmd_data, *p;

#if 0
            ROS_INFO("PID_SLOW_DOWN(%d)", PID_SLOW_DOWN);
            ROS_INFO("size of PID_SLOW_DOWN_t: %ld", sizeof(PID_SLOW_DOWN_t));
#endif

            p = &cmd_data;
            p->value = robotParamData.nSlowdown;

            PutMdData(PID_SLOW_DOWN, robotParamData.nRMID, (const uint8_t *)p, sizeof(cmd_data));

            byCntInitStep = SETTING_PARAM_STEP_PID_GAIN;
            break;
        }

        case SETTING_PARAM_STEP_PID_GAIN:
        {
            PID_GAIN_t cmd_data, *p;

#if 0
            ROS_INFO("PID_GAIN(%d)", PID_GAIN);
            ROS_INFO("size of PID_GAIN: %ld", sizeof(PID_GAIN_t));
#endif

            p = &cmd_data;
            p->position_proportion_gain = robotParamData.position_proportion_gain;
            p->speed_proportion_gain = robotParamData.speed_proportion_gain;
            p->integral_gain = robotParamData.integral_gain;

            PutMdData(PID_GAIN, robotParamData.nRMID, (const uint8_t *)p, sizeof(cmd_data));

            byCntInitStep = SETTING_PARAM_STEP_PID_INV_SIGH_CMD;
            break;
        }

        case SETTING_PARAM_STEP_PID_INV_SIGH_CMD:       // Left motor
        {
            uint8_t cmd_data;

#if 1
            ROS_INFO("PID_INV_SIGN_CMD(%d)", PID_INV_SIGN_CMD);
#endif

            if(robotParamData.reverse_direction == 0) {
                cmd_data = 1;
            }
            else {
                cmd_data = 0;
            }

            PutMdData(PID_INV_SIGN_CMD, robotParamData.nRMID, (const uint8_t *)&cmd_data, 1);

            byCntInitStep = SETTING_PARAM_STEP_PID_INV_SIGH_CMD2;
            break;
        }

        case SETTING_PARAM_STEP_PID_INV_SIGH_CMD2:      // Right motor
        {
            uint8_t cmd_data;

#if 1
            ROS_INFO("PID_INV_SIGN_CMD2(%d)", PID_INV_SIGN_CMD2);
#endif

            if(robotParamData.reverse_direction == 0) {
                cmd_data = 0;
            }
            else {
                cmd_data = 1;
            }

            PutMdData(PID_INV_SIGN_CMD2, robotParamData.nRMID, (const uint8_t *)&cmd_data, 1);

            byCntInitStep = SETTING_PARAM_STEP_PID_USE_EPOSI;
            break;
        }

        case SETTING_PARAM_STEP_PID_USE_EPOSI:
        {
            uint8_t cmd_data;

#if 1
            ROS_INFO("PID_USE_POSI(%d)", PID_USE_POSI);
#endif

            if(robotParamData.motor_position_type == 0) {
                cmd_data = 0;               // hall sensor
            }
            else {
                cmd_data = 1;               // encoder
            }

            PutMdData(PID_USE_POSI, robotParamData.nRMID, (const uint8_t *)&cmd_data, 1);

            byCntInitStep = SETTING_PARAM_STEP_PID_PPR;
            break;
        }

        case SETTING_PARAM_STEP_PID_PPR:
        {
            PID_PPR_t cmd_data, *p;

#if 1
            ROS_INFO("PID_PPR(%d)", PID_PPR);
#endif
            p = &cmd_data;

            p->PPR = robotParamData.encoder_PPR;

            PutMdData(PID_PPR, robotParamData.nRMID, (const uint8_t *)&cmd_data, sizeof(PID_PPR_t));

            byCntInitStep = SETTING_PARAM_STEP_DONE;

            fgInitsetting = INIT_SETTING_STATE_OK;
            break;
        }

        default:
            break;
    }
}

void RequestRobotStatusTask(void)
{
    int nArray[5];
    uint8_t req_pid;

    switch(byCntComStep)
    {
        case 0:
        {
            req_pid = PID_PNT_MAIN_DATA;            //PID 210
            PutMdData(PID_REQ_PID_DATA, robotParamData.nRMID, (const uint8_t *)&req_pid, 1);

            if(robotParamData.use_MDUI == 1) {  // If using MDUI
                byCntComStep = 1;
            }
            else {
                byCntComStep = 3;
            }
            break;
        }

        case 1:
        {
            if(robotParamData.use_MDUI == 1) {  // If using MDUI
                req_pid = PID_ROBOT_MONITOR2;            // PID 224, Only MDUI
                PutMdData(PID_REQ_PID_DATA, MID_MDUI, (const uint8_t *)&req_pid, 1);
            }

            byCntComStep = 3;
            break;
        }

#if 0
        case 2:
        {
            if(robotParamData.use_MDUI == 1) {  // If using MDUI
                req_pid = PID_PNT_IO_MONITOR;               // PID 241, Only MDUI, but not using
                PutMdData(PID_REQ_PID_DATA, MID_MDUI, (const uint8_t *)&req_pid, 1);
            }

            byCntComStep = 3;
            break;
        }
#endif

        case 3:
        {
            if(curr_pid_robot_monitor2.byPlatStatus.bits.bEmerSW == 1)
            {
                PID_PNT_TQ_OFF_t pid_pnt_tq_off, *p;

                fgSendCmdVel = 0;
                pid_pnt_tq_off.enable_id1 = 1;
                pid_pnt_tq_off.enable_id2 = 1;
                pid_pnt_tq_off.req_monitor_id = REQUEST_PNT_MAIN_DATA;
                PutMdData(PID_PNT_TQ_OFF, robotParamData.nRMID, (const uint8_t *)&pid_pnt_tq_off, sizeof(pid_pnt_tq_off));
            }
            else if(reset_odom_flag == true) {
                reset_odom_flag = false;

                PutMdData(PID_POSI_RESET, robotParamData.nRMID, NULL, 0);
                ResetOdom();
            }
            else if(reset_alarm_flag == true) {
                uint8_t cmd_pid;

                reset_alarm_flag = false;

                cmd_pid = CMD_ALARM_RESET;
                PutMdData(PID_COMMAND, robotParamData.nRMID, (const uint8_t *)&cmd_pid, 1);
            }

            byCntComStep = 0;
            break;
        }

        case 4:
            req_pid = PID_GAIN;            // PID: 203
            PutMdData(PID_REQ_PID_DATA, robotParamData.nIDMDT, (const uint8_t *)&req_pid, 1);

            byCntComStep = 0;
            break;

        default:
            byCntComStep = 0;
            break;
    }
}

void cmdVelCallBack(const geometry_msgs::Twist& keyVel)   //from turtlebot3_teleop_key node
{
    static geometry_msgs::Twist old_cmd;

    if(fgInitsetting == INIT_SETTING_STATE_OK) {
        velCmdUpdateCount++;

        goal_cmd_speed = keyVel.linear.x;
        goal_cmd_ang_speed = keyVel.angular.z;

#if 0
        ROS_INFO("Goal cmd_vel(m/sec): lin: %f, ang: %f", keyVel.linear.x, keyVel.angular.z);
#endif
    }

    return;
}

void resetOdomCallBack(const std_msgs::Bool& reset_odom_msg)
{
    if(reset_odom_msg.data == 1) {
        ROS_INFO("Reset Odom");
        reset_odom_flag = true;
    }
}

void resetAlarmCallBack(const std_msgs::Bool& reset_alarm_msg)
{
    if(reset_alarm_msg.data == 1) {
        ROS_INFO("Reset Alarm");
        reset_alarm_flag = true;
    }
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "md"); //Node name initialization.
    ros::NodeHandle nh;        //Node handle declaration for communication with ROS system.

    ros::Subscriber keyboard_sub = nh.subscribe("cmd_vel", 10, cmdVelCallBack);
    ros::Subscriber reset_odom_sub = nh.subscribe("reset_odom", 10, resetOdomCallBack);              //Subscriber declaration.
    ros::Subscriber reset_alarm_sub = nh.subscribe("reset_alarm", 10, resetAlarmCallBack);              //Subscriber declaration.

    robot_pose_pub = nh.advertise<md::Pose>("robot_pose", 10);

    int16_t *pGoalRPMSpeed;

    reset_odom_flag = false;
    reset_alarm_flag = false;

    fgSendCmdVel = 1;
    fgInitsetting = INIT_SETTING_STATE_NONE;

    nh.getParam("md_robot_node/use_MDUI", robotParamData.use_MDUI);
    nh.getParam("md_robot_node/wheel_radius", robotParamData.wheel_radius);               // m unit
    nh.getParam("md_robot_node/wheel_length", robotParamData.nWheelLength);                // m unit
    nh.getParam("md_robot_node/reduction", robotParamData.nGearRatio);
    nh.getParam("md_robot_node/motor_pole", robotParamData.motor_pole);
    nh.getParam("md_robot_node/reverse_direction", robotParamData.reverse_direction);
    nh.getParam("md_robot_node/maxrpm", robotParamData.nMaxRPM);
    nh.getParam("md_robot_node/motor_posi", robotParamData.motor_position_type);
    nh.getParam("md_robot_node/encoder_PPR", robotParamData.encoder_PPR);
    nh.getParam("md_robot_node/position_proportion_gain", robotParamData.position_proportion_gain);
    nh.getParam("md_robot_node/speed_proportion_gain", robotParamData.speed_proportion_gain);
    nh.getParam("md_robot_node/integral_gain", robotParamData.integral_gain);
    nh.getParam("md_robot_node/slow_start", robotParamData.nSlowstart);
    nh.getParam("md_robot_node/slow_down", robotParamData.nSlowdown);

    robotParamData.nIDPC = MID_PC;         // Platform mini-PC ID
    robotParamData.nIDMDUI = MID_MDUI;       // MDUI ID
    robotParamData.nIDMDT = MID_MDT;        // MD750T, MD400T, MD200T ID
    if(robotParamData.use_MDUI == 1) {  // If using MDUI
        robotParamData.nRMID = robotParamData.nIDMDUI;
        ROS_INFO("Using MDUI");
    }
    else {
        robotParamData.nRMID = robotParamData.nIDMDT;
        ROS_INFO("Not using MDUI");
    }

    robotParamData.nBaudrate = 57600;               // fixed

    ROS_INFO("PC ID          : %d", robotParamData.nIDPC);
    ROS_INFO("MDUI ID        : %d", robotParamData.nIDMDUI);
    ROS_INFO("MDT ID         : %d", robotParamData.nIDMDT);
    ROS_INFO("Receving ID    : %d", robotParamData.nRMID);
    ROS_INFO("baudrate       : %d", robotParamData.nBaudrate);
    ROS_INFO("Wheel Radius(m): %f", robotParamData.wheel_radius);
    ROS_INFO("WheelLength(m) : %f", robotParamData.nWheelLength);
    ROS_INFO("Reduction rate : %d", robotParamData.nGearRatio);
    ROS_INFO("Motor pole     : %d", robotParamData.motor_pole);
    if(robotParamData.motor_position_type == 0) {
        ROS_INFO("motor position detection: hall sensor");
    }
    else {
        ROS_INFO("motor position detection: encoder");
    }

    // If use hall sensor: 3 x pole no x reduction rate
    // If use encoder: 4 x encder x reduction rate
    ROS_INFO("PPR: %d", robotParamData.encoder_PPR);

    if(robotParamData.motor_position_type == 0) {
        ROS_INFO("Robot direction: Forward");
    }
    else {
        ROS_INFO("Robot direction: Reverse");
    }
    ROS_INFO("Max RPM        : %d",             robotParamData.nMaxRPM);
    ROS_INFO("Position proportion gain: %d",    robotParamData.position_proportion_gain);
    ROS_INFO("Speed proportion gain   : %d",    robotParamData.speed_proportion_gain);
    ROS_INFO("Integral gain  : %d",             robotParamData.integral_gain);
    ROS_INFO("Slow start     : %d",             robotParamData.nSlowstart);
    ROS_INFO("Slow down      : %d\r\n",         robotParamData.nSlowdown);

    if(robotParamData.motor_position_type == 0) {
        robotParamData.motor_count = robotParamData.motor_pole * 3 * robotParamData.nGearRatio;
    }
    else {
        robotParamData.motor_count = robotParamData.encoder_PPR * 4 * robotParamData.nGearRatio;
    }

    robotParamData.motor_count_per_degree = (double)(360.0 / (double)robotParamData.motor_count);
    ROS_INFO("count per degree: %f", robotParamData.motor_count_per_degree);

    robotParamData.nDiameter = (int)(robotParamData.wheel_radius * 2.0 * 1000.0);              // nDiameter is (mm) unit

    InitSerialComm();     //communication initialization in com.cpp

    ros::Rate r(1000);       //Set the loop period -> 1ms.
    ros::Time start_time = ros::Time::now();
    ros::Duration start_delay(1.5);
    double start_delay_sec = ros::Time::now().toSec();

    start_delay_sec += start_delay.toSec();

    //---------------------------------------------------------------------------------------------------------
    // Start delay: 1.5sec
    //---------------------------------------------------------------------------------------------------------
    while(ros::ok())
    {
        if(ros::Time::now().toSec() >= start_delay_sec) {
            break;
        }

        ReceiveDataFromController();

        ros::spinOnce();
        r.sleep();
    }

    appTick = 0;
    byCntInitStep = SETTING_PARAM_STEP_PID_PNT_VEL_CMD;
    ros::Timer app_tick_timer = nh.createTimer(ros::Duration(0.500), AppTickTimerCallback);
    app_tick_timer.start();

    while(ros::ok())
    {
        ReceiveDataFromController();

        if(appTick > 0) {
            appTick = 0;

            InitMotorParameter();

            if(fgInitsetting != INIT_SETTING_STATE_NONE) {
                break;
            }
        }

        ros::spinOnce();
        r.sleep();
    }

    app_tick_timer.stop();

    if(fgInitsetting != INIT_SETTING_STATE_OK) {
        ROS_INFO("error.init ROBOT");
    }
    else {
        ROS_INFO("Init done");
    }

    byCntComStep = 0;
    appTick = 0;
    app_tick_timer.setPeriod(ros::Duration(0.02));
    app_tick_timer.start();

    ros::Timer vel_cmd_rcv_timeout = nh.createTimer(ros::Duration(1.000), VelCmdRcvTimeoutCallback);
    vel_cmd_rcv_timeout.start();

    ros::Timer req_PID_PNT_MAIN_DATA_timer = nh.createTimer(ros::Duration(0.1), Req_PID_PNT_MAIN_DATA_Callback);

    while(ros::ok())
    {
        ReceiveDataFromController();

        if(appTick > 0) {
            appTick = 0;

            RequestRobotStatusTask();
        }

        if(velCmdUpdateCount > 0) {
            velCmdUpdateCount = 0;

            PID_PNT_VEL_CMD_t pid_pnt_vel_cmd, *p;

            pGoalRPMSpeed = RobotSpeedToRPMSpeed(goal_cmd_speed, goal_cmd_ang_speed);

#if 0
            ROS_INFO("Goal RPM L:%d, R:%d", pGoalRPMSpeed[0], pGoalRPMSpeed[1]);
#endif

            p = &pid_pnt_vel_cmd;
            p->enable_id1 = 1;
            p->rpm_id1 = pGoalRPMSpeed[0];
            p->enable_id2 = 1;
            p->rpm_id2 = pGoalRPMSpeed[1];
            p->req_monitor_id = REQUEST_PNT_MAIN_DATA;

            PutMdData(PID_PNT_VEL_CMD, robotParamData.nRMID, (const uint8_t *)&pid_pnt_vel_cmd, sizeof(pid_pnt_vel_cmd));
        }

        ros::spinOnce();
        r.sleep();
    }
}

void PubRobotPose(void)
{
    if(robotParamData.reverse_direction == 0) {
        robot_pose.US_1 = curr_pid_robot_monitor2.byUS1;
        robot_pose.US_2 = curr_pid_robot_monitor2.byUS2;
        robot_pose.US_3 = curr_pid_robot_monitor2.byUS3;
        robot_pose.US_4 = curr_pid_robot_monitor2.byUS4;
        robot_pose.platform_state = curr_pid_robot_monitor2.byPlatStatus.val;
    }
    else {
        PLATFORM_STATE_2_t temp;

        robot_pose.US_1 = curr_pid_robot_monitor2.byUS4;
        robot_pose.US_2 = curr_pid_robot_monitor2.byUS3;
        robot_pose.US_3 = curr_pid_robot_monitor2.byUS2;
        robot_pose.US_4 = curr_pid_robot_monitor2.byUS1;

        temp.val = curr_pid_robot_monitor2.byPlatStatus.val;
        temp.bits.bBumper1 = curr_pid_robot_monitor2.byPlatStatus.bits.bBumper4;
        temp.bits.bBumper2 = curr_pid_robot_monitor2.byPlatStatus.bits.bBumper3;
        temp.bits.bBumper3 = curr_pid_robot_monitor2.byPlatStatus.bits.bBumper2;
        temp.bits.bBumper4 = curr_pid_robot_monitor2.byPlatStatus.bits.bBumper1;

        robot_pose.platform_state = temp.val;
    }

    // robot_pose.battery_voltage = curr_pid_robot_monitor2.sVoltIn;
    // robot_pose.left_mot_current = curr_pid_pnt_main_data.current_id1;
    // robot_pose.right_mot_current = curr_pid_pnt_main_data.current_id2;
    // robot_pose.left_motor_ctrl_state = curr_pid_pnt_io_monitor.motor_1.val;
    // robot_pose.right_motor_ctrl_state = curr_pid_pnt_io_monitor.motor_2.val;

    robot_pose.left_motor_state = curr_pid_pnt_main_data.mtr_state_id1.val;
    robot_pose.right_motor_state = curr_pid_pnt_main_data.mtr_state_id2.val;

    robot_pose_pub.publish(robot_pose);
}