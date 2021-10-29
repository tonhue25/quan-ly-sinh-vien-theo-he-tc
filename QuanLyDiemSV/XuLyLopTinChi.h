#pragma once
#include "XuLyMonHoc.h"

int KiemTraThongTinLTC(ListLTC& listLTC,PTRMonHoc root, LopTinChi ltc);
void QuanLyLTC(ListLTC& listLTC, PTRMonHoc& root, LopTinChi& ltc);
void chuyenTruongNhapLieu_NK_HK(int& key, int& check);
void KhungNhap_NK_HK(string h);
int KiemTra_NK_HK(ListLTC& list, PTRMonHoc root, LopTinChi& ltc);
int Nhap_NK_HK(ListLTC& listLTC, LopTinChi& ltc, int key, int& check);

//==========================================GIAI PHONG====================================================
struct DSLopTinChi {
	int maLTC;
	int chiSo;
};

void DSLopTinChiTheoNienKhoa_HocKi(ListLTC& listLTC, DSLopTinChi* DS[], int& n, int nkd, int nkc, int hk);
void giaiPhongMangConTro_LTC(DSLopTinChi* DS[], int& n);

void giaiPhongDKLTC(PTRDangKiLTC& first) {
	PTRDangKiLTC p;
	while (first != NULL) {
		p = first;
		first = first->next;
		delete p;
	}
}

//giai phong mang con tro lop tin chi: giai phong tung con tro, giai phong dslk cua con tro do
void GiaiPhongMangConTroLTC(ListLTC &l) {
	for (int i = 0; i < l.sl; i++) {
		if (l.ds[i]->DSDKLTC != NULL) {
			giaiPhongDKLTC(l.ds[i]->DSDKLTC);
		}
		delete l.ds[i];
	}
}

//==================================================TINH SO SV DKLTC==========================================================
// tin so sinh vien dk ltc => kiem tra coi lop nay co dc xoa hay khong// co sv dk thi khong dc xoa
int tinhSoSinhVienDKLTC(LopTinChi *ltc) {
	int count = 0;
	for (PTRDangKiLTC p = ltc->DSDKLTC; p != NULL; p = p->next) {
		if (p->dk.trangThaiDK == 1) {
			count++;
		}
	}
	return count;
}

//==============================================THEM LOP TIN CHI====================================
// them theo kieu insert order, sx theo ma lop tin chi (du lop tin chi co ma lop tin chi tang dan roi)
// mang con tro, trc khi them vao thi can new vung nho moi cho no

int InsertOrder_LTC(ListLTC &l, LopTinChi ltc) {
	int j, k;

	if (l.sl == DSLOPTINCHI) return 0; 

	for (j = 0; j < l.sl && l.ds[j]->maLopTC < ltc.maLopTC; j++);

	for (k = l.sl - 1; k >= j; k--)
		l.ds[k + 1] = l.ds[k];

	l.ds[j] = new LopTinChi;
	*l.ds[j] = ltc; 
	l.sl++;
	return 1;
}

//int Them_MangConTro(DSLopTinChi* DS[],int n, LopTinChi ltc) {
//	int j, k;
//	if (n == DSLOPTINCHI) return 0;
//	for (j = 0; j < n && DS[j]->maLTC < ltc.maLopTC; j++);
//	for (k = n - 1; k >= j; k--)
//		DS[k + 1] = DS[k];
//	DS[j] = new DSLopTinChi;
//	DS[j]->chiSo = k;
//	DS[j]->maLTC = ltc.maLopTC;
//	n++;
//	return 1;
//}
//=============================================KIEM TRA DK NHAP/XUAT LOP TIN CHI===================================

int ktTrungMaLopTinChi(ListLTC &l, int maLTC) {
	for (int i = 0; i < l.sl; i++) {
		if (maLTC == l.ds[i]->maLopTC) {
			return i;
		}
	}
	return -1;
}

// khi them lop tin chi can kiem tra co trung to hop khoa khong nhe: nk,hk,mamh,nhom => khong kt la trung a
int kiemTraTrungToHopKhoaLTC(ListLTC &l, int nkd, int nkc, int hk, string maMH, int nhom) {
	for (int i = 0; i < l.sl; i++) {
		if (l.ds[i]->nienKhoa.nienKhoaDau == nkd && l.ds[i]->nienKhoa.nienKhoaCuoi == nkc && l.ds[i]->hocKy == hk && l.ds[i]->maMH.compare(maMH) == 0 && l.ds[i]->nhom == nhom) {
			return i;
		}
	}
	return -1;
}

//int kiemTraTrung_NK_HK_MAMH_NHOM_TRANGTHAI(ListLTC& l, int nkd, int nkc, int hk, string maMH, int nhom) {
//	for (int i = 0; i < l.sl; i++) {
//		if (l.ds[i]->nienKhoa.nienKhoaDau == nkd && l.ds[i]->nienKhoa.nienKhoaCuoi == nkc && l.ds[i]->hocKy == hk && l.ds[i]->maMH.compare(maMH) == 0 && l.ds[i]->nhom == nhom && l.ds[i]->trangThaiLop == 1) {
//			return i;
//		}
//	}
//	return -1;
//}

