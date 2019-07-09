#define MAXLIST 5
typedef struct DauSach {
	char ISBN[6];
	char TenSach[200];
	int SoTrang;
	char TacGia[100];
	char NamXuatBan[10];
	char TheLoai[50];
	struct DanhMucSach *dms;
}DauSach;


//Danh Sach DAU SACH - DANH SACH TUYEN TINH - MANG CONTRO
typedef struct DAUSACH {
	DauSach DS;
	DauSach *nodeDS[MAXLIST];

}DAUSACH;

//int main() {
//	
//}
