#pragma once
#include "DocGhiFile.h"
#define CHIEUNGANG 160
#define CHIEUDOC 40
#define TOADOX 2
#define TOADOY 1

int heightHeader = 0.1 * CHIEUDOC;
int widthHeader = CHIEUNGANG;
int posXHeader = TOADOX;
int posYHeader = TOADOY;

int posXFooter = TOADOX;
int posYFooter = TOADOY + (0.9 * CHIEUDOC);
int heightFooter = CHIEUDOC - (0.9 * CHIEUDOC);
int widthFooter = CHIEUNGANG;

int posXContent = TOADOX;
int posYContent = TOADOY + heightHeader;
int heightContent = CHIEUDOC - (0.1 * CHIEUDOC) - heightFooter;
int widthContent = CHIEUNGANG - (0.2375 * CHIEUNGANG);

const int posYSidebar = posYContent;
const int posXSidebar = TOADOX + widthContent;
const int widthSidebar = CHIEUNGANG - widthContent;
const int heightSidebar = heightContent;

const int UP = 72;
const int  DOWN = 80;
const int  ENTER = 13;
const int  ESC = 27;
const int  DEL = 83;
const int  INS = 82;
const int  DOT = 46;
const int  BACKSPACE = 8;
const int CTRL_F = 6;
const int F5 = 63;
const int KEY_LEFT = 75;
const int SPACEBAR = 32;
const int KEY_RIGHT = 77;
const int MACDINH  = 15;
const int DO = 79;
const int TIM = 95;
const int TIMNHAT = 223;
const int F2 = 60;
void Cls(int posX, int posY, int width, int height);

string CanGiuaChu(string center, int doRong)
{
	string centered;
	centered.resize(doRong, ' ');
	int centerStart = (doRong - center.size()) / 2 + (doRong - center.size()) % 2;
	for (int i = 0, ilen = center.size(); i < ilen; i++)
	{
		centered[centerStart + i] = center[i];
	}
	return centered;
}

void TextBoxV2(string str, int width, int height, int toaDoX, int toaDoY)
{
	int k = (height % 2 == 0) ? height / 2 - 1 : height / 2;
	for (int i = 0; i <= k - 1; i++) {
		gotoXY(toaDoX, toaDoY + i);
		cout << CanGiuaChu("", width);
	}
	gotoXY(toaDoX, toaDoY + k);
	cout << CanGiuaChu(str, width);
	for (int i = k + 1; i <= height - 1; i++) {
		gotoXY(toaDoX, toaDoY + i);
		cout << CanGiuaChu("", width);
	}
}
void Box(string str, int width, int height, int toaDoX, int toaDoY,int bColor) {
	TextColor(bColor);
	TextBoxV2(str, width - 1, height - 1, toaDoX + 1, toaDoY + 1);
	
	if (height <= 1 || width <= 1)return;
	for (int i = toaDoX; i <= toaDoX + width; i++) {
		gotoXY(i, toaDoY);
		cout << " ";
		gotoXY(i, toaDoY + height);
		cout << " ";

	}
	for (int y = toaDoY; y <= toaDoY + height; y++) {
		gotoXY(toaDoX, y);
		cout << " ";
		gotoXY(toaDoX+width,y);
		cout << " ";
	}
	TextColor(15);
}
void Menu(int X, int Y, int width, int height,int distance,int color) {
	Box("QUAN LY DIEM SINH VIEN THEO HE TIN CHI", width + 25, height, TOADOX + (CHIEUNGANG / 3), TOADOY, color);
	
	Box("QUAN LY LOP TIN CHI", width, height, X, Y, color);

	Box("QUAN LY MON HOC", width, height, X, Y + distance, color);

	Box("QUAN LY SINH VIEN", width, height, X, Y+(distance *2), color);

	Box("QUAN LY DANG KI", width, height, X , Y + (distance * 3), color);

	Box("THOAT", width, height, X , Y + (distance * 4), color);
}

void MenuQLLTC(int X, int Y, int width, int height, int distance, int color) {

	Box("DANH SACH LOP TIN CHI", width, height, X, Y, color);

	Box("HUY LOP TIN CHI", width, height, X, Y + (distance), color);

	Box("XEM DIEM LOP TIN CHI", width, height, X, Y + distance*2, color);

	Box("NHAP DIEM", width, height, X, Y + (distance*3), color);

}

void MenuDangKiLTC(int X, int Y, int width, int height, int distance, int color) {

	Box("DANG KI LOP TIN CHI", width, height, X, Y, color);

	Box("XEM DANH SACH DANG KI", width, height, X, Y + (distance), color);

	Box("HUY DANG KI", width, height, X, Y + (distance*2), color);

}

void subMenu(int X,int Y, int width, int height , int distance , int key,int check, int color) {
	if (check) {
		switch (key)
		{
		case 0:
			Box("QUAN LY LOP TIN CHI", width, height, X, Y, color);
			break;
		case 1:
			Box("QUAN LY MON HOC", width, height, X, Y + distance, color);
			break;
		case 2:
			Box("QUAN LY SINH VIEN", width, height, X, Y + (distance * 2), color);
			break;
		case 3:
			Box("QUAN LY DANG KI", width, height, X, Y + (distance * 3), color);
			break;
		case 4:
			Box("THOAT", width, height, X , Y + (distance * 4), color);
			break;
		default:
			break;
		}
	}
}

