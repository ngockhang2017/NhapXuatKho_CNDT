#include "mainwindow.h"
#include "login.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Login login;
    login.show();
    QObject::connect(&login, &Login::LoginSuccessful, &w, &MainWindow::show);
//    QObject::connect(&w, &MainWindow::show, &login, &Login::close);
//    w.show();
    return a.exec();
}
