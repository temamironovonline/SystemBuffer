#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>
#include <malloc.h>

void ClipboardInputText(LPWSTR);
LPWSTR ClipboardOutputText();
void ClipboardProhibitionOutputText();
void ClipboardDigits();

int main()
{
	LPWSTR buffer = L"Hello, world";
	/*lipboardInputText(buffer);
	ClipboardOutputText();
	ClipboardProhibitionOutputText();*/
	ClipboardDigits();

}

void ClipboardInputText(LPWSTR forTextBuffer)
{
	DWORD len;
	HANDLE hMem;
	len = wcslen(forTextBuffer) + 1;
	hMem = GlobalAlloc(GMEM_MOVEABLE, len * sizeof(LPWSTR));
	memcpy(GlobalLock(hMem), forTextBuffer, len * sizeof(LPWSTR*));
	GlobalUnlock(hMem);
	OpenClipboard(NULL);
	EmptyClipboard();
	SetClipboardData(CF_UNICODETEXT, hMem);
	CloseClipboard();
}


LPWSTR ClipboardOutputText()
{
	LPWSTR* message;
	OpenClipboard(NULL);
	HANDLE hClipboardData = GetClipboardData(CF_UNICODETEXT);
	message = (char*)GlobalLock(hClipboardData);
	GlobalUnlock(hClipboardData);
	CloseClipboard();
	return message;
}



void ClipboardProhibitionOutputText()
{
	while (TRUE)
	{
		char* buffer = ClipboardOutputText();

		if (*buffer != 0)
		{
			MessageBox(NULL, L"Буфер недоступен", L"Ошибка", MB_OK);
			ClipboardInputText(L"");
		}
		Sleep(1000);
	}
}

void ClipboardDigits()
{
	LPWSTR buffer;
	buffer = calloc(100, sizeof(LPWSTR));
	buffer = ClipboardOutputText();
	BOOL check = FALSE;
	LPWSTR* arraySymbols;
	LPWSTR symbolsDigit;
	int check1 = 0;
	symbolsDigit = calloc(7, sizeof(LPWSTR));

	for (int i = 0; buffer[i] != '\0'; i++)
	{
		if (isdigit(buffer[i]) != 0)
		{
			check++;
		}
	}

	check = TRUE;
	arraySymbols = calloc(check, sizeof(LPWSTR));

	for (int i = 0; i < check; i++)
	{
		arraySymbols[check] = calloc(10, sizeof(WCHAR));
	}

	int a = 0;
	for (int i = 0; buffer[i] != '\0'; i++)
	{
		if (isdigit(buffer[i]) != 0)
		{
			int digit = buffer[i]-'0';
			switch (digit)
			{
				case 0:
					arraySymbols[a,0] = L"ноль";
					break;
				case 1:
					arraySymbols[a,0] = L"один";
					break;
				case 2:
					arraySymbols[a,0] = L"два";
					break;
				case 3:
					arraySymbols[a,0] = L"три";
					break;
				case 4:
					arraySymbols[a,0] = L"четыре";
					break;
				case 5:
					arraySymbols[a,0] = L"пять";
					break;
				case 6:
					arraySymbols[a,0] = L"шесть";
					break;
				case 7:
					arraySymbols[a,0] = L"семь";
					break;
				case 8:
					arraySymbols[a,0] = L"восемь";
					break;
				case 9:
					arraySymbols[a,0] = L"девять";
					break;
				}
			MessageBox(NULL, arraySymbols[a, 0], L"awd", MB_OK);
			a++;
		}
		
	}
}