void subMenuQLLTC(int X, int Y, int width, int height, int distance, int key, int check, int color) {
	if (check) {
		switch (key)
		{
		case 0:
			Box("DANH SACH LOP TIN CHI", width, height, X, Y, color);
			break;
		case 1:
			Box("HUY LOP TIN CHI", width, height, X, Y + (distance), color);
			break;
		case 2:
			Box("XEM DIEM LOP TIN CHI", width, height, X, Y + distance * 2, color);
			break;
		case 3:
			Box("NHAP DIEM", width, height, X, Y + (distance * 3), color);
			break;
		default:
			break;
		}
	}
}

void subMenuDangKiLTC(int X, int Y, int width, int height, int distance, int key, int check, int color) {
	if (check) {
		switch (key)
		{
		case 0:
			Box("DANG KI LOP TIN CHI", width, height, X, Y, color);
			break;
		case 1:
			Box("XEM DANH SACH DANG KI", width, height, X, Y + (distance), color);
			break;
		case 2:
			Box("HUY DANG KI", width, height, X, Y + (distance * 2), color);
			break;
		default:
			break;
		}
	}
}

int chuyenDongVsThanhSang() {
	resizeConsole(1500, 800);
	int X = posXContent;
	int Y = posYContent;
	int x = posXContent;
	int y = posYContent;
	int width = 25;
	int height = 4;
	int distance = 7;
	int nomalColor = 159;
	int hightLight = 224;
	Menu(posXContent, posYContent, width, height,distance, nomalColor);
	int xcu = x;
	int ycu = y;
	bool kt = true;
	bool t = true;
	while (t == true) {
		if (kt == true) {
			int key1 = (ycu - Y) / 7;
			gotoXY(xcu, ycu); 
			subMenu(posXContent, posYContent, width, height, distance, key1, true, nomalColor);

			xcu = x;
			ycu = y;
			int key2 = (y - Y) / 7;
			subMenu(posXContent, posYContent, width, height, distance, key2, true, hightLight);
			kt = false;
		}
		if (_kbhit()) {
			char c = _getch();
			if (c == -32) {
				kt = true;
				c = _getch();
				if (c == UP) {
					if(y!=Y) y -= 7;
					else {
						y = Y + (distance * 4);
					}
				}
				else if (c == DOWN){
					if (y != Y + (distance * 4)) y += 7;
					else {
						y = Y;
					}
				}
			}
			if (c == ESC) {
				break;
			}
			if (c == ENTER) {
				int i = ((y - Y) / 7) + 1;
				if (i == 1) {
					int X = posXContent;
					int Y = posYContent ;
					int x = posXContent + width + 2;
					MenuQLLTC(posXContent + width + 2, posYContent + (distance), width, height, distance, nomalColor);
					int xcu = x;
					int ycu = y;

					bool kt = true;
					bool t = true;

					while (t == true) {
						if (kt == true) {
							int key1 = (ycu - Y) / 7;
							gotoXY(xcu, ycu);
							subMenuQLLTC(posXContent + width + 2, posYContent + (distance), width, height, distance, key1, true, nomalColor);

							xcu = x;
							ycu = y;
							int key2 = (y - Y) / 7;
							subMenuQLLTC(posXContent + width + 2, posYContent + (distance), width, height, distance, key2, true, hightLight);
							kt = false;
						}
						if (_kbhit()) {
							char c = _getch();
							if (c == -32) {
								kt = true;
								c = _getch();
								if (c == UP) {
									if (y != Y) y -= 7;
									else {
										y = Y + distance*3;
									}
								}
								else if (c == DOWN) {
									if (y != Y + distance*3) y += 7;
									else {
										y = Y;
									}
								}
								else if (c == KEY_RIGHT) {
									if (x != X) x += (width + 2);
								}
								else if (c == KEY_LEFT) {
									Cls(x, Y, width * 2, Y + distance * 2);
									break;
								}
							}
							if (c == ENTER) {
								int i = ((y - Y) / 7) + 1;
								if (i == 1) {
									return 11;
								}
								if (i == 2) {
									return 12;
								}
								if (i == 3) {
									return 13;
								}
								if (i == 4) {
									return 14;
								}
							}
							if (c == ESC) {
								break;
							}
						}
					}
				}
				if (i == 4) {
					int X = posXContent;
					int Y = posYContent + distance*2;
					int x = posXContent + width + 2;
					MenuDangKiLTC(posXContent + width + 2, posYContent + (distance*2), width, height, distance, nomalColor);
					int xcu = x;
					int ycu = y;
					int ytam = y - distance;
					bool kt = true;
					bool t = true;

					while (t == true) {
						if (kt == true) {
							int key1 = (ycu - Y) / 7;
							gotoXY(xcu, ycu);
							subMenuDangKiLTC(posXContent + width + 2, posYContent + (distance*2), width, height, distance, key1, true, nomalColor);

							xcu = x;
							ycu = ytam;
							int key2 = (ytam - Y) / 7;
							subMenuDangKiLTC(posXContent + width + 2, posYContent + (distance*2), width, height, distance, key2, true, hightLight);
							kt = false;
						}
						if (_kbhit()) {
							char c = _getch();
							if (c == -32) {
								kt = true;
								c = _getch();
								if (c == UP) {
									if (ytam != Y) ytam -= 7;
									else {
										ytam = Y + distance*2;
									}
								}
								else if (c == DOWN) {
									if (ytam != Y + distance*2) ytam += 7;
									else {
										ytam = Y;
									}
								}
								else if (c == KEY_RIGHT) {
									if (x != X) x += (width + 2);
								}
								else if (c == KEY_LEFT) {
									Cls(x, Y, width * 2, Y + distance);
									break;
								}
							}
							if (c == ENTER) {
								int i = ((ytam - Y) / 7) + 1;
								if (i == 1) {
									return 41;
								}
								if (i == 2) {
									return 42;
								}
								if (i == 3) {
									return 43;
								}
							}
							if (c == ESC) {
								break;
							}
						}
					}
				}
				else 
					return i;
			}
		}
	}
}

