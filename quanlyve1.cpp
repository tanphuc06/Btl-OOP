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
 void SuatChieu(){
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
            cout << "Đã cập nhật thông tin suất chiếu thành công!\n";
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
        return NULL;
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
 void datVe(danhSachSuatChieu &dsSC) {
    ve veMoi;
    string maVe, maSuatChieu;
    cout << "\nDanh sách suất chiếu hiện có:\n";
    dsSC.xuatDanhSach();
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
    suatChieu* suatChieuTim = dsSC.timSuatChieuTheoMa(maSuatChieu);
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
        cout << "Vui long thanh toan truoc gio chieu!\n";
    } else {
        cout << "Da huy dat ve.\n";
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
        cout<<"Moi quy khach lua chon phuong thuc thanh toan: ";
        cin>>phuongThuc;
        cin.ignore();
        
        if (phuongThuc==1 || phuongThuc==2){
            temp->data.setTrangThai("Da thanh toan");
            
            cout << "\n----THANH TOAN THANH CONG----\n";
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
            cout << "Phuong thuc thanh toan cua quy khach khong hop le!\n";
        }
    } else {
        cout << "Da huy thanh toan.\n";
    }
}
    void hienThiVe(const danhSachSuatChieu &dsSC) const{
        if(head==NULL){
            cout<<"Khong co ve nao trong danh sach!";
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
            cout<<"Không tim thấy vé có mã lã: "<<maVe<<endl;
        }
    }
    void suaVe(const string &maVe) {
    if (head == NULL) {
        cout << "Danh sách phòng rỗng!\n";
        return;
    }

    Node3* temp = head;
    while (temp) {
        if (temp->data.getMaVe() == maVe) {
            cout << "Đã tìm thấy vé. Nhập thông tin mới:\n";
            temp->data.nhap();
            temp->data.setMaVe(maVe);
            cout << "Đã cập nhật thông tin vé thành công!\n";
            return;
        }
        temp = temp->next;
    }
    cout << "Không tìm thấy vé có mã: " << maVe << endl;
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
float tinhDoanhThuNgay(const string &ngay, const danhSachSuatChieu &dsXuatChieu)const {
    float tongDoanhThuNgay=0;
    int soVe=0;
    Node3* temp=head;
    
    cout<<"\n========== DOANH THU NGAY " << ngay << " ==========\n";
    
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
void doanhThu(){
     int luachon;
      danhSachSuatChieu dsSC;
    danhSachVe dsVe;
     string ngay, thang, nam;
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
        	break;
        case 2:
        	break;
        case 3:
        break;
        case 0:
        cout << "Thoát chương trình.\n";
        break;
}
}
}
};
int main(){
    danhSachSuatChieu dsSC;
    danhSachVe dsVe;
    string ma;
     int luachon;
    while(1){
       cout<<"4.1 Đặt vé."<<endl;
        cout<<"4.2 Sửa vé."<<endl;
        cout<<"4.3 Xóa vé."<<endl;
        cout<<"4.4 Tìm kiếm vé."<<endl;
        cout<<"4.5 Hiển thị danh sách vé."<<endl;
        cout<<"4.6 Thanh toán vé."<<endl;
        cout<<"4.7 Doanh thu."<<endl;
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
        dsVe.suaVe(ma);
        break;
        case 3:
        cout<<"NHAP MA VE MA BAN MUON XOA: ";
        getline(cin,ma);
        dsVe.xoaVe(ma);
        break;
        case 4:
        cout << "NHAP MA VE MA BAN CAN TIM: ";
        getline(cin, ma);
        if (dsVe.timKiem(ma)) {
            ve::inTieuDe();
            dsVe.timKiem(ma)->data.hienThi(dsSC);
        } 
        else{
                cout << "KHONG TIM THAY VE!\n";}
        break;
        case 5:
        	cout<<"\n=========DANH SACH VE============\n";
        ve::inTieuDe();
        dsVe.hienThiVe(dsSC);
        break;
        case 6:
          cout<<"\n--------MOI BAN THANH TOAN VE--------------\n";
          dsVe.thanhToanVe(dsSC);
        break;
        case 0:
        cout << "Thoat chuong trinh.\n";
        break;
      case 7:
        cout<<"\n============DOANH THU VE==============\n";
        dsVe.doanhThu();
        break;
        return 0 ;
    }
    }
    }

    


