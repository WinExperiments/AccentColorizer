#pragma once
#include "framework.h"
#include "ColorHelper.h"

extern COLORREF g_dwAccent;
//
extern hsl_t g_hslAccent;
extern hsl_t g_hslDefaultAccent;
//
extern double g_balance1hslAccentS;
extern double g_balance2hslAccentS;
//
extern double g_oldhslAccentL;
extern double g_oldhslAccentS;
//
extern int accentColorChanges;

bool UpdateAccentColor();