int kiemTraTrung_NK_HK(ListLTC& l, int nkd, int nkc, int hk) {
	for (int i = 0; i < l.sl; i++) {
		if (l.ds[i]->nienKhoa.nienKhoaDau == nkd && l.ds[i]->nienKhoa.nienKhoaCuoi == nkc && l.ds[i]->hocKy == hk) {
			return i;
		}
	}
	return -1;
}

//============================================XOA LOP TIN CHI======================================================

int xoaLopTinChi(ListLTC &l, int maLTC) {
	int i = ktTrungMaLopTinChi(l, maLTC);
	if (i == -1) return 0;
	else
	{
		delete  l.ds[i];
		for (int j = i + 1; j < l.sl ; j++)
			l.ds[j - 1] = l.ds[j];

		l.sl--;
		return 1;
	}
}

int kiemTraTrungMaLTC_MangConTro(DSLopTinChi* DS[], int& n, int maLTC) {
	for (int i = 0; i < n; i++) {
		if (DS[i]->maLTC == maLTC) {
			return i;
		}
	}
	return -1;
}

//int xoaMangConTro_LTC(DSLopTinChi *DS[],int &n,int maLTC) {
//	int i = kiemTraTrungMaLTC_MangConTro(DS,n, maLTC);
//	if (i == -1) return 0;
//	else
//	{
//		delete  DS[i];
//		for (int j = i + 1; j < n; j++)
//			DS[j - 1] = DS[j];
//
//		n--;
//		return 1;
//	}
//}

void KhungNhapThongTinLopTinChi(string k)
{
	VeKhungVien(posXSidebar + 1, posYSidebar + 1, widthSidebar - 2, heightSidebar - 2);
	gotoXY(posXSidebar + 1 + (widthSidebar - 2) / 2 - (widthSidebar - 2) / 4, posYSidebar + 1);
	string h = k;
	cout << CanGiuaChu(h, (widthSidebar - 2) / 2);
	
	int i = 0;
	gotoXY(posXSidebar + 3, posYSidebar + 5 + i);
	cout << "Nien khoa dau";
	gotoXY(posXSidebar + 17, posYSidebar + 5 + i);
	cout << ":";
	i += 2;
	gotoXY(posXSidebar + 3, posYSidebar + 5 + i);
	cout << "Nien khoa cuoi";
	gotoXY(posXSidebar + 18, posYSidebar + 5 + i);
	cout << ":";
	i += 2;
	gotoXY(posXSidebar + 3, posYSidebar + 5 + i);
	cout << "Hoc ky";
	gotoXY(posXSidebar + 10, posYSidebar + 5 + i);
	cout << ":";
	i += 2;
	gotoXY(posXSidebar + 3, posYSidebar + 5 + i);
	cout << "Ma mon hoc";
	gotoXY(posXSidebar + 14, posYSidebar + 5 + i);
	cout << ":";
	i += 2;
	gotoXY(posXSidebar + 3 , posYSidebar + 5 + i);
	cout << "Nhom";
	gotoXY(posXSidebar + 8 , posYSidebar + 5 + i);
	cout << ":";
	i += 2;
	gotoXY(posXSidebar + 3 , posYSidebar + 5 + i);
	cout << "Ma LTC";
	gotoXY(posXSidebar + 10 , posYSidebar + 5 + i);
	cout << ":";
	i += 2;
	gotoXY(posXSidebar + 3, posYSidebar + 5 + i);
	cout << "SL Min";
	gotoXY(posXSidebar + 10, posYSidebar + 5 + i);
	cout << ":";
	i += 2;
	gotoXY(posXSidebar + 3, posYSidebar + 5 + i);
	cout << "SL Max";
	gotoXY(posXSidebar + 10, posYSidebar + 5 + i);
	cout << ":";

	i += 2;
	gotoXY(posXSidebar + 3, posYSidebar + 5 + i);
	cout << "Trang thai";
	gotoXY(posXSidebar + 13, posYSidebar + 5 + i);

	string arr[2] = { "Huy", "Mo" };
	int width1 = (arr[0].length() > arr[1].length()) ? arr[0].length() + 2 : arr[1].length() + 2;
	int a = posXSidebar + 15;
	int b = posYSidebar + 5 + i;
	int space1 = 14;
	gotoXY(a, b);
	cout << CanGiuaChu(arr[0], width1);
	gotoXY(a + space1, b);
	cout << CanGiuaChu(arr[1], width1);

	i += 3;
	string arr1[2] = { "Xac nhan", "Tro ve" };
	int width = (arr1[0].length() > arr1[1].length()) ? arr1[0].length() + 2 : arr1[1].length() + 2;
	int X = posXSidebar + 6;
	int Y = posYSidebar + 25;
	int space = 19;
	gotoXY(X, Y);
	cout << CanGiuaChu(arr1[0], width);
	gotoXY(X + space, Y);
	cout << CanGiuaChu(arr1[1], width);
}

