#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <cmath>
#include <std_msgs/String.h>

class data_round
{
    public:
        std::string round_data = "nothing";
        int val;
};

data_round check = data_round();

void roundCallback(const std_msgs::String::ConstPtr& msg)
{
  check.round_data = msg->data;
  std::cout<<check.round_data<<std::endl;
  if(check.round_data == "start"){
    check.val = 1;
    std::cout<<check.val<<std::endl;
  }
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "cmd_vel_publisher");
    ros::NodeHandle nh;
    
    // 발송할 cmd_vel 메시지를 위한 Publisher 생성
    ros::Publisher cmd_vel_pub = nh.advertise<geometry_msgs::Twist>("cmd_vel", 10);
    ros::Publisher round_pub = nh.advertise<std_msgs::String>("round_info", 1000);

    // 받아 올 Subscriber 설정
    ros::Subscriber round_sub = nh.subscribe("round_start", 1000, roundCallback);

    // 로봇 파라미터 설정
    double wheel_radius = 0.0535;  // 바퀴 반지름
    double wheel_distance = 0.24564;  // 바퀴 간의 사이 거리
    double rotate_time = 5.0;
    
    geometry_msgs::Twist cmd_vel;
    std_msgs::String round_msg;
    // 원을 돌기 위한 파라미터 설정
    double circle_radius = 0.5;  // 원의 반지름
    double linear_speed = M_PI * circle_radius / 12.0;  // 원을 한 바퀴 돌기 위한 선속도
    double angular_speed = linear_speed / circle_radius;  // 원을 한 바퀴 돌기 위한 각속도
    double angular_rotate = M_PI/rotate_time;
    // 시작 시간 기록

    ros::Time start_time = ros::Time::now();
    
    while (ros::ok())
    {
        // 현재 시간 계산
        ros::Time current_time = ros::Time::now();
        std::cout<<"asdfasdfasdf"<<std::endl;
        if(check.val == 1){
            start_time = ros::Time::now();
            check.val = 0;
        }

        std::cout<<"in here"<<std::endl;

        // 10초 동안 원을 돌면서 cmd_vel 메시지 발송
        if(check.round_data == "start"){
            std::cout<<"===================="<<std::endl;
            std::cout<<current_time - start_time<<std::endl;
            std::cout<<"===================="<<std::endl;
            if ((current_time - start_time).toSec() <= 10.0)
            {
                // cmd_vel 메시지 생성
                // cmd_vel 값 설정
                cmd_vel.linear.x = linear_speed;
                cmd_vel.angular.z = angular_speed;
                std::cout<<"+++++++++++++++++++"<<std::endl;
                std::cout<<cmd_vel.linear.x<<std::endl;
                std::cout<<cmd_vel.angular.z<<std::endl;
                std::cout<<"-------------------"<<std::endl;
                // cmd_vel 메시지 발송
                cmd_vel_pub.publish(cmd_vel);
                round_msg.data = "yet";
                round_pub.publish(round_msg);
            }
            else if((current_time - start_time).toSec() > 10.0&&(current_time - start_time).toSec() < 15.0)
            {
                // cmd_vel 값 설정
                cmd_vel.linear.x = 0.0;
                cmd_vel.angular.z = angular_rotate;
                std::cout<<"+++++++++++++++++++"<<std::endl;
                std::cout<<cmd_vel.linear.x<<std::endl;
                std::cout<<cmd_vel.angular.z<<std::endl;
                std::cout<<"-------------------"<<std::endl;
                // cmd_vel 메시지 발송
                cmd_vel_pub.publish(cmd_vel);
                round_msg.data = "yet";
                round_pub.publish(round_msg);
            }
            else if((current_time - start_time).toSec() > 15.0&&(current_time - start_time).toSec() < 25.0)
            {
                // cmd_vel 값 설정
                cmd_vel.linear.x = linear_speed;
                cmd_vel.angular.z = -angular_speed;
                std::cout<<"+++++++++++++++++++"<<std::endl;
                std::cout<<cmd_vel.linear.x<<std::endl;
                std::cout<<cmd_vel.angular.z<<std::endl;
                std::cout<<"-------------------"<<std::endl;
                // cmd_vel 메시지 발송
                cmd_vel_pub.publish(cmd_vel);
                round_msg.data = "yet";
                round_pub.publish(round_msg);
            }
            else{
                cmd_vel.linear.x = 0.0;
                cmd_vel.angular.z = 0.0;
                cmd_vel_pub.publish(cmd_vel);            
                round_msg.data = "done";
                round_pub.publish(round_msg);
                std::cout<<"FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFf"<<std::endl;
            }
        }
        // 10Hz로 발송하도록 대기
        ros::Rate(10).sleep();
        ros::spinOnce();
    }
    
    // 정지를 위해 cmd_vel 메시지를 발송
    cmd_vel.linear.x = 0.0;
    cmd_vel.angular.z = 0.0;
    cmd_vel_pub.publish(cmd_vel);
    
    return 0;
}
