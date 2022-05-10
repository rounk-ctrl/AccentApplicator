// AccentApplicator.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "AccentApplicator.h"
#include "AccentColorHelper.h"


#pragma region Pixel Color

inline int PixClr(int val)
{
    return val & 0xFFFFFF;
}

inline int PixR(BYTE* pPixel)
{
    return PixClr(pPixel[2]);
}
inline int PixG(BYTE* pPixel)
{
    return PixClr(pPixel[1]);
}
inline int PixB(BYTE* pPixel)
{
    return PixClr(pPixel[0]);
}
inline int PixA(BYTE* pPixel)
{
    return PixClr(pPixel[3]);
}

#pragma endregion

typedef struct {
    double r;       // a fraction between 0 and 1
    double g;       // a fraction between 0 and 1
    double b;       // a fraction between 0 and 1
} rgb;
typedef struct {
    double h;       // angle in degrees
    double s;       // a fraction between 0 and 1
    double v;       // a fraction between 0 and 1
} hsv;
static hsv   rgb2hsv(rgb in);
static rgb   hsv2rgb(hsv in);

hsv rgb2hsv(rgb in)
{
    hsv         out;
    double      min, max, delta;

    min = in.r < in.g ? in.r : in.g;
    min = min < in.b ? min : in.b;

    max = in.r > in.g ? in.r : in.g;
    max = max > in.b ? max : in.b;

    out.v = max;                                // v
    delta = max - min;
    if (delta < 0.00001)
    {
        out.s = 0;
        out.h = 0; // undefined, maybe nan?
        return out;
    }
    if (max > 0.0) { // NOTE: if Max is == 0, this divide would cause a crash
        out.s = (delta / max);                  // s
    }
    else {
        // if max is 0, then r = g = b = 0              
        // s = 0, h is undefined
        out.s = 0.0;
        out.h = NAN;                            // its now undefined
        return out;
    }
    if (in.r >= max)                           // > is bogus, just keeps compilor happy
        out.h = (in.g - in.b) / delta;        // between yellow & magenta
    else
        if (in.g >= max)
            out.h = 2.0 + (in.b - in.r) / delta;  // between cyan & yellow
        else
            out.h = 4.0 + (in.r - in.g) / delta;  // between magenta & cyan

    out.h *= 60.0;                              // degrees

    if (out.h < 0.0)
        out.h += 360.0;

    return out;
}

rgb hsv2rgb(hsv in)
{
    double      hh, p, q, t, ff;
    long        i;
    rgb         out;

    if (in.s <= 0.0) {       // < is bogus, just shuts up warnings
        out.r = in.v;
        out.g = in.v;
        out.b = in.v;
        return out;
    }
    hh = in.h;
    if (hh >= 360.0) hh = 0.0;
    hh /= 60.0;
    i = (long)hh;
    ff = hh - i;
    p = in.v * (1.0 - in.s);
    q = in.v * (1.0 - (in.s * ff));
    t = in.v * (1.0 - (in.s * (1.0 - ff)));

    switch (i) {
    case 0:
        out.r = in.v;
        out.g = t;
        out.b = p;
        break;
    case 1:
        out.r = q;
        out.g = in.v;
        out.b = p;
        break;
    case 2:
        out.r = p;
        out.g = in.v;
        out.b = t;
        break;

    case 3:
        out.r = p;
        out.g = q;
        out.b = in.v;
        break;
    case 4:
        out.r = t;
        out.g = p;
        out.b = in.v;
        break;
    case 5:
    default:
        out.r = in.v;
        out.g = p;
        out.b = q;
        break;
    }
    return out;
}

