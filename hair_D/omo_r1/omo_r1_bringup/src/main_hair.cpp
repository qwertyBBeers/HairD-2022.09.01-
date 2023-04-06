#include <ros/ros.h>
#include <std_msgs/String.h>
#include <omo_r1_bringup/yolo_check.h>
#include <omo_r1_bringup/navigation_check.h>

//srv 관리 부
bool yolo_srv(omo_r1_bringup::yolo_check::Request &req,
              omo_r1_bringup::yolo_check::Response &res)
{
  res.yolo_checkpub = "stop";
  req.yolo_checkpub = "start";

}


void callback(const std_msgs::String::ConstPtr& msg)
{
  ROS_INFO("I heard: [%s]", msg->data.c_str());
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "my_subscriber");
  ros::NodeHandle nh;

  ros::Subscriber sub = nh.subscribe("/my_topic", 10, callback);
  ros::ServiceServer server = nh.advertiseService("yolo_check", yolo_srv);
  ros::spin();
  return 0;
}