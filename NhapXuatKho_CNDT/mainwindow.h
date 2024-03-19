#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QMessageBox>
#include<QDebug>

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
    QString path_db = "C:/Users/ngock/OneDrive/Documents/GitHub/NhapXuatKho_CNDT/quanlykho";
    int ID_DoubleCLick;

    void UpdateConnection();
    void Seclect(QString LoaiLK);
    void SelectAll();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void SectionDoubleClick(int row, int column);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
