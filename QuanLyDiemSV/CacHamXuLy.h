#pragma once
#include "GiaoDien.h"
void TextBox(string str, int width, int height, int toaDoX, int toaDoY)
{
	gotoXY(toaDoX, toaDoY);
	cout << str;
}

void GhiChu(string c, int x, int y,int width, int color, int sleep)
{
	gotoXY(x, y);
	TextColor(color);
	cout << CanGiuaChu(c,width);
	Sleep(sleep);
	gotoXY(x, y);
	TextColor(MACDINH);
	for (int j = x; j <= width + 2; j++)
	{
		cout << ' ';
	}
}

// chuan hoa chuoi: chuoi rong, chuoi co khoang trang, 
void ChuanHoaChuoi(string &str, int key)
{
	/*	1: La chuoi, in hoa va khong rong
		2: La chuoi ky tu, khong rong va khong co chu so
		3: La chuoi so khong co ky tu, khong rong va khong khoang trang
	*/
	// rong => ko nhan,xoa dau cuoi la k trang
	if (key == 1 || key == 2 || key == 3)
	{
		if (str.length() == 0)
			return;
		int ilen = str.length();
		if (str[ilen - 1] == ' ') {
			str.erase(ilen - 1, 1);
		}
		if (str[0] == ' ') {
			str.erase(0, 1);
		}
	}

	if (key == 1)//In hoa va khong rong
	{
		if (str.length() == 0)
			return;
		for (int i = 0, ilen = str.length(); i < ilen; i++)
		{
			if (str[i] >= 'a' && str[i] <= 'z')
				str[i] -= 32;
		}
	}
	if (key == 2)//2: La chuoi ky tu, khong rong va khong co chu so
	{
		if (str.length() == 0)
			return;
		//Xoa khoang trang giua cac ky tu
		for (int i = 0, ilen = str.length() - 1; i < ilen; i++)
		{
			if (str[i] == ' ' && str[i + 1] == ' ')
			{
				str.erase(i, 1);
				i--;
			}
		}

		//	In hoa chu cai dau
		if (str[0] >= 'a' && str[0] <= 'z')
			str[0] -= 32;
		//In thuong
		for (int i = 1; i < str.length(); i++)
		{
			if (str[i] >= 'A' && str[i] <= 'Z' && str[i - 1] != ' ')
				str[i] += 32;
		}
		for (int i = 0, ilen = str.length() - 1; i < ilen; i++)
		{
			if (str[i] == ' ' && str[i + 1] != ' ')
			{
				if (str[i + 1] >= 'a' && str[i + 1] <= 'z')
					str[i + 1] -= 32;
			}

		}
	}
	if (key == 3) // 3: La chuoi so khong co ky tu, khong rong va khong khoang trang
	{
		/*while (str.length() > 1 && str[0] == '0' && str[1] != '.')
			str.erase(0, 1);*/
	}
}