void LayMau(){
	for (int i = 1; i < 255; i++) {
		TextColor(i);
		cout << i << " - Hello, nguoi ban den tu tuong lai";
		cout << endl;
	}
}

void Cls(int posX, int posY, int width, int height)
{
	for (int i = 0; i < height; i++)
	{
		gotoXY(posX, posY + i);
		cout << CanGiuaChu(" ", width);
	}
}

void veDuongThangDung(int toaDoX, int toaDoY ,int chieuDoc) {
	for (int i = 0; i < chieuDoc - 1; i++)
	{
		gotoXY(toaDoX, toaDoY + i + 1);
		cout << char(179);
	}
	cout << "\n";
}
void veDuongNamNgang(int toaDoX, int toaDoY, int chieuNgang) {
	
	gotoXY(toaDoX + 1, toaDoY);
	for (int i = 0; i < chieuNgang - 1; i++)
	{
		cout << char(196);
	}

}
void VeKhungVien(int toaDoX, int toaDoY, int chieuNgang, int chieuDoc)
{
	gotoXY(toaDoX, toaDoY);
	cout << char(218);
	gotoXY(toaDoX, toaDoY + chieuDoc);
	cout << char(192);
	gotoXY(toaDoX + chieuNgang, toaDoY);
	cout << char(191);
	gotoXY(toaDoX + chieuNgang, toaDoY + chieuDoc);
	cout << char(217);

	gotoXY(toaDoX + 1, toaDoY);
	for (int i = 0; i < chieuNgang - 1; i++)
	{
		cout << char(196);
	}
	gotoXY(toaDoX + 1, toaDoY + chieuDoc);
	for (int i = 0; i < chieuNgang - 1; i++)
	{
		cout << char(196);
	}
	for (int i = 0; i < chieuDoc - 1; i++)
	{
		gotoXY(toaDoX, toaDoY + i + 1);
		cout << char(179);
		gotoXY(toaDoX + chieuNgang, toaDoY + i + 1);
		cout << char(179);
	}
	cout << "\n";
}
// content
void veBang(int toaDoX, int toaDoY, int chieuDoc, int chieuNgang) {
	gotoXY(toaDoX, toaDoY);
	cout << char(218);
	gotoXY(toaDoX, toaDoY + chieuDoc);
	cout << char(192);
	gotoXY(toaDoX + chieuNgang, toaDoY);
	cout << char(191);
	gotoXY(toaDoX + chieuNgang, toaDoY + chieuDoc);
	cout << char(217);
	VeKhungVien(toaDoX, toaDoY, chieuNgang, chieuDoc);
}

void DiChuyenThanhSang(int soLuongPhanTu, int& first, int& last, int& current, int check)
{
	if (check == DOWN)
	{

		if (soLuongPhanTu > 12)
		{
			if (current != last)
			{
				current++;
			}
			else if (current == last && last != soLuongPhanTu - 1)
			{
				first++;
				last++;
				current++;
			}
			else if (current == last && last == soLuongPhanTu - 1)
			{
				first = 0;
				last = 11;
				current = first;
			}
		}
		else if (soLuongPhanTu <= 12)
		{
			if (current != last && last > 0)
			{
				current++;
			}
			else if (current == last)
			{
				first = 0;
				current = first;

			}
		}
	}
	else if (check == UP)
	{
		if (soLuongPhanTu <= 12)
		{
			if (current != first)
			{
				current--;
			}
			else if (current == first)
			{
				first = 0;
				current = last;
			}
		}
		else
		{
			if (current != first)
			{
				current--;
			}
			else if (current == first && first != 0)
			{
				first--;
				last--;
				current--;
			}
			else if (current == first && first == 0)
			{
				last = soLuongPhanTu - 1;
				first = last - 12 + 1;
				current = last;
			}

		}
	}
}

void KhungChuongTrinh()
{
	TextColor(MACDINH);
	VeKhungVien(TOADOX, TOADOY, CHIEUNGANG, CHIEUDOC);
	VeKhungVien(posXContent, posYContent, widthContent, heightContent);
	VeKhungVien(posXFooter, posYFooter, CHIEUNGANG, heightFooter);
	VeKhungVien(posXSidebar, posYSidebar, widthSidebar, heightSidebar);

	gotoXY(posXContent, posYContent);
	cout << char(195);
	gotoXY(posXFooter, posYFooter);
	cout << char(195);
	gotoXY(posXContent + CHIEUNGANG, posYContent);
	cout << char(180);
	gotoXY(posXFooter + CHIEUNGANG, posYFooter);
	cout << char(180);
	int WS = CHIEUNGANG - (CHIEUNGANG * 0.3);
	gotoXY(posXSidebar, posYSidebar);
	cout << char(194);
	gotoXY(posXFooter + widthContent, posYFooter);
	cout << char(193);
	TextColor(MACDINH);
}

