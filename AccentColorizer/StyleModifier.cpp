#include "StyleModifier.h"
#include "BitmapHelper.h"
#include "StyleColorHelper.h"
#include "ColorHelper.h"
#include "AccentColorHelper.h"
#include "SystemHelper.h"
#include <cmath>

bool g_bColorizeMenus;
bool g_bColorizeProgressBar;
double brightnessMultiplier;

HTHEME hTheme = nullptr;

void StandardBitmapPixelHandler(int& r, int& g, int& b, int& a)
{
	rgb_t rgbVal = { r, g, b };
	hsl_t hslVal = rgb2hsl(rgbVal);

	hslVal.h = g_hslDefaultAccent.h;
	hslVal.s = hslVal.s * (1.0 / g_oldhslAccentS) * g_hslDefaultAccent.s;

	hslVal.l = hslVal.l - (g_oldhslAccentL * hslVal.s * (a / 255.0)) + (g_hslAccent.l * hslVal.s * (a / 255.0)) - (g_hslDefaultAccent.l * hslVal.s);

	hslVal.h = g_hslAccent.h;
	hslVal.s = hslVal.s * g_hslAccent.s;

	rgbVal = hsl2rgb(hslVal);

	r = rgbVal.r;
	g = rgbVal.g;
	b = rgbVal.b;
}

void StandardColorHandler(int& r, int& g, int& b) // dummy code
{
	rgb_t rgbVal = { 255, 128, 128 };
	hsl_t hslVal = rgb2hsl(rgbVal);

	hslVal.h = g_hslAccent.h;
	hslVal.s = hslVal.s * (1 / g_oldhslAccentS) * g_hslAccent.s;

	rgbVal = hsl2rgb(hslVal);
}


void SetCurrentTheme(LPCWSTR pszClassList)
{
	if (hTheme)
	{
		CloseThemeData(hTheme);
	}

	hTheme = OpenThemeData(NULL, pszClassList);
}

bool ModifyStyle(int iPartId, int iStateId, int iPropId)
{
	HBITMAP hBitmap;
	GetThemeBitmap(hTheme, iPartId, iStateId, iPropId, GBF_DIRECT, &hBitmap);
	return IterateBitmap(hBitmap, StandardBitmapPixelHandler);
}

bool ModifyColorStyle(int iPartId, int iStateId, int iPropId) // dummy code
{
	COLORREF hColor;
	GetThemeColor(hTheme, iPartId, iStateId, iPropId, &hColor);
	return IterateColor(hColor, StandardColorHandler);
}

