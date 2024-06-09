#pragma once
#include "framework.h"
#include <set>

extern std::set<HBITMAP> handledBitmaps;

typedef void (*BitmapPixelHandler)(int& r, int& g, int& b, int& a);

bool IterateBitmap(HBITMAP hbm, BitmapPixelHandler handler);