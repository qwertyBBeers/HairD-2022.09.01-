#include "captain_mainwindow.h"
#include <QApplication>
#include <QFontDatabase>
//#include <QGuiApplication>
//#include <QResource>
//#include <QFont>
#include "ros/ros.h"

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "captin_qt_node");
    QApplication a(argc, argv);

    QString fontPath = ":/fonts/Binggrae_Bold.ttf";
    int fontId = QFontDatabase::addApplicationFont(fontPath);
    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont font(fontFamily, 12); // 글꼴 이름과 크기를 지정합니다.
    QApplication::setFont(font);

//    QFontDatabase::addApplicationFont(":/fonts/Binggrae.ttf");
//    QFont font("Binggrae.ttf");
//    QApplication::setFont(font);

//    QFont font;
//    font.setFamily(":/fonts/Binggrae_Bold.ttf");
//    QApplication::setFont(font);


    captain_mainwindow w;
    w.show();
    return a.exec();

}
