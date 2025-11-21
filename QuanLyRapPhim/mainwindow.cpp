#include "mainwindow.h"

danhSachPhimList sc, dc;
danhSachPhongChieu a;
danhSachXuatChieu ds;
danhSachVe dsv;

//HÀM HỖ TRỢ CHUNG

void chuyenPhim(const string& maPhim) {
    Node* node = sc.timKiem(maPhim);
    if (node) {
        dc.themPhimTuDanhSachKhac(node->data);
        sc.xoaPhim(maPhim);
    }
}

QString getCurrentDateString() {
    return QDate::currentDate().toString("dd/MM/yyyy");
}
QDate parseDateString(const string& dateStr) {
    QDate date = QDate::fromString(QString::fromStdString(dateStr), "dd/MM/yyyy");
    return date.isValid() ? date : QDate::currentDate();
}

// LỚP MAINWINDOW

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setupUI();
    refreshAllTables();
}

void MainWindow::setupUI() {
    QWidget* central = new QWidget(this);
    setCentralWidget(central);
    QHBoxLayout* mainLay = new QHBoxLayout(central);

    // Menu chính
    menu = new QListWidget();
    menu->setFixedWidth(300);
    menu->setStyleSheet("QListWidget { background: #2c3e50; color: white; font-size: 17px; }"
                        "QListWidget::item:selected { background: #e74c3c; }");
    QStringList items = {"1. Phim sắp chiếu", "2. Phim đang chiếu", "3. Quản lý Phòng chiếu", "4. Quản lý Suất chiếu", "5. Quản lý Vé", "6. Tổng Doanh thu"};
    menu->addItems(items);
    connect(menu, &QListWidget::itemClicked, this, &MainWindow::onMenuClicked);

    stack = new QStackedWidget();
    mainLay->addWidget(menu);
    mainLay->addWidget(stack, 1);

    //  Sắp chiếu
    QWidget* p1 = new QWidget();
    QVBoxLayout* v1 = new QVBoxLayout(p1);
    tblSapChieu = new QTableWidget(0, 6);
    tblSapChieu->setHorizontalHeaderLabels({"Mã", "Tên phim", "Đạo diễn", "Thể loại", "Thời lượng", "Khởi chiếu"});
    tblSapChieu->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QHBoxLayout* btns1 = new QHBoxLayout();
    QPushButton* add1 = new QPushButton("Thêm phim");
    QPushButton* edit1 = new QPushButton("Sửa");
    QPushButton* del1 = new QPushButton("Xóa");
    QPushButton* chuyen = new QPushButton("→ Chuyển sang đang chiếu");
    add1->setStyleSheet(
        "QPushButton { background: #2ecc71; color: white; font-weight: bold; }"
        "QPushButton:hover { background: #27ae60; }"
        );
    edit1->setStyleSheet(
        "QPushButton { background: #3498db; color: white; font-weight: bold; }"
        "QPushButton:hover { background: #2980b9; }"
        );
    del1->setStyleSheet(
        "QPushButton { background: #e74c3c; color: white; font-weight: bold; }"
        "QPushButton:hover { background: #c0392b; }"
        );
    chuyen->setStyleSheet("background:#e67e22; color:white; font-weight:bold;");
    btns1->addWidget(add1); btns1->addWidget(edit1); btns1->addWidget(del1); btns1->addWidget(chuyen);
    v1->addWidget(tblSapChieu);
    v1->addLayout(btns1);
    stack->addWidget(p1);

    connect(add1, &QPushButton::clicked, [this]() { handleAddPhim(true); });
    connect(edit1, &QPushButton::clicked, [this]() { handleEditPhim(true); });
    connect(del1, &QPushButton::clicked, [this]() { handleDeletePhim(true); });
    connect(chuyen, &QPushButton::clicked, this, &MainWindow::handleChuyenPhim);

    //  Đang chiếu
    QWidget* p2 = new QWidget();
    QVBoxLayout* v2 = new QVBoxLayout(p2);
    tblDangChieu = new QTableWidget(0, 6);
    tblDangChieu->setHorizontalHeaderLabels({"Mã", "Tên phim", "Đạo diễn", "Thể loại", "Thời lượng", "Khởi chiếu"});
    tblDangChieu->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    QHBoxLayout* btns2 = new QHBoxLayout();
    QPushButton* add2 = new QPushButton("Thêm phim");
    QPushButton* edit2 = new QPushButton("Sửa");
    QPushButton* del2 = new QPushButton("Xóa");
    add2->setStyleSheet(
        "QPushButton { background: #2ecc71; color: white; font-weight: bold; }"
        "QPushButton:hover { background: #27ae60; }"
        );
    edit2->setStyleSheet(
        "QPushButton { background: #3498db; color: white; font-weight: bold; }"
        "QPushButton:hover { background: #2980b9; }"
        );
    del2->setStyleSheet(
        "QPushButton { background: #e74c3c; color: white; font-weight: bold; }"
        "QPushButton:hover { background: #c0392b; }"
        );
    btns2->addWidget(add2); btns2->addWidget(edit2); btns2->addWidget(del2);
    v2->addWidget(tblDangChieu); v2->addLayout(btns2);
    stack->addWidget(p2);

    connect(add2, &QPushButton::clicked, [this]() { handleAddPhim(false); });
    connect(edit2, &QPushButton::clicked, [this]() { handleEditPhim(false); });
    connect(del2, &QPushButton::clicked, [this]() { handleDeletePhim(false); });

    // Quản lý Phòng chiếu
    QWidget* p3 = new QWidget();
    QVBoxLayout* v3 = new QVBoxLayout(p3);
    tblPhongChieu = new QTableWidget(0, 4);
    tblPhongChieu->setHorizontalHeaderLabels({"Mã phòng", "Loại phòng", "Số ghế", "Tình trạng"});
    tblPhongChieu->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    QHBoxLayout* btns3 = new QHBoxLayout();
    QPushButton* add3 = new QPushButton("Thêm phòng");
    QPushButton* edit3 = new QPushButton("Sửa");
    QPushButton* del3 = new QPushButton("Xóa");
    QPushButton* search3 = new QPushButton("Tìm kiếm");
    add3->setStyleSheet(
        "QPushButton { background: #2ecc71; color: white; font-weight: bold; }"
        "QPushButton:hover { background: #27ae60; }"
        );
    edit3->setStyleSheet(
        "QPushButton { background: #3498db; color: white; font-weight: bold; }"
        "QPushButton:hover { background: #2980b9; }"
        );
    del3->setStyleSheet(
        "QPushButton { background: #e74c3c; color: white; font-weight: bold; }"
        "QPushButton:hover { background: #c0392b; }"
        );

    btns3->addWidget(add3); btns3->addWidget(edit3); btns3->addWidget(del3); btns3->addWidget(search3);
    v3->addWidget(tblPhongChieu); v3->addLayout(btns3);
    stack->addWidget(p3);

    connect(add3, &QPushButton::clicked, this, &MainWindow::handleAddPhong);
    connect(edit3, &QPushButton::clicked, this, &MainWindow::handleEditPhong);
    connect(del3, &QPushButton::clicked, this, &MainWindow::handleDeletePhong);
    connect(search3, &QPushButton::clicked, this, &MainWindow::handleTimPhong);

    //  Quản lý Suất chiếu
    QWidget* p4 = new QWidget();
    QVBoxLayout* v4 = new QVBoxLayout(p4);
    tblXuatChieu = new QTableWidget(0, 6);
    tblXuatChieu->setHorizontalHeaderLabels({"Mã Suất Chiếu", "Mã phim", "Mã phòng", "Ngày chiếu", "Giờ chiếu", "Giá vé"});
    tblXuatChieu->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    QHBoxLayout* btns4 = new QHBoxLayout();
    QPushButton* add4 = new QPushButton("Thêm Suất Chiếu");
    QPushButton* edit4 = new QPushButton("Sửa");
    QPushButton* del4 = new QPushButton("Xóa");
    QPushButton* search4 = new QPushButton("Tìm kiếm (Giờ)");
    add4->setStyleSheet(
        "QPushButton { background: #2ecc71; color: white; font-weight: bold; }"
        "QPushButton:hover { background: #27ae60; }"
        );
    edit4->setStyleSheet(
        "QPushButton { background: #3498db; color: white; font-weight: bold; }"
        "QPushButton:hover { background: #2980b9; }"
        );
    del4->setStyleSheet(
        "QPushButton { background: #e74c3c; color: white; font-weight: bold; }"
        "QPushButton:hover { background: #c0392b; }"
        );
    btns4->addWidget(add4); btns4->addWidget(edit4); btns4->addWidget(del4); btns4->addWidget(search4);
    v4->addWidget(tblXuatChieu); v4->addLayout(btns4);
    stack->addWidget(p4);

    connect(add4, &QPushButton::clicked, this, &MainWindow::handleAddXuatChieu);
    connect(edit4, &QPushButton::clicked, this, &MainWindow::handleEditXuatChieu);
    connect(del4, &QPushButton::clicked, this, &MainWindow::handleDeleteXuatChieu);
    connect(search4, &QPushButton::clicked, this, &MainWindow::handleTimXuatChieu);

    // ---  Quản lý Vé ---
    QWidget* p5 = new QWidget();
    QVBoxLayout* v5 = new QVBoxLayout(p5);
    tblVe = new QTableWidget(0, 8);
    tblVe->setHorizontalHeaderLabels({"Mã vé", "Mã Suất Chiếu", "Mã phim", "Mã phòng", "Ngày chiếu", "Giờ chiếu", "Giá vé", "Trạng thái"});
    tblVe->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    QHBoxLayout* btns5 = new QHBoxLayout();
    QPushButton* add5 = new QPushButton("Đặt vé");
    QPushButton* edit5 = new QPushButton("Sửa");
    QPushButton* del5 = new QPushButton("Hủy Vé");
    QPushButton* pay5 = new QPushButton("Thanh toán");
    QPushButton* search5 = new QPushButton("Tìm kiếm");
    add5->setStyleSheet(
        "QPushButton { background: #2ecc71; color: white; font-weight: bold; }"
        "QPushButton:hover { background: #27ae60; }"
        );
    edit5->setStyleSheet(
        "QPushButton { background: #3498db; color: white; font-weight: bold; }"
        "QPushButton:hover { background: #2980b9; }"
        );
    del5->setStyleSheet(
        "QPushButton { background: #e74c3c; color: white; font-weight: bold; }"
        "QPushButton:hover { background: #c0392b; }"
        );
    pay5->setStyleSheet(
        "QPushButton { background: #f39c12; color: white; font-weight: bold;; }"
        "QPushButton:hover { background: #f39c12; }"
        );


    btns5->addWidget(add5); btns5->addWidget(pay5); btns5->addWidget(edit5); btns5->addWidget(del5); btns5->addWidget(search5);
    v5->addWidget(tblVe); v5->addLayout(btns5);
    stack->addWidget(p5);

    connect(add5, &QPushButton::clicked, this, &MainWindow::handleDatVe);
    connect(pay5, &QPushButton::clicked, this, &MainWindow::handleThanhToanVe);
    connect(edit5, &QPushButton::clicked, this, &MainWindow::handleEditVe);
    connect(del5, &QPushButton::clicked, this, &MainWindow::handleDeleteVe);
    connect(search5, &QPushButton::clicked, this, &MainWindow::handleTimVe);
    // DOANH THU
    QWidget* p6 = new QWidget();
    QVBoxLayout* v6 = new QVBoxLayout(p6);
    lblTongDoanhThu = new QLabel("Chọn chức năng để tính toán doanh thu.");
    lblTongDoanhThu->setStyleSheet("font-size: 20px; font-weight: bold; color: #e6b800;");

    QHBoxLayout* btns6 = new QHBoxLayout();
    btnTimDoanhThuNgay = new QPushButton("Tính Doanh Thu Theo Ngày");
    btnTimDoanhThuThang = new QPushButton("Tính Doanh Thu Theo Tháng/Năm");
    const QString revenueButtonStyle =
        "QPushButton { background: #3498db; color: white; font-weight: bold; border-radius: 5px; padding: 10px; }"
        "QPushButton:hover { background: #2980b9; }";
    btnTimDoanhThuNgay->setStyleSheet(revenueButtonStyle);
    btnTimDoanhThuThang->setStyleSheet(revenueButtonStyle);

    btns6->addWidget(btnTimDoanhThuNgay);
    btns6->addWidget(btnTimDoanhThuThang);
    btns6->addWidget(btnTimDoanhThuNgay); btns6->addWidget(btnTimDoanhThuThang);

    QTableWidget* tblDoanhThu = new QTableWidget(0, 4);
    tblDoanhThu->setHorizontalHeaderLabels({"Mã vé", "Mã suất chiếu", "Ngày chiếu", "Giá vé"});
    tblDoanhThu->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tblDoanhThu->setEnabled(false);

    v6->addWidget(lblTongDoanhThu);
    v6->addLayout(btns6);
    v6->addWidget(tblDoanhThu);
    v6->addStretch(1);
    stack->addWidget(p6);

    connect(btnTimDoanhThuNgay, &QPushButton::clicked, this, &MainWindow::handleTinhDoanhThuNgay);
    connect(btnTimDoanhThuThang, &QPushButton::clicked, this, &MainWindow::handleTinhDoanhThuThang);

    statusBar()->showMessage("Sẵn sàng - Grok Cinema Manager 2025 ©");
}

