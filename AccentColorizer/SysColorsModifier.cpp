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


		hslVal.h = g_hslAccentH;
		hslVal.s = (double)hslVal.s * (double)g_hslAccentS;

		rgbVal = hsl2rgb(hslVal);

		aNewColors[i] = RGB(rgbVal.r, rgbVal.g, rgbVal.b);
	}

	SetSysColors(nSysElements, aSysElements, aNewColors);
}