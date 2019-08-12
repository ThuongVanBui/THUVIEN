#include"DanhMucSach.cpp">
#define MAXLIST 500

char MENU_DAUSACH[5][30] 		= {"1.Them    ","2.Xoa     ","3.Sua     ","4.Xem DS     ","5.Luu tep     " };


enum ENUMTHELOAI {
	chinhtriphapluat = 0,
	khoahoccongnghekinhte = 1,
	vanhoaxahoilichsu = 2,
	vanhocnghethuat = 3,
	giaotrinh = 4,
	truyentieuthuyet = 5,
	tamlytamlinhtongiao = 6,
	sachthieunhi = 7,
	theloaikhac = 8
	
};


ENUMTHELOAI kieutheloai (int theloai) {
	switch(theloai){
		case 0:
			return chinhtriphapluat;
		case 1:
			return khoahoccongnghekinhte;	
		case 2:
			return vanhoaxahoilichsu;	
		case 3:
			return vanhocnghethuat;	
		case 4:
			return giaotrinh;	
		case 5:
			return truyentieuthuyet;	
		case 6:
			return tamlytamlinhtongiao;	
		case 7:
			return sachthieunhi;	
		case 8:
			return theloaikhac;	
	};
	
	
}



void xuatTheLoai(int x, int y) {
	gotoxy(x,y);
	printf("\n0:CHINH TRI - PHAP LUAT       ");	
	gotoxy(x,y+1);
	printf("\n1:KHOA HOC CONG NGHE - KINH TE");	
	gotoxy(x,y+2);
	printf("\n2:VAN HOA XA HOI - LICH SU    ");	
	gotoxy(x,y+3);
	printf("\n3:VAN HOA NGHE THUAT          ");	
	gotoxy(x,y+4);
	printf("\n4:GIAO TRINH                  ");	
	gotoxy(x,y+5);
	printf("\n5:TRUYEN, TIEU THUYET         ");	
	gotoxy(x,y+6);
	printf("\n6:TAM LY, TAM LINH, TON GIAO  ");	
	gotoxy(x,y+7);
	printf("\n7:SACH THIEU NHI              ");	
	gotoxy(x,y+8);
	printf("\n8:THE LOAI KHAC               ");	

}

char *stringtheloai (ENUMTHELOAI theloai) {
	ENUMTHELOAI check = theloai;
	switch(check){
		case chinhtriphapluat:
			return "CHINH TRI - PHAP LUAT       ";
		case khoahoccongnghekinhte:
			return "KHOA HOC CONG NGHE - KINH TE";	
		case vanhoaxahoilichsu:
			return "VAN HOA XA HOI - LICH SU    ";	
		case vanhocnghethuat:
			return "VAN HOA NGHE THUAT          ";	
		case giaotrinh:
			return "GIAO TRINH                  ";	
		case truyentieuthuyet:
			return "TRUYEN, TIEU THUYET         ";	
		case tamlytamlinhtongiao:
			return "TAM LY, TAM LINH, TON GIAO  ";	
		case sachthieunhi:
			return "SACH THIEU NHI              ";	
		case theloaikhac:
			return "THE LOAI KHAC               ";	
	};
	
	
}

struct DauSach {
	char ISBN[8];
	char TenSach[200];
	int SoTrang;
	char TacGia[100];
	int NamXuatBan;
	int TheLoai;
	int solanmuon;
	LISTDMS dms;
};
typedef struct DauSach DAUSACH;
typedef struct DauSach *pDAUSACH;


//Danh Sach DAU SACH - DANH SACH TUYEN TINH - MANG CONTRO

struct listDAUSACH {
	int soluong = -1;
	pDAUSACH nodeDS[MAXLIST];

};
typedef struct listDAUSACH LISTDS;

int randomsMADS() {
	int lower = 100000, upper = 999999;
	srand(time(0)); 
	return (rand() % (upper - lower + 1)) + lower; 
	
}

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
	for (int i = 0; i <= ls.soluong; i++) {
		if (strcmp(ls.nodeDS[i]->ISBN,maISBN) == 0){
			return 1;
		} else {

			return 0;
		}
	}
}

LISTDS taoDStheoTL(LISTDS ls, int theloai) {
	LISTDS lsTL;
	khoitaoDauSach(lsTL);
	for (int i = 0; i <= ls.soluong; i++) {
		if (ls.nodeDS[i]->TheLoai == theloai) {
			lsTL.soluong++;
			lsTL.nodeDS[lsTL.soluong] = ls.nodeDS[i];
		}
	}
	
	return lsTL;

}

