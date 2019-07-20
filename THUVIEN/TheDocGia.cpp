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

typedef struct DSDocGia {
	Node_DocGiaPTR dgHead;
	Node_DocGiaPTR dgTail;	
};

typedef struct DSDocGia DSDOCGIA;
DSDOCGIA.dgHead tree = NULL;
DSDOCGIA.dgTail tree = NULL;

//int main() {
//
//}
