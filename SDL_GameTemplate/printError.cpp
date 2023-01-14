#include <Windows.h>
#include <iostream>

using namespace std;

void printError(const char* messege) {
	cout << messege << endl;
	MessageBox(NULL, (LPCSTR)messege, NULL, MB_OK | MB_ICONERROR);
}