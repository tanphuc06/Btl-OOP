// data_model.h
#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// ======================= 1. PHIM =======================

class danhSachPhim {
public:
    string maPhim, tenPhim, daoDien, theLoai, khoiChieu;
    int thoiLuong = 0;
    string getMaPhim() const { return maPhim; }
    string getTenPhim() const { return tenPhim; }
    void setMaPhim(const string& s) { maPhim = s; }
    void setTenPhim(const string& s) { tenPhim = s; }
    void setDaoDien(const string& s) { daoDien = s; }
    void setTheLoai(const string& s) { theLoai = s; }
    void setThoiLuong(int n) { thoiLuong = n; }
    void setKhoiChieu(const string& s) { khoiChieu = s; }
};
struct Node { danhSachPhim data; Node* next; Node(const danhSachPhim& p) : data(p), next(nullptr) {} };
class danhSachPhimList {
public:
    Node* head = nullptr;
    ~danhSachPhimList() { while(head) { Node* t = head; head = head->next; delete t; } }
    void themPhimTuDanhSachKhac(const danhSachPhim& p) {
        if (timKiem(p.getMaPhim())) return;
        Node* n = new Node(p);
        if (!head) head = n;
        else { Node* t = head; while(t->next) t = t->next; t->next = n; }
    }
    void xoaPhim(const string& ma) {
        if (!head) return;
        if (head->data.getMaPhim() == ma) { Node* t = head; head = head->next; delete t; return; }
        Node* prev = head;
        Node* cur = head->next;
        while (cur && cur->data.getMaPhim() != ma) { prev = cur; cur = cur->next; }
        if (cur) { prev->next = cur->next; delete cur; }
    }
    Node* timKiem(const string& ma) {
        Node* t = head;
        while (t && t->data.getMaPhim() != ma) t = t->next;
        return t;
    }
};

// ======================= 2. PHÒNG CHIẾU =======================

class phongChieu {
public:
    string maPhong;
    string loaiPhong;
    int soGhe = 0;
    string tinhTrang;

    string getMaPhong() const { return maPhong; }
    string getLoaiPhong() const { return loaiPhong; }
    int getSoGhe() const { return soGhe; }
    string getTinhTrang() const { return tinhTrang; }

    void setMaPhong(const string &ma){ maPhong=ma; }
    void setLoaiPhong(const string &lp){ loaiPhong=lp; }
    void setSoGhe(const int &sg){ soGhe=sg; }
    void setTinhTrang(const string&tt){ tinhTrang=tt; }
};
struct Node1 { phongChieu data; Node1* next; Node1(const phongChieu &p): data(p), next(nullptr) {} };
class danhSachPhongChieu {
public:
    Node1* head = nullptr;
    ~danhSachPhongChieu() { while(head) { Node1* t = head; head = head->next; delete t; } }
    void themPhong(const phongChieu &p) {
        if (timKiem(p.getMaPhong())) return;
        Node1* newNode = new Node1(p);
        if (!head) head = newNode;
        else { Node1* temp = head; while (temp->next) temp = temp->next; temp->next = newNode; }
    }
    void xoaPhong(const string &maPhong) {
        if (!head) return;
        if (head->data.getMaPhong() == maPhong) { Node1* temp = head; head = head->next; delete temp; return; }
        Node1* prev = head; Node1* curr = head->next;
        while (curr && curr->data.getMaPhong() != maPhong) { prev = curr; curr = curr->next; }
        if (curr) { prev->next = curr->next; delete curr; }
    }
    Node1* timKiem(const string &maPhong) {
        Node1* temp = head;
        while (temp && temp->data.getMaPhong() != maPhong) temp = temp->next;
        return temp;
    }
};

// ======================= 3. SUẤT CHIẾU =======================

class xuatChieu {
public:
    string maXuatChieu;
    string maPhim;
    string maPhong;
    string ngayChieu;
    int gioChieu = 0;
    float giaVe = 0;

