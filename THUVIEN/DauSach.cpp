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

//int main() {
//	
//}
