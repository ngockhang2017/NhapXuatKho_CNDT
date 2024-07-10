#include "tk_canhan.h"
#include "ui_tk_canhan.h"

TK_CaNhan::TK_CaNhan(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TK_CaNhan)
{
    ui->setupUi(this);

    ui->lineEdit_tenTK->setText(this->TenTK);
}

TK_CaNhan::~TK_CaNhan()
{
    delete ui;
}

void TK_CaNhan::UpdateConnection()
{
    this->db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path_db);
    this->DatabaseConnected = db.open();
}


void TK_CaNhan::showEvent(QShowEvent *event) {
    QWidget::showEvent(event);

    UpdateConnection();

    if(this->DatabaseConnected)
    {
        QSqlQuery query(db);
        query.prepare("select * from TaiKhoan where User == '"+ this->TenTK +"'");
        query.exec();

        while(query.next())
        {
            ui->lineEdit_tenTK->setText(query.value(0).toString());
            ui->lineEdit_Quyen->setText(query.value(2).toString());
            ui->lineEdit_mk->setText(query.value(1).toString());
        }
        this->db.close();
    }
}

void TK_CaNhan::on_pushButton_luu_clicked()  //lưu mật khẩu vừa nhập
{
    QString Pass = ui->lineEdit_mk->text();
    QString User = ui->lineEdit_tenTK->text();

    this->UpdateConnection();
    if(this->DatabaseConnected)
    {
        QSqlQuery qry(this->db);
        qry.prepare("UPDATE TaiKhoan SET Pass=:Pass WHERE User=:User");

        qry.bindValue(":Pass", Pass);
        qry.bindValue(":User", User);

        if(qry.exec())
            QMessageBox::information(this, "Thông báo", "Cập nhật thông tin linh kiện thành công!");

        else
            QMessageBox::warning(this, "Thông báo", "Cập nhật thông tin không thành công. Xin hãy thử lại!");

        this->db.close();
    }
    else
    {
        QMessageBox::warning(this, "Warning", "Kết nối cơ sở dữ liệu không thành công. Vui lòng thử lại!");
    }
}
