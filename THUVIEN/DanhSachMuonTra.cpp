#include "mylib.h"

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
	
}

void themDau(LISTMT &l, DanhSachMuonTra mt) {
	
}

int main() {
	
}
