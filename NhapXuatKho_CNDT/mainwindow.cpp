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
    connect(ui->tableWidget_nhapthem, SIGNAL(cellDoubleClicked(int, int)), this, SLOT(SectionDoubleClick_3(int, int)));
    ui->tableWidget->setColumnWidth(0, 450);
    ui->tableWidget->setColumnWidth(1, 200);
    ui->tableWidget->setColumnWidth(2, 150);
    ui->tableWidget->setColumnWidth(3, 150);
    ui->tableWidget->setColumnWidth(4, 150);
    ui->tableWidget->setColumnWidth(5, 300);

    ui->tableWidget_2->setColumnWidth(0, 300);
    ui->tableWidget_2->setColumnWidth(1, 150);
    ui->tableWidget_2->setColumnWidth(2, 100);
    ui->tableWidget_2->setColumnWidth(3, 150);
    ui->tableWidget_2->setColumnWidth(4, 100);
    ui->tableWidget_2->setColumnWidth(5, 150);

    ui->tableWidget_lsnhapkho->setColumnWidth(0, 300);
    ui->tableWidget_lsnhapkho->setColumnWidth(1, 100);
    ui->tableWidget_lsnhapkho->setColumnWidth(2, 200);
    ui->tableWidget_lsnhapkho->setColumnWidth(3, 100);
    ui->tableWidget_lsnhapkho->setColumnWidth(4, 150);
    ui->tableWidget_lsnhapkho->setColumnWidth(5, 130);

    //bảng giỏ linh kiện
    ui->tableWidget_2->setColumnCount(6);
    QStringList list_labels;
    list_labels << "Tên linh kiện" << "Mã linh kiện" << "Đơn vị tính"
                << "Số lượng tồn kho" << "Loại linh kiện" << "*Số lượng xuất";
    ui->tableWidget_2->setHorizontalHeaderLabels(list_labels);

    //bảng nhập thêm linh kiện sẵn có
    ui->tableWidget_nhapthem->setColumnCount(6);
    QStringList list_labels_2;
    list_labels_2 << "Tên linh kiện" << "Mã linh kiện" << "Đơn vị tính"
                  << "Số lượng tồn kho" << "Loại linh kiện" << "*SỐ LƯỢNG THÊM";
    ui->tableWidget_nhapthem->setHorizontalHeaderLabels(list_labels_2);

    //Gợi ý tìm kiếm
    wordList_timkiem = LoadTenLK_timkiem(ui->comboBox->currentText());
    QCompleter *completer = new QCompleter(wordList_timkiem, ui->lineEdit_timkiem);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setFilterMode(Qt::MatchContains);
    ui->lineEdit_timkiem->setCompleter(completer);

    //gợi ý cho tìm lịch sử lk
    wordList = LoadTenLK();
    wordList_xk = LoadTenNguoiXuatKho();
    wordList_nk = LoadTenNguoiNhapKho();

    QCompleter *completer_2 = new QCompleter(wordList, ui->lineEdit_timlk_xuatkho);
    completer_2->setCaseSensitivity(Qt::CaseInsensitive);
    completer_2->setFilterMode(Qt::MatchContains);
    ui->lineEdit_timlk_xuatkho->setCompleter(completer_2);

    QCompleter *completer_4 = new QCompleter(wordList, ui->lineEdit_timlk_nhapkho);
    completer_4->setCaseSensitivity(Qt::CaseInsensitive);
    completer_4->setFilterMode(Qt::MatchContains);
    ui->lineEdit_timlk_nhapkho->setCompleter(completer_4);

    QCompleter *completer_1 = new QCompleter(wordList_xk, ui->lineEdit_timnguoi_xk);
    completer_1->setCaseSensitivity(Qt::CaseInsensitive);
    ui->lineEdit_timnguoi_xk->setCompleter(completer_1);

    QCompleter *completer_3 = new QCompleter(wordList_nk, ui->lineEdit_timnguoi_nhapkho);
    completer_3->setCaseSensitivity(Qt::CaseInsensitive);
    ui->lineEdit_timnguoi_nhapkho->setCompleter(completer_3);

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

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_TK->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_3->setEditTriggers(QAbstractItemView::NoEditTriggers);

    on_pushButton_22_clicked(); //load lịch sử xuất kho
    ui->dateEdit_xk_ngay->setDisabled(true);
    ui->pushButton_ThemTrucTiep->setHidden(true);
    ui->pushButton_nhapthemvaokho->setHidden(true);

    ui->pushButton_10->setHidden(true);
    ui->pushButton->setHidden(true);


    ui->pushButton_11->setDisabled(true); //lưu
    ui->pushButton_12->setDisabled(false); //bắt đầu thêm
    ui->pushButton_13->setDisabled(true); //xóa lk này
    ui->pushButton_14->setDisabled(true);  //sửa lk này
    ui->pushButton_17->setDisabled(true);//cập nhật
    ui->pushButton_20->setDisabled(true); //hủy sửa
    ui->pushButton_huythem->setDisabled(true); //hủy sửa

    ui->groupBox_3->setHidden(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SectionDoubleClick(int row, int column)  //NHẬN SIGNAL DOUBLE CLICK VÀ ĐIỀN DỮ LIỆU VÀ CÁC LINE EDIT
{
    column = 1;
    //========LẤY ID
    QString ID = ui->tableWidget->item(row, column)->text();
    //    qDebug()<<"ID DUOC CLICK LA: " << ID << endl;
    this->ID_DoubleCLick = ID;

    UpdateConnection();
    if(this->DatabaseConnected)
    {
        //Do some thing

        QSqlQuery query(db);
        QString QueryString = "SELECT * FROM LinhKien WHERE MaLK LIKE '" + ID + "'";
        query.prepare(QueryString);
        query.exec();
        if(ui->tabWidget->currentIndex() == 0)  //THONG TIN LINH KIEN
        {
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

                ui->lineEdit_timkiem->setText(query.value(0).toString());
            }
            //setDisabled all line edit
            foreach(QLineEdit* le, findChildren<QLineEdit*>())
            {
                if(le != ui->lineEdit_timkiem && le != ui->lineEdit_timnguoi_xk && le != ui->lineEdit_timlk_xuatkho && le != ui->lineEdit_timlk_nhapkho)
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

            this->db.close();
        }
        else if(ui->tabWidget->currentIndex() == 1) //NHAP THEM VAO KHO
        {
            ui->tableWidget_nhapthem->setColumnWidth(0, 500);
            ui->tableWidget_nhapthem->setColumnWidth(1, 200);
            ui->tableWidget_nhapthem->setColumnWidth(2, 150);
            ui->tableWidget_nhapthem->setColumnWidth(3, 150);
            ui->tableWidget_nhapthem->setColumnWidth(4, 150);
            ui->tableWidget_nhapthem->setColumnWidth(5, 150);

            int row = ui->tableWidget_nhapthem->rowCount();
            ui->tableWidget_nhapthem->insertRow(row);

            QTableWidgetItem *TenLK1 = new QTableWidgetItem;
            QTableWidgetItem * MaLK1 = new QTableWidgetItem;
            QTableWidgetItem *DVTinh1 = new QTableWidgetItem;
            QTableWidgetItem *SLTonKho1 = new QTableWidgetItem;
            QTableWidgetItem *LoaiLK1 = new QTableWidgetItem;

            while(query.next())
            {
                TenLK1->setText(query.value(0).toString());
                MaLK1->setText(query.value(1).toString());
                DVTinh1->setText(query.value(2).toString());
                SLTonKho1->setText(query.value(3).toString());
                LoaiLK1->setText(query.value(4).toString());

                ui->tableWidget_nhapthem->setItem(row, 0, TenLK1);
                ui->tableWidget_nhapthem->setItem(row, 1, MaLK1);
                ui->tableWidget_nhapthem->setItem(row, 2, DVTinh1);
                ui->tableWidget_nhapthem->setItem(row, 3, SLTonKho1);
                ui->tableWidget_nhapthem->setItem(row, 4, LoaiLK1);
            }
        }
        else if(ui->tabWidget->currentIndex() == 2) //THEM VAO GIO XUAT KHO
        {

            ui->tableWidget_2->setColumnWidth(0, 300);
            ui->tableWidget_2->setColumnWidth(1, 150);
            ui->tableWidget_2->setColumnWidth(2, 100);
            ui->tableWidget_2->setColumnWidth(3, 150);
            ui->tableWidget_2->setColumnWidth(4, 100);
            ui->tableWidget_2->setColumnWidth(5, 150);

            int row = ui->tableWidget_2->rowCount();
            ui->tableWidget_2->insertRow(row);

            QTableWidgetItem *TenLK1 = new QTableWidgetItem;
            QTableWidgetItem * MaLK1 = new QTableWidgetItem;
            QTableWidgetItem *DVTinh1 = new QTableWidgetItem;
            QTableWidgetItem *SLTonKho1 = new QTableWidgetItem;
            QTableWidgetItem *LoaiLK1 = new QTableWidgetItem;
            //    QTableWidgetItem *GhiChu1 = new QTableWidgetItem;

            while(query.next())
            {
                TenLK1->setText(query.value(0).toString());
                MaLK1->setText(query.value(1).toString());
                DVTinh1->setText(query.value(2).toString());
                SLTonKho1->setText(query.value(3).toString());
                LoaiLK1->setText(query.value(4).toString());

                ui->tableWidget_2->setItem(row, 0, TenLK1);
                ui->tableWidget_2->setItem(row, 1, MaLK1);
                ui->tableWidget_2->setItem(row, 2, DVTinh1);
                ui->tableWidget_2->setItem(row, 3, SLTonKho1);
                ui->tableWidget_2->setItem(row, 4, LoaiLK1);
            }
        }
    }
    else
    {
        QMessageBox::warning(this, "Warning", "Kết nối cơ sở dữ liệu không thành công. Vui lòng thử lại!");
    }
}

void MainWindow::SectionDoubleClick_2(int row, int column)  //NHẬN SIGNAL DOUBLE CLICK VÀ ĐIỀN DỮ LIỆU VÀ CÁC LINE EDIT
{
    column = 0;
    this->row_table_2_clicked = row;
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

        ui->dateEdit_xk_ngay->setDate(QDate::currentDate());
        this->db.close();
    }
    else
    {
        QMessageBox::warning(this, "Warning", "Kết nối cơ sở dữ liệu không thành công. Vui lòng thử lại!");
    }
}

