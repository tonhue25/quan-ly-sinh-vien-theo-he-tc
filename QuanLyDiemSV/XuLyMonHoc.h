#pragma once
#include "CacHamXuLy.h" 
#define DSMONHOC 500

void KhungNhapThongTinMonHoc(string k);
int KiemTraThongTinMonHoc(PTRMonHoc root, MonHoc mh);
int KiemTraThongTinSuaDL(PTRMonHoc root, MonHoc mh);

//========================================================KHOI TAO CAY========================================================

void khoiTaoCay(PTRMonHoc &root) {
	root = NULL;
}
//========================================================TIM KIEM========================================================
PTRMonHoc Search(PTRMonHoc root, string x)
{
	PTRMonHoc p;
	p = root;
	while (p != NULL && p->data.maMH.compare(x)!=0)
		if (x.compare(p->data.maMH) < 0)
			p = p->left;
		else
			p = p->right;

	return(p);
}
//========================================================XOA NODE MON HOC========================================================

PTRMonHoc rp;
void remove_case3(PTRMonHoc &r) {
	if (r->left != NULL) {
		remove_case3(r->left);
	}
	else {
		rp->data.maMH = r->data.maMH;
		rp = r;
		r = rp->right;
	}
}

int xoaNode(PTRMonHoc &p,string ma) {
	if (p == NULL) { 
		return 0;
	}
	else {
		if (ma.compare(p->data.maMH) < 0) {
			xoaNode(p->left, ma);
		}
		else if (ma.compare(p->data.maMH) >0) {
			xoaNode(p->right, ma);
		}
		else {
			rp = p;
			if (rp->right == NULL)  p = rp->left;
			// p là nút lá hoac la nut chi co cay con ben trai
			else 	if (rp->left == NULL)
				p = rp->right;  // p là nut co cay con ben phai
			else remove_case3(rp->right);
			delete rp;
		}
	}
	return 1;
}

//========================================================THEM NODE========================================================

int Insert_node(PTRMonHoc &p, MonHoc mh)
{
	if (p == NULL)
	{
		p = new nodeMonHoc;
		p->data = mh;
		p->left = NULL;
		p->right = NULL;
		return 1; 
	}
	else if (KiemTraThongTinMonHoc(p,mh) > 1) {
		return 0;
	}
	else {
		if (mh.maMH.compare(p->data.maMH) == 0)
			return -1;
		else if (mh.maMH.compare(p->data.maMH) < 0) {
			Insert_node(p->left, mh);
		}
		else {
			Insert_node(p->right, mh);
		}
	}
}

//=====================================CAU D: IN DANH SACH SV THEO LOP=========================================

struct IndexName {
	PTRMonHoc chiso;
	string name;
};

void duyetCay(PTRMonHoc root, IndexName *nodes[],int &n) {
	if (root != NULL) {
		nodes[n] = new IndexName;
		nodes[n]->chiso = root;  
		nodes[n]->name = root->data.tenMH;
		
		n++;

		duyetCay(root->left,nodes,n);
		duyetCay(root->right, nodes,n);
	}
}

void hoanViIndexName(IndexName *a,IndexName *b) {
	IndexName *tam = new IndexName;
	tam->chiso = a->chiso;
	tam->name = a->name;

	a->chiso = b->chiso;
	a->name = b->name;

	b->chiso = tam->chiso;
	b->name = tam->name;
}
//selection sort 
void indexByName(PTRMonHoc root, IndexName *nodes[], int &n) {
	duyetCay(root, nodes,n);
	for (int i = 0; i < n-1; i++) {
		for (int j = i + 1; j < n; j++) {
			if (nodes[j]->name < nodes[i]->name) {
				//swap(nodes[j], nodes[i]);
				hoanViIndexName(nodes[j], nodes[i]);
			}
		}
	}
}

void giaiPhongIndexNameDSMH(IndexName* nodes[], int& n) {
	for (int i = 0; i < n; i++) {
		delete nodes[i];
	}
}

//================================================GIAI PHONG CAY===============================================

void GiaiPhongCay(PTRMonHoc& p) {
	while (p != NULL)
	{
		if (p->left != NULL) {
			GiaiPhongCay(p->left);
		}
		if (p->right != NULL) {
			GiaiPhongCay(p->right);
		}
		else {
			PTRMonHoc rp = p;
			p = NULL;
			delete rp;
		}
	}
}

//================================================SUA MON HOC=============================================