void MainWindow::onMenuClicked(QListWidgetItem* item) {
    stack->setCurrentIndex(menu->row(item));
    refreshAllTables();
}

// PHIM SAP/DANG CHIEU

bool MainWindow::inputPhim(danhSachPhim& p, const QString& title, bool isEdit) {
    bool ok;
    QString ma = isEdit ? QString::fromStdString(p.maPhim) : "";

    QString maInput = QInputDialog::getText(this, title, "Mã phim:", QLineEdit::Normal, ma, &ok);
    if(!ok) return false;
    if (!isEdit) {
        if (sc.timKiem(maInput.toStdString()) || dc.timKiem(maInput.toStdString())) {
            QMessageBox::warning(this, "Lỗi", "Mã phim đã tồn tại!");
            return false;
        }
    }

    QString ten = QInputDialog::getText(this, title, "Tên phim:", QLineEdit::Normal, QString::fromStdString(p.tenPhim), &ok); if(!ok) return false;
    QString dd = QInputDialog::getText(this, title, "Đạo diễn:", QLineEdit::Normal, QString::fromStdString(p.daoDien), &ok); if(!ok) return false;
    QString tl = QInputDialog::getText(this, title, "Thể loại:", QLineEdit::Normal, QString::fromStdString(p.theLoai), &ok); if(!ok) return false;
    int tlPhut = QInputDialog::getInt(this, title, "Thời lượng (phút):", p.thoiLuong > 0 ? p.thoiLuong : 120, 60, 300, 1, &ok); if(!ok) return false;

    QString kcString = QInputDialog::getText(this, title, "Ngày khởi chiếu (dd/MM/yyyy):", QLineEdit::Normal, QString::fromStdString(p.khoiChieu), &ok); if(!ok) return false;
    if (!QDate::fromString(kcString, "dd/MM/yyyy").isValid()) {
        QMessageBox::warning(this, "Lỗi định dạng", "Ngày khởi chiếu phải theo định dạng dd/MM/yyyy.");
        return false;
    }

    p.maPhim = maInput.toStdString();
    p.tenPhim = ten.toStdString();
    p.daoDien = dd.toStdString();
    p.theLoai = tl.toStdString();
    p.thoiLuong = tlPhut;
    p.khoiChieu = kcString.toStdString();
    return true;
}

