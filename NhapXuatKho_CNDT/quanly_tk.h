#ifndef QUANLY_TK_H
#define QUANLY_TK_H

#include <QMainWindow>
#include<QMessageBox>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QDebug>
#include<QSqlError>

namespace Ui {
class QuanLy_TK;
}

class QuanLy_TK : public QMainWindow
{
    Q_OBJECT

public:
    explicit QuanLy_TK(QWidget *parent = nullptr);
    ~QuanLy_TK();
public:
    QSqlDatabase db;
    bool DatabaseConnected;
//    QString path_db = "C:\\Users\\ngock\\OneDrive\\Documents\\GitHub\\NhapXuatKho_CNDT\\NhapXuatKho_CNDT\\DATABASE\\QLK_DATABASE";
    QString path_db = "D:\\PM_QLK\\DATABASE\\QLK_DATABASE";

    void UpdateConnection();
    void LoadAll();
    void Select(QString loaiTK);

private slots:
    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_pushButton_BatDauThem_clicked();

    void on_lineEdit_MatKhau_textEdited(const QString &arg1);

    void on_lineEdit_MatKhau_editingFinished();

    void on_pushButton_pressed();

    void on_pushButton_released();

    void on_pushButton_Luu_clicked();
    void SectionDoubleClick(int row, int column);

    void on_pushButton_CapNhat_clicked();

    void on_pushButton_XoaTK_clicked();

private:
    Ui::QuanLy_TK *ui;
    QString User;
};

#endif // QUANLY_TK_H
