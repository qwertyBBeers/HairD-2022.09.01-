#include "captain_mainwindow.h"
#include "ui_captain_mainwindow.h"


captain_mainwindow::captain_mainwindow(QWidget *parent)
    : QMainWindow(parent, Qt::FramelessWindowHint) //, Qt::FramelessWindowHint
    , ui(new Ui::captain_mainwindow)
{
    ui->setupUi(this);

}

captain_mainwindow::~captain_mainwindow()
{
    delete ui;
}


void captain_mainwindow::on_pushButton_clicked()
{
    QDesktopServices::openUrl(QUrl("https://map.naver.com/v5/search/%EC%83%B5%ED%99%8D/place/1961938317?placePath=%3Fentry%253Dpll&c=15,0,0,0,dh", QUrl::TolerantMode));
}


void captain_mainwindow::on_chair_btn_clicked()
{
  chair1_Dialog = new Chair1_Dialog;
  chair1_Dialog->setModal(true);
  chair1_Dialog->exec();

}


void captain_mainwindow::on_chair_btn_2_clicked()
{
   chair2_Dialog = new Chair2_Dialog;
//    chair2_Dialog->setChairName("2");
   chair2_Dialog->setModal(true);
   chair2_Dialog->exec();
}


void captain_mainwindow::on_chair_btn_3_clicked()
{
   chair3_Dialog = new Chair3_Dialog;
//    chair3_Dialog->setChairName("3");
   chair3_Dialog->setModal(true);
   chair3_Dialog->exec();
}



void captain_mainwindow::on_emptyButton_clicked()
{
    Empty_Dialog = new Empty_dialog;
    Empty_Dialog->setModal(true);
    Empty_Dialog->exec();
}

void captain_mainwindow::on_player_btn_clicked()
{
  QDesktopServices::openUrl(QUrl("https://www.youtube.com/watch?v=i_bJwt7uTwQ", QUrl::TolerantMode));

}