// tam
int NhapDuLieu(string &info, int maxLength, int posX, int posY, int key, int &check, int type)
{
	/*
	1: Chuoi in hoa
	2: Chuong thuong
	3: So thuc
	4: So nguyen
	5: X, Y
	*/
	//info = "";

	int chuyen = -1;
	int currentCursor = info.length();

	gotoXY(posX, posY);
	cout << CanGiuaChu("", maxLength);

	gotoXY(posX, posY);
	cout << info;

	while (true)
	{
		gotoXY(posX + currentCursor, posY);
		chuyen = _getch();
		if (chuyen == 224)
		{
			chuyen = _getch();
			if (chuyen == UP || chuyen == DOWN || chuyen == INS)
			{
				ChuanHoaChuoi(info, key);
				gotoXY(posX + info.length(), posY);
				for (int i = info.length(); i <= maxLength; i++)
					cout << " ";
				gotoXY(posX, posY);
				cout << info;
				check = chuyen;
				return 1;
			}
		}
		else if (chuyen == ESC)
		{
			check = chuyen;
			return 0;
		}
		else if (chuyen == BACKSPACE && info.length() != 0 && currentCursor > 0)
		{
			info.erase(--currentCursor, 1);
			gotoXY(posX + currentCursor, posY);
			for (int i = currentCursor; i < (int)info.length() + 1; i++)
				cout << " ";
			gotoXY(posX + currentCursor, posY);
		}
		else if (currentCursor == 0 && chuyen == SPACEBAR || currentCursor == 0 && chuyen == DOT) {
		}
		// type = chuoi ki tu, in hoa
		else if ((chuyen >= 'a' && chuyen <= 'z' || chuyen >= 'A' && chuyen <= 'Z' || chuyen >= '0' && chuyen <= '9' || chuyen == 45) && (int)info.length() < maxLength && type == 1) {
			info.insert(currentCursor, 1, (char)toupper(chuyen));
			for (int i = currentCursor; i < (int)info.length(); i++)
				cout << info[i];
			currentCursor++;
		}
		// trg xac nhan
		else if ((chuyen == 'N' || chuyen == 'n' || chuyen == 'X' || chuyen == 'x') && type == 5)
		{
			info.insert(currentCursor, 1, (char)toupper(chuyen));
			for (int i = currentCursor; i < (int)info.length(); i++)
				cout << info[i];
			currentCursor++;
		}
			// so nguyen
		else if ((chuyen >= '0' && chuyen <= '9') && (int)info.length() < maxLength && type == 4)
		{
			info.insert(currentCursor, 1, (char)chuyen);
			for (int i = currentCursor; i < (int)info.length(); i++)
				cout << info[i];
			currentCursor++;
		}
		//2 chuoi thuong
		else if (chuyen == SPACEBAR && type == 2)
		{
			if (info[currentCursor - 1] != ' ')
			{
				info.insert(currentCursor, 1, (char)chuyen);
				for (int i = currentCursor; i < (int)info.length(); i++)
					cout << info[i];
				currentCursor++;
			}
		}
		else if ((chuyen >= 'a' && chuyen <= 'z' || chuyen >= 'A' && chuyen <= 'Z' || chuyen >= '0' && chuyen <= '9' || chuyen == SPACEBAR) && (int)info.length() < maxLength && type == 2) {
			info.insert(currentCursor, 1, (char)chuyen);
			for (int i = currentCursor; i < (int)info.length(); i++)
				cout << info[i];
			currentCursor++;
		}
		// so thuc
		else if (chuyen == DOT && type == 3)
		{
			int check = 0;
			for (int i = 0; i < currentCursor; i++)
			{
				if (info[i] == '.') {
					check++;
				}
			}
			if (check < 1)
			{
				info.insert(currentCursor, 1, (char)chuyen);
				for (int i = currentCursor; i < (int)info.length(); i++)
					cout << info[i];
				currentCursor++;
				continue;
			}
		}
		else if ((chuyen >= '0' && chuyen <= '9' || chuyen == DOT) && (int)info.length() < maxLength && type == 3) {
			info.insert(currentCursor, 1, (char)chuyen);
			for (int i = currentCursor; i < (int)info.length(); i++)
				cout << info[i];
			currentCursor++;
		}
	}
}