int SuaMonHoc(PTRMonHoc t, string ma, MonHoc mh) {
	if (t == NULL) {
		return 0;
	}
	else {
		if (t->data.maMH.compare(ma) == 0) {
			t->data = mh;
			return 1;
		}
		else if (t->data.maMH.compare(ma) > 0) {
			SuaMonHoc(t->left, ma,mh);
		}
		else if (t->data.maMH.compare(ma) < 0) {
			SuaMonHoc(t->right, ma,mh);
		}
	}
}

//=====================================

int SuaThongTinMonHoc(MonHoc &mh, int& key, int& chuyen) {
	int r = -1;
	string temp = "";
	
	switch (key) {
	case 2: {
		NhapDuLieu(mh.tenMH, 50, posXSidebar + 10, posYSidebar + 7, 1, chuyen, 2);
		break;
	}
	case 3: {
		temp = to_string(mh.soTCLT);
		NhapDuLieu(temp, 2, posXSidebar + 11, posYSidebar + 9, 4, chuyen, 3);
		if (temp == "")
			break;
		mh.soTCLT = stoi(temp);
		break;
	}
	case 4: {
		temp = to_string(mh.soTCTH);
		NhapDuLieu(temp, 2, posXSidebar + 11, posYSidebar + 11, 4, chuyen, 3);
		if (temp == "")
			break;
		mh.soTCTH = stoi(temp);
		break;
	}
	case 5:
	{
		string choice[2] = { "Xac Nhan", "Tro ve" };
		int i = LuaChon(choice);
		if (i >= 0) {
			if (i == 0)
				r = INS;
			else if (i == 1)
				r = ESC;
			return r;
		}
		break;
	}
	default:
		break;
	}
	if (chuyen == ESC) {
		return ESC;
	}
}

//  ================================================================================================

void ChuyenTruongSuaThongTinMonHoc(int& key, int& check) {
	if (check == UP || check == DOWN)
	{
		switch (check)
		{
		case DOWN:
		{
			switch (key)
			{
			case 2:
				key = 3;
				break;
			case 3:
				key = 4;
				break;
			case 4:
				key = 5;
				break;
			case 5:
				key = 2;
				break;
			}
			break;
		}
		case UP:
		{
			switch (key)
			{
			case 2:
				key = 5;
				break;
			case 3:
				key = 2;
				break;
			case 4:
				key = 3;
				break;
			case 5:
				key = 4;
				break;
			}
			break;
		}
		}
	}
}

int KiemTraThongTinSuaDL(PTRMonHoc root, MonHoc mh) {
	
	if (!KiemTraChuoi(mh.tenMH, 3) || !KiemTraChuoi(mh.tenMH, 5))
		return 2;
	
	else if (mh.soTCLT < 0 || mh.soTCLT>99)
		return 3;
	
	else if (mh.soTCTH < 0 || mh.soTCTH>99)
		return 4;
	else
		return 1;
}

int XuLySuaThongTinMonHoc(PTRMonHoc &root, string maMH) {
	PTRMonHoc edit = Search(root, maMH); // tra ve p hoac tra ve NULL. 
	PTRMonHoc p = new nodeMonHoc; // p la du lieu cua cai thong tin can sua
	p->data = edit->data;
	int key = 2; 
	int check = -1;
	KhungNhapThongTinMonHoc("Sua mon hoc");
	
	gotoXY(posXSidebar + 14, posYSidebar + 5);
	cout << p->data.maMH;
	gotoXY(posXSidebar + 10, posYSidebar + 7);
	cout << p->data.tenMH;
	gotoXY(posXSidebar + 11, posYSidebar + 9);
	cout << p->data.soTCLT;
	gotoXY(posXSidebar + 11, posYSidebar + 11);
	cout << p->data.soTCTH;

	while (true)
	{
		int r = SuaThongTinMonHoc(p->data, key, check);
		ChuyenTruongSuaThongTinMonHoc(key, check);
		int k = KiemTraThongTinSuaDL(root,p->data);
		if (r == ESC) {
			break;
		}
		 if ((key == 3) && k == 2) {
			FeedBack("TenMH khong trong, gom: a-z, A-Z ,0-9 , khoang trang , so ky tu <= 50!", posXContent + 1, posYContent + 2, widthContent - 1, DO);
			key = 2;
		}
		else if ((key == 4) && k == 3) {
			FeedBack("SoTC ly thuyet khong trong, gom: 0-9, 0 <= soTC <= 99!", posXContent + 1, posYContent + 2, widthContent - 1, DO);
			key = 3;
		}
		else if ((key == 5) && k == 4) {
			FeedBack("SoTC thuc hanh khong trong, gom: 0-9, 0 <= soTC <= 99!", posXContent + 1, posYContent + 2, widthContent - 1, DO);
			key = 4;
		}
		else if (k == 1) {
			if (r == INS) {
				int i = XacNhanLuaChon("Sua mon hoc", posXSidebar + 3, posYSidebar + 23, widthSidebar - 5);
				if (i == 1)
				{
					int kt = SuaMonHoc(root,edit->data.maMH,p->data);
					return kt;
				}
				else if (i == 0) {
					FeedBack("Moi thao tac lai!", posXSidebar + 3, posYSidebar + 23, widthSidebar - 5, DO);
					key = 2;
				}
			}
		}
	}
	return 0;
}

