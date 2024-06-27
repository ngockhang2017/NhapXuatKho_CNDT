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
//    QString path_db = "C:\\Users\\ngock\\OneDrive\\Documents\\GitHub\\NhapXuatKho_CNDT\\NhapXuatKho_CNDT\\DATABASE\\QLK_DATABASE";
     QString path_db = "D:\\PM_QLK\\DATABASE\\QLK_DATABASE";
    void UpdateConnection();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_lineEditPass_editingFinished();

    void on_lineEditUser_editingFinished();

signals:
    void LoginSuccessful(const QString &role, const QString &user);

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