void MainWindow::SectionDoubleClick_3(int row, int column)  //NHẬN SIGNAL DOUBLE CLICK VÀ ĐIỀN DỮ LIỆU VÀ CÁC LINE EDIT
{
    this->row_table_nhapthem_clicked = row;
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
    if(LoaiLK != "--TẤT CẢ--")
    {
        if(this->DatabaseConnected)
        {
            ui->tableWidget->clear();
            ui->tableWidget->setRowCount(1);

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
    else
    {
        if(this->DatabaseConnected)
        {
            ui->tableWidget->clear();
            ui->tableWidget->setRowCount(1);

            QSqlQuery query(db);
            query.prepare("select * from LinhKien");
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
}

void MainWindow::SelectAll()
{
    UpdateConnection();

    if(this->DatabaseConnected)
    {
        ui->tableWidget->clear();
        ui->tableWidget->setRowCount(1);
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
    ui->tableWidget->setRowCount(1);
    Seclect("RES");
}

void MainWindow::on_pushButton_3_clicked()//tụ
{
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(1);
    Seclect("CAP");
}

void MainWindow::on_pushButton_4_clicked()//ic
{
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(1);
    Seclect("IC");
}

void MainWindow::on_pushButton_5_clicked()//jack
{
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(1);
    Seclect("JACK");
}

void MainWindow::on_pushButton_6_clicked()//khác
{
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(1);
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
                    if(le != ui->lineEdit_timkiem&& le != ui->lineEdit_timnguoi_xk && le != ui->lineEdit_timlk_xuatkho&& le != ui->lineEdit_timlk_nhapkho)
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
                wordList_timkiem = LoadTenLK_timkiem(ui->comboBox->currentText());
                QCompleter *completer = new QCompleter(wordList_timkiem, ui->lineEdit_timkiem);
                completer->setCaseSensitivity(Qt::CaseInsensitive);
                completer->setFilterMode(Qt::MatchContains);
                ui->lineEdit_timkiem->setCompleter(completer);

                //gợi ý tìm kiếm tên lk trong lịch sử xk
                QCompleter *completer_2 = new QCompleter(wordList, ui->lineEdit_timlk_xuatkho);
                completer_2->setCaseSensitivity(Qt::CaseInsensitive);
                completer_2->setFilterMode(Qt::MatchContains);
                ui->lineEdit_timlk_xuatkho->setCompleter(completer_2);

                //gợi ý tìm kiếm tên lk trong lịch sử xk
                QCompleter *completer_4 = new QCompleter(wordList, ui->lineEdit_timlk_nhapkho);
                completer_4->setCaseSensitivity(Qt::CaseInsensitive);
                completer_4->setFilterMode(Qt::MatchContains);
                ui->lineEdit_timlk_nhapkho->setCompleter(completer_4);

                CapNhatBangTK();
                CapNhatBangLK();

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
        if(le != ui->lineEdit_timkiem&& le != ui->lineEdit_timnguoi_xk && le != ui->lineEdit_timlk_xuatkho && le != ui->lineEdit_timlk_nhapkho)
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
                    if(le != ui->lineEdit_timkiem && le != ui->lineEdit_timnguoi_xk && le != ui->lineEdit_timlk_xuatkho && le != ui->lineEdit_timlk_nhapkho)
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
                wordList_timkiem = LoadTenLK_timkiem(ui->comboBox->currentText());
                QCompleter *completer = new QCompleter(wordList_timkiem, ui->lineEdit_timkiem);
                completer->setCaseSensitivity(Qt::CaseInsensitive);
                completer->setFilterMode(Qt::MatchContains);
                ui->lineEdit_timkiem->setCompleter(completer);

                //gợi ý tìm kiếm tên lk trong lịch sử xk
                QCompleter *completer_2 = new QCompleter(wordList, ui->lineEdit_timlk_xuatkho);
                completer_2->setCaseSensitivity(Qt::CaseInsensitive);
                completer_2->setFilterMode(Qt::MatchContains);
                ui->lineEdit_timlk_xuatkho->setCompleter(completer_2);

                //gợi ý tìm kiếm tên lk trong lịch sử nhập kho
                QCompleter *completer_4 = new QCompleter(wordList, ui->lineEdit_timlk_nhapkho);
                completer_4->setCaseSensitivity(Qt::CaseInsensitive);
                completer_4->setFilterMode(Qt::MatchContains);
                ui->lineEdit_timlk_nhapkho->setCompleter(completer_4);

                CapNhatBangTK();
                CapNhatBangLK();

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
    ui->pushButton_11->setDisabled(false); //lưu
    ui->pushButton_12->setDisabled(true); //bắt đầu thêm
    ui->pushButton_huythem->setDisabled(false); //hủy thêm
    ui->pushButton_13->setDisabled(true); //xóa lk này
    ui->pushButton_14->setDisabled(true);  //sửa lk này
    ui->pushButton_17->setDisabled(true);//cập nhật
    ui->pushButton_20->setDisabled(true); //hủy sửa

    ui->lineEdit_loaiLK->setFocus();
}

void MainWindow::on_pushButton_10_clicked()///thêm vào giỏ
{
    if( (ui->lineEdit_MaLK->text() == "") || (ui->lineEdit_TenLK->text() == "") || (ui->lineEdit_DV->text() == "") || (ui->lineEdit_SoLuong->text() == "") || (ui->lineEdit_loaiLK->text() == "") )
    {
        QMessageBox::warning(this, "Thông báo", "Chưa có thông tin Linh kiện được chọn (thông tin phải đầy đủ)!");
    }
    else
    {
        ui->tableWidget_2->setColumnWidth(0, 300);
        ui->tableWidget_2->setColumnWidth(1, 150);
        ui->tableWidget_2->setColumnWidth(2, 100);
        ui->tableWidget_2->setColumnWidth(3, 150);
        ui->tableWidget_2->setColumnWidth(4, 100);
        ui->tableWidget_2->setColumnWidth(5, 150);

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
            if(le != ui->lineEdit_xk_tennguoi&& le != ui->lineEdit_timnguoi_xk && le != ui->lineEdit_timlk_xuatkho && le != ui->lineEdit_timlk_nhapkho)
            {
                le->clear();
                //                    le->setDisabled(true);
            }
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
                if(le != ui->lineEdit_timkiem&& le != ui->lineEdit_timnguoi_xk && le != ui->lineEdit_timlk_xuatkho && le != ui->lineEdit_timlk_nhapkho)
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
            wordList_timkiem = LoadTenLK_timkiem(ui->comboBox->currentText());
            QCompleter *completer = new QCompleter(wordList_timkiem, ui->lineEdit_timkiem);
            completer->setCaseSensitivity(Qt::CaseInsensitive);
            completer->setFilterMode(Qt::MatchContains);
            ui->lineEdit_timkiem->setCompleter(completer);

            //gợi ý tìm kiếm tên lk trong lịch sử xk
            QCompleter *completer_2 = new QCompleter(wordList, ui->lineEdit_timlk_xuatkho);
            completer_2->setCaseSensitivity(Qt::CaseInsensitive);
            completer_2->setFilterMode(Qt::MatchContains);
            ui->lineEdit_timlk_xuatkho->setCompleter(completer_2);

            //gợi ý tìm kiếm tên lk trong lịch sử nhập
            QCompleter *completer_4 = new QCompleter(wordList, ui->lineEdit_timlk_nhapkho);
            completer_4->setCaseSensitivity(Qt::CaseInsensitive);
            completer_4->setFilterMode(Qt::MatchContains);
            ui->lineEdit_timlk_nhapkho->setCompleter(completer_4);

            CapNhatBangTK();
            CapNhatBangLK();

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
        while (query.next()) {
            QString tenMay = query.value("TenLK").toString();
            result.append(tenMay);
        }
    }

    // Đóng kết nối
    db.close();
    return result;
}

QList<QString> MainWindow::LoadTenLK_timkiem(QString loaiLK)
{
    if(loaiLK == "--TẤT CẢ--")
    {
        return LoadTenLK();
    }
    else
    {
        UpdateConnection();
        QList<QString> result;
        QSqlQuery query(db);
        query.prepare("SELECT TenLK FROM LinhKien where LoaiLK == '"+loaiLK+"';");
        if (query.exec()) {
            while (query.next()) {
                QString tenMay = query.value("TenLK").toString();
                result.append(tenMay);
            }
        }

        // Đóng kết nối
        db.close();
        return result;
    }
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

QList<QString> MainWindow::LoadTenNguoiNhapKho()
{
    UpdateConnection();
    QList<QString> result;
    QSqlQuery query(db);
    query.prepare("SELECT TenNguoiNK FROM LSNhapKho");
    if (query.exec()) {
        while (query.next()) {
            QString ten = query.value("TenNguoiNK").toString();
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
    QString LoaiLK = ui->comboBox->currentText();
    UpdateConnection();
    if(LoaiLK == "--TẤT CẢ--")
    {
        if(this->DatabaseConnected)
        {
            ui->tableWidget->clear();
            ui->tableWidget->setRowCount(1);

            QSqlQuery query(db);
            query.prepare("select * from LinhKien where TenLK LIKE '%"+TenLK +"%'");
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

                //Cập nhật linh kiện vừa tìm thấy
                LK_timthay.Ten_LK =query.value(0).toString();
                LK_timthay.Ma_LK = query.value(1).toString();
                LK_timthay.Donvi_LK = query.value(2).toString();
                LK_timthay.Soluong_LK = query.value(3).toString();
                LK_timthay.Loai_LK = query.value(4).toString();
                LK_timthay.Ghichu_LK = query.value(5).toString();
            }
            this->db.close();
            //            ui->pushButton_ThemTrucTiep->setHidden(false);
            //            ui->pushButton_nhapthemvaokho->setHidden(false);
        }
    }
    else
    {
        if(this->DatabaseConnected)
        {
            ui->tableWidget->clear();
            ui->tableWidget->setRowCount(1);

            QSqlQuery query(db);
            query.prepare("select * from LinhKien where TenLK LIKE '%"+TenLK +"%' and LoaiLK == '"+LoaiLK+"'");
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

                //Cập nhật linh kiện vừa tìm thấy
                LK_timthay.Ten_LK =query.value(0).toString();
                LK_timthay.Ma_LK = query.value(1).toString();
                LK_timthay.Donvi_LK = query.value(2).toString();
                LK_timthay.Soluong_LK = query.value(3).toString();
                LK_timthay.Loai_LK = query.value(4).toString();
                LK_timthay.Ghichu_LK = query.value(5).toString();
            }
            this->db.close();
            //            ui->pushButton_ThemTrucTiep->setHidden(false);
            //            ui->pushButton_nhapthemvaokho->setHidden(false);
        }
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
        ui->tableWidget->setRowCount(1);
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
        DsLoai_LK.append("--TẤT CẢ--");
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

void MainWindow::CapNhatBangLK()
{
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(1);
    ui->tableWidget->scrollToTop();
    Seclect(ui->comboBox->currentText());

    //Gợi ý tìm kiếm
    wordList_timkiem = LoadTenLK_timkiem(ui->comboBox->currentText());
    QCompleter *completer = new QCompleter(wordList_timkiem, ui->lineEdit_timkiem);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setFilterMode(Qt::MatchContains);
    ui->lineEdit_timkiem->setCompleter(completer);

    ui->lineEdit_timkiem->clear();
    //    ui->pushButton_ThemTrucTiep->setHidden(true);
    //    ui->pushButton_nhapthemvaokho->setHidden(true);
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
    if( ui->lineEdit_xk_ghichu->text() =="")
    {
        QMessageBox::warning(this, "thông báo", "Lý do xuất kho trống, xin hãy nhập lại!");
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
        for (int row = 0; row < ui->tableWidget_2->rowCount(); row++)
        {
            QTableWidgetItem* item = ui->tableWidget_2->item(row, 1);
            QString MaLK = item->text();
            int SLHienTai = ui->tableWidget_2->item(row, 3)->text().toInt();
            int SLXuatKho = ui->tableWidget_2->item(row, 5)->text().toInt();

            int SLConLai = SLHienTai - SLXuatKho;
            CapNhatSoLuongLK(MaLK, SLConLai);
            CapNhatLSXuatKho(ui->lineEdit_xk_tennguoi->text(), ui->tableWidget_2->item(row, 0)->text(), ui->tableWidget_2->item(row, 1)->text(), ui->tableWidget_2->item(row, 5)->text(), ui->lineEdit_xk_ghichu->text(), QDate::currentDate().toString());

        }
        CapNhatBangTK();
        CapNhatBangLK();

        QMessageBox::warning(this, "Thông báo", "Xuất kho thành công!");
        //        on_pushButton_21_clicked();
        ui->tableWidget_2->clearContents();
        ui->tableWidget_2->setRowCount(0);   // Xóa các hàng trống

        SelectAll();
    }
}

void MainWindow::on_pushButton_22_clicked() //làm mới lịch sử
{
    this->wordList_xk = LoadTenNguoiXuatKho();
    QCompleter *completer_1 = new QCompleter(wordList_xk, ui->lineEdit_timnguoi_xk);
    completer_1->setCaseSensitivity(Qt::CaseInsensitive);
    ui->lineEdit_timnguoi_xk->setCompleter(completer_1);

    ui->lineEdit_timnguoi_xk->setDisabled(false);
    UpdateConnection();
    if(this->DatabaseConnected)
    {
        ui->tableWidget_3->clear();
        ui->tableWidget_3->setRowCount(1);

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
        ui->tableWidget_3->setRowCount(1);

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

/*void MainWindow::on_dateEdit_editingFinished() // tìm kiếm theo ngày
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
}*/

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
    ui->tableWidget->setRowCount(1);
    ui->tableWidget->scrollToTop();
    Seclect(arg1);

    //Gợi ý tìm kiếm
    wordList_timkiem = LoadTenLK_timkiem(ui->comboBox->currentText());
    QCompleter *completer = new QCompleter(wordList_timkiem, ui->lineEdit_timkiem);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setFilterMode(Qt::MatchContains);
    ui->lineEdit_timkiem->setCompleter(completer);

    ui->lineEdit_timkiem->clear();
}

void MainWindow::on_pushButton_7_clicked()  //QUẢN LÝ TÀI KHOẢN
{
    mQuanLy_TK = new QuanLy_TK();
    mQuanLy_TK->show();
}

void MainWindow::onLoginSuccessful(const QString &role, const QString &user)
{
    mTK_CaNhan = new TK_CaNhan();
    mTK_CaNhan->TenTK = user;
    qDebug() << "********************TEN NGUOI DANG NHAP LA: " << mTK_CaNhan->TenTK << endl;
    this->show();
    ui->lineEdit_xk_tennguoi->setText(user);
    ui->lineEdit_xk_tennguoi->setDisabled(true);

    if(role == "admin")
        QMessageBox::information(this, "Thông báo", "Truy cập dưới quyền Admin!");
    else if(role == "manager")
    {
        QMessageBox::information(this, "Thông báo", "Truy cập dưới quyền Quản lý kho!");
        ui->pushButton_7->setDisabled(true); //không thể truy cập vào Quản lý tài khoản

    }
    else if(role == "user")
    {
        QMessageBox::information(this, "Thông báo", "Truy cập dưới quyền Người dùng!");
        ui->pushButton_7->setDisabled(true); //không thể truy cập vào Quản lý tài khoản
        ui->tabWidget->setTabEnabled(0, false); //không thể sửa thông tin linh kiện
        ui->tabWidget->setTabEnabled(1, false); //không thể nhập thêm vào kho
        ui->pushButton_11->setDisabled(true);
        ui->pushButton_12->setDisabled(true);
        ui->pushButton_13->setDisabled(true);
        ui->pushButton_14->setDisabled(true);
        ui->pushButton_17->setDisabled(true);
        ui->pushButton_20->setDisabled(true);
    }
}

void MainWindow::on_pushButton_16_clicked()//xóa linh kiện trong giỏ
{
    if(row_table_2_clicked != -1)
    {
        ui->tableWidget_2->removeRow(this->row_table_2_clicked);
        row_table_2_clicked = -1;
    }
}

void MainWindow::on_lineEdit_timlk_xuatkho_editingFinished()//tìm kiếm lịch sử xuất kho theo Tên Linh kiện
{
    UpdateConnection();

    if(this->DatabaseConnected)
    {
        ui->tableWidget_3->clear();
        ui->tableWidget_3->setRowCount(1);

        QSqlQuery query(db);
        query.prepare("select * from LSXuatKho where TenLK == '"+ui->lineEdit_timlk_xuatkho->text() +"'");
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

QString MainWindow:: generateNewCode(const QString prefix) {
    UpdateConnection();
    QList<QString> result;
    QSqlQuery query(db);
    // Truy vấn mã lớn nhất với tiền tố prefix
    QString queryStr = QString("SELECT MAX(MaLK) FROM LinhKien WHERE MaLK LIKE '%1%'").arg(prefix);
    if (!query.exec(queryStr)) {
        qDebug() << "Database query error:" << query.lastError().text();
        return QString();
    }

    QString newCode;
    if (query.next()) {
        QString maxCode = query.value(0).toString();

        if (!maxCode.isEmpty()) {
            // Lấy phần số sau tiền tố và tăng lên 1
            int currentNumber = maxCode.mid(prefix.length()).toInt();
            int nextNumber = currentNumber + 1;

            // Tạo mã mới với số thứ tự đã tăng
            newCode = QString("%1%2").arg(prefix).arg(nextNumber, 3, 10, QChar('0'));
        } else {
            // Nếu không có mã nào với tiền tố này, bắt đầu với mã đầu tiên
            newCode = QString("%1%2").arg(prefix).arg(1, 3, 10, QChar('0'));
        }
    }

    return newCode;
}

void MainWindow::on_lineEdit_loaiLK_editingFinished()
{

    ui->lineEdit_MaLK->setText(generateNewCode(ui->lineEdit_loaiLK->text()) );
    //-------------
    ui->lineEdit_TenLK->setFocus();
}

void MainWindow::on_lineEdit_TenLK_editingFinished()
{
    ui->lineEdit_MaLK->setFocus();
}

void MainWindow::on_lineEdit_MaLK_editingFinished()
{
    ui->lineEdit_DV->setFocus();
}

void MainWindow::on_lineEdit_DV_editingFinished()
{
    ui->lineEdit_SoLuong->setFocus();
}

void MainWindow::on_lineEdit_SoLuong_editingFinished()
{
    ui->lineEdit_ghichu->setFocus();
}

/*void MainWindow::on_pushButton_ThemTrucTiep_clicked()//Thêm trực tiếp linh kiện vừa tìm được vào giỏ
{
    ui->tableWidget_2->setColumnWidth(0, 500);
    ui->tableWidget_2->setColumnWidth(1, 200);
    ui->tableWidget_2->setColumnWidth(2, 150);
    ui->tableWidget_2->setColumnWidth(3, 150);
    ui->tableWidget_2->setColumnWidth(4, 150);
    ui->tableWidget_2->setColumnWidth(5, 150);

    int row = ui->tableWidget_2->rowCount();
    ui->tableWidget_2->insertRow(row);

    QTableWidgetItem *TenLK1 = new QTableWidgetItem;
    QTableWidgetItem * MaLK1 = new QTableWidgetItem;
    QTableWidgetItem *DVTinh1 = new QTableWidgetItem;
    QTableWidgetItem *SLTonKho1 = new QTableWidgetItem;
    QTableWidgetItem *LoaiLK1 = new QTableWidgetItem;
    //    QTableWidgetItem *GhiChu1 = new QTableWidgetItem;

    TenLK1->setText(LK_timthay.Ten_LK);
    MaLK1->setText(LK_timthay.Ma_LK);
    DVTinh1->setText(LK_timthay.Donvi_LK);
    SLTonKho1->setText(LK_timthay.Soluong_LK);
    LoaiLK1->setText(LK_timthay.Loai_LK);
    //    GhiChu1->setText(ui->lineEdit_ghichu->text());

    ui->tableWidget_2->setItem(row, 0, TenLK1);
    ui->tableWidget_2->setItem(row, 1, MaLK1);
    ui->tableWidget_2->setItem(row, 2, DVTinh1);
    ui->tableWidget_2->setItem(row, 3, SLTonKho1);
    ui->tableWidget_2->setItem(row, 4, LoaiLK1);
    //    ui->tableWidget_2->setItem(row, 5, GhiChu1);

    ui->pushButton_ThemTrucTiep->setHidden(true);
}*/

void MainWindow::on_tableWidget_2_itemChanged(QTableWidgetItem *item)
{
    if(item->column() == 5)
    {
        int soluongxuat = ui->tableWidget_2->item(item->row(), 5)->text().toInt();
        QTableWidgetItem *thisitem = ui->tableWidget_2->item(item->row(), 3);
        int SLHienCo = thisitem->text().toInt();

        if(soluongxuat > SLHienCo)
            QMessageBox::warning(this, "Thông báo", "Số lượng xuất kho vượt quá số lượng hiện có, nhập lại!");
    }
}

void MainWindow::on_pushButton_nhapthemvaokho_clicked()//Nhập thêm linh kiện vào kho
{
    ui->tableWidget_nhapthem->setColumnWidth(0, 500);
    ui->tableWidget_nhapthem->setColumnWidth(1, 200);
    ui->tableWidget_nhapthem->setColumnWidth(2, 150);
    ui->tableWidget_nhapthem->setColumnWidth(3, 150);
    ui->tableWidget_nhapthem->setColumnWidth(4, 150);
    ui->tableWidget_nhapthem->setColumnWidth(5, 150);

    int row = ui->tableWidget_nhapthem->rowCount();
    ui->tableWidget_nhapthem->insertRow(row);

    QTableWidgetItem *TenLK1 = new QTableWidgetItem;
    QTableWidgetItem * MaLK1 = new QTableWidgetItem;
    QTableWidgetItem *DVTinh1 = new QTableWidgetItem;
    QTableWidgetItem *SLTonKho1 = new QTableWidgetItem;
    QTableWidgetItem *LoaiLK1 = new QTableWidgetItem;

    TenLK1->setText(LK_timthay.Ten_LK);
    MaLK1->setText(LK_timthay.Ma_LK);
    DVTinh1->setText(LK_timthay.Donvi_LK);
    SLTonKho1->setText(LK_timthay.Soluong_LK);
    LoaiLK1->setText(LK_timthay.Loai_LK);

    ui->tableWidget_nhapthem->setItem(row, 0, TenLK1);
    ui->tableWidget_nhapthem->setItem(row, 1, MaLK1);
    ui->tableWidget_nhapthem->setItem(row, 2, DVTinh1);
    ui->tableWidget_nhapthem->setItem(row, 3, SLTonKho1);
    ui->tableWidget_nhapthem->setItem(row, 4, LoaiLK1);

    ui->pushButton_nhapthemvaokho->setHidden(true);
}

void MainWindow::on_pushButton_xacnhapnhapthem_clicked()//Xác nhận nhập thêm vào kho
{
    //Kiểm tra số lượng nhập kho phù hợp
    for (int row = 0; row < ui->tableWidget_nhapthem->rowCount(); row++)
    {

        if(ui->tableWidget_nhapthem->item(row, 5) == nullptr)
        {
            QMessageBox::warning(this, "Thông báo", "Bạn chưa nhập hoàn thành số lượng nhập thêm, hãy kiểm tra lại!");
            return;
        }
    }

    //    bắt đầu cộng thêm vào số linh kiện còn lại
    for (int row = 0; row < ui->tableWidget_nhapthem->rowCount(); row++)
    {
        QTableWidgetItem* item = ui->tableWidget_nhapthem->item(row, 1);
        QString MaLK = item->text();
        int SLHienTai = ui->tableWidget_nhapthem->item(row, 3)->text().toInt();
        int SLXuatKho = ui->tableWidget_nhapthem->item(row, 5)->text().toInt();

        int SLMoi = SLHienTai + SLXuatKho;
        CapNhatSoLuongLK(MaLK, SLMoi);
        CapNhatLSNhapKho(ui->lineEdit_xk_tennguoi->text(), ui->tableWidget_nhapthem->item(row, 0)->text(), ui->tableWidget_nhapthem->item(row, 1)->text(), ui->tableWidget_nhapthem->item(row, 5)->text(), QDate::currentDate().toString());
    }
    CapNhatBangTK();
    CapNhatBangLK();

    QMessageBox::warning(this, "Thông báo", "Nhập kho thành công!");
    ui->tableWidget_nhapthem->clear();
    ui->tableWidget_nhapthem->setRowCount(1);
    SelectAll();
}

void MainWindow::CapNhatLSNhapKho(QString TenNguoiNK, QString TenLK, QString MaLK, QString SoLuongNK, QString NgayNK)
{
    this->UpdateConnection();
    if(this->DatabaseConnected)
    {
        QSqlQuery qry(this->db);
        qry.prepare("INSERT INTO LSNhapKho ( TenNguoiNK, TenLK, MaLK, SoLuongNK, "
                    "NgayNK) "
                    "VALUES (:TenNguoiNK, :TenLK, :MaLK, :SoLuongNK,"
                    ":NgayNK)");

        qry.bindValue(":TenNguoiNK", TenNguoiNK);
        qry.bindValue(":TenLK", TenLK);
        qry.bindValue(":MaLK", MaLK);
        qry.bindValue(":SoLuongNK", SoLuongNK);
        qry.bindValue(":NgayNK", NgayNK);

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

void MainWindow::on_pushButton_xoalknhapthem_clicked()///xóa linh kiện trong danh sách nhập thêm
{
    if(this->row_table_nhapthem_clicked != -1)
    {
        ui->tableWidget_nhapthem->removeRow(this->row_table_nhapthem_clicked);
        this->row_table_nhapthem_clicked = -1;
    }
}

void MainWindow::on_pushButton_huynhapthem_clicked()//hủy nhập thêm vào kho
{
    QMessageBox::warning(this, "Thông báo", "Hủy nhập thêm linh kiện có sẵn vào kho!");
    ui->tableWidget_nhapthem->clear();
    ui->tableWidget_nhapthem->setRowCount(1);

}

void MainWindow::on_pushButton_TK_canhanh_clicked()
{
    mTK_CaNhan->show();
}

void MainWindow::on_pushButton_lichsunhapkho_clicked()
{

    //------------
    this->wordList_nk = LoadTenNguoiNhapKho();
    QCompleter *completer_1 = new QCompleter(wordList_nk, ui->lineEdit_timnguoi_nhapkho);
    completer_1->setCaseSensitivity(Qt::CaseInsensitive);
    ui->lineEdit_timnguoi_nhapkho->setCompleter(completer_1);
    ui->lineEdit_timnguoi_nhapkho->setDisabled(false);

    UpdateConnection();
    if(this->DatabaseConnected)
    {
        ui->tableWidget_lsnhapkho->clear();
        ui->tableWidget_lsnhapkho->setRowCount(1);

        QSqlQuery query(db);
        query.prepare("select * from LSNhapKho");
        query.exec();

        ui->tableWidget_lsnhapkho->setColumnCount(6);
        QStringList list_labels;
        list_labels << "Tên người nhập kho" << "Mã nhập kho" << "Tên linh kiện"
                    << "Mã linh kiện" << "Số lượng nhập kho"<< "Ngày xuất kho";
        ui->tableWidget_lsnhapkho->setHorizontalHeaderLabels(list_labels);

        int rowcount = 0;
        while(query.next())
        {
            ui->tableWidget_lsnhapkho->insertRow(rowcount);
            QTableWidgetItem *TenNguoiNK = new QTableWidgetItem;
            QTableWidgetItem * MaNK = new QTableWidgetItem;
            QTableWidgetItem *TenLK = new QTableWidgetItem;
            QTableWidgetItem *MaLK = new QTableWidgetItem;
            QTableWidgetItem *SoLuongNK = new QTableWidgetItem;
            QTableWidgetItem *NgayNK = new QTableWidgetItem;

            TenNguoiNK->setText(query.value(0).toString());
            MaNK->setText(query.value(1).toString());
            TenLK->setText(query.value(2).toString());
            MaLK->setText(query.value(3).toString());
            SoLuongNK->setText(query.value(4).toString());
            NgayNK->setText(query.value(5).toString());

            ui->tableWidget_lsnhapkho->setItem(rowcount, 0, TenNguoiNK);
            ui->tableWidget_lsnhapkho->setItem(rowcount, 1, MaNK);
            ui->tableWidget_lsnhapkho->setItem(rowcount, 2, TenLK);
            ui->tableWidget_lsnhapkho->setItem(rowcount, 3, MaLK);
            ui->tableWidget_lsnhapkho->setItem(rowcount, 4, SoLuongNK);
            ui->tableWidget_lsnhapkho->setItem(rowcount, 5, NgayNK);

            rowcount++;
        }
        this->db.close();
    }
    ui->tableWidget_lsnhapkho->setColumnWidth(0, 300);
    ui->tableWidget_lsnhapkho->setColumnWidth(1, 100);
    ui->tableWidget_lsnhapkho->setColumnWidth(2, 200);
    ui->tableWidget_lsnhapkho->setColumnWidth(3, 100);
    ui->tableWidget_lsnhapkho->setColumnWidth(4, 150);
    ui->tableWidget_lsnhapkho->setColumnWidth(5, 130);
}

void MainWindow::on_lineEdit_timnguoi_nhapkho_editingFinished()
{
    UpdateConnection();

    if(this->DatabaseConnected)
    {
        ui->tableWidget_lsnhapkho->clear();
        ui->tableWidget_lsnhapkho->setRowCount(1);


        QSqlQuery query(db);
        query.prepare("select * from LSNhapKho where TenNguoiNK == '"+ui->lineEdit_timnguoi_nhapkho->text() +"'");
        query.exec();

        ui->tableWidget_lsnhapkho->setColumnCount(6);
        QStringList list_labels;
        list_labels << "Tên người nhập kho" << "Mã nhập kho" << "Tên linh kiện"
                    << "Mã linh kiện" << "Số lượng nhập kho" << "Ngày nhập kho";
        ui->tableWidget_lsnhapkho->setHorizontalHeaderLabels(list_labels);;

        int rowcount = 0;
        while(query.next())
        {
            ui->tableWidget_lsnhapkho->insertRow(rowcount);
            QTableWidgetItem *TenNguoiNK = new QTableWidgetItem;
            QTableWidgetItem * MaNK = new QTableWidgetItem;
            QTableWidgetItem *TenLK = new QTableWidgetItem;
            QTableWidgetItem *MaLK = new QTableWidgetItem;
            QTableWidgetItem *SoLuongNK = new QTableWidgetItem;
            QTableWidgetItem *NgayNK = new QTableWidgetItem;

            TenNguoiNK->setText(query.value(0).toString());
            MaNK->setText(query.value(1).toString());
            TenLK->setText(query.value(2).toString());
            MaLK->setText(query.value(3).toString());
            SoLuongNK->setText(query.value(4).toString());
            NgayNK->setText(query.value(5).toString());

            ui->tableWidget_lsnhapkho->setItem(rowcount, 0, TenNguoiNK);
            ui->tableWidget_lsnhapkho->setItem(rowcount, 1, MaNK);
            ui->tableWidget_lsnhapkho->setItem(rowcount, 2, TenLK);
            ui->tableWidget_lsnhapkho->setItem(rowcount, 3, MaLK);
            ui->tableWidget_lsnhapkho->setItem(rowcount, 4, SoLuongNK);
            ui->tableWidget_lsnhapkho->setItem(rowcount, 5, NgayNK);

            rowcount++;
        }
        this->db.close();
    }
    ui->tableWidget_lsnhapkho->setColumnWidth(0, 300);
    ui->tableWidget_lsnhapkho->setColumnWidth(1, 100);
    ui->tableWidget_lsnhapkho->setColumnWidth(2, 200);
    ui->tableWidget_lsnhapkho->setColumnWidth(3, 100);
    ui->tableWidget_lsnhapkho->setColumnWidth(4, 150);
    ui->tableWidget_lsnhapkho->setColumnWidth(5, 130);

}

void MainWindow::on_lineEdit_timlk_nhapkho_editingFinished()
{

    UpdateConnection();

    if(this->DatabaseConnected)
    {
        ui->tableWidget_lsnhapkho->clear();
        ui->tableWidget_lsnhapkho->setRowCount(1);


        QSqlQuery query(db);
        query.prepare("select * from LSNhapKho where TenLK == '"+ui->lineEdit_timlk_nhapkho->text() +"'");
        query.exec();

        ui->tableWidget_lsnhapkho->setColumnCount(6);
        QStringList list_labels;
        list_labels << "Tên người nhập kho" << "Mã nhập kho" << "Tên linh kiện"
                    << "Mã linh kiện" << "Số lượng nhập kho" << "Ngày nhập kho";
        ui->tableWidget_lsnhapkho->setHorizontalHeaderLabels(list_labels);;

        int rowcount = 0;
        while(query.next())
        {
            ui->tableWidget_lsnhapkho->insertRow(rowcount);
            QTableWidgetItem *TenNguoiNK = new QTableWidgetItem;
            QTableWidgetItem * MaNK = new QTableWidgetItem;
            QTableWidgetItem *TenLK = new QTableWidgetItem;
            QTableWidgetItem *MaLK = new QTableWidgetItem;
            QTableWidgetItem *SoLuongNK = new QTableWidgetItem;
            QTableWidgetItem *NgayNK = new QTableWidgetItem;

            TenNguoiNK->setText(query.value(0).toString());
            MaNK->setText(query.value(1).toString());
            TenLK->setText(query.value(2).toString());
            MaLK->setText(query.value(3).toString());
            SoLuongNK->setText(query.value(4).toString());
            NgayNK->setText(query.value(5).toString());

            ui->tableWidget_lsnhapkho->setItem(rowcount, 0, TenNguoiNK);
            ui->tableWidget_lsnhapkho->setItem(rowcount, 1, MaNK);
            ui->tableWidget_lsnhapkho->setItem(rowcount, 2, TenLK);
            ui->tableWidget_lsnhapkho->setItem(rowcount, 3, MaLK);
            ui->tableWidget_lsnhapkho->setItem(rowcount, 4, SoLuongNK);
            ui->tableWidget_lsnhapkho->setItem(rowcount, 5, NgayNK);

            rowcount++;
        }
        this->db.close();
    }
    ui->tableWidget_lsnhapkho->setColumnWidth(0, 300);
    ui->tableWidget_lsnhapkho->setColumnWidth(1, 100);
    ui->tableWidget_lsnhapkho->setColumnWidth(2, 200);
    ui->tableWidget_lsnhapkho->setColumnWidth(3, 100);
    ui->tableWidget_lsnhapkho->setColumnWidth(4, 150);
    ui->tableWidget_lsnhapkho->setColumnWidth(5, 130);

}

void MainWindow::on_pushButton_xuatfile_lsnhapkho_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(nullptr, "Export to Excel", "", "Excel Files (*.xls *.xlsx)");
    if (!fileName.isEmpty())
    {
        exportToExcel(ui->tableWidget_lsnhapkho, fileName);
        QMessageBox::information(nullptr, "Export to Excel", "Exported successfully!");
    }
}

void MainWindow::on_pushButton_huythem_clicked()
{
    foreach(QLineEdit* le, findChildren<QLineEdit*>())
    {
        if(le != ui->lineEdit_timkiem)
        {
            le->clear();
            le->setDisabled(false);
        }
    }
    ui->lineEdit_loaiLK->setFocus();
}