void KhungNhapThongTinMonHoc(string k){
	VeKhungVien(posXSidebar + 1, posYSidebar + 1, widthSidebar - 2, heightSidebar - 2);
	TextColor(DO);
	gotoXY(posXSidebar + 1 + (widthSidebar - 2) / 2 - (widthSidebar - 2) / 4, posYSidebar + 1);
	string h = k;
	cout << CanGiuaChu(h, (widthSidebar - 2) / 2);
	TextColor(15);
	gotoXY(posXSidebar + 3, posYSidebar + 5 );
	cout << "Ma mon hoc";
	gotoXY(posXSidebar + 13, posYSidebar + 5);
	cout << ":";
	gotoXY(posXSidebar + 3, posYSidebar + 7);
	cout << "Ten MH";
	gotoXY(posXSidebar + 9, posYSidebar + 7);
	cout << ":";
	gotoXY(posXSidebar + 3, posYSidebar + 9);
	cout << "So TCLT";
	gotoXY(posXSidebar + 10, posYSidebar + 9);
	cout << ":";
	gotoXY(posXSidebar + 3, posYSidebar + 11);
	cout << "So TCTH";
	gotoXY(posXSidebar + 10, posYSidebar + 11);
	cout << ":";
	string arr[2] = { "Xac nhan", "Tro ve" };
	int width = (arr[0].length() > arr[1].length()) ? arr[0].length() + 2 : arr[1].length() + 2;
	int color = DO;
	int X = posXSidebar + 6;
	int Y = posYSidebar + 25;
	int space = 19;
	gotoXY(X, Y);
	cout << CanGiuaChu(arr[0], width);
	gotoXY(X + space, Y);
	cout << CanGiuaChu(arr[1], width);
}

int NhapThongTinMonHoc(MonHoc &mh, int& key, int& chuyen) {
	int r = -1;
	string temp = "";
	switch (key) {
	case 1: {
		NhapDuLieu(mh.maMH, 10, posXSidebar + 14, posYSidebar + 5, 1, chuyen, 1);
		break;
	}
	case 2: {
		NhapDuLieu(mh.tenMH, 50, posXSidebar + 10, posYSidebar + 7, 1, chuyen, 2);
		break;
	}
	case 3: {
		NhapDuLieu(temp, 2, posXSidebar + 11, posYSidebar + 9, 4, chuyen, 3);
		if (temp == "")
			break;
		mh.soTCLT = stoi(temp);
		break;
	}
	case 4: {
		NhapDuLieu(temp, 2, posXSidebar + 11, posYSidebar + 11, 4, chuyen, 3);
		if (temp == "")
			break;
		mh.soTCTH = stoi(temp);
		break;
	}
	case 5: 
	{
		string choice[2] = { "Xac Nhan", "Tro ve" };
		int i = LuaChon(choice);
		if (i >= 0) {
			if (i == 0)
				r = INS;
			else if (i == 1)
				r = ESC;
			return r;
		}
		break;
	}
	default:
		break;
	}
	if (chuyen == ESC) {
		return ESC;
	}
}

void ChuyenTruongNhapThongTinMonHoc(int &key, int &chuyen){
	if (chuyen == UP || chuyen == DOWN)
	{
		switch (chuyen)
		{
		case DOWN:
		{
			switch (key)
			{
			case 1:
				key = 2;
				break;
			case 2:
				key = 3;
				break;
			case 3:
				key = 4;
				break;
			case 4:
				key = 5;
				break;
			case 5:
				key = 2;
				break;
			}
			break;
		}
		case UP:
		{
			switch (key)
			{
			case 1:
				key = 5;
				break;
			case 2:
				key = 1;
				break;
			case 3:
				key = 2;
				break;
			case 4:
				key = 3;
				break;
			case 5:
				key = 4;
				break;
			}
			break;
		}
		}
	}
}

