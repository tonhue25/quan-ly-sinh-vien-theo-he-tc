#pragma once
#include "ctdl.h"

void BaoLoi(string s, int toaDoX, int toaDoY);
void themNode(PTRMonHoc& p, MonHoc mh);
void Insert_Order(PTRDangKiLTC& First, DangKiLTC x);

PTRDangKiLTC khoiTaoNodeDKLTC(DangKiLTC& dk);
LopTinChi* ktTrungMaLopTinChi2(ListLTC& list, int maLTC);
PTRMonHoc khoiTaoNodeMH(MonHoc& mh);
//==========================================================================================
void themDauDKLTC(PTRDangKiLTC& First, DangKiLTC dk)
{
	PTRDangKiLTC p;
	p = new nodeDangKiLTC;
	p->dk = dk;
	p->next = First;
	First = p;
}
void themSauDKLTC(PTRDangKiLTC p, DangKiLTC dk) {
	PTRDangKiLTC q;
	if (p == NULL) {
		return;
	}
	else
	{
		q = new nodeDangKiLTC;
		q->dk = dk;
		q->next = p->next;
		p->next = q;
	}
}
void Insert_Order(PTRDangKiLTC& First, DangKiLTC x)
{
	PTRDangKiLTC p, q;  // q la nut truoc, p la nut sau
	q = NULL;
	for (p = First; p != NULL && p->dk.maSV < x.maSV; p = p->next)
		q = p;
	if (q == NULL)  // them nut vao dau danh sach lien ket
		themDauDKLTC(First, x);
	else           // them nut vao sau nut q
		themSauDKLTC(q, x);
}

LopTinChi* ktTrungMaLopTinChi2(ListLTC& list, int maLTC)
{
	for (int i = 0; i < list.sl; i++)
	{
		if (list.ds[i]->maLopTC == maLTC)
			return list.ds[i];
	}
	return NULL;
}
//============================ DOC / GHI FILE DANH SACH LOP TIN CHI==================

void docFileDanhSachLTC(ListLTC& l);
void ghiFileDanhSachLTC(ListLTC &l);

//================================DOC GHI FILE DS SINH VIEN===============
void docFileDanhSachSV(ListSV& l);
void ghiFileDanhSachSinhVien(ListSV& l);

//===============================DOC/GHI FILE DANH SACH MON HOC============================

void docFileDanhSachMonHoc(PTRMonHoc& root);


//=======================DOC/ GHI FILE DANG KI LOP TIN CHI=======

void docFileDanhSachDKLTC(ListLTC& listLTC);
void ghiFileDanhSachDKLTC(ListLTC& listLTC);


//============================ ==================DOC / GHI FILE DANH SACH LOP TIN CHI==================
void docFileDanhSachLTC(ListLTC &l) {
	ifstream filein;
	filein.open("DanhSachLopTinChi.txt", ios_base::in);
	while (filein.eof() != true)
	{
		l.ds[l.sl] = new LopTinChi;
		filein >> l.ds[l.sl]->maLopTC;
		
		if (l.ds[l.sl]->maLopTC < 0 ) {
			break;
		}

		filein.ignore();
		getline(filein, l.ds[l.sl]->maMH,',');
		filein >> l.ds[l.sl]->nienKhoa.nienKhoaDau;
		filein.ignore();
		filein >> l.ds[l.sl]->nienKhoa.nienKhoaCuoi;
		filein.ignore();
		filein >> l.ds[l.sl]->hocKy;
		filein.ignore();
		filein >> l.ds[l.sl]->nhom;
		filein.ignore();
		filein >> l.ds[l.sl]->soSVMin;
		filein.ignore();
		filein >> l.ds[l.sl]->soSVMax;
		filein.ignore();
		filein >> l.ds[l.sl]->trangThaiLop;
		filein.ignore();
		l.sl++;
	}
	filein.close();
}

void ghiFileDanhSachLTC(ListLTC &l) {
	ofstream fileout;
	fileout.open("DanhSachLopTinChi.txt", ios_base::out);
	for (int i = 0; i < l.sl; i++) {
		fileout << l.ds[i]->maLopTC << ',';
		fileout << l.ds[i]->maMH << ',';
		fileout << l.ds[i]->nienKhoa.nienKhoaDau << ',';
		fileout << l.ds[i]->nienKhoa.nienKhoaCuoi << ',';
		fileout << l.ds[i]->hocKy << ',';
		fileout << l.ds[i]->nhom << ',';
		fileout << l.ds[i]->soSVMin << ',';
		fileout << l.ds[i]->soSVMax << ',';
		fileout << l.ds[i]->trangThaiLop<<endl;
	}
	fileout.close();
}

