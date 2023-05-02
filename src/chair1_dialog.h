#ifndef CHAIR1_DIALOG_H
#define CHAIR1_DIALOG_H

#include <QDialog>
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <cstdlib>

namespace Ui {
class Chair1_Dialog;
}

class Chair1_Dialog : public QDialog
{
  Q_OBJECT

public:
  explicit Chair1_Dialog(QWidget *parent = nullptr);
  ~Chair1_Dialog();

private slots:
  void spinOnce();
  void on_cleanbtn_clicked();
  void on_movebtn_clicked();
  void on_cancel_clicked();
  // void buttonCallback(const std_msgs::String::ConstPtr& msg);

private:
  Ui::Chair1_Dialog *ui;
  // std::string chair_name_;
  ros::NodeHandle nh_;
  ros::ServiceClient client_;
};

#endif // CHAIR1_DIALOG_H
