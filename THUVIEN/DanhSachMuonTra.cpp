#include "DauSach.cpp"

char MENU_DOCGIA[7][30] 		= {"1.Them    ","2.Nhap Sach     ","3. Sua         ","4.Xem thong tin sach     ","5.Xem DS     ","6.Luu tep     ", "7.Tim doc gia      " };

enum TrangThaiMT {
	DANGMUON = 0,
	DATRA = 1,
	LAMMAT = 2
};

typedef struct DanhSachMuonTra {
	char MaSach[21];
	NGAY_THANG NgayMuon;
	NGAY_THANG NgayTra;
	int trangthaiMT;

};


//Danh Sach MUON TRA - DANH SACH LIEN KET KEP
typedef struct NodeMT {
	DanhSachMuonTra DSMT;
	NodeMT *mtLeft;
	NodeMT *mtRight;
	
};

typedef struct NodeMT *NodeMT_PTR;

struct ListMT{
	NodeMT_PTR mtFirst;
	NodeMT_PTR mtLast;
};

typedef struct ListMT LISTMT;

int Rong(LISTMT l) {
	return l.mtFirst == NULL ? 0 : 1;
}

void khoiTaoDSMUONTRA(LISTMT &l) {
	l.mtFirst = l.mtLast = NULL;
}

NodeMT_PTR newNodeMT(DanhSachMuonTra mt) {
	NodeMT_PTR p = new NodeMT;
	p->DSMT = mt;
	p->mtLeft = NULL;
	p->mtRight = NULL;
	return p;
}

int checkMaDMS_DSMT(LISTMT ls, char *masach){
	for(NodeMT_PTR p = ls.mtFirst; p != NULL; p = p->mtRight) {
		if (strcmp(p->DSMT.MaSach, masach) == 0 && p->DSMT.trangthaiMT == 0){
			return 1;
		}
		
	}
		return 0;

}

int TraSach_DSMT(LISTMT &ls, LISTDS &LISTDauSach, char *masach, int trangthai){
	NGAY_THANG ntHT;
	LayNgayGioHT(ntHT);
	int vitriSach = KiemTraMaSachTraVeViTri(LISTDauSach,masach);
	
	for(NodeMT_PTR p = ls.mtFirst; p != NULL; p = p->mtRight) {
		if (strcmp(p->DSMT.MaSach, masach) == 0) {
			p->DSMT.trangthaiMT = trangthai;
			p->DSMT.NgayTra = ntHT;
			if (vitriSach > -1) {
				if (capNhatTrangThaiSach(LISTDauSach.nodeDS[vitriSach]->dms,trangthai,masach) == 1) {
					return 1;
				}
			
			}
			
		}
	}
	return 0;
}



int demDS(LISTMT ls){
	int dem = 0;
	for(NodeMT_PTR p = ls.mtFirst; p != NULL; p = p->mtRight) {
		dem += 1;
	}
	
	return dem;
}

int demSoSachDangMuon(LISTMT ls){
	int dem = 0;
	for(NodeMT_PTR p = ls.mtFirst; p != NULL; p = p->mtRight) {
		if (p->DSMT.trangthaiMT == 0) {
			dem += 1;

		}
	}
	
	return dem;
}



int sachQuaHan7Ngay(LISTMT ls) {
	
	for(NodeMT_PTR p = ls.mtFirst; p != NULL; p = p->mtRight) {
		if (KhoangCachNgay(p->DSMT.NgayMuon) == 7) {
			return 1;
		} else {
			return 0;
		}
	}
	
}

void themDau(LISTMT &l, DanhSachMuonTra mt) {
	NodeMT_PTR p = newNodeMT(mt);
	if (Rong(l) == 0) {
		l.mtFirst = l.mtLast = p;
		return;
	}
	
	p->mtRight = l.mtFirst;
	l.mtFirst->mtLeft = p;
	l.mtFirst = p;
	return;
}

void themCuoi(LISTMT &l, DanhSachMuonTra mt) {
	NodeMT_PTR p = newNodeMT(mt);
	if (Rong(l) == 0) {
		l.mtFirst = l.mtLast = p;
		return;		
	}
	
	l.mtLast->mtRight = p;
	p->mtLeft = l.mtLast;
	l.mtLast = p;
	return;
	
}