int RecolorizeBitmap(HBITMAP hbm)
{
    BITMAP bm;
    GetObject(hbm, sizeof(bm), &bm);

    if (!hbm || bm.bmBitsPixel != 32)
    {
        return FALSE;
    }

    BYTE* pBits = new BYTE[bm.bmWidth * bm.bmHeight * 4];
    GetBitmapBits(hbm, bm.bmWidth * bm.bmHeight * 4, pBits);

    for (int y = 0; y < bm.bmHeight; y++)
    {
        BYTE* pPixel = (BYTE*)pBits + bm.bmWidth * 4 * y;

        for (int x = 0; x < bm.bmWidth; x++)
        {
            int r = PixR(pPixel); // [2]
            int g = PixG(pPixel); // [1]
            int b = PixB(pPixel); // [0]
            int a = PixA(pPixel); // [3]

            if ((r == 0 && g == 120 && b == 215) || (r == 0 && g == 84 && b == 153))
            {
                // Main Blue Color for Buttons, Comboboxes, etc.
                pPixel[2] = GetRValue(accent);
                pPixel[1] = GetGValue(accent);
                pPixel[0] = GetBValue(accent);
            }
            else if (r == 229 && g == 241 && b == 251)
            {
                // Hovered Button (DARK BLUE)
                pPixel[2] = GetRValue(accentLight3);
                pPixel[1] = GetGValue(accentLight3);
                pPixel[0] = GetBValue(accentLight3);
            }
            else if (r == 204 && g == 228 && b == 247)
            {
                // Hovered Button (DARK BLUE)
                pPixel[2] = GetRValue(accentLight2);
                pPixel[1] = GetGValue(accentLight2);
                pPixel[0] = GetBValue(accentLight2);
            }
            else if (r == 216 && g == 234 && b == 249)
            {
                // Tab (LIGHT BLUE)
                pPixel[2] = GetRValue(accentLight3);
                pPixel[1] = GetGValue(accentLight3);
                pPixel[0] = GetBValue(accentLight3);
            }
            else if ((r == 0 && g == 56 && b == 102) || (r == 0 && g == 28 && b == 51))
            {
                // Toolbar Item / Item Corner (VERY LIGHT BLUE)
                pPixel[2] = GetRValue(accentLight3);
                pPixel[1] = GetGValue(accentLight3);
                pPixel[0] = GetBValue(accentLight3);
            }
            else if ((r == 0 && g == 27 && b == 50) || (r == 0 && g == 14 && b == 26))
            {
                // Explorer Item / Inactive Explorer Item Hover (VERY LIGHT BLUE)
                rgb rg;
                rg.r = GetRValue(accentLight3);
                rg.g = GetGValue(accentLight3);
                rg.b = GetBValue(accentLight3);
                hsv oee = rgb2hsv(rg);
                oee.s = 0.175;
                rgb newval = hsv2rgb(oee);
                pPixel[2] = newval.r;
                pPixel[1] = newval.g;
                pPixel[0] = newval.b;
            }
            else if (r == 217 && g == 235 && b == 249)
            {
                // Items View Header
                pPixel[2] = GetRValue(accentLight3);
                pPixel[1] = GetGValue(accentLight3);
                pPixel[0] = GetBValue(accentLight3);
            }
            else if (r == 188 && g == 220 && b == 244)
            {
                // Items View Header
                pPixel[2] = GetRValue(accentLight3);
                pPixel[1] = GetGValue(accentLight3);
                pPixel[0] = GetBValue(accentLight3);
            }
            else if (r == 35 && g == 130 && b == 217)
            {
                pPixel[2] = GetRValue(accent);
                pPixel[1] = GetGValue(accent);
                pPixel[0] = GetBValue(accent);
            }
            else if (r == 83 && g == 150 && b == 223)
            {
                pPixel[2] = GetRValue(accentLight1);
                pPixel[1] = GetGValue(accentLight1);
                pPixel[0] = GetBValue(accentLight1);
            }
            else if (r == 119 && g == 169 && b == 228)
            {
                pPixel[2] = GetRValue(accentLight1);
                pPixel[1] = GetGValue(accentLight1);
                pPixel[0] = GetBValue(accentLight1);
            }
            else if (r == 134 && g == 178 && b == 230)
            {
                pPixel[2] = GetRValue(accentLight2);
                pPixel[1] = GetGValue(accentLight2);
                pPixel[0] = GetBValue(accentLight2);
            }
            else if (r == 188 && g == 211 && b == 240)
            {
                pPixel[2] = GetRValue(accentLight3);
                pPixel[1] = GetGValue(accentLight3);
                pPixel[0] = GetBValue(accentLight3);
            }
            else if (r == 223 && g == 233 && b == 248)
            {
                pPixel[2] = GetRValue(accentLight3);
                pPixel[1] = GetGValue(accentLight3);
                pPixel[0] = GetBValue(accentLight3);
            }
            else if (r == 25 && g == 96 && b == 159)
            {
                pPixel[2] = GetRValue(accent);
                pPixel[1] = GetGValue(accent);
                pPixel[0] = GetBValue(accent);
            }
            else if (r == 64 && g == 118 && b == 173)
            {
                pPixel[2] = GetRValue(accentLight1);
                pPixel[1] = GetGValue(accentLight1);
                pPixel[0] = GetBValue(accentLight1);
            }
            else if (r == 93 && g == 138 && b == 185)
            {
                pPixel[2] = GetRValue(accentLight1);
                pPixel[1] = GetGValue(accentLight1);
                pPixel[0] = GetBValue(accentLight1);
            }
            else if (r == 106 && g == 148 && b == 191)
            {
                pPixel[2] = GetRValue(accentLight2);
                pPixel[1] = GetGValue(accentLight2);
                pPixel[0] = GetBValue(accentLight2);
            }
            else if (r == 150 && g == 182 && b == 215)
            {
                pPixel[2] = GetRValue(accentLight2);
                pPixel[1] = GetGValue(accentLight2);
                pPixel[0] = GetBValue(accentLight2);
            }
            else if (r == 178 && g == 206 && b == 231)
            {
                pPixel[2] = GetRValue(accentLight2);
                pPixel[1] = GetGValue(accentLight2);
                pPixel[0] = GetBValue(accentLight2);
            }
            else if (r == 196 && g == 221 && b == 242)
            {
                pPixel[2] = GetRValue(accentLight2);
                pPixel[1] = GetGValue(accentLight2);
                pPixel[0] = GetBValue(accentLight2);
            }
            //pPixel[3] = 1;
            pPixel += 4;
        }
    }
    SetBitmapBits(hbm, bm.bmWidth * bm.bmHeight * 4, pBits);
    delete[] pBits;
    return TRUE;
}
int ModifyStyle(LPCWSTR pszClassList, int iPartId, int iStateId, int iPropId)
{
    HBITMAP hBitmap;

    HTHEME hTheme = OpenThemeData(GetForegroundWindow(), pszClassList);
    GetThemeBitmap(hTheme, iPartId, iStateId, iPropId, GBF_DIRECT, &hBitmap);
    CloseThemeData(hTheme);

    return RecolorizeBitmap(hBitmap);
}


