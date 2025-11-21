#include "dialog_phim.h"
#include "ui_dialog_phim.h"

Dialog_phim::Dialog_phim(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_phim)
{
    ui->setupUi(this);
}

Dialog_phim::~Dialog_phim()
{
    delete ui;
}
