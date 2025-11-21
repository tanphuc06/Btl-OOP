#include<iostream>
#include <string>
#include <iomanip>
using namespace std;
class danhSachPhim {
private:
    string maPhim;
    string tenPhim;
    string daoDien;
    string theLoai;
    int thoiLuong;
    string khoiChieu;

public:
    danhSachPhim() : thoiLuong(0) {}

 
    string getMaPhim() const { return maPhim; }
    string getTenPhim() const { return tenPhim; }
    string getDaoDien() const { return daoDien; }
    string getTheLoai() const { return theLoai; }
    int getThoiLuong() const { return thoiLuong; }
    string getKhoiChieu() const { return khoiChieu; }
 
    void setMaPhim(const string &ma) { maPhim = ma; }
    void setTenPhim(const string &ten) { tenPhim = ten; }
    void setDaoDien(const string &dd) { daoDien = dd; }
    void setTheLoai(const string &tl) { theLoai = tl; }
    void setThoiLuong(int tl) { thoiLuong = tl; }
    void setKhoiChieu(const string &kc) { khoiChieu = kc; }
    
    void nhapPhim() {
        cout << "Nhập mã phim: "; getline(cin, maPhim);
        cout << "Nhập tên phim: "; getline(cin, tenPhim);
        cout << "Nhập đạo diễn: "; getline(cin, daoDien);
        cout << "Nhập thể loại: "; getline(cin, theLoai);
        cout << "Nhập thời lượng (phút): "; cin >> thoiLuong;
        cin.ignore();
        cout << "Nhập ngày khởi chiếu: "; getline(cin, khoiChieu);
  
    }

    void xuatPhim() const {
        cout << left
             << setw(9) << maPhim
             << setw(17) << tenPhim
             << setw(18) << daoDien
             << setw(13) << theLoai
             << setw(10) << thoiLuong
             << setw(10) << khoiChieu
           
             << endl;
    }

    static void inTieuDe() {
        cout << left
             << setw(10) << "Mã phim"
             << setw(18) << "Tên phim"
             << setw(18) << "Đạo diễn"
             << setw(15) << "Thể loại"
             << setw(15) << "Thời lượng"
             << setw(10) << "   Khởi chiếu"
            
             << endl;

    }
};

struct Node {
    danhSachPhim data;
    Node* next;
    Node(const danhSachPhim &p){
        data=p;
        next=NULL;
    }
};


class danhSachPhimList {
private:
    Node* head;

public:
    danhSachPhimList() {
        head=NULL;}
    ~danhSachPhimList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }


    void themPhim() {
        danhSachPhim p;
        cin.ignore();
        p.nhapPhim();

        Node* newNode = new Node(p);
        if (head==NULL) {
            head = newNode;
        }
        else {
            Node* temp = head;
            while (temp->next!=NULL) {
                temp = temp->next;}
            temp->next = newNode;
        }
        cout << "Đã thêm phim vào danh sách!\n";
    }

    void xoaPhim(const string &maPhim) {
        if (head==NULL) {
            cout<<"Danh sách phòng trống!\n";
        return;}

        if (head->data.getMaPhim() == maPhim) {
            Node* temp = head;
            head = head->next;
            delete temp;
            cout << "Đã xóa phim có mã: " << maPhim << endl;
            return;
        }

       Node* prev = head;        
       Node* curr = head->next;    
       while (curr != NULL && curr->data.getMaPhim() != maPhim) {
        prev = curr;            
        curr = curr->next;      
    }

    if (curr != NULL) {
        prev->next = curr->next; 
        delete curr;             
        cout << "Đã xóa phim có mã: " << maPhim << endl;
    } 
    else {
        cout << "Không tìm thấy phim có mã " << maPhim << endl;
    }
}

    Node* timKiem(const string &maPhim) {
        Node* temp = head;
        while (temp !=NULL) {
            if (temp->data.getMaPhim() == maPhim)
                return temp;
            temp = temp->next;
        }
        return NULL;
    }

    void xuatDanhSach() const {
        if (head==NULL) {
            cout << "Danh sách phim rỗng!\n";
            return;
        }
        danhSachPhim::inTieuDe();
        Node* temp = head;
        while (temp) {
            temp->data.xuatPhim();
            temp = temp->next;
        }
    }
    void themPhimTuDanhSachKhac(const danhSachPhim &p) {
    Node* newNode = new Node(p);
    if (head == NULL) {
        head = newNode;
    } else {
        Node* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    cout << "Đã thêm phim vào danh sách!\n";
}
void suaPhim(const string &maPhim) {
    if (head == NULL) {
        cout << "Danh sách phòng rỗng!\n";
        return;
    }
    Node* temp = head;
    while (temp) {
        if (temp->data.getMaPhim() == maPhim) {
            cout << "Đã tìm thấy phim. Nhập thông tin mới:\n";
            temp->data.nhapPhim();
            temp->data.setMaPhim(maPhim);
            cout << "Đã cập nhật thông tin phim thành công!\n";
            return;
        }
        temp = temp->next;
    }

    cout << "Không tìm thấy phim có mã: " << maPhim << endl;
}
};
danhSachPhimList sc; 
danhSachPhimList dc;

    void chuyenPhim(const string &maPhim){
        Node* nodeTim = sc.timKiem(maPhim); 
    if (nodeTim != NULL) {
        dc.themPhimTuDanhSachKhac(nodeTim->data);
        sc.xoaPhim(maPhim);

        cout << "Đã chuyển phim " << nodeTim->data.getTenPhim() << " sang danh sách đang chiếu.\n";
    } else {
        cout << "Không tìm thấy phim có mã " << maPhim << " trong danh sách sắp chiếu.\n";
    }
    }
