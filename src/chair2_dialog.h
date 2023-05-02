#ifndef CHAIR2_DIALOG_H
#define CHAIR2_DIALOG_H

#include <QDialog>
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <cstdlib>



namespace Ui {
class Chair2_Dialog;
}

class Chair2_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Chair2_Dialog(QWidget *parent = nullptr);
    ~Chair2_Dialog();

private slots:
    void spinOnce();

    void on_cleanbtn_clicked();

    void on_movebtn_clicked();

    void on_cancel_clicked();

    // void buttonCallback(const std_msgs::String::ConstPtr& msg);

private:
    Ui::Chair2_Dialog *ui;
    ros::NodeHandle nh_;
    ros::ServiceClient client_;
};

#endif // CHAIR2_DIALOG_H
