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
    connect(ui->tableWidget_2, SIGNAL(cellDoubleClicked(int, int)), this, SLOT(SectionDoubleClick_2(int, int)));
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
                << "Số lượng tồn kho" << "Loại linh kiện" << "*Số lượng xuất";
    ui->tableWidget_2->setHorizontalHeaderLabels(list_labels);

    //Gợi ý tìm kiếm
    wordList = LoadTenLK();
    wordList_xk = LoadTenNguoiXuatKho();

    QCompleter *completer = new QCompleter(wordList, ui->lineEdit_timkiem);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setFilterMode(Qt::MatchContains);
    ui->lineEdit_timkiem->setCompleter(completer);

    QCompleter *completer_1 = new QCompleter(wordList_xk, ui->lineEdit_timnguoi_xk);
    completer_1->setCaseSensitivity(Qt::CaseInsensitive);
    ui->lineEdit_timnguoi_xk->setCompleter(completer_1);

    CapNhatDS_loaiLK();
    ui->comboBox->addItems(this->DsLoai_LK);

    QCompleter *completer_loaiLK = new QCompleter(DsLoai_LK, ui->lineEdit_loaiLK);
    completer_loaiLK->setCaseSensitivity(Qt::CaseInsensitive);
    completer_loaiLK->setFilterMode(Qt::MatchContains);
    ui->lineEdit_loaiLK->setCompleter(completer_loaiLK);

    ui->dateEdit_xk_ngay->setDate(QDate::currentDate());

    CapNhatBangTK();
    ui->tableWidget_TK->setColumnWidth(0, 500);
    ui->tableWidget_TK->setColumnWidth(1, 500);

    on_pushButton_22_clicked(); //load lịch sử xuất kho
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
            ui->lineEdit_MaLK->setText(query.value(1).toString());
            ui->lineEdit_DV->setText(query.value(2).toString());
            ui->lineEdit_SoLuong->setText(query.value(3).toString());
            QString loaiLK = query.value(4).toString();
            ui->lineEdit_loaiLK->setText(loaiLK);
            //            if(loaiLK != "RES" && loaiLK != "CAP" &&loaiLK != "JACK" &&loaiLK != "IC")
            //                ui->comboBox_loaiLK->setCurrentText("Khác");
            //            else
            //                ui->comboBox_loaiLK->setCurrentText(loaiLK);

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

        //        ui->tab->show();
        //        ui->tab_2->close();
        //        ui->tab_3->close();
        //        ui->tab_4->close();

        this->db.close();
    }
    else
    {
        QMessageBox::warning(this, "Warning", "Kết nối cơ sở dữ liệu không thành công. Vui lòng thử lại!");
    }
}


void MainWindow::SectionDoubleClick_2(int row, int column)  //NHẬN SIGNAL DOUBLE CLICK VÀ ĐIỀN DỮ LIỆU VÀ CÁC LINE EDIT
{
    column = 0;
    //========LẤY ID
    QString ID = ui->tableWidget_2->item(row, column)->text();
    //    qDebug()<<"ID DUOC CLICK LA: " << ID << endl;
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
            ui->lineEdit_xk_ten->setText(query.value(0).toString());
            this->SLhienCoCuaMotLK = query.value(3).toInt();
            ui->lineEdit_xk_ma->setText(query.value(1).toString());
        }
        ui->lineEdit_xksl->setDisabled(false);
        ui->lineEdit_xk_ghichu->setDisabled(false);
        ui->lineEdit_xk_ten->setDisabled(false);
        ui->lineEdit_xk_tennguoi->setDisabled(false);

        ui->dateEdit_xk_ngay->setDate(QDate::currentDate());
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
        this->db.close();
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
        this->db.close();
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
        this->db.close();
    }
}

void MainWindow::on_pushButton_14_clicked()//bắt đầu sửa thông tin linh kiện
{
    if(ui->lineEdit_MaLK->text() != "")
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
    else
    {
        QMessageBox::information(this, "Warning", "Trường mã linh kiện đang trống, xin hãy chọn linh kiện muốn sửa!");
    }
}

