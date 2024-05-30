#pragma once
#include "framework.h"

extern COLORREF g_dwAccent;
extern int g_hslAccentH;
extern double g_hslAccentS;
extern double g_oldhslAccentS;
extern double g_balance1hslAccentS;
extern double g_balance2hslAccentS;
extern double g_hslAccentL;
extern double g_oldhslAccentL;
extern double g_defaulthslAccentH;
extern double g_defaulthslAccentS;
extern double g_defaulthslAccentL;
extern int accentColorChanges;

bool UpdateAccentColor();
