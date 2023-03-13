import rospy
from std_msgs.msg import String

def callback(data):
    rospy.loginfo(rospy.get_caller_id() + "centerpoint is %s",data.data)

def listener():

    rospy.init_node('qr_receive',anonymous =True)
    rospy.Subscriber("qr",String,callback)
    rospy.spin()

if __name__ == '__main__':
    listener()