void MainWindow::handleAddPhim(bool isSapChieu) {
    danhSachPhim p;
    if (inputPhim(p, isSapChieu ? "Thêm phim sắp chiếu" : "Thêm phim đang chiếu")) {
        if (isSapChieu) sc.themPhimTuDanhSachKhac(p);
        else dc.themPhimTuDanhSachKhac(p);
        refreshAllTables();
    }
}

void MainWindow::handleEditPhim(bool isSapChieu) {
    QTableWidget* tbl = isSapChieu ? tblSapChieu : tblDangChieu;
    danhSachPhimList& list = isSapChieu ? sc : dc;
    int row = tbl->currentRow();
    if (row >= 0) {
        string ma = tbl->item(row, 0)->text().toStdString();
        Node* n = list.timKiem(ma);
        if (n) {
            if (inputPhim(n->data, "Sửa phim", true)) {
                QMessageBox::information(this, "Thành công", "Cập nhật phim thành công!");
                refreshAllTables();
            }
        }
    } else {
        QMessageBox::warning(this, "Lỗi", "Vui lòng chọn một hàng để sửa.");
    }
}

void MainWindow::handleDeletePhim(bool isSapChieu) {
    QTableWidget* tbl = isSapChieu ? tblSapChieu : tblDangChieu;
    danhSachPhimList& list = isSapChieu ? sc : dc;
    int row = tbl->currentRow();
    if (row >= 0) {
        if (QMessageBox::question(this, "Xác nhận", "Bạn có chắc chắn muốn xóa phim này không?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
            list.xoaPhim(tbl->item(row, 0)->text().toStdString());
            refreshAllTables();
        }
    } else {
        QMessageBox::warning(this, "Lỗi", "Vui lòng chọn một hàng để xóa.");
    }
}

void MainWindow::handleChuyenPhim() {
    int row = tblSapChieu->currentRow();
    if (row >= 0) {
        string ma = tblSapChieu->item(row, 0)->text().toStdString();
        chuyenPhim(ma);
        refreshAllTables();
    } else {
        QMessageBox::warning(this, "Lỗi", "Vui lòng chọn một phim sắp chiếu để chuyển.");
    }
}

//PHÒNG CHIẾU

bool MainWindow::inputPhongChieu(phongChieu& p, const QString& title, bool isEdit) {
    bool ok;
    QString ma = isEdit ? QString::fromStdString(p.maPhong) : "";

    QString maInput = QInputDialog::getText(this, title, "Mã phòng:", QLineEdit::Normal, ma, &ok);
    if(!ok) return false;
    if (!isEdit) {
        if (a.timKiem(maInput.toStdString())) {
            QMessageBox::warning(this, "Lỗi", "Mã phòng đã tồn tại!");
            return false;
        }
    }

    QString loai = QInputDialog::getText(this, title, "Loại phòng:", QLineEdit::Normal, QString::fromStdString(p.loaiPhong), &ok); if(!ok) return false;
    int soGhe = QInputDialog::getInt(this, title, "Số ghế:", p.soGhe > 0 ? p.soGhe : 100, 50, 500, 1, &ok); if(!ok) return false;

    QStringList tinhTrangList = {"Trống", "Đang chiếu", "Đang sửa"};
    QString tinhTrang = QInputDialog::getItem(this, title, "Tình trạng:", tinhTrangList, tinhTrangList.indexOf(QString::fromStdString(p.tinhTrang)), false, &ok); if(!ok) return false;

    p.maPhong = maInput.toStdString();
    p.loaiPhong = loai.toStdString();
    p.soGhe = soGhe;
    p.tinhTrang = tinhTrang.toStdString();
    return true;
}

void MainWindow::handleAddPhong() {
    phongChieu p;
    if (inputPhongChieu(p, "Thêm phòng chiếu")) {
        a.themPhong(p);
        refreshAllTables();
        QMessageBox::information(this, "Thành công", "Đã thêm phòng chiếu thành công.");
    }
}

void MainWindow::handleEditPhong() {
    int row = tblPhongChieu->currentRow();
    if (row >= 0) {
        string ma = tblPhongChieu->item(row, 0)->text().toStdString();
        Node1* n = a.timKiem(ma);
        if (n) {
            if (inputPhongChieu(n->data, "Sửa phòng chiếu", true)) {
                QMessageBox::information(this, "Thành công", "Cập nhật phòng thành công!");
                refreshAllTables();
            }
        }
    } else {
        QMessageBox::warning(this, "Lỗi", "Vui lòng chọn một hàng để sửa.");
    }
}

void MainWindow::handleDeletePhong() {
    int row = tblPhongChieu->currentRow();
    if (row >= 0) {
        if (QMessageBox::question(this, "Xác nhận", "Bạn có chắc chắn muốn xóa phòng này không?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
            a.xoaPhong(tblPhongChieu->item(row, 0)->text().toStdString());
            refreshAllTables();
        }
    } else {
        QMessageBox::warning(this, "Lỗi", "Vui lòng chọn một hàng để xóa.");
    }
}

void MainWindow::handleTimPhong() {
    bool ok;
    QString maOrTt = QInputDialog::getText(this, "Tìm kiếm phòng", "Nhập Mã phòng hoặc Tình trạng:", QLineEdit::Normal, "", &ok);
    if (!ok || maOrTt.isEmpty()) return;

    tblPhongChieu->setRowCount(0);
    bool found = false;

    for (Node1* t = a.head; t; t = t->next) {
        QString ma = QString::fromStdString(t->data.getMaPhong());
        QString tt = QString::fromStdString(t->data.getTinhTrang());

        if (ma.compare(maOrTt, Qt::CaseInsensitive) == 0 || tt.compare(maOrTt, Qt::CaseInsensitive) == 0) {
            int r = tblPhongChieu->rowCount(); tblPhongChieu->insertRow(r);
            tblPhongChieu->setItem(r,0,new QTableWidgetItem(ma));
            tblPhongChieu->setItem(r,1,new QTableWidgetItem(QString::fromStdString(t->data.getLoaiPhong())));
            tblPhongChieu->setItem(r,2,new QTableWidgetItem(QString::number(t->data.getSoGhe())));
            tblPhongChieu->setItem(r,3,new QTableWidgetItem(tt));
            found = true;
        }
    }

    if (!found) {
        QMessageBox::information(this, "Tìm kiếm", "Không tìm thấy phòng phù hợp.");
        refreshPhongChieuTable();
    } else {
        QMessageBox::information(this, "Tìm kiếm", "Đã tìm thấy phòng phù hợp. Chỉ hiển thị kết quả tìm kiếm.");
    }
}

// SUẤT CHIẾU

bool MainWindow::inputXuatChieu(xuatChieu& xc, const QString& title, bool isEdit) {
    bool ok;
    QString ma = isEdit ? QString::fromStdString(xc.maXuatChieu) : "";

    QString maInput = QInputDialog::getText(this, title, "Mã suất chiếu:", QLineEdit::Normal, ma, &ok);
    if(!ok) return false;
    if (!isEdit) {
        if (ds.timXuatChieuTheoMa(maInput.toStdString())) {
            QMessageBox::warning(this, "Lỗi", "Mã suất chiếu đã tồn tại!");
            return false;
        }
    }

    QString maPhim = QInputDialog::getText(this, title, "Mã phim (Phải đang chiếu):", QLineEdit::Normal, QString::fromStdString(xc.maPhim), &ok); if(!ok) return false;
    if (!dc.timKiem(maPhim.toStdString())) {
        QMessageBox::warning(this, "Lỗi", "Mã phim không tồn tại trong danh sách đang chiếu!");
        return false;
    }

    QString maPhong = QInputDialog::getText(this, title, "Mã phòng (Phải tồn tại):", QLineEdit::Normal, QString::fromStdString(xc.maPhong), &ok); if(!ok) return false;
    if (!a.timKiem(maPhong.toStdString())) {
        QMessageBox::warning(this, "Lỗi", "Mã phòng không tồn tại!");
        return false;
    }

    QString ncString = QInputDialog::getText(this, title, "Ngày chiếu (dd/MM/yyyy):", QLineEdit::Normal, QString::fromStdString(xc.ngayChieu), &ok); if(!ok) return false;
    if (!QDate::fromString(ncString, "dd/MM/yyyy").isValid()) {
        QMessageBox::warning(this, "Lỗi định dạng", "Ngày chiếu phải theo định dạng dd/MM/yyyy.");
        return false;
    }

    int gioChieu = QInputDialog::getInt(this, title, "Giờ chiếu (1-24):", xc.gioChieu > 0 ? xc.gioChieu : 12, 1, 24, 1, &ok); if(!ok) return false;
    float giaVe = QInputDialog::getDouble(this, title, "Giá vé:", xc.giaVe > 0 ? xc.giaVe : 80000, 10000, 500000, 0, &ok); if(!ok) return false;

    xc.maXuatChieu = maInput.toStdString();
    xc.maPhim = maPhim.toStdString();
    xc.maPhong = maPhong.toStdString();
    xc.ngayChieu = ncString.toStdString();
    xc.gioChieu = gioChieu;
    xc.giaVe = giaVe;
    return true;
}

void MainWindow::handleAddXuatChieu() {
    xuatChieu xc;
    if (inputXuatChieu(xc, "Thêm suất chiếu")) {
        ds.themXuatChieu(xc);
        refreshAllTables();
        QMessageBox::information(this, "Thành công", "Đã thêm suất chiếu thành công.");
    }
}

void MainWindow::handleEditXuatChieu() {
    int row = tblXuatChieu->currentRow();
    if (row >= 0) {
        string ma = tblXuatChieu->item(row, 0)->text().toStdString();
        xuatChieu* xcPtr = ds.timXuatChieuTheoMa(ma);
        if (xcPtr) {
            if (inputXuatChieu(*xcPtr, "Sửa suất chiếu", true)) {
                QMessageBox::information(this, "Thành công", "Cập nhật suất chiếu thành công!");
                refreshAllTables();
            }
        }
    } else {
        QMessageBox::warning(this, "Lỗi", "Vui lòng chọn một hàng để sửa.");
    }
}

void MainWindow::handleDeleteXuatChieu() {
    int row = tblXuatChieu->currentRow();
    if (row >= 0) {
        if (QMessageBox::question(this, "Xác nhận", "Bạn có chắc chắn muốn xóa suất chiếu này không?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
            ds.xoaXuatChieu(tblXuatChieu->item(row, 0)->text().toStdString());
            refreshAllTables();
        }
    } else {
        QMessageBox::warning(this, "Lỗi", "Vui lòng chọn một hàng để xóa.");
    }
}

void MainWindow::handleTimXuatChieu() {
    bool ok;
    int gio = QInputDialog::getInt(this, "Tìm kiếm suất chiếu", "Nhập Giờ chiếu (1-24):", 12, 1, 24, 1, &ok);
    if (!ok) return;

    tblXuatChieu->setRowCount(0);
    bool found = false;

    for (Node2* t = ds.head; t; t = t->next) {
        if (t->data.getGioChieu() == gio) {
            int r = tblXuatChieu->rowCount(); tblXuatChieu->insertRow(r);
            tblXuatChieu->setItem(r,0,new QTableWidgetItem(QString::fromStdString(t->data.getMaXuatChieu())));
            tblXuatChieu->setItem(r,1,new QTableWidgetItem(QString::fromStdString(t->data.getMaPhim())));
            tblXuatChieu->setItem(r,2,new QTableWidgetItem(QString::fromStdString(t->data.getMaPhong())));
            tblXuatChieu->setItem(r,3,new QTableWidgetItem(QString::fromStdString(t->data.getNgayChieu())));
            tblXuatChieu->setItem(r,4,new QTableWidgetItem(QString::number(t->data.getGioChieu())));
            tblXuatChieu->setItem(r,5,new QTableWidgetItem(QString::number(t->data.getGiaVe())));
            found = true;
        }
    }

    if (!found) {
        QMessageBox::information(this, "Tìm kiếm", "Không tìm thấy suất chiếu vào giờ này.");
        refreshXuatChieuTable();
    } else {
        QMessageBox::information(this, "Tìm kiếm", "Đã tìm thấy suất chiếu phù hợp. Chỉ hiển thị kết quả tìm kiếm.");
    }
}


// VÉ

bool MainWindow::inputVe(ve& v, const QString& title, bool isEdit) {
    bool ok;
    QString ma = isEdit ? QString::fromStdString(v.maVe) : "";

    QString maInput = QInputDialog::getText(this, title, "Mã vé:", QLineEdit::Normal, ma, &ok);
    if(!ok) return false;
    if (!isEdit) {
        if (dsv.timKiem(maInput.toStdString())) {
            QMessageBox::warning(this, "Lỗi", "Mã vé đã tồn tại!");
            return false;
        }
    }

    QString maSC = QInputDialog::getText(this, title, "Mã suất chiếu:", QLineEdit::Normal, QString::fromStdString(v.maSuatChieu), &ok); if(!ok) return false;
    xuatChieu* xc = ds.timXuatChieuTheoMa(maSC.toStdString());
    if (!xc) {
        QMessageBox::warning(this, "Lỗi", "Mã suất chiếu không tồn tại!");
        return false;
    }

    if (!isEdit) {
        v.setTrangThai("Da dat");
    } else {

    }

    v.maVe = maInput.toStdString();
    v.maSuatChieu = maSC.toStdString();
    return true;
}

void MainWindow::handleDatVe() {
    ve v;
    if (inputVe(v, "Đặt vé")) {
        dsv.themVe(v);
        refreshAllTables();
        QMessageBox::information(this, "Đặt vé thành công", "Đã đặt vé thành công! Vui lòng thanh toán.");
    }
}

void MainWindow::handleThanhToanVe() {
    int row = tblVe->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "Lỗi", "Vui lòng chọn một vé để thanh toán.");
        return;
    }
    string maVe = tblVe->item(row, 0)->text().toStdString();
    Node3* n = dsv.timKiem(maVe);

    if (n && n->data.getTrangThai() == "Da thanh toan") {
        QMessageBox::information(this, "Thông báo", "Vé này đã được thanh toán.");
        return;
    }

    if (n) {
        xuatChieu* xc = ds.timXuatChieuTheoMa(n->data.getMaSuatChieu());
        if (!xc) {
            QMessageBox::critical(this, "Lỗi", "Không tìm thấy thông tin suất chiếu!");
            return;
        }

        if (QMessageBox::question(this, "Thanh toán", QString("Xác nhận thanh toán vé %1 với giá %2 VND?")
                                                          .arg(QString::fromStdString(maVe)).arg(xc->getGiaVe()), QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {

            QStringList phuongThuc = {"Tiền mặt", "Thẻ ngân hàng"};
            bool ok;
            QString pt = QInputDialog::getItem(this, "Chọn phương thức", "Phương thức thanh toán:", phuongThuc, 0, false, &ok);
            if(ok) {
                n->data.setTrangThai("Da thanh toan");
                refreshAllTables();
                QMessageBox::information(this, "Thành công", QString("Vé %1 đã thanh toán thành công bằng %2.").arg(QString::fromStdString(maVe)).arg(pt));
            }
        }
    } else {
        QMessageBox::warning(this, "Lỗi", "Không tìm thấy vé.");
    }
}

void MainWindow::handleEditVe() {
    int row = tblVe->currentRow();
    if (row >= 0) {
        string ma = tblVe->item(row, 0)->text().toStdString();
        Node3* n = dsv.timKiem(ma);
        if (n) {
            if (inputVe(n->data, "Sửa vé", true)) {
                QMessageBox::information(this, "Thành công", "Cập nhật vé thành công!");
                refreshAllTables();
            }
        }
    } else {
        QMessageBox::warning(this, "Lỗi", "Vui lòng chọn một hàng để sửa.");
    }
}

void MainWindow::handleDeleteVe() {
    int row = tblVe->currentRow();
    if (row >= 0) {
        if (QMessageBox::question(this, "Xác nhận", "Bạn có chắc chắn muốn xóa vé này không?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
            dsv.xoaVe(tblVe->item(row, 0)->text().toStdString());
            refreshAllTables();
        }
    } else {
        QMessageBox::warning(this, "Lỗi", "Vui lòng chọn một hàng để xóa.");
    }
}

void MainWindow::handleTimVe() {
    bool ok;
    QString ma = QInputDialog::getText(this, "Tìm kiếm vé", "Nhập Mã vé:", QLineEdit::Normal, "", &ok);
    if (!ok || ma.isEmpty()) return;

    tblVe->setRowCount(0);
    bool found = false;

    Node3* t = dsv.timKiem(ma.toStdString());

    if (t) {
        xuatChieu* xc = ds.timXuatChieuTheoMa(t->data.getMaSuatChieu());
        int r = tblVe->rowCount(); tblVe->insertRow(r);
        tblVe->setItem(r,0,new QTableWidgetItem(QString::fromStdString(t->data.getMaVe())));
        tblVe->setItem(r,1,new QTableWidgetItem(QString::fromStdString(t->data.getMaSuatChieu())));
        if (xc) {
            tblVe->setItem(r,2,new QTableWidgetItem(QString::fromStdString(xc->getMaPhim())));
            tblVe->setItem(r,3,new QTableWidgetItem(QString::fromStdString(xc->getMaPhong())));
            tblVe->setItem(r,4,new QTableWidgetItem(QString::fromStdString(xc->getNgayChieu())));
            tblVe->setItem(r,5,new QTableWidgetItem(QString::number(xc->getGioChieu())));
            tblVe->setItem(r,6,new QTableWidgetItem(QString::number(xc->getGiaVe())));
        }
        tblVe->setItem(r,7,new QTableWidgetItem(QString::fromStdString(t->data.getTrangThai())));
        found = true;
    }

    if (!found) {
        QMessageBox::information(this, "Tìm kiếm", "Không tìm thấy vé có mã: " + ma);
        refreshVeTable();
    } else {
        QMessageBox::information(this, "Tìm kiếm", "Đã tìm thấy vé phù hợp. Chỉ hiển thị kết quả tìm kiếm.");
    }
}

// DOANH THU

void MainWindow::handleTinhDoanhThuNgay() {
    bool ok;

    QString dateString = QInputDialog::getText(this, "Doanh thu theo ngày", "Nhập ngày (dd/MM/yyyy):", QLineEdit::Normal, QDate::currentDate().toString("dd/MM/yyyy"), &ok);
    if (!ok || dateString.isEmpty()) return;
    QDate date = QDate::fromString(dateString, "dd/MM/yyyy");
    if (!date.isValid()) {
        QMessageBox::warning(this, "Lỗi", "Ngày không hợp lệ. Vui lòng nhập theo định dạng dd/MM/yyyy.");
        return;
    }
    string ngay = dateString.toStdString();

    float tongDoanhThu = 0;
    int soVe = 0;

    QTableWidget* tbl = (QTableWidget*)stack->widget(5)->findChild<QTableWidget*>();
    if (!tbl) return;

    tbl->setRowCount(0);

    for(Node3* temp = dsv.head; temp; temp = temp->next) {
        if(temp->data.getTrangThai() == "Da thanh toan") {
            xuatChieu* xc = ds.timXuatChieuTheoMa(temp->data.getMaSuatChieu());

            if(xc && xc->getNgayChieu() == ngay) {
                tongDoanhThu += xc->getGiaVe();
                soVe++;
                int r = tbl->rowCount(); tbl->insertRow(r);
                tbl->setItem(r,0,new QTableWidgetItem(QString::fromStdString(temp->data.getMaVe())));
                tbl->setItem(r,1,new QTableWidgetItem(QString::fromStdString(temp->data.getMaSuatChieu())));
                tbl->setItem(r,2,new QTableWidgetItem(QString::fromStdString(xc->getNgayChieu())));
                tbl->setItem(r,3,new QTableWidgetItem(QString::number(xc->getGiaVe())));
            }
        }
    }

    lblTongDoanhThu->setText(QString("Doanh thu ngày %1: %2 VND (%3 vé)")
                                 .arg(QString::fromStdString(ngay))
                                 .arg(QString::number(tongDoanhThu, 'f', 0))
                                 .arg(soVe));
}

void MainWindow::handleTinhDoanhThuThang() {
    bool ok;
    int thang = QInputDialog::getInt(this, "Doanh thu theo tháng", "Nhập tháng:", QDate::currentDate().month(), 1, 12, 1, &ok);
    if (!ok) return;
    int nam = QInputDialog::getInt(this, "Doanh thu theo tháng", "Nhập năm:", QDate::currentDate().year(), 2000, 2100, 1, &ok);
    if (!ok) return;

    string sThang = QString::number(thang).rightJustified(2, '0').toStdString();
    string sNam = QString::number(nam).toStdString();
    float tongDoanhThu = 0;
    int soVe = 0;

    QTableWidget* tbl = (QTableWidget*)stack->widget(5)->findChild<QTableWidget*>();
    if (!tbl) return;

    tbl->setRowCount(0);

    for (Node3* temp = dsv.head; temp; temp = temp->next) {
        if (temp->data.getTrangThai() == "Da thanh toan") {
            xuatChieu* xc = ds.timXuatChieuTheoMa(temp->data.getMaSuatChieu());
            if (xc) {
                string ngayChieu = xc->getNgayChieu();
                if (ngayChieu.length() >= 10) {
                    string thangChieu = ngayChieu.substr(3, 2);
                    string namChieu = ngayChieu.substr(6, 4);
                    if (thangChieu == sThang && namChieu == sNam) {
                        tongDoanhThu += xc->getGiaVe();
                        soVe++;
                        int r = tbl->rowCount(); tbl->insertRow(r);
                        tbl->setItem(r,0,new QTableWidgetItem(QString::fromStdString(temp->data.getMaVe())));
                        tbl->setItem(r,1,new QTableWidgetItem(QString::fromStdString(temp->data.getMaSuatChieu())));
                        tbl->setItem(r,2,new QTableWidgetItem(QString::fromStdString(xc->getNgayChieu())));
                        tbl->setItem(r,3,new QTableWidgetItem(QString::number(xc->getGiaVe())));
                    }
                }
            }
        }
    }

    lblTongDoanhThu->setText(QString("Doanh thu Tháng %1 Năm %2: %3 VND (%4 vé)")
                                 .arg(thang).arg(nam)
                                 .arg(QString::number(tongDoanhThu, 'f', 0))
                                 .arg(soVe));
}

// REFRESH TABLES

void MainWindow::refreshAllTables() {
    refreshPhimTables();
    refreshPhongChieuTable();
    refreshXuatChieuTable();
    refreshVeTable();
}

void MainWindow::refreshPhimTables() {
    tblSapChieu->setRowCount(0);
    for (Node* t = sc.head; t; t = t->next) {
        int r = tblSapChieu->rowCount(); tblSapChieu->insertRow(r);
        tblSapChieu->setItem(r,0,new QTableWidgetItem(QString::fromStdString(t->data.maPhim)));
        tblSapChieu->setItem(r,1,new QTableWidgetItem(QString::fromStdString(t->data.tenPhim)));
        tblSapChieu->setItem(r,2,new QTableWidgetItem(QString::fromStdString(t->data.daoDien)));
        tblSapChieu->setItem(r,3,new QTableWidgetItem(QString::fromStdString(t->data.theLoai)));
        tblSapChieu->setItem(r,4,new QTableWidgetItem(QString::number(t->data.thoiLuong)));
        tblSapChieu->setItem(r,5,new QTableWidgetItem(QString::fromStdString(t->data.khoiChieu)));
    }

    tblDangChieu->setRowCount(0);
    for (Node* t = dc.head; t; t = t->next) {
        int r = tblDangChieu->rowCount(); tblDangChieu->insertRow(r);
        tblDangChieu->setItem(r,0,new QTableWidgetItem(QString::fromStdString(t->data.maPhim)));
        tblDangChieu->setItem(r,1,new QTableWidgetItem(QString::fromStdString(t->data.tenPhim)));
        tblDangChieu->setItem(r,2,new QTableWidgetItem(QString::fromStdString(t->data.daoDien)));
        tblDangChieu->setItem(r,3,new QTableWidgetItem(QString::fromStdString(t->data.theLoai)));
        tblDangChieu->setItem(r,4,new QTableWidgetItem(QString::number(t->data.thoiLuong)));
        tblDangChieu->setItem(r,5,new QTableWidgetItem(QString::fromStdString(t->data.khoiChieu)));
    }
}

void MainWindow::refreshPhongChieuTable() {
    tblPhongChieu->setRowCount(0);
    for (Node1* t = a.head; t; t = t->next) {
        int r = tblPhongChieu->rowCount(); tblPhongChieu->insertRow(r);
        tblPhongChieu->setItem(r,0,new QTableWidgetItem(QString::fromStdString(t->data.getMaPhong())));
        tblPhongChieu->setItem(r,1,new QTableWidgetItem(QString::fromStdString(t->data.getLoaiPhong())));
        tblPhongChieu->setItem(r,2,new QTableWidgetItem(QString::number(t->data.getSoGhe())));
        tblPhongChieu->setItem(r,3,new QTableWidgetItem(QString::fromStdString(t->data.getTinhTrang())));
    }
}

void MainWindow::refreshXuatChieuTable() {
    tblXuatChieu->setRowCount(0);
    for (Node2* t = ds.head; t; t = t->next) {
        int r = tblXuatChieu->rowCount(); tblXuatChieu->insertRow(r);
        tblXuatChieu->setItem(r,0,new QTableWidgetItem(QString::fromStdString(t->data.getMaXuatChieu())));
        tblXuatChieu->setItem(r,1,new QTableWidgetItem(QString::fromStdString(t->data.getMaPhim())));
        tblXuatChieu->setItem(r,2,new QTableWidgetItem(QString::fromStdString(t->data.getMaPhong())));
        tblXuatChieu->setItem(r,3,new QTableWidgetItem(QString::fromStdString(t->data.getNgayChieu())));
        tblXuatChieu->setItem(r,4,new QTableWidgetItem(QString::number(t->data.getGioChieu())));
        tblXuatChieu->setItem(r,5,new QTableWidgetItem(QString::number(t->data.getGiaVe())));
    }
}

void MainWindow::refreshVeTable() {
    tblVe->setRowCount(0);
    for (Node3* t = dsv.head; t; t = t->next) {
        int r = tblVe->rowCount(); tblVe->insertRow(r);
        xuatChieu* xc = ds.timXuatChieuTheoMa(t->data.getMaSuatChieu());

        tblVe->setItem(r,0,new QTableWidgetItem(QString::fromStdString(t->data.getMaVe())));
        tblVe->setItem(r,1,new QTableWidgetItem(QString::fromStdString(t->data.getMaSuatChieu())));

        if (xc) {
            tblVe->setItem(r,2,new QTableWidgetItem(QString::fromStdString(xc->getMaPhim())));
            tblVe->setItem(r,3,new QTableWidgetItem(QString::fromStdString(xc->getMaPhong())));
            tblVe->setItem(r,4,new QTableWidgetItem(QString::fromStdString(xc->getNgayChieu())));
            tblVe->setItem(r,5,new QTableWidgetItem(QString::number(xc->getGioChieu())));
            tblVe->setItem(r,6,new QTableWidgetItem(QString::number(xc->getGiaVe())));
        } else {
            tblVe->setItem(r,2,new QTableWidgetItem("N/A"));
            tblVe->setItem(r,3,new QTableWidgetItem("N/A"));
            tblVe->setItem(r,4,new QTableWidgetItem("N/A"));
            tblVe->setItem(r,5,new QTableWidgetItem("N/A"));
            tblVe->setItem(r,6,new QTableWidgetItem("N/A"));
        }

        QString trangThai = QString::fromStdString(t->data.getTrangThai());
        QTableWidgetItem* ttItem = new QTableWidgetItem(trangThai);
        if (trangThai == "Da thanh toan") {
            ttItem->setForeground(QBrush(Qt::darkGreen));
        } else {
            ttItem->setForeground(QBrush(Qt::darkRed));
        }
        tblVe->setItem(r,7,ttItem);
    }
}


MainWindow::~MainWindow() = default;
