#include "ctdl.h"
#define MAXDKLTC 500
#include "XuLySinhVien.h"
#define MAXHUYLTC 300

int kiemTraTrungMaSV(ListSV &l, string ma);

int tinhSoSinhVienDKLTC(LopTinChi* ltc);

void DangKiLTC_NK_HK(ListLTC& list, PTRMonHoc root, ListSV& listSV,SinhVien &sv);

void BangDangKiLopTinChi(ListLTC& listLTC, PTRMonHoc& root, ListSV& listSV, LopTinChi& ltc,SinhVien &sv);

void hienThiSinhVienConDKLopTinChi(ListLTC& listLTC, ListSV& listSV, LopTinChi& ltc, PTRMonHoc& root);

void CauH_HuyLopTinChi(ListLTC& listLTC, PTRMonHoc& root, LopTinChi& ltc);

void KiemTraThongTinInBangDiemLTC(ListLTC& list, PTRMonHoc root, ListSV& listSV);

void BangDiem(ListLTC& listLTC, PTRMonHoc& root, ListSV& listSV, LopTinChi& ltc);

void BangSVHuyDK(ListLTC& listLTC, PTRMonHoc& root, LopTinChi& ltc, SinhVien& sv);

void chuyenTruongNhapLieu_NK_HK(int& key, int& check);

void KhungNhap_NK_HK(string h);

int KiemTra_NK_HK(ListLTC& list, PTRMonHoc root, LopTinChi& ltc);

int Nhap_NK_HK(ListLTC& listLTC, LopTinChi& ltc, int key, int& check);

//===================================================KHOI TAO =================================================
void khoiTaoListDKLTC(PTRDangKiLTC &first) {
	first = NULL;
}

PTRDangKiLTC khoiTaoNodeDKLTC(DangKiLTC &dk){
	PTRDangKiLTC p;
	p = new nodeDangKiLTC;
	p->dk = dk;
	p->next = NULL;
	return p;
}
//=========================================TIM KIEM ===================================================

PTRDangKiLTC timKiem(PTRDangKiLTC First, string maSV){
	PTRDangKiLTC p;
	p = First;
	while (p != NULL && p->dk.maSV != maSV)
		p = p->next;
	return(p);
}


//============================================XOA===================================================

void xoaDauDKLTC(PTRDangKiLTC &first) {
	PTRDangKiLTC p;
	if (first == NULL) {
		return;
	}
	else {
		p = first;
		first = first->next;
		delete p;
	}
}

void xoaSauPDKLTC(PTRDangKiLTC p) {
	PTRDangKiLTC q;
	if (p == NULL || p->next == NULL) {
		return;
	}
	else {
		q = p->next;
		p->next = q->next;
		delete q;
	}
}

void xoaCuoiDKLTC(PTRDangKiLTC& first) {
	if (first == NULL) {
		return;
	}
	else {
		if (first->next == NULL) {
			PTRDangKiLTC p = first;
			first = NULL;
			delete p;
			return;
		}
		for (PTRDangKiLTC k = first; ; k = k->next) {
			if (k->next->next == NULL) {
				delete k->next;
				k->next = NULL;
				break;
			}
		}
	}
}

int Delete_info(PTRDangKiLTC& first, string ma){
	PTRDangKiLTC p;
	int dem = 0;
	while (first != NULL && first->dk.maSV == ma)
	{
		p = first;
		first = p->next;
		delete p;
		dem++;
	}
	if (first == NULL) return dem;
	for (p = first; p->next != NULL; )
	{
		if (p->next->dk.maSV == ma)
		{
			xoaSauPDKLTC(p);
			dem++;
		}
		else p = p->next;
	}
	return dem;
}

//======================================CAU G DANG KI LOP TIN CHI========================================
struct IndexDangKiLopTinChi
{
	int chiso;
};

void giaiPhongIndexDangKiLopTinChi(IndexDangKiLopTinChi *nodes[], int &n) {
	for (int i = 0; i < n; i++) {
		delete nodes[i];
	}
}

void DangKiLopTinChiChoTungSinhVien(ListLTC &listLTC,IndexDangKiLopTinChi *nodes[], int &n, int nkd, int nkc, int hk) {
	for (int i = 0; i < listLTC.sl; i++) {
		if (nkd == listLTC.ds[i]->nienKhoa.nienKhoaDau && nkc == listLTC.ds[i]->nienKhoa.nienKhoaCuoi && hk == listLTC.ds[i]->hocKy && listLTC.ds[i]->trangThaiLop == 1) {
			nodes[n] = new IndexDangKiLopTinChi;
			nodes[n]->chiso = i;
			n++;
		}
	}
}

int NhapMaSinhVien(SinhVien &sv,int &key, int &chuyen) {
	int x = posXContent + 30;

	switch (key) {
	case 1: {
		NhapDuLieu(sv.maSV, 15, x + 22, posYContent + 5, 1, chuyen, 1);
		break;
	}
	default:
		break;
	}
	if (chuyen == ESC) {
		return ESC;
	}
}

int KiemTraMaSinhVien(ListSV &list, SinhVien sv)
{
	int i = kiemTraTrungMaSV(list, sv.maSV);
	if (!KiemTraChuoi(sv.maSV, 3) || !KiemTraChuoi(sv.maSV, 5) || !KiemTraChuoi(sv.maSV, 4))
		return 2;
	else if (i == -1)
		return 3;
	else
		return 1;
}

// cau g
void DangKiLopTinChi(ListLTC& list, PTRMonHoc root, ListSV& listSV) {
	int key = 1;
	int check = -1;
	SinhVien sv;
	KhungNhapMaTimKiem("Nhap thong tin", "Nhap ma sinh vien");
	HuongDan(8);
	while (true)
	{
		int r = NhapMaSinhVien(sv,key, check);
		int k = KiemTraMaSinhVien(listSV, sv);
		if (r == ESC) {
			break;
		}
		if (k == 2) {
			FeedBack("Ma sinh vien khong trong, gom: a-z,A-Z,0-9, so ky tu <= 15!", posXContent + 3, posYContent + 23, widthContent - 5, DO);
			key = 1;
		}
		else if (k == 3) {
			FeedBack("Ma sinh vien chua ton tai!", posXContent + 3, posYContent + 23, widthContent  - 5, DO);
			key = 1;
		}
		else if (k == 1) {
			int i = kiemTraTrungMaSV(listSV, sv.maSV);
			gotoXY(3, 2);
			cout << "Ma lop  : " << listSV.ds[i].maLop;
			gotoXY(3, 3);
			cout << "Ma SV   : " << sv.maSV;
			gotoXY(3, 4);
			cout << "Ho ten  : " << listSV.ds[i].ho<<" "<< listSV.ds[i].ten;
			gotoXY(3, 5);
			cout << "Phai    : " << (listSV.ds[i].phai == 1 ? "Nam" : "Nu");
			gotoXY(3, 6);
			cout << "SDT     : " << listSV.ds[i].soDT;
			Cls(posXContent, posYContent+2, widthContent, CHIEUDOC);
			DangKiLTC_NK_HK(list, root, listSV, sv);
			Cls(TOADOX, TOADOY, CHIEUNGANG, CHIEUDOC);
			break;
		}
	}
}

void DangKiLTC_NK_HK(ListLTC& list, PTRMonHoc root, ListSV& listSV,SinhVien &sv) {
	int key = 1;
	int check = -1;
	LopTinChi ltc;
	KhungNhap_NK_HK("Nhap thong tin");
	HuongDan(7);
	while (true)
	{
		int r = Nhap_NK_HK(list,ltc,key,check);
		chuyenTruongNhapLieu_NK_HK(key, check);
		int k = KiemTra_NK_HK(list,root, ltc);
		if (r == ESC) {
			break;
		}
		if (key == 2 && k == 2) {
			FeedBack("Nien khoa trong, gom: 0-9 , NK Dau >= 2020!", posXContent + 3, posYContent + 28, widthContent  - 5, DO);
			key = 1;
		}
		else if (key == 3 && k == 3) {
			FeedBack("Nien khoa trong, gom: 0-9, NK Cuoi > NKD !", posXContent + 3, posYContent + 28, widthContent  - 5, DO);
			key = 2;
		}
		else if (key == 1 && k == 4) {
			FeedBack("Hoc ki trong, gom: 1-3!", posXContent + 3, posYContent + 28, widthContent - 5, DO);
			key = 3;
		}
		else if (k == 5) {
			FeedBack("Nien Khoa,Hoc ki khong ton tai!", posXContent + 3, posYContent + 28, widthContent  - 5, DO);
		}
		else if (k == 1) {
			gotoXY(120, 2);
			cout << "Nien Khoa  : " << ltc.nienKhoa.nienKhoaDau<<" - " <<ltc.nienKhoa.nienKhoaCuoi;
			gotoXY(120, 3);
			cout << "Hoc ki     : " << ltc.hocKy;
			Cls(posXContent, posYContent+2, CHIEUNGANG, CHIEUDOC);
			BangDangKiLopTinChi(list, root, listSV,ltc,sv);
			Cls(TOADOX, TOADOY, CHIEUNGANG+2, CHIEUDOC+2); 
			break;
		}
	}
}