void MainWindow::on_pushButton_17_clicked()  //Cập nhật linh kiện
{
    if(ui->lineEdit_MaLK->text() != "")
    {
        QString LoaiLK = ui->lineEdit_loaiLK->text();
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
                    if(le != ui->lineEdit_timkiem)
                    {
                        le->clear();
                        //                    le->setDisabled(true);
                    }
                }

                ui->pushButton_10->setDisabled(false); //thêm vào giỏ
                ui->pushButton_11->setDisabled(true); //lưu
                ui->pushButton_12->setDisabled(false); //bắt đầu thêm
                ui->pushButton_13->setDisabled(false); //xóa lk này
                ui->pushButton_14->setDisabled(false);  //sửa lk này
                ui->pushButton_17->setDisabled(true);//cập nhật
                ui->pushButton_20->setDisabled(true); //hủy sửa


                CapNhatDS_loaiLK(); //cập nhật danh sách loại linh kiện
                ui->comboBox->addItems(this->DsLoai_LK);

                QCompleter *completer_loaiLK = new QCompleter(DsLoai_LK, ui->lineEdit_loaiLK);
                completer_loaiLK->setCaseSensitivity(Qt::CaseInsensitive);
                completer_loaiLK->setFilterMode(Qt::MatchContains);
                ui->lineEdit_loaiLK->setCompleter(completer_loaiLK);
                //Gợi ý tìm kiếm
                wordList = LoadTenLK();
                QCompleter *completer = new QCompleter(wordList, ui->lineEdit_timkiem);
                completer->setCaseSensitivity(Qt::CaseInsensitive);
                completer->setFilterMode(Qt::MatchContains);
                ui->lineEdit_timkiem->setCompleter(completer);
                CapNhatBangTK();
            }
            else
            {
                QMessageBox::warning(this, "Thông báo", "Cập nhật thông tin không thành công. Xin hãy thử lại!");
            }
            this->db.close();
        }
        else
        {
            QMessageBox::warning(this, "Warning", "Kết nối cơ sở dữ liệu không thành công. Vui lòng thử lại!");
        }
    }
    else
    {
        QMessageBox::information(this, "warning", "Trường mã linh kiện đang trống, hãy chọn linh kiện muốn lưu thay đổi!");
    }
}

void MainWindow::on_pushButton_20_clicked()//hủy sửa linh kiện
{
    foreach(QLineEdit* le, findChildren<QLineEdit*>())
    {
        if(le != ui->lineEdit_timkiem)
        {
            le->clear();
            le->setDisabled(true);
        }
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
                    if(le != ui->lineEdit_timkiem)
                    {
                        le->clear();
                        //                        le->setDisabled(true);
                    }
                }
                ui->pushButton_10->setDisabled(true); //thêm vào giỏ
                ui->pushButton_11->setDisabled(true); //lưu
                ui->pushButton_12->setDisabled(false); //bắt đầu thêm
                ui->pushButton_13->setDisabled(true); //xóa lk này
                ui->pushButton_14->setDisabled(true);  //sửa lk này
                ui->pushButton_17->setDisabled(true);//cập nhật
                ui->pushButton_20->setDisabled(true); //hủy sửa

                CapNhatDS_loaiLK(); //cập nhật danh sách loại linh kiện
                ui->comboBox->addItems(this->DsLoai_LK);

                QCompleter *completer_loaiLK = new QCompleter(DsLoai_LK, ui->lineEdit_loaiLK);
                completer_loaiLK->setCaseSensitivity(Qt::CaseInsensitive);
                completer_loaiLK->setFilterMode(Qt::MatchContains);
                ui->lineEdit_loaiLK->setCompleter(completer_loaiLK);
                //Gợi ý tìm kiếm
                wordList = LoadTenLK();
                QCompleter *completer = new QCompleter(wordList, ui->lineEdit_timkiem);
                completer->setCaseSensitivity(Qt::CaseInsensitive);
                completer->setFilterMode(Qt::MatchContains);
                ui->lineEdit_timkiem->setCompleter(completer);
                CapNhatBangTK();

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

    this->db.close();
}

