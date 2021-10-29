#pragma once
#include "ctdl.h"
#include "XuLyLopTinChi.h"
#define MAXML 100
#define MAXSV 200
#define MAXLOP 200

struct IndexSV {
    int chiso;
    string ten;
    string ho;
};

struct Lop
{
    int chiSo;
    string maLop;
};

int tinhSoSinhVienDKLTC(LopTinChi *ltc);
void khoiTaoListDKLTC(PTRDangKiLTC& first);
void BangDanhSachSVTheoLop(ListSV& list, ListLTC& listLTC, SinhVien& sv);

//==============================CAC HAM KIEM TRA=========================

int kiemTraTrungMaSV(ListSV& l, string ma);
int kiemTraTrungMaLop(ListSV& l, string ma);

//========================NHAP SINH VIEN ================================

int KiemTraThongTinSinhVien(ListSV &list, SinhVien sv);

//===============================XOA SINH VIEN ==========================

int xoaTheoTenSV(ListSV& l,string ten);

int themSinhVien(ListSV& l, SinhVien sv);

//======================================CAC HAM KIEM TRA===============================

int kiemTraTrungMaSV(ListSV &l,string ma) {
    for (int i = 0; i < l.sl; i++) {
        if (l.ds[i].maSV.compare(ma) == 0) {
            return i;
        }
    }
    return -1;
}

int kiemTraTrungMaLop(ListSV& l, string ma) {
    for (int i = 0; i < l.sl; i++) {
        if (l.ds[i].maLop.compare(ma) == 0) {
            return i;
        }
    }
    return -1;
}

//========================================THEM SINH VIEN==========================================
// them cuoi
int themSinhVien(ListSV &l,SinhVien sv) {
    if (l.sl < DSSINHVIEN) {
        l.ds[l.sl] = sv;
        l.sl++;
        return 1;
    }
    if (KiemTraThongTinSinhVien(l, sv) > 1)
    {
        return 0;
    }
}
// them co thu tu theo ten, ho
//int Them_MangConTro_SV(IndexSV *DS[], int &n, SinhVien sv) {
//    int j, k;
//    if (n == DSLOPTINCHI) return 0;
//    for (j = 0; j < n && (DS[j]->ten + DS[j]->ho).compare(sv.ten+sv.ho) < 0; j++);
//    for (k = n - 1; k >= j; k--)
//        DS[k + 1] = DS[k];
//    DS[j] = new IndexSV;
//    DS[j]->chiso = k;
//    DS[j]->ho = sv.ho;
//    DS[j]->ten = sv.ten;
//    n++;
//    return 1;
//}

//================================================XOASINH VIEN=================================================
PTRDangKiLTC KiemTraTrungMaSVDKLTC(PTRDangKiLTC& first, string maSV)
{
    int kt = 0;
    for (PTRDangKiLTC k = first; k != NULL; k = k->next) {
        kt = maSV.compare(k->dk.maSV); //kiem tra trang thai cua no co = 1 khong da 
        if (kt == 0 && k->dk.trangThaiDK == 1) { // ma sinh vien ton tai va trang thai dk  == 1
            return k;
        }
    }
    return NULL;
}

int kiemTraSVCoDuocXoa(ListLTC& listLTC, string maSV) {
    PTRDangKiLTC p;
    for (int i = 0; i < listLTC.sl; i++) {
        p = KiemTraTrungMaSVDKLTC(listLTC.ds[i]->DSDKLTC, maSV);
        if (p != NULL) { 
            return 1;
        }
    }
    return 0;
}

int xoaSVTrongDSSV(ListSV& l, string ma) {
    int vt = kiemTraTrungMaSV(l, ma);
    if (vt == -1) {
        return 0;
    }
    else {
        for (int i = vt + 1; i < l.sl; i++) {
            l.ds[i - 1] = l.ds[i];
        }
        l.sl--;
        return 1;
    }
}

int kiemTraTrungMaSV_MangConTro(ListSV &listSV,IndexSV* DS[], int& n, string maSV) {
    int chiSo = 0;
    for (int i = 0; i < n; i++) {
        chiSo = DS[i]->chiso;
        if (listSV.ds[chiSo].maSV.compare(maSV) == 0) {
            return i;
        }
    }
    return -1;
}

