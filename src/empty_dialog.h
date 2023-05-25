#ifndef EMPTY_DIALOG_H
#define EMPTY_DIALOG_H

#include <QDialog>
#include <ros/ros.h>
#include <cstdlib>

namespace Ui {
class Empty_dialog;
}

class Empty_dialog : public QDialog
{
  Q_OBJECT

public:
  explicit Empty_dialog(QWidget *parent = nullptr);
  ~Empty_dialog();

private slots:

  void spinOnce();
  void on_empty_btn_clicked();

  void on_cancel_btn_clicked();

private:
  Ui::Empty_dialog *ui;
  ros::NodeHandle nh_;
  ros::ServiceClient client_;
};

#endif // EMPTY_DIALOG_H
