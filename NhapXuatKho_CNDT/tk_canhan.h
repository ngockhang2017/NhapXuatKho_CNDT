#ifndef TK_CANHAN_H
#define TK_CANHAN_H

#include <QMainWindow>
#include <QShowEvent>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QMessageBox>

namespace Ui {
class TK_CaNhan;
}

class TK_CaNhan : public QMainWindow
{
    Q_OBJECT

public:
    explicit TK_CaNhan(QWidget *parent = nullptr);
    ~TK_CaNhan();
    QString TenTK = "...";
    void UpdateConnection();

protected:
    void showEvent(QShowEvent *event) override;

private:
    Ui::TK_CaNhan *ui;

public:
    QSqlDatabase db;
    bool DatabaseConnected;
     QString path_db = "C:\\Users\\ngock\\OneDrive\\Documents\\GitHub\\NhapXuatKho_CNDT\\NhapXuatKho_CNDT\\DATABASE\\QLK_DATABASE";
//    QString path_db = "D:\\PM_QLK\\DATABASE\\QLK_DATABASE";
private slots:
    void on_pushButton_luu_clicked();
};

#endif // TK_CANHAN_H
