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

void yolo_callback(const std_msgs::String::ConstPtr& msg)
{
  yolo_topic = msg->data; //if yolo detect arco marker, give me that topic and name will be "start"
}

//if i want to publish bbangle topic to yolo, use that bbangle_topic
void bbangle_topic(){
  std_msgs::String msg;
  msg.data = "stop";
  pub_bbangle.publish(msg);
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "haird_maincode");
  ros::NodeHandle nh;

  ros::Publisher pub_bbangle = nh.advertise<omo_r1_bringup::String>("/bbangle_stop")
  
  ros::Rate rate(10);
  while (ros::ok())
  {
    ros::Subscriber sub = nh.subscribe("/yolo_start", 1, callback);
    ros::ServiceServer server = nh.advertiseService("yolo_check", yolo_srv);
    
    rate.sleep();
  }

  return 0;
}