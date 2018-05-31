#pragma once
#include <iostream>
#include <string>
#include <windows.h>
#include <stdarg.h>

#define MENU_X 40 //Default X-axis coordinate of a console window
#define MENU_Y 10 //Default Y-axis coordinate of a console window

//Places the console cursor at a given position
void gotoXY(int x, int y);

//Hides the console cursor animation
void hideCursor();

//Console menu form, that allows user to navigate using arrow keys
int menu(int x, int y, std::string title, int count, ...);

std::string inputPrompt(std::string title);