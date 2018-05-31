#include "stdafx.h"
#include "ConsoleNav.h"

void gotoXY(int x, int y)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	_COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(hConsole, pos);
}

void hideCursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

int menu(int coordX, int coordY, std::string title, int n, ...)
{
	std::cin.clear();
	std::cin.sync();
	hideCursor();
	std::string whitespaces = "                                        ";
	for (int i = 0; i < title.length(); i++) {
		whitespaces[(39 - title.length()) / 2 + i] = title[i];
	}
	va_list parametry;
	va_start(parametry, n);
	std::string *wsk;
	wsk = new std::string[n];
	int pozycja = 1, pozycjaOLD = 1;
	bool refresh = true;
	for (int i = 0; i < n; i++)
	{
		wsk[i] = va_arg(parametry, const char *);
	}
	system("cls");
	va_end(parametry);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 207);
	gotoXY(coordX, coordY);
	std::cout << whitespaces;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

	for (int i = 1; i <= n; i++)
	{
		gotoXY(coordX, coordY + i);
		std::cout << "[" << i << "] " << wsk[i - 1];
	}
	std::cout << std::endl;

	while (refresh == true)
	{
		refresh = false;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		gotoXY(coordX, coordY + pozycjaOLD); std::cout << "[" << pozycjaOLD << "] " << wsk[pozycjaOLD - 1];
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		gotoXY(coordX, coordY + pozycja); std::cout << "[" << pozycja << "] " << wsk[pozycja - 1];
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

		while (refresh == false && (GetConsoleWindow() == GetForegroundWindow()))
		{
			Sleep(10);
			if (GetAsyncKeyState(VK_UP) & 0x8000)
			{
				refresh = true;
				if (pozycja == 1)
				{
					pozycjaOLD = pozycja;
					pozycja = n;
					Sleep(100);
				}

				else
				{
					pozycjaOLD = pozycja;
					pozycja--;
					Sleep(100);
				}
			}
			else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
			{
				refresh = true;
				if (pozycja == n)
				{
					pozycjaOLD = pozycja;
					pozycja = 1;
					Sleep(100);
				}
				else
				{
					pozycjaOLD = pozycja;
					pozycja++;
					Sleep(100);
				}
			}
			else if (GetAsyncKeyState(VK_RETURN) & 0x8000)
			{
				delete[] wsk;
				gotoXY(1, 1);
				Sleep(200);
				std::cin.ignore(1000, '\n');
				return pozycja;
			}
		}
		if (GetConsoleWindow() != GetForegroundWindow())
			Sleep(200);
	}
	return 0;
}

std::string inputPrompt(std::string title)
{
	Sleep(100);
	std::cin.sync();
	std::string input;
	std::string whitespaces = "                                        ";
	for (int i = 0; i < title.length(); i++) {
		whitespaces[(39 - title.length()) / 2 + i] = title[i];
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 207);
	gotoXY(MENU_X, MENU_Y);
	std::cout << whitespaces;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	gotoXY(MENU_X, MENU_Y + 1);
	std::cin >> input;
	system("cls");
	std::cin.clear();
	return input;
}