void veBangLopTinChi(int toaDoX, int toaDoY, int chieuDoc, int chieuNgang) {
	toaDoX = posXContent + 1;
	toaDoY = posYContent + 0.15 * heightContent;
	chieuNgang = widthContent - 2;
	chieuDoc = heightContent - 0.15 * heightContent;
	Box("DANH SACH LOP TIN CHI", 30, 2, TOADOX + 50, TOADOY, 159);
	int heightMenu = 2;
	veBang(toaDoX, toaDoY, chieuDoc, chieuNgang);
	int i = 0;
	int x = 0.08 * chieuNgang - 1;

	gotoXY(toaDoX + 1, toaDoY + 1);
	cout << CanGiuaChu("STT", 0.08 * chieuNgang - 1);
	veDuongThangDung(toaDoX + 1 + x, toaDoY, chieuDoc);

	i += 0.08 * chieuNgang;
	x += 0.15 * chieuNgang;
	gotoXY(toaDoX + 1 + i, toaDoY + 1);
	cout << CanGiuaChu("Ma mon hoc", 0.15 * chieuNgang - 1);
	veDuongThangDung(toaDoX + 1 + x, toaDoY, chieuDoc);

	i += 0.15 * chieuNgang;
	x += 0.3*chieuNgang;
	gotoXY(toaDoX + 1 + i, toaDoY + 1);
	cout << CanGiuaChu("Ten mon hoc", 0.3 * chieuNgang - 1);

	veDuongThangDung(toaDoX + 1 + x, toaDoY, chieuDoc);

	i += 0.3 * chieuNgang;
	x += 0.1 * chieuNgang;
	gotoXY(toaDoX + 1 + i, toaDoY + 1);
	cout << CanGiuaChu("Nhom", 0.1 * chieuNgang - 1);
	veDuongThangDung(toaDoX + 1 + x, toaDoY, chieuDoc);

	i += 0.1 * chieuNgang;
	x += 0.1 * chieuNgang;
	gotoXY(toaDoX + 1 + i, toaDoY + 1);
	cout << CanGiuaChu("Ma LTC", 0.1 * chieuNgang - 1);

	veDuongThangDung(toaDoX + 1 + x, toaDoY, chieuDoc);

	i += 0.1 * chieuNgang;
	x += 0.1 * chieuNgang;
	gotoXY(toaDoX + 1 + i, toaDoY + 1);
	cout << CanGiuaChu("SL Min", 0.1 * chieuNgang - 1);

	veDuongThangDung(toaDoX + 1 + x, toaDoY, chieuDoc);

	i += 0.1 * chieuNgang;
	x += 0.1 * chieuNgang;
	gotoXY(toaDoX + 1 + i, toaDoY + 1);
	cout << CanGiuaChu("SL Max", 0.1 * chieuNgang - 1);

	veDuongThangDung(toaDoX + 1 + x, toaDoY, chieuDoc);

	i += 0.1 * chieuNgang;
	gotoXY(toaDoX + 1 + i, toaDoY + 1);
	cout << CanGiuaChu("TTL", chieuNgang - x - 1);

	veDuongNamNgang(toaDoX, toaDoY + heightMenu, chieuNgang);

}

void ClsDanhSachLTC(){
	int k = 0;
	int posX = posXContent + 1;
	int posY = posYContent + 0.15 * heightContent;
	int width = widthContent - 2;
	int height = heightContent - 0.15 * heightContent;
	while (k != 12)
	{
		int j = 0;
		gotoXY(posX + 1, posY + 3 + k * 2);
		cout << CanGiuaChu(" ", 0.08 * width - 1);

		j += 0.08 * width;
		gotoXY(posX + 1 + j, posY + 3 + k * 2);
		cout << CanGiuaChu(" ", 0.15 * width - 1);

		j += 0.15 * width;
		gotoXY(posX + 1 + j, posY + 3 + k * 2);
		cout << CanGiuaChu(" ", 0.3 * width - 1);

		j += 0.3 * width;
		gotoXY(posX + 1 + j, posY + 3 + k * 2);
		cout << CanGiuaChu(" ", 0.1 * width - 1);
		j += 0.1 * width;
		gotoXY(posX + 1 + j, posY + 3 + k * 2);
		cout << CanGiuaChu(" ", 0.1 * width - 1);

		j += 0.1 * width;
		gotoXY(posX + 1 + j, posY + 3 + k * 2);
		cout << CanGiuaChu(" ", 0.08 * width - 1);

		j += 0.1 * width;
		gotoXY(posX + 1 + j, posY + 3 + k * 2);
		cout << CanGiuaChu(" ", 0.1 * width - 1);

		j += 0.1 * width;
		gotoXY(posX + 1 + j, posY + 3 + k * 2);
		cout << CanGiuaChu(" ", width - j - 1);
		k += 1;
	}
}

void ClsDanhSachMonHoc() {
	int k = 0;
	int posX = posXContent + 1;
	int posY = posYContent + 0.15 * heightContent;
	int width = widthContent - 2;
	int height = heightContent - 0.15 * heightContent;
	while (k != 12)
	{
		int j = 0;

		gotoXY(posX + 1, posY + 3 + k * 2);
		cout << CanGiuaChu(" ", 0.1 * width - 1);

		j += 0.1 * width;
		gotoXY(posX + 1 + j, posY + 3 + k * 2);
		cout << CanGiuaChu(" ", 0.2 * width - 1);

		j += 0.2 * width;
		gotoXY(posX + 1 + j, posY + 3 + k * 2);
		cout << CanGiuaChu(" ", 0.4 * width - 1);

		j += 0.4 * width;
		gotoXY(posX + 1 + j, posY + 3 + k * 2);
		cout << CanGiuaChu(" ", 0.15 * width - 1);

		j += 0.15 * width;
		gotoXY(posX + 1 + j, posY + 3 + k * 2);
		cout << CanGiuaChu(" ", width - j - 1);
		k += 1;
	}
}

void XoaKhungDKLopTinChi() {
	int height = heightContent - 0.15 * heightContent;
	int width = widthContent - 2;
	int posX = posXContent + 1;
	int posY = posYContent + 0.15 * heightContent;
	int k = 1;
	while (k != 11) {
		int j = 0;

		gotoXY(posX + width + 1, posY + 3 + k*2);
		cout << CanGiuaChu(" ", 0.3 * widthSidebar - 1);

		j += 0.3 * widthSidebar;
		gotoXY(posX + width + 1 + j, posY + 3+k*2);
		cout << CanGiuaChu(" ", widthSidebar - j - 1);

		k += 1;
	}
}

