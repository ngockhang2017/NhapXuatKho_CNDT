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
    ui->tableWidget->setColumnWidth(1, 200);
    ui->tableWidget->setColumnWidth(2, 150);
    ui->tableWidget->setColumnWidth(3, 150);
    ui->tableWidget->setColumnWidth(4, 150);
    ui->tableWidget->setColumnWidth(5, 300);

    //bảng giỏ linh kiện
    ui->tableWidget_2->setColumnCount(6);
    QStringList list_labels;
    list_labels << "Tên linh kiện" << "Mã linh kiện" << "Đơn vị tính"
                << "Số lượng tồn kho" << "Loại linh kiện" << "Ghi chú";
    ui->tableWidget_2->setHorizontalHeaderLabels(list_labels);

    //Gợi ý tìm kiếm
    QStringList wordList;
    wordList = LoadTenLK();

    QCompleter *completer = new QCompleter(wordList, ui->lineEdit_timkiem);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    ui->lineEdit_timkiem->setCompleter(completer);

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
    this->ID_DoubleCLick = ID;

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

        ui->pushButton_10->setDisabled(false); //thêm vào giỏ
        ui->pushButton_11->setDisabled(true); //lưu
        ui->pushButton_12->setDisabled(false); //bắt đầu thêm
        ui->pushButton_13->setDisabled(false); //xóa lk này
        ui->pushButton_14->setDisabled(false);  //sửa lk này
        ui->pushButton_17->setDisabled(true);//cập nhật
        ui->pushButton_20->setDisabled(true); //hủy sửa

        ui->tab->show();
        ui->tab_2->close();
        ui->tab_3->close();
        ui->tab_4->close();

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

void MainWindow::on_pushButton_14_clicked()//bắt đầu sửa thông tin linh kiện
{
    //setDisabled all line edit
    foreach(QLineEdit* le, findChildren<QLineEdit*>())
    {
        le->setDisabled(false);
    }

    ui->pushButton_10->setDisabled(true); //thêm vào giỏ
    ui->pushButton_11->setDisabled(true); //lưu
    ui->pushButton_12->setDisabled(true); //bắt đầu thêm
    ui->pushButton_13->setDisabled(true); //xóa lk này
    ui->pushButton_14->setDisabled(true);  //bắt đầu sửa
    ui->pushButton_17->setDisabled(false);//cập nhật
    ui->pushButton_20->setDisabled(false); //hủy sửa
}

void MainWindow::on_pushButton_17_clicked()  //Cập nhật linh kiện
{

    QString LoaiLK = ui->comboBox_loaiLK->currentText();
    QString TenLK = ui->lineEdit_TenLK->text();
    QString MaLK = ui->lineEdit_MaLK->text();
    QString DVTinh = ui->lineEdit_DV->text();
    QString SLTonKho = ui->lineEdit_SoLuong->text();
    QString GhiChu = ui->lineEdit_ghichu->text();

    this->UpdateConnection();
    if(this->DatabaseConnected)
    {
        QSqlQuery qry(this->db);
        qry.prepare("UPDATE LinhKien SET TenLK=:TenLK, DonVi=:DonVi, SoLuongConLai=:SoLuongConLai, LoaiLK=:LoaiLK, "
                    "GhiChu=:GhiChu WHERE MaLK=:MaLK");

        //  qry.bindValue(":id", 50);
        qry.bindValue(":TenLK", TenLK);
        qry.bindValue(":MaLK", MaLK);
        qry.bindValue(":DonVi", DVTinh);
        qry.bindValue(":SoLuongConLai", SLTonKho);
        qry.bindValue(":LoaiLK", LoaiLK);
        qry.bindValue(":GhiChu", GhiChu);

        if(qry.exec())
        {
            QMessageBox::information(this, "Thông báo", "Cập nhật thông tin linh kiện thành công!");
            foreach(QLineEdit* le, findChildren<QLineEdit*>())
            {
                le->setDisabled(true);
            }

            //            foreach(QTextEdit* le, findChildren<QTextEdit*>())
            //            {
            //                le->clear();
            //            }
            ui->pushButton_10->setDisabled(false); //thêm vào giỏ
            ui->pushButton_11->setDisabled(true); //lưu
            ui->pushButton_12->setDisabled(false); //bắt đầu thêm
            ui->pushButton_13->setDisabled(false); //xóa lk này
            ui->pushButton_14->setDisabled(false);  //sửa lk này
            ui->pushButton_17->setDisabled(true);//cập nhật
            ui->pushButton_20->setDisabled(true); //hủy sửa
        }
        else
        {
            QMessageBox::warning(this, "Thông báo", "Cập nhật thông tin không thành công. Xin hãy thử lại!");
        }
    }
    else
    {
        QMessageBox::warning(this, "Warning", "Kết nối cơ sở dữ liệu không thành công. Vui lòng thử lại!");
    }
}