void themBatKiRIGHT(LISTMT &l, DanhSachMuonTra mt, int vitri) {
	NodeMT_PTR p = newNodeMT(mt);
	NodeMT_PTR q;
	int dem = 0;
	if (Rong(l) == 0 || vitri == 0) {
		themDau(l, mt);
		return;
	} if (vitri > demDS(l)) {
		themCuoi(l, mt);
		return;
	}
	
	for (NodeMT_PTR before = l.mtFirst; before != NULL; before = before->mtRight) {
		if (dem == vitri) {
			q->mtRight = p;
			p->mtLeft = q;
			p->mtRight = before;
			before->mtLeft = p;
			return;
		}
		
		q = before;
		dem += 1;

	}
	
}
void _themBatKiRight(LISTMT &l,DanhSachMuonTra mt,int vitri){
	NodeMT_PTR p =  newNodeMT(mt);// tao node can them
	NodeMT_PTR before;// node dung truoc node p;
	int dem = 1 ;// bien tim vi tri
	if(Rong(l)== 0 || vitri ==0 ){// neu ds rong hoac vi tri can them = 0->  them dau
		themDau(l,mt);
		printf("them dau\n");
		return;
	}
	if(vitri > demDS(l)|| vitri<0){// neu ma vi trí can them 0 co trong ds thi them cuoi
		themCuoi(l,mt);
		printf("them cuoi\n");
		return;
	}
	for(NodeMT_PTR k=l.mtFirst;k!=NULL;k=k->mtRight){// duyet tu dau -> cuoi ds
		if(dem==vitri){
			p->mtRight = k;// khi them node p thi k se la node sau node p
			k->mtLeft = p;// tao lk giua node sau p() va p
			
			before->mtRight = p;
			p->mtLeft = before;// tao lk giua node truoc p va p
			printf("them bat ki\n");
			return;
		}
		dem++;
		before = k;//neu khong tim thay vi tri phu hop cap nhat lai node before;
	}
}

void themBatKiLEFT(LISTMT &l, DanhSachMuonTra mt, int vitri) {
	NodeMT_PTR p = newNodeMT(mt);
	NodeMT_PTR q;
	int dem = demDS(l);
	if (Rong(l) == 0 || vitri == 0) {
		themDau(l, mt);
		return;
	} else if (vitri > demDS(l)) {
		themCuoi(l, mt);
		return;
	}
	
	for (NodeMT_PTR after = l.mtLast; after != NULL; after = after->mtLeft) {
		dem -= 1;

		if (dem == vitri) {
			p->mtRight = q;
			q->mtLeft = p;
			p->mtLeft = after;
			after->mtRight = p;

			return;
		}
		
		q = after;

	}
}



void xoaDauMT(LISTMT &ls) {
	NodeMT_PTR p = ls.mtFirst;
	if (Rong(ls) == 0) {
		printf("Danh sach rong!");
		return;
	} else {
		if (ls.mtFirst->mtRight == NULL) {
			ls.mtFirst = ls.mtLast = NULL;
			
		} else {
			p->mtRight = ls.mtFirst;
			ls.mtFirst->mtLeft = NULL;
		}
		
		delete(p);
	}
	
		

}

