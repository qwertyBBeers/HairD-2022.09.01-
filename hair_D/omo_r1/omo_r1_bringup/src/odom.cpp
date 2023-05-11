#include <ros/ros.h>
#include <ros/package.h>

#include <geometry_msgs/Pose2D.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Float32.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>
#include <omo_r1_bringup/Pose.h>
#include "std_srvs/Empty.h"


#include <string>
#include <vector>
#include <utility>
#include <set>
#include <stdio.h>
#include <fstream>
 
const double math_pi = 3.141592;
const double wheel_base = 0.4104;
int costmap_time = 0;
//std_srvs::Empty srv;

geometry_msgs::Pose2D able_odom;
nav_msgs::Odometry odom;
geometry_msgs::TransformStamped odom_trans;
float dt;
ros::Time current_time, last_time;

float pose_x = 0.0, pose_y = 0.0, robot_theta = 0.0;
float linear_vel = 0.0;
float angular_vel = 0.0;

void robotPoseCallback(const omo_r1_bringup::Pose::ConstPtr& msg){ 
  pose_x = msg->x;
  pose_y = msg->y;
  robot_theta = msg->theta;
  linear_vel = msg->linear_velocity;
  angular_vel = msg->angular_velocity;
}

void CalcAblePosition()
{
    current_time = ros::Time::now();
    dt = (current_time - last_time).toSec();
    last_time = current_time;
    
    // float linear_vel = (velL + velR) / 2;
    // float angular_vel = (velR - velL) / wheel_base;

    // float distance_delta = linear_vel * 0.1;
    // float angular_delta = angular_vel * 0.1;

    // able_odom.x = able_odom.x + distance_delta * cos(able_odom.theta + angular_delta / 2);
    // able_odom.y = able_odom.y + distance_delta * sin(able_odom.theta + angular_delta / 2);

    // able_odom.theta += angular_delta;

    geometry_msgs::Quaternion odom_quat = tf::createQuaternionMsgFromYaw(-robot_theta);

    odom_trans.header.stamp = current_time;
    odom_trans.header.frame_id = "odom";
    odom_trans.child_frame_id = "base_footprint";

    odom_trans.transform.translation.x = -pose_x;
    odom_trans.transform.translation.y = -pose_y;
    odom_trans.transform.translation.z = 0.0;
    odom_trans.transform.rotation = odom_quat;

    odom.header.stamp = current_time;
    odom.header.frame_id = "odom";

    odom.pose.pose.position.x = pose_x;
    odom.pose.pose.position.y = pose_y;
    odom.pose.pose.position.z = 0.0;
    odom.pose.pose.orientation = odom_quat;
    //set the velocity
    odom.child_frame_id = "base_footprint";
    odom.twist.twist.linear.x= linear_vel;
    odom.twist.twist.linear.y=0.0;
    odom.twist.twist.angular.z = angular_vel;

    /*
    if(able_odom.theta < 0)
    {
        able_odom.theta = able_odom.theta + 2 * math_pi;
    }
    else if(able_odom.theta > 2 * math_pi)
    {
        able_odom.theta = able_odom.theta - 2 * math_pi;
    }
    if(able_odom.theta > math_pi)
    {
        able_odom.theta = able_odom.theta - 2 * math_pi;
    }
    */
}


int main(int argc, char **argv)
{

    ros::init(argc, argv, "mobile_localization_node");
    ros::NodeHandle nh;

    ros::Rate loop_rate(10);

    ros::Publisher pub_able_odom = nh.advertise<nav_msgs::Odometry>("odom", 10);
    tf::TransformBroadcaster odom_broadcaster;
    //ros::ServiceClient clear_costmaps_client = nh.serviceClient<std_srvs::Empty>("/move_base/clear_costmaps");
    ros::Subscriber robotPose_sub = nh.subscribe("robot_pose", 10, robotPoseCallback);
    able_odom.x = 0.0;
    able_odom.y = 0.0;
    able_odom.theta = 0.0;
    
    while (ros::ok())
    {
        CalcAblePosition();
        odom_broadcaster.sendTransform(odom_trans);
        pub_able_odom.publish(odom);
        // if(costmap_time == 50){
        //     if(clear_costmaps_client.call(srv))
        //         {
        //             ROS_INFO("CLEAR COSTMAP");
        //             ROS_INFO("-------------");
        //             costmap_time = 0;
        //         }
        //     }
        // else{
        //     costmap_time++;
        // }
        loop_rate.sleep();
        ros::spinOnce();
    }
    return 0;
}