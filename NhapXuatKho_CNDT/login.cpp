#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_clicked() // Login
{
    QString usernam = ui->lineEditUser->text();
    QString password = ui->lineEditPass->text();

    if(usernam == "admin" && password == "admin")
    {
        emit LoginSuccessful("admin");
        this->close();
    }
    else
    {
        QMessageBox::information(this, "Report", "Login information is wroing, Enter again!");
    }
}
