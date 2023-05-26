#!/usr/bin/env python3

import rospy
import actionlib
from move_base_msgs.msg import MoveBaseAction, MoveBaseGoal
from math import radians, degrees, pi, sin, cos
from actionlib_msgs.msg import *
from geometry_msgs.msg import PoseWithCovarianceStamped
from copy import deepcopy
import tf
import numpy as np
import time
from std_msgs.msg import Float32MultiArray
from std_msgs.msg import Int32
from std_msgs.msg import String

class con:
    def __init__(self):
        self.flag = 0
        self.a = 0
        self.list_stage = []
        self.listFlag = 0
        self.count = 0
        self.clean_info = "yet"
        self.clean_flag = 0
        self.round_info = 'yet'
        self.round_flag = 0
        self.qt_num = 0


def callback(msg):
    global current_pose
    current_pose = msg

def cleanInfoCallback(msg):
    curr.clean_info = msg.data

def roundInfoCallback(msg):
    curr.round_info = msg.data

def callbackRoom(data):
    stage = data.data
    print("stage: {} ", stage)
    curr.qt_num = stage

    # if(stage > 0 and stage < 5):
    #     curr.flag = 1

    # if (curr.flag == 0):
    #     if (stage == 0):
    #         nav_info_msg = "before"
    #         main_pub.publish(nav_info_msg)
    #     elif (stage == 10):
    #         nav_info_msg = "done"
    #         main_pub.publish(nav_info_msg)
    print("flag: ",curr.flag)
    if(curr.flag == 0 and stage < 5 and stage > 0):
        #목적지 순서
        curr.list_stage = []

        if stage == 1:
            c_x = 0.6106761024768365                 #shophong 
            c_y = 0.3714892187985502
        elif stage == 2:                                
            c_x = 2.032741242737444                  #5gong
            c_y = 0.13712451358191208
        elif stage == 3:
            c_x = 1
            c_y = 1
        gap = 0.6
        
        for i in range(1,9):
        #목적지 순서당 가지는 Goal 값
            if i == 1:
                c_x_ = c_x - gap
                c_y_ = c_y - gap
                hh_stage.stage_goal = [c_x_, c_y_, 0.025430730456035645, 0.9996765866761472]
            elif i == 2:
                c_x_ = c_x + gap
                c_y_ = c_y - gap                   
                hh_stage.stage_goal = [c_x_, c_y_, 0.7229380096706861, 0.6909128991221593]
            elif i == 3:
                c_x_ = c_x + gap
                c_y_ = c_y + gap
                hh_stage.stage_goal = [c_x_, c_y_, -0.9998953133538889, 0.01446935841453293]
            elif i == 4:
                c_x_ = c_x - gap
                c_y_ = c_y + gap
                hh_stage.stage_goal = [c_x_, c_y_, -0.6933633504018728, 0.7205881377871063]
            elif i == 5:
                c_x_ = c_x - gap
                c_y_ = c_y
                hh_stage.stage_goal = [c_x_, c_y_, -0.6933633504018728, 0.7205881377871063]
            elif i == 6:
                c_x_ = c_x - 1.0
                c_y_ = c_y + gap
                hh_stage.stage_goal = [c_x_, c_y_, 0.025430730456035645, 0.9996765866761472]
            elif i == 7:
                c_x_ = c_x - 1.0
                c_y_ = c_y + gap
                hh_stage.stage_goal = [c_x_, c_y_, 0.025430730456035645, 0.9996765866761472]
            elif i == 8:
                c_x_ = c_x - 1.0
                c_y_ = c_y + gap
                hh_stage.stage_goal = [c_x_, c_y_, 0.025430730456035645, 0.9996765866761472]

            curr.list_stage.append(hh_stage.stage_goal)
        if(len(curr.list_stage) == 8):
            curr.listFlag = 1
    
    if(stage > 10 and curr.flag == 0 and curr.count == 0):
        #목적지 순서
        curr.list_stage = []

        if stage == 11:
            c_x = -10
            c_y = -1
        elif stage == 22:
            c_x = 1
            c_y = 1
        elif stage == 33:
            c_x = 1
            c_y = 1

        for i in range(1,9):
        #목적지 순서당 가지는 Goal 값
            if i == 1:
                c_x = 0.15673527273573193
                c_y = 0.12170742233113975
                hh_stage.stage_goal = [c_x, c_y, 0.0412841107943205, 0.9991474476752279]
            elif i == 2:
                c_x = 0.15673527273573193
                c_y = 0.12170742233113975
                hh_stage.stage_goal = [c_x, c_y, 0.0412841107943205, 0.9991474476752279]
            elif i == 3:
                c_x = 0.15673527273573193
                c_y = 0.12170742233113975
                hh_stage.stage_goal = [c_x, c_y, 0.0412841107943205, 0.9991474476752279]
            elif i == 4:
                c_x = 0.15673527273573193
                c_y = 0.12170742233113975
                hh_stage.stage_goal = [c_x, c_y, 0.0412841107943205, 0.9991474476752279]
            elif i == 5:
                c_x = 0.15673527273573193
                c_y = 0.12170742233113975
                hh_stage.stage_goal = [c_x, c_y, 0.0412841107943205, 0.9991474476752279]
            elif i == 6:
                c_x = 0.15673527273573193
                c_y = 0.12170742233113975
                hh_stage.stage_goal = [c_x, c_y, 0.0412841107943205, 0.9991474476752279]
            elif i == 7:
                c_x = 0.15673527273573193
                c_y = 0.12170742233113975
                hh_stage.stage_goal = [c_x, c_y, 0.0412841107943205, 0.9991474476752279]
            elif i == 8:
                c_x = 0.15673527273573193
                c_y = 0.12170742233113975
                hh_stage.stage_goal = [c_x, c_y, 0.0412841107943205, 0.9991474476752279]

            curr.list_stage.append(hh_stage.stage_goal)
        if(len(curr.list_stage) == 8):
            curr.listFlag = 1




    if(stage > 0 and stage < 5 and curr.listFlag == 1):
        curr.flag = 1
    if(stage > 10 and curr.listFlag == 1):
        curr.flag = 1
    if(stage > 5 and stage < 11):
        curr.flag = 0

    if (curr.flag == 0):
        if (stage == 0):
            nav_info_msg = "before"
            main_pub.publish(nav_info_msg)
            print("pub before")
            curr.count = 0
        elif (stage == 10):
            nav_info_msg = "done"
            main_pub.publish(nav_info_msg)
            curr.count = 0


    if(curr.flag == 1 and stage < 5 and curr.count == 0):
        print(curr.list_stage)
        goal_def(curr.list_stage)

    if(curr.flag == 1 and stage > 10 and curr.count == 0):
        print(curr.list_stage)
        goal_def(curr.list_stage)