void MainWindow::on_pushButton_12_clicked()  //bắt đầu thêm mới linh kiện
{
    foreach(QLineEdit* le, findChildren<QLineEdit*>())
    {
        if(le != ui->lineEdit_timkiem)
        {
            le->clear();
            le->setDisabled(false);
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
    //    QTableWidgetItem *GhiChu1 = new QTableWidgetItem;

    TenLK1->setText(ui->lineEdit_TenLK->text());
    MaLK1->setText(ui->lineEdit_MaLK->text());
    DVTinh1->setText(ui->lineEdit_DV->text());
    SLTonKho1->setText(ui->lineEdit_SoLuong->text());
    LoaiLK1->setText(ui->lineEdit_loaiLK->text());
    //    GhiChu1->setText(ui->lineEdit_ghichu->text());

    ui->tableWidget_2->setItem(row, 0, TenLK1);
    ui->tableWidget_2->setItem(row, 1, MaLK1);
    ui->tableWidget_2->setItem(row, 2, DVTinh1);
    ui->tableWidget_2->setItem(row, 3, SLTonKho1);
    ui->tableWidget_2->setItem(row, 4, LoaiLK1);
    //    ui->tableWidget_2->setItem(row, 5, GhiChu1);

    foreach(QLineEdit* le, findChildren<QLineEdit*>())
    {
        if(le != ui->lineEdit_timkiem)
        {
            le->clear();
            //                    le->setDisabled(true);
        }
    }

}

void MainWindow::on_pushButton_11_clicked()  //Lưu linh kiện mới
{
    QString LoaiLK = ui->lineEdit_loaiLK->text();
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
                if(le != ui->lineEdit_timkiem)
                {
                    le->clear();
                    //                    le->setDisabled(true);
                }
            }


            ui->pushButton_10->setDisabled(false); //thêm vào giỏ
            ui->pushButton_11->setDisabled(true); //lưu
            ui->pushButton_12->setDisabled(false); //bắt đầu thêm
            ui->pushButton_13->setDisabled(false); //xóa lk này
            ui->pushButton_14->setDisabled(false);  //sửa lk này
            ui->pushButton_17->setDisabled(true);//cập nhật
            ui->pushButton_20->setDisabled(true); //hủy sửa

            CapNhatDS_loaiLK(); //cập nhật danh sách loại linh kiện
            ui->comboBox->addItems(this->DsLoai_LK);

            QCompleter *completer_loaiLK = new QCompleter(DsLoai_LK, ui->lineEdit_loaiLK);
            completer_loaiLK->setCaseSensitivity(Qt::CaseInsensitive);
            completer_loaiLK->setFilterMode(Qt::MatchContains);
            ui->lineEdit_loaiLK->setCompleter(completer_loaiLK);
            //Gợi ý tìm kiếm
            wordList = LoadTenLK();
            QCompleter *completer = new QCompleter(wordList, ui->lineEdit_timkiem);
            completer->setCaseSensitivity(Qt::CaseInsensitive);
            completer->setFilterMode(Qt::MatchContains);
            ui->lineEdit_timkiem->setCompleter(completer);

            CapNhatBangTK();
        }
        else
        {
            QMessageBox::warning(this, "Thông báo", "Cập nhật thông tin không thành công. Xin hãy thử lại!");
        }
        this->db.close();
    }
    else
    {
        QMessageBox::warning(this, "Warning", "Kết nối cơ sở dữ liệu không thành công. Vui lòng thử lại!");
    }
}

QList<QString> MainWindow::LoadTenLK()
{
    UpdateConnection();
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

QList<QString> MainWindow::LoadTenNguoiXuatKho()
{
    UpdateConnection();
    QList<QString> result;
    QSqlQuery query(db);
    query.prepare("SELECT TenNguoiXK FROM LSXuatKho");
    if (query.exec()) {
        qDebug() << "du lieu da exec!!!!";
        while (query.next()) {
            QString ten = query.value("TenNguoiXK").toString();
            result.append(ten);
        }
    }
    else
    {
        qDebug() << "Load khong thanh cong";
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
            QTableWidgetItem *MaLK = new QTableWidgetItem;
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
        this->db.close();
    }
}

void MainWindow::exportToExcel(QTableWidget *tableWidget, const QString &fileName) {
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(nullptr, "Error", "Could not create file!");
        return;
    }

    QTextStream out(&file);

    const int rows = tableWidget->rowCount();
    const int columns = tableWidget->columnCount();

    // Write column headers
    for (int column = 0; column < columns; ++column) {
        if (column > 0)
            out << "\t";
        out << tableWidget->horizontalHeaderItem(column)->data(Qt::DisplayRole).toString().toUtf8();
    }
    out << "\n";

    // Write data
    for (int row = 0; row < rows; ++row) {
        for (int column = 0; column < columns; ++column) {
            if (column > 0)
                out << "\t";
            QTableWidgetItem *item = tableWidget->item(row, column);
            if (item) {
                out << item->data(Qt::DisplayRole).toString();
            }
        }
        out << "\n";
    }

    file.close();
}

