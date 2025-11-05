#include<iostream>
#include "danhSachPhim.h"
using namespace std;
danhSachPhim::danhSachPhim(){
    maPhim="";
    tenPhim="";
    daoDien="";
    theLoai="";
    thoiLuong=0;
    khoiChieu="";
    ngonNgu="";}
    string danhSachPhim::getMaPhim(){
        return maPhim;
    }
    string danhSachPhim::getTenPhim(){
        return tenPhim;
    }
    string danhSachPhim::getDaoDien(){
        return daoDien;
    }
    string danhSachPhim::getTheLoai(){
        return theLoai;
    }
    int danhSachPhim::getThoiLuong(){
        return thoiLuong;
    }
    string danhSachPhim::getKhoiChieu(){
        return khoiChieu;
    }
    string danhSachPhim::getNgonNgu(){
        return ngonNgu;
    }
    
    void danhSachPhim::setMaPhim(const string &ma){
        maPhim=ma;
    }
    void danhSachPhim::setTenPhim(const string &ten){
        tenPhim=ten;
    }
    void danhSachPhim::setDaoDien(const string &daodien){
        daoDien=daodien;
    }
    void danhSachPhim::setTheLoai(const string &tl){
        theLoai=tl;
    }
    void danhSachPhim::setThoiLuong(int thoiluong){
        thoiLuong=thoiluong;
    }
    void danhSachPhim::setKhoiChieu(const string &khoichieu){
        khoiChieu=khoichieu;
    }
    void danhSachPhim::setNgonNgu(const string &ngonngu){
        ngonNgu=ngonngu;
    }
    void danhSachPhim::themPhim(){
        cin.ignore();
        cout<<"Nhập mã phim: ";
        getline(cin,maPhim);
        cout<<"Nhập tên phim: ";
        getline(cin,tenPhim);
        cout<<"Nhập đạo diễn: ";
        getline(cin,daoDien);
        cout<<"Nhập thể loại: ";
        getline(cin,theLoai);
        cout<<"Nhập thời lượng: ";
        cin >> thoiLuong;
        cin.ignore();
        cout<<"Nhập khởi chiếu: ";
        getline(cin,khoiChieu);
        cout<<"Nhập ngôn ngữ: ";
        getline(cin,ngonNgu);
        cout<<"\nNhấn enter để tiếp tục....";
        cin.get();
    }
    void danhSachPhim::xoaPhim(){
        
    }
    void danhSachPhim::timKiem(){
        
    }
    void danhSachPhim::xuatPhim(){
        
    }
