#include "AccentColorHelper.h"
#include "ColorHelper.h"
#include <cmath>

COLORREF g_dwAccent{};
hsl_t g_hslAccent{};
hsl_t g_hslDefaultAccent{};
double g_oldhslAccentS{};
double g_balance1hslAccentS{};
double g_balance2hslAccentS{};
double g_oldhslAccentL{};
int g_hslLightAccentH{};
int g_hslDarkAccentH{};
double g_hslEnhancedAccentL{};
double g_oldhslEnhancedAccentL{};

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

	if (accentColorChanges >= 2) {
		g_oldhslAccentS = g_hslAccent.s;
		if (g_oldhslAccentS <= 0.08) {
			g_oldhslAccentS = 0.08;
		}
	}
	else g_oldhslAccentS = 1;

	if (accentColorChanges >= 2) {
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
	if (g_hslAccent.h >= 0 && g_hslAccent.h < 125) {
		g_hslLightAccentH = 60;
	}
	else if (g_hslAccent.h >= 125 && g_hslAccent.h < 150) {
		g_hslLightAccentH = 120;
	}
	else if (g_hslAccent.h >= 150 && g_hslAccent.h < 240) {
		g_hslLightAccentH = 180;
	}
	else if (g_hslAccent.h >= 240 && g_hslAccent.h < 345) {
		g_hslLightAccentH = 300;
	}
	else if (g_hslAccent.h >= 345 && g_hslAccent.h < 360) {
		g_hslLightAccentH = 420;
	}
	if (g_hslAccent.h >= 0 && g_hslAccent.h < 60) {
		g_hslDarkAccentH = 0;
	}
	else if (g_hslAccent.h >= 60 && g_hslAccent.h < 180) {
		g_hslDarkAccentH = 120;
	}
	else if (g_hslAccent.h >= 180 && g_hslAccent.h < 300) {
		g_hslDarkAccentH = 240;
	}
	else if (g_hslAccent.h >= 300 && g_hslAccent.h < 360) {
		g_hslDarkAccentH = 360;
	}

	g_dwAccent = dwAccent;
	if ((double)GetRValue(dwAccent) == (double)GetGValue(dwAccent) && (double)GetGValue(dwAccent) == (double)GetBValue(dwAccent)) {
		if (accentColorChanges == 1) {
			g_hslAccent.s = 0.5;
		}
		else g_hslAccent.s = 0.0801;
	}
	else {
		g_hslAccent.s = pow(double(rgb2hsl({
			(double)GetRValue(dwAccent) / 254.999999999,
			(double)GetGValue(dwAccent) / 254.999999999,
			(double)GetBValue(dwAccent) / 254.999999999 }).s), double(0.95));
	}


	g_balance1hslAccentS = g_hslAccent.s;
	g_balance2hslAccentS = (1 - g_hslAccent.s);

	g_hslDefaultAccent.h = 206.532;
	g_hslDefaultAccent.s = 1;
	g_hslDefaultAccent.l = (double)(rgb2hsl({
		(double)0 / 255,
		(double)120 / 255,
		(double)215 / 255 }).l);

	if (g_hslAccent.s < 0.08) {
		g_hslAccent.s = 0.08;
	}
	if (accentColorChanges >= 1) {
		if (g_hslAccent.s > 1) {
			g_hslAccent.s = g_balance1hslAccentS + g_balance2hslAccentS;
		}
	}

	if ((double)GetRValue(dwAccent) == (double)GetGValue(dwAccent) && (double)GetGValue(dwAccent) == (double)GetBValue(dwAccent)){
		if (accentColorChanges == 1) {
			g_hslAccent.l = 0.0;
		}
	}
	else {
		g_hslAccent.l = ((double)(rgb2hsl({
			(double)GetRValue(dwAccent) / 255,
			(double)GetGValue(dwAccent) / 255,
			(double)GetBValue(dwAccent) / 255 }).l) - (double)(rgb2hsl({
			(double)0 / 255,
			(double)110 / 255,
			(double)199 / 255 }).l)) * -255.0; // based on default accent color #0078D7 (RGB 0, 120, 215), which is slightly darkened for DWM.
	}
	g_hslAccent.l = g_hslAccent.l;
	g_oldhslEnhancedAccentL = (g_hslDefaultAccent.l * 255) - (g_oldhslAccentL);

	return true;
}