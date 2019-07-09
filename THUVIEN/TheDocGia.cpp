enum TrangThaiThe {
	DuocPhep = 0,
	KhongDuocPhep = 1
};

enum Phai {
	Nam = 0,
	Nu = 1
};



typedef struct DanhSachTheDocGia {
	int MaThe;
	char Ho[20];
	char Ten[50];
	int phai;
	int trangthaithe;
	struct DanhSachTheDocGia *DSTheDocGia;
	
}DanhSachTheDocGia;


//Danh Sach THE DOC GIA - CAY NHI PHAN
typedef struct THEDOCGIA {
	DanhSachTheDocGia DSTDG;
	THEDOCGIA *tdgLeft;
	THEDOCGIA *tdgRight;

}THEDOCGIA;

//int main() {
//
//}
