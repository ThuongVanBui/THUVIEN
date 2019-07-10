#include "mylib.h"

char MENU_DMS[4][30] 		= {"1.Them    ","2.Xoa     ","3.Sua     ","4.Xem DS  " };

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


void NhapSach(LISTDMS &ls, char *s) {
	int c;
	int vitri;
	int endchar;
	while(true) {
		DanhMucSach item;
		clrscr();
		printf("Nhap ma sach:");
	NHAPMA:
	//	c = getch();
	//	if ( ( c >= 'A' && c <= 'Z') || ( c >='a' && c <= 'z' ) ) {
	//		scanf("%s",&item.MaSach);
	//
	//	} else {
	//		goto NHAPMA;
	// 
	//		
	//	}
		strcpy(item.MaSach,InputNormal(5,endchar,1));
		if (strcmp(item.MaSach,"0") == 0) {
			break;
		}	
	NHAPTT:
		printf("\nNhap trang thai(0:Duoc Muon, 1:Da Duoc Muon, 2:Da Thanh Ly): ");		
		item.trangthaiDMS= atoi(InputNormal(5,endchar,2));		
	NHAPVITRI:
		printf("\nNhap vi tri:");
		strcpy(item.ViTri,InputNormal(5,endchar,1));
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


void HienThiMenu(LISTDMS &ls) {
	int choice;
	char *s;	
	do {
		for (int i = 0; i < 4; i++) {
			printf(MENU_DMS[i]);
		}	
	 	scanf("%d",&choice);
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
			XuatDMS(ls); 
			getch();
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
