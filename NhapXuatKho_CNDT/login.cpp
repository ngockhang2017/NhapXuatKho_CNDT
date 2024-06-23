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

void Login::UpdateConnection()
{
    this->db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path_db);
    this->DatabaseConnected = db.open();
}

void Login::on_pushButton_clicked() // Login
{
    QString username = ui->lineEditUser->text();
    QString password = ui->lineEditPass->text();

    if (username.isEmpty() || password.isEmpty())
    {
        QMessageBox::warning(this, "Login Failed", "Please enter both username and password");
        return;
    }

    UpdateConnection();
    if(this->DatabaseConnected)
    {

        QSqlQuery query(db);
        query.prepare("select * FROM TaiKhoan WHERE User == :user AND Pass == :pass");
        query.bindValue(":user", username);
        query.bindValue(":pass", password);

        if (query.exec()) {
            if (query.next()) {
                QString role = query.value(0).toString();
                emit LoginSuccessful(role);
                this->close();
            }
            else
            {
                QMessageBox::warning(this, "Login Failed", "Invalid username or password");
                ui->lineEditPass->clear();
                ui->lineEditUser->clear();
            }
        }
        else
            qDebug() << "Query execution error:" << query.lastError();
    }
    else
        qDebug() << "---------------------SQLITE CANNOT CONNTECTED"<< endl;
}

void Login::on_pushButton_2_clicked()
{
    QApplication::quit();
}

void Login::on_lineEditPass_editingFinished()
{
    on_pushButton_clicked();
}

void Login::on_lineEditUser_editingFinished()
{
    ui->lineEditPass->setFocus();
}
