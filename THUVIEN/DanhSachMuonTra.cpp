#include "mylib.h"

char MENU_DMS[5][30] 		= {"1.Them    ","2.Xoa     ","3.Them item theo vi tri     ","4.Xem DS     ","5.Luu tep     " };

enum TrangThaiMT {
	DANGMUON = 0,
	DATRA = 1,
	LAMMAT = 2
};

typedef struct DanhSachMuonTra {
	char MaSach[20];
	char NgayMuon[11];
	char NgayTra[11];
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

void khoiTao(LISTMT &l) {
	l.mtFirst = l.mtLast = NULL;
}

NodeMT_PTR newNodeMT(DanhSachMuonTra mt) {
	NodeMT_PTR p = new NodeMT;
	p->DSMT = mt;
	p->mtLeft = NULL;
	p->mtRight = NULL;
	return p;
}

int checkMaDMS(LISTMT ls, char *masach){
	for(NodeMT_PTR p = ls.mtFirst; p != NULL; p = p->mtRight) {
		if (strcmp(p->DSMT.MaSach, masach) == 0){
			return 1;
		}else{
			return 0;
		}
	}
}

int demDS(LISTMT ls){
	int dem = 0;
	for(NodeMT_PTR p = ls.mtFirst; p != NULL; p = p->mtRight) {
		dem += 1;
	}
	
	return dem;
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


DanhSachMuonTra _NhapDuLieuSach(LISTMT &ls){
	int endchar;
	char *maSach;
	char *trangThai;
	char *NgayMuon;
	
	DanhSachMuonTra item;
		clrscr();	
	NHAPMA:
		printf("\nNhap ma sach:");
		maSach =InputType(20,endchar,1);
		if(strlen(maSach)==0){
			printf("Ma sach khong duoc rong");
			goto NHAPMA;
		}
		if (checkMaDMS(ls, maSach) == 1) {
			printf("Ma sach trung");
			goto NHAPMA;
		}
		
		if (strcmp(maSach,"0") == 0) {
			//break;
		}
		strcpy(item.MaSach,maSach);
	NHAPNGAYMUON:
		printf("\nNhap ngay muon (dd/MM/yyyy):");
		NgayMuon = InputType(11,endchar,1);
		if(strlen(NgayMuon)==0){
			printf("Ngay muon khong duoc rong");
			goto NHAPNGAYMUON;
		}
		strcpy(item.NgayMuon,NgayMuon);
	NHAPNGAYTRA:
		printf("\nNhap ngay muon (dd/MM/yyyy):");
		NgayMuon = InputType(11,endchar,1);
		if(strlen(NgayMuon)==0){
			printf("Ngay tra khong duoc rong");
			goto NHAPNGAYTRA;
		}
		strcpy(item.NgayTra,NgayMuon);		
	NHAPTT:
		printf("\nNhap trang thai(0:Duoc Muon, 1:Da Duoc Muon, 2:Da Thanh Ly): ");		
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
		
	return item;
}
void _NhapSachTheoViTri(LISTMT &l){
	int endchar;
	printf("\nNhap du lieu sach: \n");
	DanhSachMuonTra item= _NhapDuLieuSach(l);
	printf("\nXin nhap vi tri can them: ");
	char *pos = InputType(3,endchar,2);
	printf("%s",pos);
	printf("\n");
	_themBatKiRight(l,item,atoi(pos));
	getch();
}
void NhapMT(LISTMT &ls) {
	int c;
	int vitri;
	int endchar;
	char *maSach;
	char *trangThai;
	char *NgayMuon;
	while(true) {
		DanhSachMuonTra item;
	NHAPMA:
		printf("\nNhap ma sach:");
		maSach =InputType(20,endchar,1);
		if(strlen(maSach)==0){
			printf("Ma sach khong duoc rong");
			goto NHAPMA;
		}
		if (checkMaDMS(ls, maSach) == 1) {
			printf("Ma sach trung");
			goto NHAPMA;
		}
		
		if (strcmp(maSach,"0") == 0) {
			break;
		}
		strcpy(item.MaSach,maSach);
	NHAPNGAYMUON:
		printf("\nNhap ngay muon (dd/MM/yyyy):");
		NgayMuon = InputType(11,endchar,1);
		if(strlen(NgayMuon)==0){
			printf("Ngay muon khong duoc rong");
			goto NHAPNGAYMUON;
		}
		strcpy(item.NgayMuon,NgayMuon);
	NHAPNGAYTRA:
		printf("\nNhap ngay muon (dd/MM/yyyy):");
		NgayMuon = InputType(11,endchar,1);
		if(strlen(NgayMuon)==0){
			printf("Ngay tra khong duoc rong");
			goto NHAPNGAYTRA;
		}
		strcpy(item.NgayTra,NgayMuon);		
	NHAPTT:
		printf("\nNhap trang thai(0:Duoc Muon, 1:Da Duoc Muon, 2:Da Thanh Ly): ");		
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

		themDau(ls,item);
	};	
}


void XuatDSMT(LISTMT ls) {
	for(NodeMT_PTR p = ls.mtFirst; p != NULL; p = p->mtRight) {
		printf("\nMa sach: %s", p->DSMT.MaSach);
		switch (p->DSMT.trangthaiMT) {
			case DANGMUON:
				printf("\nTrang thai: Dang muon");
				break;
			case DATRA:
				printf("\nTrang thai: Da tra");
				break;

			case LAMMAT:
				printf("\nTrang thai: Lat mat");
				break;

		}
		printf("\nNgay muon: %s", p->DSMT.NgayMuon);
		printf("\nNgay tra: %s", p->DSMT.NgayTra);
		printf("\n");
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
			printf(MENU_DMS[i]);
		}
		gotoxy(20,20);
		printf("ESC: Thoat");
		gotoxy(0,1);	
	 	choice = atoi(InputType(1,endchar,2));

	 	switch (choice) {
	    case 1: 
	    		clrscr();
	    		NhapMT(ls);
				break;
	    case 2:	printf(MENU_DMS[1]); 
	    	//	xoaDau(ls);
	    //		xoaCuoi(ls);
	    	//	luuFile(ls);
	          break;
	    case 3:
	    //	MenuXoaDMS(ls);
	    	printf("\n");
	    	_NhapSachTheoViTri(ls);
	    	printf("\n");
	    	XuatDSMT(ls);
	    	getch(); 
	        break;
	    case 4:
			printf("\n");
			XuatDSMT(ls); 
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
//	khoiTao(ls);
//	docFile(ls);
//	HienThiMenu(ls);
//}
