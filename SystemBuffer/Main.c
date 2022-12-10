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
	//ClipboardInputText(buffer);
	//ClipboardProhibitionOutputText();
	//ClipboardProhibitionOutputText();
	ClipboardDigits();

}

void ClipboardInputText(LPWSTR forTextBuffer)
{
	DWORD len;
	HANDLE hMem;
	len = wcslen(forTextBuffer) + 1;

	hMem = GlobalAlloc(GMEM_MOVEABLE, len * sizeof(WCHAR));
	memcpy(GlobalLock(hMem), forTextBuffer, len * sizeof(WCHAR));
	GlobalUnlock(hMem);
	OpenClipboard(NULL);
	EmptyClipboard();
	SetClipboardData(CF_UNICODETEXT, hMem);
	CloseClipboard();
}


LPWSTR ClipboardOutputText()
{
	LPWSTR message;
	OpenClipboard(NULL);
	HANDLE hClipboardData = GetClipboardData(CF_UNICODETEXT);
	message = (LPWSTR)GlobalLock(hClipboardData);
	GlobalUnlock(hClipboardData);
	CloseClipboard(hClipboardData);
	return message;
}


void ClipboardProhibitionOutputText()
{
	while (TRUE)
	{
		LPWSTR buffer = ClipboardOutputText();

		if (*buffer != 0)
		{
			MessageBox(NULL, L"����� ����������", L"������", MB_OK);
			ClipboardInputText(L"");
		}
		Sleep(1000);
	}
}

void ClipboardDigits()
{
	LPWSTR buffer = ClipboardOutputText();
	BOOL check = FALSE;
	for (int i = 0; buffer[i] != '\0'; i++)
	{
		if (isdigit(buffer[i]) != 0)
		{
			LPWSTR symbolsDigit;
			symbolsDigit = calloc(7, sizeof(WCHAR));

			int digit = atoi(buffer);
			check = TRUE;
			switch (digit)
			{
				case 0:
					symbolsDigit = L"����";
					break;
				case 1:
					symbolsDigit = L"����";
					break;
				case 2:
					symbolsDigit = L"���";
					break;
				case 3:
					symbolsDigit = L"���";
					break;
				case 4:
					symbolsDigit = L"������";
					break;
				case 5:
					symbolsDigit = L"����";
					break;
				case 6:
					symbolsDigit = L"�����";
					break;
				case 7:
					symbolsDigit = L"����";
					break;
				case 8:
					symbolsDigit = L"������";
					break;
				case 9:
					symbolsDigit = L"������";
					break;
			}
			swprintf(buffer, 15, L"%d - %s", digit, symbolsDigit);
		}
		if (check)
		{
			break;
		}
			
	}
	if (check)
	{
		MessageBox(NULL, buffer, L"����� ����� ������", MB_OK);

	}
	else
	{
		MessageBox(NULL, buffer, L"���� �� ����������", MB_OK);
	}
}