void HuongDan(int type)
{
	int i = 0, j = 0;
	switch (type)
	{
	case 1:
	{
		TextColor(14);
		TextColor(MACDINH);
		int posX = posXFooter + 3;
		int posY = posYFooter + 2;
		string s[] = { "Ins: Them","Enter: Sua","Delete: Xoa","ESC: Thoat","Up/Down: Len/Xuong" };
		i = 0;
		gotoXY(posX + i, posY);
		cout << s[0];
		i += 25;
		gotoXY(posX + i, posY);
		cout << s[1];
		i += 25;
		gotoXY(posX + i, posY);
		cout << s[2];
		i += 25;
		gotoXY(posX + i, posY);
		cout << s[3];
		i += 25;
		gotoXY(posX + i, posY);
		cout << s[4];
		break;
	}
	case 2:
	{
		TextColor(14);
		VeKhungVien(posXFooter + 1, posYFooter + 1, widthContent - 2, 2);
		TextColor(MACDINH);
		int posX = posXFooter + 3;
		int posY = posYFooter + 2;
		string s[] = { "ESC: Thoat","Up/Down: Len/Xuong" };
		i = 25;
		gotoXY(posX + i, posY);
		cout << s[0];
		i += 35;
		gotoXY(posX + i, posY);
		cout << s[1];
		break;
	}
	case 3:
	{
		TextColor(14);
		VeKhungVien(posXFooter + 1, posYFooter + 1, widthContent - 2, 2);
		TextColor(MACDINH);
		int posX = posXFooter + 3;
		int posY = posYFooter + 2;
		string s[] = { "Enter: Chon","Del: Xoa","ESC: Thoat","Up/Down: Len/Xuong" };
		i = 0;
		gotoXY(posX + i, posY);
		cout << s[0];
		i += 25;
		gotoXY(posX + i, posY);
		cout << s[1];
		i += 25;
		gotoXY(posX + i, posY);
		cout << s[2];
		i += 25;
		gotoXY(posX + i, posY);
		cout << s[3];
		break;
	}
	case 4:
	{
		TextColor(14);
		VeKhungVien(posXFooter + 1, posYFooter + 1, widthContent - 2, 2);
		TextColor(MACDINH);
		int posX = posXFooter + 3;
		int posY = posYFooter + 2;
		string s[] = { "Del: Xoa","ESC: Thoat","Up/Down: Len/Xuong" };
		i = 0;
		gotoXY(posX + i, posY);
		cout << s[0];
		i += 25;
		gotoXY(posX + i, posY);
		cout << s[1];
		i += 25;
		gotoXY(posX + i, posY);
		cout << s[2];
		break;
	}
	case 5:
	{
		TextColor(14);
		VeKhungVien(posXFooter + 1, posYFooter + 1, widthContent - 2, 2);
		TextColor(MACDINH);
		int posX = posXFooter + 3;
		int posY = posYFooter + 2;
		string s[] = { "Backspace: Xoa","Enter: OK","F2: Luu","ESC: Thoat","Up/Down: Len/Xuong" };
		i = 0;
		gotoXY(posX + i, posY);
		cout << s[0];
		i += 25;
		gotoXY(posX + i, posY);
		cout << s[1];
		i += 25;
		gotoXY(posX + i, posY);
		cout << s[2];
		i += 25;
		gotoXY(posX + i, posY);
		cout << s[3];
		i += 25;
		gotoXY(posX + i, posY);
		cout << s[4];
		break;
	}
	case 6:
	{
		TextColor(14);
		VeKhungVien(posXFooter + 1, posYFooter + 1, widthContent - 2, 2);
		TextColor(MACDINH);
		int posX = posXFooter + 3;
		int posY = posYFooter + 2;
		string s[] = { "Enter: Chon","INS: Them","ESC: Thoat","Up/Down: Len/Xuong" };
		i = 0;
		gotoXY(posX + i, posY);
		cout << s[0];
		i += 25;
		gotoXY(posX + i, posY);
		cout << s[1];
		i += 25;
		gotoXY(posX + i, posY);
		cout << s[2];
		i += 25;
		gotoXY(posX + i, posY);
		cout << s[3];
		break;
	}
	case 7:
	{
		TextColor(14);
		VeKhungVien(posXFooter + 1, posYFooter + 1, widthContent - 2, 2);
		TextColor(MACDINH);
		int posX = posXFooter + 3;
		int posY = posYFooter + 2;
		string s[] = { "Up: Len","Down: Xuong / Tiep tuc","ESC: Thoat" };
		i = 25;
		gotoXY(posX + i, posY);
		cout << s[0];
		i += 25;
		gotoXY(posX + i, posY);
		cout << s[1];
		i += 40;
		gotoXY(posX + i, posY);
		cout << s[2];
		break;
	}
	case 8:
	{
		TextColor(14);
		VeKhungVien(posXFooter + 1, posYFooter + 1, widthContent - 2, 2);
		TextColor(MACDINH);
		int posX = posXFooter + 3;
		int posY = posYFooter + 2;
		string s[] = { "Down: Tiep tuc","ESC: Thoat" };
		i = 25;
		gotoXY(posX + i, posY);
		cout << s[0];
		i += 40;
		gotoXY(posX + i, posY);
		cout << s[1];
		break;
	}
	case 9:
	{
		TextColor(14);
		VeKhungVien(posXFooter + 1, posYFooter + 1, widthContent - 2, 2);
		TextColor(MACDINH);
		int posX = posXFooter + 3;
		int posY = posYFooter + 2;
		string s[] = { "Up/Down: Len/Xuong","ESC: Thoat" };
		i = 25;
		gotoXY(posX + i, posY);
		cout << s[0];
		i += 40;
		gotoXY(posX + i, posY);
		cout << s[1];
		break;
	}
	default:
		break;
	}
}

