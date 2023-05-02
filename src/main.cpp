#include "captain_mainwindow.h"
#include <QApplication>
#include "ros/ros.h"

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "captin_qt_node");
    // ros::init(argc, argv, "captin_qt_node",ros::init_options::AnonymousName);

    QApplication a(argc, argv);
    captain_mainwindow w;
    // w.setWindowTitle(QString::fromStdString(ros::this_node::getName()));
    w.show();
    // ros::spin();
    return a.exec();



}