void NhapMTvoiMaSach(LISTMT &ls, LISTDS &listDS) {
	int c;
	int vitri;
	int endchar;
	char *trangThai;
	NGAY_THANG ngaymuon;
	NGAY_THANG ngaytra;
	int vitriDMSTrongDS;
	char *tenSachCanTim;
	char *maSachHopLe;
	NodeDMS_PTR pNODEdanhmucsach;
	
	while(true) {
		DanhSachMuonTra item;
		if (demSoSachDangMuon(ls) == 3) {
			printf("\nDoc gia da muon toi da so luong cho phep!\n Nhan phim bat ky de thoat!");
			getch();
			break;
		}
		
	NHAPTENSACH:
			printf("\nNhap ten sach: ");
			tenSachCanTim = InputType(200,endchar,1);
			uppercaseChar(tenSachCanTim);
			maSachHopLe = MaSachDuocPhepMuon(listDS,tenSachCanTim);
			if (strcmp(tenSachCanTim,"0") == 0) {
				break;
			}
			
			if (strlen(maSachHopLe) == 0) {
				printf("\nKhong co sach: %s",tenSachCanTim);
				goto NHAPTENSACH;
			}
					
			if (ls.mtFirst == NULL) {
				khoiTaoDSMUONTRA(ls);
	
			}
			
	
	NHAPMA:
		uppercaseChar(maSachHopLe);
		strcpy(item.MaSach,maSachHopLe);
		printf("\nMa sach: %s",item.MaSach);
		vitriDMSTrongDS = KiemTraMaSachTraVeViTri(listDS, maSachHopLe);

	NHAPNGAYMUON:
		LayNgayGioHT(ngaymuon);
		printf("\nNhap ngay muon (dd/MM/yyyy):%d /%d /%d", ngaymuon.ngay,ngaymuon.thang,ngaymuon.nam);
		item.NgayMuon = ngaymuon;

	NHAPNGAYTRA:
		printf("\nNhap ngay tra (dd/MM/yyyy):");
		int check1 = NhapNgayThang(ngaytra,wherex(),wherey());
		if (SoSanhNgay(ngaymuon, ngaytra) < 0) {
			goto NHAPNGAYTRA;

		}
		item.NgayTra = ngaytra;
		
	NHAPTT:
		printf("\nTrang thai sach(0:Duoc Muon, 1:Da Duoc Muon, 2:Da Thanh Ly): ");
		trangThai= InputType(1,endchar,2);
		int _trangThai = atoi(trangThai);	
		
		if(strlen(trangThai)==0){
			printf("Trang Thai khong duoc rong");
			goto NHAPTT;
		}
		if(_trangThai<0 || _trangThai>2)
		{
			printf("Xin nhap 0 hoac 1 hoac 2");
			goto NHAPTT;
		}
		item.trangthaiMT = _trangThai;
		
		themCuoi(ls,item);
		if (item.trangthaiMT == 0 && vitriDMSTrongDS != -1) {
			capnhatTrangThai(listDS.nodeDS[vitriDMSTrongDS]->dms,maSachHopLe,1);
			listDS.nodeDS[vitriDMSTrongDS]->solanmuon += 1;
		}
	};	
}


void NhapMT(LISTMT &ls, LISTDS &listDS) {
	int c;
	int vitri;
	int endchar;
	char *maSach;
	char *trangThai;
	NGAY_THANG ngaymuon;
	NGAY_THANG ngaytra;
	int vitriDMSTrongDS;
	NodeDMS_PTR pNODEdanhmucsach;
	while(true) {
		DanhSachMuonTra item;
	NHAPMA:
		printf("\nNhap ma sach:");
		maSach =InputType(20,endchar,1);
		uppercaseChar(maSach);
		if (strcmp(maSach,"0") == 0) {
			break;
		}
		if(strlen(maSach)==0){
			printf("Ma sach khong duoc rong");
			goto NHAPMA;
		}
		vitriDMSTrongDS = KiemTraMaSachTraVeViTri(listDS, maSach);
		pNODEdanhmucsach = KiemTraMaSach(listDS, maSach);
		if (pNODEdanhmucsach == NULL) {
			printf("Ma sach khong ton tai");
			goto NHAPMA;
		} 

		if (pNODEdanhmucsach->dms.trangthaiDMS != 0){
			printf("\nSach nay: %s",stringTrangThaiDMS(pNODEdanhmucsach->dms.trangthaiDMS));
			goto NHAPMA;

		}
		
		strcpy(item.MaSach,maSach);
	NHAPNGAYMUON:
		LayNgayGioHT(ngaymuon);
		printf("\nNhap ngay muon (dd/MM/yyyy):%d /%d /%d", ngaymuon.ngay,ngaymuon.thang,ngaymuon.nam);
		item.NgayMuon = ngaymuon;

	NHAPNGAYTRA:
		printf("\nNhap ngay tra (dd/MM/yyyy):");
		int check1 = NhapNgayThang(ngaytra,wherex(),wherey());
		if (SoSanhNgay(ngaymuon, ngaytra) < 0) {
			goto NHAPNGAYTRA;

		}
		item.NgayTra = ngaytra;
		
	NHAPTT:
		printf("\nTrang thai sach(0:Duoc Muon, 1:Da Duoc Muon, 2:Da Thanh Ly): ");
		trangThai= InputType(1,endchar,2);
		int _trangThai = atoi(trangThai);	
		
		if(strlen(trangThai)==0){
			printf("\nTrang Thai khong duoc rong");
			goto NHAPTT;
		}
		if(_trangThai<0 || _trangThai>2)
		{
			printf("\nXin nhap 0 hoac 1 hoac 2");
			goto NHAPTT;
		}
		item.trangthaiMT = _trangThai;
		

		
		themCuoi(ls,item);
		if (item.trangthaiMT == 0 && vitriDMSTrongDS != -1) {
			printf("%s",maSach);
			capnhatTrangThai(listDS.nodeDS[vitriDMSTrongDS]->dms,maSach,1);

		}
	};	
}