int KiemTraThongTinMonHoc(PTRMonHoc root,MonHoc mh)
{
	PTRMonHoc p = Search(root, mh.maMH);
	if (!KiemTraChuoi(mh.maMH, 3) || !KiemTraChuoi(mh.maMH, 5) || !KiemTraChuoi(mh.maMH, 4))
		return 2;
	else if (p != NULL) {
		return 3;
	}
	else if (!KiemTraChuoi(mh.tenMH, 3) || !KiemTraChuoi(mh.tenMH, 5))
		return 4;
	else if (mh.soTCLT < 0 || mh.soTCLT>=100)
		return 5;
	else if (mh.soTCTH < 0 || mh.soTCTH>=100)
		return 6;
	else
		return 1;
}

int XuLyThemMonHoc(PTRMonHoc &root)
 {
	MonHoc mh;
	int key = 1;
	int check = -1;
	KhungNhapThongTinMonHoc("Them mon hoc");
	while (true)
	{
		int r = NhapThongTinMonHoc(mh, key, check);
		ChuyenTruongNhapThongTinMonHoc(key, check);
		int k = KiemTraThongTinMonHoc(root,mh);
		if (r == ESC) {
			break;
		}
		if (key == 2 && k == 2) {
			FeedBack("Ma mon hoc ko trong, gom a-z ,A-Z ,0-9, so ki tu<=10!", posXContent + 1, posYContent + 2, widthContent - 1, DO);
			key = 1;
		}
		else if ((key == 2) && k == 3) {
			FeedBack("Ma mon hoc da ton tai!", posXContent + 1, posYContent + 2, widthContent - 1, DO);
			key = 1;
		}
		else if ((key == 3) && k == 4) {
			FeedBack("Ten mon hoc khong trong, gom a-z, A-Z, 0-9, khoang trang, so ki tu<=50!", posXContent + 1, posYContent + 2, widthContent - 1, DO);
			key = 2;
		}
		else if ((key == 4) && k == 5) {
			FeedBack("SoTC ly thuyet khong trong, gom: 0-9, 0<=soTC<=99!", posXContent + 1, posYContent + 2, widthContent - 1, DO);
			key = 3;
		}
		else if ((key == 5) && k == 6) {
			FeedBack("SoTC thuc hanh khong trong, gom: 0-9, 0<=soTC<=99!", posXContent + 1, posYContent + 2, widthContent - 1, DO);
			key = 4;
		}
		else if (k == 1) {
			if (r == INS) {
				int i = XacNhanLuaChon("them mon hoc", posXSidebar + 3, posYSidebar + 23, widthSidebar - 5);
				if (i == 1)
				{
					int kt =  Insert_node(root, mh);
					return kt;
				}
				else if (i == 0) {
					FeedBack("Moi thao tac lai!", posXSidebar + 3, posYSidebar + 23, widthSidebar - 5, DO);
					key = 1;
				}
			}
		}
	}
	return 0;
}

int kiemTraMonHocDuocDKLopTinChi(ListLTC &listLTC,string maMH) {
	for (int i = 0; i < listLTC.sl; i++) {
		if (listLTC.ds[i]->maMH.compare(maMH) == 0) {
			return i;
		}
	}
	return -1;
}

int XuLyXoaMonHoc(PTRMonHoc &root,ListLTC &listLTC, string maMH) 
{
	int key = 1;
	int check = -1;
	PTRMonHoc p = Search(root, maMH);
	KhungNhapThongTinMonHoc("Xoa Mon Hoc");
	gotoXY(posXSidebar + 14, posYSidebar + 5);
	cout << p->data.maMH;
	gotoXY(posXSidebar + 10, posYSidebar + 7);
	cout << p->data.tenMH;
	gotoXY(posXSidebar + 11, posYSidebar + 9);
	cout << p->data.soTCLT;
	gotoXY(posXSidebar + 11, posYSidebar + 11);
	cout << p->data.soTCTH;
	
	if (kiemTraMonHocDuocDKLopTinChi(listLTC, p->data.maMH) >= 0) {
		return 2;
	}
	int i = XacNhanLuaChon("xoa mon hoc", posXSidebar + 3, posYSidebar + 23, widthSidebar - 5);
	if (i == 1)
	{
		if(kiemTraMonHocDuocDKLopTinChi(listLTC,p->data.maMH) == -1){
			return xoaNode(root, maMH);
		}
	}
	else if (i == 0) {
		return 0;
	}
}

