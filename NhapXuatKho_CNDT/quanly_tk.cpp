#include "quanly_tk.h"
#include "ui_quanly_tk.h"

QuanLy_TK::QuanLy_TK(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QuanLy_TK)
{
    ui->setupUi(this);
}

QuanLy_TK::~QuanLy_TK()
{
    delete ui;
}
