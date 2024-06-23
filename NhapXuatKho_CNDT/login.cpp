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


        /* bool temp = false;
        if (query.exec())
        {
            qDebug() << "---------------------SQLITE  EXEC"<< endl;
            while (query.next())
            {
                QString role = query.value(0).toString();
                qDebug()<< "======= role trong login la: " << role << endl;
                emit LoginSuccessful(role);
                //managePermissions(role);
                temp = true;
            }
            if(temp)
            {
                QMessageBox::warning(this, "Login Failed", "Invalid username or password");
            }
        }
        else
        {
            qDebug() << "Query execution error:" << query.lastError().text();
            //            qDebug() << "Executed query:" << query.lastQuery();
            //            qDebug() << "Database open status:" << db.isOpen();
        }*/

        if (query.exec()) {
            if (query.next()) {
                QString role = query.value(0).toString();
                emit LoginSuccessful(role);
            } else {
                QMessageBox::warning(this, "Login Failed", "Invalid username or password");
            }
        } else {
            qDebug() << "Query execution error:" << query.lastError();
        }

    }
    else
    {
        qDebug() << "---------------------SQLITE CANNOT CONNTECTED"<< endl;
    }
}