//================================DOC GHI FILE DS SINH VIEN===============

void docFileDanhSachSV(ListSV &l) {
	ifstream filein;
	filein.open("DanhSachSinhVien.txt", ios_base::in);
	while (filein.eof() != true)
	{
		SinhVien sv;
		getline(filein, sv.maLop, ',');
		if (sv.maLop == "\n" || sv.maLop == "") {
			break;
		}
		getline(filein, sv.maSV, ',');
		getline(filein, sv.ho, ',');
		getline(filein, sv.ten, ',');
		filein >> sv.phai;
		filein.ignore();
		getline(filein, sv.soDT);
		
		l.ds[l.sl] = sv;
		l.sl++;
	}
	filein.close();
}

void ghiFileDanhSachSinhVien(ListSV &l) {
	ofstream fileout;
	fileout.open("DanhSachSinhVien.txt", ios_base::out);
	for (int i = 0; i < l.sl; i++) {
		fileout << l.ds[i].maLop << ',';
		fileout << l.ds[i].maSV << ',';
		fileout << l.ds[i].ho << ',';
		fileout << l.ds[i].ten << ',';
		fileout << l.ds[i].phai << ',';
		fileout << l.ds[i].soDT << endl;
	}
	fileout.close();
}

//===============================DOC/GHI FILE DANH SACH MON HOC============================

PTRMonHoc khoiTaoNodeMH(MonHoc& mh) {
	PTRMonHoc p;
	p = new nodeMonHoc;
	p->data = mh;
	p->left = NULL;
	p->right = NULL;
	return p;
}

 void themNode(PTRMonHoc& p, MonHoc mh) {
	if (p == NULL) {
		p = khoiTaoNodeMH(mh);
	}
	else {
		if (p->data.maMH.compare(mh.maMH) > 0) {
			themNode(p->left, mh);
		}
		else if (p->data.maMH.compare(mh.maMH) < 0) {
			themNode(p->right, mh);
		}
	}
}
void docFileDanhSachMonHoc(PTRMonHoc &root) {
	ifstream filein;
	filein.open("DanhSachMonHoc.txt", ios_base::in);
	while (filein.eof() != true)
	{
		MonHoc mh;
		getline(filein, mh.maMH, ',');
		if (mh.maMH == "\n" || mh.maMH == "") {
			break;
		}
		getline(filein, mh.tenMH, ',');
		filein >> mh.soTCLT;
		filein.ignore();
		filein >> mh.soTCTH;
		filein.ignore();
		PTRMonHoc p = khoiTaoNodeMH(mh);
		themNode(root, p->data);
	}
	filein.close();
}

void GhiFile_LNR(ofstream& file, PTRMonHoc root)
{
	if (root != NULL)
	{
		file << root->data.maMH << ','
			<< root->data.tenMH << ','
			<< root->data.soTCLT << ','
			<< root->data.soTCTH << endl;
		GhiFile_LNR(file, root->left);
		GhiFile_LNR(file, root->right);
	}
}
void GhiFileMH(PTRMonHoc root) {
	ofstream outfile;
	outfile.open("DanhSachMonHoc.txt", ios::out);
	GhiFile_LNR(outfile, root);
	outfile.close();
}

//=======================DOC/ GHI FILE DANG KI LOP TIN CHI=======

void docFileDanhSachDKLTC(ListLTC &listLTC) {
	ifstream filein;
	filein.open("DanhSachDKLTC.txt", ios_base::in);
	while (filein.eof() != true)
	{
		DangKiLTC dk;
		int ma;
		filein >> ma;
		if (ma < 100) {
			break;
		}
		filein.ignore();
		LopTinChi* p = ktTrungMaLopTinChi2(listLTC,ma);
		if (p == NULL) {
			return;
		}
		else {
			getline(filein, dk.maSV, ',');
			if (dk.maSV == "\n" || dk.maSV == "") {
				break;
			}
			filein >> dk.trangThaiDK;
			filein.ignore();
			filein >> dk.diem;
			filein.ignore();
			Insert_Order(p->DSDKLTC, dk);
		}
	}
	filein.close();
}

void ghiFileDanhSachDKLTC(ListLTC &listLTC) {
	ofstream fileout;
	fileout.open("DanhSachDKLTC.txt", ios_base::out);
	for (int i = 0; i < listLTC.sl; i++) {
		for (PTRDangKiLTC k = listLTC.ds[i]->DSDKLTC; k != NULL; k = k->next) {
			fileout << listLTC.ds[i]->maLopTC << ',';
			fileout << k->dk.maSV << ',';
			fileout << k->dk.trangThaiDK << ',';
			fileout << k->dk.diem << '\n';
		}
	}
	fileout.close();
}
