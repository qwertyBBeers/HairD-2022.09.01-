#include "chair2_dialog.h"
#include "ui_chair2_dialog.h"
#include <captin_qt_pkg/qt_check.h>



Chair2_Dialog::Chair2_Dialog(QWidget *parent) :
    QDialog(parent, Qt::FramelessWindowHint),
    ui(new Ui::Chair2_Dialog)
{
    ui->setupUi(this);
    client_ = nh_.serviceClient<captin_qt_pkg::qt_check>("qt_service");
    captin_qt_pkg::qt_check srv;
}

Chair2_Dialog::~Chair2_Dialog()
{
    delete ui;
}

void Chair2_Dialog::spinOnce()
{
    if(ros::ok()){
        ros::spinOnce();
    }
    else
        QApplication::quit();
}


void Chair2_Dialog::on_cleanbtn_clicked()
{
    ui->cleanbtn->setStyleSheet("QPushButton { color : #506975; background: white; border-width: 2px; border-radius: 10px; }"
                                "QPushButton:pressed { background-color: #536a77; color:white; border-width: 2px; border-radius: 10px; }");
    captin_qt_pkg::qt_check srv;
    srv.request.qt_req = "2";
    bool k = client_.call(srv);
}


void Chair2_Dialog::on_movebtn_clicked()
{
    ui->movebtn->setStyleSheet("QPushButton { color : #506975; background: white; border-width: 2px; border-radius: 10px; }"
                                "QPushButton:pressed { background-color: #536a77; color:white; border-width: 2px; border-radius: 10px; }");
    captin_qt_pkg::qt_check srv;
    srv.request.qt_req = "22";
    bool k = client_.call(srv);
}


void Chair2_Dialog::on_cancel_clicked()
{
    close();
}