struct nodePhu{
	int chiSo;
};

// lop tin chi da dk cua moi ca nhan sinh vien
// do trong cung nk hk do, va lop do co mo, thi se tim coi co sinh vien do dk hay chua.
void hienThiLTCDaDK(ListLTC &listLTC,nodePhu *nodes[], int &sl, string maSV,int nkd,int nkc,int hk) {
	PTRDangKiLTC p;
	for (int i = 0; i < listLTC.sl; i++) {
		if (listLTC.ds[i]->hocKy == hk && listLTC.ds[i]->nienKhoa.nienKhoaDau == nkd && listLTC.ds[i]->nienKhoa.nienKhoaCuoi == nkc && listLTC.ds[i]->trangThaiLop == 1) {
			for (p = listLTC.ds[i]->DSDKLTC; p != NULL; p = p->next) {
				if (p->dk.maSV.compare(maSV) == 0 && p->dk.trangThaiDK == 1) {
					nodes[sl] = new nodePhu;
					nodes[sl]->chiSo = i;
					sl++;
				}
			}
		}
	}
}

int kiemTraLTCDaDKChua(ListLTC& listLTC, nodePhu* node[], int& sl, int maLTC) {
	int cs = 0;
	for (int i = 0; i < sl; i++) {
		cs = node[i]->chiSo;
		if (maLTC == listLTC.ds[cs]->maLopTC) {
			return cs;
		}
	}
	return -1;
}

// trong sd lop tin chi da dk=> kiem tra xem ma mon hoc da ton tai chua
int kiemTraTrungMaMHKhiDKLTC(ListLTC& listLTC, nodePhu *node[], int& sl, string maMH) {
	int cs = 0;
	for (int i = 0; i < sl; i++) {
		cs = node[i]->chiSo;
		if (maMH.compare(listLTC.ds[cs]->maMH) == 0) {
			return cs;
		}
	}
	return -1;
}

int themDangKiLTC(ListLTC& listLTC, nodePhu* node[], int& sl, LopTinChi* p, DangKiLTC& dk) {
	PTRDangKiLTC i = KiemTraTrungMaSVDKLTC(p->DSDKLTC, dk.maSV);
	int vitritrung = kiemTraTrungMaMHKhiDKLTC(listLTC,node,sl,p->maMH);
	dk.diem = 0;
	string temp = "";
	temp = to_string(dk.diem);
	temp = DinhDangKieuSoThuc(temp);
	dk.diem = stof(temp);
	int kt = kiemTraLTCDaThi(listLTC, p->maLopTC);
	if (i != NULL) {
		return 0; // da dk ltc nay roi a
	}
	else if (vitritrung >= 0) {
		return 2;
	}
	else if (kt == 1) {
		return 3;
	}
	else {
		Insert_Order(p->DSDKLTC, dk);
		return 1;
	}
}

// xoa dang ki ltc: kiem tra dk chua, thi chua??
int XuLyXoaDangKiLTC(ListLTC &listLTC,nodePhu* node[],int &sl,string maSV,int info) {
	int cs = 0;
	int kt = kiemTraLTCDaDKChua(listLTC, node, sl, info);
	if (kt == -1) {
		return -1;
	}
	else {
		for (int i = 0; i < sl; i++) {
			cs = node[i]->chiSo;
			if (listLTC.ds[cs]->maLopTC == info) {
				int kt = kiemTraLTCDaThi(listLTC, info);
				if (kt == 1) {
					return 3;
				}
				else {
					for (PTRDangKiLTC k = listLTC.ds[cs]->DSDKLTC; k != NULL; k = k->next) {
						if (k->dk.maSV.compare(maSV) == 0 && k->dk.trangThaiDK == 1) {
							k->dk.trangThaiDK = 0;
							return 1;
						}
					}
				}
			}
		}
	}
	return 0;
}

void giaiPhongNodePhu(nodePhu *node[],int &sl) {
	for (int i = 0; i < sl; i++) {
		delete node[i];
	}
}

