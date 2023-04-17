import rospy
from std_msgs.msg import String

def yoloCallback(data):
    print(data.data)

def talker():
    pub = rospy.Publisher('yolo_start', String, queue_size=10)
    rospy.Subscriber("yolo_info",String,yoloCallback)
    rospy.init_node('main',anonymous=True)
    rate = rospy.Rate(10)
    while not rospy.is_shutdown():
        pub.publish("start")
        rate.sleep()
        


if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException:
        pass
    
    