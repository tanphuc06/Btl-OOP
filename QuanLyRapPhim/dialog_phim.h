#ifndef DIALOG_PHIM_H
#define DIALOG_PHIM_H

#include <QDialog>

namespace Ui {
class Dialog_phim;
}

class Dialog_phim : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_phim(QWidget *parent = nullptr);
    ~Dialog_phim();

private:
    Ui::Dialog_phim *ui;
};

#endif
