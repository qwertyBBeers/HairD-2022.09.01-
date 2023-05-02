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
    std::string bbangle_con = "before";      //before, proceeding, done
    std::string yolo_con = "before";         //yet, detected, done
    std::string yolo_check = "stop";         //stop, start
    int flag = 1;                            //0, 1
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
      if(con.qt_con > 0 and con.qt_con < 5){
        con.flag = 1;
      }
      if(con.qt_con > 10){
        con.flag = 2;
      }
    }

    return true; // 서비스 요청 처리 성공
}




// void qtCallback(const std_msgs::String::ConstPtr& msg)
// {
//   if(con.flag == 0){
//     con.qt_con = std::stoi(msg->data.c_str());
//     con.flag = 1;
//   }
// }

void navCallback(const std_msgs::String::ConstPtr& msg)
{
  con.nav_con = msg->data;
  std::cout<<con.nav_con<<std::endl;
  if(con.nav_con == "done"){
 
  }
}

void bbangleCallback(const std_msgs::String::ConstPtr& msg)
{
  con.bbangle_con = msg->data;
}

void yoloCallback(const std_msgs::String::ConstPtr& msg)
{
  con.yolo_con = msg->data;
  std::cout<<con.yolo_con<<std::endl;
}



int main(int argc, char** argv)
{
  ros::init(argc, argv, "main_hair");
  ros::NodeHandle nh;

  ros::ServiceServer service_server = nh.advertiseService("qt_service", qtServiceHandler);

  ros::Publisher navStart_pub = nh.advertise<std_msgs::Int32>("nav_start", 1000);
  ros::Publisher bbangleStart_pub = nh.advertise<std_msgs::String>("bbangle_start", 1000);
  ros::Publisher yoloStart_pub = nh.advertise<std_msgs::String>("yolo_start", 1000);


  //ros::Subscriber qt_sub = nh.subscribe("qt_info", 1000, qtCallback);
  ros::Subscriber nav_sub = nh.subscribe("nav_info", 1000, navCallback);
  ros::Subscriber bbangle_sub = nh.subscribe("bbangle_info", 1000, bbangleCallback);
  ros::Subscriber yolo_sub = nh.subscribe("yolo_info", 1000, yoloCallback);
  
  ros::Rate loop_rate(10);
  while (ros::ok())
  {
    std::cout<<"con_flag: "<<con.flag<<std::endl;
    if (con.flag == 1){
      if (con.nav_con == "before" && con.nav_flag == 0){                                                           //before cleaning
        std_msgs::Int32 nav_msg;
        nav_msg.data = con.qt_con;
        navStart_pub.publish(nav_msg); 

        std_msgs::String bbangle_msg;
        bbangle_msg.data = "stop";
        bbangleStart_pub.publish(bbangle_msg);
      }
      if (con.nav_con == "done"){
        if(con.yolo_con == "yet"){
          std_msgs::Int32 nav_msg;
          nav_msg.data = 10;
          con.qt_con = 10;
          navStart_pub.publish(nav_msg); 
        
          std_msgs::String bbangle_msg;
          bbangle_msg.data = "start";
          bbangleStart_pub.publish(bbangle_msg);

          std_msgs::String yolo_msg;
          yolo_msg.data = "start";
          yoloStart_pub.publish(yolo_msg);
        }
        else if(con.yolo_con == "detected"){
          std_msgs::Int32 nav_msg;
          nav_msg.data = 10;
          con.qt_con = 10;
          navStart_pub.publish(nav_msg); 

          std_msgs::String bbangle_msg;
          bbangle_msg.data = "stop";
          bbangleStart_pub.publish(bbangle_msg);

          std_msgs::String yolo_msg;
          yolo_msg.data = "start";
          yoloStart_pub.publish(yolo_msg);
        }
        else if(con.yolo_con == "done"){
          std_msgs::String bbangle_msg;
          bbangle_msg.data = "stop";
          bbangleStart_pub.publish(bbangle_msg);

          std_msgs::String yolo_msg;
          yolo_msg.data = "stop";
          yoloStart_pub.publish(yolo_msg);
          con.yolo_check == "stop";

          std_msgs::Int32 nav_msg;
          nav_msg.data = 0;
          con.qt_con = 0;
          navStart_pub.publish(nav_msg);
        
          con.flag = 0; 
          con.nav_flag = 0; 
        }
        else{
          std_msgs::Int32 nav_msg;
          nav_msg.data = 10;
          con.qt_con = 10;
          navStart_pub.publish(nav_msg); 
        }
      }
      std::cout<<"con_yolo: "<<con.yolo_con<<std::endl;
      std::cout<<"con_nav: "<<con.nav_con<<std::endl;
    }
    if(con.flag == 2){
      if(con.nav_con == "before"){
        std_msgs::Int32 nav_msg;
        nav_msg.data = con.qt_con;
        navStart_pub.publish(nav_msg);
      }
      if(con.nav_con == "done"){
        std_msgs::Int32 nav_msg;
        nav_msg.data = 0;
        con.qt_con = 0;
        navStart_pub.publish(nav_msg);
        
        con.flag = 0; 
        con.nav_flag = 0; 
      }
      std::cout<<"con_nav move: "<<con.nav_con<<std::endl;
    } 

    ros::spinOnce();
    loop_rate.sleep();
    // ros::spinOnce();
    // rate.sleep();
  }

  return 0;
}
