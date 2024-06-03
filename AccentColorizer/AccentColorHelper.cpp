#include "AccentColorHelper.h"
#include "ColorHelper.h"
#include <cmath>

COLORREF g_dwAccent;
int g_hslAccentH;
double g_hslAccentS;
double g_oldhslAccentS;
double g_balance1hslAccentS;
double g_balance2hslAccentS;
double g_hslAccentL;
double g_oldhslAccentL;
double g_defaulthslAccentH;
double g_defaulthslAccentS;
double g_defaulthslAccentL;

bool UpdateAccentColor()
{
	COLORREF dwAccentRGB;
	BOOL bIsColorOpaque;

	DwmGetColorizationColor(&dwAccentRGB, &bIsColorOpaque);

	DWORD dwAccent = rgb2bgr(dwAccentRGB);

	if (g_dwAccent == dwAccent)
	{
		return false;
	}

	g_dwAccent = dwAccent;
	if (accentColorChanges >= 1) {
		g_oldhslAccentS = g_hslAccentS;
		if (g_oldhslAccentS <= 0.0666) {
			g_oldhslAccentS = 0.0666;
		}
	}
	else g_oldhslAccentS = 1;

	if (accentColorChanges >= 1) {
		g_oldhslAccentL = g_hslAccentL;
	}
	else g_oldhslAccentL = 0;

	g_dwAccent = dwAccent;
	if ((double)GetRValue(dwAccent) == (double)GetGValue(dwAccent) && (double)GetGValue(dwAccent) == (double)GetBValue(dwAccent)) {
		g_hslAccentH = 210.0;
	}
	else {
		g_hslAccentH = rgb2hsl({
			(double)GetRValue(dwAccent) / 255,
			(double)GetGValue(dwAccent) / 255,
			(double)GetBValue(dwAccent) / 255 }).h;
	}
	/* if (g_hslAccentH < 0.0) {
		g_hslAccentH += 360.0;
	}

	if (g_hslAccentH > 360.0) {
		g_hslAccentH -= 360.0;
	} */

	g_dwAccent = dwAccent;
	if ((double)GetRValue(dwAccent) == (double)GetGValue(dwAccent) && (double)GetGValue(dwAccent) == (double)GetBValue(dwAccent)) {
		g_hslAccentS = 0.0667;
	}
	else {
		g_hslAccentS = pow(double(rgb2hsl({
			(double)GetRValue(dwAccent) / 254.999999999,
			(double)GetGValue(dwAccent) / 254.999999999,
			(double)GetBValue(dwAccent) / 254.999999999 }).s), double(0.85));
	}


	g_balance1hslAccentS = g_hslAccentS;
	g_balance2hslAccentS = (1 - g_hslAccentS);

	g_defaulthslAccentH = 207;
	g_defaulthslAccentS = 1;
	g_defaulthslAccentL = (double)(rgb2hsl({
		(double)0 / 254.999999999,
		(double)120 / 254.999999999,
		(double)215 / 254.999999999 }).l);

	if (g_hslAccentS < 0.0666) {
		g_hslAccentS = 0.0666;
	}
	if (accentColorChanges >= 1) {
		if (g_hslAccentS > 1) {
			g_hslAccentS = g_balance1hslAccentS + g_balance2hslAccentS;
		}
	}

	g_hslAccentL = ((double)(rgb2hsl({
		(double)GetRValue(dwAccent) / 254.999999999,
		(double)GetGValue(dwAccent) / 254.999999999,
		(double)GetBValue(dwAccent) / 254.999999999 }).l) - 
					(double)(rgb2hsl({
		(double)0 / 254.999999999,
		(double)120 / 254.999999999,
		(double)215 / 254.999999999 }).l)) * -255; // based on default accent color #0078D7 (RGB 0, 120, 215)

	return true;
}