int xoaMangConTro_SV(ListSV &listSV, IndexSV* DS[], int& n, string maSV) {
    int i = kiemTraTrungMaSV_MangConTro(listSV,DS, n, maSV);
    if (i == -1) return 0;
    else
    {
        delete  DS[i];
        for (int j = i + 1; j < n; j++)
            DS[j - 1] = DS[j];

        n--;
        return 1;
    }
}
//=======================xuat thong tin ds sinh vien theo lop====================

void LuuDuLieu(ListSV &list,string ma, IndexSV *nodes[], int& n) {
      for (int i = 0; i < list.sl; i++) {
            if (list.ds[i].maLop.compare(ma) == 0) {
                nodes[n] = new IndexSV;
                nodes[n]->chiso = i;
                nodes[n]->ho = list.ds[i].ho;
                nodes[n]->ten = list.ds[i].ten;
                n++;
            }
      }
}

void SapXepDSSVTheoHoTen(ListSV &list,string ma, IndexSV *nodes[], int& n) {
    LuuDuLieu(list, ma, nodes, n);
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (nodes[j]->ten.compare(nodes[i]->ten) == 0) {
                if (nodes[j]->ho.compare(nodes[i]->ho) < 0) {
                    swap(nodes[j], nodes[i]);
                }
            }
            else if (nodes[j]->ten.compare(nodes[i]->ten) < 0) {
                swap(nodes[j], nodes[i]);
            }
        }
    }
}

void giaiPhongMangConTroIndexSV(IndexSV *nodes[], int& n) {
    for (int i = 0; i < n; i++) {
        delete nodes[i];
    }
}

int KiemTraThongTinSinhVien(ListSV &list, SinhVien sv)
{
    int i = kiemTraTrungMaSV(list, sv.maSV);
    if (!KiemTraChuoi(sv.maSV, 3) || !KiemTraChuoi(sv.maSV, 5) || !KiemTraChuoi(sv.maSV, 4))
        return 2;
    else if (i >= 0)
        return 3;
    else if (!KiemTraChuoi(sv.ho, 1) || !KiemTraChuoi(sv.ho, 5))
        return 4;
    else if (!KiemTraChuoi(sv.ten, 1) || !KiemTraChuoi(sv.ten, 5))
        return 5;
    else if (sv.phai != 0 && sv.phai != 1)
        return 6;
    else if (!KiemTraChuoi(sv.soDT, 2) || !KiemTraChuoi(sv.soDT, 5) || !KiemTraChuoi(sv.soDT, 4))
        return 7;
    else
        return 1;
}

int KiemTraThongTinSuaSV(ListSV& list, SinhVien sv)
{
    if (!KiemTraChuoi(sv.ho, 1) || !KiemTraChuoi(sv.ho, 5))
        return 2;
    else if (!KiemTraChuoi(sv.ten, 1) || !KiemTraChuoi(sv.ho, 5))
        return 3;
    else if (sv.phai != 0 && sv.phai != 1)
        return 4;
    else if (!KiemTraChuoi(sv.soDT, 2) || !KiemTraChuoi(sv.soDT, 5) || !KiemTraChuoi(sv.soDT, 4))
        return 5;
    else
        return 1;
}

void KhungNhapThongTinSinhVien(string k) {
    VeKhungVien(posXSidebar + 1, posYSidebar + 1, widthSidebar - 2, heightSidebar - 2);
    TextColor(DO);
    gotoXY(posXSidebar + 1 + (widthSidebar - 2) / 2 - (widthSidebar - 2) / 4, posYSidebar + 1);
    string h = k;
    cout << CanGiuaChu(h, (widthSidebar - 2) / 2);
    TextColor(15);
    gotoXY(posXSidebar + 3, posYSidebar + 5);
    cout << "Ma sinh vien";
    gotoXY(posXSidebar + 16, posYSidebar + 5);
    cout << ":";

    gotoXY(posXSidebar + 3, posYSidebar + 7);
    cout << "Ho";
    gotoXY(posXSidebar + 6, posYSidebar + 7);
    cout << ":";

    gotoXY(posXSidebar + 3, posYSidebar + 9);
    cout << "Ten";
    gotoXY(posXSidebar + 7, posYSidebar + 9);
    cout << ":";

    gotoXY(posXSidebar + 3, posYSidebar + 11);
    cout << "Phai";
    gotoXY(posXSidebar + 8, posYSidebar + 11);
    cout << ":";

    string arr[2] = { "Nam", "Nu" };
    int width = (arr[0].length() > arr[1].length()) ? arr[0].length() + 2 : arr[1].length() + 2;
    int a = posXSidebar + 16;
    int b = posYSidebar + 11;
    int space = 14;
    gotoXY(a, b);
    cout << CanGiuaChu(arr[0], width);
    gotoXY(a + space, b);
    cout << CanGiuaChu(arr[1], width);

    gotoXY(posXSidebar + 3, posYSidebar + 13);
    cout << "SDT";
    gotoXY(posXSidebar + 7, posYSidebar + 13);
    cout << ":";

    string arr1[2] = { "Xac nhan", "Tro ve" };
    int width2 = (arr1[0].length() > arr1[1].length()) ? arr1[0].length() + 2 : arr1[1].length() + 2;
    int color = DO;
    int X = posXSidebar + 6;
    int Y = posYSidebar + 25;
    int space2 = 19;
    gotoXY(X, Y);
    cout << CanGiuaChu(arr1[0], width2);
    gotoXY(X + space2, Y);
    cout << CanGiuaChu(arr1[1], width2);
}