void MainWindow::CapNhatSoLuongLK(QString MaLK, int SoLuongConLai)
{
    this->UpdateConnection();
    if(this->DatabaseConnected)
    {
        QSqlQuery qry(this->db);
        qry.prepare("UPDATE LinhKien SET SoLuongConLai='" + QString::number(SoLuongConLai) + "' WHERE MaLK= '" + MaLK + "';");

        //        qry.bindValue(":MaLK", MaLK);
        //        qry.bindValue(":SoLuongConLai", SoLuongConLai);
        if(qry.exec())
        {
        }
        else
        {
            QMessageBox::warning(this, "Thông báo", "Cập nhật thông tin không thành công. Xin hãy thử lại!");
        }
        this->db.close();
    }
    else
    {
        QMessageBox::warning(this, "Warning", "Kết nối cơ sở dữ liệu không thành công. Vui lòng thử lại!");
    }
}

void MainWindow::CapNhatLSXuatKho(QString TenNguoiXK, QString TenLK, QString MaLK, QString SoLuongXK, QString GhiChu, QString NgayXK)
{
    this->UpdateConnection();
    if(this->DatabaseConnected)
    {
        QSqlQuery qry(this->db);
        qry.prepare("INSERT INTO LSXuatKho ( TenNguoiXK, TenLK, MaLK, SoLuongXK, GhiChu, "
                    "NgayXK) "
                    "VALUES (:TenNguoiXK, :TenLK, :MaLK, :SoLuongXK, :GhiChu,"
                    ":NgayXK)");

        qry.bindValue(":TenNguoiXK", TenNguoiXK);
        qry.bindValue(":TenLK", TenLK);
        qry.bindValue(":MaLK", MaLK);
        qry.bindValue(":SoLuongXK", SoLuongXK);
        qry.bindValue(":GhiChu", GhiChu);
        qry.bindValue(":NgayXK", NgayXK);

        if(qry.exec())
        {
        }
        else
        {
            QMessageBox::warning(this, "Thông báo", "Cập nhật thông tin không thành công. Xin hãy thử lại!");
        }
        this->db.close();
    }
    else
    {
        QMessageBox::warning(this, "Warning", "Kết nối cơ sở dữ liệu không thành công. Vui lòng thử lại!");
    }
}

void MainWindow::CapNhatDS_loaiLK()
{
    UpdateConnection();

    if(this->DatabaseConnected)
    {
        ui->tableWidget->clear();
        QSqlQuery query(db);
        query.prepare("select distinct LoaiLK from LinhKien");
        query.exec();

        int rowcount = 0;
        this->DsLoai_LK.clear();
        while(query.next())
        {
            DsLoai_LK.append(query.value("LoaiLK").toString());
        }
        this->db.close();
    }
}

void MainWindow::CapNhatBangTK()
{
    UpdateConnection();
    if(this->DatabaseConnected)
    {
        ui->tableWidget_TK->clear();

        QSqlQuery query(db);
        query.prepare("SELECT LoaiLK, SUM(SoLuongConLai) AS TongSoLuongConLai FROM LinhKien GROUP BY LoaiLK");
        query.exec();

        ui->tableWidget_TK->setColumnCount(2);
        QStringList list_labels;
        list_labels << "TÊN LOẠI LINH KIỆN" << " TỔNG SỐ LƯỢNG CÒN LẠI" ;
        ui->tableWidget_TK->setHorizontalHeaderLabels(list_labels);

        int rowcount = 0;
        while(query.next())
        {
            ui->tableWidget_TK->insertRow(rowcount);
            QTableWidgetItem *LoaiLK = new QTableWidgetItem;
            QTableWidgetItem *SoLuong = new QTableWidgetItem;

            LoaiLK->setText(query.value(0).toString());
            SoLuong->setText(query.value(1).toString());

            ui->tableWidget_TK->setItem(rowcount, 0, LoaiLK);
            ui->tableWidget_TK->setItem(rowcount, 1, SoLuong);

            rowcount++;
        }
        this->db.close();
    }
}

