#include "chair2_dialog.h"
#include "ui_chair2_dialog.h"
#include <captin_qt_pkg/qt_check.h>



Chair2_Dialog::Chair2_Dialog(QWidget *parent) :
    QDialog(parent),
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
    captin_qt_pkg::qt_check srv;
    srv.request.qt_req = "2";
    bool k = client_.call(srv);
}


void Chair2_Dialog::on_movebtn_clicked()
{
    captin_qt_pkg::qt_check srv;
    srv.request.qt_req = "22";
    bool k = client_.call(srv);
}


void Chair2_Dialog::on_cancel_clicked()
{
    close();
}


