#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path_db);
    this->DatabaseConnected = db.open();
    SelectAll();

    connect(ui->tableWidget, SIGNAL(cellDoubleClicked(int, int)), this, SLOT(SectionDoubleClick(int, int)));
    ui->tableWidget->setColumnWidth(0, 450);
    ui->tableWidget->setColumnWidth(1, 400);
    ui->tableWidget->setColumnWidth(2, 150);
    ui->tableWidget->setColumnWidth(3, 150);
    ui->tableWidget->setColumnWidth(4, 150);
    ui->tableWidget->setColumnWidth(5, 150);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SectionDoubleClick(int row, int column)  //NHẬN SIGNAL DOUBLE CLICK VÀ ĐIỀN DỮ LIỆU VÀ CÁC LINE EDIT
{
    column = 0;
    //========LẤY ID
    QString ID = ui->tableWidget->item(row, column)->text();
    qDebug()<<"ID DUOC CLICK LA: " << ID << endl;
    this->ID_DoubleCLick = ID.toInt();

    UpdateConnection();
    if(this->DatabaseConnected)
    {
        //Do some thing

        QSqlQuery query(db);
        QString QueryString = "SELECT * FROM LinhKien WHERE TenLK LIKE '" + ID + "'";
        query.prepare(QueryString);
        query.exec();
        while(query.next())
        {
            ui->lineEdit_TenLK->setText(query.value(0).toString());
            ui->lineEdit_MaLK->setText(query.value(1).toString()); //set datetime
            ui->lineEdit_DV->setText(query.value(2).toString());
            ui->lineEdit_SoLuong->setText(query.value(3).toString());
            QString loaiLK = query.value(4).toString();
            if(loaiLK != "RES" && loaiLK != "CAP" &&loaiLK != "JACK" &&loaiLK != "IC")
                ui->comboBox_loaiLK->setCurrentText("Khác");
            else
                ui->comboBox_loaiLK->setCurrentText(loaiLK);

            ui->lineEdit_ghichu->setText(query.value(5).toString());
        }
        //setDisabled all line edit
        foreach(QLineEdit* le, findChildren<QLineEdit*>())
        {
            if(le != ui->lineEdit_timkiem)
            {
                le->setDisabled(true);
            }
        }

        //        ui->pushButton->setDisabled(false);
        //        ui->pushButton_2->setDisabled(true); //ẩn nút lưu thông tin
        //        ui->pushButton_3->setDisabled(false);
        //        ui->pushButton_4->setDisabled(true); //ẩn nút cập nhật
        //        ui->pushButton_5->setDisabled(false);

        this->db.close();
    }
    else
    {
        QMessageBox::warning(this, "Warning", "Kết nối cơ sở dữ liệu không thành công. Vui lòng thử lại!");
    }
}

void MainWindow::UpdateConnection()
{
    this->db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path_db);
    this->DatabaseConnected = db.open();
}

void MainWindow::Seclect(QString LoaiLK)
{
    UpdateConnection();

    if(this->DatabaseConnected)
    {
        ui->tableWidget->clear();

        QSqlQuery query(db);
        query.prepare("select * from LinhKien where LoaiLK == '"+LoaiLK +"'");
        query.exec();

        ui->tableWidget->setColumnCount(6);
        QStringList list_labels;
        list_labels << "Tên linh kiện" << "Mã linh kiện" << "Đơn vị tính"
                    << "Số lượng tồn kho" << "Loại linh kiện" << "Ghi chú";
        ui->tableWidget->setHorizontalHeaderLabels(list_labels);

        int rowcount = 0;
        while(query.next())
        {
            ui->tableWidget->insertRow(rowcount);
            QTableWidgetItem *TenLK = new QTableWidgetItem;
            QTableWidgetItem * MaLK = new QTableWidgetItem;
            QTableWidgetItem *DVTinh = new QTableWidgetItem;
            QTableWidgetItem *SLTonKho = new QTableWidgetItem;
            QTableWidgetItem *LoaiLK = new QTableWidgetItem;
            QTableWidgetItem *GhiChu = new QTableWidgetItem;


            TenLK->setText(query.value(0).toString());
            MaLK->setText(query.value(1).toString());
            DVTinh->setText(query.value(2).toString());
            SLTonKho->setText(query.value(3).toString());
            LoaiLK->setText(query.value(4).toString());
            GhiChu->setText(query.value(5).toString());

            ui->tableWidget->setItem(rowcount, 0, TenLK);
            ui->tableWidget->setItem(rowcount, 1, MaLK);
            ui->tableWidget->setItem(rowcount, 2, DVTinh);
            ui->tableWidget->setItem(rowcount, 3, SLTonKho);
            ui->tableWidget->setItem(rowcount, 4, LoaiLK);
            ui->tableWidget->setItem(rowcount, 5, GhiChu);

            rowcount++;
        }
    }
}

