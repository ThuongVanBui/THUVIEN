#include "mylib.h"


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
typedef struct NodeDANHMUCSACH {
	DanhMucSach dms;
	NodeDANHMUCSACH *dmsNext;

};
typedef struct NodeDANHMUCSACH *NodeDANHMUCSACHPTR;

struct ListDANHMUCSACH{
	NodeDANHMUCSACHPTR dmsFirst;
	NodeDANHMUCSACHPTR dmsLast;
};
typedef struct ListDANHMUCSACH LISTDMS;


void khoiTaoDS(LISTDMS &lsDMS){
	lsDMS.dmsFirst = lsDMS.dmsLast = NULL;
}

int Rong(LISTDMS lsDMS){
	return lsDMS.dmsFirst == NULL ? 0 : 1;
}

void themDau(LISTDMS &lsDMS, DanhMucSach dms) {
	NodeDANHMUCSACHPTR p;
	p = new NodeDANHMUCSACH;
	p->dms = dms;
	p->dmsNext = NULL;
	if (Rong(lsDMS) == 0) {
		lsDMS.dmsFirst = lsDMS.dmsLast = p;
		
	} else {
		p->dmsNext = lsDMS.dmsFirst;
		lsDMS.dmsFirst = p;
		
	}
}


void NhapSach(LISTDMS &ls) {
	while(true) {
	DanhMucSach item;
	printf("Nhap ma sach:");
	scanf("%s",&item.MaSach);
	if (strcmp(item.MaSach,"0") == 0) {
		break;
	}
	printf("Nhap trang thai(0:Duoc Muon, 1:Da Duoc Muon, 2:Da Thanh Ly): ");
	scanf("%d",&item.trangthaiDMS);
	printf("Nhap vi tri:");
	scanf("%s",&item.ViTri);
	themDau(ls, item);
	};
	
}


void XuatDMS(LISTDMS ls) {
	for(NodeDANHMUCSACHPTR p = ls.dmsFirst; p != NULL; p = p->dmsNext) {
		printf("Ma sach: %s", p->dms.MaSach);
		printf("Trang thai: %d", p->dms.trangthaiDMS);
		printf("Vi tri: %s\n", p->dms.ViTri);
	}
}

int main() {
	LISTDMS ls;
	khoiTaoDS(ls);
	NhapSach(ls);
	XuatDMS(ls);
}