void QuanLyMonHoc(PTRMonHoc& root,ListLTC &listLTC) 
{
	int first = 0;
	int last = 11;
	int current = first;
	int check = -1;
	int posX = posXContent + 1;
	int posY = posYContent + 0.15 * heightContent;
	int width = widthContent - 2;
	int height = heightContent - 0.15 * heightContent;
	KhungChuongTrinh();
	veBangMonHoc(posX, posY, width, height);
	int n = 0;
	PTRMonHoc cs;
	int k = 1;
	int STT = 0;
	int j = 0;
	IndexName* nodes[DSMONHOC];
	indexByName(root, nodes, n);
	while (true) {
		k = 1;
		if (check == ESC) {
			break;
		}
		if (n <= 12)
		{
			last = n - 1;
		}
		STT = first;
		for (int i = first; i <= last; i++) {
			STT++;
			cs = nodes[i]->chiso;
			if (last >= 0) {
				if (i == current) {
					TextColor(240);
				}
				j = 0;
				gotoXY(posX + 1, posY + 2 + k * 1);
				cout << CanGiuaChu(to_string(STT), 0.1 * width - 1);
				j += 0.1 * width;
				gotoXY(posX + 1 + j, posY + 2 + k * 1);
				cout << CanGiuaChu(cs->data.maMH, 0.2 * width - 1);
				j += 0.2 * width;
				gotoXY(posX + 1 + j, posY + 2 + k * 1);
				cout << CanGiuaChu(nodes[i]->name, 0.4 * width - 1);
				j += 0.4 * width;
				gotoXY(posX + 1 + j, posY + 2 + k * 1);
				cout << CanGiuaChu(to_string(cs->data.soTCLT), 0.15 * width - 1);
				j += 0.15 * width;
				gotoXY(posX + 1 + j, posY + 2 + k * 1);
				cout << CanGiuaChu(to_string(cs->data.soTCTH), width - j - 1);
				k = k + 2;
				if (i == current) {
					TextColor(MACDINH);
				}
			}
			else
			{
				return;
			}
		}
		check = _getch();
		if (check == DOWN || check == UP) {
			DiChuyenThanhSang(n, first, last, current, check);
		}
		if (check == DEL && n > 0) {
			int  kt = XuLyXoaMonHoc(root, listLTC, nodes[current]->chiso->data.maMH);
			giaiPhongIndexNameDSMH(nodes, n);
			n = 0;
			indexByName(root, nodes, n);
			if (kt == 1) {
				if (last == n && n >= 12) {
					first--;
					last--;
					current--;
				}
				else if (current == last && last == n && n < 12) {
					last--;
					current--;
				}
				FeedBack("Xoa mon hoc thanh cong!", posXContent + 1, posYContent + 2, widthContent - 1, DO);
			}
			if (kt == 2) FeedBack("Mon hoc da duoc dang ki lop tin chi, khong the xoa!", posXContent + 1, posYContent + 2, widthContent - 1, DO);
			Cls(posXSidebar + 1, posYSidebar + 1, widthSidebar - 1, heightSidebar - 1);
			ClsDanhSachMonHoc();
		}
		else if (check == INS)
		{
			int add = XuLyThemMonHoc(root);
			giaiPhongIndexNameDSMH(nodes, n);
			n = 0;
			indexByName(root, nodes, n);
			if (add == 1) {
				FeedBack("Them mon hoc thanh cong!", posXContent + 1, posYContent + 2, widthContent - 1, DO);
			}
			if (add == 0) {
				FeedBack("Thong tin mon hoc khong hop le!", posXContent + 1, posYContent + 2, widthContent - 1, DO);
			}
			Cls(posXSidebar + 1, posYSidebar + 1, widthSidebar - 1, heightSidebar - 1);
			ClsDanhSachMonHoc();
		}
		else if (check == ENTER && n > 0)
		{
			int edit = XuLySuaThongTinMonHoc(root, nodes[current]->chiso->data.maMH);
			giaiPhongIndexNameDSMH(nodes, n);
			n = 0;
			indexByName(root, nodes, n);
			if (edit == 1) {
				FeedBack("Sua mon hoc thanh cong!", posXContent + 1, posYContent + 2, widthContent - 1, DO);
			}
			if (edit == 0) {
				FeedBack("Thong tin mon hoc khong hop le!", posXContent + 1, posYContent + 2, widthContent - 1, DO);
			}
			Cls(posXSidebar + 1, posYSidebar + 1, widthSidebar - 1, heightSidebar - 1);
			ClsDanhSachMonHoc();
		}
	}
	giaiPhongIndexNameDSMH(nodes, n);
}


		