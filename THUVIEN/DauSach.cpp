#include"DanhMucSach.cpp">
#define MAXLIST 5
struct DauSach {
	char ISBN[6];
	char TenSach[200];
	int SoTrang;
	char TacGia[100];
	char NamXuatBan[10];
	char TheLoai[50];
	LISTDMS dms;
};
typedef struct DauSach DAUSACH;


//Danh Sach DAU SACH - DANH SACH TUYEN TINH - MANG CONTRO
struct listDAUSACH {
	int soluong;
	DAUSACH *nodeDS[MAXLIST];

};
typedef struct listDAUSACH LISTDS;
int randomsMADS() {
	int lower = 100000, upper = 999999;
	srand(time(0)); 
	return (rand() % (upper - lower + 1)) + lower; 
	
}
void NhapDauSach(LISTDS &l){
	int endchar;
	int ISBN;
	char *TenSach;
	char * SoTrang;
	char *TacGia;
	char *NamXuatBan;
	char *TheLoai;
	while(true){
	NhapISBN:
		ISBN = randomsMADS();
		printf("\nISBN:  %d",ISBN);
	NhapTenSach:
		printf("\nNhap ten sach: ");
		TenSach = InputType(200,endchar,1);
	NhapSoTrang:
		printf("Nhap so trang : ");
		SoTrang  =InputType(6,endchar,2);
	NhapTacGia:
		printf("Nhap tac gia : ");
		TacGia =InputType(100,endchar,3);
	NhapNXB:
		printf("Nhap nam xuat ban : ");
		NamXuatBan = InputType(11,enchar,1);
	NhapTheLoai:
		printf("Nhap the loai : ");	
		TheLoai = InputType(51,endchar,2);
	}
}