void XuatDSMT(LISTMT ls, int x, int y) {
	int y2 = y;
	gotoxy(x,y2);
	printf("Ma sach");
	gotoxy(x+20,y2);
	printf("Trang thai");
	gotoxy(x+40,y2);
	printf("Ngay muon");
	gotoxy(x+60,y2);
	printf("Ngay tra");
	
	for(NodeMT_PTR p = ls.mtFirst; p != NULL; p = p->mtRight) {
		y2+=1;
		gotoxy(x,y2);
		printf("%s",p->DSMT.MaSach);
		gotoxy(x+20,y2);
		switch (p->DSMT.trangthaiMT) {
			case DANGMUON:
				printf("Dang muon");
				break;
			case DATRA:
				printf("Da tra");
				break;

			case LAMMAT:
				printf("Lat mat");
				break;

		}
		gotoxy(x+40,y2);
		printf("%d /%d /%d", p->DSMT.NgayMuon.ngay,p->DSMT.NgayMuon.thang,p->DSMT.NgayMuon.nam);
		gotoxy(x+60,y2);
		printf("%d /%d /%d", p->DSMT.NgayTra.ngay,p->DSMT.NgayTra.thang,p->DSMT.NgayTra.nam);
	}
}


void luuFile(LISTMT ls) {
	clrscr();
	int i = 0;
	FILE *f;
	 if ((f = fopen("DanhSachMuonTra.bin","wb+") )== NULL){
       printf("Error! opening file");
       exit(1);
   }
 
	for(NodeMT_PTR p = ls.mtFirst; p != NULL; p = p->mtRight) {
		fwrite(&p->DSMT,sizeof(DanhSachMuonTra),1,f);
	}
	getch();
	fclose(f);
	return; 
}


void docFile(LISTMT &ls) {
	clrscr();
	DanhSachMuonTra mt;
	NodeMT_PTR p ;
	int i = 0;
	FILE *f;
	 if ((f = fopen("DanhSachMuonTra.bin","rb") )== NULL){
       printf("Error! opening file");
       exit(1);
   }
 
	while(fread(&mt, sizeof(mt), 1, f)) {
		themCuoi(ls, mt);	
	}
	fclose(f);
	return; 
}

//void MenuXoaDMS(LISTMT &ls){
//	clrscr();
//	int choice;
//	int endchar;
//	char *maDMS;
//	do{
//		for (int i = 0; i < 5; i++){
//			printf(MENU_XOA_DMS[i]);
//		}
//		choice = atoi(InputType(1,endchar,2));
//		switch(choice){
//		case 1:
//			xoaDau(ls);
//			break;
//		case 2:
//			xoaCuoi(ls);
//			break;
//		case 3:
//			printf("Nhap ma sach can xoa:");
//			maDMS = InputType(20, endchar,1);
//			xoaBatKi_DMS(ls,maDMS);
//			XuatDMS(ls);
//
//			break;
//		case 4:
//			xoaHet(ls);
//			XuatDMS(ls);
//			break;
//		} 
//		
//	}while(endchar != ESC);
//}

void HienThiMenu(LISTMT &ls) {
	int choice;
	int endchar;
	char *s;	
	do {
		for (int i = 0; i < 5; i++) {
			printf(MENU_DOCGIA[i]);
		}
		gotoxy(20,20);
		printf("ESC: Thoat");
		gotoxy(0,1);	
	 	choice = atoi(InputType(1,endchar,2));

	 	switch (choice) {
	    case 1: 
	    		clrscr();
	    	//	NhapMT(ls);
				break;
	    case 2:	printf(MENU_DOCGIA[1]); 
	    	//	xoaDau(ls);
	    //		xoaCuoi(ls);
	    	//	luuFile(ls);
	          break;
	    case 3:
	    //	MenuXoaDMS(ls);
	    	printf("\n");
//	    	_NhapSachTheoViTri(ls);
	    	printf("\n");
	    	XuatDSMT(ls,0,0);
	    	getch(); 
	        break;
	    case 4:
			printf("\n");
			XuatDSMT(ls,0,0); 
			getch();
	         break;
	    case 5:
	   		luuFile(ls);
	    	break;
	     default: printf("Wrong Choice. Enter again\n");
	     getch();
	         
	 	} 
  	clrscr(); 	
	} while (endchar != ESC);
}

//int main() {
//	LISTMT ls;
//	khoiTaoDSMUONTRA(LISTMT &l)ls);
//	docFile(ls);
//	HienThiMenu(ls);
//}