class hh_stage:
    stage_goal = []


class GoalPose:
    x = 0.
    y = 0.
    theta = 0.
    z = 0.
    w = 0.

def move_to(goal_point):
    goal = MoveBaseGoal()
    goal.target_pose.header.frame_id = "map"
    goal.target_pose.header.stamp = rospy.Time.now()

    print(curr.a)
    #print(len(stage_check))
    curr.a += 1 

    goal.target_pose.pose.orientation.x = 0
    goal.target_pose.pose.orientation.y = 0
    goal.target_pose.pose.orientation.z = goal_point.z
    goal.target_pose.pose.orientation.w = goal_point.w

    goal.target_pose.pose.position.x = goal_point.x
    goal.target_pose.pose.position.y = goal_point.y
    goal.target_pose.pose.position.z = 0

    print(goal)
    ac.send_goal(goal)

def goal_def(list_stage):
    goal_test = GoalPose()
    error = 0.2

    for i in range(8):
        stage_check = list_stage[i]

    # for room in stage:
    #     if room == 101:
    #         rospy.loginfo("101")
    #         goal_test.x = -1.73096152587
    #         goal_test.y = 0.651883785386
    #         goal_test.z = 0.213383708578
    #         goal_test.w = 0.976968478788
    #     elif room == 102:
    #         rospy.loginfo("102")
    #         goal_test.x = 1.75060760178
    #         goal_test.y = -0.279016830127
    #         goal_test.z = 0.657537242689
    #         goal_test.w = 0.753422042733
    #     elif room == 103:
    #         rospy.loginfo("103")
    #         goal_test.x = -1.73096152587
    #         goal_test.y = 0.651883785386
    #         goal_test.z = 0.213383708578
    #         goal_test.w = 0.976968478788
    #     elif room == 104:
    #         rospy.loginfo("104")
    #         goal_test.x = 1.75060760178
    #         goal_test.y = -0.279016830127
    #         goal_test.z = 0.657537242689
    #         goal_test.w = 0.753422042733
        goal_test.x = stage_check[0]
        goal_test.y = stage_check[1]
        goal_test.z = stage_check[2]
        goal_test.w = stage_check[3]
        nav_info_msg = "proceeding"
        main_pub.publish(nav_info_msg)
        
        move_to(goal_test)

        while((abs(current_pose.pose.pose.position.x - goal_test.x) > error) or (abs(current_pose.pose.pose.position.y - goal_test.y) > error)):
            pass
        
        if(curr.qt_num < 5 and curr.qt_num > 0):
            if(i == 0):
                clean_pub_msg = "start"
                clean_pub.publish(clean_pub_msg)
                while(curr.clean_info == "yet"):
                    print("clean wait")
                curr.clean_info = "yet"
            if(i>0 and i<4):
                clean_pub_msg = "clean"
                clean_pub.publish(clean_pub_msg)
                while(curr.clean_info == "yet"):
                    print("clean wait")
                curr.clean_info = "yet"
            if(i == 4):
                round_pub_msg = "start"
                round_pub.publish(round_pub_msg)
                while(curr.round_info == "yet"):
                    print("clean wait") 
                curr.round_info = "yet"
                round_pub_msg = "stop"
                round_pub.publish(round_pub_msg)

                clean_pub_msg = "stop"
                clean_pub.publish(clean_pub_msg)           
                while(curr.clean_info == "yet"):
                    print("clean wait")         
                curr.clean_info = "yet"

    
    print("c")
    nav_info_msg = "done"
    main_pub.publish(nav_info_msg)
    curr.flag = 0
    curr.listFlag = 0
    curr.count += 1

    
    

if __name__=='__main__':
    current_pose = PoseWithCovarianceStamped()
    rospy.init_node('map_navigation_lis', anonymous=True)

    curr = con()
    main_pub = rospy.Publisher('nav_info', String, queue_size=10)
    clean_pub = rospy.Publisher('clean_start', String, queue_size=10)
    round_pub = rospy.Publisher('round_start', String, queue_size=10)


    odom_sub = rospy.Subscriber('/amcl_pose', PoseWithCovarianceStamped, callback)
    clean_sub = rospy.Subscriber('clean_info', String, cleanInfoCallback)
    round_sub = rospy.Subscriber('round_info', String, roundInfoCallback)


    tu_sub = rospy.Subscriber('nav_start', Int32, callbackRoom)
    ac = actionlib.SimpleActionClient("move_base", MoveBaseAction)
    ac.wait_for_server() # !!!!!!!!!!!!!!!!!!!!!!!!!!!

    rospy.spin()