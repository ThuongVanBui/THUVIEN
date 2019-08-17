#include "DanhSachMuonTra.cpp"


char MENU_MUONTRASACH[3][30] 		= {	"1.Muon sach    ",
										"2.Tra sach     ",
										"ESC: Thoat     "
										};
enum TrangThaiThe {
	KhongDuocPhep = 0,
	DuocPhep = 1
};

enum Phai {
	Nam = 0,
	Nu = 1
};

typedef int (*comparer)(int, int);

int index = 0;

struct TenHo
{
	string HoTen;
	int MaThe;
	int phai;
	int trangthai;
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

Node_DocGiaPTR findMin(tree root)
{
    while(root->tdgLeft != NULL)
    {
        root = root->tdgLeft;
    }
    return root;
}


void XuatDG(TheDocGia dg);
Node_DocGiaPTR SearchDG(tree root,int value)
{ 
	if(root==NULL)
		return NULL;
	else if(root->tdg.MaThe == value)
	{
		return root;
	}
	else if(value < root->tdg.MaThe)
		SearchDG(root->tdgLeft,value);
	else if(value > root->tdg.MaThe)
		SearchDG(root->tdgRight,value);
}




Node_DocGiaPTR XOAMOTDOCGIA( tree &root,int value)
{ 

//	bool c = SearchDG(root,value);
	
	if(root==NULL)
		return root;
	else if(value < root->tdg.MaThe)
	{
		root->tdgLeft= XOAMOTDOCGIA(root->tdgLeft,value);
	}
	else if(value > root->tdg.MaThe)
	{
		root->tdgRight= XOAMOTDOCGIA(root->tdgRight,value);
	}
	
	// Node deletion
	else
	{
		//case 1: Leaf Node
		if(root->tdgLeft  ==NULL && root->tdgRight == NULL)
		{
			delete root;
			root = NULL;
			return root;
		}
		//case 2: one child
		else if(root->tdgLeft == NULL)
		{
			Node_DocGiaPTR temp = root;
			root = root->tdgRight;
			delete temp;
			return root;
		}
		else if(root->tdgRight == NULL)
		{
			Node_DocGiaPTR temp = root;
			root = root->tdgLeft;
			delete temp;
			return root;
		}
		//case 3: 2 child
		else
		{
			Node_DocGiaPTR temp = findMin(root->tdgRight);
			root->tdg = temp->tdg;
			root->tdgRight = XOAMOTDOCGIA(root->tdgRight,temp->tdg.MaThe);
		}
		
	}
	return root;

}


void ThemDG(tree &l,TheDocGia dg){
	Node_DocGiaPTR p = newNodeDG(dg);
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

void ThemNodeDG(tree &l,Node_DocGiaPTR nodeDG){
	if(l==NULL){
		l=nodeDG;
		return;
	}
	if(nodeDG->tdg.MaThe < l->tdg.MaThe){
		ThemNodeDG(l->tdgLeft,nodeDG);
	}else if(nodeDG->tdg.MaThe > l->tdg.MaThe){
		ThemNodeDG(l->tdgRight,nodeDG);
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
	gotoxy(10,0);
	printf("Ma the doc gia");
	gotoxy(10,1);
	printf("%d",dg.MaThe);

	gotoxy(30,0);
	printf("Ho Ten");
	gotoxy(30,1);
	uppercaseChar(dg.Ho);
	uppercaseChar(dg.Ten);
	printf("%s %s",dg.Ho,dg.Ten);
	gotoxy(60,0);
	printf("Phai");
	gotoxy(60,1);
	switch(dg.phai){
		case Nam:
			printf("Nam");
			break;
		case Nu:
			printf("Nu");
			break;
	}
	gotoxy(70,0);
	printf("Trang thai");
	gotoxy(70,1);
	switch(dg.trangthaithe){
		case DuocPhep:
			printf("Duoc phep");
			break;
		case KhongDuocPhep:
			printf("Khong duoc phep");
			break;
	}
	if (dg.lsMuonTra.mtFirst != NULL){
		gotoxy(35,4);
		printf("Danh sach sach muon tra");
		XuatDSMT(dg.lsMuonTra,10,6);
	}

	
}


void XuatDGTRASACH(TheDocGia dg){
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
			printf("\nPhai : Nu");
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
}

void XuatTieuDeCotBangDG(int x, int y) {
	gotoxy(x,y);
	printf("Stt");
	gotoxy(x+10,y);
	printf("Ma the doc gia");
	gotoxy(x+30,y);
	printf("Ho Ten");
	gotoxy(x+55,y);
	printf("Phai");
	gotoxy(x+70,y);
	printf("Trang thai");

}
void XuatDGTheoStt(int dem,TheDocGia dg, int x, int y){
//STT
	gotoxy(x,y+1);
	printf("%d",dem);
//MA THE
	gotoxy(x+10,y+1);
	printf("%d",dg.MaThe);
//HO TEN
	gotoxy(x+30,y+1);
	uppercaseChar(dg.Ho);
	uppercaseChar(dg.Ten);
	printf("%s %s",dg.Ho,dg.Ten);
//PHAI
	gotoxy(x + 55,y+1);
	switch(dg.phai){
		case Nam:
			printf("NAM");
			break;
		case Nu:
			printf("NU");
			break;
	}
//TRANG THAI
	gotoxy(x+70,y+1);
	switch(dg.trangthaithe){
		case DuocPhep:
			printf("THE DANG HOAT DONG");
			break;
		case KhongDuocPhep:
			printf("THE DA NGUNG HOAT DONG");
			break;
	}
//	if (dg.lsMuonTra.mtFirst != NULL){
//		gotoxy(35,y+3);
//		printf(" Danh sach sach muon tra");
//		XuatDSMT(dg.lsMuonTra,10,y+7);
//	}

}

int dem = 1;
void XuatDanhSachTheoSTT(tree ls) {
	int x = 10;
	int y = dem;
	if (ls != NULL)
	{
		dem+=1;
		XuatDanhSachTheoSTT(ls->tdgLeft);
		XuatDGTheoStt(dem - 1,ls->tdg,x,y);
		XuatDanhSachTheoSTT(ls->tdgRight);
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
			dem+=1;
			p=Stack[sp--];
			XuatDGTheoStt(dem - 1,p->tdg,10,dem);
			p=p->tdgRight;
		}
		else break;
	}while(1);
}


TheDocGia _NhapDuLieuDG(tree &l, LISTDS listDauSach){
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
	NhapMT(listMTDG,listDauSach);
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
	arr[index].phai = ls->tdg.phai;
	arr[index].trangthai = ls->tdg.trangthaithe;
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


void XuatDanhSachTheoThuTuHoTen( TEN_HO* ArrTenHo, int countDG){
	int x = 10;
	int y = 0;
	clrscr();
	XuatTieuDeCotBangDG(10,1);

	for(int i = 0; i < countDG; i++) {
		y+=1;
		dem+=1;
		//MA THE
		gotoxy(x,y+1);
		cout<<dem;
		//MA THE
		gotoxy(x+10,y+1);
		cout<<ArrTenHo[i].MaThe;
		//HO TEN
		gotoxy(x+30,y+1);
		cout<<ArrTenHo[i].HoTen;

		//PHAI
		gotoxy(x+55,y+1);
		switch(ArrTenHo[i].phai){
			case Nam:
				cout<<"NAM";
				break;
			case Nu:
				cout<<"NU";
				break;
		}
		//TRANG THAI
		gotoxy(x+70,y+1);
		switch(ArrTenHo[i].trangthai){
			case DuocPhep:
				cout<<"THE DANG HOAT DONG";
				break;
			case KhongDuocPhep:
				cout<<"THE DA NGUNG HOAT DONG";
				break;
		}
		
		
	}

}

Node_DocGiaPTR NhapSuaChuaDocGia(int maTheDG, LISTMT listMT){
	int endchar;
	int maThe;
	char *ho;
	char *ten;
	char *phai;
	char *trangThai;
	int sex;
while(endchar != ESC) {	
		TheDocGia item;
	MaTheDG: 	
		maThe = maTheDG;
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
		item.lsMuonTra = listMT;
		return newNodeDG(item);
	}
	return NULL;
}


char MENU_DSDG[6][30] 		= {	"1.Sap xep theo ten      ",
								"2.Sap xep theo stt      ",
								"3.Sua thong tin doc gia ",
								"4.Xoa thong tin doc gia ",
								"5.Them thong tin doc gia",
								"ESC: Thoat              " };
								

void menuXemDanhSachDG(tree &ls) {
	int choice;
	int endchar;
	Node_DocGiaPTR nodeDG;
	int maTDG;

	do {
		clrscr();
		for (int i = 0; i < 6;  i++) {
			printf("\n%s",MENU_DSDG[i]);
		}
		printf("\nNhap chuc nang:");
		choice = atoi(InputType(1,endchar,2));
		
		switch (choice) {
			case 1: {
				index =  0;
				int nDG = countDG(ls);
				TEN_HO* ArrTenHo = new TEN_HO[nDG];
				Create_ArrTenHo(ls, ArrTenHo);
				QuicKsort_ARRTenHo(ArrTenHo, 0, nDG - 1);
				dem = 0;
				XuatDanhSachTheoThuTuHoTen(ArrTenHo,nDG);
				break;
				}
			case 2:{
				clrscr();
				dem = 1;
				XuatTieuDeCotBangDG(10,1);
				XuatDSDG(ls);
				break;
			}
			case 3:{
				NHAPMASODOCGIACANSUA:
				printf("\nNhap ma so the DG:");
	    		maTDG = atoi(InputType(6,endchar,2));
		    	nodeDG = SearchDG(ls,maTDG);
		    	if(nodeDG == NULL){
		    		printf("\nDoc gia: %d khong ton tai \n ===> Thao tac that bai. <===",maTDG);
		    		goto NHAPMASODOCGIACANSUA;
		    		
		    	}else{
		    		nodeDG = NhapSuaChuaDocGia(maTDG,nodeDG->tdg.lsMuonTra);
		    		if (nodeDG != NULL) {
		    			XOAMOTDOCGIA(ls,maTDG);
		    			ThemNodeDG(ls, nodeDG);
						printf("\n====> Cap nhat thanh cong! <=====");
						
					} else {
						printf("\n====> Cap nhat khong thanh cong! <=====");
						
					}
		    		
				}

				break;
			}
			case 4:{
				NHAPMASODOCGIAMUONXOA:
				printf("\n");
		    	printf("Nhap ma the doc gia muon xoa:");
		    	getch();
		    	maTDG = atoi(InputType(6,endchar,2));
		    	//nodeDG = timDG(ls,maTDG);
		    	nodeDG = SearchDG(ls,maTDG);
		    	if(nodeDG==NULL){
		    		printf("\nDoc gia: %d khong ton tai \n ===> Xoa that bai. <===",maTDG);
		    		goto NHAPMASODOCGIAMUONXOA;
		    	}else{
		    		nodeDG = newNodeDG(nodeDG->tdg);
					XOAMOTDOCGIA(ls,maTDG);
		    		printf("\nDa xoa doc gia: '%d' '%s %s' \n ===> Xoa thanh cong. <===",maTDG,nodeDG->tdg.Ho,nodeDG->tdg.Ten);
				}
				break;
			}
			case 5:{
	    		clrscr();
	    		NhapDSDocGia(ls);
				break;
			}

		}
		getch();
	}while(endchar != ESC);
	
}



void MenuMuonTraSach(tree &ls, LISTDS &lsDauSach, Node_DocGiaPTR nodeDG, int maTDG) {
	int choice;
	int endchar;
	char *maSachTra;
	int thongtinTraSach;
	char *tenSachCanTim;
	Node_DocGiaPTR nodeDG2 = new Node_THEDOCGIA ;

	
	
	do {
		printf("\n");
		for (int i = 0; i < 3;  i++) {
			printf(MENU_MUONTRASACH[i]);
		}
	NHAPCHUCNANG:
		printf("\nNhap chuc nang:");
		choice = atoi(InputType(1,endchar,2));
		if (endchar == ESC) {
			break;
		}
		if (choice < 1 || choice > 2) {
			printf("\nKhong co chuc nang nay! Vui long chon chuc nang khac!");
			goto NHAPCHUCNANG;
	
		}
		switch (choice) {
			case 1:{
				//=====> MUON <=======//
		    	if (nodeDG != NULL){
		    		XuatDG(nodeDG->tdg);

			    	if (demSoSachDangMuon(nodeDG->tdg.lsMuonTra) == 3) {
						printf("\nDoc gia da muon toi da so luong cho phep!\n");
						
					} else if (sachQuaHan7Ngay(nodeDG->tdg.lsMuonTra) == 1) {
						printf("\nDoc gia khong muon vi da giu sach qua 7 ngay!\n");
						
					} else {
						gotoxy(wherex(),wherey()+2);
						NhapMTvoiMaSach(nodeDG->tdg.lsMuonTra,lsDauSach);
						
				    	if(nodeDG == NULL)
				    		cout<<"NULL"<<endl;
				    	else{	
							XOAMOTDOCGIA(ls,maTDG);
				    		ThemDG(ls,nodeDG->tdg);
						}
						
					}
				}
				
			break;
			}
			case 2: {
				//=====> TRA <=======//
	    		NHAPMASACHBANMUONTRA:
					printf("\nNhap ma sach muon tra:");
					maSachTra = InputType(20, endchar,1);
					uppercaseChar(maSachTra);
					if (strlen(maSachTra) == 0) {
						goto NHAPMASACHBANMUONTRA;
						
					}
		
					
					if (checkMaDMS_DSMT(nodeDG->tdg.lsMuonTra,maSachTra) == 1) {
					NHAPTRANGTHAITRASACH:
						printf("\nNhap thong tin tra sach (1: Tra sach, 2: Da mat): ");
						thongtinTraSach = atoi(InputType(1,endchar,2));
						if (endchar == ESC) {
							break;
						}
						if (thongtinTraSach < 1 || thongtinTraSach > 2 ) {
							printf("\nChi nhan trang thai '1' hoac '2'");
							goto NHAPTRANGTHAITRASACH;
						}
		
						if (TraSach_DSMT(nodeDG->tdg.lsMuonTra,lsDauSach,maSachTra,thongtinTraSach) == 1) {
							printf("\nBan da tra sach thanh cong!");
							
						} else {
							printf("\nBan tra sach that bai!");
							
						}
					} else {
							printf("\nKhong tim thay sach!");
							goto NHAPMASACHBANMUONTRA;
		
					}
					break;
				}
		}
		getch(); 
	}while(endchar != ESC);
	
}


void hienThiMenuMuonTra(tree &ls, LISTDS &lsDauSach) {
	Node_DocGiaPTR nodeDG;
	int maTDG;
	int endchar;
	
NHAPMATHEDOCGIA:
	clrscr();
	printf("\nNhap ma the doc gia:");
	maTDG = atoi(InputType(6,endchar,2));

	if (maTDG == 0) {
		goto NHAPMATHEDOCGIA;
		
	}
	nodeDG = timDG(ls,maTDG);
	if (nodeDG != NULL) {
		nodeDG = newNodeDG(nodeDG->tdg);
		
	} else {
		printf("\nMa the khong ton tai: %d", maTDG);
		goto NHAPMATHEDOCGIA;
	}
	
	if (nodeDG->tdg.trangthaithe == 0) {
		printf("\nHien tai ma the '%d' da ngung hoat dong!\n",nodeDG->tdg.MaThe);
		getch();
		return;
	}
	clrscr();
	XuatDG(nodeDG->tdg);
	MenuMuonTraSach(ls, lsDauSach, nodeDG, maTDG);
		
}




void HienThiMenuDocGia(tree &ls, LISTDS &lsDauSach) {
	int choice;
	int endchar;
	char *s;
	int maTDG;
	char *maSachTra;
	int thongtinTraSach;
	Node_DocGiaPTR nodeDG;
	Node_DocGiaPTR nodeDG2 = new Node_THEDOCGIA ;
	char *tenSachCanTim;

	do {
		for (int i = 0; i < 7; i++) {
			printf(MENU_DOCGIA[i]);
		}
		printf("\nNhap chuc nang:");
	 	choice = atoi(InputType(1,endchar,2));

	 	switch (choice) {
	    case 1: 

				
				break;
	    case 2:	printf("\nNhap Dau Sach\n"); 
				NhapThemDauSach(lsDauSach);

			//	HienThiMenuDauSach(lsDauSach);

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
//	    	printf("%d",lsDauSach.soluong);
			XuatDauSach(lsDauSach);
//	    				XuatDSDG(ls);

	    	getch(); 

	    	break;
	    case 5:
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
	   		
			if ((f = fopen("dausach2.bin","wb+") )== NULL){
		       printf("Error! opening file");
		       exit(1);
		   }
	   		//luuFileDAUSACH(ls,f);
	   		LuuDauSach(lsDauSach,"dausach2.bin","wb+");
	   		fclose(f);

	   		printf("Da luu");
	   		getch();
	    	break;
	    case 7:
	    	//MUON TRA SACH
	    	clrscr();
			hienThiMenuMuonTra(ls, lsDauSach);
	    	
	    	getch(); 
	    	break;
	     default: printf("\nWrong Choice. Enter again\n");
	     getch();
	         
	 	} 
  		clrscr(); 	
	} while (endchar != ESC);
//	

}

int main() {
	tree ls;
	LISTDS lsDauSach;
	KhoiTaoDocGia(ls);
	docFileDSDG(ls);
	RECT r;
	HWND console = GetConsoleWindow();
	GetWindowRect(console, &r); //stores the console's current dimensions
	MoveWindow(console, r.left, r.top, 1400, 800, TRUE);

	
//Dau Sach
	khoitaoDauSach(lsDauSach);
	DocDauSach(lsDauSach,"rb","dausach2.bin");
	
	HienThiMenuDocGia(ls,lsDauSach);

}
