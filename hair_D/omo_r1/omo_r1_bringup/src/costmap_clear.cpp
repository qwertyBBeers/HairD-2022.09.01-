#include <ros/ros.h>
#include <ros/package.h>

#include <geometry_msgs/Pose2D.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Float32.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>
#include "std_srvs/Empty.h"

int costmap_time = 0;
std_srvs::Empty srv;

int main(int argc, char **argv)
{

    ros::init(argc, argv, "costmap_clear_node");
    ros::NodeHandle nh;

    ros::Rate loop_rate(10);
    ros::ServiceClient clear_costmaps_client = nh.serviceClient<std_srvs::Empty>("/move_base/clear_costmaps");
    
    while (ros::ok())
    {
        if(costmap_time == 50){
            if(clear_costmaps_client.call(srv))
                {
                    ROS_INFO("CLEAR COSTMAP");
                    ROS_INFO("-------------");
                    costmap_time = 0;
                }
            }
        else{
            costmap_time++;
        }
        loop_rate.sleep();
        ros::spinOnce();
    }
    return 0;
}