void BangDangKiLopTinChi(ListLTC &listLTC, PTRMonHoc &root, ListSV &listSV,LopTinChi &ltc,SinhVien &sv)
{
	int first = 0;
	int last = 11;
	int current = first;

	int l = 10;
	int f = 0;
	int c = f;

	int check = -1;

	int posX = posXContent + 1;
	int posY = posYContent + 0.15 * heightContent;
	int width = widthContent - 2;
	int height = heightContent - 0.15 * heightContent;
	int sc = 0;

	VeKhungDKLopTinChi("Dang ki LTC");
	VeKhungVien(TOADOX, TOADOY, CHIEUNGANG, CHIEUDOC);
	veBangDangKiLTC(posX, posX, width, height);
	HuongDan(3);

	IndexDangKiLopTinChi* nodes[MAXDKLTC];
	nodePhu* node[MAXDKLTC];
	int n = 0;
	int sl = 0;
	int  k = 1;
	int STT;
	DangKiLopTinChiChoTungSinhVien(listLTC, nodes, n, ltc.nienKhoa.nienKhoaDau, ltc.nienKhoa.nienKhoaCuoi, ltc.hocKy);

	hienThiLTCDaDK(listLTC, node, sl, sv.maSV, ltc.nienKhoa.nienKhoaDau, ltc.nienKhoa.nienKhoaCuoi, ltc.hocKy);

	while (true) {
		k = 1;
		if (check == ESC) { break; }
		if (n <= 12) {
			last = n - 1;
		}
		STT = first;
		for (int i = first; i <= last; i++) {
			STT++;
			sc = nodes[i]->chiso;
			if (last >= 0) {
				if (i == current) {
					TextColor(240);
				}
				int j = 0;
				gotoXY(posX + 1, posY + 2 + k * 1);
				cout << CanGiuaChu(to_string(STT), 0.06 * width - 1);

				j += 0.06 * width;
				gotoXY(posX + 1 + j, posY + 2 + k * 1);
				cout << CanGiuaChu(listLTC.ds[sc]->maMH, 0.15 * width - 1);

				j += 0.15 * width;
				gotoXY(posX + 1 + j, posY + 2 + k * 1);
				PTRMonHoc p = Search(root, listLTC.ds[sc]->maMH);
				cout << CanGiuaChu(p->data.tenMH, 0.3 * width - 1);

				j += 0.3 * width;
				gotoXY(posX + 1 + j, posY + 2 + k * 1);
				cout << CanGiuaChu(to_string(listLTC.ds[sc]->maLopTC), 0.15 * width - 1);

				j += 0.15 * width;
				gotoXY(posX + 1 + j, posY + 2 + k * 1);
				cout << CanGiuaChu(to_string(listLTC.ds[sc]->nhom), 0.15 * width - 1);

				int soSVDK = tinhSoSinhVienDKLTC(listLTC.ds[sc]);
				int slotTrong = listLTC.ds[sc]->soSVMax - soSVDK;

				j += 0.15 * width;
				gotoXY(posX + 1 + j, posY + 2 + k * 1);
				cout << CanGiuaChu(to_string(soSVDK), 0.1 * width - 1);

				j += 0.1 * width;
				gotoXY(posX + 1 + j, posY + 2 + k * 1);
				cout << CanGiuaChu(to_string(slotTrong), width - j - 1);
				k = k + 2;
				if (i == current) {
					TextColor(MACDINH);
				}
			}
		}
		if (sl > 0) {
			int ST = f;
			int a = 1;
			int chiso = 0;
			if (sl <= 11) {
				l = sl - 1;
			}
			for (int i = f; i <= l; i++) {
				ST++;
				chiso = node[i]->chiSo;
				if (l >= 0) {
					int j = 0;
					gotoXY(posX + width + 1, posY + 4 + a * 1);
					cout << CanGiuaChu(to_string(ST), 0.3 * widthSidebar - 1);

					j += 0.3 * widthSidebar;
					gotoXY(posX + width + 1 + j, posY + 4 + a * 1);
					cout << CanGiuaChu(to_string(listLTC.ds[chiso]->maLopTC), widthSidebar - j - 1);
					a = a + 2;
				}
			}
		}
		check = _getch();
		if (check == DOWN || check == UP) {
			DiChuyenThanhSang(n, first, last, current, check);
		}
		else if (check == ENTER) {
			DangKiLTC dk;
			LopTinChi* l = listLTC.ds[current];
			int tt = nodes[current]->chiso;
			dk.diem = 0;
			dk.maSV = sv.maSV;
			dk.trangThaiDK = 1;
			int add = themDangKiLTC(listLTC, node, sl, listLTC.ds[tt], dk);
			if (add == 1) {
				FeedBack("Dang ki LTC thanh cong!", posXContent + 1, posYContent + 2, widthContent - 1, DO);
			}
			if (add == 0) {
				FeedBack("Sinh vien da DK!", posXContent + 1, posYContent + 2, widthContent - 1, DO);
			}
			if (add == 2) {
				FeedBack("Sinh vien da dang ki lop tin chi khac!", posXContent + 1, posYContent + 2, widthContent - 1, DO);
			}
			if (add == 3) {
				FeedBack("Lop tin chi da thi, khong the dang ki!", posXContent + 1, posYContent + 2, widthContent - 1, DO);
			}
			giaiPhongNodePhu(node, sl);
			sl = 0;
			hienThiLTCDaDK(listLTC, node, sl, sv.maSV, ltc.nienKhoa.nienKhoaDau, ltc.nienKhoa.nienKhoaCuoi, ltc.hocKy);
		}
		else if (check == DEL) {
			VeKhungVien(129, 4, 30, 3);
			string info = "";
			int currentCursor = info.length();
			gotoXY(130, 5);
			cout << "Nhap ma LTC:";
			gotoXY(143, 5);
			int getCheck = -1;
			while (true) {
				if (getCheck == ESC) {
					Cls(128, 4, 34, 5);
					break;
				}
				if (_kbhit()) {
					getCheck = _getch();
					if ((getCheck >= '0' && getCheck <= '9') && (int)info.length() < 3) {
						info.insert(currentCursor, 1, (char)toupper(getCheck));
						for (int i = currentCursor; i < (int)info.length(); i++)
							cout << info[i];
						currentCursor++;
					}
					else if (getCheck == BACKSPACE && info.length() != 0)
					{
						info.erase(--currentCursor, 1);
						gotoXY(143 + currentCursor, 5);
						for (int i = currentCursor; i < (int)info.length() + 1; i++)
							cout << " ";
						gotoXY(143 + currentCursor, 5);
					}
					else if (getCheck == ENTER) {
						int dk = stoi(info);
						int xoa = XuLyXoaDangKiLTC(listLTC, node, sl, sv.maSV, dk);
						if (xoa == 1) {
							FeedBack("Xoa Dang ki LTC thanh cong!", posXContent + 1, posYContent + 2, widthContent - 1, DO);
							giaiPhongNodePhu(node, sl);
							sl = 0;
							hienThiLTCDaDK(listLTC, node, sl, sv.maSV, ltc.nienKhoa.nienKhoaDau, ltc.nienKhoa.nienKhoaCuoi, ltc.hocKy);
							XoaKhungDKLopTinChi();
						}
						if (xoa == 0) {
							FeedBack("Xoa Dang ki LTC khong thanh cong!", posXContent + 1, posYContent + 2, widthContent - 1, DO);
						}
						if (xoa == -1) {
							FeedBack("LTC chua dang ki!", posXContent + 1, posYContent + 2, widthContent - 1, DO);
						}
						if (xoa == 3) {
							FeedBack("Lop tin chi da thi, khong the huy!", posXContent + 1, posYContent + 2, widthContent - 1, DO);
						}
					}
				}
			}
		}
	}
	giaiPhongIndexDangKiLopTinChi(nodes, n);
	giaiPhongNodePhu(node, sl);
}

//==============================================CAU B: IN DANH SACH SV CON DK LOP TIN CHI===================================================

struct IndexDKLTC
{
	PTRDangKiLTC chiso;
};

void timKiemTheoThamSo(ListLTC& listLTC, IndexDKLTC* nodes[], int& n, int nkd, int nkc, int hk, string maMH, int nhom) {
	int vttrung = kiemTraTrungToHopKhoaLTC(listLTC, nkd, nkc, hk, maMH, nhom);
	if (vttrung >= 0 && listLTC.ds[vttrung]->trangThaiLop == 1) {
		for (PTRDangKiLTC p = listLTC.ds[vttrung]->DSDKLTC; p != NULL; p = p->next) {
			if (p->dk.trangThaiDK == 1) {
				nodes[n] = new IndexDKLTC;
				nodes[n]->chiso = p;
				n++;
			}
		}
	}
}

void giaiPhongIndexDKLTC(IndexDKLTC* nodes[], int& n) {
	for (int i = 0; i < n; i++) {
		delete nodes[i];
	}
}

int Nhap_NK_HK_MaMH_Nhom(ListLTC& listLTC, LopTinChi& ltc, int key, int& check)
{
	int r = -1;
	string temp = "";
	int x = posXContent + 30;

	switch (key)
	{
	case 1: {
		NhapDuLieu(temp, 4, x + 18, posYContent + 5, 4, check, 3);
		if (temp == "")
			break;
		ltc.nienKhoa.nienKhoaDau = stoi(temp);
		break;
	}
	case 2: {
		NhapDuLieu(temp, 4, x + 19, posYContent + 7, 4, check, 3);
		if (temp == "")
			break;
		ltc.nienKhoa.nienKhoaCuoi = stoi(temp);
		break;
	}
	case 3: {
		NhapDuLieu(temp, 1, x + 11, posYContent + 9, 4, check, 3);
		if (temp == "")
			break;
		ltc.hocKy = stoi(temp);
		break;
	}
	case 4:
		NhapDuLieu(ltc.maMH, 10, x + 15, posYContent + 11, 1, check, 1);
		break;
	case 5: {
		NhapDuLieu(temp, 3, x + 9, posYContent + 13, 4, check, 3);
		if (temp == "")
			break;
		ltc.nhom = stoi(temp);
		break;
	}
	default:
		break;
	}
	if (check == ESC) {
		return ESC;
	}
}

