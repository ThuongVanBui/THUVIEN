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

}DanhSachMuonTra;


//Danh Sach MUON TRA - DANH SACH LIEN KET KEP
typedef struct MUONTRA {
	DanhSachMuonTra DSMT;
	MUONTRA *mtLeft;
	MUONTRA *mtRight;
	
}MUONTRA;

typedef struct MUONTRA *MUONTRAPTR;
MUONTRAPTR mtFirst, mtLast;

//int main() {
//	
//}
