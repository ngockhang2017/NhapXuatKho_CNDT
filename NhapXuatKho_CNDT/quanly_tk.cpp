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

    ui->lineEdit_MatKhau->setEchoMode(QLineEdit::PasswordEchoOnEdit);
    ui->widget_6->setMaximumHeight(50);

    ui->pushButton_Luu->setDisabled(true);
    ui->pushButton_CapNhat->setDisabled(true);
    ui->pushButton_XoaTK->setDisabled(true);

    connect(ui->tableWidget, SIGNAL(cellDoubleClicked(int, int)), this, SLOT(SectionDoubleClick(int, int)));

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


void QuanLy_TK::on_pushButton_BatDauThem_clicked()//Bắt đầu thêm tài khoản mới
{
    foreach(QLineEdit* le, findChildren<QLineEdit*>())
    {
        le->clear();
    }

    ui->pushButton_Luu->setDisabled(false);
}

void QuanLy_TK::on_lineEdit_MatKhau_textEdited(const QString &arg1)
{
    ui->lineEdit_MatKhau->setEchoMode(QLineEdit::Normal);
}

void QuanLy_TK::on_lineEdit_MatKhau_editingFinished()
{
    ui->lineEdit_MatKhau->setEchoMode(QLineEdit::Password);
}

void QuanLy_TK::on_pushButton_pressed() ///xem mật khẩu
{
    ui->lineEdit_MatKhau->setEchoMode(QLineEdit::Normal);
}

void QuanLy_TK::on_pushButton_released()///Ngừng xem mật khẩu
{
    ui->lineEdit_MatKhau->setEchoMode(QLineEdit::Password);
}

void QuanLy_TK::on_pushButton_Luu_clicked() //Lưu tài khoản mới này
{
    QString User = ui->lineEdit_TenTK->text();
    QString Pass = ui->lineEdit_MatKhau->text();
    QString Role = "";

    int QuyenTruyCap = ui->comboBox_QuyenTruyCap->currentIndex();
    if(QuyenTruyCap == 0)
        Role = "admin";
    else if(QuyenTruyCap == 1)
        Role = "ql";
    else if(QuyenTruyCap == 2)
        Role = "nvkt";

    if(User == "" || Pass == "" || Role == "")
        QMessageBox::warning(this, "Thông báo", "Thông tin Tài khoản chưa được cung cấp đầy đủ, hãy thử lại!");
    else
    {
        this->UpdateConnection();
        if(this->DatabaseConnected)
        {
            QSqlQuery qry(this->db);
            qry.prepare("INSERT INTO TaiKhoan ( User, Pass, Role) "
                        "VALUES (:User, :Pass, :Role)");

            qry.bindValue(":User", User);
            qry.bindValue(":Pass", Pass);
            qry.bindValue(":Role", Role);

            if(qry.exec())
            {
                QMessageBox::information(this, "Thông báo", "Thêm Tài khoản thành công!");
                foreach(QLineEdit* le, findChildren<QLineEdit*>())
                {
                    le->clear();
                }
            }
            else
            {
                QMessageBox::warning(this, "Thông báo", "Thêm Tài khoản KHÔNG thành công. Xin hãy thử lại!");
            }
            this->db.close();

            LoadAll();
        }
        else
        {
            QMessageBox::warning(this, "Warning", "Kết nối cơ sở dữ liệu không thành công. Vui lòng thử lại!");
        }
    }
}

void QuanLy_TK::SectionDoubleClick(int row, int column)
{
    column = 0;//Lấy từ khóa là cột đầu tiên
    //========LẤY ID
    QString User_ID = ui->tableWidget->item(row, column)->text();
    qDebug()<<"User DUOC CLICK LA: " << User_ID << endl;
    this->User = User_ID;

    UpdateConnection();
    if(this->DatabaseConnected)
    {
        QSqlQuery query(db);
        QString QueryString = "SELECT * FROM TaiKhoan WHERE User LIKE '" + User + "'";
        query.prepare(QueryString);
        query.exec();
        while(query.next())
        {
            ui->lineEdit_TenTK->setText(query.value(0).toString());
            ui->lineEdit_MatKhau->setText(query.value(1).toString());
            QString QuyenTruyCap = query.value(2).toString();

            if(QuyenTruyCap == "admin")
                ui->comboBox_QuyenTruyCap->setCurrentIndex(0);
            else if (QuyenTruyCap == "ql")
                ui->comboBox_QuyenTruyCap->setCurrentIndex(1);
            else if(QuyenTruyCap == "nvkt")
                ui->comboBox_QuyenTruyCap->setCurrentIndex(2);
        }
        this->db.close();
    }
    else
    {
        QMessageBox::warning(this, "Warning", "Kết nối cơ sở dữ liệu không thành công. Vui lòng thử lại!");
    }
}