//TAM
int KiemTraChuoi(string check, int checkKind)
{
	/*
		1 = check chuoi ky tu
		2 = check chuoi so
		3 = check chuoi
		4 = check chuoi khong khoang trang
		5 = check chuoi khong rong
		return dung = 1 or sai = 0
	*/
	// loai 1: chuoi ky tu : A-Z,a-z, khoang trang
	if (checkKind == 1)
	{
		for (int i = 0, ilen = check.length(); i < ilen; i++)
		{
			if ((check[i] >= 'A' && check[i] <= 'Z') || (check[i] >= 'a' && check[i] <= 'z') || (check[i] == (char)SPACEBAR))
				continue;
			else
				return 0;
		}
	}
	//loai 2: chuoi so
	else if (checkKind == 2)
	{
		for (int i = 0, ilen = check.length(); i < ilen; i++)
		{
			if ((check[i] >= '0' && check[i] <= '9') || check[i] == DOT)
				continue;
			else
				return 0;
		}
	}
	// loai 3 : vua so vua ki tu = 1+ 2 = 3;
	else if (checkKind == 3)
	{
		for (int i = 0, ilen = check.length(); i < ilen; i++)
		{
			if ((check[i] >= '0' && check[i] <= '9') || (check[i] >= 'A' && check[i] <= 'Z') || (check[i] >= 'a' && check[i] <= 'z') || check[i] == (char)SPACEBAR || check[i] == DOT || check[i] == 45)
				continue;
			else
				return 0;
		}
	}
	// chuoi bat ky ma khong co khoang trang
	else if (checkKind == 4)
	{
		for (int i = 0, ilen = check.length(); i < ilen; i++)
		{
			if (check[i] != (char)SPACEBAR)
				continue;
			else
				return 0;
		}
	}
	//chuoi rong
	else if (checkKind == 5)
	{
		if (check.length() == 0)
			return 0;
		else
			return 1;
	}
	return 1;
}

//OK LAAAAAAAAAAAAAAAAA
void FeedBack(string s1, int posX, int posY, int width, int color)
{
	TextColor(color);
	gotoXY(posX, posY);
	cout << CanGiuaChu(s1, width);
	Sleep(2500);
	gotoXY(posX, posY);
	TextColor(MACDINH);
	for (int i = posX; i <= width + 5; i++) {
		cout << " ";
	}
}

//OK LAAAAAAAAAAAAAAAAAAAA
int XacNhanLuaChon(string s, int posX, int posY, int length){
	while (true)
	{
		gotoXY(posX, posY);
		TextColor(DO);
		string t = "Xac nhan ";
		t += s;
		t += " Y/N";
		cout << CanGiuaChu(t, length);
		gotoXY(posX + length / 2, posY + 1);
		TextColor(MACDINH);
		char check = _getch();
		if (check == 'y' || check == 'Y')
		{
			return 1;
		}
		else if (check == 'n' || check == 'N')
		{
			return 0;
		}
	}
}

// OK LAAAAAAAAAAAAAAAA
int LuaChon(string arr[])
{
	int key = 0;
	int choice = 0;
	int color = DO;
	int width = (arr[0].length() > arr[1].length()) ? arr[0].length() + 2 : arr[1].length() + 2;
	int X = posXSidebar + 6;
	int Y = posYSidebar + 25;
	int space = 19;
	TextColor(color);
	gotoXY(X, Y);
	cout << CanGiuaChu(arr[0], width);
	TextColor(MACDINH);
	while (true)
	{
		if (key == 224)
		{
			key = _getch();
			switch (key)
			{
			case KEY_LEFT:
			{
				if (choice > 0)
				{
					TextColor(TIM);
					gotoXY(X + space, Y);
					cout << CanGiuaChu(arr[1], width);
					TextColor(color);
					gotoXY(X + space + choice * (-space), Y);
					cout << CanGiuaChu(arr[choice - 1], width);
					choice--;

				}
				else
				{
					TextColor(TIM);
					gotoXY(X, Y);
					cout << CanGiuaChu(arr[0], width);
					TextColor(color);
					gotoXY(X + space + choice * (-space), Y);
					cout << CanGiuaChu(arr[choice + 1], width);
					choice = 2 - 1;

				}
				TextColor(MACDINH);
				break;

			}
			case KEY_RIGHT:
			{
				if (choice < 2 - 1)
				{
					TextColor(TIM);
					gotoXY(X, Y);
					cout << CanGiuaChu(arr[0], width);
					TextColor(color);
					gotoXY(X + space + choice * (-space), Y);
					cout << CanGiuaChu(arr[choice + 1], width);
					choice++;
				}
				else {
					TextColor(TIM);
					gotoXY(X + space, Y);
					cout << CanGiuaChu(arr[1], width);
					TextColor(color);
					gotoXY(X + space + choice * (-space), Y);
					cout << CanGiuaChu(arr[choice - 1], width);
					choice = 0;
				}
				TextColor(MACDINH);
				break;
			}
			default:
			{
				TextColor(TIM);
				gotoXY(X, Y);
				cout << CanGiuaChu(arr[0], width);
				gotoXY(X + space, Y);
				cout << CanGiuaChu(arr[1], width);
				TextColor(MACDINH);
				return -1;
			}
			}
		}
		else if (key == ENTER)
		{
			TextColor(TIM);
			gotoXY(X, Y);
			cout << CanGiuaChu(arr[0], width);
			gotoXY(X + space, Y);
			cout << CanGiuaChu(arr[1], width);
			TextColor(MACDINH);
			return choice;
		}
		key = _getch();
	}
}

