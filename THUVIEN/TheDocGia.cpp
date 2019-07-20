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
	//LISTMT lsMuonTra;
	
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
	l->tdgLeft=l->tdgRight=NULL;
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
	char *maThe;
	char *ho;
	char *ten;
	char *phai;
	char *trangThai;
	TheDocGia item;
MaTheDG:	
	printf("\Nhap ma the doc gia : ");
	maThe=InputType(7,endchar,2);
	int id = atoi(maThe);
	if(endchar==ESC){
	//	break;
	}
	if(strlen(maThe)==0){
		printf("Ma the khong duoc trong");
		goto MaTheDG;
	}
	if(strcmp(maThe,"0")==0){
		//break;
	}

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
	printf("\nPhai (1:Nam-2:Nu): ");
	phai =InputType(2,endchar,2);
	int sex = atoi(phai);
	if(strlen(phai)==0){
		printf("Phai khong duoc trong");
		goto GioiTinh;
	}
	if(sex!=0||sex!=1){
		printf("Xin vui long chon 0: Nam hoac 1:Nu");
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
	if(status!=0||status!=1){
		printf("Xin vui long chon 0 hoac 1 ");
		goto TrangThaiThe;
	}
	
	item.MaThe = id;
	strcpy(item.Ho,ho);
	strcpy(item.Ten,ten);
	item.phai=sex;
	item.trangthaithe = status;
	
	return item;
}
void HienThiMenuDocGia(tree &ls) {
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
			
			getch();
	         break;
	    case 5:
	   	
	    	break;
	     default: printf("Wrong Choice. Enter again\n");
	     getch();
	         
	 	} 
  	clrscr(); 	
	} while (endchar != ESC);
}
//int main() {
//
//}