void ModifyStyles()
{
    int i,j;
    ModifyStyle(VSCLASS_BUTTON, BP_RADIOBUTTON, 0, 3);
    ModifyStyle(VSCLASS_BUTTON, BP_CHECKBOX, 0, 3);
    ModifyStyle(VSCLASS_BUTTON, BP_PUSHBUTTON, 0, TMT_DIBDATA);
    for (i = CP_DROPDOWNBUTTON; i <= CP_DROPDOWNBUTTONLEFT; i++)
    {
        ModifyStyle(VSCLASS_COMBOBOX, i, 0, TMT_DIBDATA);
    }
    for (i = EP_EDITBORDER_NOSCROLL; i <= EP_EDITBORDER_HVSCROLL; i++)
    {
        ModifyStyle(VSCLASS_EDIT, i, 0, TMT_DIBDATA);
    }
    for (i = TABP_TABITEM; i <= TABP_AEROWIZARDBODY; i++)
    {
        ModifyStyle(VSCLASS_TAB, i, 0, TMT_DIBDATA);
    }
    for (i = TKP_THUMB; i <= TKP_THUMBRIGHT; i++)
    {
        ModifyStyle(VSCLASS_TRACKBAR, i, 0, TMT_DIBDATA);
    }
    ModifyStyle(VSCLASS_HEADERSTYLE, HP_HEADERITEM, 0, 2);
    for (i = LBCP_BORDER_HSCROLL; i <= LBCP_ITEM; i++)
    {
        ModifyStyle(VSCLASS_LISTBOX, i, 0, TMT_DIBDATA);
    }
    for (i = TP_BUTTON; i <= TP_SPLITBUTTONDROPDOWN; i++)
    {
        ModifyStyle(VSCLASS_TOOLBAR, i, 0, TMT_DIBDATA);
    }
    for (i = SPNP_UP; i <= SPNP_DOWNHORZ; i++)
    {
        ModifyStyle(VSCLASS_SPIN, i, 0, TMT_DIBDATA);
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
const int size = 5;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    InitAccentColors();

    ModifyStyles();

    int aElements[size] =
    {
        COLOR_ACTIVECAPTION,
        COLOR_GRADIENTACTIVECAPTION,
        COLOR_HIGHLIGHT,
        COLOR_HOTLIGHT,
        COLOR_MENUHILIGHT
    };
    DWORD aOldColors[size];
    DWORD aNewColors[size];

    for (int i = 0; i < size; i++)
    {
        aOldColors[i] = GetSysColor(aElements[i]);
        aNewColors[i] = RGB(GetRValue(accent), GetGValue(accent), GetBValue(accent));
    }

    SetSysColors(size, aElements, aNewColors);

    return 0;
}
