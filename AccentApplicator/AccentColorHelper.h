#pragma once
#include "framework.h"

extern COLORREF accent;
extern COLORREF accentLight1;
extern COLORREF accentLight2;
extern COLORREF accentLight3;

extern COLORREF accentDark1;
extern COLORREF accentDark2;
extern COLORREF accentDark3;

extern COLORREF oldAccent;
extern COLORREF oldAccentLight1;
extern COLORREF oldAccentLight2;
extern COLORREF oldAccentLight3;

extern COLORREF oldAccentDark1;
extern COLORREF oldAccentDark2;
extern COLORREF oldAccentDark3;

void UpdateAccentColors();
void SaveCurrentAccentColors();
