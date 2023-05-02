#ifndef CHAIR3_DIALOG_H
#define CHAIR3_DIALOG_H

#include <QDialog>
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <cstdlib>



namespace Ui {
class Chair3_Dialog;
}

class Chair3_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Chair3_Dialog(QWidget *parent = nullptr);
    ~Chair3_Dialog();
    
private slots:
    void spinOnce();

    void on_cleanbtn_clicked();

    void on_movebtn_clicked();

    void on_cancel_clicked();

    // void buttonCallback(const std_msgs::String::ConstPtr& msg);

private:
    Ui::Chair3_Dialog *ui;
    // std::string chair_name_;
    ros::NodeHandle nh_;
    ros::ServiceClient client_;
};

#endif // CHAIR3_DIALOG_H
