#pragma once

#include <QMainWindow>
#include <QTableWidget>
#include <QListWidget>
#include <QStackedWidget>
#include <QPushButton>
#include <QLabel>
#include <QInputDialog>
#include <QMessageBox>
#include <QHeaderView>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QStatusBar>
#include <QLineEdit>
#include <QDate>
#include <QBrush>

#include "data_model.h"

// BIẾN TOÀN CỤC & HÀM HỖ TRỢ

extern danhSachPhimList sc, dc;
extern danhSachPhongChieu a;
extern danhSachXuatChieu ds;
extern danhSachVe dsv;
void chuyenPhim(const string& maPhim);
//  LỚP MAINWINDOW
class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onMenuClicked(QListWidgetItem* item);
    // Phim
    void handleAddPhim(bool isSapChieu);
    void handleEditPhim(bool isSapChieu);
    void handleDeletePhim(bool isSapChieu);
    void handleChuyenPhim();

    // Phòng chiếu
    void handleAddPhong();
    void handleEditPhong();
    void handleDeletePhong();
    void handleTimPhong();

    // Suất chiếu
    void handleAddXuatChieu();
    void handleEditXuatChieu();
    void handleDeleteXuatChieu();
    void handleTimXuatChieu();

    // Vé
    void handleDatVe();
    void handleThanhToanVe();
    void handleEditVe();
    void handleDeleteVe();
    void handleTimVe();

    // Doanh thu
    void handleTinhDoanhThuNgay();
    void handleTinhDoanhThuThang();

private:
    void setupUI();
    void addSampleData();
    void refreshAllTables();
    void refreshPhimTables();
    void refreshPhongChieuTable();
    void refreshXuatChieuTable();
    void refreshVeTable();

    bool inputPhim(danhSachPhim& p, const QString& title, bool isEdit = false);
    bool inputPhongChieu(phongChieu& p, const QString& title, bool isEdit = false);
    bool inputXuatChieu(xuatChieu& xc, const QString& title, bool isEdit = false);
    bool inputVe(ve& v, const QString& title, bool isEdit = false);

    // Thành phần UI
    QListWidget* menu;
    QStackedWidget* stack;
    QTableWidget *tblSapChieu, *tblDangChieu;
    QTableWidget *tblPhongChieu, *tblXuatChieu, *tblVe;

    QLabel *lblTongDoanhThu;
    QPushButton *btnTimDoanhThuNgay, *btnTimDoanhThuThang;
};