int NhapThongTinSinhVien(SinhVien &sv,string maLop, int &key, int &chuyen) {
    int r = -1;
    sv.maLop = maLop;
    switch (key) {
    case 1: {
        NhapDuLieu(sv.maSV, 15, posXSidebar + 17, posYSidebar + 5, 1, chuyen, 1);
        break;
    }
    case 2: {
        NhapDuLieu(sv.ho, 50, posXSidebar + 7, posYSidebar + 7, 2, chuyen, 2);
        break;
    }
    case 3: {
        NhapDuLieu(sv.ten, 10, posXSidebar + 8, posYSidebar + 9, 2, chuyen, 2);
        break;
    }
    case 4:
    {
        string choiceSex[] = { "Nam", "Nu" };
        int i = ChonGioiTinh(choiceSex, chuyen, posXSidebar + 16, posYSidebar + 11);
        if (i == 0)
            sv.phai = 1;
        else if (i == 1)
            sv.phai = 0;
        break;
    }
    case 5: {
        NhapDuLieu(sv.soDT, 10, posXSidebar + 8, posYSidebar + 13, 3, chuyen, 4);
        break;
    }
    case 6:
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

int SuaThongTinSinhVien(SinhVien& sv,int& key, int& chuyen) {
    int r = -1;
    switch (key) {
    
    case 2: {
        NhapDuLieu(sv.ho, 50, posXSidebar + 7, posYSidebar + 7, 2, chuyen, 2);
        break;
    }
    case 3: {
        NhapDuLieu(sv.ten, 10, posXSidebar + 8, posYSidebar + 9, 2, chuyen, 2);
        break;
    }
    case 4:
    {
        string choiceSex[] = { "Nam", "Nu" };
        int i = ChonGioiTinh(choiceSex, chuyen, posXSidebar + 16, posYSidebar + 11);
        if (i == 0)
            sv.phai = 1;
        else if (i == 1)
            sv.phai = 0;
        break;
    }
    case 5: {
        NhapDuLieu(sv.soDT, 10, posXSidebar + 8, posYSidebar + 13, 3, chuyen, 4);
        break;
    }
    case 6:
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

void ChuyenTruongNhapThongTinSV(int& key, int& chuyen) {
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
                key = 6;
                break;
            case 6:
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
                key = 6;
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
            case 6:
                key = 5;
            }
            break;
        }
        }
    }
}

void ChuyenTruongSuaThongTinSinhVien(int& key, int& chuyen) {
    if (chuyen == UP || chuyen == DOWN)
    {
        switch (chuyen)
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
                key = 6;
                break;
            case 6:
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
                key = 6;
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
            case 6:
                key = 5;
            }
            break;
        }
        }
    }
}

