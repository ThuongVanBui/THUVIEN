#include "DanhSachMuonTra.cpp"

enum TrangThaiThe {
	KhongDuocPhep = 0,
	DuocPhep = 1
};

enum Phai {
	Nam = 0,
	Nu = 1
};

int index = 0;

struct TenHo
{
	string HoTen;
	int MaThe;
};
typedef struct TenHo TEN_HO;

typedef struct TheDocGia {
	int MaThe;
	char Ho[50];
	char Ten[70];
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



Node_THEDOCGIA* timDG(tree ls, int maTDG)
{
    if (ls == NULL)
        return NULL;
 
	if (ls->tdg.MaThe == maTDG)
	{
		return ls;
	}
	if (ls->tdg.MaThe > maTDG)
	{
		timDG(ls->tdgLeft, maTDG);
	}
	else
	{
		timDG(ls->tdgRight, maTDG);
	}
}

TheDocGia LeftMostValue( tree root )
{
    while ( root->tdgLeft != NULL )
        root = root->tdgLeft;
    return root->tdg;
}


Node_THEDOCGIA* XoaDG( tree &root, int maTDG )
{
    if ( root == NULL )
        return root;
    if ( maTDG < root->tdg.MaThe )
        root->tdgLeft = XoaDG( root->tdgLeft, maTDG );
    else if ( maTDG > root->tdg.MaThe )
        root->tdgRight = XoaDG( root->tdgRight, maTDG );
    else
    {
        // root->data == value, delete this node
        if ( root->tdgLeft == NULL )
        {
            Node_THEDOCGIA* newRoot = root->tdgRight;
            free( root );
            return newRoot;
        }
        if ( root->tdgRight == NULL )
        {
            Node_THEDOCGIA* newRoot = root->tdgLeft;
            free( root );
            return newRoot;
        }
        root->tdg = LeftMostValue( root->tdgRight );
        root->tdgRight = XoaDG( root->tdgRight, root->tdg.MaThe );
    }
    return root;
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
 		khoiTaoDSMUONTRA(p.lsMuonTra);
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
	uppercaseChar(dg.Ho);
	printf("\nHo : %s",dg.Ho);
	uppercaseChar(dg.Ten);
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
			printf("\nTrang thai : Duoc phep\n");
			break;
		case KhongDuocPhep:
			printf("\nTrang thai : Khong duoc phep\n");
			break;
	}
	if (dg.lsMuonTra.mtFirst != NULL){
		printf("\n Danh sach sach muon tra");
		XuatDSMT(dg.lsMuonTra);
	}

	
}

void XuatDGTheoStt(TheDocGia dg){
	printf("\nMa the doc gia: %d",dg.MaThe);
	uppercaseChar(dg.Ho);
	uppercaseChar(dg.Ten);
	printf("\nHo Ten: %s %s",dg.Ho,dg.Ten);
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
			printf("\nTrang thai : Duoc phep\n");
			break;
		case KhongDuocPhep:
			printf("\nTrang thai : Khong duoc phep\n");
			break;
	}
	if (dg.lsMuonTra.mtFirst != NULL){
		printf("\n Danh sach sach muon tra");
		XuatDSMT(dg.lsMuonTra);
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
	int maThe;
	char *ho;
	char *ten;
	char *phai;
	char *trangThai;
	int sex;
	
	LISTMT listMTDG;
	khoiTaoDSMUONTRA(listMTDG);
	
	TheDocGia item;
MaTheDG:	
	maThe = checkMADG(l, randomsMADG());
	printf("\Ma the doc gia : %d", maThe);
	printf("\n");

HoDG:
	printf("\Nhap ho: ");
	ho=InputType(40,endchar,3);
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
	printf("\nNhap trang thai the (0: the bi khoa, 1: the dang hoat dong): ");
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

	khoiTaoDSMUONTRA(listMTDG);
	
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
	printf("\nPhai (0:Nam - 1:Nu): ");
	phai =InputType(1,endchar,2);
	if (strcmp(phai,"0") == 0) {
		sex = 0;
	} else if (strcmp(phai, "1") == 0) {
		sex = 1;
	}
	if(strlen(phai)==0){
		printf("Phai khong duoc trong");
		goto GioiTinh;
	}
	if(strcmp(phai,"0") == 0 || strcmp(phai,"1") == 0){
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
//NhapMT:
//	NhapMT(listMTDG);
	item.MaThe = maThe;
	strcpy(item.Ho,ho);
	strcpy(item.Ten,ten);
	uppercaseChar(item.Ho);
	uppercaseChar(item.Ten);

	
	item.lsMuonTra = listMTDG;
	
	ThemDG(l, item);
	
	}
}

int countDG(tree ls)
{
	int c = 1;             // ban than node duoc dem la 1;
	if (ls == NULL)
		return 0;
	else
	{
		c += countDG(ls->tdgLeft);
		c += countDG(ls->tdgRight);
		return c;
	}
}

string Get_TenHO(TheDocGia dg)
{
	string token;
	string hoten;
	strcat(dg.Ten," ");
	strcat(dg.Ten,dg.Ho);
	
	token = dg.Ten ;

	hoten = token;
	return hoten;
}



