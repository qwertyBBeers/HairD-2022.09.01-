#include "chair1_dialog.h"
#include "ui_chair1_dialog.h"
#include <captin_qt_pkg/qt_check.h>

Chair1_Dialog::Chair1_Dialog(QWidget *parent) :
  QDialog(parent, Qt::FramelessWindowHint),
  ui(new Ui::Chair1_Dialog)
{
  ui->setupUi(this);
  client_ = nh_.serviceClient<captin_qt_pkg::qt_check>("qt_service");
  captin_qt_pkg::qt_check srv;
}

Chair1_Dialog::~Chair1_Dialog()
{
  delete ui;
}

void Chair1_Dialog::spinOnce(){
  if(ros::ok()){
    ros::spinOnce();
  }
  else
      QApplication::quit();
}
void Chair1_Dialog::on_cleanbtn_clicked()
{
  ui->cleanbtn->setStyleSheet("QPushButton { color : #506975; background: white; border-width: 2px; border-radius: 10px; }"
                              "QPushButton:pressed { background-color: #536a77; color:white; border-width: 2px; border-radius: 10px; }");
  captin_qt_pkg::qt_check srv;
  srv.request.qt_req = "1";
  bool k = client_.call(srv);
  std::cout << "check_clean" << std::endl;

}


void Chair1_Dialog::on_movebtn_clicked()
{
    ui->movebtn->setStyleSheet("QPushButton { color : #506975; background: white; border-width: 2px; border-radius: 10px; }"
                                "QPushButton:pressed { background-color: #536a77; color:white; border-width: 2px; border-radius: 10px; }");
   captin_qt_pkg::qt_check srv;
   srv.request.qt_req = "11" ;
   bool k = client_.call(srv);
    std::cout << "checkmove" << std::endl;
}


void Chair1_Dialog::on_cancel_clicked()
{
    close();
}