int NhapThongTinLopTinChi(ListLTC& listLTC, PTRMonHoc& root, LopTinChi& ltc, int nkd, int nkc, int hk, string maMH, int key, int& check)
{
	int posX = posXContent + 1;
	int posY = posYContent + 0.15 * heightContent;
	int width = widthContent - 2;
	int height = heightContent - 0.15 * heightContent;

	int r = -1;
	string temp = "";
	gotoXY(posXSidebar + 11, posYSidebar + 15);
	if (listLTC.sl == 0) {
		cout << 100;
	}
	else {
		cout << listLTC.ds[listLTC.sl - 1]->maLopTC + 1;
	}
	gotoXY(posXSidebar + 18, posYSidebar + 5);
	cout << nkd;
	ltc.nienKhoa.nienKhoaDau = nkd;

	gotoXY(posXSidebar + 19, posYSidebar + 7);
	cout << nkc;
	ltc.nienKhoa.nienKhoaCuoi = nkc;

	gotoXY(posXSidebar + 11, posYSidebar + 9);
	ltc.hocKy = hk;
	cout << ltc.hocKy;

	switch (key)
	{
	case 4: {
		Cls(posXContent - 1, posYContent - 1, width, CHIEUDOC);
		Cls(TOADOX + 49, TOADOY, 32, 4);
		int first = 0;
		int last = 11;
		int current = first;
		KhungChuongTrinh();
		HuongDan(9);
		veBangMonHoc(posX, posY, width, height);
		int n = 0;
		PTRMonHoc cs;
		IndexName* nodes[DSMONHOC];
		indexByName(root, nodes, n);
		int k = 1;
		int STT = 0;
		int j = 0;
		bool kt = true;
		int c = -1;
		while (kt == true) {
			k = 1;
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
			}
			if (c == ESC) {
				kt = false;
				check = ESC;
				Cls(TOADOX + 59, TOADOY, 32, 4);
				Cls(posXContent - 1, posYContent - 1, width, CHIEUDOC);

				KhungChuongTrinh();
				HuongDan(1);
				veBangLopTinChi(posX, posY, width, height);
				int k = 1;
				int j = 0;
				int STT = 0;
				int n = 0;
				int cs = 0;
				DSLopTinChi* DSLop[DSLOPTINCHI];
				DSLopTinChiTheoNienKhoa_HocKi(listLTC, DSLop, n, ltc.nienKhoa.nienKhoaDau, ltc.nienKhoa.nienKhoaCuoi, ltc.hocKy);
				if (n <= 12) {
					last = n - 1;
				}
				STT = first;
				PTRMonHoc p;

				for (int i = first; i <= last; i++) {
					cs = DSLop[i]->chiSo;
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
				}
				giaiPhongMangConTro_LTC(DSLop, n);
			}
			c = _getch();
			if (c == DOWN || c == UP) { 
				DiChuyenThanhSang(n, first, last, current, c); 
			}
			else if (c == ENTER && n > 0)
			{
				cs = nodes[current]->chiso;
				ltc.maMH = cs->data.maMH;
				gotoXY(posXSidebar + 15, posYSidebar + 11);
				cout << ltc.maMH;
				kt = false;
				check = DOWN;
				Cls(TOADOX + 59, TOADOY, 32, 4);
				Cls(posXContent - 1, posYContent - 1, width, CHIEUDOC);

				KhungChuongTrinh();
				HuongDan(1);
				veBangLopTinChi(posX, posY, width, height);
				int k = 1;
				int j = 0;
				int STT = 0;
				DSLopTinChi* DSLop[DSLOPTINCHI];
				int n = 0;
				int cs = 0;
				DSLopTinChiTheoNienKhoa_HocKi(listLTC, DSLop, n, ltc.nienKhoa.nienKhoaDau, ltc.nienKhoa.nienKhoaCuoi, ltc.hocKy);
				if (n <= 12) {
					last = n - 1;
				}
				STT = first;
				PTRMonHoc p;

				for (int i = first; i <= last; i++) {
					cs = DSLop[i]->chiSo;
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
				}
				giaiPhongMangConTro_LTC(DSLop, n);
			}
		}
		giaiPhongIndexNameDSMH(nodes, n);
	break;
	}
	case 5: {
		NhapDuLieu(temp, 3, posXSidebar + 9, posYSidebar + 13, 4, check, 3);
		if (temp == "")
			break;
		ltc.nhom = stoi(temp);
		break;
	}
	case 6: {
		if (listLTC.sl == 0) {
			ltc.maLopTC = 100;
		}
		else {
			ltc.maLopTC = listLTC.ds[listLTC.sl - 1]->maLopTC + 1;
		}
		break;
	}
	case 7: {
		NhapDuLieu(temp, 3, posXSidebar + 11, posYSidebar + 17, 4, check, 3);
		if (temp == "")
			break;
		ltc.soSVMin = stoi(temp);
		break;
	}
	case 8: {
		NhapDuLieu(temp, 3, posXSidebar + 11, posYSidebar + 19, 4, check, 3);
		if (temp == "")
			break;
		ltc.soSVMax = stoi(temp);
		break;
	}
	case 9:
	{
		string choiceTinhTrang[] = { "Huy", "Mo" };
		int i = ChonGioiTinh(choiceTinhTrang, check, posXSidebar + 15, posYSidebar + 21);
		if (i == 0)
			ltc.trangThaiLop = 0;
		else if (i == 1)
			ltc.trangThaiLop = 1;
		break;
	}
	case 10: {
		string choice[2] = { "Xac Nhan", "Tro ve" };
		int i = LuaChon(choice);
		if (i == 0)
			r = INS;
		else if (i == 1)
			r = ESC;
		return r;
		break;
	}
	default:
		break;
	}
	if (check == ESC) {
		return ESC;
	}
}