void veBangMonHoc(int toaDoX, int toaDoY, int chieuDoc, int chieuNgang) {
	toaDoX = posXContent + 1;
	toaDoY = posYContent + 0.15 * heightContent;
	chieuNgang = widthContent - 2;
	chieuDoc = heightContent - 0.15 * heightContent;
	Box("DANH SACH MON HOC", 30, 2, TOADOX + 60, TOADOY, 159);
	int heightMenu = 2;
	veBang(toaDoX, toaDoY, chieuDoc, chieuNgang);
	int i = 0;
	int x = 0.1 * chieuNgang - 1;
	gotoXY(toaDoX + 1, toaDoY + 1);
	cout << CanGiuaChu("STT", 0.1 * chieuNgang - 1);
	veDuongThangDung(toaDoX + 1 + x, toaDoY, chieuDoc);
	i += 0.1 * chieuNgang;
	x += 0.2 * chieuNgang;
	gotoXY(toaDoX + 1 + i, toaDoY + 1);
	cout << CanGiuaChu("Ma mon hoc", 0.2 * chieuNgang - 1);
	veDuongThangDung(toaDoX + 1 + x, toaDoY, chieuDoc);
	i += 0.2 * chieuNgang;
	x += 0.4 * chieuNgang;
	gotoXY(toaDoX + 1 + i, toaDoY + 1);
	cout << CanGiuaChu("Ten mon hoc", 0.4 * chieuNgang - 1);
	veDuongThangDung(toaDoX + 1 + x, toaDoY, chieuDoc);
	i += 0.4 * chieuNgang;
	x += 0.15 * chieuNgang;
	gotoXY(toaDoX + 1 + i, toaDoY + 1);
	cout << CanGiuaChu("SoTC LT", 0.15 * chieuNgang - 1);
	veDuongThangDung(toaDoX + 1 + x, toaDoY, chieuDoc);
	i += 0.15 * chieuNgang;
	x += 0.1 * chieuNgang;
	gotoXY(toaDoX + 1 + i, toaDoY + 1);
	cout << CanGiuaChu("SoTC TH", 0.1 * chieuNgang - 1);
	veDuongNamNgang(toaDoX, toaDoY + heightMenu, chieuNgang);
}

void veBangSinhVien(int toaDoX, int toaDoY, int chieuDoc, int chieuNgang) {
	toaDoX = posXContent + 1;
	toaDoY = posYContent + 0.15 * heightContent;
	chieuNgang = widthContent - 2;
	chieuDoc = heightContent - 0.15 * heightContent;
	Box("DANH SACH SINH VIEN", 30, 2, TOADOX + 60, TOADOY, 159);

	int heightMenu = 2;
	veBang(toaDoX, toaDoY, chieuDoc, chieuNgang);

	int i = 0;
	int x = 0.1 * chieuNgang - 1;
	gotoXY(toaDoX + 1, toaDoY + 1);
	cout << CanGiuaChu("STT", 0.1 * chieuNgang - 1);
	veDuongThangDung(toaDoX + 1 + x, toaDoY, chieuDoc);

	//string maSV, ho, ten, phai, soDT, maLop;
	i += 0.1 * chieuNgang;
	x += 0.2 * chieuNgang; 
	gotoXY(toaDoX + 1 + i, toaDoY + 1);
	cout << CanGiuaChu("Ma sinh vien", 0.2 * chieuNgang - 1);
	veDuongThangDung(toaDoX + 1 + x, toaDoY, chieuDoc);

	i += 0.2 * chieuNgang;
	x += 0.3 * chieuNgang;
	gotoXY(toaDoX + 1 + i, toaDoY + 1);
	cout << CanGiuaChu("Ho", 0.3 * chieuNgang - 1);
	veDuongThangDung(toaDoX + 1 + x, toaDoY, chieuDoc);

	i += 0.3 * chieuNgang;
	x += 0.15 * chieuNgang;
	gotoXY(toaDoX + 1 + i, toaDoY + 1);
	cout << CanGiuaChu("Ten", 0.15 * chieuNgang - 1);
	veDuongThangDung(toaDoX + 1 + x, toaDoY, chieuDoc);

	i += 0.15 * chieuNgang;
	x += 0.1 * chieuNgang;
	gotoXY(toaDoX + 1 + i, toaDoY + 1);
	cout << CanGiuaChu("Phai", 0.1 * chieuNgang - 1);
	veDuongThangDung(toaDoX + 1 + x, toaDoY, chieuDoc);

	i += 0.1 * chieuNgang;
	x += 0.1 * chieuNgang;
	gotoXY(toaDoX + 1 + i, toaDoY + 1);
	cout << CanGiuaChu("SDT", 0.1 * chieuNgang - 1);
	veDuongNamNgang(toaDoX, toaDoY + heightMenu, chieuNgang);

}

