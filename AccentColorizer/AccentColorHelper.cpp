#include "AccentColorHelper.h"
#include "ColorHelper.h"
#include <cmath>

COLORREF g_dwAccent;
//
hsl_t g_hslAccent;
hsl_t g_hslDefaultAccent;
//
double g_balance1hslAccentS;
double g_balance2hslAccentS;
//
double g_oldhslAccentL;
double g_oldhslAccentS;

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

	if (accentColorChanges >= 1) {
		g_oldhslAccentS = g_hslAccent.s;
		if (g_oldhslAccentS <= 0.0666) {
			g_oldhslAccentS = 0.0666;
		}
	}
	else g_oldhslAccentS = 1;

	if (accentColorChanges >= 1) {
		g_oldhslAccentL = g_hslAccent.l;
	}
	else g_oldhslAccentL = 0;

	g_dwAccent = dwAccent;
	if ((double)GetRValue(dwAccent) == (double)GetGValue(dwAccent) && (double)GetGValue(dwAccent) == (double)GetBValue(dwAccent)) {
		g_hslAccent.h = 210.0;
	}
	else {
		g_hslAccent.h = rgb2hsl({
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
		g_hslAccent.s = 0.0667;
	}
	else {
		g_hslAccent.s = pow(double(rgb2hsl({
			(double)GetRValue(dwAccent) / 254.999999999,
			(double)GetGValue(dwAccent) / 254.999999999,
			(double)GetBValue(dwAccent) / 254.999999999 }).s), double(0.85));
	}


	g_balance1hslAccentS = g_hslAccent.s;
	g_balance2hslAccentS = (1 - g_hslAccent.s);

	g_hslDefaultAccent.h = 207;
	g_hslDefaultAccent.s = 1;
	g_hslDefaultAccent.l = (double)(rgb2hsl({
		(double)0 / 254.999999999,
		(double)120 / 254.999999999,
		(double)215 / 254.999999999 }).l);

	if (g_hslAccent.s < 0.0666) {
		g_hslAccent.s = 0.0666;
	}
	if (accentColorChanges >= 1) {
		if (g_hslAccent.s > 1) {
			g_hslAccent.s = g_balance1hslAccentS + g_balance2hslAccentS;
		}
	}

	g_hslAccent.l = ((double)(rgb2hsl({
		(double)GetRValue(dwAccent) / 254.999999999,
		(double)GetGValue(dwAccent) / 254.999999999,
		(double)GetBValue(dwAccent) / 254.999999999 }).l) - 
					(double)(rgb2hsl({
		(double)0 / 254.999999999,
		(double)120 / 254.999999999,
		(double)215 / 254.999999999 }).l)) * -255; // based on default accent color #0078D7 (RGB 0, 120, 215)

	return true;
}