#include "quanly_tk.h"
#include "ui_quanly_tk.h"

QuanLy_TK::QuanLy_TK(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QuanLy_TK)
{
    ui->setupUi(this);
    LoadAll();
    ui->tableWidget->setColumnWidth(0, 150);
    ui->tableWidget->setColumnWidth(1, 150);
    ui->tableWidget->setColumnWidth(2, 250);
}

QuanLy_TK::~QuanLy_TK()
{
    delete ui;
}

void QuanLy_TK::UpdateConnection()
{
    this->db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path_db);
    this->DatabaseConnected = db.open();
}

void QuanLy_TK::LoadAll()
{
    UpdateConnection();

    if(this->DatabaseConnected)
    {
        ui->tableWidget->clear();
        QSqlQuery query(db);
        query.prepare("SELECT * FROM TaiKhoan");
        query.exec();

        ui->tableWidget->setColumnCount(3);
        QStringList list_labels;
        list_labels << "Tên đăng nhập" << "Mật khẩu" << "Cấp độ truy cập của tài khoản";
        ui->tableWidget->setHorizontalHeaderLabels(list_labels);

        int rowcount = 0;
        while(query.next())
        {
            ui->tableWidget->insertRow(rowcount);
            QTableWidgetItem *User = new QTableWidgetItem;
            QTableWidgetItem * Pass = new QTableWidgetItem;
            QTableWidgetItem *Role = new QTableWidgetItem;

            User->setText(query.value(0).toString());
            Pass->setText(query.value(1).toString());
            Role->setText(query.value(2).toString());

            ui->tableWidget->setItem(rowcount, 0, User);
            ui->tableWidget->setItem(rowcount, 1, Pass);
            ui->tableWidget->setItem(rowcount, 2, Role);

            rowcount++;
        }
        this->db.close();
    }
}

void QuanLy_TK::Select(QString loaiTK)
{
    UpdateConnection();

    if(this->DatabaseConnected)
    {
        ui->tableWidget->clear();

        QSqlQuery query(db);
        query.prepare("select * from TaiKhoan where Role == '"+ loaiTK +"'");
        query.exec();

        ui->tableWidget->setColumnCount(3);
        QStringList list_labels;
        list_labels << "Tên đăng nhập" << "Mật khẩu" << "Cấp độ truy cập của tài khoản";
        ui->tableWidget->setHorizontalHeaderLabels(list_labels);

        int rowcount = 0;
        while(query.next())
        {
            ui->tableWidget->insertRow(rowcount);
            QTableWidgetItem *User = new QTableWidgetItem;
            QTableWidgetItem * Pass = new QTableWidgetItem;
            QTableWidgetItem *Role = new QTableWidgetItem;

            User->setText(query.value(0).toString());
            Pass->setText(query.value(1).toString());
            Role->setText(query.value(2).toString());

            ui->tableWidget->setItem(rowcount, 0, User);
            ui->tableWidget->setItem(rowcount, 1, Pass);
            ui->tableWidget->setItem(rowcount, 2, Role);

            rowcount++;
        }
        this->db.close();
    }
}

void QuanLy_TK::on_comboBox_currentIndexChanged(const QString &arg1)
{
    ui->tableWidget->clear();
    ui->tableWidget->scrollToTop();

    if(arg1 == "Admin")
        Select("admin");
    else if(arg1 == "Quản lý kho")
        Select("ql");
    else if(arg1 == "Kỹ thuật viên")
        Select("nvkt");
}

