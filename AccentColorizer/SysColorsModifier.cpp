#include "SysColorsModifier.h"
#include "ColorHelper.h"
#include "AccentColorHelper.h"
#include <cmath>

double g_hslEnhancedAccentHL2{};

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
	rgb_t rgbVal{};
	hsl_t hslVal{};

	for (int i = 0; i < nSysElements; i++)
	{
		dwCurrentColor = GetSysColor(aSysElements[i]);

		rgbVal = {
			(double)GetRValue(dwCurrentColor),
			(double)GetGValue(dwCurrentColor),
			(double)GetBValue(dwCurrentColor)
		};
		hslVal = rgb2hsl(rgbVal);

		// While this is a straight up copy of the bitmap colorization, at least it works properly... old code is below.

		g_hslEnhancedAccentHL2 = (g_hslDefaultAccent.l * 255.0) - g_hslAccent.l;

		hslVal.h = g_hslDefaultAccent.h;
		if (hslVal.l >= 128 && hslVal.l <= 254) {
			hslVal.s = (double)hslVal.s * (double)(1 / (double)g_oldhslAccentS) * (double)g_hslDefaultAccent.s / ((1.0 - (hslVal.l / 255.0)) / (hslVal.l / 255.0));
		}
		else hslVal.s = (double)hslVal.s * (double)(1 / (double)g_oldhslAccentS) * (double)g_hslDefaultAccent.s;

		if (hslVal.l > (g_oldhslEnhancedAccentL)) {
			if (g_oldhslAccentL < g_hslAccent.l && g_oldhslEnhancedAccentL > 107) {
				hslVal.l = hslVal.l + ((g_hslAccent.l - g_oldhslAccentL + (0.000042 * (200 + g_oldhslAccentL) * ((hslVal.l - g_oldhslEnhancedAccentL) * g_oldhslAccentL))) * (pow(1 - ((hslVal.l - g_oldhslEnhancedAccentL) / 255.0), 2.0)) * hslVal.s);
			}
			else hslVal.l = hslVal.l + ((g_hslAccent.l - g_oldhslAccentL) * (pow(1 - ((hslVal.l - g_oldhslEnhancedAccentL) / 255.0), 2.0)) * hslVal.s);
		}
		else hslVal.l = hslVal.l - ((g_oldhslAccentL - g_hslAccent.l) * hslVal.s);

		if (hslVal.l > g_hslEnhancedAccentHL2) {
			hslVal.h = g_hslAccent.h + 0.5 * ((g_hslLightAccentH - g_hslAccent.h) * ((hslVal.l - g_hslEnhancedAccentHL2) / (255.0 - g_hslEnhancedAccentHL2)));
		}
		else if (hslVal.l <= g_hslEnhancedAccentHL2) {
			hslVal.h = g_hslAccent.h + 0.5 * ((g_hslDarkAccentH - g_hslAccent.h) * ((g_hslEnhancedAccentHL2 - hslVal.l) / g_hslEnhancedAccentHL2));
		}

		if (hslVal.l >= 128 && hslVal.l <= 254) {
			hslVal.s = (double)hslVal.s * (double)g_hslAccent.s * ((1.0 - (hslVal.l / 255.0)) / (hslVal.l / 255.0));
		}
		else hslVal.s = (double)hslVal.s * (double)g_hslAccent.s;

		rgbVal = hsl2rgb(hslVal);

		aNewColors[i] = RGB(rgbVal.r, rgbVal.g, rgbVal.b);
		
	}

	SetSysColors(nSysElements, aSysElements, aNewColors);

	// old code

	/*hslVal.h = g_hslDefaultAccent.h;
	if (hslVal.l >= 128 && hslVal.l <= 254) {
		hslVal.s = (double)hslVal.s * (double)(1 / (double)g_oldhslAccentS) * (double)g_hslDefaultAccent.s / ((1.0 - (hslVal.l / 255.0)) / (hslVal.l / 255.0));
	}
	else hslVal.s = (double)hslVal.s * (double)(1 / (double)g_oldhslAccentS) * (double)g_hslDefaultAccent.s;

	hslVal.l = hslVal.l - (g_oldhslAccentL - g_hslAccent.l  - (3.6 * (g_hslDefaultAccent.l - (g_hslAccent.l / 255)))) * (1 - (hslVal.l / 255.0) ) * hslVal.s;

	hslVal.h = g_hslAccent.h;

	if (hslVal.l >= 128 && hslVal.l <= 254) {
		hslVal.s = (double)hslVal.s * (double)g_hslAccent.s * ((1.0 - (hslVal.l / 255.0)) / (hslVal.l / 255.0));
	}
	else hslVal.s = (double)hslVal.s * (double)g_hslAccent.s;

	rgbVal = hsl2rgb(hslVal);*/


	// code for changing highlighttext to black when highlight is too bright. doesn't work good enough.

	/*rgbVal = {
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