void swap_DS(pDAUSACH ds1, pDAUSACH ds2)
{
	DAUSACH temp = *ds1;
	*ds1 = *ds2;
	*ds2 = temp;
}
//
//
//void sapXepDSTLTheoTen(LISTDS &ls) {
//	
//}


void XuatDauSach(LISTDS ls) {
	clrscr();
	for (int i = 0; i <= ls.soluong; i++) {
		printf("\nMa ISBN: %s\n",ls.nodeDS[i]->ISBN);
		printf("Ten sach: %s\n",ls.nodeDS[i]->TenSach);
		printf("Tac gia: %s\n",ls.nodeDS[i]->TacGia);
		printf("The loai: %s\n",stringtheloai(kieutheloai(ls.nodeDS[i]->TheLoai)));
		printf("So Trang: %d\n",ls.nodeDS[i]->SoTrang);
		printf("Nam xuat ban: %d\n",ls.nodeDS[i]->NamXuatBan);
		printf("\n\n==> DANH MUC SACH <==\n\n");
		XuatDMS(ls.nodeDS[i]->dms);
		
	}
}

void XuatDauSachTheoTheLoai(LISTDS ls) {
	clrscr();
	for (int i = 0; i <= ls.soluong; i++) {
			printf("\nMa ISBN: %s\n",ls.nodeDS[i]->ISBN);
			printf("Ten sach: %s\n",ls.nodeDS[i]->TenSach);
			printf("Tac gia: %s\n",ls.nodeDS[i]->TacGia);
			printf("The loai: %s\n",stringtheloai(kieutheloai(ls.nodeDS[i]->TheLoai)));
			printf("So Trang: %d\n",ls.nodeDS[i]->SoTrang);
			printf("Nam xuat ban: %d\n",ls.nodeDS[i]->NamXuatBan);
//			printf("\n\n==> DANH MUC SACH <==\n\n");
//			XuatDMS(ls.nodeDS[i]->dms);
		

		
	}
}

void NhapThemDauSach(LISTDS &ls) {
	if (ls.soluong != -1) {
		khoitaoDauSach(ls);
	}
	
	//dau sach
	DAUSACH *ds;
	
	int endchar;
	char *_isbn;
	
	char *tenTG;
	int sotrang;
	int namXB;
	int theloai;
	char *tenSach;
	
	
	//Danh Muc Sach
	int soLuong;
	char *viTri;
	

		
	while(true){

		ds = new DAUSACH;
		
	NHAPISBN:
		printf("\nMa ISBN:");
		_isbn = InputType(6,endchar,1);
		uppercaseChar(removeSpaces(_isbn));

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
		

	NHAPTENSACH:
		printf("\nNhap ten sach:");

		tenSach = InputType(200,endchar,1);
		if (strlen(tenSach) == 0) {
			printf("Ten sach khong duoc rong!\n");
			goto NHAPTENSACH;

		}

	NHAPSOTRANG:
		printf("\nNhap so trang:");
		sotrang = atoi(InputType(10,endchar,2));
		if (sotrang == 0) {
			printf("So trang phai khac 0!\n");
			goto NHAPSOTRANG;

		}
		
		
	NHAPTACGIA:
		printf("\nNhap tac gia:");
		tenTG = InputType(100,endchar,3);
		if (strlen(tenTG) == 0) {
			printf("Ten tac gia khong duoc bo trong!\n");
			goto NHAPTACGIA;

		}
		

		
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
		

	
	NHAPTHELOAI:
		xuatTheLoai(200,200);
		printf("\nNhap the loai:");
		theloai = atoi(InputType(50,endchar,2));
		if (theloai < 0 || theloai > 8) {
			printf("The loai khong ton tai!\n");
			goto NHAPNAMXUATBAN;

		}

		printf(":%s",stringtheloai(kieutheloai(theloai)));
		

		
		if (endchar == ESC) {
			break;
		}

	
		
		//cap nhat dau sach
			strcpy(ds->ISBN, _isbn);
			
			uppercaseChar(tenSach);
			strcpy(ds->TenSach, tenSach);
			
			uppercaseChar(tenTG);
			strcpy(ds->TacGia, tenTG);	
			
			ds->SoTrang = sotrang ;			
			ds->NamXuatBan = namXB;		
	
			ds->TheLoai = theloai;
		
	//Danh muc sach
		printf("\n\n==> NHAP DANH MUC SACH <==\n\n");
		khoiTaoDMS(ds->dms);
		printf("\nNhap so luong tai ban:");
		soLuong = atoi(InputType(5,endchar,2));
		
		printf("\nNhap vi tri luu tru:");
		viTri = InputType(200,endchar,1);
		uppercaseChar(viTri);
			
		NhapVitriSLDMS(ds->dms,ds->ISBN, viTri, 0, soLuong);
	
	//cap nhat danh sach		
		if (dauSachDay(ls) == 1) {
			printf("Danh sach da day!");
			break;
		}		
		ls.soluong++;
		
		ls.nodeDS[ls.soluong] = ds;
	
	}
		
}