void chuyenTruongNhap_NK_HK_MaMH_Nhom(int& key, int& check) {
	if (check == UP || check == DOWN)
	{
		switch (check)
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
				key = 1;
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

void KhungNhap_NK_HK_MaMH_Nhom(string h) {
	int x  = posXContent + 30;
	VeKhungVien(x + 1, posYContent + 1, widthContent / 2 - 2, heightContent/2 - 2);
	gotoXY(x + 1 + (widthContent / 2 - 2) / 2 - (widthContent / 2 - 2) / 4, posYContent + 1);
	cout << CanGiuaChu(h, (widthContent / 2 - 2) / 2);

	int i = 0;
	gotoXY(x + 3, posYContent + 5 + i);
	cout << "Nien khoa dau";
	gotoXY(x + 17, posYContent + 5 + i);
	cout << ":";
	i += 2;
	gotoXY(x + 3, posYContent + 5 + i);
	cout << "Nien khoa cuoi";
	gotoXY(x + 18, posYContent + 5 + i);
	cout << ":";
	i += 2;
	gotoXY(x + 3, posYContent + 5 + i);
	cout << "Hoc ky";
	gotoXY(x + 10, posYContent + 5 + i);
	cout << ":";
	i += 2;
	gotoXY(x + 3, posYContent + 5 + i);
	cout << "Ma mon hoc";
	gotoXY(x + 14, posYContent + 5 + i);
	cout << ":";
	i += 2;
	gotoXY(x + 3, posYContent + 5 + i);
	cout << "Nhom";
	gotoXY(x + 8, posYContent + 5 + i);
	cout << ":";
}


int KiemTraThongTin_NK_HK_MaMH_Nhom(ListLTC &list,PTRMonHoc root, LopTinChi ltc)
{
	PTRMonHoc p;
	p = Search(root, ltc.maMH);
	int vttrung = kiemTraTrungToHopKhoaLTC(list, ltc.nienKhoa.nienKhoaDau, ltc.nienKhoa.nienKhoaCuoi, ltc.hocKy, ltc.maMH, ltc.nhom);
	if (ltc.nienKhoa.nienKhoaDau < 2020)
		return 2;
	else if (ltc.nienKhoa.nienKhoaCuoi < 2020 || ltc.nienKhoa.nienKhoaCuoi <= ltc.nienKhoa.nienKhoaDau)
		return 3;
	else if (ltc.hocKy <= 0 || ltc.hocKy > 3)
		return 4;
	else if (!KiemTraChuoi(ltc.maMH, 3) || !KiemTraChuoi(ltc.maMH, 5) || !KiemTraChuoi(ltc.maMH, 4))
		return 5;
	else if (p == NULL) {
		return 6;
	}
	else if (ltc.nhom <= 0 || ltc.nhom>999) {
		return 7;
	}
	else if (vttrung == -1) {
		return 8;
	}
	else if (list.ds[vttrung]->trangThaiLop == 0) {
		return 9;
	}
	return 1;
}

void DSSinhVienConDKLopTinChi(ListLTC& list, PTRMonHoc root,ListSV &listSV) {
	int key = 1;
	int check = -1;
	LopTinChi ltc;
	KhungNhap_NK_HK_MaMH_Nhom("Nhap thong tin");
	HuongDan(7);

	while (true)
	{
		int r = Nhap_NK_HK_MaMH_Nhom(list, ltc, key, check);
		chuyenTruongNhap_NK_HK_MaMH_Nhom(key, check);
		int k = KiemTraThongTin_NK_HK_MaMH_Nhom(list,root, ltc);
		if (r == ESC) {
			break;
		}
		if (key == 2 && k == 2) {
			FeedBack("Nien khoa dau trong, gom: 0-9, NKD >= 2020!", posXContent + 3, posYContent + 28, widthContent - 5, DO);
			key = 1;
		}
		else if (key == 3 && k == 3) {
			FeedBack("Nien khoa cuoi trong, gom: 0-9, NKC > NKD!", posXContent + 3, posYContent + 28, widthContent  - 5, DO);
			key = 2;
		}
		else if (key == 4 && k == 4) {
			FeedBack("Hoc ki trong, gom: 1-3!", posXContent + 3, posYContent + 28, widthContent  - 5, DO);
			key = 3;
		}
		else if (key == 5 && k == 5) {
			FeedBack("Ma mon hoc trong, gom: a-z, A-Z, 0-9, so ky tu <= 10!", posXContent + 3, posYContent + 28, widthContent - 5, DO);
			key = 4;
		}
		else if (key == 5 && k == 6) {
			FeedBack("Ma mon hoc chua ton tai!", posXContent + 3, posYContent + 28, widthContent  - 5, DO);
			key = 4;
		}
		else if (key == 1 && k == 7) {
			FeedBack("Nhom trong!, 0 < nhom <= 999", posXContent + 3, posYContent + 28, widthContent  - 5, DO);
			key = 5;
		}
		else if (k == 8) {
			FeedBack("Nien khoa, hoc ki, Ma mon hoc, Nhom khong ton tai!", posXContent + 3, posYContent + 28, widthContent  - 5, DO);
		}
		else if (k == 9) {
			FeedBack("Lop da bi huy!", posXContent + 3, posYContent + 28, widthContent  - 5, DO);
		}
		else if (k == 1) {
			Cls(TOADOX, TOADOY, TOADOX + CHIEUNGANG, CHIEUDOC + 1);
			hienThiSinhVienConDKLopTinChi(list, listSV,ltc,root);
			break;
		}
	}
}

void hienThiSinhVienConDKLopTinChi(ListLTC &listLTC,ListSV &listSV,LopTinChi &ltc,PTRMonHoc &root) {
	int first = 0;
	int last = 11;
	int current = first;

	int check = -1;

	int posX = posXContent + 1;
	int posY = posYContent + 0.15 * heightContent;
	int width = widthContent - 2;
	int height = heightContent - 0.15 * heightContent;
	veBangDSSVConDangKiLTC(posX, posY, width, height);
	
	HuongDan(2);

	IndexDKLTC* nodes[MAXDKLTC];
	int n = 0;
	timKiemTheoThamSo(listLTC, nodes, n, ltc.nienKhoa.nienKhoaDau, ltc.nienKhoa.nienKhoaCuoi, ltc.hocKy, ltc.maMH, ltc.nhom);

	gotoXY(3, 3);
	cout << "Nien khoa  : " << ltc.nienKhoa.nienKhoaDau << " - " << ltc.nienKhoa.nienKhoaCuoi<<endl;
	gotoXY(3, 4);
	cout << "Hoc ki     : " <<ltc.hocKy << endl;
	gotoXY(3, 5);
	cout << "Ma mon hoc : " <<ltc.maMH << endl;
	PTRMonHoc p = Search(root, ltc.maMH);
	gotoXY(3, 6);
	cout << "Ten mon hoc: "<<p->data.tenMH << endl;
	gotoXY(3, 7);
	cout << "Nhom       : "<<ltc.nhom << endl;
	int k = 1;
	int STT = 0;
	int j = 0;
	while (true) {
		k = 1;
		if (check == ESC) { break; }
		if (n <= 12) {
			last = n - 1;
		}
		STT = first;
		for (int i = first; i <= last; i++) {
			STT++;
			if (last >= 0) {
				if (i == current) {
					TextColor(240);
				}
				j = 0;
				gotoXY(posX + 1, posY + 2 + k * 1);
				cout << CanGiuaChu(to_string(STT), 0.1 * width - 1);

				j += 0.1 * width;
				gotoXY(posX + 1 + j, posY + 2 + k * 1);
				cout << CanGiuaChu(nodes[i]->chiso->dk.maSV, 0.3 * width - 1);

				int vt = kiemTraTrungMaSV(listSV, nodes[i]->chiso->dk.maSV);

				j += 0.3 * width;
				gotoXY(posX + 1 + j, posY + 2 + k * 1);
				cout << CanGiuaChu(listSV.ds[vt].ho, 0.3 * width - 1);

				j += 0.3 * width;
				gotoXY(posX + 1 + j, posY + 2 + k * 1);
				cout << CanGiuaChu(listSV.ds[vt].ten, width - j - 1);

				k = k + 2;
				if (i == current) {
					TextColor(MACDINH);
				}
			}
		}
		check = _getch();
		if (check == DOWN || check == UP) {
			DiChuyenThanhSang(n, first, last, current, check);
		}
	}
	giaiPhongIndexDKLTC(nodes, n);
}

//====================================================CAU H - HUY LOP TIN CHI=============================================================

struct HuyLopTinChi
{
	int chiSo;
};

// huy lop tin chi,
// loc ra lop nao chua thi
void DanhSachHuyLopTinChi(ListLTC& listLTC,HuyLopTinChi *HuyLTC[],int &n, int nkd, int nkc, int hocKy) {
	int sl = 0;
	LopTinChi* ltc;
	for (int i = 0; i < listLTC.sl; i++) {
		if (kiemTraLTCDaThi(listLTC, listLTC.ds[i]->maLopTC) == 0)
		{
			if (nkd == listLTC.ds[i]->nienKhoa.nienKhoaDau && nkc == listLTC.ds[i]->nienKhoa.nienKhoaCuoi && hocKy == listLTC.ds[i]->hocKy && listLTC.ds[i]->trangThaiLop == 1) {
				ltc = listLTC.ds[i];
				sl = tinhSoSinhVienDKLTC(ltc);
				if (ltc->soSVMin > sl) {
					HuyLTC[n] = new HuyLopTinChi;
					HuyLTC[n]->chiSo = i;
					n++;
				}
			}
		}
	}
}
void GiaiPhongHuyLopTinChi(HuyLopTinChi* HuyLTC[], int& n) {
	for (int i = 0; i < n; i++) {
		delete HuyLTC[i];
	}
}

// huy lop tin chi => dua trang thai ltc = 0,
// da thi thi ko dc huy
int XuLyHuyLopTinChi(ListLTC &listLTC, int maLTC) {
	int vt = ktTrungMaLopTinChi(listLTC, maLTC);
	if (vt == -1) {
		return 0;
	}
	else {
		for (PTRDangKiLTC p = listLTC.ds[vt]->DSDKLTC; p != NULL; p = p->next) {
			p->dk.trangThaiDK = 0;
		}
		listLTC.ds[vt]->trangThaiLop = 0;
		return 1;
	}
}

void HuyLopTinChi_NK_HK(ListLTC& list, PTRMonHoc root) {
	int key = 1;
	int check = -1;
	LopTinChi ltc;
	KhungNhap_NK_HK("Nhap thong tin");
	HuongDan(7);

	while (true)
	{
		int r = Nhap_NK_HK(list,ltc,key,check);
		chuyenTruongNhapLieu_NK_HK(key, check);
		int k = KiemTra_NK_HK(list,root, ltc);
		if (r == ESC) {
			break;
		}
		if (key == 2 && k == 2) {
			FeedBack("Nien khoa dau trong, gom: 0-9, NKD >= 2020!", posXContent + 3, posYContent + 28, widthContent  - 5, DO);
			key = 1;
		}
		else if (key == 3 && k == 3) {
			FeedBack("Nien khoa cuoi trong, gom: 0-9 , NKC > NKD (2020)!", posXContent + 3, posYContent + 28, widthContent  - 5, DO);
			key = 2;
		}
		else if (key == 1 && k == 4) {
			FeedBack("Hoc ki trong, gom: 1-3!", posXContent + 3, posYContent + 28, widthContent  - 5, DO);
			key = 3;
		}
		else if (k == 5) {
			FeedBack("Nien khoa, Hoc ki khong ton tai!", posXContent + 3, posYContent + 28, widthContent - 5, DO);
		}
		else if (k == 1) {
			gotoXY(3, 2);
			cout << "Nien Khoa  : " << ltc.nienKhoa.nienKhoaDau << " - " << ltc.nienKhoa.nienKhoaCuoi;
			gotoXY(3, 3);
			cout << "Hoc ki     : " << ltc.hocKy;
			Cls(posXContent, posYContent + 2, CHIEUNGANG, CHIEUDOC);
			CauH_HuyLopTinChi(list, root, ltc);
			Cls(TOADOX, TOADOY, CHIEUNGANG + 2, CHIEUDOC + 2); 
			break;
		}
	}
}

void CauH_HuyLopTinChi(ListLTC &listLTC,PTRMonHoc &root,LopTinChi &ltc) {
	int first = 0;
	int last = 11;
	int current = first;

	int check = -1;

	int posX = posXContent + 1;
	int posY = posYContent + 0.15 * heightContent;
	int width = widthContent - 2;
	int height = heightContent - 0.15 * heightContent;

	HuongDan(4);
	veBangLopTinChi(posX, posX, width, height);
	int n = 0;
	HuyLopTinChi* HuyLTC[MAXHUYLTC];
	int k = 0;
	int STT = 0;
	int j = 0;
	DanhSachHuyLopTinChi(listLTC, HuyLTC, n, ltc.nienKhoa.nienKhoaDau, ltc.nienKhoa.nienKhoaCuoi, ltc.hocKy);
	while (true) {
		k = 1;
		if (check == ESC) {
			break;
		}
		if (n <= 12) {
			last = n - 1;
		}
		STT = first;
		for (int i = first; i <= last; i++) {
			int cs = HuyLTC[i]->chiSo;
			STT++;
			if (last >= 0) {
				if (i == current) {
					TextColor(240);
				}
				j = 0;
				
				gotoXY(posX + 1, posY + 2 + k * 1);
				cout << CanGiuaChu(to_string(STT), 0.08 * width - 1);

				j += 0.08 * width;
				gotoXY(posX + 1 + j, posY + 2 + k * 1);
				cout << CanGiuaChu(listLTC.ds[cs]->maMH, 0.15 * width - 1);

				j += 0.15 * width;
				gotoXY(posX + 1 + j, posY + 2 + k * 1);
				PTRMonHoc p = Search(root, listLTC.ds[cs]->maMH);
				cout << CanGiuaChu(p->data.tenMH, 0.3 * width - 1);

				j += 0.3 * width;
				gotoXY(posX + 1 + j, posY + 2 + k * 1);
				cout << CanGiuaChu(to_string(listLTC.ds[cs]->nhom), 0.1 * width - 1);

				j += 0.1 * width;
				gotoXY(posX + 1 + j, posY + 2 + k * 1);
				cout << CanGiuaChu(to_string(listLTC.ds[cs]->maLopTC), 0.1 * width - 1);

				j += 0.1 * width;
				gotoXY(posX + 1 + j, posY + 2 + k * 1);
				cout << CanGiuaChu(to_string(listLTC.ds[cs]->soSVMin), 0.1 * width - 1);

				j += 0.1 * width;
				gotoXY(posX + 1 + j, posY + 2 + k * 1);
				cout << CanGiuaChu(to_string(listLTC.ds[cs]->soSVMax), 0.1 * width - 1);

				j += 0.1 * width;
				gotoXY(posX + 1 + j, posY + 2 + k * 1);
				cout << CanGiuaChu((listLTC.ds[cs]->trangThaiLop == 1 ? "Mo" : "Huy"), width - j - 1);

				k += 2;
				if (i == current) {
					TextColor(MACDINH);
				}
			}
			else {
				return;
			}
		}
		check = _getch();
		if (check == DOWN || check == UP) {
			DiChuyenThanhSang(n, first, last, current, check);
		}
		else if (check == DEL && listLTC.sl > 0) {
			int chiSo = HuyLTC[current]->chiSo;
			int kt = XuLyHuyLopTinChi(listLTC, listLTC.ds[chiSo]->maLopTC);
			GiaiPhongHuyLopTinChi(HuyLTC, n);
			n = 0;
			DanhSachHuyLopTinChi(listLTC, HuyLTC, n, ltc.nienKhoa.nienKhoaDau, ltc.nienKhoa.nienKhoaCuoi, ltc.hocKy);

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
				FeedBack("Huy lop tin chi thanh cong!", posXContent + 1, posYContent + 2, widthContent - 1, DO);
			}
			else if (kt == 0) FeedBack("Huy lop tin chi khong thanh cong!", posXContent + 1, posYContent + 2, widthContent - 1, DO);
			Cls(posXSidebar + 1, posYSidebar + 1, widthSidebar - 1, heightSidebar - 1);
			ClsDanhSachLTC();
		}
	}
	GiaiPhongHuyLopTinChi(HuyLTC, n);
}

//========================================CAU J IN BANG DIEM===============================================

struct IndexBangDiem
{
	PTRDangKiLTC chiSo;
};

void DanhSachDiemSinhVienTheoLTC(ListLTC& listLTC,IndexBangDiem *nodes[],int &n,int nkd, int nkc, int hk, int nhom, string maMH) {
	int vt = kiemTraTrungToHopKhoaLTC(listLTC, nkd, nkc, hk, maMH, nhom);
	if (vt >= 0 && listLTC.ds[vt]->trangThaiLop == 1) {
		for (PTRDangKiLTC p = listLTC.ds[vt]->DSDKLTC; p != NULL; p = p->next) {
			if (p->dk.trangThaiDK == 1) {
				nodes[n] = new IndexBangDiem;
				nodes[n]->chiSo = p;
				n++;
			}
		}
	}
}

void giaiPhongIndexBangDiem(IndexBangDiem* nodes[], int& n) {
	for (int i = 0; i < n; i++) {
		delete nodes[i];
	}
}

void InBangDiemCuaMotLTC(ListLTC& list, PTRMonHoc root, ListSV& listSV) {
	int key = 1;
	int check = -1;
	LopTinChi ltc;
	KhungNhap_NK_HK_MaMH_Nhom("Nhap thong tin");
	HuongDan(7);

	while (true)
	{
		int r = Nhap_NK_HK_MaMH_Nhom(list, ltc, key, check);
		chuyenTruongNhap_NK_HK_MaMH_Nhom(key, check);
		int k = KiemTraThongTin_NK_HK_MaMH_Nhom(list,root, ltc);
		if (r == ESC) {
			break;
		}
		if (key == 2 && k == 2) {
			FeedBack("Nien khoa dau trong, gom: 0-9, NKD >= 2020!", posXContent + 3, posYContent + 28, widthContent  - 5, DO);
			key = 1;
		}
		else if (key == 3 && k == 3) {
			FeedBack("Nien khoa cuoi trong, gom: 0-9, NKC > NKD (2020)!", posXContent + 3, posYContent + 28, widthContent - 5, DO);
			key = 2;
		}
		else if (key == 4 && k == 4) {
			FeedBack("Hoc ki trong, gom: 1-3!", posXContent + 3, posYContent + 28, widthContent - 5, DO);
			key = 3;
		}
		else if (key == 5 && k == 5) {
			FeedBack("Ma mon hoc trong, gom: a-z,A-Z,0-9, so ky tu <= 15!", posXContent + 3, posYContent + 28, widthContent  - 5, DO);
			key = 4;
		}
		else if (key == 5 && k == 6) {
			FeedBack("MaMH chua ton tai!", posXContent + 3, posYContent + 28, widthContent  - 5, DO);
			key = 4;
		}
		else if (key == 1 && k == 7) {
			FeedBack("Nhom trong!, 0 < nhom <= 999", posXContent + 3, posYContent + 28, widthContent  - 5, DO);
			key = 5;
		}
		else if (k == 8) {
			FeedBack("Nien khoa, hoc ki, ma mon hoc, nhom khong ton tai!", posXContent + 3, posYContent + 28, widthContent - 5, DO);
		}
		else if (k == 9) {
			FeedBack("Lop tin chi da huy!", posXContent + 3, posYContent + 28, widthContent  - 5, DO);
		}
		else if (k == 1) {
			Cls(posXContent, posYContent, widthContent, CHIEUDOC);
			int vttrung = kiemTraTrungToHopKhoaLTC(list, ltc.nienKhoa.nienKhoaDau, ltc.nienKhoa.nienKhoaCuoi, ltc.hocKy, ltc.maMH, ltc.nhom);
			int slsv = tinhSoSinhVienDKLTC(list.ds[vttrung]);
			if (slsv == 0) {
				FeedBack("Lop tin chi chua co sinh vien nao dk!", posXContent + 1, posYContent + 2, widthContent - 1, DO);
				break;
			}
			BangDiem(list, root, listSV, ltc);
			Cls(TOADOX, TOADOY, TOADOX + CHIEUNGANG, CHIEUDOC + 1);
			break;
		}
	}
}

void BangDiem(ListLTC& listLTC, PTRMonHoc& root, ListSV& listSV, LopTinChi& ltc) {
	int first = 0;
	int last = 11;
	int current = first;

	int check = -1;

	int posX = posXContent + 1;
	int posY = posYContent + 0.15 * heightContent;
	int width = widthContent - 2;
	int height = heightContent - 0.15 * heightContent;
	HuongDan(2);

	PTRMonHoc p = Search(root, ltc.maMH);

	string title = "BANG DIEM MON " + p->data.tenMH;

	veBangDiem(posX, posX, width, height);
	Box(title, 70, 2, TOADOX + 30, TOADOY, 159);
	gotoXY(TOADOX + 40, TOADOY + 4);
	cout << "Nien Khoa : " << ltc.nienKhoa.nienKhoaDau << " - " << ltc.nienKhoa.nienKhoaCuoi << "   ";
	cout << "Hoc ky : " << ltc.hocKy << "  ";
	cout << "Nhom : " << ltc.nhom;
	int n = 0;
	IndexBangDiem* nodes[MAXHUYLTC];
	int k = 1;
	int STT = 0;
	string temp = "";
	int j = 0;
	PTRDangKiLTC cs;
	DanhSachDiemSinhVienTheoLTC(listLTC, nodes, n, ltc.nienKhoa.nienKhoaDau, ltc.nienKhoa.nienKhoaCuoi, ltc.hocKy, ltc.nhom, ltc.maMH);
	while (true) {
		k = 1;
		if (check == ESC) {
			break;
		}
		if (n <= 12) {
			last = n - 1;
		}
		STT = first;
		for (int i = first; i <= last; i++) {
			cs = nodes[i]->chiSo;
			STT++;
			if (last >= 0) {
				if (i == current) {
					TextColor(240);
				}
				j = 0;

				gotoXY(posX + 1, posY + 2 + k * 1);
				cout << CanGiuaChu(to_string(STT), 0.1 * width - 1);

				j += 0.1 * width;
				gotoXY(posX + 1 + j, posY + 2 + k * 1);
				cout << CanGiuaChu(cs->dk.maSV, 0.2 * width - 1);

				int vt = kiemTraTrungMaSV(listSV, cs->dk.maSV);
				j += 0.2 * width;
				gotoXY(posX + 1 + j, posY + 2 + k * 1);
				cout << CanGiuaChu(listSV.ds[vt].ho, 0.3 * width - 1);

				j += 0.3 * width;
				gotoXY(posX + 1 + j, posY + 2 + k * 1);
				cout << CanGiuaChu(listSV.ds[vt].ten, 0.2 * width - 1);

				j += 0.2 * width;

				gotoXY(posX + 1 + j, posY + 2 + k * 1);
				temp = to_string(cs->dk.diem);
				temp = DinhDangKieuSoThuc(temp);
				cout << CanGiuaChu((temp), width - j - 1);

				k += 2;
				if (i == current) {
					TextColor(MACDINH);
				}
			}
			else {
				return;
			}
		}
		check = _getch();
		if (check == DOWN || check == UP) {
			DiChuyenThanhSang(n, first, last, current, check);
		}
	}
	giaiPhongIndexBangDiem(nodes, n);
}

//==========================================CAU K SINH VIEN HUY DK LTC======================================
struct SVHuyDK {
	int chiSo;
};

// kiem tra lop da huy chua => boi neu huy thi khong can huy nua
// o day sinh vien la nguoi duy dk=> can kiem tra sv co dk nua hay khong => trang thai dk  == 1
void sinhVienHuyDangKiLTC(ListLTC& listLTC, SVHuyDK *node[], int &n,string maSV, int nkd, int nkc, int hocKy) {
	for (int i = 0; i < listLTC.sl; i++) {
		if (nkd == listLTC.ds[i]->nienKhoa.nienKhoaDau && nkc == listLTC.ds[i]->nienKhoa.nienKhoaCuoi && hocKy == listLTC.ds[i]->hocKy && listLTC.ds[i]->trangThaiLop == 1) {
			for (PTRDangKiLTC p = listLTC.ds[i]->DSDKLTC; p != NULL; p = p->next) {
				if (p->dk.trangThaiDK == 1 && p->dk.maSV.compare(maSV) == 0) {
					node[n] = new SVHuyDK;
					node[n]->chiSo = i;
					n++;
				}
			}
		}
	}
}

void giaiPhongSVHuyDK(SVHuyDK *node[], int &n) {
	for (int i = 0; i < n; i++) {
		delete node[i];
	}
}

void SVHuyDKTinChi_NK_HK(ListLTC& list, PTRMonHoc root,SinhVien &sv) {
	int key = 1;
	int check = -1;
	LopTinChi ltc;
	KhungNhap_NK_HK("Nhap thong tin");
	HuongDan(7);
	while (true)
	{
		int r = Nhap_NK_HK(list,ltc, key, check);
		chuyenTruongNhapLieu_NK_HK(key, check);
		int k = KiemTra_NK_HK(list, root, ltc);
		if (r == ESC) {
			break;
		}
		if (key == 2 && k == 2) {
			FeedBack("Nien khoa dau trong!", posXContent + 3, posYContent + 28, widthContent - 5, DO);
			key = 1;
		}
		else if (key == 3 && k == 3) {
			FeedBack("Nien khoa cuoi trong!", posXContent + 3, posYContent + 28, widthContent  - 5, DO);
			key = 2;
		}
		else if (key ==  1 && k == 4) {
			FeedBack("Hoc ki trong!", posXContent + 3, posYContent + 28, widthContent  - 5, DO);
			key = 3;
		}
		else if (k == 5) {
			FeedBack("Nien khoa,! Hoc ki khong ton tai!", posXContent + 3, posYContent + 28, widthContent  - 5, DO);
		}
		else if (k == 1) {
			gotoXY(120, 3);
			cout << "Nien Khoa  : " << ltc.nienKhoa.nienKhoaDau << " - " << ltc.nienKhoa.nienKhoaCuoi;
			gotoXY(120, 4);
			cout << "Hoc ki     : " << ltc.hocKy;
			Cls(posXContent, posYContent + 2, CHIEUNGANG, CHIEUDOC);
			BangSVHuyDK(list, root, ltc, sv);
			Cls(TOADOX, TOADOY, CHIEUNGANG + 2, CHIEUDOC + 2);
			break;
		}
	}
}

void SinhVienHuyDangKiLTC(ListLTC& list, PTRMonHoc root, ListSV& listSV) {
	int key = 1;
	int check = -1;
	SinhVien sv;
	KhungNhapMaTimKiem("Nhap thong tin", "Nhap ma sinh vien");
	HuongDan(8);
	while (true)
	{
		int r = NhapMaSinhVien(sv, key, check);
		int k = KiemTraMaSinhVien(listSV, sv);
		if (r == ESC) {
			break;
		}
		if (k == 2) {
			FeedBack("Ma sinh vien khong hop le, gom: a-z,A-Z,0-9, so ky tu <= 15!", posXContent + 3, posYContent + 23, widthContent  - 5, DO);
			key = 1;
		}
		else if (k == 3) {
			FeedBack("Ma sinh vien chua ton tai!", posXContent + 3, posYContent + 23, widthContent - 5, DO);
			key = 1;
		}
		else if (k == 1) {
			int i = kiemTraTrungMaSV(listSV, sv.maSV);
			gotoXY(3, 2);
			cout << "Ma lop  : " << listSV.ds[i].maLop;
			gotoXY(3, 3);
			cout << "Ma SV   : " << sv.maSV;
			gotoXY(3, 4);
			cout << "Ho ten  : " << listSV.ds[i].ho << " " << listSV.ds[i].ten;
			gotoXY(3, 5);
			cout << "Phai    : " << (listSV.ds[i].phai == 1 ? "Nam" : "Nu");
			gotoXY(3, 6);
			cout << "SDT     : " << listSV.ds[i].soDT;
			Cls(posXContent, posYContent + 2, widthContent, CHIEUDOC);
			SVHuyDKTinChi_NK_HK(list, root,sv);
			Cls(TOADOX, TOADOY, CHIEUNGANG, CHIEUDOC);
			break;
		}
	}
}

int XuLySVHuyDangKiLopTinChi(PTRDangKiLTC &first,string maSV,ListLTC &list,int maLTC) {
	PTRDangKiLTC vt = KiemTraTrungMaSVDKLTC(first,maSV);
	int kt = kiemTraLTCDaThi(list, maLTC);
	if (kt == 1) {
		return 2;
	}
	if(kt == 0){
		vt->dk.trangThaiDK = 0;
		return 1;
	}
}

void BangSVHuyDK(ListLTC& listLTC, PTRMonHoc& root, LopTinChi& ltc,SinhVien &sv) {
	int first = 0;
	int last = 11;
	int current = first;

	int check = -1;

	int posX = posXContent + 1;
	int posY = posYContent + 0.15 * heightContent;
	int width = widthContent - 2;
	int height = heightContent - 0.15 * heightContent;

	HuongDan(4);
	veBangLopTinChi(posX, posX, width, height);
	int n = 0;
	SVHuyDK* node[MAXHUYLTC];
	int k = 1;
	PTRMonHoc p;
	int j = 0;
	int STT = 0;
	int cs = 0;
	sinhVienHuyDangKiLTC(listLTC, node, n, sv.maSV, ltc.nienKhoa.nienKhoaDau, ltc.nienKhoa.nienKhoaCuoi, ltc.hocKy);
	while (true) {
		k = 1;
		if (check == ESC) {
			break;
		}
		if (n <= 12) {
			last = n - 1;
		}
		STT = first;
		for (int i = first; i <= last; i++) {
			cs = node[i]->chiSo;
			STT++;
			if (last >= 0) {
				if (i == current) {
					TextColor(240);
				}
				j = 0;
				gotoXY(posX + 1, posY + 2 + k * 1);
				cout << CanGiuaChu(to_string(STT), 0.08 * width - 1);

				j += 0.08 * width;
				gotoXY(posX + 1 + j, posY + 2 + k * 1);
				cout << CanGiuaChu(listLTC.ds[cs]->maMH, 0.15 * width - 1);

				j += 0.15 * width;
				gotoXY(posX + 1 + j, posY + 2 + k * 1);
				p = Search(root, listLTC.ds[cs]->maMH);
				cout << CanGiuaChu(p->data.tenMH, 0.3 * width - 1);

				j += 0.3 * width;
				gotoXY(posX + 1 + j, posY + 2 + k * 1);
				cout << CanGiuaChu(to_string(listLTC.ds[cs]->nhom), 0.1 * width - 1);

				j += 0.1 * width;
				gotoXY(posX + 1 + j, posY + 2 + k * 1);
				cout << CanGiuaChu(to_string(listLTC.ds[cs]->maLopTC), 0.1 * width - 1);

				j += 0.1 * width;
				gotoXY(posX + 1 + j, posY + 2 + k * 1);
				cout << CanGiuaChu(to_string(listLTC.ds[cs]->soSVMin), 0.1 * width - 1);
				j += 0.1 * width;
				gotoXY(posX + 1 + j, posY + 2 + k * 1);
				cout << CanGiuaChu(to_string(listLTC.ds[cs]->soSVMax), 0.1 * width - 1);

				j += 0.1 * width;
				gotoXY(posX + 1 + j, posY + 2 + k * 1);
				cout << CanGiuaChu(listLTC.ds[cs]->trangThaiLop == 1 ? "Mo" : "Huy", width - j - 1);

				k += 2;
				if (i == current) {
					TextColor(MACDINH);
				}
			}
			else {
				return;
			}
		}
		check = _getch();
		if (check == DOWN || check == UP) {
			DiChuyenThanhSang(n, first, last, current, check);
		}
		else if (check == DEL && listLTC.sl > 0) {
			int chiSo = node[current]->chiSo;
			int kt = XuLySVHuyDangKiLopTinChi(listLTC.ds[chiSo]->DSDKLTC, sv.maSV,listLTC,listLTC.ds[chiSo]->maLopTC);
			giaiPhongSVHuyDK(node, n);
			n = 0;
			sinhVienHuyDangKiLTC(listLTC, node, n, sv.maSV, ltc.nienKhoa.nienKhoaDau, ltc.nienKhoa.nienKhoaCuoi, ltc.hocKy);
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
				FeedBack("Huy dang ki lop tin chi thanh cong!", posXContent + 1, posYContent + 2, widthContent - 1, DO);
			}
			else if (kt == 0) FeedBack("Huy dang ki lop tin chi khong thanh cong!", posXContent + 1, posYContent + 2, widthContent - 1, DO);
			else if (kt == 2) FeedBack("Lop tin chi da thi,khong duoc huy!", posXContent + 1, posYContent + 2, widthContent - 1, DO);
			Cls(posXSidebar + 1, posYSidebar + 1, widthSidebar - 1, heightSidebar - 1);
			ClsDanhSachLTC();
		}
	}
	giaiPhongSVHuyDK(node, n);
}

