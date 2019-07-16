#include "mylib.h"

char MENU_DMS[5][30] 		= {"1.Them    ","2.Xoa     ","3.Sua     ","4.Xem DS     ","5.Luu tep     " };

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

void themDau(LISTDMS &lsDMS, DanhMucSach dms) {
	NodeDMS_PTR p;
	p = new NodeDMS;
	p->dms = dms;
	p->dmsNext = NULL;
	
	if (Rong(lsDMS) == 0) {
		lsDMS.dmsFirst = lsDMS.dmsLast = p;
		
	} else {
		p->dmsNext = lsDMS.dmsFirst;
		lsDMS.dmsFirst = p;
		
	}
}
void themSau(LISTDMS &lsDMS,DanhMucSach dms){
	NodeDMS_PTR p = NewNode_DMS(dms);
	if(Rong(lsDMS)==0){
		lsDMS.dmsFirst = lsDMS.dmsLast = p;
	}else{
		lsDMS.dmsLast->dmsNext=p;
		lsDMS.dmsLast = p;
	}
}


void NhapSach(LISTDMS &ls, char *s) {
	int c;
	int vitri;
	int endchar;
	char *trangThai;
	while(true) {
		DanhMucSach item;
		clrscr();
		printf("Nhap ma sach:");
	NHAPMA:
		strcpy(item.MaSach,InputType(20,endchar,1));
		if (strcmp(item.MaSach,"0") == 0) {
			break;
		}	
	NHAPTT:
		printf("\nNhap trang thai(0:Duoc Muon, 1:Da Duoc Muon, 2:Da Thanh Ly): ");		
		trangThai= (InputType(1,endchar,2));	
		if(strlen(trangThai)==0)
			goto NHAPTT;
		item.trangthaiDMS = atoi(trangThai);
	NHAPVITRI:
		printf("\nNhap vi tri:");
		strcpy(item.ViTri,InputType(51,endchar,1));
	themDau(ls, item);	
	};	
}


void XuatDMS(LISTDMS ls) {
	for(NodeDMS_PTR p = ls.dmsFirst; p != NULL; p = p->dmsNext) {
		printf("\nMa sach: %s", p->dms.MaSach);
		printf("\nTrang thai: %d", p->dms.trangthaiDMS);
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
//		fwrite(&p->dms.MaSach, sizeof(p->dms.MaSach), 1, f); 
//		fwrite(&p->dms.trangthaiDMS, sizeof(p->dms.trangthaiDMS), 1, f); 
//		fwrite(&p->dms.ViTri, sizeof(p->dms.ViTri), 1, f); 
		fwrite(&p->dms,sizeof(DanhMucSach),1,f);
	}
	getch();
	fclose(f);
	return; 
}


void docFile(LISTDMS &ls) {
	clrscr();
	khoiTaoDS(ls);
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
	    		NhapSach(ls, s);
				break;
	    case 2:	printf(MENU_DMS[1]); 
	          break;
	    case 3: printf(MENU_DMS[2]); 
	         break;
	    case 4://printf(MENU_DMS[3]);
			
			printf("\n");
			docFile(ls);
			printf("\n");
			XuatDMS(ls); 
			getch();
	         break;
	    case 5:
	    	luuFile(ls);
	    	break;
	     default: printf("Wrong Choice. Enter again\n");
	         break;
	 	} 
  	clrscr();
	} while (choice != 0);
}

int main() {
	LISTDMS ls;
	khoiTaoDS(ls);
//	XuatDMS(ls);
	HienThiMenu(ls);
}