void MainWindow::on_pushButton_21_clicked() // xuất file excel giỏ
{
    QString fileName = QFileDialog::getSaveFileName(nullptr, "Export to Excel", "", "Excel Files (*.xls *.xlsx)");
    if (!fileName.isEmpty()) {
        exportToExcel(ui->tableWidget_2, fileName);
        QMessageBox::information(nullptr, "Export to Excel", "Exported successfully!");
    }
}

void MainWindow::on_lineEdit_xksl_editingFinished()
{
    qDebug() << "on_lineEdit_xksl_editingFinished" << endl;
    int soluongxuat = ui->lineEdit_xksl->text().toInt();
    if(soluongxuat > this->SLhienCoCuaMotLK)
    {
        QMessageBox::warning(this, "Thông báo", "Số lượng xuất kho vượt quá số lượng hiện có, nhập lại!");
        ui->lineEdit_xksl->clear();
    }
    else
    {
        for (int row = 0; row < ui->tableWidget_2->rowCount(); ++row)
        {
            // Kiểm tra giá trị cột ID của hàng hiện tại
            QTableWidgetItem* item = ui->tableWidget_2->item(row, 1);
            if (item && item->text() == ui->lineEdit_xk_ma->text())
            {
                // Tạo một item mới để thêm vào cột thứ m
                QTableWidgetItem* newItem = new QTableWidgetItem(ui->lineEdit_xksl->text());
                // Set text cho item mới
                ui->tableWidget_2->setItem(row, 5, newItem);
            }
        }
    }
    //    ui->lineEdit_xksl->clear();
}

void MainWindow::on_pushButton_15_clicked()//Xuất kho
{
    if(ui->lineEdit_xk_tennguoi->text() == "" || ui->lineEdit_xksl->text() == "" || ui->lineEdit_xksl->text().toInt() < 0)
    {
        QMessageBox::warning(this, "thông báo", "TÊN NGƯỜI XUẤT KHO và SỐ LƯỢNG XUẤT KHO không được trống, xin hãy nhập tên người xuất kho!");
    }
    else
    {
        //Kiểm tra số lượng xuất kho phù hợp
        for (int row = 0; row < ui->tableWidget_2->rowCount(); row++)
        {
            QTableWidgetItem* item = ui->tableWidget_2->item(row, 1);
            QString MaLK = item->text();
            int SLHienTai = ui->tableWidget_2->item(row, 3)->text().toInt();
            int SLXuatKho = ui->tableWidget_2->item(row, 5)->text().toInt();
            if(SLHienTai < SLXuatKho)
            {
                QMessageBox::warning(this, "Thông báo", "Số lượng hiện tại của " + item->text() + " nhỏ hơn số lượng xuất kho!");
                return;
            }

        }

        //bắt đầu trừ đi số linh kiện còn lại
        bool temp = false;
        for (int row = 0; row < ui->tableWidget_2->rowCount(); row++)
        {
            QTableWidgetItem* item = ui->tableWidget_2->item(row, 1);
            QString MaLK = item->text();
            int SLHienTai = ui->tableWidget_2->item(row, 3)->text().toInt();
            int SLXuatKho = ui->tableWidget_2->item(row, 5)->text().toInt();

            int SLConLai = SLHienTai - SLXuatKho;
            CapNhatSoLuongLK(MaLK, SLConLai);
            CapNhatLSXuatKho(ui->lineEdit_xk_tennguoi->text(), ui->tableWidget_2->item(row, 0)->text(), ui->tableWidget_2->item(row, 1)->text(), ui->tableWidget_2->item(row, 5)->text(), ui->lineEdit_xk_ghichu->text(), QDate::currentDate().toString());

            temp = true;
        }
        if(temp)
        {
            CapNhatBangTK();
            QMessageBox::warning(this, "Thông báo", "Xuất kho thành công!");
            on_pushButton_21_clicked();
        }
    }
}