///
/// At first glance, such refactoring looks useless,
/// premature and counterproductive, but
/// it speeded up the colorization four times,
/// i.e. tenths of a second
///
void ModifyStyles()
{
	int i, j, k;
	//
	
	SetCurrentTheme(L"CommandModule"); // dummy code
	//
	ModifyColorStyle(3, 2, TMT_TEXTCOLOR);

	SetCurrentTheme(VSCLASS_BUTTON);
	//
	ModifyStyle(BP_PUSHBUTTON, 0, 0);
	ModifyStyle(BP_COMMANDLINK, 0, 0);
	for (j = 1; j <= 7; j++)
	{
		ModifyStyle(BP_RADIOBUTTON, 0, j);
		ModifyStyle(BP_CHECKBOX, 0, j);
		ModifyStyle(BP_GROUPBOX, 0, j);
		ModifyStyle(BP_COMMANDLINKGLYPH, 0, j);
	}


	SetCurrentTheme(VSCLASS_COMBOBOX);
	//
	for (i = CP_DROPDOWNBUTTON; i <= CP_DROPDOWNBUTTONLEFT; i++)
	{
		for (k = 1; k <= 7; k++)
		{
			ModifyStyle(i, 0, k);
		}
	}


	SetCurrentTheme(VSCLASS_EDIT);
	//
	for (i = EP_EDITBORDER_NOSCROLL; i <= EP_EDITBORDER_HVSCROLL; i++)
	{
		for (k = 1; k <= 7; k++)
		{
			ModifyStyle(i, 0, k);
		}
	}


	SetCurrentTheme(VSCLASS_TAB);
	//
	for (i = TABP_TABITEM; i <= TABP_TOPTABITEMBOTHEDGE; i++)
	{
		for (k = 1; k <= 7; k++)
		{
			ModifyStyle(i, 0, k);
		}
	}


	SetCurrentTheme(VSCLASS_TRACKBAR);
	//
	for (i = TKP_THUMB; i <= TKP_THUMBRIGHT; i++)
	{
		for (j = 1; j <= 7; j++)
		{
			ModifyStyle(i, 0, j);
		}
	}


	SetCurrentTheme(VSCLASS_LISTBOX);
	//
	for (i = LBCP_BORDER_HSCROLL; i <= LBCP_ITEM; i++)
	{
		ModifyStyle(i, 0, 0);
	}


	SetCurrentTheme(VSCLASS_SPIN);
	//
	for (i = SPNP_UP; i <= SPNP_DOWNHORZ; i++)
	{
		ModifyStyle(i, 0, 0);
	}


	SetCurrentTheme(VSCLASS_HEADERSTYLE);
	//
	for (k = 1; k <= 7; k++)
	{
		ModifyStyle(HP_HEADERITEM, 0, k);
	}


	/////////////////////////////////////////////////////
	SetCurrentTheme(L"Toolbar");
	//
	for (i = TP_BUTTON; i <= TP_SPLITBUTTONDROPDOWN; i++)
	{
		for (k = 1; k <= 7; k++)
		{
			ModifyStyle(i, 1, k);
		}
	}

	SetCurrentTheme(L"DarkMode::Toolbar");
	//
	for (i = TP_BUTTON; i <= TP_SPLITBUTTONDROPDOWN; i++)
	{
		for (k = 1; k <= 7; k++)
		{
			ModifyStyle(i, 1, k);
		}
	}


	SetCurrentTheme(L"ExplorerMenu::Toolbar");
	//
	for (i = TP_BUTTON; i <= TP_SPLITBUTTONDROPDOWN; i++)
	{
		for (k = 1; k <= 7; k++)
		{
			ModifyStyle(i, 1, k);
		}
	}


	SetCurrentTheme(L"Alternate::Toolbar");
	//
	for (i = TP_BUTTON; i <= TP_SPLITBUTTONDROPDOWN; i++)
	{
		for (k = 1; k <= 7; k++)
		{
			ModifyStyle(i, 1, k);
		}
	}


	SetCurrentTheme(L"Communications::Toolbar");
	//
	for (i = TP_BUTTON; i <= TP_SPLITBUTTONDROPDOWN; i++)
	{
		for (k = 1; k <= 7; k++)
		{
			ModifyStyle(i, 1, k);
		}
	}


	SetCurrentTheme(L"InfoPaneToolbar::Toolbar");
	//
	for (i = TP_BUTTON; i <= TP_SPLITBUTTONDROPDOWN; i++)
	{
		for (k = 1; k <= 7; k++)
		{
			ModifyStyle(i, 1, k);
		}
	}

	SetCurrentTheme(L"Placesbar::Toolbar");
	//
	for (k = 1; k <= 7; k++)
	{
		ModifyStyle(1, 0, k);
	}

	SetCurrentTheme(L"TrayNotify::Toolbar");
	//
	ModifyStyle(TP_BUTTON, 1, 0);

	/////////////////////////////////////////////////////

	SetCurrentTheme(L"BreadcrumbBar");
	//
	ModifyStyle(1, 0, 0);

	SetCurrentTheme(L"BrowserTab");
	//
	for (j = 1; j <= 3; j++)
	{
		ModifyStyle(1, 0, j);
	}

	SetCurrentTheme(L"BrowserTabBar");
	//
	ModifyStyle(0, 0, 0);

	SetCurrentTheme(L"Explorer::TreeView");
	//
	for (i = 1; i <= 4; i++)
	{
		for (j = 1; j <= 6; j++)
		{
			for (k = 1; k <= 7; k++)
			{
				ModifyStyle(i, j, k);
			}
		}
	}

	SetCurrentTheme(L"DarkMode_Explorer::TreeView");
	//
	for (i = 1; i <= 4; i++)
	{
		for (j = 1; j <= 6; j++)
		{
			for (k = 1; k <= 7; k++)
			{
				ModifyStyle(i, j, k);
			}
		}
	}


	SetCurrentTheme(L"Explorer::ListView");
	//
	for (i = 1; i <= 10; i++)
	{
		for (j = 1; j <= 16; j++)
		{
			ModifyStyle(i, j, 0);
		}
	}


	SetCurrentTheme(L"PreviewPane");
	//
	for (i = 1; i <= 4; i++)
	{
		ModifyStyle(i, 0, 0); // Windows Vista/7 Explorer Bottom Details Panel
	}

	SetCurrentTheme(L"DarkMode::PreviewPane");
	//
	for (i = 1; i <= 4; i++)
	{
		ModifyStyle(i, 0, 0); // Windows Vista/7 Explorer Bottom Details Panel
	}

	SetCurrentTheme(L"CommandModule");
	//
	for (i = 1; i <= 11; i++)
	{
		if (i == 8) continue;
		ModifyStyle(i, 0, 0);
		ModifyStyle(i, 1, 0);
	}
	SetCurrentTheme(L"DarkMode::CommandModule");
	//
	for (i = 1; i <= 11; i++)
	{
		if (i == 8) continue;
		ModifyStyle(i, 0, 0);
		ModifyStyle(i, 1, 0);
	}


	SetCurrentTheme(L"ItemsView");
	//
	for (i = 2; i <= 6; i++)
	{
		for (k = 1; k <= 7; k++)
		{
			ModifyStyle(i, 0, k);
			ModifyStyle(3, 1, k);
			ModifyStyle(3, 2, k);
		}
	}
	for (j = 1; j <= 4; j++)
	{
		for (k = 1; k <= 7; k++)
		{
			ModifyStyle(1, j, k);
		}
	}

	SetCurrentTheme(L"DarkMode::ItemsView");
	//
	for (i = 2; i <= 6; i++)
	{
		for (k = 1; k <= 7; k++)
		{
			ModifyStyle(i, 0, k);
			ModifyStyle(3, 1, k);
			ModifyStyle(3, 2, k);
		}
	}
	for (j = 1; j <= 4; j++)
	{
		for (k = 1; k <= 7; k++)
		{
			ModifyStyle(1, j, k);
		}
	}


	SetCurrentTheme(L"ItemsView::Header");
	//
	for (i = 1; i <= 7; i++)
	{
		for (j = 1; j <= 12; j++)
		{
			for (k = 1; k <= 7; k++)
			{
				ModifyStyle(i, j, k);
			}
		}
	}


	/////////////////////////////////////////////////////
	SetCurrentTheme(L"ItemsView::ListView");
	//
	for (i = 1; i <= 16; i++)
	{
		for (j = 1; j <= 16; j++)
		{
			for (k = 1; k <= 7; k++)
			{
				ModifyStyle(i, j, k); // Explorer File Selection
			}
		}
	}
	for (i = 8; i <= 9; i++)
	{
		for (j = 1; j <= 7; j++)
		{
			for (k = 1; k <= 7; k++)
			{
				ModifyStyle(i, j, k);
			}
		}
	}

	SetCurrentTheme(L"DarkMode_ItemsView::ListView");
	//
	for (i = 1; i <= 16; i++)
	{
		for (j = 1; j <= 16; j++)
		{
			for (k = 1; k <= 7; k++)
			{
				ModifyStyle(i, j, k); // Explorer File Selection
			}
		}
	}
	for (i = 8; i <= 9; i++)
	{
		for (j = 1; j <= 7; j++)
		{
			for (k = 1; k <= 7; k++)
			{
				ModifyStyle(i, j, k);
			}
		}
	}


	SetCurrentTheme(L"ListView");
	//
	for (i = 6; i <= 9; i++)
	{
		for (j = 1; j <= 7; j++)
		{
			for (k = 0; k <= 7; k++)
			{
				ModifyStyle(i, j, k);
			}
		}
	}


	SetCurrentTheme(L"Explorer::ListView");
	//
	for (i = 8; i <= 9; i++)
	{
		for (j = 1; j <= 7; j++)
		{
			for (k = 1; k <= 7; k++)
			{
				ModifyStyle(i, j, k);
			}
		}
	}

	/////////////////////////////////////////////////////


	SetCurrentTheme(L"BB::Toolbar");
	//
	for (i = 1; i <= 4; i++)
	{
		ModifyStyle(i, 0, 0); // Explorer Breadcrumbs Highlight color
	}

	SetCurrentTheme(L"DarkMode_BBComposited::Toolbar");
	//
	for (i = 1; i <= 4; i++)
	{
		ModifyStyle(i, 0, 0); // Explorer Breadcrumbs Highlight color
	}

	SetCurrentTheme(L"MaxInactiveBB::Toolbar");
	//
	for (i = 1; i <= 4; i++)
	{
		ModifyStyle(i, 0, 0); // Explorer Breadcrumbs Highlight color
	}

	SetCurrentTheme(L"MaxInactiveBBComposited::Toolbar");
	//
	for (i = 1; i <= 4; i++)
	{
		ModifyStyle(i, 0, 0); // Explorer Breadcrumbs Highlight color
	}

	SetCurrentTheme(L"ExplorerMenu::Toolbar");
	//
	for (i = 1; i <= 4; i++)
	{
		ModifyStyle(i, 0, 0);
	}

	/////////////////////////////////////////////////////
	SetCurrentTheme(L"Go::Toolbar");
	//
	ModifyStyle(1, 1, 0);


	SetCurrentTheme(L"InactiveGo::Toolbar");
	//
	ModifyStyle(1, 1, 0);
	/////////////////////////////////////////////////////


	SetCurrentTheme(L"MaxGo::Toolbar");
	//
	ModifyStyle(1, 1, 0);

	SetCurrentTheme(L"MaxInactiveGo::Toolbar");
	//
	ModifyStyle(1, 1, 0);


	/////////////////////////////////////////////////////
	SetCurrentTheme(L"LVPopup::Toolbar");
	//
	ModifyStyle(1, 1, 0);


	SetCurrentTheme(L"LVPopupBottom::Toolbar");
	//
	ModifyStyle(1, 1, 0);
	/////////////////////////////////////////////////////



	/////////////////////////////////////////////////////
	SetCurrentTheme(L"InactiveBB::Toolbar");
	//
	ModifyStyle(3, 1, 0);
	for (j = 1; j <= 6; j++)
	{
		ModifyStyle(4, j, j);
		ModifyStyle(4, j, 0);
	}


	SetCurrentTheme(L"InactiveBBComposited::Toolbar");
	//
	for (j = 1; j <= 6; j++)
	{
		ModifyStyle(4, j, j);
		ModifyStyle(4, j, 0);
	}
	/////////////////////////////////////////////////////


	SetCurrentTheme(L"DragDrop");
	//
	for (k = 1; k <= 7; k++)
	{
		ModifyStyle(1, 0, k);
		ModifyStyle(2, 0, k);
		ModifyStyle(3, 0, k);
		ModifyStyle(4, 0, k);
		ModifyStyle(7, 0, k);
		ModifyStyle(8, 0, k);
	}

	SetCurrentTheme(L"DropListControl");
	//
	ModifyStyle(1, 0, 0);

	SetCurrentTheme(L"Header");
	//
	ModifyStyle(1, 0, 0);


	SetCurrentTheme(L"PAUSE");
	//
	for (j = 1; j <= 7; j++)
	{
		ModifyStyle(1, 0, j);
	}


	SetCurrentTheme(VSCLASS_MONTHCAL); // Explorer / Legacy Shell Date Picker
	//
	for (i = 10; i <= 11; i++)
	{
		ModifyStyle(i, 0, 0);
		ModifyStyle(i, 1, 0);
	}
	for (j = 1; j <= 6; j++)
	{
		ModifyStyle(MC_GRIDCELLBACKGROUND, j, 0);
	}


	SetCurrentTheme(L"DatePicker");
	//
	for (i = 2; i <= 3; i++)
	{
		for (j = 0; j <= 1; j++)
		{
			ModifyStyle(i, j, 1);
			for (k = 1; k <= 7; k++)
			{
				ModifyStyle(i, j, k);
			}
		}
	}


	/////////////////////////////////////////////////////
	SetCurrentTheme(L"Rebar");
	//
	ModifyStyle(6, 0, 0);
	for (i = 4; i <= 6; i++) {
		ModifyStyle(i, 1, 0);
		ModifyStyle(i, 1, 0);
	}

	SetCurrentTheme(L"Default::Rebar");
	//
	ModifyStyle(6, 0, 0);

	SetCurrentTheme(L"ExplorerBar::Rebar");
	//
	ModifyStyle(6, 0, 0);


	SetCurrentTheme(L"Navbar::Rebar");
	//
	ModifyStyle(6, 0, 0);
	ModifyStyle(6, 1, 0);


	SetCurrentTheme(L"InactiveNavbar::Rebar");
	//
	ModifyStyle(6, 0, 0);
	ModifyStyle(6, 1, 0);
	/////////////////////////////////////////////////////


	SetCurrentTheme(L"Desktop::ListView");
	//
	for (j = 0; j <= 6; j++)
	{
		ModifyStyle(1, j, 0); // Desktop icons
	}

	/////////////////////////////////////////////////////
	SetCurrentTheme(L"TreeView");
	//
	for (i = 0; i <= 10; i++)
	{
		for (j = 0; j <= 10; j++)
		{
			for (k = 0; k <= 10; k++)
			{
				ModifyStyle(i, j, k);
			}
		}
	}

	SetCurrentTheme(L"ProperTree");
	//
	ModifyStyle(1, 0, 0);


	SetCurrentTheme(L"Navigation");
	//
	for (i = 0; i <= 10; i++)
	{
		for (j = 0; j <= 10; j++)
		{
			for (k = 0; k <= 10; k++)
			{
				ModifyStyle(i, j, k);
			}
		}
	}

	SetCurrentTheme(L"DarkMode::Navigation");
	//
	for (i = 0; i <= 10; i++)
	{
		for (j = 0; j <= 10; j++)
		{
			for (k = 0; k <= 10; k++)
			{
				ModifyStyle(i, j, k);
			}
		}
	}
	/////////////////////////////////////////////////////


	/////////////////////////////////////////////////////
	SetCurrentTheme(L"CopyClose");
	//
	for (j = 1; j <= 7; j++)
	{
		for (k = 1; k <= 7; k++)
		{
			ModifyStyle(1, j, k);
		}
	}


	SetCurrentTheme(L"SearchBox");
	//
	for (i = 1; i <= 3; i++)
	{
		for (j = 1; j <= 7; j++)
		{
			ModifyStyle(i, j, k);
		}
	}

	SetCurrentTheme(L"DarkMode::SearchBox");
	//
	for (i = 1; i <= 3; i++)
	{
		for (j = 1; j <= 7; j++)
		{
			ModifyStyle(i, j, k);
		}
	}

	SetCurrentTheme(L"HelpSearchBox");
	//
	for (k = 1; k <= 7; k++)
	{
		ModifyStyle(1, 0, k);
	}


	SetCurrentTheme(L"SearchBoxComposited::SearchBox");
	//
	for (j = 1; j <= 7; j++)
	{
		for (k = 1; k <= 7; k++)
		{
			ModifyStyle(2, j, k);
		}
	}


	SetCurrentTheme(L"SearchButton::Toolbar");
	//
	for (j = 1; j <= 7; j++)
	{
		for (k = 1; k <= 7; k++)
		{
			ModifyStyle(3, j, k);
			ModifyStyle(4, j, k);
		}
	}
	/////////////////////////////////////////////////////


	SetCurrentTheme(L"TaskbandExtendedUI");	// Taskbar Thumbnail Media Controls
	//
	for (i = (g_winver >= WIN_10 ? 6 : 8); i <= (g_winver >= WIN_10 ? 9 : 11); i++)
	{
		for (j = 1; j <= 4; j++)
		{
			for (k = 1; k <= 7; k++)
			{
				ModifyStyle(i, j, k);
			}
		}
	}

	SetCurrentTheme(L"TaskbandExtendedUILight::TaskbandExtendedUI");	// Light Mode Taskbar Thumbnail Media Controls
	//
	for (i = (g_winver >= WIN_10 ? 6 : 8); i <= (g_winver >= WIN_10 ? 9 : 11); i++)
	{
		for (j = 1; j <= 4; j++)
		{
			for (k = 1; k <= 7; k++)
			{
				ModifyStyle(i, j, k);
			}
		}
	}

	if (g_bColorizeMenus)
	{
		SetCurrentTheme(L"Menu");
		//
		for (k = 1; k <= 7; k++)
		{
			ModifyStyle(27, 0, k);
			ModifyStyle(26, 0, k);
			ModifyStyle(16, 0, k);
			ModifyStyle(15, 0, k);
			ModifyStyle(14, 0, k);
			ModifyStyle(13, 0, k);
			ModifyStyle(12, 0, k);
			ModifyStyle(10, 0, k);
			ModifyStyle(9, 0, k);
			ModifyStyle(8, 0, k);
			ModifyStyle(7, 0, k);
		}
		// Menu Checkbox
		for (j = 0; j <= 7; j++)
		{
			for (k = 0; k <= 7; k++)
			{
				ModifyStyle(11, j, k);
			}
		}

		SetCurrentTheme(L"DarkMode::Menu");
		//
		for (k = 1; k <= 7; k++)
		{
			ModifyStyle(27, 0, k);
			ModifyStyle(26, 0, k);
			ModifyStyle(16, 0, k);
			ModifyStyle(15, 0, k);
			ModifyStyle(14, 0, k);
			ModifyStyle(13, 0, k);
			ModifyStyle(12, 0, k);
			ModifyStyle(10, 0, k);
			ModifyStyle(9, 0, k);
			ModifyStyle(8, 0, k);
			ModifyStyle(7, 0, k);
		}
		// Menu Checkbox
		for (j = 0; j <= 7; j++)
		{
			for (k = 0; k <= 7; k++)
			{
				ModifyStyle(11, j, k);
			}
		}

		SetCurrentTheme(L"ImmersiveStart::Menu");
		//
		for (k = 1; k <= 7; k++)
		{
			ModifyStyle(27, 0, k);
			ModifyStyle(26, 0, k);
			ModifyStyle(15, 0, k);
			ModifyStyle(14, 0, k);
		}

		SetCurrentTheme(L"ImmersiveStartDark::Menu");
		//
		for (k = 1; k <= 7; k++)
		{
			ModifyStyle(27, 0, k);
			ModifyStyle(26, 0, k);
			ModifyStyle(15, 0, k);
			ModifyStyle(14, 0, k);
		}

		SetCurrentTheme(L"DarkMode_ImmersiveStart::Menu");
		//
		for (k = 1; k <= 7; k++)
		{
			ModifyStyle(27, 0, k);
			ModifyStyle(26, 0, k);
			ModifyStyle(15, 0, k);
			ModifyStyle(14, 0, k);
		}

		SetCurrentTheme(L"LightMode_ImmersiveStart::Menu");
		//
		for (k = 1; k <= 7; k++)
		{
			ModifyStyle(27, 0, k);
			ModifyStyle(26, 0, k);
			ModifyStyle(15, 0, k);
			ModifyStyle(14, 0, k);
		}

		SetCurrentTheme(L"Communications::Menu");
		//
		for (k = 1; k <= 7; k++)
		{
			ModifyStyle(27, 0, k);
			ModifyStyle(26, 0, k);
			ModifyStyle(15, 0, k);
			ModifyStyle(14, 0, k);
			ModifyStyle(13, 0, k);
			ModifyStyle(10, 0, k);
			ModifyStyle(9, 0, k);
		}

		SetCurrentTheme(L"Media::Menu");
		//
		for (k = 1; k <= 7; k++)
		{
			ModifyStyle(27, 0, k);
			ModifyStyle(26, 0, k);
			ModifyStyle(15, 0, k);
			ModifyStyle(14, 0, k);
			ModifyStyle(13, 0, k);
			ModifyStyle(10, 0, k);
			ModifyStyle(9, 0, k);
		}
	}

	if (g_bColorizeProgressBar)
	{
		SetCurrentTheme(L"Progress");
		//
		for (k = 1; k <= 7; k++)
		{
			ModifyStyle(5, 4, k);
			ModifyStyle(6, 4, k);
		}
		for (i = 3; i <= 12; i++)
		{
			for (k = 1; k <= 7; k++)
			{
				ModifyStyle(i, 1, k);
			}
		}


		SetCurrentTheme(L"Indeterminate::Progress");
		//
		for (i = 3; i <= 10; i++)
		{
			for (k = 1; k <= 7; k++)
			{
				ModifyStyle(i, 1, k);
			}
		}


		SetCurrentTheme(L"AB::AddressBand");
		//
		for (k = 1; k <= 7; k++)
		{
			ModifyStyle(1, 4, k);
		}

		SetCurrentTheme(L"DarkMode_ABComposited::AddressBand");
		//
		for (k = 1; k <= 7; k++)
		{
			ModifyStyle(i, 4, k);
		}
	}

	/** Tweaks for legacy components **/

	SetCurrentTheme(L"Communications::Rebar");
	//
	ModifyStyle(6, 0, 0);

	SetCurrentTheme(L"Media::Rebar");
	//
	ModifyStyle(6, 0, 0);


	SetCurrentTheme(L"StartPanel");
	//
	ModifyStyle(1, 1, 0);


	SetCurrentTheme(L"StartMenu::Toolbar");
	//
	ModifyStyle(10, 1, 0);
	ModifyStyle(12, 1, 0);


	/////////////////////////////////////////////////////
	SetCurrentTheme(L"StartPanelPriv");
	//
	for (i = 1; i <= 38; i++)
	{
		ModifyStyle(i, 0, 0);
	}


	SetCurrentTheme(L"StartPanelComposited::StartPanelPriv");
	//
	for (i = 1; i <= 38; i++)
	{
		ModifyStyle(i, 0, 0);
	}
	/////////////////////////////////////////////////////

	SetCurrentTheme(L"TaskDialog");
	//
	for (i = 1; i <= 8; i++)
	{
		for (k = 1; k <= 7; k++)
		{
			ModifyStyle(13, i, k);
		}
	}


	/////////////////////////////////////////////////////
	SetCurrentTheme(L"Header");
	//
	for (i = 1; i <= 7; i++)
	{
		for (j = 1; j <= 12; j++)
		{
			for (k = 1; k <= 7; k++)
			{
				ModifyStyle(i, j, k);
			}
		}
	}

	/////////////////////////////////////////////////////


	SetCurrentTheme(L"ScrollBar");
	//
	for (i = 1; i <= 10; i++)
	{
		ModifyStyle(i, 0, 0);
	}

	//
	// Aero Basic
	//


	SetCurrentTheme(L"TaskBar2::TaskBar");
	//
	for (i = 1; i <= 8; i++)
	{
		ModifyStyle(i, 0, 0);
	}


	SetCurrentTheme(L"AltTab");
	//
	for (i = 1; i <= 11; i++)
	{
		for (k = 1; k <= 7; k++)
		{
			ModifyStyle(i, 0, k);
		}
	}

	SetCurrentTheme(L"Tooltip");
	//
	for (i = 1; i <= 6; i++)
	{
		ModifyStyle(i, 0, 0);
	}


	SetCurrentTheme(L"BasicMenuMode::TaskbandExtendedUI");
	//
	ModifyStyle(1, 0, 0);

	SetCurrentTheme(L"Flyout");
	//
	ModifyStyle(5, 0, 0);
	ModifyStyle(6, 0, 0);

	SetCurrentTheme(L"Window");
	//
	for (i = 1; i <= 17; i++)
	{
		ModifyStyle(i, 0, 0);
	}
	for (i = 21; i <= 23; i++)
	{
		ModifyStyle(i, 0, 0);
	}

	//
	// Metro UI custom controls
	SetCurrentTheme(L"DirectUI::Button");
	//
	for (k = 1; k <= 7; k++)
	{
		ModifyStyle(1, 0, k);
		ModifyStyle(2, 0, k);
		ModifyStyle(3, 0, k);
		ModifyStyle(6, 0, k);
	}

	SetCurrentTheme(L"DirectUIDark::Button");
	//
	for (k = 1; k <= 7; k++)
	{
		ModifyStyle(2, 0, k);
		ModifyStyle(3, 0, k);
		ModifyStyle(6, 0, k);
	}

	SetCurrentTheme(L"DirectUILight::Button");
	//
	for (k = 1; k <= 7; k++)
	{
		ModifyStyle(2, 0, k);
		ModifyStyle(3, 0, k);
		ModifyStyle(6, 0, k);
	}

	SetCurrentTheme(L"PillTab::Tab");
	//
	for (k = 1; k <= 7; k++)
	{
		ModifyStyle(1, 0, k);
	}

	SetCurrentTheme(L"PillTabHighDPI::Tab");
	//
	for (k = 1; k <= 7; k++)
	{
		ModifyStyle(1, 0, k);
	}

	SetCurrentTheme(L"TouchSlider::TrackBar");
	//
	for (i = 1; i <= 6; i++)
	{
		for (j = 1; j <= 5; j++)
		{
			for (k = 1; k <= 7; k++)
			{
				ModifyStyle(i, j, k);
			}
		}
	}

	CloseThemeData(hTheme);
	hTheme = nullptr;
}
