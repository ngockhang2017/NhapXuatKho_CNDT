#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include<QMessageBox>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QDebug>
#include<QSqlError>

namespace Ui {
class Login;
}

class Login : public QMainWindow
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();
public:
    QSqlDatabase db;
    bool DatabaseConnected;
    QString path_db = "C:\\Users\\ngock\\OneDrive\\Documents\\GitHub\\NhapXuatKho_CNDT\\quanlykho";

    void UpdateConnection();

private slots:
    void on_pushButton_clicked();

signals:
    void LoginSuccessful(const QString &role);

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
