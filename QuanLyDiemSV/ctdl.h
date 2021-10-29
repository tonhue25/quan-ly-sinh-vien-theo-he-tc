#pragma once
#pragma warning (disable : 4244)
#pragma warning (disable :  4715)
#include <iostream>
#include <string>
#include <fstream>
#include "mylib.h"
using namespace std;

#define DSLOPTINCHI 10000
#define DSSINHVIEN 5000

//===============DANH SACH DANG KY LOP TIN CHI - DSLKD===================
struct DangKiLTC
{
	string maSV;
	int trangThaiDK;
	float diem;
};

struct nodeDangKiLTC
{
	DangKiLTC dk;
	nodeDangKiLTC* next;
};
typedef struct nodeDangKiLTC* PTRDangKiLTC;
PTRDangKiLTC first = NULL;

//==============DANH SACH LOP TIN CHI- MANG CON TRO ==================
struct NienKhoa {
	int nienKhoaDau,nienKhoaCuoi;
};
struct LopTinChi {
	int maLopTC; 
	string maMH;
	NienKhoa nienKhoa;
	int hocKy, nhom, soSVMin, soSVMax;
	int trangThaiLop = 1;
	PTRDangKiLTC DSDKLTC = NULL;
};

struct DanhSachLopTinChi {
	int sl = 0;
	LopTinChi *ds[DSLOPTINCHI];
};
typedef struct DanhSachLopTinChi ListLTC;

//======================DANH SACH SINH VIEN - DSTT====================

struct SinhVien {
	string maSV, ho, ten, soDT, maLop;
	int phai;
};
struct DanhSachSinhVien {
	SinhVien ds[DSSINHVIEN];
	int sl = 0;
};
typedef struct DanhSachSinhVien ListSV;

//===============DANH SACH MON HOC -- CAY NHI PHAN TIM KIEM===========

struct MonHoc{
	string maMH, tenMH;
	int soTCLT, soTCTH;
};

struct nodeMonHoc {
	MonHoc data;
	nodeMonHoc* left;
	nodeMonHoc* right;
};
typedef struct nodeMonHoc* PTRMonHoc;