void MainWindow::SelectAll()
{
    UpdateConnection();

    if(this->DatabaseConnected)
    {
        ui->tableWidget->clear();
        QSqlQuery query(db);
        query.prepare("SELECT * FROM LinhKien");
        query.exec();

        ui->tableWidget->setColumnCount(6);
        QStringList list_labels;
        list_labels << "Tên linh kiện" << "Mã linh kiện" << "Đơn vị tính"
                    << "Số lượng tồn kho" << "Loại linh kiện" << "Ghi chú";
        ui->tableWidget->setHorizontalHeaderLabels(list_labels);

        int rowcount = 0;
        while(query.next())
        {
            ui->tableWidget->insertRow(rowcount);
            QTableWidgetItem *TenLK = new QTableWidgetItem;
            QTableWidgetItem * MaLK = new QTableWidgetItem;
            QTableWidgetItem *DVTinh = new QTableWidgetItem;
            QTableWidgetItem *SLTonKho = new QTableWidgetItem;
            QTableWidgetItem *LoaiLK = new QTableWidgetItem;
            QTableWidgetItem *GhiChu = new QTableWidgetItem;


            TenLK->setText(query.value(0).toString());
            MaLK->setText(query.value(1).toString());
            DVTinh->setText(query.value(2).toString());
            SLTonKho->setText(query.value(3).toString());
            LoaiLK->setText(query.value(4).toString());
            GhiChu->setText(query.value(5).toString());

            ui->tableWidget->setItem(rowcount, 0, TenLK);
            ui->tableWidget->setItem(rowcount, 1, MaLK);
            ui->tableWidget->setItem(rowcount, 2, DVTinh);
            ui->tableWidget->setItem(rowcount, 3, SLTonKho);
            ui->tableWidget->setItem(rowcount, 4, LoaiLK);
            ui->tableWidget->setItem(rowcount, 5, GhiChu);

            rowcount++;
        }
    }
}

void MainWindow::on_pushButton_2_clicked()//trở
{
    ui->tableWidget->clear();
    Seclect("RES");
}

void MainWindow::on_pushButton_3_clicked()//tụ
{
    ui->tableWidget->clear();
    Seclect("CAP");
}

void MainWindow::on_pushButton_4_clicked()//ic
{
    ui->tableWidget->clear();
    Seclect("IC");
}

void MainWindow::on_pushButton_5_clicked()//jack
{
    ui->tableWidget->clear();
    Seclect("JACK");
}

void MainWindow::on_pushButton_6_clicked()//khác
{
    ui->tableWidget->clear();
    UpdateConnection();

    if(this->DatabaseConnected)
    {
        QSqlQuery query(db);
        query.prepare("SELECT * FROM LinhKien WHERE LoaiLK != 'RES' AND LoaiLK != 'CAP' AND LoaiLK != 'IC' AND LoaiLK != 'JACK'");
        query.exec();

        ui->tableWidget->setColumnCount(6);
        QStringList list_labels;
        list_labels << "Tên linh kiện" << "Mã linh kiện" << "Đơn vị tính"
                    << "Số lượng tồn kho" << "Loại linh kiện" << "Ghi chú";
        ui->tableWidget->setHorizontalHeaderLabels(list_labels);

        int rowcount = 0;
        while(query.next())
        {
            ui->tableWidget->insertRow(rowcount);
            QTableWidgetItem *TenLK = new QTableWidgetItem;
            QTableWidgetItem * MaLK = new QTableWidgetItem;
            QTableWidgetItem *DVTinh = new QTableWidgetItem;
            QTableWidgetItem *SLTonKho = new QTableWidgetItem;
            QTableWidgetItem *LoaiLK = new QTableWidgetItem;
            QTableWidgetItem *GhiChu = new QTableWidgetItem;


            TenLK->setText(query.value(0).toString());
            MaLK->setText(query.value(1).toString());
            DVTinh->setText(query.value(2).toString());
            SLTonKho->setText(query.value(3).toString());
            LoaiLK->setText(query.value(4).toString());
            GhiChu->setText(query.value(5).toString());

            ui->tableWidget->setItem(rowcount, 0, TenLK);
            ui->tableWidget->setItem(rowcount, 1, MaLK);
            ui->tableWidget->setItem(rowcount, 2, DVTinh);
            ui->tableWidget->setItem(rowcount, 3, SLTonKho);
            ui->tableWidget->setItem(rowcount, 4, LoaiLK);
            ui->tableWidget->setItem(rowcount, 5, GhiChu);

            rowcount++;
        }
    }
}
