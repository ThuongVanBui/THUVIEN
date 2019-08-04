#include"DanhMucSach.cpp">
#define MAXLIST 5
struct DauSach {
	char ISBN[6];
	char TenSach[200];
	int SoTrang;
	char TacGia[100];
	int NamXuatBan;
	char TheLoai[50];
	LISTDMS dms;
};
typedef struct DauSach DAUSACH;


//Danh Sach DAU SACH - DANH SACH TUYEN TINH - MANG CONTRO

struct listDAUSACH {
	int soluong = -1;
	DAUSACH *nodeDS[MAXLIST];

};
typedef struct listDAUSACH LISTDS;


//khoi tao dau sach
void khoitaoDauSach(LISTDS &ls) {
	ls.soluong = -1;
}

//kiem tra danh sach rong
int dauSachRong (LISTDS ls) {
	return ls.soluong == -1 ? 0 : 1;
}

//kiem tra danh sach day
int dauSachDay(LISTDS ls) {
	return ls.soluong == (MAXLIST - 1) ? 1 : 0;
}

int kiemTraMaISBN(LISTDS ls, char *maISBN) {
	for (int i = 0; i < ls.soluong; i++) {
		if (strcmp(maISBN,ls.nodeDS[i]->ISBN) == 0){
			return 1;
		} else {
			return 0;
		}
	}
}

void NhapThemDauSach(LISTDS &ls) {
	int endchar;
	char *_isbn;
	
	char *tenTG;
	int sotrang;
	int namXB;
	char *theloai;
	char *tenSach;

		
	while(true){
		DAUSACH *ds= new DAUSACH;
	NHAPISBN:
		printf("Ma ISBN:");
		scanf("%s", _isbn);
	//	_isbn = InputType(6,endchar,1);
		if (endchar == ESC) {
			break;
		}
		if (strlen(_isbn) == 0) {
			printf("Ma ISBN khong duoc rong!\n");
			goto NHAPISBN;

		}		
		if (strlen(_isbn) < 6) {
			printf("Ma ISBN it nhat phai co 6 ky tu!\n");
			goto NHAPISBN;
		}
		if (kiemTraMaISBN(ls,_isbn) == 1) {
			printf("Ma ISBN nay da co!\n");
			goto NHAPISBN;
		}
		

		strcpy(ds->ISBN, _isbn);
	printf("%s",ds->ISBN);
	NHAPTENSACH:
		printf("\nNhap ten sach:");
		fflush(stdin);
		scanf("%s",tenSach);
	//	tenSach = InputType(200,endchar,1);
		if (strlen(tenSach) == 0) {
			printf("Ten sach khong duoc rong!\n");
			goto NHAPTENSACH;

		}
		printf("   %s",ds->ISBN);
		strcpy(ds->TenSach, tenSach);
		printf("    %s",ds->ISBN);
		
	NHAPSOTRANG:
		printf("\nNhap so trang:");
		sotrang = atoi(InputType(10,endchar,2));
		if (sotrang == 0) {
			printf("So trang phai khac 0!\n");
			goto NHAPSOTRANG;

		}
		
		ds->SoTrang = sotrang ;			
		
	NHAPTACGIA:
		printf("\nNhap tac gia:");
		tenTG = InputType(100,endchar,3);
		if (strlen(tenTG) == 0) {
			printf("Ten tac gia khong duoc bo trong!\n");
			goto NHAPTACGIA;

		}
		
		strcpy(ds->TacGia, tenTG);	
		
	NHAPNAMXUATBAN:
		printf("\nNhap nam xuat ban:");
		namXB = atoi(InputType(5,endchar,2));
		if (namXB == 0) {
			printf("Nam san xuat khong duoc bo trong!\n");
			goto NHAPNAMXUATBAN;

		}
		
		if (namXB > LayNamHT()) {
			printf("Nam san xuat khong duoc lon hon nam hien tai!\n");
			goto NHAPNAMXUATBAN;		
		}
		
		ds->NamXuatBan = namXB;		
	
	NHAPTHELOAI:
		printf("\nNhap the loai:");
		theloai = InputType(50,endchar,3);
		if (strlen(theloai) == 0) {
			printf("The loai khong duoc bo trong!\n");
			goto NHAPNAMXUATBAN;

		}
		
		strcpy(ds->TheLoai, theloai);
		
		if (endchar == ESC) {
			break;
		}
	printf("%s",ds->ISBN);
	//Danh muc sach
		printf("\n\n==> NHAP DANH MUC SACH <==\n\n");
		khoiTaoDS(ds->dms);
		
		NhapDMSach(ds->dms,ds->ISBN);
		XuatDMS(ds->dms);
		getch();
		if (dauSachDay(ls) == 1) {
			printf("Danh sach da day!");
			break;
		}
		
		ls.soluong++;
		ls.nodeDS[ls.soluong] = ds;
	
	}
	
}


void nhapDauSach(LISTDS &ls) {
	int endchar;
	char *maISBN;
	char *tenSach = "";
	
	while(true) {
		DAUSACH *dSach = new DAUSACH;
		printf("\nNhap ISBN:");
//		fflush(stdin);
		gets(maISBN);
//		maISBN = InputType(6,endchar,1);
		strcpy(dSach->ISBN, maISBN);

		printf("\nNhap ten sach:");
//		fflush(stdin);
		gets(tenSach);

//		tenSach = InputType(200,endchar,3);
		strcpy(dSach->TenSach,tenSach);

		printf("\n%s",dSach->ISBN);
		printf("\n%s",dSach->TenSach);
	
	}
	
}

void XuatDauSach(LISTDS ls) {
	for (int i = 0; i <= ls.soluong; i++) {
		printf("\nMa ISBN: %s\n",ls.nodeDS[i]->ISBN);
		printf("Ten sach: %s\n",ls.nodeDS[i]->TenSach);
		printf("Tac gia: %s\n",ls.nodeDS[i]->TacGia);
		printf("The loai: %s\n",ls.nodeDS[i]->TheLoai);
		printf("So Trang: %d\n",ls.nodeDS[i]->SoTrang);
		printf("Nam xuat ban: %d\n",ls.nodeDS[i]->NamXuatBan);
		printf("\n\n==> DANH MUC SACH <==\n\n");
		XuatDMS(ls.nodeDS[i]->dms);
		
	}
}

int main() {
	LISTDS ls;
	khoitaoDauSach(ls);
//	NhapThemDauSach(ls);
	nhapDauSach(ls);
	
	XuatDauSach(ls);
	getch();
}
