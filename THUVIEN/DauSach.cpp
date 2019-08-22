#include"DanhMucSach.cpp">
#define MAXLIST 500

char MENU_DAUSACH[7][30] 		= {"1.Them dau sach",
									"2.Sua dau sach	", 
									"3.Xoa dau sach	", 
									"4.Xem theo the loai",
									"5.Luu tep",
									"6.Tim sach ",
									"7.Sap xep danh sach " };


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
	char ISBN[7];
	char TenSach[201];
	int SoTrang;
	char TacGia[101];
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
	return ls.soluong == MAXLIST ? 1 : 0;
}

int kiemTraMaISBN(LISTDS ls, char *maISBN) {
	for (int i = 0; i <= ls.soluong; i++) {
		if (strcmp(removeSpaces(ls.nodeDS[i]->ISBN),maISBN) == 0){
			return 1;
		}
	}
	return 0;
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



void quickSortDAUSACH(LISTDS &ls, int left, int right) { 
	int i, j;

	  i = left;
	  j = right;
	  pDAUSACH pDS = ls.nodeDS[(left+right)/2];
	
	  do {
	    while((strcmp(ls.nodeDS[i]->TenSach,pDS->TenSach) < 0) && (i < right)) {
	       i++;
	    }
	    while((strcmp(ls.nodeDS[j]->TenSach,pDS->TenSach) > 0) && (j > left)) {
	        j--;
	    }
	    if(i <= j) {
			swap_DS(ls.nodeDS[i], ls.nodeDS[j]);
	      	i++;
	    	j--;
	   }
	  } while(i <= j);
	
	  if(left < j) {
	     quickSortDAUSACH(ls, left, j);
	  }
	  if(i < right) {
	     quickSortDAUSACH(ls, i, right);
	  }
}

void soSachTrungTen(LISTDS ls, char *tenSachCanTim, LISTDS &newLISTDS) {
	khoitaoDauSach(newLISTDS);  
	int i = 0;  
    int last = ls.soluong;
    int cmpval;

    while(i <= last) {
        cmpval = strcmp(tenSachCanTim, ls.nodeDS[i]->TenSach);
        if(cmpval == 0){
        	newLISTDS.soluong++;
            newLISTDS.nodeDS[newLISTDS.soluong] = ls.nodeDS[i];
            printf("%s",newLISTDS.nodeDS[newLISTDS.soluong]->ISBN);
		}
		i+=1;

    }

}

pDAUSACH timkiemDauSachTheoTen(LISTDS ls,char *tenSachCanTim) {
	int first = 0;  
    int last = ls.soluong;
    int middle;
    int cmpval;

    while(first <= last) {
        middle = (first + last) / 2;
        cmpval = strcmp(tenSachCanTim, ls.nodeDS[middle]->TenSach);
        if(cmpval == 0)
            return ls.nodeDS[middle];
        else if(cmpval < 0)
            last = middle - 1;
        else
            first = middle + 1;
    }
    return NULL;
}

pDAUSACH timkiemDauSachTuanTuTheoTen(LISTDS ls,char *tenSachCanTim) {
		int l = 0 ; 
        int r = ls.soluong; 
        while (l <= r)  
        {   
	        if (strcmp(tenSachCanTim,ls.nodeDS[l]->TenSach) == 0) {
					return ls.nodeDS[l]; 
	        }
	        l++;
		}
  
        return NULL; 
}

int KiemTraMaSachTraVeViTri(LISTDS listDauSach, char *masach) {
	NodeDMS_PTR p;
	for (int i = 0; i <= listDauSach.soluong; i++) {
		p = pNodeDMS(listDauSach.nodeDS[i]->dms,masach);
		if (p != NULL) {
			return i;
		}
	}
	return -1;
}

int KiemTraISBNTraVeViTri(LISTDS listDauSach, char *isbn) {
	for (int i = 0; i <= listDauSach.soluong; i++) {
		if (strcmp(isbn,listDauSach.nodeDS[i]->ISBN) == 0) {
			return i;
		}
	}
	return -1;
}

NodeDMS_PTR KiemTraMaSach(LISTDS listDauSach, char *masach) {
	NodeDMS_PTR p;
	for (int i = 0; i <= listDauSach.soluong; i++) {
		p = pNodeDMS(listDauSach.nodeDS[i]->dms,masach);
		if (p != NULL) {
			return p;
		}
	}
	return NULL;

}

void XuatThongTinDauSach(pDAUSACH pDS) {
	clrscr();
		gotoxy(10,3);
		printf("Ma ISBN");
		gotoxy(20,3);
		printf("Ten sach");
		gotoxy(40,3);
		printf("Tac gia");
		gotoxy(60,3);
		printf("The loai");
		gotoxy(90,3);
		printf("So Trang");
		gotoxy(100,3);
		printf("Nam xuat ban");
		gotoxy(10,4);
	int y = 5;
		gotoxy(10,y);
			printf("%s",pDS->ISBN);
		gotoxy(20,y);
			printf("%s",pDS->TenSach);
		gotoxy(40,y);
			printf("%s",pDS->TacGia);
		gotoxy(60,y);
			printf("%s",stringtheloai(kieutheloai(pDS->TheLoai)));
		gotoxy(90,y);
			printf("%d",pDS->SoTrang);
		gotoxy(100,y);
			printf("%d",pDS->NamXuatBan);
	gotoxy(30,y+2);
	printf("==> DANH MUC SACH <==");
	XuatDMS_Returny(pDS->dms, y+5);
	
}

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

void XuatDauSachTheoTheLoai(LISTDS ls, char *theloai) {
	clrscr();
	
	if (strlen(theloai) != 0) {
		gotoxy(50,1);
		printf("Nhung sach thuoc the loai: %s", theloai);
	}

		gotoxy(10,3);
		printf("Ma ISBN");
		gotoxy(20,3);
		printf("Ten sach");
		gotoxy(50,3);
		printf("Tac gia");
		gotoxy(70,3);
		printf("The loai");
		gotoxy(100,3);
		printf("So Trang");
		gotoxy(110,3);
		printf("Nam xuat ban");
		gotoxy(10,4);
	int y = 5;
	for (int i = 0; i <= ls.soluong; i++) {
		gotoxy(10,y);
			printf("%s",ls.nodeDS[i]->ISBN);
		gotoxy(20,y);
			printf("%s",ls.nodeDS[i]->TenSach);
		gotoxy(50,y);
			printf("%s",ls.nodeDS[i]->TacGia);
		gotoxy(70,y);
			printf("%s",stringtheloai(kieutheloai(ls.nodeDS[i]->TheLoai)));
		gotoxy(100,y);
			printf("%d",ls.nodeDS[i]->SoTrang);
		gotoxy(110,y);
			printf("%d",ls.nodeDS[i]->NamXuatBan);
//			printf("\n\n==> DANH MUC SACH <==\n\n");
//			XuatDMS(ls.nodeDS[i]->dms);
		y+=1;
	}
}

char *MaSachDuocPhepMuon(LISTDS ls, char *tenSachCanTim) {
	pDAUSACH sachtimDuoc = timkiemDauSachTheoTen(ls,tenSachCanTim);
	if (sachtimDuoc != NULL) {
		return MaSachHopLe(sachtimDuoc->dms);
		
	}
	return "";
}

void NhapSuaDauSach(LISTDS &ls, char *ISBN, int pos) {

	//dau sach
	DAUSACH *ds;
	
	int endchar;
	char *_isbn;
	
	char *tenTG;
	int sotrang;
	int namXB;
	int theloai;
	char *tl;
	char *tenSach;
	
	
	//Danh Muc Sach
	int soLuong;
	char *viTri;
	

		
		clrscr();
		ds = new DAUSACH;
		
	NHAPISBN:
		uppercaseChar(ISBN);
		printf("\nMa ISBN:%s", ISBN);

	NHAPTENSACH:
		printf("\nNhap ten sach:");
		tenSach = InputType(200,endchar,1);
		if (strlen(tenSach) == 0) {
			printf("Ten sach khong duoc rong!\n");
			goto NHAPTENSACH;

		}
		if (endchar == ESC) {
			return;
		}

	NHAPSOTRANG:
		printf("\nNhap so trang:");
		sotrang = atoi(InputType(10,endchar,2));
		if (sotrang == 0) {
			printf("So trang phai khac 0!\n");
			goto NHAPSOTRANG;

		}
		if (endchar == ESC) {
			return;
		}		
	NHAPTACGIA:
		printf("\nNhap tac gia:");
		tenTG = InputType(100,endchar,3);
		if (strlen(tenTG) == 0) {
			printf("Ten tac gia khong duoc bo trong!\n");
			goto NHAPTACGIA;

		}
		if (endchar == ESC) {
			return;
		}
		
	NHAPNAMXUATBAN:
		printf("\nNhap nam xuat ban:");
		namXB = atoi(InputType(4,endchar,2));
		if (namXB == 0) {
			printf("Nam san xuat khong duoc bo trong!\n");
			goto NHAPNAMXUATBAN;

		}
		
		if (namXB > LayNamHT()) {
			printf("Nam san xuat khong duoc lon hon nam hien tai!\n");
			goto NHAPNAMXUATBAN;		
		}
		if (endchar == ESC) {
			return;
		}
	
	NHAPTHELOAI:
		xuatTheLoai(200,200);
		printf("\nNhap the loai:");
		tl = (InputType(1,endchar,2));
		theloai = atoi(tl);
		if (strcmp(tl,"") == 0){
			printf("The loai khong duoc bo trong!");
			goto NHAPTHELOAI;
		}
		if (theloai < 0 || theloai > 8) {
			printf("The loai khong ton tai!\n");
			goto NHAPTHELOAI;

		}  
		if (endchar == ESC) {
			return;
		}
		printf(":%s",stringtheloai(kieutheloai(theloai)));
	
		
		//cap nhat dau sach
		strcpy(ds->ISBN, ISBN);
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
	NHAPSOLUONG:
		printf("\nNhap so luong tai ban:");
		soLuong = atoi(InputType(5,endchar,2));
		if (soLuong == 0) {
			printf("\nSo luong phai khac 0!");
			goto NHAPSOLUONG;
		}
	NHAPVITRILUUTRU:	
		printf("\nNhap vi tri luu tru:");
		viTri = InputType(200,endchar,1);
		if (strcmp(viTri,"") == 0) {
			printf("\nVi tri luu tru khong duoc bo trong!");
			goto NHAPVITRILUUTRU;
		}
		uppercaseChar(viTri);
		NhapVitriSLDMS(ds->dms,ds->ISBN, viTri, 0, soLuong);
	
	//cap nhat danh sach		
		if (dauSachDay(ls) == 1) {
			printf("Danh sach da day!");
			return;
		}

		ls.nodeDS[pos] = ds;
		

		
}


void NhapThemDauSach(LISTDS &ls) {

	//dau sach
	DAUSACH *ds;
	
	int endchar;
	char *_isbn;
	
	char *tenTG;
	int sotrang;
	int namXB;
	int theloai;
	char *tl;
	char *tenSach;
	
	
	//Danh Muc Sach
	int soLuong;
	char *viTri;
	

		
	do{
		clrscr();
		ds = new DAUSACH;
		
	NHAPISBN:
		printf("\nMa ISBN:");
		_isbn = InputType(6,endchar,1);
		strcpy(_isbn,removeSpaces(_isbn));
		uppercaseChar(_isbn);
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
		tl = (InputType(1,endchar,2));
		theloai = atoi(tl);
		if (strcmp(tl,"") == 0){
			printf("The loai khong duoc bo trong!");
			goto NHAPTHELOAI;
		}
		if (theloai < 0 || theloai > 8) {
			printf("The loai khong ton tai!\n");
			goto NHAPTHELOAI;

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
	NHAPSOLUONG:
		printf("\nNhap so luong tai ban:");
		soLuong = atoi(InputType(5,endchar,2));
		if (soLuong == 0) {
			printf("\nSo luong phai khac 0!");
			goto NHAPSOLUONG;
		}
	NHAPVITRILUUTRU:	
		printf("\nNhap vi tri luu tru:");
		viTri = InputType(200,endchar,1);
		if (strcmp(viTri,"") == 0) {
			printf("\nVi tri luu tru khong duoc bo trong!");
			goto NHAPVITRILUUTRU;
		}
		uppercaseChar(viTri);
		NhapVitriSLDMS(ds->dms,ds->ISBN, viTri, 0, soLuong);
	
	//cap nhat danh sach		
		if (dauSachDay(ls) == 1) {
			printf("Danh sach da day!");
			getch();
			break;
		}		
		ls.soluong++;
		
		ls.nodeDS[ls.soluong] = ds;
	
	} while(endchar != ESC);
		
}

int Delete_DauSach(LISTDS &l, int i)
{
	if (i == l.soluong) {

		l.soluong--;
		return 1;
	}	
	
	int j;
	
	if(i < 0 || i >= l.soluong) return 0;
	for(j = i+1;  j <= l.soluong ; j++)
		l.nodeDS[j-1] = l.nodeDS[j];
	l.soluong--;
	return 1;
}

void docFileDAUSACH(LISTDS &ls) {
	DanhMucSach dms;
	pDAUSACH pds;
	
	int i = 0;
	FILE *f;
	 if ((f = fopen("DAUSACH.bin","rb") )== NULL){
       printf("Error! opening file");
       exit(1);
   }
   khoitaoDauSach(ls);
   cout<<"So luong"<<ls.soluong<<endl;
   getch();
   	
 	while(fread(pds = new DAUSACH,sizeof(DAUSACH),1,f)){
 		if(strcmp(pds->ISBN,"@@")==0){
		 	break;
		 }
		 cout<<"ISBN"<<pds->ISBN;
		 getch();
		khoiTaoDMS(pds->dms);
 		while(fread(&dms, sizeof(DanhMucSach), 1, f)) {
			//NodeMT_PTR nodeMT = newNodeMT(mt);
			if(strcmp(dms.MaSach,"@@")==0){
				break;
			}
			themCuoi(pds->dms,dms);
		}
		ls.soluong++;
		ls.nodeDS[ls.soluong] = pds;
	 }
	
	fclose(f);
	return; 
}

void luuFileDAUSACH(LISTDS lsDS, FILE *f) {
	int i = 0;
	while(i <= lsDS.soluong){
		fwrite(lsDS.nodeDS[i],sizeof(DAUSACH), 1, f);
		LISTDMS lsdms = lsDS.nodeDS[i]->dms;
		for(NodeDMS_PTR p = lsdms.dmsFirst; p != NULL; p = p->dmsNext) {
			fwrite(&p->dms,sizeof(DanhMucSach),1,f);
		}
	
		DanhMucSach temp ;
		strcpy(temp.MaSach,"@@");
		fwrite(&temp,sizeof(DanhMucSach),1,f);
		i++;
	}
}
void LuuDauSach(LISTDS lsDS,char *tenfile,char *mode){
	FILE *f = fopen(tenfile,mode);
	if(f==NULL)
		return;
	for(int i=0;i<lsDS.soluong+1;i++){
		fwrite(lsDS.nodeDS[i],sizeof(DAUSACH),1,f);
	//	cout<<"luu"<<lsDS.nodeDS[i]->ISBN;
		for(NodeDMS_PTR p = lsDS.nodeDS[i]->dms.dmsFirst;p!=NULL;p=p->dmsNext){
			fwrite(&p->dms,sizeof(DanhMucSach),1,f);
		}
		DanhMucSach temp;
		strcpy(temp.MaSach,"@@");
		fwrite(&temp,sizeof(DanhMucSach),1,f);
	}
	getch();
	fclose(f);
}
void DocDauSach(LISTDS &lsDS,char *mode,char *tenfile){
	FILE *f=fopen(tenfile,mode);
	if(f==NULL)
		return;
	fseek(f,0,SEEK_SET);
	DanhMucSach dms;
	pDAUSACH ds;
	khoitaoDauSach(lsDS);
//	cout<<"soluong "<<lsDS.soluong<<endl;
	while(fread(ds = new DAUSACH,sizeof(DAUSACH),1,f)){
		if(strcmp(ds->ISBN,"@@")==0)
			break;
		khoiTaoDMS(ds->dms);
		while(fread(&dms,sizeof(DanhMucSach),1,f)){
			if(strcmp(dms.MaSach,"@@")==0)
				break;
			//cout<<"Masach :"<<dms.MaSach<<endl;
			themCuoi(ds->dms,dms);
		}
		lsDS.nodeDS[++lsDS.soluong] = ds;
	}
	
//	getch();
	fclose(f);
}

void HienThiMenuDauSach(LISTDS &ls) {
	clrscr();
	int choice;
	int endchar;
	char *s;
	char *tenSachCanTim;
	int _theloai;
	char *_isbn;
	char *confirm;
	LISTDS lsTL;
	pDAUSACH sachTimDuoc;
	

	do {
		for (int i = 0; i < 7; i++) {
			printf("\n");
			printf(MENU_DAUSACH[i]);
		}
		printf("\nNhap chuc nang:");
	 	choice = atoi(InputType(1,endchar,2));

	 	switch (choice) {
	    case 1: 
	    		clrscr();
	    		NhapThemDauSach(ls);

				break;
	    case 2:	{
			printf("\nNhap ma ISBN ban muon sua:");
	 		_isbn = InputType(6,endchar,1);
	 		uppercaseChar(_isbn);
	 		int pos = KiemTraISBNTraVeViTri(ls,_isbn);
	 		if (pos != -1) {
	 			NhapSuaDauSach(ls,_isbn,pos);
			 }
			break;
		}

	    case 3:{
	    	NHAPSACHDEXOA:
	    	clrscr();
			printf("\nNhap ten sach ban muon xoa:");
	 		tenSachCanTim = InputType(200,endchar,1);
	 		uppercaseChar(tenSachCanTim);
	 		if (strlen(tenSachCanTim) == 0) {
	 			goto NHAPSACHDEXOA;
			}
			if (endchar == ESC) {
				break;
			}
	 		LISTDS newLSDS;
			soSachTrungTen(ls,tenSachCanTim,newLSDS);
			if (newLSDS.soluong > 0) {
				if (newLSDS.soluong == -1){
					printf("\nSach %s ban muon xoa khong ton tai!",tenSachCanTim);
				
				} else {
					XuatDauSachTheoTheLoai(newLSDS,"");
					gotoxy(30,newLSDS.soluong + 7);
					printf("\nNhap ma ISBN ban muon xoa:");
			 		_isbn = InputType(6,endchar,1);
			 		uppercaseChar(_isbn);
			 		int pos = KiemTraISBNTraVeViTri(ls,_isbn);
			 		if (pos != -1)
			 			if (demsoDMSdangduocmuon(ls.nodeDS[pos]->dms) > 0){
			 				printf("\n ===> Sach nay dang co doc gia muon, khong duoc xoa!<==");
			 				printf("\n                   ===> Xoa that bai <==");
						 }else if (Delete_DauSach(ls,pos) == 1) {
			 				printf("\n ===> Xoa thanh cong <==");
						 } else {
			 				printf("\n ===> Xoa that bai <==");
						 }
					}
				} else if (newLSDS.soluong == 0) {
					gotoxy(30,newLSDS.soluong + 7);
			 		uppercaseChar(newLSDS.nodeDS[0]->ISBN);
			 		int pos = KiemTraISBNTraVeViTri(ls,newLSDS.nodeDS[0]->ISBN);
			 			if (demsoDMSdangduocmuon(ls.nodeDS[pos]->dms) > 0){
			 				printf("\n ===> Sach nay dang co doc gia muon, khong duoc xoa!<==");
			 				printf("\n                   ===> Xoa that bai <==");
						}else if (Delete_DauSach(ls,pos) == 1) {
			
			 				printf("\n ===> Xoa thanh cong <==");
						 } else {
			 				printf("\n ===> Xoa that bai <==");
						 }
				} else {
					clrscr();
					gotoxy(30,4);
			 		printf(" ===> Hien tai khong co sach %s trong danh muc <==",tenSachCanTim);
				}
				getch();
				break;
			}			
	    case 4:
	    	clrscr();
	    	xuatTheLoai(0,0);
	    	printf("Nhap the loai:");
	    	_theloai = atoi(InputType(1,endchar,2));
	    	printf("\n\n%s",stringtheloai(kieutheloai(_theloai)));
	    	khoitaoDauSach(lsTL);
			lsTL = taoDStheoTL(ls,_theloai);
			if (lsTL.soluong == -1) {
				clrscr();
				gotoxy(40,4);
	    		printf("%s",stringtheloai(kieutheloai(_theloai)));
				gotoxy(30,5);
				printf("====> Hien tai the loai nay trong! <====");
			} else {
				quickSortDAUSACH(lsTL,0,lsTL.soluong);
				printf("%d%s",_theloai,stringtheloai(kieutheloai(_theloai)));
	    		XuatDauSachTheoTheLoai(lsTL,stringtheloai(kieutheloai(_theloai)));
			}
			
	    	getch();
	    	break;
	    case 5:
	    	FILE *f;
			if ((f = fopen("dausach2.bin","wb+") )== NULL){
		       printf("Error! opening file");
		       exit(1);
		   }
	   		//luuFileDAUSACH(ls,f);
	   		LuuDauSach(ls,"dausach2.bin","wb+");
	   		fclose(f);

	   		printf("Da luu");
	   		getch();
	         break;
		case 6:{
			clrscr();
			printf("Nhap ten sach:");
			tenSachCanTim = InputType(200,endchar,1);
			uppercaseChar(tenSachCanTim);
	 		LISTDS newLSDS;
			soSachTrungTen(ls,tenSachCanTim,newLSDS);
			if (newLSDS.soluong > 0) {
				if (newLSDS.soluong == -1){
					printf("\nSach %s ban muon xoa khong ton tai!",tenSachCanTim);
				
				} else {
					XuatDauSachTheoTheLoai(newLSDS,"");
					gotoxy(30,newLSDS.soluong + 7);
					printf("\nNhap ma ISBN ban muon xem thong tin:");
			 		_isbn = InputType(6,endchar,1);
			 		uppercaseChar(_isbn);
			 		int pos = KiemTraISBNTraVeViTri(ls,_isbn);
			 		if (pos != -1)
						XuatThongTinDauSach(ls.nodeDS[pos]);

					}
				} else if (newLSDS.soluong == 0) {
					gotoxy(30,newLSDS.soluong + 7);
			 		uppercaseChar(newLSDS.nodeDS[0]->ISBN);
			 		int pos = KiemTraISBNTraVeViTri(ls,newLSDS.nodeDS[0]->ISBN);
					XuatThongTinDauSach(newLSDS.nodeDS[0]);

				} else {
					clrscr();
					gotoxy(30,4);
			 		printf(" ===> Hien tai khong co sach %s trong danh muc <==",tenSachCanTim);
				}
			
//			sachTimDuoc = timkiemDauSachTheoTen(ls,tenSachCanTim);
//			if (sachTimDuoc != NULL) {
//				XuatThongTinDauSach(sachTimDuoc);
//
//			}else {
//				printf("Khong co sach: %s ban muon tim!",tenSachCanTim);
//			}
			getch();
			break;
		}
		case 7:
			printf("Dang sap xep....");
			Sleep(500);
			if (ls.soluong > -1){
				quickSortDAUSACH(ls,0,ls.soluong);
				XuatDauSachTheoTheLoai(ls,"");
			} else 	{
				clrscr();
				gotoxy(50,1);
				printf("Danh sach rong!");
			}

			getch();
			break;
	     default: printf("Wrong Choice. Enter again\n");
	     getch();
	         
	 	} 
  	clrscr(); 	
	} while (endchar != ESC);


}


//int main() {
//	LISTDS ls;
//	khoitaoDauSach(ls);
////	docFileDAUSACH(ls);
////	XuatDauSach(ls);
//	HienThiMenuDauSach(ls);
//	//NhapThemDauSach(ls);
////	nhapDauSach(ls);
//	
////	XuatDauSach(ls);
//}

