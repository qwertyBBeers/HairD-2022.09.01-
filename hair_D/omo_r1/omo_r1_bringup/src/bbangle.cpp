#include <ros/ros.h>
#include <std_msgs/String.h>
#include <iostream>
#include <string>
#include <sstream>
#include "geometry_msgs/Twist.h"

class bbangle
{
    public:
        std::string con;
        int flag = 0;
};

bbangle curr = bbangle();

void mainCallback(const std_msgs::String::ConstPtr& msg)
{
    curr.con = msg->data.c_str();
    if(curr.con == "start")
    {
        curr.flag = 1;
    }
}



int main(int argc, char **argv)
{

  ros::init(argc, argv, "bbangle");

  ros::NodeHandle n;

  ros::Publisher cmdvel_pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 1000);

  ros::Publisher bbangle_pub = n.advertise<std_msgs::String>("bbangle_info", 1000);
  ros::Subscriber main_sub = n.subscribe("bbangle_start", 1000, mainCallback);

  geometry_msgs::Twist cmdvel_msg;
  std_msgs::String bbangle_info;


  ros::Rate rate(10);
  while (ros::ok())
  {
    if (curr.flag == 1)
    {
        if(curr.con == "start")
        {   
            cmdvel_msg.linear.x = 0.0;
            cmdvel_msg.angular.z = 0.1;
            cmdvel_pub.publish(cmdvel_msg);

            bbangle_info.data = "proceeding";
            bbangle_pub.publish(bbangle_info);
        }
        if(curr.con == "stop")
        {   
            bbangle_info.data = "done";
            bbangle_pub.publish(bbangle_info);
            curr.flag = 0;
        }
    }
    if(curr.flag == 0)
    {
        bbangle_info.data = "before";
        bbangle_pub.publish(bbangle_info);
    }    
    
    ros::spinOnce();
    rate.sleep();
  }


  return 0;
}