void ClsDanhSachSinhVien() {
	int k = 0;
	int posX = posXContent + 1;
	int posY = posYContent + 0.15 * heightContent;
	int width = widthContent - 2;
	int height = heightContent - 0.15 * heightContent;
	while (k != 12)
	{
		int j = 0;

		gotoXY(posX + 1, posY + 3 + k * 2);
		cout << CanGiuaChu(" ", 0.1 * width - 1);

		j += 0.1 * width;
		gotoXY(posX + 1 + j, posY + 3 + k * 2);
		cout << CanGiuaChu(" ", 0.2 * width - 1);

		j += 0.2 * width;
		gotoXY(posX + 1 + j, posY + 3 + k * 2);
		cout << CanGiuaChu(" ", 0.3 * width - 1);

		j += 0.3 * width;
		gotoXY(posX + 1 + j, posY + 3 + k * 2);
		cout << CanGiuaChu(" ", 0.15 * width - 1);

		j += 0.15 * width;
		gotoXY(posX + 1 + j, posY + 3 + k * 2);
		cout << CanGiuaChu(" ", 0.1 * width - 1);

		j += 0.1 * width;
		gotoXY(posX + 1 + j, posY + 3 + k * 2);
		cout << CanGiuaChu(" ", width - j - 1);
		k += 1;
	}
}

//=================VE BANG DANG KI LOP TIN CHI ==========================

// su dung cls mon hoc nhe// no tuong tu a
void veBangDangKiLTC(int toaDoX, int toaDoY, int chieuDoc, int chieuNgang) {
	toaDoX = posXContent + 1;
	toaDoY = posYContent + 0.15 * heightContent;
	chieuNgang = widthContent - 2;
	chieuDoc = heightContent - 0.15 * heightContent;

	Box("DANG KI LOP TIN CHI", 30, 2, TOADOX + 60, TOADOY, 159);

	int heightMenu = 2;
	veBang(toaDoX, toaDoY, chieuDoc, chieuNgang);

	int i = 0;
	int x = 0.06 * chieuNgang - 1;
	gotoXY(toaDoX + 1, toaDoY + 1);
	cout << CanGiuaChu("STT", 0.06 * chieuNgang - 1);
	veDuongThangDung(toaDoX + 1 + x, toaDoY, chieuDoc);

	// MA MH, TEN MH,NHOM, SO SV DA DK, SO SLOT CON TRONG

	i += 0.06 * chieuNgang;
	x += 0.15 * chieuNgang;
	gotoXY(toaDoX + 1 + i, toaDoY + 1);
	cout << CanGiuaChu("Ma mon hoc", 0.15 * chieuNgang - 1);
	veDuongThangDung(toaDoX + 1 + x, toaDoY, chieuDoc);

	i += 0.15 * chieuNgang;
	x += 0.3 * chieuNgang;
	gotoXY(toaDoX + 1 + i, toaDoY + 1);
	cout << CanGiuaChu("Ten mon hoc", 0.3 * chieuNgang - 1);
	veDuongThangDung(toaDoX + 1 + x, toaDoY, chieuDoc);

	i += 0.3 * chieuNgang;
	x += 0.15 * chieuNgang;
	gotoXY(toaDoX + 1 + i, toaDoY + 1);
	cout << CanGiuaChu("Ma LTC", 0.15 * chieuNgang - 1);
	veDuongThangDung(toaDoX + 1 + x, toaDoY, chieuDoc);

	i += 0.15 * chieuNgang;
	x += 0.15 * chieuNgang;
	gotoXY(toaDoX + 1 + i, toaDoY + 1);
	cout << CanGiuaChu("Nhom", 0.15 * chieuNgang - 1);
	veDuongThangDung(toaDoX + 1 + x, toaDoY, chieuDoc);

	i += 0.15 * chieuNgang;
	x += 0.1 * chieuNgang;
	gotoXY(toaDoX + 1 + i, toaDoY + 1);
	cout << CanGiuaChu("SL Da DK", 0.1 * chieuNgang - 1);
	veDuongThangDung(toaDoX + 1 + x, toaDoY, chieuDoc);

	i += 0.1 * chieuNgang;
	x += 0.1 * chieuNgang;
	gotoXY(toaDoX + 1 + i, toaDoY + 1);
	cout << CanGiuaChu("SL trong", 0.1 * chieuNgang - 1);
	veDuongNamNgang(toaDoX, toaDoY + heightMenu, chieuNgang);

}

//==============================================VE BANG CHO CAU B==================================
void veBangDSSVConDangKiLTC(int toaDoX, int toaDoY, int chieuDoc, int chieuNgang) {
	toaDoX = posXContent + 1;
	toaDoY = posYContent + 0.15 * heightContent;
	chieuNgang = widthContent - 2;
	chieuDoc = heightContent - 0.15 * heightContent;

	Box("DANH SACH SINH VIEN CON DANG KI LOP TIN CHI", 65, 2, TOADOX + 35, TOADOY, 159);
	int heightMenu = 2;
	veBang(toaDoX, toaDoY, chieuDoc, chieuNgang);
	int i = 0;
	int x = 0.1 * chieuNgang - 1;
	gotoXY(toaDoX + 1, toaDoY + 1);
	cout << CanGiuaChu("STT", 0.1 * chieuNgang - 1);
	veDuongThangDung(toaDoX + 1 + x, toaDoY, chieuDoc);

	i += 0.1 * chieuNgang;
	x += 0.3 * chieuNgang;
	gotoXY(toaDoX + 1 + i, toaDoY + 1);
	cout << CanGiuaChu("Ma sinh vien", 0.3 * chieuNgang - 1);
	veDuongThangDung(toaDoX + 1 + x, toaDoY, chieuDoc);


	i += 0.3 * chieuNgang;
	x += 0.3 * chieuNgang;
	gotoXY(toaDoX + 1 + i, toaDoY + 1);
	cout << CanGiuaChu("Ho", 0.3 * chieuNgang - 1);
	veDuongThangDung(toaDoX + 1 + x, toaDoY, chieuDoc);


	i += 0.3 * chieuNgang;
	gotoXY(toaDoX + 1 + i, toaDoY + 1);
	cout << CanGiuaChu("Ten", chieuNgang - i - 1);
	veDuongNamNgang(toaDoX, toaDoY + heightMenu, chieuNgang);
}
void KhungNhapMaTimKiem(string h, string chuoi) {
	int x = posXContent + 30;
	VeKhungVien(x + 1, posYContent + 2, widthContent / 2 - 2, heightContent / 4 - 2);
	gotoXY(x + 1 + (widthContent / 2 - 2) / 2 - (widthContent / 2 - 2) / 4, posYContent + 2);
	cout << CanGiuaChu(h, (widthContent / 2 - 2) / 2);
	int i = 0;
	gotoXY(x + 3, posYContent + 5 + i);
	cout << chuoi;
	gotoXY(x + 3 + chuoi.length() + 1, posYContent + 5 + i);
	cout << ":";
}