void MainWindow::on_pushButton_22_clicked() //làm mới lịch sử
{
    this->wordList_xk = LoadTenNguoiXuatKho();
    QCompleter *completer_1 = new QCompleter(wordList_xk, ui->lineEdit_timnguoi_xk);
    completer_1->setCaseSensitivity(Qt::CaseInsensitive);
    ui->lineEdit_timnguoi_xk->setCompleter(completer_1);

    ui->lineEdit_timnguoi_xk->setDisabled(false);
    ui->dateEdit->setDisabled(false);
    UpdateConnection();
    if(this->DatabaseConnected)
    {
        ui->tableWidget_3->clear();

        QSqlQuery query(db);
        query.prepare("select * from LSXuatKho");
        query.exec();

        ui->tableWidget_3->setColumnCount(7);
        QStringList list_labels;
        list_labels << "Tên người xuất kho" << "Mã xuất kho" << "Tên linh kiện"
                    << "Mã linh kiện" << "Số lượng xuất kho" << "Ghi chú" << "Ngày xuất kho";
        ui->tableWidget_3->setHorizontalHeaderLabels(list_labels);

        int rowcount = 0;
        while(query.next())
        {
            ui->tableWidget_3->insertRow(rowcount);
            QTableWidgetItem *TenNguoiXK = new QTableWidgetItem;
            QTableWidgetItem * MaXK = new QTableWidgetItem;
            QTableWidgetItem *TenLK = new QTableWidgetItem;
            QTableWidgetItem *MaLK = new QTableWidgetItem;
            QTableWidgetItem *SoLuongXK = new QTableWidgetItem;
            QTableWidgetItem *GhiChu = new QTableWidgetItem;
            QTableWidgetItem *NgayXK = new QTableWidgetItem;



            TenNguoiXK->setText(query.value(0).toString());
            MaXK->setText(query.value(1).toString());
            TenLK->setText(query.value(2).toString());
            MaLK->setText(query.value(3).toString());
            SoLuongXK->setText(query.value(4).toString());
            GhiChu->setText(query.value(5).toString());
            NgayXK->setText(query.value(6).toString());

            ui->tableWidget_3->setItem(rowcount, 0, TenNguoiXK);
            ui->tableWidget_3->setItem(rowcount, 1, MaXK);
            ui->tableWidget_3->setItem(rowcount, 2, TenLK);
            ui->tableWidget_3->setItem(rowcount, 3, MaLK);
            ui->tableWidget_3->setItem(rowcount, 4, SoLuongXK);
            ui->tableWidget_3->setItem(rowcount, 5, GhiChu);
            ui->tableWidget_3->setItem(rowcount, 6, NgayXK);

            rowcount++;
        }
        this->db.close();
    }
}

void MainWindow::on_lineEdit_timnguoi_xk_editingFinished()  // tìm lịch sử theo tên
{
    UpdateConnection();

    if(this->DatabaseConnected)
    {
        ui->tableWidget_3->clear();

        QSqlQuery query(db);
        query.prepare("select * from LSXuatKho where TenNguoiXK == '"+ui->lineEdit_timnguoi_xk->text() +"'");
        query.exec();

        ui->tableWidget_3->setColumnCount(7);
        QStringList list_labels;
        list_labels << "Tên người xuất kho" << "Mã xuất kho" << "Tên linh kiện"
                    << "Mã linh kiện" << "Số lượng xuất kho" << "Ghi chú" << "Ngày xuất kho";
        ui->tableWidget_3->setHorizontalHeaderLabels(list_labels);;

        int rowcount = 0;
        while(query.next())
        {
            ui->tableWidget_3->insertRow(rowcount);
            QTableWidgetItem *TenNguoiXK = new QTableWidgetItem;
            QTableWidgetItem * MaXK = new QTableWidgetItem;
            QTableWidgetItem *TenLK = new QTableWidgetItem;
            QTableWidgetItem *MaLK = new QTableWidgetItem;
            QTableWidgetItem *SoLuongXK = new QTableWidgetItem;
            QTableWidgetItem *GhiChu = new QTableWidgetItem;
            QTableWidgetItem *NgayXK = new QTableWidgetItem;



            TenNguoiXK->setText(query.value(0).toString());
            MaXK->setText(query.value(1).toString());
            TenLK->setText(query.value(2).toString());
            MaLK->setText(query.value(3).toString());
            SoLuongXK->setText(query.value(4).toString());
            GhiChu->setText(query.value(5).toString());
            NgayXK->setText(query.value(6).toString());

            ui->tableWidget_3->setItem(rowcount, 0, TenNguoiXK);
            ui->tableWidget_3->setItem(rowcount, 1, MaXK);
            ui->tableWidget_3->setItem(rowcount, 2, TenLK);
            ui->tableWidget_3->setItem(rowcount, 3, MaLK);
            ui->tableWidget_3->setItem(rowcount, 4, SoLuongXK);
            ui->tableWidget_3->setItem(rowcount, 5, GhiChu);
            ui->tableWidget_3->setItem(rowcount, 6, NgayXK);

            rowcount++;
        }
        this->db.close();
    }
}

