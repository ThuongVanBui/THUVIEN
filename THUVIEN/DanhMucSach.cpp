#include "mylib.h"

char MENU_DMS[5][30] 		= {"1.Them    ","2.Xoa     ","3.Sua     ","4.Xem DS     ","5.Luu tep     " };
char MENU_XOA_DMS[4][30] 		= {"1.Xoa Dau    ","2.Xoa Cuoi    ","3.Xoa Bat Ki     ","4.Xoa Het     " };

enum TrangThaiDMS {
	DUOCMUON = 0,
	DADUOCMUON = 1,
	DATHANHLY = 2
};

typedef struct DanhMucSach {
	char MaSach[20];
	int trangthaiDMS;
	char ViTri[50];
	
};

//Danh Sach SACH - DANH SACH LIEN DON
typedef struct NodeDMS {
	DanhMucSach dms;
	NodeDMS *dmsNext;

};
typedef struct NodeDMS *NodeDMS_PTR;

struct ListDMS{
	NodeDMS_PTR dmsFirst;
	NodeDMS_PTR dmsLast;
};
typedef struct ListDMS LISTDMS;


void khoiTaoDS(LISTDMS &lsDMS){
	lsDMS.dmsFirst = lsDMS.dmsLast = NULL;
}

int Rong(LISTDMS lsDMS){
	return lsDMS.dmsFirst == NULL ? 0 : 1;
}

NodeDMS_PTR NewNode_DMS(DanhMucSach dm){
	NodeDMS_PTR p= new NodeDMS;
	p->dms=dm;
	p->dmsNext=NULL;
	return p;
}


int checkMaDMS(LISTDMS ls, char masach[]){
	for(NodeDMS_PTR p = ls.dmsFirst; p != NULL; p = p->dmsNext) {
		if (strcmp(p->dms.MaSach, masach) == 0){
			return 1;
		}else{
			return 0;
		}
	}
}

void themDau(LISTDMS &lsDMS, DanhMucSach dms) {
	NodeDMS_PTR p;
	p = NewNode_DMS(dms);

	if (Rong(lsDMS) == 0) {
		lsDMS.dmsFirst = lsDMS.dmsLast = p;
		
	} else {
		p->dmsNext = lsDMS.dmsFirst;
		lsDMS.dmsFirst = p;
		
	}
}
void themCuoi(LISTDMS &lsDMS,DanhMucSach dms){
	NodeDMS_PTR p = NewNode_DMS(dms);
	if(Rong(lsDMS)==0){
		lsDMS.dmsFirst = lsDMS.dmsLast = p;
	}else{
		lsDMS.dmsLast->dmsNext=p;
		lsDMS.dmsLast = p;
	}
}
void ThemSauNode(LISTDMS &lsDMS,DanhMucSach dms,char *masach_node_truoc){
	NodeDMS_PTR info= NewNode_DMS(dms);
	for(NodeDMS_PTR p=lsDMS.dmsFirst;p!=NULL;p=p->dmsNext){
		if(strcmp(p->dms.MaSach,masach_node_truoc)==0){
			info->dmsNext=p->dmsNext->dmsNext;
			p->dmsNext=info;
		}
	}
}
void xoaDau(LISTDMS &lsDMS){
	if(Rong(lsDMS)==0){
		return;
	}
	NodeDMS_PTR p = lsDMS.dmsFirst;
	lsDMS.dmsFirst=lsDMS.dmsFirst->dmsNext;
	delete p;
	
}
void xoaCuoi(LISTDMS &lsDMS){
	if(Rong(lsDMS)==0){
		return;
	}
	if(strcmp(lsDMS.dmsFirst->dms.MaSach,lsDMS.dmsLast->dms.MaSach)==0){
		lsDMS.dmsFirst=lsDMS.dmsLast=NULL;
		return;
	}
	for(NodeDMS_PTR  p=lsDMS.dmsFirst;p!=NULL;p=p->dmsNext){
		if(strcmp(p->dmsNext->dms.MaSach,lsDMS.dmsLast->dms.MaSach)==0){
			NodeDMS_PTR _delete  = p->dmsNext;
			delete _delete;
			lsDMS.dmsLast = p;
			return;
		}
	}
}

void xoaBatKi_DMS(LISTDMS &ls, char *MaDMS ) {
	if (Rong(ls) == 0) {
		return;
	}
	NodeDMS_PTR q;
	
	for (NodeDMS_PTR p = ls.dmsFirst; p != NULL; p = p->dmsNext) {
		if (strcmp(p->dms.MaSach,MaDMS) == 0) {
			if (strcmp(p->dms.MaSach,ls.dmsFirst->dms.MaSach) == 0) {
				xoaDau(ls);
				return;
			};
			q->dmsNext = p->dmsNext;
			delete(p);
			return;
		}
		q = p;
	}
	
}

void xoaHet(LISTDMS &ls) {
	if (Rong(ls) == 0) {
		return;
	}
	
	ls.dmsFirst = ls.dmsLast = NULL;

}

