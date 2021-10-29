#include "DangKiLTC.h"

void khoiTaoListDKLTC(PTRDangKiLTC& first);
void QuanLyLTC(ListLTC& listLTC, PTRMonHoc& root);
void GiaiPhongMangConTroLTC(ListLTC& l);

int main() {
    system("cls");
	PTRMonHoc tree;
	khoiTaoCay(tree);
	docFileDanhSachMonHoc(tree);
	
	PTRDangKiLTC firstDKLTC;
	khoiTaoListDKLTC(firstDKLTC);

	ListLTC listLTC;
	docFileDanhSachLTC(listLTC);

	ListSV listSV;

	docFileDanhSachSV(listSV);

	docFileDanhSachDKLTC(listLTC);

	bool kt = true;
	while (kt == true) {
		int chon = chuyenDongVsThanhSang();
		system("cls");
		switch (chon) {
		case 11:
			Cls(posXContent + 1, posYContent + 1, widthContent - 1, heightContent - 1);
			QuanLyLopTinChi(listLTC, tree);
			Cls(TOADOX, TOADOY, TOADOX + CHIEUNGANG, CHIEUDOC+1);
			break;
		case 12: {
			// huy lop thi can kiem tra lop da thi chua, neu da thi thi ko huy dc
			Cls(posXContent + 1, posYContent + 1, widthContent - 1, heightContent - 1);
			HuyLopTinChi_NK_HK(listLTC, tree);
			Cls(TOADOX, TOADOY, TOADOX + CHIEUNGANG, CHIEUDOC + 1);
			break;
		}
		case 13:
			Cls(posXContent + 1, posYContent + 1, widthContent - 1, heightContent - 1);
			InBangDiemCuaMotLTC(listLTC, tree, listSV);
			Cls(TOADOX, TOADOY, TOADOX + CHIEUNGANG, CHIEUDOC + 1);
			break;
		case 14:
			Cls(posXContent + 1, posYContent + 1, widthContent - 1, heightContent - 1);
			NhapDiem(listLTC, tree, listSV);
			Cls(TOADOX, TOADOY, TOADOX + CHIEUNGANG, CHIEUDOC + 1);
			break;
		case 2: {
			Cls(posXContent + 1, posYContent + 1, widthContent - 1, heightContent - 1);
			HuongDan(1);
			QuanLyMonHoc(tree,listLTC);
			Cls(TOADOX, TOADOY, TOADOX + CHIEUNGANG, CHIEUDOC + 1);
			break;
		}
		case 3: {
			Cls(posXContent + 1, posYContent + 1, widthContent - 1, heightContent - 1);
			BangDanhSachLop(listSV,listLTC,tree);
			Cls(TOADOX, TOADOY, TOADOX + CHIEUNGANG, CHIEUDOC + 1);
			break;
		}
		case 41: {
			Cls(posXContent + 1, posYContent + 1, widthContent - 1, heightContent - 1);
			DangKiLopTinChi(listLTC, tree, listSV);
			Cls(TOADOX, TOADOY, TOADOX + CHIEUNGANG, CHIEUDOC + 1);
			break;
		}
		case 42: 
		{
			DSSinhVienConDKLopTinChi(listLTC, tree, listSV);
			Cls(TOADOX, TOADOY, TOADOX + CHIEUNGANG, CHIEUDOC + 1);
			break;
		}
		case 43:
		{
			SinhVienHuyDangKiLTC(listLTC, tree, listSV);
			Cls(TOADOX, TOADOY, TOADOX + CHIEUNGANG, CHIEUDOC + 1);
			break;
		}
		case 5:
			kt = false;
			break;
		}
	}
	ghiFileDanhSachDKLTC(listLTC);

	ghiFileDanhSachLTC(listLTC);

	ghiFileDanhSachSinhVien(listSV);

	GhiFileMH(tree);

	GiaiPhongCay(tree);
	GiaiPhongMangConTroLTC(listLTC);
    return 0;
}

