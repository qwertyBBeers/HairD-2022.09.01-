#!/usr/bin/python3

import rospy
from std_msgs.msg import Int32
from std_msgs.msg import Float32MultiArray
from std_msgs.msg import String

def talker():
    rate = rospy.Rate(10) # 10hz

    arr_stage_1 = 1
    arr_stage_2 = 2
    arr_stage_3 = 3

    rospy.loginfo("When you press on 'a','b','c', your robot will go to the goal!!!")

    while not rospy.is_shutdown():
        t = input()
        rospy.loginfo(t)
        if (t == "a"):
            rospy.loginfo("gogo!")
            tu_pub.publish(arr_stage_1)
        elif (t == "b"):
            rospy.loginfo("gogo!")
            tu_pub.publish(arr_stage_2)
        elif (t == "c"):
            rospy.loginfo("gogo!")
            tu_pub.publish(arr_stage_3)

        rate.sleep()

if __name__ == '__main__':
    try:
        rospy.init_node('map_navigation_tal', anonymous=True)
        tu_pub = rospy.Publisher('stage_info', Int32, queue_size=1)
        talker()
    except rospy.ROSInterruptException:
        pass