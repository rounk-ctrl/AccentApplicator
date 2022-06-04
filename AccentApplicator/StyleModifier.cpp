#include "StyleModifier.h"
#include "BitmapHelper.h"
#include "ColorHelper.h"
#include "AccentColorHelper.h"

void StandardBitmapHandler(int* r, int* g, int* b, int* a) {
    rgb rgbOriginal = { *r, *g, *b };
    rgb rgbAccent = { GetRValue(accent), GetGValue(accent), GetBValue(accent) };

    hsv hsvOriginal = rgb2hsv(rgbOriginal);
    hsv hsvAccent = rgb2hsv(rgbAccent);

    hsvOriginal.h = hsvAccent.h;

    rgb rgbNew = hsv2rgb(hsvOriginal);

    *r = rgbNew.r;
    *g = rgbNew.g;
    *b = rgbNew.b;
}

int ModifyStyle(LPCWSTR pszClassList, int iPartId, int iStateId, int iPropId)
{
    HBITMAP hBitmap;

    HTHEME hTheme = OpenThemeData(GetForegroundWindow(), pszClassList);
    GetThemeBitmap(hTheme, iPartId, iStateId, iPropId, GBF_DIRECT, &hBitmap);
    CloseThemeData(hTheme);

    return RecolorizeBitmap(hBitmap, StandardBitmapHandler);
}

void ModifyStyles() {
    int i;

    ModifyStyle(VSCLASS_BUTTON, BP_PUSHBUTTON, 0, TMT_DIBDATA);
    ModifyStyle(VSCLASS_BUTTON, BP_CHECKBOX, 0, 3);
    for (i = CP_DROPDOWNBUTTON; i <= CP_DROPDOWNBUTTONLEFT; i++)
    {
        ModifyStyle(VSCLASS_COMBOBOX, i, 0, TMT_DIBDATA);
    }
    for (i = EP_EDITBORDER_NOSCROLL; i <= EP_EDITBORDER_HVSCROLL; i++)
    {
        ModifyStyle(VSCLASS_EDIT, i, 0, TMT_DIBDATA);
    }
    for (i = TABP_TABITEM; i <= TABP_TOPTABITEMBOTHEDGE; i++)
    {
        ModifyStyle(VSCLASS_TAB, i, 0, TMT_DIBDATA);
    }
    for (i = TKP_THUMB; i <= TKP_THUMBRIGHT; i++)
    {
        ModifyStyle(VSCLASS_TRACKBAR, i, 0, 2);
        ModifyStyle(VSCLASS_TRACKBAR, i, 0, 3);
    }
    for (i = LBCP_BORDER_HSCROLL; i <= LBCP_ITEM; i++)
    {
        ModifyStyle(VSCLASS_LISTBOX, i, 0, TMT_DIBDATA);
    }
    for (i = SPNP_UP; i <= SPNP_DOWNHORZ; i++)
    {
        ModifyStyle(VSCLASS_SPIN, i, 0, TMT_DIBDATA);
    }
    ModifyStyle(VSCLASS_BUTTON, BP_RADIOBUTTON, 0, 3);
    ModifyStyle(VSCLASS_HEADERSTYLE, HP_HEADERITEM, 0, 2);
    for (i = TP_BUTTON; i <= TP_SPLITBUTTONDROPDOWN; i++)
    {
        ModifyStyle(VSCLASS_TOOLBAR, i, 0, TMT_DIBDATA);
    }
    ModifyStyle(L"BreadcrumbBar", 1, 0, TMT_DIBDATA);
    for (i = 2; i <= 6; i++)
    {
        ModifyStyle(L"Explorer::TreeView", 1, i, TMT_DIBDATA);
    }
    for (i = 2; i <= 6; i++)
    {
        ModifyStyle(L"Explorer::ListView", 1, i, TMT_DIBDATA);
    }
    ModifyStyle(L"PreviewPane", 1, 1, TMT_DIBDATA); // Windows Vista/7 Explorer Bottom Details Panel

    ModifyStyle(L"CommandModule", 1, 0, TMT_DIBDATA); // Windows 7 Explorer Command Bar
    for (i = 3; i <= 5; i++)
    {
        ModifyStyle(L"CommandModule", i, 0, TMT_DIBDATA);
    }
    ModifyStyle(L"ItemsView::Header", 1, 0, TMT_DIBDATA); // Explorer File Groups Header
    for (i = 1; i <= 2; i++)
    {
        ModifyStyle(L"ItemsView", 3, i, TMT_DIBDATA);
    }
    for (i = 1; i <= 16; i++)
    {
        ModifyStyle(L"ItemsView::ListView", 6, i, TMT_DIBDATA); // Explorer File Selection
    }

    for (i = 1; i <= 4; i++)
    {
        ModifyStyle(L"BB::Toolbar", i, 0, TMT_DIBDATA); // Explorer Breadcrumbs Highlight color
    }
}