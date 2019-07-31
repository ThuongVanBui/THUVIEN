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
	char *isbn;
	char *tenSach;
	char *tenTG;
	int sotrang;
	int namXB;
	char *theloai;
	
		
	while(true){
		DAUSACH *ds;
	NHAPISBN:
		printf("Ma ISBN:");
		isbn = InputType(6,endchar,1);
		if (endchar == ESC) {
			break;
		}
		if (strlen(isbn) == 0) {
			printf("Ma ISBN khong duoc rong!\n");
			goto NHAPISBN;

		}		
		if (strlen(isbn) < 6) {
			printf("Ma ISBN it nhat phai co 6 ky tu!\n");
			goto NHAPISBN;
		}
		if (kiemTraMaISBN(ls,isbn) == 1) {
			printf("Ma ISBN nay da co!\n");
			goto NHAPISBN;
		}
		strcpy(ds->ISBN, isbn);
	
	NHAPTENSACH:
		printf("\nNhap ten sach:");
		tenSach = InputType(200,endchar,1);
		if (strlen(tenSach) == 0) {
			printf("Ten sach khong duoc rong!\n");
			goto NHAPTENSACH;

		}
		strcpy(ds->TenSach, tenSach);
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
	
	//Danh muc sach
		printf("\n\n==> NHAP DANH MUC SACH <==\n\n");
		khoiTaoDS(ds->dms);
		NhapDMSach(ds->dms);
		if (dauSachDay(ls) == 1) {
			printf("Danh sach da day!");
			break;
		}
		printf("=====");
		ls.soluong++;
		printf("%d",ls.soluong);

		ls.nodeDS[0] = ds;
	}
	
}

void XuatDauSach(LISTDS ls) {
	for (int i = 0; i < ls.soluong; i++) {
		printf("Ma ISBN: %s\n",ls.nodeDS[i]->ISBN);
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
	NhapThemDauSach(ls);
	
	XuatDauSach(ls);
}
