#include "DanhSachMuonTra.cpp"

enum TrangThaiThe {
	DuocPhep = 0,
	KhongDuocPhep = 1
};

enum Phai {
	Nam = 0,
	Nu = 1
};

typedef struct TheDocGia {
	int MaThe;
	char Ho[20];
	char Ten[50];
	int phai;
	int trangthaithe;
	LISTMT lsMuonTra;
	
};


//Danh Sach THE DOC GIA - CAY NHI PHAN
typedef struct Node_THEDOCGIA {
	TheDocGia tdg;
	Node_THEDOCGIA *tdgLeft;
	Node_THEDOCGIA *tdgRight;

};

typedef struct Node_THEDOCGIA *Node_DocGiaPTR;

typedef Node_DocGiaPTR tree;

void KhoiTaoDocGia(tree &l){
	l=NULL;
}

int randomsMADG() {
	int lower = 11111, upper = 99999;
	srand(time(0)); 
	return (rand() % (upper - lower + 1)) + lower; 
	
}

int checkMADG(tree l,int maDG) {
	if (l == NULL) {
		return maDG;
	}
	
	if (maDG < l->tdg.MaThe) {
		return checkMADG(l->tdgLeft, maDG);
	} else 	if (maDG > l->tdg.MaThe) {
		return checkMADG(l->tdgRight, maDG);
	}
}


Node_DocGiaPTR newNodeDG(TheDocGia dg){
	Node_DocGiaPTR p= new Node_THEDOCGIA;
	p->tdg=dg;
	p->tdgRight=NULL;
	p->tdgLeft=NULL;
}

void ThemDG(tree &l,TheDocGia dg){
	Node_DocGiaPTR p=newNodeDG(dg);
	if(l==NULL){
		l=p;
		return;
	}
	if(dg.MaThe < l->tdg.MaThe){
		ThemDG(l->tdgLeft,dg);
	}else if(dg.MaThe > l->tdg.MaThe){
		ThemDG(l->tdgRight,dg);
	}
}



//MARK: - Thao Tac FILE
void luuFileDSDG(TheDocGia tdg, FILE *f) {

 	fwrite(&tdg,sizeof(TheDocGia), 1, f);
 	LISTMT lsmt = tdg.lsMuonTra;
	for(NodeMT_PTR p = lsmt.mtFirst; p != NULL; p = p->mtRight) {
		fwrite(&p->DSMT,sizeof(DanhSachMuonTra),1,f);
	}
	DanhSachMuonTra temp ;
	strcpy(temp.MaSach,"@@");
	fwrite(&temp,sizeof(DanhSachMuonTra),1,f);
	return; 
}


void docFileDSDG(tree &ls) {
	clrscr();
	DanhSachMuonTra mt;
	TheDocGia p;
	int i = 0;
	FILE *f;
	 if ((f = fopen("DanhSachDocGia.bin","rb") )== NULL){
       printf("Error! opening file");
       exit(1);
   }
   KhoiTaoDocGia(ls);
 	while(fread(&p,sizeof(p),1,f)){
 		if(strcmp(p.MaThe+"","@@")==0)
 			break;
 		khoiTao(p.lsMuonTra);
 		while(fread(&mt, sizeof(DanhSachMuonTra), 1, f)) {
			//NodeMT_PTR nodeMT = newNodeMT(mt);
			if(strcmp(mt.MaSach,"@@")==0){
				break;
			}
			themCuoi(p.lsMuonTra,mt);
		}
		ThemDG(ls,p);
	 }
	
	fclose(f);
	return; 
}


void DuyetLNR(tree l, FILE *f) {
	if (l != NULL){
		DuyetLNR(l->tdgLeft,f);
	//	printf("MASACH:%d", l.tdg);
		luuFileDSDG(l->tdg,f);
		DuyetLNR(l->tdgRight,f);
	}
}

void XuatDG(TheDocGia dg){
	printf("\nMa the doc gia: %d",dg.MaThe);
	printf("\nHo : %s",dg.Ho);
	printf("\nTen : %s",dg.Ten);
	switch(dg.phai){
		case Nam:
			printf("\nPhai : Nam");
			break;
		case Nu:
			printf("\Phai : Nu");
			break;
	}
	
	switch(dg.trangthaithe){
		case DuocPhep:
			printf("\nTrang thai : Duoc phep");
			break;
		case KhongDuocPhep:
			printf("\nTrang thai : Khong duoc phep");
			break;
	}
	
	printf("\n Danh sach sach muon tra");
	XuatDSMT(dg.lsMuonTra);
	
}
void XuatDSDG(tree l){
	const int STACKSIZE =500;
	Node_DocGiaPTR Stack[STACKSIZE];
	Node_DocGiaPTR p=l;
	int sp=-1;//khoi tao  stack rong
	do{
		while(p!=NULL){
			Stack[++sp] = p;
			p=p->tdgLeft;
		}
		if(sp!=-1){
			p=Stack[sp--];
			XuatDG(p->tdg);
			p=p->tdgRight;
		}
		else break;
	}while(1);
}


