#pragma once
#include<string>
using namespace std;
class danhSachPhim{
    private:
    string maPhim;
    string tenPhim;
    string daoDien;
    string theLoai;
    int thoiLuong;
    string khoiChieu;
    string ngonNgu;
    public:
    danhSachPhim();
    
    string getMaPhim();
    string getTenPhim();
    string getDaoDien();
    string getTheLoai();
    int getThoiLuong();
    string getKhoiChieu();
    string getNgonNgu();
    
    void setMaPhim(const string &ma);
    void setTenPhim(const string &ten);
    void setDaoDien(const string &daodien);
    void setTheLoai(const string &tl);
    void setThoiLuong(int thoiluong);
    void setKhoiChieu(const string &khoichieu);
    void setNgonNgu(const string &ngongu);
    void themPhim();
    void xoaPhim();
    void timKiem();
    void xuatPhim();
};