void MainWindow::on_pushButton_20_clicked()//hủy sửa linh kiện
{
    foreach(QLineEdit* le, findChildren<QLineEdit*>())
    {
        le->clear();
        le->setDisabled(true);
    }
    ui->pushButton_10->setDisabled(true); //thêm vào giỏ
    ui->pushButton_11->setDisabled(true); //lưu
    ui->pushButton_12->setDisabled(false); //bắt đầu thêm
    ui->pushButton_13->setDisabled(true); //xóa lk này
    ui->pushButton_14->setDisabled(true);  //sửa lk này
    ui->pushButton_17->setDisabled(true);//cập nhật
    ui->pushButton_20->setDisabled(true); //hủy sửa
}

void MainWindow::on_pushButton_13_clicked() //xóa linh kiện
{
    if(ui->lineEdit_MaLK->text() != "")
    {
        UpdateConnection();
        if(this->DatabaseConnected)
        {
            QSqlQuery qry(this->db);
            qry.prepare("DELETE FROM LinhKien WHERE MaLK=:MaLK");
            qry.bindValue(":MaLK", ui->lineEdit_MaLK->text());

            if(qry.exec())
            {
                this->db.close(); //đóng kết nối database cũ
                QMessageBox::information(this, "Thông báo", "Xóa linh kiện thành công!");
                foreach(QLineEdit* le, findChildren<QLineEdit*>())
                {
                    le->clear();
                    le->setDisabled(true);
                }
                ui->pushButton_10->setDisabled(true); //thêm vào giỏ
                ui->pushButton_11->setDisabled(true); //lưu
                ui->pushButton_12->setDisabled(false); //bắt đầu thêm
                ui->pushButton_13->setDisabled(true); //xóa lk này
                ui->pushButton_14->setDisabled(true);  //sửa lk này
                ui->pushButton_17->setDisabled(true);//cập nhật
                ui->pushButton_20->setDisabled(true); //hủy sửa
            }
            this->db.close();
        }
        else
        {
            QMessageBox::warning(this, "Warning", "Kết nối cơ sở dữ liệu không thành công. Vui lòng thử lại!");
        }
    }
    else
        QMessageBox::warning(this, "Warning", "Trường mã linh kiện đang trống!!!");
}

void MainWindow::on_pushButton_12_clicked()  //bắt đầu thêm mới linh kiện
{
    foreach(QLineEdit* le, findChildren<QLineEdit*>())
    {
        if(le != ui->lineEdit_timkiem)
        {
            le->clear();
        }
    }

}

void MainWindow::on_pushButton_10_clicked()///thêm vào giỏ
{
    int row = ui->tableWidget_2->rowCount();
    ui->tableWidget_2->insertRow(row);

    QTableWidgetItem *TenLK1 = new QTableWidgetItem;
    QTableWidgetItem * MaLK1 = new QTableWidgetItem;
    QTableWidgetItem *DVTinh1 = new QTableWidgetItem;
    QTableWidgetItem *SLTonKho1 = new QTableWidgetItem;
    QTableWidgetItem *LoaiLK1 = new QTableWidgetItem;
    QTableWidgetItem *GhiChu1 = new QTableWidgetItem;

    TenLK1->setText(ui->lineEdit_TenLK->text());
    MaLK1->setText(ui->lineEdit_MaLK->text());
    DVTinh1->setText(ui->lineEdit_DV->text());
    SLTonKho1->setText(ui->lineEdit_SoLuong->text());
    LoaiLK1->setText(ui->comboBox_loaiLK->currentText());
    GhiChu1->setText(ui->lineEdit_ghichu->text());

    ui->tableWidget_2->setItem(row, 0, TenLK1);
    ui->tableWidget_2->setItem(row, 1, MaLK1);
    ui->tableWidget_2->setItem(row, 2, DVTinh1);
    ui->tableWidget_2->setItem(row, 3, SLTonKho1);
    ui->tableWidget_2->setItem(row, 4, LoaiLK1);
    ui->tableWidget_2->setItem(row, 5, GhiChu1);
}