    string getMaXuatChieu() const { return maXuatChieu;}
    string getMaPhim() const { return maPhim;}
    string getMaPhong() const { return maPhong;}
    string getNgayChieu() const { return ngayChieu;}
    int getGioChieu() const { return gioChieu;}
    float getGiaVe() const { return giaVe;}

    void setMaXuatChieu(const string &xuatChieu){ maXuatChieu=xuatChieu;}
    void setMaPhim(const string &phim){ maPhim=phim;}
    void setMaPhong(const string &phong){ maPhong=phong;}
    void setNgayChieu(const string &ngaychieu){ ngayChieu=ngaychieu;}
    void setGioChieu(const int &giochieu){ gioChieu=giochieu;}
    void setGiaVe(const float &giave){ giaVe=giave;}
};
struct Node2 { xuatChieu data; Node2* next; Node2(const xuatChieu &p): data(p), next(nullptr) {} };
class danhSachXuatChieu {
public:
    Node2* head = nullptr;
    ~danhSachXuatChieu(){ while(head) { Node2* temp = head; head = head->next; delete temp; } }

    void themXuatChieu(const xuatChieu &p) {
        if (timXuatChieuTheoMa(p.getMaXuatChieu())) return;
        Node2* newNode = new Node2(p);
        if (!head) head = newNode;
        else { Node2* temp = head; while (temp->next) temp = temp->next; temp->next = newNode; }
    }
    void xoaXuatChieu(const string &maXuatChieu) {
        if (!head) return;
        if (head->data.getMaXuatChieu() == maXuatChieu) { Node2* temp = head; head = head->next; delete temp; return; }
        Node2* prev = head; Node2* curr = head->next;
        while (curr && curr->data.getMaXuatChieu() != maXuatChieu) { prev = curr; curr = curr->next; }
        if (curr) { prev->next = curr->next; delete curr; }
    }
    xuatChieu* timXuatChieuTheoMa(const string &ma) const {
        Node2 *temp = head;
        while (temp) {
            if (temp->data.getMaXuatChieu() == ma)
                return &(temp->data);
            temp = temp->next;
        }
        return nullptr;
    }
};

// ======================= 4. VÉ & DOANH THU =======================

class ve {
public:
    string maVe;
    string maSuatChieu;
    string trangThai; // "Da dat" hoặc "Da thanh toan"

    string getMaVe() const {return maVe;}
    string getMaSuatChieu() const {return maSuatChieu;}
    string getTrangThai() const {return trangThai;}

    void setMaVe(const string &mave) { maVe=mave; }
    void setMaSuatChieu(const string &masuatchieu) { maSuatChieu=masuatchieu;}
    void setTrangThai(const string &tt) { trangThai=tt;}
};
struct Node3 { ve data; Node3* next; Node3(const ve &p): data(p), next(nullptr) {} };
class danhSachVe {
public:
    Node3* head = nullptr;
    ~danhSachVe(){ while(head) { Node3* temp = head; head = head->next; delete temp; } }

    void themVe(const ve &v) {
        if (timKiem(v.getMaVe())) return;
        Node3* newNode = new Node3(v);
        if (!head) head = newNode;
        else { Node3* temp = head; while (temp->next) temp = temp->next; temp->next = newNode; }
    }
    void xoaVe(const string &maVe){
        if(!head) return;
        if(head->data.getMaVe() == maVe){
            Node3*temp=head; head=head->next; delete temp; return;
        }
        Node3* prev= head; Node3* curr=head->next;
        while(curr && curr->data.getMaVe()!=maVe){ prev = curr; curr=curr->next; }
        if(curr){ prev->next=curr->next; delete curr; }
    }
    Node3* timKiem(const string &maVe) const {
        Node3 *temp = head;
        while (temp) {
            if (temp->data.getMaVe() == maVe)
                return temp;
            temp = temp->next;
        }
        return nullptr;
    }
};