//=====================================================CAU I: NHAP DIEM============================================================

void NhapDiem(ListLTC& list, PTRMonHoc root, ListSV& listSV) {
	int key = 1;
	int check = -1;
	LopTinChi ltc;
	KhungNhap_NK_HK_MaMH_Nhom("Nhap thong tin");
	bool kt = true;
	HuongDan(7);
	while (kt == true)
	{
		int r = Nhap_NK_HK_MaMH_Nhom(list, ltc, key, check);
		chuyenTruongNhap_NK_HK_MaMH_Nhom(key, check);
		int k = KiemTraThongTin_NK_HK_MaMH_Nhom(list, root, ltc);
		if (r == ESC) {
			break;
		}
		if (key == 2 && k == 2) {
			FeedBack("Nien khoa dau khong hop le!", posXContent + 3, posYContent + 28, widthContent - 5, DO);
			key = 1;
		}
		else if (key == 3 && k == 3) {
			FeedBack("Nien khoa cuoi khong hop le!", posXContent + 3, posYContent + 28, widthContent  - 5, DO);
			key = 2;
		}
		else if (key == 4 && k == 4) {
			FeedBack("Hoc ki khong hop le! Gom 1-3!", posXContent + 3, posYContent + 28, widthContent  - 5, DO);
			key = 3;
		}
		else if (key == 5 && k == 5) {
			FeedBack("Ma mon hoc trong!", posXContent + 3, posYContent + 28, widthContent  - 5, DO);
			key = 4;
		}
		else if (key == 5 && k == 6) {
			FeedBack("MaMH chua ton tai!", posXContent + 3, posYContent + 28, widthContent  - 5, DO);
			key = 4;
		}
		else if (key == 1 && k == 7) {
			FeedBack("Nhom trong!, 0 < nhom < 250", posXContent + 3, posYContent + 28, widthContent  - 5, DO);
			key = 5;
		}
		else if (k == 8) {
			FeedBack("Nien khoa, Hoc ki, Ma mon hoc, nhom khong ton tai!", posXContent + 3, posYContent + 28, widthContent - 5, DO);
		}
		else if (k == 9) {
			FeedBack("Lop tin chi da huy!", posXContent + 3, posYContent + 28, widthContent  - 5, DO);
		}
		else if (k == 1) {
			Cls(TOADOX, TOADOY, TOADOX + CHIEUNGANG, CHIEUDOC + 1);
			int slsv = 0;
			int demDong = 0; int demSV = 0; int demDiem = 0;
			int vttrung = kiemTraTrungToHopKhoaLTC(list, ltc.nienKhoa.nienKhoaDau, ltc.nienKhoa.nienKhoaCuoi, ltc.hocKy, ltc.maMH, ltc.nhom);
			int vitri = 0;
			slsv = tinhSoSinhVienDKLTC(list.ds[vttrung]);
			if (slsv == 0) {
				FeedBack("Lop tin chi chua co sinh vien nao dk!", posXContent + 1, posYContent + 2, widthContent - 1, DO);
				kt = false;
			}
			else {
				HuongDan(5);
				SinhVien *SV = new SinhVien[slsv + 1];
				string *Tam = new string[slsv + 1];

				for (PTRDangKiLTC p = list.ds[vttrung]->DSDKLTC; p != NULL; p = p->next) {
					int vtsv = kiemTraTrungMaSV(listSV, p->dk.maSV);
					if (vtsv >= 0 && p->dk.trangThaiDK == 1) {
						SV[demSV] = listSV.ds[vtsv];
						demSV++;
					}
				}

				for (int i = 0; i < demSV; i++) {
					for (PTRDangKiLTC p = list.ds[vttrung]->DSDKLTC; p != NULL; p = p->next) {
						if (p->dk.maSV.compare(SV[i].maSV) == 0 && p->dk.trangThaiDK == 1) {
							Tam[i] = to_string(p->dk.diem);
							Tam[i] = DinhDangKieuSoThuc(Tam[i]);
						}
					}
				}
				int first = 0;
				int last = 11;
				int current = first; 
				int check = -1;
				int posX = posXContent + 1;
				int posY = posYContent + 0.15 * heightContent;
				int width = widthContent - 2;
				int height = heightContent - 0.15 * heightContent;
				PTRMonHoc p = Search(root, ltc.maMH);
				string title = "NHAP DIEM MON " + p->data.tenMH;
				veBangDiem(posX, posX, width, height);
				Box(title, 70, 2, TOADOX + 30, TOADOY, 159);
				gotoXY(TOADOX + 40, TOADOY + 4);
				cout << "Nien Khoa : " << ltc.nienKhoa.nienKhoaDau << " - " << ltc.nienKhoa.nienKhoaCuoi << "   ";
				cout << "Hoc ky : " << ltc.hocKy << "  ";
				cout << "Nhom : " << ltc.nhom;
				int k = 1;
				if (slsv <= 12) {
					last = slsv - 1;
				}
				int STT = first;
				for (int i = first; i <= last; i++) {
					STT++;
					if (last >= 0) {
						int j = 0;
						gotoXY(posX + 1, posY + 2 + k * 1);
						cout << CanGiuaChu(to_string(STT), 0.1 * width - 1);

						j += 0.1 * width;
						gotoXY(posX + 1 + j, posY + 2 + k * 1);
						cout << CanGiuaChu(SV[i].maSV, 0.2 * width - 1);

						j += 0.2 * width;
						gotoXY(posX + 1 + j, posY + 2 + k * 1);
						cout << CanGiuaChu(SV[i].ho, 0.3 * width - 1);

						j += 0.3 * width;
						gotoXY(posX + 1 + j, posY + 2 + k * 1);
						cout << CanGiuaChu(SV[i].ten, 0.2 * width - 1);

						j += 0.2 * width;
						gotoXY(111, posY + 2 + k * 1);
						cout << Tam[i];
						k += 2;
					}
					else {
						return;
					}
				}
				int y = posY + 3;
				vitri = Tam[0].length();
				int x = 111;
				while (kt == true) {
					gotoXY(x + vitri, y);

					if (check == ESC) kt = false;

					if (_kbhit())
					{
						check = _getch();

						if (((check >= 48 && check <= 57) || check == DOT) && vitri < 3) {
							Tam[demDiem].insert(vitri, 1, (char)check);
							for (int i = vitri; i < (int)Tam[demDiem].length(); i++)
								cout << Tam[demDiem][i];
							vitri++;
						}
						else if (check == BACKSPACE && Tam[demDiem].length() != 0 && vitri > 0)
						{
							Tam[demDiem].erase(--vitri, 1);
							gotoXY(x + vitri, y);
							for (int i = vitri; i < (int)Tam[demDiem].length() + 1; i++)
								cout << " ";
							gotoXY(x + vitri, y);
						}
						else if (Tam[demDiem].length() == 0) {
							FeedBack("Thong tin khong hop le, 0 <= Diem <= 10!, khong rong!!", posXContent + 1, posYContent + 2, widthContent - 1, DO);
						}
						else if (check == UP && y > posY + 3) {
							Tam[demDiem][vitri] = '\0';
							if (stof(Tam[demDiem]) > 10 || stof(Tam[demDiem]) < 0) {
								FeedBack("Thong tin khong hop le, 0 <= Diem <= 10!, khong rong!!", posXContent + 1, posYContent + 2, widthContent - 1, DO);
							}
							// cai doan nay de giu lại nhap cho den khi nao dung du lieu dinh dang thi thoi.
							else {
								demDiem--;
								vitri = Tam[demDiem].length();
								y = y - 2;
								gotoXY(x + vitri, y);
							}
						}
						else if (check == DOWN && demDiem < demSV - 1) {
							Tam[demDiem][vitri] = '\0';
							if (stof(Tam[demDiem]) > 10 || stof(Tam[demDiem]) < 0) {
								FeedBack("Thong tin khong hop le, 0 <= Diem <= 10!, khong rong!!", posXContent + 1, posYContent + 2, widthContent - 1, DO);
							}
							else {
								demDiem++;
								vitri = Tam[demDiem].length();
								y = y + 2;
								gotoXY(x + vitri, y);
							}
						}
						else if (check == ENTER)
						{
							if (stof(Tam[demDiem]) > 10 || stof(Tam[demDiem]) < 0) {
								FeedBack("Thong tin khong hop le, 0 <= Diem <= 10!, khong rong!!", posXContent + 1, posYContent + 2, widthContent - 1, DO);
							}
							else {
								FeedBack("Sua Diem Thanh Cong!", posXContent + 1, posYContent + 2, widthContent - 1, DO);
							}
						}
						else if (check == F2)
						{
							Tam[demDiem][vitri] = '\0';
							for (PTRDangKiLTC p = list.ds[vttrung]->DSDKLTC; p != NULL; p = p->next) {
								for (int i = 0; i < demSV; i++) {
									if (p->dk.maSV.compare(SV[i].maSV) == 0) {
											p->dk.diem = stof(Tam[i]);
									}
								}
							}
							ghiFileDanhSachDKLTC(list);
							FeedBack("Luu file thanh cong!", posXContent + 1, posYContent + 2, widthContent - 1, DO);
						}
					}
				}
				delete []SV; 
				delete []Tam;
			}
		}
	}
}
