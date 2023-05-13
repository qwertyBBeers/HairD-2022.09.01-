#include <ros/ros.h>
#include <std_msgs/String.h>
#include <iostream>
#include <string>
#include <omo_r1_bringup/yolo_check.h>
#include <omo_r1_bringup/navigation_check.h>
#include "std_msgs/Int32.h"
#include <omo_r1_bringup/qt_check.h>


class robot_con
{
  public:
    int qt_con= 1;
    std::string qt_con_str = "";                           //1, 2, 3
    std::string nav_con = "before";          //before, proceeding, done
    int flag = 0;                            //0, 1
    int nav_flag = 0;
};

robot_con con = robot_con();


// 서비스 핸들러 함수
bool qtServiceHandler(omo_r1_bringup::qt_check::Request& req, omo_r1_bringup::qt_check::Response& res)
{
    ROS_INFO("Service Request: %s, Service Response: %s", req.qt_req.c_str(), res.qt_res.c_str()); // 로그 출력
    if(con.flag == 0)
    {
      std::cout<<"service in"<<std::endl;
      con.qt_con_str = req.qt_req;
      con.qt_con = std::stoi(req.qt_req);
      con.flag = 1;
    }

    return true; // 서비스 요청 처리 성공
}


void qtCallback(const std_msgs::String::ConstPtr& msg)
{
  if(con.flag == 0){
    con.qt_con = std::stoi(msg->data.c_str());
    con.flag = 1;
  }
}



void navCallback(const std_msgs::String::ConstPtr& msg)
{
  con.nav_con = msg->data;
  std::cout<<con.nav_con<<std::endl;
  if(con.nav_con == "done"){
 
  }
}



int main(int argc, char** argv)
{
  ros::init(argc, argv, "emptying_hair");
  ros::NodeHandle nh;

  ros::ServiceServer service_server = nh.advertiseService("qt_service_em", qtServiceHandler);

  ros::Publisher navStart_pub = nh.advertise<std_msgs::Int32>("nav_start_em", 1000);
  ros::Subscriber nav_sub = nh.subscribe("nav_info_em", 1000, navCallback);
  ros::Subscriber qt_sub = nh.subscribe("qt_em", 1000, qtCallback);

  
  ros::Rate loop_rate(10);
  while (ros::ok())
  {
    if(con.flag == 1){
        if (con.nav_con == "before"){                                                           //before cleaning
            std_msgs::Int32 nav_msg;
            nav_msg.data = con.qt_con;

            navStart_pub.publish(nav_msg);
        }
        if (con.nav_con == "done"){
            std_msgs::Int32 nav_msg;
            nav_msg.data = 0;
            con.qt_con = 0;
            navStart_pub.publish(nav_msg);
        
            con.flag = 0; 
            con.nav_flag = 0; 
      }
    }
    ros::spinOnce();
    loop_rate.sleep();
    // ros::spinOnce();
    // rate.sleep();
  }

  return 0;
}