void MainWindow::on_pushButton_11_clicked()  //Lưu linh kiện mới
{
    QString LoaiLK = ui->comboBox_loaiLK->currentText();
    QString TenLK = ui->lineEdit_TenLK->text();
    QString MaLK = ui->lineEdit_MaLK->text();
    QString DVTinh = ui->lineEdit_DV->text();
    QString SLTonKho = ui->lineEdit_SoLuong->text();
    QString GhiChu = ui->lineEdit_ghichu->text();

    this->UpdateConnection();
    if(this->DatabaseConnected)
    {
        QSqlQuery qry(this->db);
        qry.prepare("INSERT INTO LinhKien ( TenLK, MaLK, DonVi, SoLuongConLai, LoaiLK, "
                    "GhiChu) "
                    "VALUES (:TenLK, :MaLK, :DonVi, :SoLuongConLai, :LoaiLK,"
                    ":GhiChu)");

        qry.bindValue(":TenLK", TenLK);
        qry.bindValue(":MaLK", MaLK);
        qry.bindValue(":DonVi", DVTinh);
        qry.bindValue(":SoLuongConLai", SLTonKho);
        qry.bindValue(":LoaiLK", LoaiLK);
        qry.bindValue(":GhiChu", GhiChu);

        if(qry.exec())
        {
            QMessageBox::information(this, "Thông báo", "Cập nhật thông tin linh kiện thành công!");
            foreach(QLineEdit* le, findChildren<QLineEdit*>())
            {
                le->setDisabled(true);
            }

            //            foreach(QTextEdit* le, findChildren<QTextEdit*>())
            //            {
            //                le->clear();
            //            }
            ui->pushButton_10->setDisabled(false); //thêm vào giỏ
            ui->pushButton_11->setDisabled(true); //lưu
            ui->pushButton_12->setDisabled(false); //bắt đầu thêm
            ui->pushButton_13->setDisabled(false); //xóa lk này
            ui->pushButton_14->setDisabled(false);  //sửa lk này
            ui->pushButton_17->setDisabled(true);//cập nhật
            ui->pushButton_20->setDisabled(true); //hủy sửa
        }
        else
        {
            QMessageBox::warning(this, "Thông báo", "Cập nhật thông tin không thành công. Xin hãy thử lại!");
        }
    }
    else
    {
        QMessageBox::warning(this, "Warning", "Kết nối cơ sở dữ liệu không thành công. Vui lòng thử lại!");
    }
}

QList<QString> MainWindow::LoadTenLK()
{
    QList<QString> result;
    QSqlQuery query(db);
    query.prepare("SELECT TenLK FROM LinhKien");
    if (query.exec()) {
        qDebug() << "du lieu da exec!!!!";
        while (query.next()) {
            QString tenMay = query.value("TenLK").toString();
            result.append(tenMay);
        }
    }

    // Đóng kết nối
    db.close();
    return result;
}

void MainWindow::on_lineEdit_timkiem_editingFinished()
{
    on_pushButton_clicked();
}

void MainWindow::on_pushButton_clicked()//tìm kiếm
{
    QString TenLK = ui->lineEdit_timkiem->text();
    UpdateConnection();

    if(this->DatabaseConnected)
    {
        ui->tableWidget->clear();

        QSqlQuery query(db);
        query.prepare("select * from LinhKien where TenLK == '"+TenLK +"'");
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
