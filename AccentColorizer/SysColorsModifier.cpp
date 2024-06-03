#include "SysColorsModifier.h"
#include "ColorHelper.h"
#include "AccentColorHelper.h"

constexpr int aSysElements[] = {
	COLOR_ACTIVECAPTION,
	COLOR_GRADIENTACTIVECAPTION,
	COLOR_INACTIVECAPTION,
	COLOR_GRADIENTINACTIVECAPTION,
	COLOR_HIGHLIGHT,
	COLOR_HOTLIGHT,
	COLOR_MENUHILIGHT
};
constexpr size_t nSysElements = sizeof(aSysElements) / sizeof(*aSysElements);

constexpr int aSysElements2[] = {
	COLOR_HIGHLIGHTTEXT,
};
constexpr size_t nSysElements2 = sizeof(aSysElements2) / sizeof(*aSysElements2);

void ModifySysColors()
{
	DWORD aNewColors[nSysElements];

	COLORREF dwCurrentColor;
	rgb_t rgbVal;
	hsl_t hslVal;

	for (int i = 0; i < nSysElements; i++)
	{
		dwCurrentColor = GetSysColor(aSysElements[i]);

		rgbVal = {
			(double)GetRValue(dwCurrentColor),
			(double)GetGValue(dwCurrentColor),
			(double)GetBValue(dwCurrentColor)
		};
		hslVal = rgb2hsl(rgbVal);

		hslVal.h = g_defaulthslAccentH;
		hslVal.s = (double)hslVal.s * (double)(1 / (double)g_oldhslAccentS) * (double)g_defaulthslAccentS;

		hslVal.l = hslVal.l - (g_oldhslAccentL * hslVal.s) + (g_hslAccentL * hslVal.s) -  (g_defaulthslAccentL * hslVal.s);

		hslVal.h = g_hslAccentH;
		hslVal.s = (double)hslVal.s * (double)g_hslAccentS;



		rgbVal = hsl2rgb(hslVal);

		aNewColors[i] = RGB(rgbVal.r, rgbVal.g, rgbVal.b);
	}

	SetSysColors(nSysElements, aSysElements, aNewColors);

/*	rgbVal = {							// code for changing highlighttext to black when highlight is too bright. doesn't work good enough.
	(double)GetRValue(COLOR_HIGHLIGHT),
	(double)GetGValue(COLOR_HIGHLIGHT),
	(double)GetBValue(COLOR_HIGHLIGHT)
	};
	hslVal = rgb2hsl(rgbVal);

	hslVal.h = g_defaulthslAccentH;
	hslVal.s = (double)hslVal.s * (double)(1 / (double)g_oldhslAccentS) * (double)g_defaulthslAccentS;

	hslVal.l = hslVal.l - (g_oldhslAccentL * hslVal.s) + (g_hslAccentL * hslVal.s);

	hslVal.h = g_hslAccentH;
	hslVal.s = (double)hslVal.s * (double)g_hslAccentS;

	DWORD aNewColors2[nSysElements2];
	int i = 0;
		if (hslVal.h >= 120 && hslVal.h <= 180) {
			if (hslVal.l >= 120) {
				aNewColors2[i] = RGB(0, 0, 0);
			}
		}
		else if (hslVal.h >= 60 && hslVal.h < 120 || hslVal.h > 180 && hslVal.h <= 240) {
			if (hslVal.l >= 145) {
				aNewColors2[i] = RGB(0, 0, 0);
			}
		}
		else if (hslVal.h >= 0 && hslVal.h < 60 || hslVal.h > 240 && hslVal.h <= 360) {
			if (hslVal.l >= 170) {
				aNewColors2[i] = RGB(0, 0, 0);
			}
		}
		else if (hslVal.h >= 0 && hslVal.h <= 360) {
			if (hslVal.l >= 0) {
				aNewColors2[i] = RGB(255, 255, 255);
			}
		}
	SetSysColors(nSysElements2, aSysElements2, aNewColors2); */
}