#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <tchar.h>
#include <CommCtrl.h>
extern "C"{
#include "person.h"
}

const char g_szClassName[] = "ProgBase2";

#define ID_LABEL 131
#define ID_LB    132
#define HSTATICKEY 144
#define HSTATICVALUE 145

// Step 4: the Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
	)
{
	WNDCLASSEX wc;
	HWND hwnd;
	MSG Msg;

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = (TCHAR*)(g_szClassName);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, (TCHAR*)"Window Registration Failed!", (TCHAR*)"Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		(TCHAR*)g_szClassName,
		(TCHAR*)"ProgBase2 | Windows",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 425, 200,
		NULL, NULL, hInstance, NULL);

	if (hwnd == NULL)
	{
		MessageBox(NULL, (TCHAR*)"Window Creation Failed!", (TCHAR*)"Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&Msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HINSTANCE hInstance = GetModuleHandle(NULL);
	static HWND hLabel, hStaticKey, hStaticValue, hWndList;
	static person_t person1 = NULL, person2 = NULL, person3 = NULL, person4 = NULL;
	switch (msg)
	{
	case WM_CREATE:
	{
		hLabel = CreateWindowEx(
			0,
			(TCHAR*)"STATIC",
			(TCHAR*)"List of persons",
			WS_CHILD | WS_VISIBLE,
			10, 10, 100, 26,
			hwnd, (HMENU)ID_LABEL, hInstance, NULL
			);
		hStaticKey = CreateWindowEx(0,
			WC_STATIC,
			"Name",
			WS_CHILD | WS_VISIBLE,
			220, 40, 170, 23,
			hwnd,
			(HMENU)HSTATICKEY,
			hInstance,
			NULL);
		hStaticValue = CreateWindowEx(0,
			WC_STATIC,
			"Value",
			WS_CHILD | WS_VISIBLE,
			220, 70, 170, 23,
			hwnd,
			(HMENU)HSTATICVALUE,
			hInstance,
			NULL);
		hWndList = CreateWindowW(
			L"listbox",
			L"Update timer",
			WS_VISIBLE | WS_CHILD | WS_VSCROLL | ES_AUTOVSCROLL | WS_BORDER | LBS_NOTIFY,
			10, 40, 185, 125,
			hwnd, (HMENU)ID_LB, NULL, NULL
			);

		person1 = person_new("Ivan", "Ivanov", 1995);
		person_insertToList(person1, hWndList);
		
		person2 = person_new("Petr", "Petrov", 1944);
		person_insertToList(person2, hWndList);

		person3 = person_new("Dmitriy", "Dmitrenko", 1986);
		person_insertToList(person3, hWndList);

		person4 = person_new("Maxim", "Maximov", 1954);
		person_insertToList(person4, hWndList);

	}
	break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam)) {
		case ID_LB: 
			switch (HIWORD(wParam))
			{
			case LBN_SELCHANGE: 
			{
				HWND hLabel = GetDlgItem(hwnd, ID_LABEL);
				HWND control = GetDlgItem(hwnd, ID_LB);

				char text[256];
				int count = SendMessage(control, LB_GETCOUNT, 0, 0);
				int iSelected = -1;

				for (int i = 0; i < count; i++)
				{
					if (SendMessage(control, LB_GETSEL, i, 0) > 0)
					{
						iSelected = i;
						char key[100] = "";
						SendMessage(control, LB_GETTEXT, (WPARAM)iSelected, (LPARAM)key);
						SetWindowText(hStaticKey, key);
						char * value = (char*)SendMessage(control, LB_GETITEMDATA, (WPARAM)iSelected, 0);
						SetWindowText(hStaticValue, value);
					}
				}
			}
			break;
			}
			break;
		}
	}
	break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		DestroyWindow(hStaticKey);
		DestroyWindow(hStaticValue);
		DestroyWindow(hWndList);
		DestroyWindow(hLabel);
		person_free(person1);
		person_free(person2);
		person_free(person3);
		person_free(person4);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}