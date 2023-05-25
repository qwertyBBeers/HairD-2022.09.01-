#include "empty_dialog.h"
#include "ui_empty_dialog.h"
#include <captin_qt_pkg/et_check.h>


Empty_dialog::Empty_dialog(QWidget *parent) :
  QDialog(parent, Qt::FramelessWindowHint),
  ui(new Ui::Empty_dialog)
{
  ui->setupUi(this);
  client_ = nh_.serviceClient<captin_qt_pkg::et_check>("et_service");
  captin_qt_pkg::et_check srv;
}

Empty_dialog::~Empty_dialog()
{
  delete ui;
}

void Empty_dialog::spinOnce(){
  if(ros::ok()){
    ros::spinOnce();
  }
  else
      QApplication::quit();
}

void Empty_dialog::on_empty_btn_clicked()
{
  captin_qt_pkg::et_check srv;
  srv.request.et_req = "100";
  bool k = client_.call(srv);
  std::cout << "check_empty" << std::endl;
}

void Empty_dialog::on_cancel_btn_clicked()
{
  close();
}