int KiemTraThongTinLTC(ListLTC &listLTC,PTRMonHoc root,LopTinChi ltc)
{
	PTRMonHoc p;
	p = Search(root, ltc.maMH);
	int vttrung = kiemTraTrungToHopKhoaLTC(listLTC, ltc.nienKhoa.nienKhoaDau, ltc.nienKhoa.nienKhoaCuoi, ltc.hocKy, ltc.maMH, ltc.nhom);
	if (!KiemTraChuoi(ltc.maMH, 3) || !KiemTraChuoi(ltc.maMH, 5) || !KiemTraChuoi(ltc.maMH, 4))
		return 5;
	if (p == NULL) {
		return 6;
	}
	else if (ltc.nhom <= 0 || ltc.nhom > 999)
		return 7;
	else if (vttrung >= 0) {
		return 8;
	}
	else if (ltc.soSVMin < 15)
		return 9;
	else if (ltc.soSVMax < ltc.soSVMin || ltc.soSVMax > 999)
		return 10;
	else
		return 1;
}

int KiemTraThongTinSuaLTC(ListLTC& listLTC, PTRMonHoc root, LopTinChi ltc)
{
	if (ltc.soSVMin < 15)
		return 2;
	else if (ltc.soSVMax < ltc.soSVMin || ltc.soSVMax > 999)
		return 3;
	else
		return 1;
}

void ChuyenTruongNhapDuLieuLTC(int& key, int& check){
	if (check == UP || check == DOWN)
	{
		switch (check)
		{
		case DOWN:
		{
			switch (key)
			{
			case 4:
				key = 5;
				break;
			case 5:
				key = 6;
				break;
			case 6:
				key = 7;
				break;
			case 7:
				key = 8;
				break;
			case 8:
				key = 9;
				break;
			case 9:
				key = 10;
				break;
			case 10:
				key = 4;
				break;
			}
			break;
		}
		case UP:
		{
			switch (key)
			{
			case 4:
				key = 10;
				break;
			case 5:
				key = 4;
				break;
			case 6:
				key = 5;
				break;
			case 7:
				key = 6;
				break;
			case 8:
				key = 7;
				break;
			case 9:
				key = 8;
				break;
			case 10:
				key = 9;
				break;
			}
			break;
		}
		}
	}
}

void ChuyenTruongSuaDuLieuLTC(int& key, int& check) {
	if (check == UP || check == DOWN)
	{
		switch (check)
		{
		case DOWN:
		{
			switch (key)
			{
			case 7:
				key = 8;
				break;
			case 8:
				key = 9;
				break;
			case 9:
				key = 10;
				break;
			case 10:
				key = 7;
				break;
			}
			break;
		}
		case UP:
		{
			switch (key)
			{
			case 7:
				key = 10;
				break;
			case 8:
				key = 7;
				break;
			case 9:
				key = 8;
				break;
			case 10:
				key = 9;
				break;
			}
			break;
		}
		}
	}
}