//void XuatDauSach(LISTDS ls) {
//	
//	for (int i = 0; i <= ls.soluong; i++) {
//		printf("\nMa ISBN: %s\n",ls.nodeDS[i]->ISBN);
//		printf("Ten sach: %s\n",ls.nodeDS[i]->TenSach);
//		printf("Tac gia: %s\n",ls.nodeDS[i]->TacGia);
//		printf("The loai: %s\n",ls.nodeDS[i]->TheLoai);
//		printf("So Trang: %d\n",ls.nodeDS[i]->SoTrang);
//		printf("Nam xuat ban: %d\n",ls.nodeDS[i]->NamXuatBan);
//		printf("\n\n==> DANH MUC SACH <==\n\n");
//		XuatDMS(ls.nodeDS[i]->dms);
//}
//}
//void docFileDAUSACH(LISTDS &ls) {
//	clrscr();
//	pDAUSACH ds ;
//	int i = 0;
//	FILE *f;
//	 if ((f = fopen("DAUSACH.bin","rb") )== NULL){
//       printf("Error! opening file");
//       exit(1);
//   }
//   
//   	while(fread(&ds, sizeof(mt), 1, f)) {
//   		
//	}
// 
//	while(fread(&mt, sizeof(mt), 1, f)) {
//		themCuoi(ls, mt);	
//	}
//	fclose(f);
//	return; 
//}

void luuFileDAUSACH(LISTDS ls) {
	clrscr();
	int i = 0;
	FILE *f;
	 if ((f = fopen("DAUSACH.bin","wb+") )== NULL){
       printf("Error! opening file");
       exit(1);
   }
 
	for(int i = 0; i <= ls.soluong; i++) {
		fwrite(&ls.nodeDS[i],sizeof(DauSach),1,f);
	}
	getch();
	fclose(f);
	return; 
}


void HienThiMenuDauSach(LISTDS &ls) {
	int choice;
	int endchar;
	char *s;
	int _theloai;
	
	do {
		for (int i = 0; i < 5; i++) {
			printf(MENU_DAUSACH[i]);
		}
	
	 	choice = atoi(InputType(1,endchar,2));

	 	switch (choice) {
	    case 1: 
	    		clrscr();
	    		NhapThemDauSach(ls);
				
				break;
	    case 2:	
	    		
	          break;
	    case 3:

	        break;
	    case 4:
	    	clrscr();
	    	xuatTheLoai(0,0);
	    	printf("Nhap the loai:");
	    	_theloai = atoi(InputType(1,endchar,2));
	    	printf("\n\n%s",stringtheloai(kieutheloai(_theloai)));

	    	XuatDauSachTheoTheLoai(taoDStheoTL(ls,_theloai));
	    	getch();
	    	break;
	    case 5:
	    	FILE *f;
			if ((f = fopen("DAUSACH.bin","wb+") )== NULL){
		       printf("Error! opening file");
		       exit(1);
		   }
	   		luuFileDAUSACH(ls);
	   		fclose(f);

	   		printf("Da luu");
	   		getch();
	         break;

	     default: printf("Wrong Choice. Enter again\n");
	     getch();
	         
	 	} 
  	clrscr(); 	
	} while (endchar != ESC);


}


int main() {
	LISTDS ls;
	khoitaoDauSach(ls);
	HienThiMenuDauSach(ls);
	//NhapThemDauSach(ls);
//	nhapDauSach(ls);
	
//	XuatDauSach(ls);
}

