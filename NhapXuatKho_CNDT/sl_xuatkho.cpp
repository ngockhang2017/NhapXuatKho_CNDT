#include "sl_xuatkho.h"
#include "ui_sl_xuatkho.h"

SL_XuatKho::SL_XuatKho(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SL_XuatKho)
{
    ui->setupUi(this);
}

SL_XuatKho::~SL_XuatKho()
{
    delete ui;
}

void SL_XuatKho::on_pushButton_clicked()
{

}
