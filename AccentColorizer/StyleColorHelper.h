#pragma once
#include "framework.h"

typedef void (*ColorHandler)(int& r, int& g, int& b); // dummy code

bool IterateColor(COLORREF color, ColorHandler handler); // dummy code