#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QMessageBox>
#include<QDebug>
#include<QCompleter>
#include<QFileDialog>
//#include <QXlsx/xlsxdocument.h>
#include <QFile>
#include <QTextStream>
#include <QVariant>
#include<QTableWidget>
#include<sl_xuatkho.h>
#include<QDateTime>
#include<login.h>
#include<quanly_tk.h>
#include<tk_canhan.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct MotLK
{
    QString Loai_LK;
    QString Ten_LK;
    QString Ma_LK;
    QString Donvi_LK;
    QString Soluong_LK;
    QString Ghichu_LK;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public:
    QSqlDatabase db;
    bool DatabaseConnected;
//        QString path_db = "D:\\PM_QLK\\DATABASE\\QLK_DATABASE";
    QString path_db = "C:\\Users\\HuynhPhanNgocKhang\\Documents\\GitHub\\NhapXuatKho_CNDT\\NhapXuatKho_CNDT\\DATABASE\\QLK_DB_new";

    QString ID_DoubleCLick;

    void UpdateConnection();
    void Seclect(QString LoaiLK);
    void SelectAll();
    QList<QString> LoadTenLK();
    QList<QString> LoadTenLK_timkiem(QString loaiLK);
    QList<QString> LoadTenNguoiXuatKho();
    QList<QString> LoadTenNguoiNhapKho();

    void exportToExcel(QTableWidget *tableWidget, const QString &fileName);
    int SLhienCoCuaMotLK = 0;
    void CapNhatSoLuongLK(QString MaLK, int SoLuongConLai);
    void CapNhatLSXuatKho(QString TenNguoiXK, QString TenLK, QString MaLK, QString SoLuongXK, QString GhiChu, QString NgayXK);
     void CapNhatLSNhapKho(QString TenNguoiNK, QString TenLK, QString MaLK, QString SoLuongNK, QString NgayNK);
    void CapNhatDS_loaiLK();
    void CapNhatBangTK();
    void CapNhatBangLK();
    QString generateNewCode(const QString prefix);

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void SectionDoubleClick(int row, int column);
    void SectionDoubleClick_2(int row, int column);
    void SectionDoubleClick_3(int row, int column);

    void on_pushButton_14_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_20_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_lineEdit_timkiem_editingFinished();

    void on_pushButton_clicked();

    void on_pushButton_21_clicked();

    void on_lineEdit_xksl_editingFinished();

    void on_pushButton_15_clicked();

    void on_pushButton_22_clicked();

    void on_lineEdit_timnguoi_xk_editingFinished();

    void on_pushButton_23_clicked();

//    void on_dateEdit_editingFinished();

    void on_pushButton_18_clicked();

    void on_comboBox_editTextChanged(const QString &arg1);

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_pushButton_7_clicked();

    // MainWindow.h
    void on_pushButton_16_clicked();

    void on_lineEdit_timlk_xuatkho_editingFinished();

    void on_lineEdit_loaiLK_editingFinished();

    void on_lineEdit_TenLK_editingFinished();

    void on_lineEdit_MaLK_editingFinished();

    void on_lineEdit_DV_editingFinished();

    void on_lineEdit_SoLuong_editingFinished();

//    void on_pushButton_ThemTrucTiep_clicked();

    void on_tableWidget_2_itemChanged(QTableWidgetItem *item);

    void on_pushButton_nhapthemvaokho_clicked();

    void on_pushButton_xacnhapnhapthem_clicked();

    void on_pushButton_xoalknhapthem_clicked();

    void on_pushButton_huynhapthem_clicked();

    void on_pushButton_TK_canhanh_clicked();

    void on_pushButton_lichsunhapkho_clicked();

    void on_lineEdit_timnguoi_nhapkho_editingFinished();

    void on_lineEdit_timlk_nhapkho_editingFinished();

    void on_pushButton_xuatfile_lsnhapkho_clicked();

    void on_pushButton_huythem_clicked();

    void on_lineEdit_lonhon_bang_editingFinished();

    void on_pushButton_xuatfile_dshientai_clicked();

public slots:
    void onLoginSuccessful(const QString &role, const QString &user);

private:
    Ui::MainWindow *ui;
    SL_XuatKho *m_SL_XuatKho;
    QStringList wordList, wordList_xk, wordList_timkiem, wordList_nk;
    QStringList DsLoai_LK;
    Login *mLogin;
    QuanLy_TK *mQuanLy_TK;
    int row_table_2_clicked = -1, row_table_nhapthem_clicked = -1;

    MotLK LK_timthay;
    TK_CaNhan *mTK_CaNhan;
};
#endif // MAINWINDOW_H
