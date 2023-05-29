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

  ui->empty_btn->setStyleSheet("QPushButton { color:#506975; border-width:1px; background: white; border-radius: 10px; border: none; }"
                                "QPushButton:pressed { background-color: #536a77;color:white; border-width:1px; border-radius: 10px; border: none;}");


  captin_qt_pkg::et_check srv;
  srv.request.et_req = "100";
  bool k = client_.call(srv);
  std::cout << "check_empty" << std::endl;
  close();

}

void Empty_dialog::on_cancel_btn_clicked()
{
  close();
}
