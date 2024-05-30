#pragma once
#include "framework.h"
#include <iostream>
#include <vector>

using namespace std;
extern vector <HBITMAP> hBitmapList;

typedef void (*BitmapPixelHandler)(int& r, int& g, int& b, int& a);

bool IterateBitmap(HBITMAP hbm, BitmapPixelHandler handler);