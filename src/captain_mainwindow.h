#ifndef CAPTAIN_MAINWINDOW_H
#define CAPTAIN_MAINWINDOW_H

#include <QMainWindow>
#include <QDesktopServices>
#include <QUrl>
#include <ros/ros.h>
#include "chair1_dialog.h"
#include "chair2_dialog.h"
#include "chair3_dialog.h"


QT_BEGIN_NAMESPACE
namespace Ui { class captain_mainwindow; }
QT_END_NAMESPACE

class captain_mainwindow : public QMainWindow
{
    Q_OBJECT

public:
    captain_mainwindow(QWidget *parent = nullptr);
    ~captain_mainwindow();

private slots:
    void on_pushButton_clicked();

    void on_chair_btn_clicked();

    void on_chair_btn_2_clicked();

    void on_chair_btn_3_clicked();

private:
    Ui::captain_mainwindow *ui;
    // ros::NodeHandle nh_;

    Chair1_Dialog *chair1_Dialog;
    Chair2_Dialog *chair2_Dialog;
    Chair3_Dialog *chair3_Dialog;
};
#endif // CAPTAIN_MAINWINDOW_H
