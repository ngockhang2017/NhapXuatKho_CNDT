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

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public:
    QSqlDatabase db;
    bool DatabaseConnected;
//    QString path_db = "C:/Users/ngock/OneDrive/Documents/GitHub/NhapXuatKho_CNDT/quanlykho";
    QString path_db = "D:/PM_QLK/quanlykho";
    QString ID_DoubleCLick;

    void UpdateConnection();
    void Seclect(QString LoaiLK);
    void SelectAll();
    QList<QString> LoadTenLK();
    QList<QString> LoadTenNguoiXuatKho();
    void exportToExcel(QTableWidget *tableWidget, const QString &fileName);
    int SLhienCoCuaMotLK = 0;
    void CapNhatSoLuongLK(QString MaLK, int SoLuongConLai);
    void CapNhatLSXuatKho(QString TenNguoiXK, QString TenLK, QString MaLK, QString SoLuongXK, QString GhiChu, QString NgayXK);
    void CapNhatDS_loaiLK();
    void CapNhatBangTK();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void SectionDoubleClick(int row, int column);
    void SectionDoubleClick_2(int row, int column);

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

    void on_dateEdit_editingFinished();

    void on_pushButton_19_clicked();

    void on_pushButton_18_clicked();

    void on_comboBox_editTextChanged(const QString &arg1);

    void on_comboBox_currentIndexChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    SL_XuatKho *m_SL_XuatKho;

    QStringList wordList, wordList_xk;
    QStringList DsLoai_LK;
    Login *mLogin;
};
#endif // MAINWINDOW_H