int XuLyThemLTC(ListLTC &list,PTRMonHoc root,int &nkd,int &nkc, int &hk, string maMH){
	int key = 4;
	int check = -1;
	LopTinChi ltc;
	ltc.DSDKLTC = NULL;
	KhungNhapThongTinLopTinChi("Them lop tin chi");
	while (true)
	{
		int r = NhapThongTinLopTinChi(list,root,ltc,nkd,nkc,hk,maMH, key, check);
		ChuyenTruongNhapDuLieuLTC(key, check);
		int k = KiemTraThongTinLTC(list,root,ltc);
		if (r == ESC) {
			break;
		}
		if (key == 5 && k == 5) {
			FeedBack("Ma mon hoc trong, gom: a-z,A-Z,0-9, so ki tu <= 10!", posXContent + 1, posYContent + 2, widthContent - 1, DO);
			key = 4;
		}
		else if (key == 5 && k == 6) {
			FeedBack("MaMH chua ton tai!", posXContent + 1, posYContent + 2, widthContent - 1, DO);
			key = 4;
		}
		else if (key == 6 && k == 7) {
			FeedBack("Nhom trong!, 0 < nhom <= 999", posXContent + 1, posYContent + 2, widthContent - 1, DO);
			key = 5;
		}
		else if (k == 8) {
			FeedBack("Nien khoa, Hoc ki, Nhom, Ma mon hoc trung!", posXContent + 1, posYContent + 2, widthContent - 1, DO);
			key = 5;
		}
		else if (key == 8 && k == 9) {
			FeedBack("SL sinh vien min trong!, sl >= 15", posXContent + 1, posYContent + 2, widthContent - 1, DO);
			key = 7;
		}
		else if (key == 9 && k == 10) {
			FeedBack("SL sinh vien max trong!, sl min (15) <= sl <= 999", posXContent + 1, posYContent + 2, widthContent - 1, DO);
			key = 8;
		}
		else if (k == 1) {
			if (r == INS) {
				int i = XacNhanLuaChon("Them lop tin chi", posXSidebar + 3, posYSidebar + 23, widthSidebar - 5);
				if (i == 1)
				{
					int kt = InsertOrder_LTC(list,ltc);
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

// lop tin chi da duoc dk, tuc la co so sinh vien dk>0
// kiem tra trang thai dk == 1, tuc la khi do sinh vien co diem thi cung co trang thai dk = 1
int XuLyXoaLTC(ListLTC& list, int maLTC)
{
	int key = 1;
	int check = -1;

	KhungNhapThongTinLopTinChi("Xoa lop tin chi");

	int i = ktTrungMaLopTinChi(list, maLTC);

	int soDKLTC = tinhSoSinhVienDKLTC(list.ds[i]);

	gotoXY(posXSidebar + 18, posYSidebar + 5);
	cout << list.ds[i]->nienKhoa.nienKhoaDau;

	gotoXY(posXSidebar + 19, posYSidebar + 7);
	cout << list.ds[i]->nienKhoa.nienKhoaCuoi;

	gotoXY(posXSidebar + 11, posYSidebar + 9);
	cout << list.ds[i]->hocKy;

	gotoXY(posXSidebar + 15, posYSidebar + 11);
	cout << list.ds[i]->maMH;

	gotoXY(posXSidebar + 9, posYSidebar + 13);
	cout << list.ds[i]->nhom;

	gotoXY(posXSidebar + 11, posYSidebar + 15);
	cout << list.ds[i]->maLopTC;

	gotoXY(posXSidebar + 11, posYSidebar + 17);
	cout << list.ds[i]->soSVMin;

	gotoXY(posXSidebar + 11, posYSidebar + 19);
	cout << list.ds[i]->soSVMax;

	gotoXY(posXSidebar + 3, posYSidebar + 23);
	cout << "So sinh vien dang ki LTC : ";

	gotoXY(posXSidebar + 30, posYSidebar + 23);
	cout << to_string(soDKLTC);

	string arr[2] = { "Huy", "Mo" };
	int width = (arr[0].length() > arr[1].length()) ? arr[0].length() + 2 : arr[1].length() + 2;
	int X = posXSidebar + 15;
	int Y = posYSidebar + 21;
	int space = 14;
	TextColor(DO);
	if (list.ds[i]->trangThaiLop == 0) {
		gotoXY(X, Y);
		cout << CanGiuaChu(arr[0], width);
	}
	else {
		gotoXY(X + space, Y);
		cout << CanGiuaChu(arr[1], width);
	}
	TextColor(MACDINH);
	if (soDKLTC > 0) {
		return 2;
	}
	if (soDKLTC == 0) {
		int h = XacNhanLuaChon("Xoa lop tin chi", posXSidebar + 3, posYSidebar + 23, widthSidebar - 5);
		if (h == 1)
		{
			return xoaLopTinChi(list, list.ds[i]->maLopTC);
		}
		else if (h == 0) {
			return 0;
		}
	}
}

int NhapSuaThongTinLTC(LopTinChi &ltc, int &key, int& check)
{
	int r = -1;
	string temp = "";
	switch (key)
	{
	case 7: {
		temp = to_string(ltc.soSVMin);
		NhapDuLieu(temp, 3, posXSidebar + 11, posYSidebar + 17, 4, check, 3);
		if (temp == "")
			break;
		ltc.soSVMin = stoi(temp);
		break;
	}
	case 8: {
		temp = to_string(ltc.soSVMax);
		NhapDuLieu(temp, 3, posXSidebar + 11, posYSidebar + 19, 4, check, 3);
		if (temp == "")
			break;
		ltc.soSVMax = stoi(temp);
		break;
	}
	case 9:
	{
		string choiceTinhTrang[] = { "Huy", "Mo" };
		int i = ChonGioiTinh(choiceTinhTrang,check, posXSidebar + 15, posYSidebar + 21);
		if (i == 0)
			ltc.trangThaiLop = 0;
		else if (i == 1)
			ltc.trangThaiLop = 1;
		break;
	}
	case 10: {
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
	if (check == ESC) {
		return ESC;
	}
}

int SuaLopTinChi(ListLTC &list, PTRMonHoc root , LopTinChi &l)
{
	int i = ktTrungMaLopTinChi(list, l.maLopTC);
	if (i >= 0) {
		list.ds[i]->DSDKLTC = l.DSDKLTC;
		list.ds[i]->nienKhoa.nienKhoaDau = l.nienKhoa.nienKhoaDau ;
		list.ds[i]->nienKhoa.nienKhoaCuoi = l.nienKhoa.nienKhoaCuoi;
		list.ds[i]->hocKy = l.hocKy;
		list.ds[i]->maLopTC = l.maLopTC;
		list.ds[i]->maMH = l.maMH;
		list.ds[i]->nhom = l.nhom;
		list.ds[i]->soSVMax = l.soSVMax;
		list.ds[i]->soSVMin = l.soSVMin;
		list.ds[i]->trangThaiLop = l.trangThaiLop;
		return 1;
	}
	if (KiemTraThongTinLTC(list,root,l) > 1)
	{
		return 0;
	}
}

// sua lop tin chi: thi roi thi khong cho sua, xoa => tim trong lop do co sinh vien nao diem !=0 khong
// thi roi => bat ki mot sinh vien nao trong ltc do co diem != 0
int kiemTraLTCDaThi(ListLTC &list,int maLTC) {
	int vt = ktTrungMaLopTinChi(list, maLTC);
	if (vt == -1) {
		return -1;
	}
	else {
		PTRDangKiLTC p;
		for (p = list.ds[vt]->DSDKLTC; p != NULL; p = p->next) {
			if (p->dk.diem != 0) {
				return 1;
			}
		}
		return 0;
	}
}

int XuLySuaThongTinLTC(ListLTC &list,PTRMonHoc &root, int  maLTC){
	int key = 7;
	int check = -1;
	int i = ktTrungMaLopTinChi(list, maLTC);
	LopTinChi l;
	l.nienKhoa.nienKhoaDau = list.ds[i]->nienKhoa.nienKhoaDau;
	l.nienKhoa.nienKhoaCuoi = list.ds[i]->nienKhoa.nienKhoaCuoi;
	l.hocKy = list.ds[i]->hocKy;
	l.maLopTC = list.ds[i]->maLopTC;
	l.maMH = list.ds[i]->maMH;
	l.nhom = list.ds[i]->nhom;
	l.soSVMax = list.ds[i]->soSVMax;
	l.soSVMin = list.ds[i]->soSVMin;
	l.trangThaiLop = list.ds[i]->trangThaiLop;
	l.DSDKLTC = list.ds[i]->DSDKLTC;

	KhungNhapThongTinLopTinChi("Sua thong tin");

	gotoXY(posXSidebar + 18, posYSidebar + 5);
	cout << l.nienKhoa.nienKhoaDau;

	gotoXY(posXSidebar + 19, posYSidebar + 7);
	cout << l.nienKhoa.nienKhoaCuoi;

	gotoXY(posXSidebar + 11, posYSidebar + 9);
	cout << l.hocKy;

	gotoXY(posXSidebar + 15, posYSidebar + 11);
	cout << l.maMH;

	gotoXY(posXSidebar + 9, posYSidebar + 13);
	cout << l.nhom;

	gotoXY(posXSidebar + 11, posYSidebar + 15);
	cout << l.maLopTC;

	gotoXY(posXSidebar + 11, posYSidebar + 17);
	cout << l.soSVMin;

	gotoXY(posXSidebar + 11, posYSidebar + 19);
	cout << l.soSVMax;

	string arr[2] = { "Huy", "Mo" };
	int width = (arr[0].length() > arr[1].length()) ? arr[0].length() + 2 : arr[1].length() + 2;
	int X = posXSidebar + 15;
	int Y = posYSidebar + 21;
	int space = 14;
	TextColor(DO);
	if (l.trangThaiLop == 0) {
		gotoXY(X, Y);
		cout << CanGiuaChu(arr[0], width);
	}
	else {
		gotoXY(X + space, Y);
		cout << CanGiuaChu(arr[1], width);
	}
	TextColor(MACDINH);
	int kt = kiemTraLTCDaThi(list, list.ds[i]->maLopTC);
	if (kt == 1) {
		return 2;
	}
	if(kt == 0){
		while (true)
		{
			int r = NhapSuaThongTinLTC(l, key, check);
			ChuyenTruongSuaDuLieuLTC(key, check);
			int k = KiemTraThongTinSuaLTC(list, root, l);
			if (r == ESC) {
				break;
			}
			else if (k == 2) {
				FeedBack("SL sinh vien min trong!,sl min >= 15", posXContent + 1, posYContent + 2, widthContent - 1, DO);
				key = 7;
			}
			else if (k == 3) {
				FeedBack("SL sinh vien max trong!,sl min(15) <= sl max <= 999 ", posXContent + 1, posYContent + 2, widthContent - 1, DO);
				key = 8;
			}
			else if (k == 1) {
				if (r == INS) {
					int i = XacNhanLuaChon("sua lop TC", posXSidebar + 3, posYSidebar + 23, widthSidebar - 5);
					if (i == 1)
					{
						return SuaLopTinChi(list, root, l);
					}
					else if (i == 0) {
						FeedBack("Moi thao tac lai!", posXSidebar + 3, posYSidebar + 23, widthSidebar - 5, DO);
						key = 7;
					}
				}
			}
		}
	}
}

//==========================================================================================================================

void DSLopTinChiTheoNienKhoa_HocKi(ListLTC& listLTC, DSLopTinChi *DS[], int& n, int nkd, int nkc, int hk) {
	for (int i = 0; i < listLTC.sl; i++) {
		if (listLTC.ds[i]->nienKhoa.nienKhoaDau == nkd && listLTC.ds[i]->nienKhoa.nienKhoaCuoi == nkc && listLTC.ds[i]->hocKy == hk) {
			DS[n] = new DSLopTinChi;
			DS[n]->maLTC = listLTC.ds[i]->maLopTC;
			DS[n]->chiSo = i;
			n++;
		}
	}
}
void giaiPhongMangConTro_LTC(DSLopTinChi* DS[], int& n) {
	for (int i = 0; i < n; i++) {
		delete DS[i];
	}
}

int KiemTra_NK_HK(ListLTC& list, PTRMonHoc root, LopTinChi& ltc)
{
	PTRMonHoc p;
	p = Search(root, ltc.maMH);
	int vtTrung = kiemTraTrung_NK_HK(list, ltc.nienKhoa.nienKhoaDau, ltc.nienKhoa.nienKhoaCuoi, ltc.hocKy);
	if (ltc.nienKhoa.nienKhoaDau < 2020)
		return 2;
	else if (ltc.nienKhoa.nienKhoaCuoi < 2020 || ltc.nienKhoa.nienKhoaCuoi <= ltc.nienKhoa.nienKhoaDau)
		return 3;
	else if (ltc.hocKy <= 0 || ltc.hocKy > 3 )
		return 4;
	else if (vtTrung == -1) {
		return 5;
	}
	return 1;
}

void chuyenTruongNhapLieu_NK_HK(int& key, int& check) {
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
				key = 3;
				break;
			case 2:
				key = 1;
				break;
			case 3:
				key = 2;
				break;
				break;
			}
		}
		}
	}
}

int Nhap_NK_HK(ListLTC& listLTC, LopTinChi &ltc, int key, int& check)
{
	int x = posXContent + 35;
	int y = posYContent + 5;
	string temp = "";
	switch (key)
	{
	case 1: {
		NhapDuLieu(temp, 4, x + 18, y + 5, 4, check, 3);
		if (temp == "")
			break;
		ltc.nienKhoa.nienKhoaDau = stoi(temp);
		break;
	}
	case 2: {
		NhapDuLieu(temp, 4, x + 19, y + 7, 4, check, 3);
		if (temp == "")
			break;
		ltc.nienKhoa.nienKhoaCuoi = stoi(temp);
		break;
	}
	case 3: {
		NhapDuLieu(temp, 1, x + 11, y + 9, 4, check, 3);
		if (temp == "")
			break;
		ltc.hocKy = stoi(temp);
		break;
	}
	default:
		break;
	}
	if (check == ESC) {
		return ESC;
	}
}

void KhungNhap_NK_HK(string h) {
	int x = posXContent + 35;
	int y = posYContent + 5;
	VeKhungVien(x + 1, y + 1, widthContent / 2 - 2, heightContent / 2 - 2);
	gotoXY(x + 1 + (widthContent / 2 - 2) / 2 - (widthContent / 2 - 2) / 4, y + 1);
	cout << CanGiuaChu(h, (widthContent / 2 - 2) / 2);

	int i = 0;
	gotoXY(x + 3, y + 5 + i);
	cout << "Nien khoa dau";
	gotoXY(x + 17, y + 5 + i);
	cout << ":";
	i += 2;
	gotoXY(x + 3, y + 5 + i);
	cout << "Nien khoa cuoi";
	gotoXY(x + 18, y + 5 + i);
	cout << ":";
	i += 2;
	gotoXY(x + 3, y + 5 + i);
	cout << "Hoc ky";
	gotoXY(x + 10, y + 5 + i);
	cout << ":";
}

void QuanLyLopTinChi(ListLTC& list, PTRMonHoc root) {
	int key = 1;
	int check = -1;
	LopTinChi ltc;
	KhungNhap_NK_HK("Nhap thong tin");
	HuongDan(7);
	while (true)
	{
		int r = Nhap_NK_HK(list, ltc, key, check);
		chuyenTruongNhapLieu_NK_HK(key, check);
		int k = KiemTra_NK_HK(list, root, ltc);
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
			FeedBack("Hoc ki trong, gom: 1-3!", posXContent + 3, posYContent + 28, widthContent  - 5, DO);
			key = 3;
		}
		else if (k == 5) {
			FeedBack("Nien Khoa,Hoc ki khong ton tai!", posXContent + 3, posYContent + 28, widthContent  - 5, DO);
		}
		else if (k == 1) {
			gotoXY(3, 2);
			cout << "Nien Khoa  : " << ltc.nienKhoa.nienKhoaDau << " - " << ltc.nienKhoa.nienKhoaCuoi;
			gotoXY(3, 3);
			cout << "Hoc ki     : " << ltc.hocKy;
			Cls(posXContent, posYContent + 2, CHIEUNGANG, CHIEUDOC);
			QuanLyLTC(list, root,ltc);
			Cls(TOADOX, TOADOY, CHIEUNGANG + 2, CHIEUDOC + 2);
			break;
		}
	}
}

void QuanLyLTC(ListLTC &listLTC, PTRMonHoc &root , LopTinChi &ltc) {
	int first = 0;
	int last = 11;
	int current = first;
	int check = -1;
	int posX = posXContent + 1;
	int posY = posYContent + 0.15 * heightContent;
	int width = widthContent - 2;
	int height = heightContent - 0.15 * heightContent;
	KhungChuongTrinh();
	HuongDan(1);
	veBangLopTinChi(posX, posY, width, height);
	int k = 1;
	int j = 0;
	int STT = 0;
	DSLopTinChi* DSLop[DSLOPTINCHI];
	int n = 0;
	int cs = 0;
	DSLopTinChiTheoNienKhoa_HocKi(listLTC, DSLop, n, ltc.nienKhoa.nienKhoaDau, ltc.nienKhoa.nienKhoaCuoi, ltc.hocKy);
	while (true) {
		k = 1;
		if (check == ESC) {
			break;
		}
		if (n <= 12) {
			last = n - 1;
		}
		STT = first;
		PTRMonHoc p;
		
		for (int i = first; i <= last; i++) {
			cs = DSLop[i]->chiSo;
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
		else if (check == INS) {
			int kt = XuLyThemLTC(listLTC, root, ltc.nienKhoa.nienKhoaDau, ltc.nienKhoa.nienKhoaCuoi, ltc.hocKy,ltc.maMH);
			giaiPhongMangConTro_LTC(DSLop, n);
			n = 0;
			DSLopTinChiTheoNienKhoa_HocKi(listLTC, DSLop, n, ltc.nienKhoa.nienKhoaDau, ltc.nienKhoa.nienKhoaCuoi, ltc.hocKy);
			if (kt == 1) {
				FeedBack("Them lop tin chi thanh cong!", posXContent + 1, posYContent + 2, widthContent - 1, DO);
			}
			else if (kt == 0) {
				FeedBack("Thong tin khong hop le!", posXContent + 1, posYContent + 2, widthContent - 1, DO);
			}
			ClsDanhSachLTC();
			Cls(posXSidebar + 1, posYSidebar + 1, widthSidebar - 1, heightSidebar - 1);
		}
		else if (check == DEL && n > 0) {
			int maLTC = DSLop[current]->maLTC;
			int kt = XuLyXoaLTC(listLTC, maLTC);
			giaiPhongMangConTro_LTC(DSLop, n);
			n = 0;
			DSLopTinChiTheoNienKhoa_HocKi(listLTC, DSLop, n, ltc.nienKhoa.nienKhoaDau, ltc.nienKhoa.nienKhoaCuoi, ltc.hocKy);
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
				FeedBack("Xoa lop tin chi thanh cong!", posXContent + 1, posYContent + 2, widthContent - 1, DO);
			}
			else if (kt == -1) FeedBack("Xoa lop tin chi khong thanh cong!", posXContent + 1, posYContent + 2, widthContent - 1, DO);
			else if (kt == 2) FeedBack("Lop tin chi da dang ki khong the xoa!", posXContent + 1, posYContent + 2, widthContent - 1, DO);
			Cls(posXSidebar + 1, posYSidebar + 1, widthSidebar - 1, heightSidebar - 1);
			ClsDanhSachLTC();
		}
		else if (check == ENTER && n > 0) {
			int kt = XuLySuaThongTinLTC(listLTC, root,listLTC.ds[DSLop[current]->chiSo]->maLopTC);
			giaiPhongMangConTro_LTC(DSLop, n);
			n = 0;
			DSLopTinChiTheoNienKhoa_HocKi(listLTC, DSLop, n, ltc.nienKhoa.nienKhoaDau, ltc.nienKhoa.nienKhoaCuoi, ltc.hocKy);
			if (kt == 1) {
				FeedBack("Sua lop tin chi thanh cong!", posXContent + 1, posYContent + 2, widthContent - 1, DO);
			}
			if (kt == 0) {
				FeedBack("Sua lop tin chi khong thanh cong!", posXContent + 1, posYContent + 2, widthContent - 1, DO);
			}
			if (kt == 2) {
				FeedBack("Lop tin chi da thi, khong duoc sua!", posXContent + 1, posYContent + 2, widthContent - 1, DO);
			}
			Cls(posXSidebar + 1, posYSidebar + 1, widthSidebar - 1, heightSidebar - 1);
		}
	}
	giaiPhongMangConTro_LTC(DSLop, n);
}