//OK LAAAAAAAAAAAAAAAAAA
int ChonGioiTinh(string arr[], int& check, int X, int Y) {

	int width = (arr[0].length() > arr[1].length()) ? arr[0].length() + 2 : arr[1].length() + 2;
	/*int X = posXSidebar + 16;
	int Y = posYSidebar + 11;*/
	int space = 14;
	int choice = 0;
	TextColor(MACDINH);
	gotoXY(X + space, Y);
	cout << CanGiuaChu(arr[choice + 1], width); 
	TextColor(MACDINH);
	TextColor(DO);
	gotoXY(X, Y);
	cout << CanGiuaChu(arr[choice], width); 
	TextColor(MACDINH);
	while (true)
	{
		if (check == 224)
		{
			check = _getch();
			switch (check)
			{
			case UP:
			case DOWN:
			case ENTER:
				return choice;
			case KEY_LEFT:
			{
				if (choice > 0) 
				{
					TextColor(MACDINH);
					gotoXY(X + space, Y); 
					cout << CanGiuaChu(arr[1], width);
					TextColor(DO);
					gotoXY(X + space + choice * (-space), Y);
					cout << CanGiuaChu(arr[choice - 1], width);
					choice--;
				}
				else {
					TextColor(MACDINH);
					gotoXY(X, Y);
					cout << CanGiuaChu(arr[0], width);
					TextColor(DO);
					gotoXY(X + space + choice * (-space), Y);
					cout << CanGiuaChu(arr[choice + 1], width);
					choice = 2 - 1;
				}
				TextColor(MACDINH);
				break;
			}
			case KEY_RIGHT:
			{
				if (choice < 2 - 1) {
					TextColor(MACDINH);
					gotoXY(X, Y);
					cout << CanGiuaChu(arr[0], width);
					TextColor(DO);
					gotoXY(X + space + choice * (-space), Y);
					cout << CanGiuaChu(arr[choice + 1], width);
					choice++;
				}
				else {
					TextColor(MACDINH);
					gotoXY(X + space, Y);
					cout << CanGiuaChu(arr[1], width);
					TextColor(DO);
					gotoXY(X + space + choice * (-space), Y);
					cout << CanGiuaChu(arr[choice - 1], width);
					choice = 0;
				}
				TextColor(MACDINH);
				break;
			}
			default:
			{
				TextColor(MACDINH);
				gotoXY(X, Y);
				cout << CanGiuaChu(arr[0], width);
				gotoXY(X + space, Y);
				cout << CanGiuaChu(arr[1], width);
				TextColor(MACDINH);
				return -1;
			}
			}
		}
		check = _getch();
	}
}

//OK LAAAAAAAAAAAAAAAA
string DinhDangKieuSoThuc(string &f)
{
	while (f[f.length() - 1] == '0')
		f.erase(f.length() - 1, 1);
	if (f[f.length() - 1] == '.')
		f.erase(f.length() - 1);
	return f;
}