class phongChieu{
    private:
    string maPhong;
    string loaiPhong;
    int soGhe;
    string tinhTrang;
    public:
    phongChieu(){
        soGhe=0;
    }
    
    string getMaPhong() const { return maPhong; }
    string getLoaiPhong() const { return loaiPhong; }
    int getSoGhe() const { return soGhe; }
    string getTinhTrang() const { return tinhTrang; }
    
    void setMaPhong(const string &ma){ maPhong=ma; }
    void setLoaiPhong(const string &lp){ loaiPhong=lp; }
    void setSoGhe(const int &sg){ soGhe=sg; }
    void setTinhTrang(const string&tt){ tinhTrang=tt; }
    
    void nhapPhong(){
        cout<<"Nhập mã phòng: ";
        getline(cin, maPhong);
        cout<<"Nhập loại phòng: ";
        getline(cin, loaiPhong);
        cout<<"Nhập số ghế: ";
        cin>>soGhe;
        cin.ignore();
        cout<<"Nhập tình trạng: ";
        getline(cin, tinhTrang);
    }
    void hienThiPhong() const {
        cout << left
             << setw(15) << maPhong
             << setw(15) << loaiPhong
             << setw(13) << soGhe
             << setw(13) << tinhTrang
             << endl;
    }

    static void inTieuDe() {
        cout << left
             << setw(15) << "Mã phòng"
             << setw(18) << "Loại phòng"
             << setw(18) << "Số ghế"
             << setw(15) << "Tình trạng"
             << endl;

    }
};
struct Node1 {
    phongChieu data;
    Node1* next;
    Node1(const phongChieu &p){
        data=p;
        next=NULL;
    }
};
class danhSachPhongChieu{
  private:
  Node1*head;
  public:
   danhSachPhongChieu() {
        head=NULL;}
    ~danhSachPhongChieu() {
        while (head) {
            Node1* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void themPhong(){
        phongChieu p;
        p.nhapPhong();
        Node1* temp = head;
        while(temp) {
        if(temp->data.getMaPhong() == p.getMaPhong()) {
            cout << "Mã phòng này đã tồn tại! Không thể thêm.\n";
            return; 
        }
        temp = temp->next;
    }

        Node1* newNode = new Node1(p);
        if (head==NULL) {
            head = newNode;
        }
        else {
            Node1* temp = head;
            while (temp->next!=NULL) {
                temp = temp->next;}
            temp->next = newNode;
        }
        cout << "Đã thêm phòng vào danh sách!\n";
    }
    
    void xoaPhong(const string &maPhong) {
        if (head==NULL) {
            cout<<"Danh sách phòng trống!\n";
        return;}

        if (head->data.getMaPhong() == maPhong) {
            Node1* temp = head;
            head = head->next;
            delete temp;
            cout << "Đã xóa phòng có mã: " << maPhong << endl;
            return;
        }

       Node1* prev = head;        
       Node1* curr = head->next;    
       while (curr != NULL && curr->data.getMaPhong() != maPhong) {
        prev = curr;            
        curr = curr->next;      
    }

    if (curr != NULL) {
        prev->next = curr->next; 
        delete curr;             
        cout << "Đã xóa phòng có mã: " << maPhong << endl;
    } 
    else {
        cout << "Không tìm thấy phòng có mã " << maPhong << endl;
    }
}
void xuatDanhSach() const {
        if (head==NULL) {
            cout << "Danh sách phòng rỗng!\n";
            return;
        }
        phongChieu::inTieuDe();
        Node1* temp = head;
        while (temp) {
            temp->data.hienThiPhong();
            temp = temp->next;
        }
    }
    
    void timPhong(const string &tinhTrang){
        Node1* temp = head;
        bool timThay = false;
        phongChieu::inTieuDe();
        while (temp !=NULL) {
            if (temp->data.getTinhTrang() == tinhTrang ){
                temp->data.hienThiPhong();
                timThay= true;}
            temp = temp->next;
        }
        if (timThay==false){
        cout << "Không có phòng nào có trạng thái \"" << tinhTrang << "\"!\n";
    }
    }
     Node1* timKiem(const string &maPhong) {
        Node1* temp = head;
        while (temp !=NULL) {
            if (temp->data.getMaPhong() == maPhong)
                return temp;
            temp = temp->next;
        }
        return NULL;
    }
    void suaPhong(const string &maPhong) {
    if (head == NULL) {
        cout << "Danh sách phòng rỗng!\n";
        return;
    }

    Node1* temp = head;
    while (temp) {
        if (temp->data.getMaPhong() == maPhong) {
            cout << "Đã tìm thấy phòng. Nhập thông tin mới:\n";
            temp->data.nhapPhong();
            temp->data.setMaPhong(maPhong);
            cout << "Đã cập nhật thông tin phòng thành công!\n";
            return;
        }
        temp = temp->next;
    }

    cout << "Không tìm thấy phòng có mã: " << maPhong << endl;
}

};
danhSachPhongChieu a;
class suatChieu{
  private:
  string maSuatChieu;
  string maPhim;
  string maPhong;
  string ngayChieu;
  int gioChieu;
  float giaVe;
  public:
  suatChieu(){
      giaVe=0;
  }
  string getMaSuatChieu() const { return maSuatChieu;}
  string getMaPhim() const { return maPhim;}
  string getMaPhong() const { return maPhong;}
  string getNgayChieu() const { return ngayChieu;}
  int getGioChieu() const { return gioChieu;}
  float getGiaVe() const { return giaVe;}
  
  void setMaSuatChieu(const string &suatChieu){ maSuatChieu=suatChieu;}
  void setMaPhim(const string &phim){ maPhim=phim;}
  void setMaPhong(const string &phong){ maPhong=phong;}
  void setNgayChieu(const string &ngaychieu){ ngayChieu=ngaychieu;}
  void setGioChieu(const int &giochieu){ gioChieu=giochieu;}
  void setGiaVe(const float &giave){ giaVe=giave;}
  
  void nhap(){
      cout<<"Nhập mã suất chiếu: "; getline(cin,maSuatChieu);
      cout<<"Nhập mã phim: "; getline(cin,maPhim);
      cout<<"Nhập mã phòng: "; getline(cin,maPhong);
      cout<<"Nhập ngày chiếu: "; getline(cin,ngayChieu);
      do{
      cout<<"Nhập giờ chiếu(0-24): ";
      cin>>gioChieu;}while(gioChieu<=0 || gioChieu >=25);
      cout<<"Nhập giá vé: ";
      cin>>giaVe;
  }
  
  void hienThi() const {
        cout << left
             << setw(15) << maSuatChieu
             << setw(10) << maPhim
             << setw(8) << maPhong
             << setw(10) << ngayChieu
             << setw(10) << gioChieu
             << setw(10) << giaVe
             << endl;
    }

    static void inTieuDe() {
        cout << left
             << setw(20) << "Mã suất chiếu"
             << setw(10) << "Mã phim"
             << setw(14) << "Mã phòng"
             << setw(15) << "Ngày chiếu"
             << setw(18) << "Giờ chiếu"
             << setw(15) << "Giá vé"
             << endl;

    }
};
struct Node2 {
    suatChieu data;
    Node2* next;
    Node2(const suatChieu &p){
        data=p;
        next=NULL;
    }
};
class danhSachSuatChieu{
    private:
    Node2*head;
    public:
    danhSachSuatChieu(){
        head=NULL;}
    ~danhSachSuatChieu(){
        while(head != NULL){
            Node2* temp= head;
            head= head->next;
            delete temp;
        }
    }
    void themSuatChieu(danhSachPhimList &dsPhimDangChieu, danhSachPhongChieu &dsPhong) {
    suatChieu p;
    p.nhap();
    if (dsPhong.timKiem(p.getMaPhong()) == NULL) {
        cout << "Mã phòng không tồn tại! Không thể thêm suất chiếu.\n";
        return;
    }
    if (dsPhimDangChieu.timKiem(p.getMaPhim()) == NULL) {
        cout << "Mã phim không tồn tại trong danh sách đang chiếu!\n";
        cout << "Hãy chuyển phim sang danh sách đang chiếu trước.\n";
        return;
    }
    Node2* temp = head;
    while (temp != NULL) {
        if (temp->data.getMaSuatChieu() == p.getMaSuatChieu()) {
            cout << "Mã suất chiếu đã tồn tại!\n";
            return;
        }
        temp = temp->next;
    }
    Node2* newNode = new Node2(p);

    if (head == NULL)
        head = newNode;
    else {
        temp = head;
        while (temp->next != NULL) temp = temp->next;
        temp->next = newNode;
    }

    cout << "Thêm suất chiếu thành công!\n";
}

    void xoaSuatChieu(const string &maSuatChieu) {
        if (head==NULL) {
            cout<<"Danh sách phòng trống!\n";
        return;}

        if (head->data.getMaSuatChieu() == maSuatChieu) {
            Node2* temp = head;
            head = head->next;
            delete temp;
            cout << "Đã xóa suất chiếu có mã: " << maSuatChieu << endl;
            return;
        }

       Node2* prev = head;        
       Node2* curr = head->next;    
       while (curr != NULL && curr->data.getMaSuatChieu() != maSuatChieu) {
        prev = curr;            
        curr = curr->next;      
    }

    if (curr != NULL) {
        prev->next = curr->next; 
        delete curr;             
        cout << "Đã xóa suất chiếu có mã: " << maSuatChieu << endl;
    } 
    else {
        cout << "Không tìm thấy suất chiếu có mã " << maSuatChieu << endl;
    }
}
    void xuatDanhSach() const {
        if (head==NULL) {
            cout << "Danh sách phòng rỗng!\n";
            return;
        }
        suatChieu::inTieuDe();
        Node2* temp = head;
        while (temp) {
            temp->data.hienThi();
            temp = temp->next;
        }
    }
    void suaSuatChieu(const string &ma, danhSachPhimList &dsPhim, danhSachPhongChieu &dsPhong) {
    Node2* temp = head;
    while (temp) {
        if (temp->data.getMaSuatChieu() == ma) {
            cout << "Nhập thông tin mới:\n";
            suatChieu p;
            p.nhap();
            if (dsPhong.timKiem(p.getMaPhong()) == NULL) {
                cout << "Mã phòng không tồn tại! Không cập nhật.\n";
                return;
            }
            if (dsPhim.timKiem(p.getMaPhim()) == NULL) {
                cout << "Mã phim không tồn tại trong danh sách đang chiếu!\n";
                return;
            }
            p.setMaSuatChieu(ma);
            temp->data = p;

            cout << "Cập nhật suất chiếu thành công!\n";
            return;
        }
        temp = temp->next;
    }
    cout << "Không tìm thấy suất chiếu!\n";
}

void timSuatChieu(const int &gioChieu){
        Node2* temp = head;
        bool timThay = false;
        suatChieu::inTieuDe();
        while (temp !=NULL) {
            if (temp->data.getGioChieu() == gioChieu ){
                temp->data.hienThi();
                timThay= true;}
            temp = temp->next;
        }
        if (timThay==false){
        cout << "Không có phòng nào có giờ chiếu \"" << gioChieu << "\"!\n";
    }
    }
     suatChieu* timSuatChieuTheoMa(const string &ma) const {
        Node2 *temp = head;
        while (temp != NULL) {
            if (temp->data.getMaSuatChieu() == ma)
                return &(temp->data);
            temp = temp->next;
        }
        return NULL;
    }
};

danhSachSuatChieu dsSC;

class ve{
  private:
  string maVe;
  string maSuatChieu;
  string trangThai;
  public:
  string getMaVe() const {return maVe;}
  string getMaSuatChieu() const {return maSuatChieu;}
  string getTrangThai() const {return trangThai;}
  
  void setMaVe(const string &mave) { maVe=mave; }
  void setMaSuatChieu(const string &masuatchieu) { maSuatChieu=masuatchieu;}
  void setTrangThai(const string &tt) { trangThai=tt;}
  
  void nhap(){
      cout<<"Nhập mã vé: "; getline(cin,maVe);
      cout<<"Nhập mã suất chiếu: "; getline(cin,maSuatChieu);
  }

static void inTieuDe() {
    cout << left
         << setw(8) << "Mã vé"
         << setw(20) << "Mã suất chiếu"
         << setw(10) << "Mã phim"
         << setw(11) << "Mã phòng"
         << setw(14) << "Ngày chiếu"
         << setw(14) << "Giờ chiếu"
         << setw(10) << "Giá vé"
         << endl;
}

    void hienThi(const danhSachSuatChieu &ds) const {
    suatChieu* x = ds.timSuatChieuTheoMa(maSuatChieu);
    cout << left << setw(10) << maVe;
    if(x) {
        x->hienThi();
    } else {
        cout << setw(75) << "[Không tìm thấy suất chiếu]";
    }
}
};
struct Node3 {
    ve data;
    Node3* next;
    Node3(const ve &p){
        data=p;
        next=NULL;
    }
};
class danhSachVe{
  private:
  Node3*head;
  public:
  danhSachVe(){
      head=NULL;
  }
  
  ~danhSachVe(){
        while(head != NULL){
            Node3* temp= head;
            head= head->next;
            delete temp;
        }
    }
    
    void datVe(danhSachSuatChieu &dsX) {
    ve veMoi;
    string maVe, maSuatChieu;
    cout << "\nDanh sách suất chiếu hiện có:\n";
    dsX.xuatDanhSach();
    cout << "\nNhập mã vé: ";
    getline(cin, maVe);
    Node3* temp = head;
    while (temp != NULL) {
        if (temp->data.getMaVe() == maVe) {
            cout << "Mã vé đã tồn tại! Vui lòng chọn mã khác.\n";
            return;
        }
        temp = temp->next;
    }
    cout << "Nhập mã suất chiếu: ";
    getline(cin, maSuatChieu);
    suatChieu* suatChieuTim = dsX.timSuatChieuTheoMa(maSuatChieu);
    if (suatChieuTim == NULL) {
        cout << "Mã suất chiếu không tồn tại! Không thể đặt vé.\n";
        return;
    }
    
    cout << "\n--- Thông tin suất chiếu bạn đã chọn ---\n";
    suatChieu::inTieuDe();
    suatChieuTim->hienThi();
    
    char xacNhan;
    cout << "\nXác nhận đặt vé này?: ";
    cin >> xacNhan;
    cin.ignore();
    
    if (xacNhan == 'Y' || xacNhan == 'y') {
        veMoi.setMaVe(maVe);
        veMoi.setMaSuatChieu(maSuatChieu);
        veMoi.setTrangThai("Da dat");
        
        Node3* newNode = new Node3(veMoi);
        if (head == NULL) {
            head = newNode;
        } else {
            temp = head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
        
        cout << "\n ĐẶT VÉ THÀNH CÔNG\n";
        cout << "Mã vé của bạn: " << maVe << endl;
        cout << "Giá vé: " << suatChieuTim->getGiaVe() << " VND\n";
        cout << "Vui lòng thanh toán trước giờ chiếu!\n";
    } else {
        cout << "Đã hủy đặt vé.\n";
    }
}

void thanhToanVe(danhSachSuatChieu &dsSC){
    if(head==NULL){
        cout<<"Khong co ve nao de thanh toan\n";
        return;
    }
    string maVe;
    cout<<"Nhap ma ve can thanh toan: ";
    getline(cin, maVe);
    Node3* temp=timKiem(maVe);
    if(temp==NULL){
        cout<<"Khong tim thay ve co ma: "<<maVe<<endl;
        return;
    }
    if(temp->data.getTrangThai()=="Da thanh toan"){
        cout<<"Ve nay da duoc thanh toan\n";
        return;
    }
    suatChieu* suatChieuTim = dsSC.timSuatChieuTheoMa(temp->data.getMaSuatChieu());
    if (suatChieuTim == NULL) {
        cout << "Lỗi: Không tìm thấy thông tin suất chiếu!\n";
        return;
    }
    cout << "\n--- Thông tin vé cần thanh toán ---\n";
    cout << "Mã vé: " << temp->data.getMaVe() << endl;
    cout << "Số tiền phải trả: " << suatChieuTim->getGiaVe() << " VND\n";
    
    char xacNhan;
    cout << "\nXác nhận thanh toán vé này?: ";
    cin >> xacNhan;
    cin.ignore();
    
    if (xacNhan == 'Y' || xacNhan == 'y') {
        int phuongThuc;
        cout<<"\n------Chon phuong thuc thanh toan------\n";
        cout<<"1. Tien mat\n";
        cout<<"2. The ngan hang\n";
        cout<<"Moi quy khach lua chon cach thanh toan: ";
        cin>>phuongThuc;
        cin.ignore();
        
        if (phuongThuc==1 || phuongThuc==2){
            temp->data.setTrangThai("Da thanh toan");
            
            cout << "\n----THANH TOÁN THÀNH CÔNG----\n";
            cout << "Mã vé: " << maVe << endl;
            cout << "Số tiền: " << suatChieuTim->getGiaVe() << " VND\n";
            switch(phuongThuc) {
                case 1:
                    cout << "Phương thức: Tien mat\n";
                    break;
                case 2:
                    cout << "Phương thức: The ngan hang\n";
                    break;
            }
            cout << "Quy khach da thanh toan thanh cong! Chuc quy khach xem phim vui ve\n";
        } else {
            cout << "Phương thức thanh toán không hợp lệ!\n";
        }
    } else {
        cout << "Đã hủy thanh toán.\n";
    }
}

    void hienThiVe(const danhSachSuatChieu &dsSC) const{
        if(head==NULL){
            cout<<"Danh sách vé rỗng!";
            return;
        }
        Node3*temp=head;
        while(temp!= NULL){
            temp->data.hienThi(dsSC);
            temp=temp->next;
        }
    }
    
    void xoaVe(const string &maVe){
        if(head== NULL){
            cout<<"Danh sách vé trống!\n";
            return;
        }
        if(head->data.getMaVe() == maVe){
            Node3*temp=head;
            head=head->next;
            delete temp;
            cout<<"Đã xóa vé có mã là: "<<maVe<<endl;
            return;
        }
        
        Node3* prev= head;
        Node3* curr=head->next;
        
        while(curr != NULL && curr->data.getMaVe()!=maVe){
            prev = curr;
            curr=curr->next;
        }
        if(curr !=NULL){
            prev->next=curr->next;
            delete curr;
            cout<<"Đã xóa vé có mã là: "<<maVe<<endl;
        }
        else{
            cout<<"Không tim thấy vé có mã: "<<maVe<<endl;
        }
    }
    
    void suaVe(const string &ma, danhSachSuatChieu &dsSC) {
        Node3* temp = head;
        while (temp != NULL) {
            if (temp->data.getMaVe() == ma) {
                cout << "Nhập thông tin mới:\n";
                ve v;
                v.nhap();

                if (dsSC.timSuatChieuTheoMa(v.getMaSuatChieu()) == NULL) {
                    cout << "Mã suất chiếu không tồn tại! Không thể cập nhật.\n";
                    return;
                }

                v.setMaVe(ma);
                temp->data = v;

                cout << "Cập nhật vé thành công!\n";
                return;
            }
            temp = temp->next;
        }
        cout << "Không tìm thấy vé!\n";
    }

    Node3* timKiem(const string &maVe) const {
        Node3 *temp = head;
        while (temp != NULL) {
            if (temp->data.getMaVe() == maVe)
                return temp;
            temp = temp->next;
        }
        return NULL;
    }
float tinhDoanhThuNgay(const string &ngay, const string &thang, const string &nam, const danhSachSuatChieu &dsXuatChieu)const {
    float tongDoanhThuNgay=0;
    int soVe=0;
    Node3* temp=head;
    
    cout<<"\n========== DOANH THU NGAY " << ngay <<"/"<<thang<<"/" <<nam<< " ==========\n";
    
    while(temp!=NULL){
        if(temp->data.getTrangThai()=="Da thanh toan"){
            suatChieu*sc=dsXuatChieu.timSuatChieuTheoMa(temp->data.getMaSuatChieu());
            
            if(sc!=NULL&&sc->getNgayChieu()==ngay){
                tongDoanhThuNgay+=sc->getGiaVe();
                soVe++;
                cout<<"  Ve " << temp->data.getMaVe()
                    << " | Gia: " << sc->getGiaVe() << " VND\n";	
            }	
        }
        temp=temp->next;
    }
    
    cout<<"------------------------------------------------\n";
    cout<<"Tong so ve ban duoc trong ngay: " << soVe << " ve\n";
    cout<<"Tong doanh thu trong ngay la: " << tongDoanhThuNgay << " VND\n";
    cout<<"-------------------------------------------------\n";
    
    return tongDoanhThuNgay;
}
	float tinhDoanhThuTuan(const string &ngayBatDau, const string &ngayKetThuc,const string &thang, const string &nam, const danhSachSuatChieu &dsXuatChieu)const {
    float tongDoanhThuTuan=0;
    int soVe=0;
    Node3*temp=head;
    
    cout<<"\n========== DOANH THU TU NGAY " << ngayBatDau << " - " << ngayKetThuc<<"/"<<thang<<"/" <<nam<< " ==========\n";
    
    while(temp!=NULL){
        if(temp->data.getTrangThai()=="Da thanh toan"){
            suatChieu*sc=dsXuatChieu.timSuatChieuTheoMa(temp->data.getMaSuatChieu());
            if(sc!=NULL){
                string ngayChieu=sc->getNgayChieu();
                if(ngayChieu>=ngayBatDau&&ngayChieu<=ngayKetThuc){
                    tongDoanhThuTuan+=sc->getGiaVe();
                    soVe++;
                    cout<<"   Ngay " << ngayChieu
                        << " | Ve " << temp->data.getMaVe()
                        << " | Gia: " << sc->getGiaVe() << " VND\n";
                }
            }
        }
        temp=temp->next;
    }
    
    cout<<"------------------------------------------------------------\n";
    cout<<"Tong so ve ban duoc trong tuan: " << soVe << " ve\n";
    cout<<"Tong doanh thu trong tuan la: " << tongDoanhThuTuan << " VND\n";
    cout<<"-------------------------------------------------------------\n";
    
    return tongDoanhThuTuan;
}
	float tinhDoanhThuThang(const string &thang, const string &nam, const danhSachSuatChieu& dsXuatChieu)const{
    float tongDoanhThuThang=0;
    int soVe=0;
    Node3* temp=head;
    
    cout<<"\n==============DOANH THU THANG " << thang << " NAM " << nam << "===============\n";
    
    while (temp!=NULL){
        if(temp->data.getTrangThai()=="Da thanh toan"){
            suatChieu*sc=dsXuatChieu.timSuatChieuTheoMa(temp->data.getMaSuatChieu());
            if(sc!=NULL){
                string ngayChieu=sc->getNgayChieu();
                if (ngayChieu.length() >= 10) {
                    string thangChieu=ngayChieu.substr(3, 2);
                    string namChieu=ngayChieu.substr(6, 4);
                    if (thangChieu == thang && namChieu == nam) {
                        tongDoanhThuThang += sc->getGiaVe();
                        soVe++;
                        cout<<"  Ngay " << ngayChieu
                            << " | Ve " << temp->data.getMaVe()
                            << " | Gia: " << sc->getGiaVe() << " VND\n";
                    }
                }
            }
        }
        temp=temp->next;
    }
    
    cout<<"-----------------------------------------------------\n";
    cout<<"Tong so ve ban duoc trong thang: " << soVe << " ve\n";
    cout<<"Tong doanh thu trong thang la: " << tongDoanhThuThang << " VND\n";
    cout<<"------------------------------------------------------\n";
    
    return tongDoanhThuThang;
}
};
danhSachVe dsVe;
	     
void doanhThu(){
     int luachon;
     string ngay, ngayBatDau, ngayKetThuc, thang, nam;
    while(1){
        cout<<"5.1 Tổng doanh thu trong ngày."<<endl;
        cout<<"5.2 Tổng doanh thu trong tuần."<<endl;
        cout<<"5.3 Tổng doanh thu trong tháng."<<endl;
        cout<<"0. Quay lại."<<endl;
        cout<<"Chọn chức năng: "<<endl;
        cin>>luachon;
        cin.ignore();
    switch(luachon){
        case 1:
        	cout<<"Nhap ngay can xem doanh thu: ";
        	getline(cin, ngay);
        	cout<<"Nhap thang: ";
        	getline(cin, thang);
        	cout<<"Nhap nam: ";
        	getline(cin, nam);
        	dsVe.tinhDoanhThuNgay(ngay,thang, nam, dsSC);
        	break;
        case 2:
        	cout<<"Nhap ngay bat dau tuan: ";
        	getline(cin, ngayBatDau);
        	cout<<"Nhap ngay ket thuc tuan: ";
        	getline(cin, ngayKetThuc);
        	cout<<"Nhap thang: ";
        	getline(cin, thang);
        	cout<<"Nhap nam: ";
        	getline(cin, nam);
        	dsVe.tinhDoanhThuTuan(ngayBatDau, ngayKetThuc,thang, nam, dsSC);
        	break;
        case 3:
        	cout<<"Nhap thang: ";
        	getline(cin, thang);
        	cout<<"Nhap nam: ";
        	getline(cin, nam);
        	dsVe.tinhDoanhThuThang(thang, nam, dsSC);
        break;
        case 0:
        cout << "Thoát chương trình.\n";
        break;
}
}
    }
void ve(){
    string ma;
     int luachon;
    while(1){
    	cout<<"4.1 Đặt vé."<<endl;
        cout<<"4.2 Sửa vé."<<endl;
        cout<<"4.3 Xóa vé."<<endl;
        cout<<"4.4 Tìm kiếm vé."<<endl;
        cout<<"4.5 Hiển thị danh sách vé."<<endl;
        cout<<"4.6 Thanh toán vé."<<endl;
        cout<<"0. Quay lại."<<endl;
        cout<<"Chọn chức năng: "<<endl;
        cin>>luachon;
        cin.ignore();
    switch(luachon){
        case 1:
         cout<<"MOI BAN DAT VE XEM PHIM\n";
        dsVe.datVe(dsSC);
        break;
        case 2:
        cout<<"NHAP MA VE MA BAN MUON SUA: ";
        getline(cin,ma);
        dsVe.suaVe(ma, dsSC);
        break;
        case 3:
        cout<<"NHAP MA VE MA BAN MUON XOA: ";
        getline(cin,ma);
        dsVe.xoaVe(ma);
        break;
        case 4:
        cout << "NHAP MA VE CAN TIM: ";
        getline(cin, ma);
        if (dsVe.timKiem(ma)) {
            ve::inTieuDe();
            dsVe.timKiem(ma)->data.hienThi(dsSC);
        } 
        else{
                cout << "Không tìm thấy vé!\n";}
        break;
        case 5:
        ve::inTieuDe();
        dsVe.hienThiVe(dsSC);
        break;
        case 6:
        cout<<"-----MOI BAN THANH TOAN VE-----\n";
        dsVe.thanhToanVe(dsSC);
        break;
        case 0:
        	cout<<"Thoat chuong trinh\n";
        return;
    }
    }
    }
void suatChieu(){
    string ma;
    int gio;
   int luachon;
    while(1){
        cout<<"3.1 Thêm suất chiếu."<<endl;
        cout<<"3.2 Xóa suất chiếu."<<endl;
        cout<<"3.3 Xem danh sách các suất chiếu."<<endl;
        cout<<"3.4 Cập nhật suất chiếu."<<endl;
        cout<<"3.5 Tìm kiếm suất chiếu theo giờ chiếu."<<endl;
        cout<<"0. Quay lại."<<endl;
        cout<<"Chọn chức năng: "<<endl;
        cin>>luachon;
        cin.ignore();
    switch(luachon){
        case 1:
        dsSC.themSuatChieu(dc, a);
        break;
        case 2:
        cout<<"Nhập mã suất chiếu bạn muốn xóa: ";
         getline(cin,ma);
        dsSC.xoaSuatChieu(ma);
        break;
        case 3:
        dsSC.xuatDanhSach();
        break;
        case 4:
        cout << "Nhập mã suất chiếu cần cập nhật: ";
        getline(cin, ma);
        dsSC.suaSuatChieu(ma, dc, a);
        break;
        case 5:
        do{
            cout<<"Nhập giờ bạn muốn tìm(0-24): ";
            cin>>gio;
        }while(gio<=0 || gio>=25);
        dsSC.timSuatChieu(gio);
        break;
        case 0:
        return;
    }
    }
}
void qlPhongChieu(){
     string ma;
    int luachon;
    while(1){
        cout<<"2.1 Thêm phòng chiếu."<<endl;
        cout<<"2.2 Xóa phòng chiếu."<<endl;
        cout<<"2.3 Xem danh sách các phòng chiếu."<<endl;
        cout<<"2.4 Tìm phòng chiếu theo trạng thái."<<endl;
        cout<<"2.5 Tìm phòng chiếu theo mã phòng."<<endl;
        cout<<"2.6 Cập nhật phòng"<<endl;
        cout<<"0. Quay lại."<<endl;
        cout<<"Chọn chức năng: "<<endl;
        cin>>luachon;
        cin.ignore();
    switch(luachon){
        case 1:
        a.themPhong();
        break;
        case 2:
         cout<<"Nhập mã phòng bạn muốn xóa: ";
         getline(cin,ma);
         a.xoaPhong(ma);
        break;
        case 3:
        a.xuatDanhSach();
        break;
        case 4:
        cout << "Nhập trạng thái cần tìm: ";
        getline(cin, ma);
        a.timPhong(ma);
        break;
        case 5:
        cout << "Nhập mã phim cần tìm: ";
        getline(cin, ma);
        if (a.timKiem(ma)) {
            phongChieu::inTieuDe();
            a.timKiem(ma)->data.hienThiPhong();
        } 
        else{
                cout << "Không tìm thấy phòng!\n";}
        break;
        case 6:
        cout << "Nhập mã phòng cần cập nhật: ";
        getline(cin, ma);
        a.suaPhong(ma);
        break;
        case 0:
        return ;
    }
    }
}
void sapChieu(){
    string ma;
    int luachon;
    while(1){
        cout<<"1.1.1 Thêm phim vào danh sách."<<endl;
        cout<<"1.1.2 Xóa phim khỏi danh sách."<<endl;
        cout<<"1.1.3 Tìm phim theo mã."<<endl;
        cout<<"1.1.4 Xem danh sách."<<endl;
        cout<<"1.1.5 Chuyển phim vào danh sách đang chiếu."<<endl;
        cout<<"1.1.6 Cập nhật phim."<<endl;
        cout<<"0. Quay lại."<<endl;
        cout<<"Chọn chức năng: "<<endl;
        cin>>luachon;
    switch(luachon){
        case 1:
        sc.themPhim();
        break;
        case 2:
        cin.ignore();
        cout << "Nhập mã phim cần xóa: ";
        getline(cin, ma);
        sc.xoaPhim(ma);
        break;
        case 3:
        cin.ignore();
        cout << "Nhập mã phim cần tìm: ";
        getline(cin, ma);
        if (sc.timKiem(ma)) {
            danhSachPhim::inTieuDe();
            sc.timKiem(ma)->data.xuatPhim();
        } 
        else{
                cout << "Không tìm thấy phim!\n";}
        break;
        case 4:
        sc.xuatDanhSach();
        break;
        case 5:
        cin.ignore();
        cout << "Nhập mã phim cần chuyển sang đang chiếu: ";
        getline(cin, ma);
        chuyenPhim(ma);
        break;
        case 6:
        cin.ignore();
        cout << "Nhập mã phim cần cập nhật: ";
        getline(cin, ma);
        sc.suaPhim(ma);
        break;
        case 0:
        return ;
    }
}
}
void dangChieu(){
    string ma;
    int luachon;
    while(1){
        cout<<"1.1.1 Thêm phim vào danh sách."<<endl;
        cout<<"1.1.2 Xóa phim khỏi danh sách."<<endl;
        cout<<"1.1.3 Tìm phim theo mã."<<endl;
        cout<<"1.1.4 Xem danh sách."<<endl;
        cout<<"1.1.5 Cập nhật phim."<<endl;
        cout<<"0. Quay lại."<<endl;
        cout<<"Chọn chức năng: "<<endl;
        cin>>luachon;
    switch(luachon){
        case 1:
        dc.themPhim();
        break;
        case 2:
        cin.ignore();
        cout << "Nhập mã phim cần xóa: ";
        getline(cin, ma);
        dc.xoaPhim(ma);
        break;
        case 3:
        cin.ignore();
        cout << "Nhập mã phim cần tìm: ";
        getline(cin, ma);
        if (dc.timKiem(ma)) {
            danhSachPhim::inTieuDe();
            dc.timKiem(ma)->data.xuatPhim();
        } 
        else{
                cout << "Không tìm thấy phim!\n";}
        break;
        case 4:
        dc.xuatDanhSach();
        break;
        case 5:
        cin.ignore();
        cout << "Nhập mã phim cần cập nhật: ";
        getline(cin, ma);
        dc.suaPhim(ma);
        break;
        case 0:
        return ;
    }
    }
}
void qlDanhSachPhim(){
    int luachon;
    while(1){
        cout<<"1.1 Danh sách phim đang chiếu."<<endl;
        cout<<"1.2 Danh sách phim sắp chiếu."<<endl;
        cout<<"0. Quay lại."<<endl;
        cout<<"Chọn chức năng: "<<endl;
        cin>>luachon;
    switch(luachon){
        case 1:
        dangChieu();
        break;
        case 2:
        sapChieu();
        break;
        case 0:
        return ;
    }
}
}
int main(){
    int luachon;
    while(1){
        cout<<"Quản lý rạp chiếu phim"<<endl;
        cout<<"1. Quản lý danh sách phim."<<endl;
        cout<<"2. Quản lý phòng chiếu."<<endl;
        cout<<"3. Quản lý suất chiếu."<<endl;
        cout<<"4. Quản lý vé."<<endl;
        cout<<"5. Tổng doanh thu."<<endl;
        cout<<"0. Thoát."<<endl;
        cout<<"Chọn chức năng: "<<endl;
        cin>>luachon;
    switch(luachon){
        case 1:
        qlDanhSachPhim();
        break;
        case 2:
        qlPhongChieu();
        break;
        case 3:
        suatChieu();
        break;
        case 4:
        ve();
        break;
        case 5:
        doanhThu();
        break;
        case 0:
        cout << "Thoát chương trình.\n";
        return 0;
    }
    }
}
