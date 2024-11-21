#include "AccentColorHelper.h"
#include "SysColorsModifier.h"
#include "StyleModifier.h"
#include "SettingsHelper.h"
#include "SystemHelper.h"
#include "BitmapHelper.h"

constexpr LPCWSTR szWindowClass = L"ACCENTCOLORIZER";
HANDLE hMutex;
int accentColorChanges = 0;

void ApplyAccentColorization()
{
	if (!UpdateAccentColor())
	{
		// Accent Colors have not been changed.
		// There's a bug in Windows 10 1809+ because of which
		// WM_DWMCOLORIZATIONCOLORCHANGED message is sent multiple times,
		// it also affects accent color changing performance in general.
		// Apparently it is fixed in Windows 11 version 22H2
		return;
	}
	ModifyStyles();
	ModifySysColors();
	handledBitmaps.clear();
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_DWMCOLORIZATIONCOLORCHANGED ||
		message == WM_THEMECHANGED || message == WM_DPICHANGED ||
		(message == WM_WTSSESSION_CHANGE && wParam == WTS_SESSION_UNLOCK)
		)
	{
		if (message != WM_DWMCOLORIZATIONCOLORCHANGED)
		{
			// We need to re-apply colorization completely because:
			//  a) DPI changed
			//  b) Visual Theme has been changed, and bitmaps were reset
			//  c) Another user was probably logged in, and we need to override the colors and bitmaps
			//  d) Device was turned on after sleep, and colors and bitmaps probably were reset
			g_dwAccent = NULL;
		}
		if (message == WM_THEMECHANGED) {
			accentColorChanges = 0; // IMPORTANT: While this works better on modern 22H2, it doesn't on early 22H2 unless the program is compiled in debug mode.
									// 23H2 is most likely working the same as modern 22H2, as they use the same base. Please test this on 24H2.
									// Updated 22H2 issue: Brightness change is not applied correctly if the color applied has brightness different from the original #0078D7. 
									// (Fixed on November 20, 2024 by adding line 45 (setting a hue value before returning the HSL struct) to ColorHelper.cpp.)
									// Early 22H2 issues: Colors are completely wrong (This could have been fixed after the November 20 code update.)
		}
		else if (message == WM_DWMCOLORIZATIONCOLORCHANGED || (message == WM_WTSSESSION_CHANGE && wParam == WTS_SESSION_UNLOCK) || message == WM_DPICHANGED) {
			accentColorChanges = 2 + accentColorChanges;
		}
		else {
			accentColorChanges = 0;
		}
		ApplyAccentColorization();
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	hMutex = CreateMutex(NULL, TRUE, szWindowClass);
	if (!hMutex || ERROR_ALREADY_EXISTS == GetLastError())
	{
		return 1;
	}

	DetectWindowsVersion();

	g_bColorizeMenus = IsMenuColorizationEnabled();
	g_bColorizeProgressBar = IsProgressBarColorizationEnabled();

	ApplyAccentColorization();
	if (g_winver < WIN_8)
	{
		g_dwAccent = NULL;
	}

	WNDCLASSEX wcex = {};
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.lpfnWndProc = WndProc;
	wcex.hInstance = hInstance;
	wcex.lpszClassName = szWindowClass;
	if (!RegisterClassEx(&wcex))
	{
		return 2;
	}

	HWND hWnd = CreateWindowEx(0, szWindowClass, nullptr, 0, 0, 0, 0, 0, nullptr, NULL, NULL, NULL);
	WTSRegisterSessionNotification(hWnd, NOTIFY_FOR_THIS_SESSION);

	if (g_winver < WIN_8)
	{
		SendMessageTimeout(hWnd, WM_DWMCOLORIZATIONCOLORCHANGED, g_dwAccent, g_dwAccent, SMTO_NORMAL, 2000, nullptr);
	}

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	ReleaseMutex(hMutex);
	CloseHandle(hMutex);

	return (int)msg.wParam;
}