TheDocGia _NhapDuLieuDG(tree &l){
	int endchar;
	int maThe;
	char *ho;
	char *ten;
	char *phai;
	char *trangThai;
	int sex;
	
	LISTMT listMTDG;
	khoiTao(listMTDG);
	
	TheDocGia item;
MaTheDG:	
	maThe = checkMADG(l, randomsMADG());
	printf("\Ma the doc gia : %d", maThe);
	printf("\n");

HoDG:
	printf("\Nhap ho: ");
	ho=InputType(20,endchar,3);
	if(strlen(ho)==0){
		printf("Ho khong duoc trong");
		goto HoDG;
	}
TenDG:
	printf("\nNhap ten: ");
	ten =InputType(50,endchar,3);
	if(strlen(ten)==0){
		printf("Ten khong duoc trong");
		goto TenDG;
	}
GioiTinh:
	printf("\nPhai (Nam - Nu): ");
	phai =InputType(3,endchar,3);
	if (strcmp(phai,"Nam") == 0) {
		sex = 0;
	} else if (strcmp(phai, "Nu") == 0) {
		sex = 1;
	}
	if(strlen(phai)==0){
		printf("Phai khong duoc trong");
		goto GioiTinh;
	}
	if(strcmp(phai,"Nam") == 0 || strcmp(phai,"Nu") == 0){
		item.phai = sex;
	} else {
		printf("Xin vui long nhap Nam hoac Nu");
		goto GioiTinh;
	}
TrangThaiThe:
	printf("\nNhap trang thai the (0: the bi khoa -1: the dang hoat dong) : ");
	trangThai = InputType(2,endchar,2); 
	int status = atoi(trangThai);
	if((strlen(trangThai))==0){
		printf("Trang thai khong duoc rong");
		goto TrangThaiThe;
	}
	if(status == 0||status == 1){
		item.trangthaithe = status;

	} else {
		printf("Xin vui long chon 0 hoac 1 ");
		goto TrangThaiThe;
	}
NhapMT:
	NhapMT(listMTDG);
	item.MaThe = maThe;
	strcpy(item.Ho,ho);
	strcpy(item.Ten,ten);
	item.lsMuonTra = listMTDG;
	
	return item;
}


void NhapDSDocGia(tree &l){
	int endchar;
	int maThe;
	char *ho;
	char *ten;
	char *phai;
	char *trangThai;
	int sex;
	LISTMT listMTDG;

	while(true) {

	khoiTao(listMTDG);
	
	TheDocGia item;
MaTheDG:	
	maThe = checkMADG(l, randomsMADG());
	printf("\nMa the doc gia : %d", maThe);
	printf("\n");
	
HoDG:
	printf("\Nhap ho: ");
	ho=InputType(20,endchar,3);

	if (endchar == ESC) {
		break;
	}
	if(strlen(ho)==0){
		printf("Ho khong duoc trong");
		goto HoDG;
	}
TenDG:
	printf("\nNhap ten: ");
	ten =InputType(50,endchar,3);
	if(strlen(ten)==0){
		printf("Ten khong duoc trong");
		goto TenDG;
	}
GioiTinh:
	printf("\nPhai (Nam - Nu): ");
	phai =InputType(3,endchar,3);
	if (strcmp(phai,"Nam") == 0) {
		sex = 0;
	} else if (strcmp(phai, "Nu") == 0) {
		sex = 1;
	}
	if(strlen(phai)==0){
		printf("Phai khong duoc trong");
		goto GioiTinh;
	}
	if(strcmp(phai,"Nam") == 0 || strcmp(phai,"Nu") == 0){
		item.phai = sex;
	} else {
		printf("Xin vui long nhap Nam hoac Nu");
		goto GioiTinh;
	}
TrangThaiThe:
	printf("\nNhap trang thai the (0: the bi khoa -1: the dang hoat dong) : ");
	trangThai = InputType(2,endchar,2); 
	int status = atoi(trangThai);
	if((strlen(trangThai))==0){
		printf("Trang thai khong duoc rong");
		goto TrangThaiThe;
	}
	if(status == 0||status == 1){
		item.trangthaithe = status;

	} else {
		printf("Xin vui long chon 0 hoac 1 ");
		goto TrangThaiThe;
	}
NhapMT:
	NhapMT(listMTDG);
	item.MaThe = maThe;
	strcpy(item.Ho,ho);
	strcpy(item.Ten,ten);
	item.lsMuonTra = listMTDG;
	
	ThemDG(l, item);
	
	}
}

void HienThiMenuDocGia(tree &ls) {
	int choice;
	int endchar;
	char *s;	
	do {
		for (int i = 0; i < 5; i++) {
			printf(MENU_DMS[i]);
		}
//		gotoxy(20,20);
//		printf("ESC: Thoat");
//		gotoxy(0,1);	
	 	choice = atoi(InputType(1,endchar,2));

	 	switch (choice) {
	    case 1: 
	    		clrscr();
	    		NhapDSDocGia(ls);
				
				break;
	    case 2:	printf(MENU_DMS[1]); 
	    
	          break;
	    case 3:
	    //	MenuXoaDMS(ls);
	    	printf("\n");
	    	printf("\n");
	    	
	    	getch(); 
	        break;
	    case 4:
			printf("\n");
			XuatDSDG(ls);
			getch();
	         break;
	    case 5:
    		FILE *f;
			if ((f = fopen("DanhSachDocGia.bin","wb+") )== NULL){
		       printf("Error! opening file");
		       exit(1);
		   }
	   		DuyetLNR(ls,f);
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
	tree ls;
	KhoiTaoDocGia(ls);
	docFileDSDG(ls);
	HienThiMenuDocGia(ls);

}