void MainWindow::on_pushButton_23_clicked()
{
    SelectAll();
}

void MainWindow::on_dateEdit_editingFinished() // tìm kiếm theo ngày
{
    UpdateConnection();
    QString Search_date = ui->dateEdit->date().toString("ddd MMM d yyyy");
    //qDebug() << "Ngay theo dang chuan"<< Search_date;
    if(this->DatabaseConnected)
    {
        ui->tableWidget_3->clear();

        QSqlQuery query(db);
        query.prepare("select * from LSXuatKho where NgayXK == '"+ Search_date +"'");
        query.exec();

        ui->tableWidget_3->setColumnCount(7);
        QStringList list_labels;
        list_labels << "Tên người xuất kho" << "Mã xuất kho" << "Tên linh kiện"
                    << "Mã linh kiện" << "Số lượng xuất kho" << "Ghi chú" << "Ngày xuất kho";
        ui->tableWidget_3->setHorizontalHeaderLabels(list_labels);;

        int rowcount = 0;
        while(query.next())
        {
            ui->tableWidget_3->insertRow(rowcount);
            QTableWidgetItem *TenNguoiXK = new QTableWidgetItem;
            QTableWidgetItem * MaXK = new QTableWidgetItem;
            QTableWidgetItem *TenLK = new QTableWidgetItem;
            QTableWidgetItem *MaLK = new QTableWidgetItem;
            QTableWidgetItem *SoLuongXK = new QTableWidgetItem;
            QTableWidgetItem *GhiChu = new QTableWidgetItem;
            QTableWidgetItem *NgayXK = new QTableWidgetItem;



            TenNguoiXK->setText(query.value(0).toString());
            MaXK->setText(query.value(1).toString());
            TenLK->setText(query.value(2).toString());
            MaLK->setText(query.value(3).toString());
            SoLuongXK->setText(query.value(4).toString());
            GhiChu->setText(query.value(5).toString());
            NgayXK->setText(query.value(6).toString());

            ui->tableWidget_3->setItem(rowcount, 0, TenNguoiXK);
            ui->tableWidget_3->setItem(rowcount, 1, MaXK);
            ui->tableWidget_3->setItem(rowcount, 2, TenLK);
            ui->tableWidget_3->setItem(rowcount, 3, MaLK);
            ui->tableWidget_3->setItem(rowcount, 4, SoLuongXK);
            ui->tableWidget_3->setItem(rowcount, 5, GhiChu);
            ui->tableWidget_3->setItem(rowcount, 6, NgayXK);

            rowcount++;
        }
        this->db.close();
    }
}

void MainWindow::on_pushButton_19_clicked()
{
    ui->lineEdit_timnguoi_xk->clear();
}

void MainWindow::on_pushButton_18_clicked()  /// xuất lịch sử
{
    QString fileName = QFileDialog::getSaveFileName(nullptr, "Export to Excel", "", "Excel Files (*.xls *.xlsx)");
    if (!fileName.isEmpty()) {
        exportToExcel(ui->tableWidget_3, fileName);
        QMessageBox::information(nullptr, "Export to Excel", "Exported successfully!");
    }
}

void MainWindow::on_comboBox_editTextChanged(const QString &arg1)
{
    //    ui->tableWidget->clear();
    //    qDebug() << "&arg1 --------------------"<< endl;
    //    Seclect("CẢM");
}

void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    ui->tableWidget->clear();
    ui->tableWidget->scrollToTop();
    Seclect(arg1);
}
