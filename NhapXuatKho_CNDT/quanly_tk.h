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
    QString path_db = "C:\\Users\\ngock\\OneDrive\\Documents\\GitHub\\NhapXuatKho_CNDT\\quanlykho";

    void UpdateConnection();
    void LoadAll();
    void Select(QString loaiTK);

private slots:
    void on_comboBox_currentIndexChanged(const QString &arg1);

private:
    Ui::QuanLy_TK *ui;
};

#endif // QUANLY_TK_H