void Create_ArrTenHo(tree ls, TEN_HO* arr)
{
	if (ls == NULL)
		return;
	Create_ArrTenHo(ls->tdgLeft, arr); // visit left subtree
	arr[index].HoTen = toUpper(Get_TenHO(ls->tdg));
///	cout<<Get_TenHO(ls->tdg)<<endl;
	arr[index++].MaThe = ls->tdg.MaThe;
	Create_ArrTenHo(ls->tdgRight, arr);// visti right subtree
}

void Swap_TenHo(TEN_HO &a, TEN_HO &b)
{
	TEN_HO temp;
	temp = a;
	a = b;
	b = temp;
}

void Swap_NodeTree(TEN_HO &a, TEN_HO &b)
{
	TEN_HO temp;
	temp = a;
	a = b;
	b = temp;
}
void QuicKsort_ARRTenHo(TEN_HO *th, int left, int right)
{
	TEN_HO key = th[(left + right) / 2];
	int i = left, j = right;
	do {
		while (th[i].HoTen < key.HoTen)
			i++;
		while (th[j].HoTen > key.HoTen)
			j--;
		if (i <= j) {
			Swap_TenHo(th[i], th[j]);
			i++;
			j--;
		}
	} while (i <= j);
	if (left < j) QuicKsort_ARRTenHo(th, left, j);
	if ( i < right) QuicKsort_ARRTenHo(th, i, right);
}




void DuyetLNR(tree ls) {
	if (ls != NULL)
	{
		DuyetLNR(ls->tdgLeft);
		XuatDG(ls->tdg);
		DuyetLNR(ls->tdgRight);
	}

	
}

void XuatDanhSachTheoSTT(tree ls) {
	if (ls != NULL)
	{
		XuatDanhSachTheoSTT(ls->tdgLeft);
		XuatDGTheoStt(ls->tdg);
		XuatDanhSachTheoSTT(ls->tdgRight);
	}

	
}

//void xuatTENHO(tree ls,TEN_HO *arr) {
//	
//	for(int i = 0; i < countDG(ls); i++) {
//		printf("%s",arr[i].HoTen);
//	}
//
//}

char MENU_DSDG[3][30] 		= {"1.Sap xep theo ten    ","2.Sap xep theo stt     ","ESC: Thoat     " };

void menuXemDanhSachDG(tree ls) {
	int choice;
	int endchar;
	do {
		for (int i = 0; i < 3;  i++) {
			printf(MENU_DSDG[i]);
		}
		choice = atoi(InputType(1,endchar,2));
		
		switch (choice) {
			case 1: {
				index =  0;
				int nDG = countDG(ls);
				TEN_HO* ArrTenHo = new TEN_HO[nDG];
				Create_ArrTenHo(ls, ArrTenHo);
				QuicKsort_ARRTenHo(ArrTenHo, 0, nDG - 1);
				for(int i = 0; i < nDG; i++) {
					cout<<ArrTenHo[i].MaThe<< "        ";
					cout<<ArrTenHo[i].HoTen<<endl;
				}

				break;
				}
			case 2:
				XuatDanhSachTheoSTT(ls);
				break;
		}
		
	}while(endchar != ESC);
	
}

void HienThiMenuDocGia(tree &ls) {
	int choice;
	int endchar;
	char *s;
	int maTDG;
	Node_DocGiaPTR nodeDG;
	LISTDS lsDauSach;

	do {
		for (int i = 0; i < 7; i++) {
			printf(MENU_DOCGIA[i]);
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
	    case 2:	printf("\nNhap Dau Sach\n"); 
				khoitaoDauSach(lsDauSach);
				HienThiMenuDauSach(lsDauSach);

	          break;
	    case 3:
	    //	MenuXoaDMS(ls);
	    	printf("\n");
	    	printf("\nNhap ma so the DG:");
	    	maTDG = atoi(InputType(6,endchar,2));
	    	XuatDG(timDG(ls,maTDG)->tdg);
	    	getch(); 
	        break;
	    case 4:
	    	break;
	    case 5:
			printf("\n");
//			XuatDSDG(ls);
			menuXemDanhSachDG(ls);
			getch();
	         break;
	    case 6:
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
	    case 7:
	    	printf("Nhap ma the doc gia:");
	    	maTDG = atoi(InputType(6,endchar,2));
	    	nodeDG = timDG(ls,maTDG);
	    	XuatDG(nodeDG->tdg);
	    	if (demSoSachDangMuon(nodeDG->tdg.lsMuonTra) == 3) {
				printf("Doc gia da muon toi da so luong cho phep!");
			} else if (sachQuaHan7Ngay(nodeDG->tdg.lsMuonTra) == 1) {
				printf("Doc gia khong muon vi da giu sach qua 7 ngay!");
				
			} else {
				
				khoiTaoDSMUONTRA(nodeDG->tdg.lsMuonTra);
				NhapMT(nodeDG->tdg.lsMuonTra);
			}
	    	
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
