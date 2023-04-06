#include <ros/ros.h>
#include <std_msgs/String.h>

std::string yolo_msg, bbangle_msg;
void bbangle_callback(const std_msgs::String::ConstPtr& msg)
{
  bbangle_msg = msg->data;
}

void yolo_topic(){
    yolo_msg = "start";
    pub.publish(yolo_msg);
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "main_haird");
  ros::NodeHandle nh;

  ros::Subscriber sub = nh.subscribe("/bbangle_stop", 10, bbangle_callback);

  ros::Rate rate(10); //Set the loop rate in 10Hz
  while (ros::ok())
  {
    yolo_topic();
    rate.sleep();
  }
  
  return 0;
}