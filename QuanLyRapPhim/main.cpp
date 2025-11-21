#include "mainwindow.h"
#include <QApplication>
#include <QLocale>
#include <QFont>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QLocale::setDefault(QLocale(QLocale::Vietnamese, QLocale::Vietnam));
    QFont font("Segoe UI", 10);
    a.setFont(font);

    a.setApplicationName("Quản Lý Rạp Chiếu Phim");
    a.setApplicationVersion("2.0 - GUI Full");

    MainWindow w;
    w.setWindowTitle("QUẢN LÝ RẠP CHIẾU PHIM ");
    w.resize(1600, 900);
    w.show();

    return a.exec();
}