void veBangDiem(int toaDoX, int toaDoY, int chieuDoc, int chieuNgang) {
	toaDoX = posXContent + 1;
	toaDoY = posYContent + 0.15 * heightContent;
	chieuNgang = widthContent - 2;
	chieuDoc = heightContent - 0.15 * heightContent;

	int heightMenu = 2;
	veBang(toaDoX, toaDoY, chieuDoc, chieuNgang);
	int i = 0;
	int x = 0.1 * chieuNgang - 1;
	gotoXY(toaDoX + 1, toaDoY + 1);
	cout << CanGiuaChu("STT", 0.1 * chieuNgang - 1);
	veDuongThangDung(toaDoX + 1 + x, toaDoY, chieuDoc);

	i += 0.1 * chieuNgang;
	x += 0.2 * chieuNgang;
	gotoXY(toaDoX + 1 + i, toaDoY + 1);
	cout << CanGiuaChu("Ma sinh vien", 0.2 * chieuNgang - 1);
	veDuongThangDung(toaDoX + 1 + x, toaDoY, chieuDoc);


	i += 0.2 * chieuNgang;
	x += 0.3 * chieuNgang;
	gotoXY(toaDoX + 1 + i, toaDoY + 1);
	cout << CanGiuaChu("Ho", 0.3 * chieuNgang - 1);
	veDuongThangDung(toaDoX + 1 + x, toaDoY, chieuDoc);


	i += 0.3 * chieuNgang;
	x += 0.2 * chieuNgang;
	gotoXY(toaDoX + 1 + i, toaDoY + 1);
	cout << CanGiuaChu("Ten", 0.2 * chieuNgang - 1);
	veDuongThangDung(toaDoX + 1 + x, toaDoY, chieuDoc);

	i += 0.2 * chieuNgang;
	gotoXY(toaDoX + 1 + i, toaDoY + 1);
	cout << CanGiuaChu("Diem", chieuNgang - i - 1);
	veDuongNamNgang(toaDoX, toaDoY + heightMenu, chieuNgang);
}

void veBangDSLop(int toaDoX, int toaDoY, int chieuDoc, int chieuNgang) {
	toaDoX = posXContent + 1;
	toaDoY = posYContent + 0.15 * heightContent;
	chieuNgang = widthContent - 2;
	chieuDoc = heightContent - 0.15 * heightContent;
	Box("DANH SACH LOP", 30, 2, TOADOX + 50, TOADOY, 159);
	int heightMenu = 2;
	veBang(toaDoX, toaDoY, chieuDoc, chieuNgang);
	int i = 0;
	int x = 0.1 * chieuNgang - 1;
	gotoXY(toaDoX + 1, toaDoY + 1);
	cout << CanGiuaChu("STT", 0.1 * chieuNgang - 1);
	veDuongThangDung(toaDoX + 1 + x, toaDoY, chieuDoc);
	i += 0.1 * chieuNgang;
	x += 0.5 * chieuNgang;
	gotoXY(toaDoX + 1 + i, toaDoY + 1);
	cout << CanGiuaChu("Ma lop", 0.5 * chieuNgang - 1);
	veDuongThangDung(toaDoX + 1 + x, toaDoY, chieuDoc);
	
	i += 0.5 * chieuNgang;
	gotoXY(toaDoX + 1 + i, toaDoY + 1);
	cout << CanGiuaChu("So Luong SV", chieuNgang -i- 1);

	veDuongNamNgang(toaDoX, toaDoY + heightMenu, chieuNgang);
}

// ve khung hien thi lop tin chi da dk
void VeKhungDKLopTinChi(string h) {
	int height = heightContent - 0.15 * heightContent;
	int width = widthContent - 2;
	int posX = posXContent + 1;
	int posY = posYContent + 0.15 * heightContent;


	VeKhungVien(posX + width, posY, widthSidebar, height);
	veDuongNamNgang(posX + width, posY + 2, widthSidebar);
	TextColor(DO);
	gotoXY(posX + width + widthSidebar / 4, posY + 1);
	cout << CanGiuaChu(h, (widthSidebar - 2) / 2);
	TextColor(15);

	int i = 0;
	int x = 0.3 * widthSidebar - 1;
	gotoXY(posX + width + 1, posY + 3);
	cout << CanGiuaChu("STT", 0.3 * widthSidebar - 1);
	veDuongNamNgang(posX + width, posY + 4, widthSidebar);
	veDuongThangDung(posX + width + 1 + x, posY + 2, height - 2);

	i += 0.3 * widthSidebar;
	gotoXY(posX + width + 1 + i, posY + 3);
	cout << CanGiuaChu("Ma LTC", widthSidebar - i - 1);
}
