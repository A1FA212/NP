#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <CommCtrl.h>
#include "resource.h"
#include <cstdio>

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc, 0);
	return 0;
}

//Процедура окна - это самая обычная функция, которая вызывается при запуске окна.
BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//Все принимаемые параметры - это числовые значения длиной 4 Байта.
	//HWND - Handler to Window (обработчик окна) - это число, которое идентифицирует окно.
	//Любые обращения к окну можно выполнить только через его обработчик.
	//uMsg  (Message) - сообщение, которое отправляется окну.
	//wParam, lParam - параметры сообщения. Они еще делятся на LOWORD и HIWORD.
	//LOWORD - это младшее слово.
	//HIWORD - старшее слово.
	//WORD (Слово) - это два Байта.
	int a = 2;
	{
		int a = 2;
	}
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HWND hUpDown = GetDlgItem(hwnd, IDC_SPIN_PREFIX);
		//Функция GetDlgItem() получает HWND элемента интерфейса по его ID
		SendMessage(hUpDown, UDM_SETRANGE32, 0, 32);
		HWND hIPadress = GetDlgItem(hwnd, IDC_IPADDRESS);
		SetFocus(hIPadress);
	}
	break;
	case WM_COMMAND:
		//WM_ - Window Message
		switch (LOWORD(wParam))
		{
		case IDC_IPADDRESS:
		{
			CONST INT SIZE = 256;
			CHAR sz_info[SIZE]{};

			HWND hIPaddress = GetDlgItem(hwnd, IDC_IPADDRESS);
			HWND hStaticInfo = GetDlgItem(hwnd, IDC_STATIC_INFO);
			//EN_ - Edit notification (Уведомление)
			if (HIWORD(wParam) == EN_CHANGE)
			{
				//BYTE = 8 bit;		CHAR
				//WORD = 2 Bytes (16 bit);	SHORT
				//DWORD (Double Word - Двойное слоово) = 4 Bytes (32 bit)	INT
				//QWORD (Quad Word - Учетверенное слово) = 8 Bytes (64 bit)	LONG LONG
				//TBYTE (Ten Bytes - Десять Байт) = 80 bit;
				//DQWORD (Double Quad Word - Двойное учетверенное слово) = 128 bit;
				DWORD dw_address;
				SendMessage(hIPaddress, IPM_GETADDRESS, 0, (LPARAM)&dw_address);
				INT first = FIRST_IPADDRESS(dw_address);
				INT second = SECOND_IPADDRESS(dw_address);
				INT third = THIRD_IPADDRESS(dw_address);
				INT fourth = FOURTH_IPADDRESS(dw_address);

				sprintf_s(sz_info, SIZE, "Info:\nFirst: %i, Second: %i, Third: %i, Forth: %i", first, second, third, fourth);
				SendMessage(hStaticInfo, WM_SETTEXT, 0, (LPARAM)sz_info);
			}
		}
		break;
		case IDOK: MessageBox(hwnd, "Была нажата кнопка OK", "Info", MB_OK | MB_ICONINFORMATION); break;
			//	MB_OK | MB_ICONINFORMATION - MB_OK or MB_ICONINFORMATION
			// || - логическое 'OR'
			// |  - побитовое  'OR'
		case IDCANCEL: EndDialog(hwnd, 0); break;
		}
		break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
		break;
	}
	return FALSE;
}