void NhapDMSach(LISTDMS &ls, char *maISBN) {
	int c;
	int vitri;
	int endchar;
	int stt = 0;
	char *maSach;
	char *trangThai;
	char *viTri;
	while(true) {
		DanhMucSach item;
	//	clrscr();	
	NHAPMA:
		printf("\nNhap ma sach:");
		stt += 1;
		char buffer[20];
		maSach = maISBN ;
		strcat(maSach,itoa(stt,buffer,10));
		if(strlen(maSach)==0){
			printf("Ma sach khong duoc rong");
			goto NHAPMA;
		}
		if (checkMaDMS(ls, maSach) == 1) {
		//	printf("Ma sach trung");
			goto NHAPMA;
		}
		
		if (strcmp(maSach,"0") == 0) {
			break;
		}
		printf("%s",maSach);
		strcpy(item.MaSach,maSach);	
	NHAPTT:
		printf("\nNhap trang thai(0:Duoc Muon, 1:Da Duoc Muon, 2:Da Thanh Ly): ");		
		trangThai= InputType(1,endchar,2);
		int _trangThai = atoi(trangThai);	
		if (endchar == ESC) {
			break;
		}
		if(strlen(trangThai)==0){
			printf("Trang Thai khong duoc rong");
			goto NHAPTT;
		}
		if(_trangThai<0 || _trangThai>2)
		{
			printf("Xin nhap 0 hoac 1 hoac 2");
			goto NHAPTT;
		}
		item.trangthaiDMS = _trangThai;
	NHAPVITRI:
		printf("\nNhap vi tri:");
		viTri = InputType(51,endchar,1);
		if(strlen(viTri)==0){
			printf("Vi Tri khong duoc rong");
			goto NHAPVITRI;
		}
		strcpy(item.ViTri,viTri);
		
	themDau(ls, item);	
	};	
}


void XuatDMS(LISTDMS ls) {
	for(NodeDMS_PTR p = ls.dmsFirst; p != NULL; p = p->dmsNext) {
		printf("\nMa sach: %s", p->dms.MaSach);
		switch (p->dms.trangthaiDMS) {
			case DUOCMUON:
				printf("\nTrang thai: Duoc muon");
				break;
			case DADUOCMUON:
				printf("\nTrang thai: Da muon");
				break;

			case DATHANHLY:
				printf("\nTrang thai: Da thanh ly");
				break;

		}
		printf("\nVi tri: %s\n", p->dms.ViTri);
	}
}


void luuFile(LISTDMS ls) {
	clrscr();
	int i = 0;
	FILE *f;
	 if ((f = fopen("DANHMUCSACH.bin","wb+") )== NULL){
       printf("Error! opening file");
       exit(1);
   }
 
	for(NodeDMS_PTR p = ls.dmsFirst; p != NULL; p = p->dmsNext) {
		fwrite(&p->dms,sizeof(DanhMucSach),1,f);
	}
	getch();
	fclose(f);
	return; 
}


void docFile(LISTDMS &ls) {
	clrscr();
	DanhMucSach dms;
	NodeDMS_PTR p ;
	int i = 0;
	FILE *f;
	 if ((f = fopen("DANHMUCSACH.bin","rb") )== NULL){
       printf("Error! opening file");
       exit(1);
   }
 
	while(fread(&dms, sizeof(dms), 1, f)) {
		themDau(ls, dms);	
	}
	fclose(f);
	return; 
}


void MenuXoaDMS(LISTDMS &ls){
	clrscr();
	int choice;
	int endchar;
	char *maDMS;
	do{
		for (int i = 0; i < 5; i++){
			printf(MENU_XOA_DMS[i]);
		}
		choice = atoi(InputType(1,endchar,2));
		switch(choice){
		case 1:
			xoaDau(ls);
			break;
		case 2:
			xoaCuoi(ls);
			break;
		case 3:
			printf("Nhap ma sach can xoa:");
			maDMS = InputType(20, endchar,1);
			xoaBatKi_DMS(ls,maDMS);
			XuatDMS(ls);

			break;
		case 4:
			xoaHet(ls);
			XuatDMS(ls);
			break;
		} 
		
	}while(endchar != ESC);
}

void HienThiMenu(LISTDMS &ls) {
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
	    		NhapDMSach(ls,s);
				break;
	    case 2:	printf(MENU_DMS[1]); 
	    	//	xoaDau(ls);
	    		xoaCuoi(ls);
	    	//	luuFile(ls);
	          break;
	    case 3:
	    	MenuXoaDMS(ls);
	        break;
	    case 4:
			printf("\n");
			XuatDMS(ls); 
			getch();
	         break;
	    case 5:
	    	luuFile(ls);
	    	break;
	     default: 
		 	luuFile(ls);
		 printf("Wrong Choice. Enter again\n");
	     getch();
	         break;
	 	} 
  	clrscr();
	} while (endchar != ESC);
}



//
//int main() {
//	LISTDMS ls;
//	khoiTaoDS(ls);
//	docFile(ls);
//	HienThiMenu(ls);
//}
