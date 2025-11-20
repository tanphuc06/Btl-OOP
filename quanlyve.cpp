#include<iostream>
#include <iomanip>
using namespace std;
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
    void themSuatChieu(){
        suatChieu p;
        p.nhap();
        Node2* temp= head;
        while(temp!= NULL){
            if(temp->data.getMaSuatChieu() == p.getMaSuatChieu()){
                cout<<"Mã suất chiếu này đã tồn tại. Không thể thêm. \n";
                return;
            }
            temp=temp->next;
        }
        Node2* newNode = new Node2(p);
        if (head==NULL) {
            head = newNode;
        }
        else {
            Node2* temp = head;
            while (temp->next!=NULL) {
                temp = temp->next;}
            temp->next = newNode;
        }
        cout << "Đã thêm suất chiếu vào danh sách!\n";
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
    void suaSuatChieu(const string &maSuatChieu) {
    if (head == NULL) {
        cout << "Danh sách phòng rỗng!\n";
        return;
    }

    Node2* temp = head;
    while (temp) {
        if (temp->data.getMaSuatChieu() == maSuatChieu) {
            cout << "Đã tìm thấy phòng. Nhập thông tin mới:\n";
            temp->data.nhap();
            temp->data.setMaSuatChieu(maSuatChieu);
            cout << "Đã cập nhật thông tin xuất chiếu thành công!\n";
            return;
        }
        temp = temp->next;
    }

    cout << "Không tìm thấy suất chiếu có mã: " << maSuatChieu << endl;
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
        return nullptr;
    }
};
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
      cout<<"Nhập tình trạng: "; getline(cin,trangThai);
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
int main(){
    danhSachSuatChieu ds;
    ve v;
     int luachon;
    while(1){
        cout<<"4.1 Đặt vé."<<endl;
        cout<<"4.2 In vé."<<endl;
        cout<<"4.3 Thêm vé."<<endl;
        cout<<"0. Quay lại."<<endl;
        cout<<"Chọn chức năng: "<<endl;
        cin>>luachon;
    switch(luachon){
        case 1:
        cout << "== Nhập danh sách suất chiếu ==\n";
        cin.ignore();
    ds.themSuatChieu();
        break;
        case 2:
        cout << "\n== Thông tin vé chi tiết ==\n";
    ve::inTieuDe();
    v.hienThi(ds);
        break;
        case 3:
        cout << "\n== Nhập thông tin vé ==\n";
    cin.ignore();
    v.nhap();
        break;
        case 0:
        cout << "Thoát chương trình.\n";
        break;
        return 0 ;
    }
    }
    }