int XuLyThemSinhVien(ListSV &list,string maLop)
{
    SinhVien sv;
    int key = 1;
    int check = -1;
    KhungNhapThongTinSinhVien("Them sinh vien");
    while (true)
    {
        int r = NhapThongTinSinhVien(sv,maLop, key, check);
        ChuyenTruongNhapThongTinSV(key, check);
        int k = KiemTraThongTinSinhVien(list, sv);
        if (r == ESC) {
            break;
        }
        if (key == 2 && k == 2) {
            FeedBack("Ma sinh vien khong trong, gom: a-z,A-Z,0-9, so ky tu <= 10!", posXContent + 1, posYContent + 2, widthContent - 1, DO);
            key = 1;
        }
        else if ((key == 2) && k == 3) {
            FeedBack("Ma sinh vien da ton tai!", posXContent + 1, posYContent + 2, widthContent - 1, DO);
            key = 1;
        }
        else if ((key == 3) && k == 4) {
            FeedBack("Ho khong trong, gom: a-z,A-Z, so ky tu <= 50!", posXContent + 1, posYContent + 2, widthContent - 1, DO);
            key = 2;
        }
        else if (key == 4 && k == 5) {
            FeedBack("Ten khong trong, gom: a-z,A-Z, so ky tu <= 10!", posXContent + 1, posYContent + 2, widthContent - 1, DO);
            key = 3;
        }
        else if ((key == 6) && k == 7) {
            FeedBack("SDT khong trong, gom: 0-9, so ky tu <= 10!", posXContent + 1, posYContent + 2, widthContent - 1, DO);
            key = 5;
        }
        else if (k == 1) {
            if (r == INS) {
                int i = XacNhanLuaChon("Them sinh vien", posXSidebar + 3, posYSidebar + 23, widthSidebar - 5);
                if (i == 1)
                {
                    int kt = themSinhVien(list, sv);
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

int XuLyXoaSinhVien(ListSV &list,ListLTC &listLTC, string maSV)
{
    int key = 1;
    int check = -1;
    int i = kiemTraTrungMaSV(list, maSV);
    KhungNhapThongTinSinhVien("Xoa sinh vien");
    
    gotoXY(posXSidebar + 17, posYSidebar + 5);
    cout << list.ds[i].maSV;

    gotoXY(posXSidebar + 7, posYSidebar + 7);
    cout << list.ds[i].ho;

    gotoXY(posXSidebar + 8, posYSidebar + 9);
    cout << list.ds[i].ten;

    string arr[2] = { "Nam", "Nu" };
    int width = (arr[0].length() > arr[1].length()) ? arr[0].length() + 2 : arr[1].length() + 2;
    int X = posXSidebar + 17;
    int Y = posYSidebar + 11;
    int space = 14;
    TextColor(DO);
    if (list.ds[i].phai == 1) {
        gotoXY(X, Y);
        cout << CanGiuaChu(arr[0], width);
    }
    else {
        gotoXY(X + space, Y);
        cout << CanGiuaChu(arr[1], width);
    }
    TextColor(MACDINH);
    gotoXY(posXSidebar + 8, posYSidebar + 13);
    cout << list.ds[i].soDT;
    if (kiemTraSVCoDuocXoa(listLTC, list.ds[i].maSV) == 1) {
        return 2;
    }
    int kt = XacNhanLuaChon("Xoa sinh vien", posXSidebar + 3, posYSidebar + 23, widthSidebar - 5);
    if (kiemTraSVCoDuocXoa(listLTC, list.ds[i].maSV) == 0) {
        if (kt == 1)
        {
            return xoaSVTrongDSSV(list, list.ds[i].maSV);
        }
        else if (i == 0)
            return 0;
    }
}
int SuaSinhVien(ListSV &list, SinhVien sv) {
    int vt = kiemTraTrungMaSV(list, sv.maSV);
    if (vt >= 0) {
        list.ds[vt] = sv;
        return 1;
    }
    if (KiemTraThongTinSuaSV(list, sv) > 1) {
        return 0;
    }
}

int XuLySuaThongTinSinhVien(ListSV &list, string maSV) {
    int i = kiemTraTrungMaSV(list, maSV);
    SinhVien sv;
    sv = list.ds[i];
    int key = 2;
    int check = -1;
    KhungNhapThongTinSinhVien("Sua sinh vien");

    gotoXY(posXSidebar + 17, posYSidebar + 5);
    cout << sv.maSV;

    gotoXY(posXSidebar + 7, posYSidebar + 7);
    cout << sv.ho;

    gotoXY(posXSidebar + 8, posYSidebar + 9);
    cout << sv.ten;

    string arr[2] = { "Nam", "Nu" };
    int width = (arr[0].length() > arr[1].length()) ? arr[0].length() + 2 : arr[1].length() + 2;
    int X = posXSidebar + 17;
    int Y = posYSidebar + 11;
    int space = 14;
    TextColor(DO);
    if (sv.phai == 1) {
        gotoXY(X, Y);
        cout << CanGiuaChu(arr[0], width);
    }
    else {
        gotoXY(X + space, Y);
        cout << CanGiuaChu(arr[1], width);
    }
    TextColor(MACDINH);
    gotoXY(posXSidebar + 8, posYSidebar + 13);
    cout << sv.soDT;
    
    while (true)
    {
        int r = SuaThongTinSinhVien(sv, key, check);
        ChuyenTruongSuaThongTinSinhVien(key, check);
        int k = KiemTraThongTinSuaSV(list, sv);
        if (r == ESC) {
            break;
        }
        if ((key == 3) && k == 2) {
            FeedBack("Ho khong trong, gom: a-z,A-Z, so ky tu <= 50!", posXContent + 1, posYContent + 2, widthContent - 1, DO);
            key = 2;
        }
        else if ((key == 4) && k == 3) {
            FeedBack("Ten khong trong, gom: a-z,A-Z, so ky tu <= 10!", posXContent + 1, posYContent + 2, widthContent - 1, DO);
            key = 3;
        }
        else if ((key == 5) && k == 4) {
            FeedBack("Phai khong hop le: Nam/Nu!", posXContent + 1, posYContent + 2, widthContent - 1, DO);
            key = 4;
        }
        else if ((key == 6) && k == 5) {
            FeedBack("SDT khong trong, gom: 0-9, so ky tu <= 10!", posXContent + 1, posYContent + 2, widthContent - 1, DO);
            key = 5;
        }
        else if (k == 1) {
            if (r == INS) {
                int i = XacNhanLuaChon("Sua sinh vien", posXSidebar + 3, posYSidebar + 23, widthSidebar - 5);
                if (i == 1)
                {
                    int kt = SuaSinhVien(list, sv);
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

void BangDanhSachSVTheoLop(ListSV &list,ListLTC &listLTC,SinhVien &sv)
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
    HuongDan(1);
    veBangSinhVien(posX, posX, width, height);
    int n = 0;
    int cs = 0;
    int STT;
    IndexSV *nodes[MAXSV];
    gotoXY(3, 4);
    cout << "Ma lop : " << sv.maLop;
    SapXepDSSVTheoHoTen(list, sv.maLop, nodes, n);
    if (n == 0) {
        FeedBack("Lop chua co sinh vien!", posXContent + 1, posYContent + 2, widthContent - 1, DO);
    }
    int k = 1;
    bool kt = true;
    while (kt == true) {
        k = 1;
        if (check == ESC) { kt = false; }
        if (n <= 12) {
            last = n - 1;
        }
        STT = first;
        if (n > 0) {
            for (int i = first; i <= last; i++) {
                cs = nodes[i]->chiso;
                STT++;
                if (last >= 0) {
                    if (i == current) {
                        TextColor(240);
                    }
                    int j = 0;
                    gotoXY(posX + 1, posY + 2 + k * 1);
                    cout << CanGiuaChu(to_string(STT), 0.1 * width - 1);

                    j += 0.1 * width;
                    gotoXY(posX + 1 + j, posY + 2 + k * 1);
                    cout << CanGiuaChu(list.ds[cs].maSV, 0.2 * width - 1);

                    j += 0.2 * width;
                    gotoXY(posX + 1 + j, posY + 2 + k * 1);
                    cout << CanGiuaChu(nodes[i]->ho, 0.3 * width - 1);

                    j += 0.3 * width;
                    gotoXY(posX + 1 + j, posY + 2 + k * 1);
                    cout << CanGiuaChu(nodes[i]->ten, 0.15 * width - 1);

                    j += 0.15 * width;
                    gotoXY(posX + 1 + j, posY + 2 + k * 1);
                    cout << CanGiuaChu((list.ds[cs].phai == 1 ? "Nam" : "Nu"), 0.1 * width - 1);

                    j += 0.1 * width;
                    gotoXY(posX + 1 + j, posY + 2 + k * 1);
                    cout << CanGiuaChu(list.ds[cs].soDT, width - j - 1);
                    k = k + 2;
                    if (i == current) {
                        TextColor(MACDINH);
                    }
                }
            }
        }
        check = _getch();
        if (check == DOWN || check == UP) {
            DiChuyenThanhSang(n, first, last, current, check);
        }
        if (check == INS)
        {
            int add = XuLyThemSinhVien(list, sv.maLop);
            giaiPhongMangConTroIndexSV(nodes, n);
            n = 0;
            SapXepDSSVTheoHoTen(list, sv.maLop, nodes, n);
            if (add == 1) {
                FeedBack("Them sinh vien thanh cong!", posXContent + 1, posYContent + 2, widthContent - 1, DO);
            }
            if (add == 0) {
                FeedBack("Them sinh vien khong thanh cong!", posXContent + 1, posYContent + 2, widthContent - 1, DO);
            }
            Cls(posXSidebar + 1, posYSidebar + 1, widthSidebar - 1, heightSidebar - 1);
        }
        else if (check == DEL && n > 0) {
            string maSV = list.ds[nodes[current]->chiso].maSV;
            int  i = XuLyXoaSinhVien(list, listLTC, maSV);
            giaiPhongMangConTroIndexSV(nodes, n);
            n = 0;
            SapXepDSSVTheoHoTen(list, sv.maLop, nodes, n);
            if (i == 1) {

                if (last == n && n >= 12) {
                    first--;
                    last--;
                    current--;
                }
                else if (current == last && last == n && n < 12) {
                    last--;
                    current--;
                }
               FeedBack("Xoa sinh vien thanh cong!", posXContent + 1, posYContent + 2, widthContent - 1, DO);
            }
            if (i == 2) FeedBack("Sinh vien da dang ki lop tin chi, khong the xoa!", posXContent + 1, posYContent + 2, widthContent - 1, DO);
            Cls(posXSidebar + 1, posYSidebar + 1, widthSidebar - 1, heightSidebar - 1);
            ClsDanhSachSinhVien();
        }
        else if (check == ENTER)
        {
            int edit = XuLySuaThongTinSinhVien(list, list.ds[nodes[current]->chiso].maSV);
            giaiPhongMangConTroIndexSV(nodes, n);
            n = 0;
            SapXepDSSVTheoHoTen(list, sv.maLop, nodes, n);
            if (edit == 1) {
                FeedBack("Sua sinh vien thanh cong!", posXContent + 1, posYContent + 2, widthContent - 1, DO);
            }
            if (edit == 0) {
                FeedBack("Thong tin sinh vien khong hop le!", posXContent + 1, posYContent + 2, widthContent - 1, DO);
            }
            Cls(posXSidebar + 1, posYSidebar + 1, widthSidebar - 1, heightSidebar - 1);
            ClsDanhSachSinhVien();
        }
    }
    giaiPhongMangConTroIndexSV(nodes, n);
}

//=====================================================DANH SACH LOP==========================================

void xoaPhanTuTrung(Lop *DSLop[], int &n, int vtx) {
    delete DSLop[vtx];
    for (int i = vtx + 1; i < n; i++) {
        DSLop[i - 1] = DSLop[i];
    }
    n--;
}

void DanhSachLop(ListSV &listSV, Lop *DSLop[], int &n) {

    // lay all danh sach lop
    for (int i = 0; i < listSV.sl; i++) {
        DSLop[n] = new Lop;
        DSLop[n]->chiSo = i;
        DSLop[n]->maLop = listSV.ds[i].maLop;
        n++;
    }

    // xem ma lop co trung khong, neu trung thi xoa
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (DSLop[i]->maLop.compare(DSLop[j]->maLop) == 0) {
                xoaPhanTuTrung(DSLop, n, j);
                j--;
            }
        }
    }

    // sap xep danh sach lop
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (DSLop[i]->maLop.compare(DSLop[j]->maLop) > 0) {
                swap(DSLop[i], DSLop[j]);
            }
        }
    }
}

// tinh so luong sinh vien theo tung lop
int tinhSoLuongSVCuaLop(ListSV &listSV,string maLop) {
    int count = 0;
    for (int i = 0; i < listSV.sl; i++) {
        if (listSV.ds[i].maLop.compare(maLop) == 0) {
            count++;
        }
    }
    return count;
}

void giaiPhongDanhSachLop(Lop* DSLop[], int& n) {
    for (int i = 0; i < n; i++) {
        delete DSLop[i];
    }
}

int kiemTraTrungLop(Lop* DSLop[], int &n,string maLop) {
    for (int i = 0; i < n; i++) {
        if (DSLop[i]->maLop.compare(maLop) == 0) {
            return i;
        }
    }
    return -1;
}

void BangDanhSachLop(ListSV &listSV,ListLTC &listLTC,PTRMonHoc &tree)
{
    int f = 0;
    int l = 11;
    int c = f;
    
    int gc = -1;

    int pX = posXContent + 1;
    int pY = posYContent + 0.15 * heightContent;
    int w = widthContent - 2;
    int h = heightContent - 0.15 * heightContent;

    int n = 0;
    Lop *DSLop[MAXLOP];
    Lop lop;
    int k = 1;
    int cs = 0;
    int STT = 0;
    int slsv = 0;
    int j = 0;
    while (true) {
        HuongDan(6);
        veBangDSLop(pX, pY, w, h);
        n = 0;
        DanhSachLop(listSV, DSLop, n);
        k = 1;
        if (gc == ESC) { break; }
        STT = f;
        if (n <= 12)
        {
            l = n - 1;
        }
        slsv = 0;
        for (int i = f; i <= l; i++) {
            STT++;
            if (l >= 0) {
                if (i == c) {
                    TextColor(240);
                }
                j = 0;
                gotoXY(pX + 1, pY + 2 + k * 1);
                cout << CanGiuaChu(to_string(STT), 0.1 * w - 1);

                j += 0.1 * w;
                gotoXY(pX + 1 + j, pY + 2 + k * 1);
                cout << CanGiuaChu(DSLop[i]->maLop, 0.5 * w - 1);

                slsv = tinhSoLuongSVCuaLop(listSV, DSLop[i]->maLop);
                j += 0.5 * w;
                gotoXY(pX + 1 + j, pY + 2 + k * 1);
                cout << CanGiuaChu(to_string(slsv), w - j - 1);
                k = k + 2;
                if (i == c) {
                    TextColor(MACDINH);
                }
            }
            else
            {
                return;
            }
        }
        gc = _getch();
        if (gc == DOWN || gc == UP)
            DiChuyenThanhSang(n, f, l, c, gc);
        else if (gc == INS) {
            VeKhungVien(129, 4, 30, 3);
            int currentCursor = lop.maLop.length();
            gotoXY(130, 5);
            cout << "Nhap ma lop:";
            gotoXY(143, 5);
            int getCheck = -1;
            while (true) {
                if (getCheck == ESC) {
                    Cls(128, 4, 34, 5);
                    break;
                }
                if (_kbhit()) {
                    getCheck = _getch();
                    if ((getCheck >= 'a' && getCheck <= 'z' || getCheck >= 'A' && getCheck <= 'Z' || getCheck >= '0' && getCheck <= '9' || getCheck == 45) && (int)lop.maLop.length() < 15) {
                        lop.maLop.insert(currentCursor, 1, (char)toupper(getCheck));
                        for (int i = currentCursor; i < (int)lop.maLop.length(); i++)
                            cout << lop.maLop[i];
                        currentCursor++;
                    }
                    else if (getCheck == BACKSPACE && lop.maLop.length() != 0)
                    {
                        lop.maLop.erase(--currentCursor, 1);
                        gotoXY(143 + currentCursor, 5);
                        for (int i = currentCursor; i < (int)lop.maLop.length() + 1; i++)
                            cout << " ";
                        gotoXY(143 + currentCursor, 5);
                    }

                    else if (getCheck == ENTER) {
                        int kt = kiemTraTrungLop(DSLop, n, lop.maLop);
                        if (kt == -1) {
                            SinhVien sv;
                            sv.maLop = lop.maLop;
                            Cls(TOADOX, TOADOY, CHIEUNGANG + 2, CHIEUDOC + 2);
                            BangDanhSachSVTheoLop(listSV, listLTC, sv);
                            Cls(TOADOX, TOADOY, CHIEUNGANG + 2, CHIEUDOC + 2);
                        }
                        else {
                            FeedBack("Lop da ton tai!", posXContent + 1, posYContent + 2, widthContent - 1, DO);
                        }
                    }
                }
            }
        }
        else if (gc == ENTER) {
            SinhVien sv;
            sv.maLop = DSLop[c]->maLop;
            Cls(TOADOX, TOADOY, CHIEUNGANG + 2, CHIEUDOC + 2);
            BangDanhSachSVTheoLop(listSV, listLTC, sv);
            Cls(TOADOX, TOADOY, CHIEUNGANG + 2, CHIEUDOC + 2);
        }
        giaiPhongDanhSachLop(DSLop, n);
    }
}

