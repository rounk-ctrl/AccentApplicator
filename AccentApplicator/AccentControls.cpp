#include "AccentControls.h"

void SetValues(int** r, int** g, int** b, int** a, COLORREF color)
{
	**r = GetRValue(color);
	**g = GetGValue(color);
	**b = GetBValue(color);
}

void Accent_Button(int* r, int* g, int* b, int* a)
{
	// PBS_HOT, PBS_DEFAULTED, PBS_DEFAULTED_ANIMATING outline
	if (*r == 0 && *g == 120 && *b == 215)
	{
		SetValues(&r, &g, &b, 0, accent);
	}
	// PBS_HOT
	else if (*r == 206 && *g == 229 && *b == 247)
	{
		SetValues(&r, &g, &b, 0, accentLight3);
	}
	// single pixel in top left of PBS_HOT
	else if (*r == 229 && *g == 241 && *b == 251)
	{
		SetValues(&r, &g, &b, 0, accentLight3);
	}
	// PBS_PRESSED outline
	else if (*r == 0 && *g == 84 && *b == 153)
	{
		SetValues(&r, &g, &b, 0, accentDark1);
	}
	// PBS_PRESSED
	else if (*r == 204 && *g == 228 && *b == 247)
	{
		SetValues(&r, &g, &b, 0, accentLight2);
	}
}

void Accent_CheckBox(int* r, int* g, int* b, int* a)
{
	// outline and some pixels on hot checkbox states
	if (*r == 0 && *g == 120 && *b == 215)
	{
		SetValues(&r, &g, &b, 0, accent);
	}
	// outline and some pixels on pressed checkbox states
	else if (*r == 0 && *g == 84 && *b == 153)
	{
		SetValues(&r, &g, &b, 0, accentDark1);
	}
	// some pixels on hot checkbox states
	else if (*r == 35 && *g == 130 && *b == 217)
	{
		SetValues(&r, &g, &b, 0, accent);
	}
	// some pixels on hot checkbox states
	else if (*r == 83 && *g == 150 && *b == 223)
	{
		SetValues(&r, &g, &b, 0, accentLight1);
	}
	// some pixels on hot checkbox states
	else if (*r == 134 && *g == 178 && *b == 230)
	{
		SetValues(&r, &g, &b, 0, accentLight2);
	}
	else if (*r == 119 && *g == 169 && *b == 228)
	{
		SetValues(&r, &g, &b, 0, accentLight2);
	}
	else if (*r == 188 && *g == 211 && *b == 240)
	{
		SetValues(&r, &g, &b, 0, accentLight3);
	}
	else if (*r == 36 && *g == 131 && *b == 218)
	{
		SetValues(&r, &g, &b, 0, accent);
	}
	else if (*r == 84 && *g == 151 && *b == 223)
	{
		SetValues(&r, &g, &b, 0, accentLight1);
	}
	else if (*r == 176 && *g == 203 && *b == 238)
	{
		SetValues(&r, &g, &b, 0, accentLight3);
	}
	else if (*r == 66 && *g == 142 && *b == 221)
	{
		SetValues(&r, &g, &b, 0, accentLight1);
	}
	else if (*r == 51 && *g == 147 && *b == 223)
	{
		SetValues(&r, &g, &b, 0, accentLight1);
	}
	else if (*r == 184 && *g == 208 && *b == 240)
	{
		SetValues(&r, &g, &b, 0, accentLight3);
	}
	// pressed background
	else if (*r == 204 && *g == 228 && *b == 247)
	{
		SetValues(&r, &g, &b, 0, accentLight3);
	}
	else if (*r == 64 && *g == 118 && *b == 173)
	{
		SetValues(&r, &g, &b, 0, accentLight1);
	}
	else if (*r == 25 && *g == 96 && *b == 159)
	{
		SetValues(&r, &g, &b, 0, accent);
	}
	else if (*r == 106 && *g == 148 && *b == 191)
	{
		SetValues(&r, &g, &b, 0, accentLight2);
	}
	else if (*r == 150 && *g == 182 && *b == 215)
	{
		SetValues(&r, &g, &b, 0, accentLight2);
	}
	else if (*r == 93 && *g == 138 && *b == 185)
	{
		SetValues(&r, &g, &b, 0, accentLight1);
	}
	else if (*r == 178 && *g == 206 && *b == 231)
	{
		SetValues(&r, &g, &b, 0, accentLight3);
	}
	else if (*r == 196 && *g == 221 && *b == 242)
	{
		SetValues(&r, &g, &b, 0, accentLight3);
	}
	else if (*r == 27 && *g == 96 && *b == 160)
	{
		SetValues(&r, &g, &b, 0, accent);
	}
	else if (*r == 65 && *g == 119 && *b == 173)
	{
		SetValues(&r, &g, &b, 0, accentLight1);
	}
	else if (*r == 140 && *g == 174 && *b == 209)
	{
		SetValues(&r, &g, &b, 0, accentLight2);
	}
	else if (*r == 51 && *g == 109 && *b == 167)
	{
		SetValues(&r, &g, &b, 0, accent);
	}
	else if (*r == 146 && *g == 179 && *b == 213)
	{
		SetValues(&r, &g, &b, 0, accentLight3);
	}
	else if (*r == 233 && *g == 240 && *b == 250)
	{
		SetValues(&r, &g, &b, 0, accentLight3);
	}
	else if (*r == 176 && *g == 205 && *b == 230)
	{
		SetValues(&r, &g, &b, 0, accentLight3);
	}
	else if (*r == 186 && *g == 213 && *b == 236)
	{
		SetValues(&r, &g, &b, 0, accentLight3);
	}
}

void Accent_Tab(int* r, int* g, int* b, int* a)
{
	if (*r == 216 && *g == 234 && *b == 249)
	{
		SetValues(&r, &g, &b, 0, accentLight3);
	}
	else if (*r == 0 && *g == 120 && *b == 215)
	{
		SetValues(&r, &g, &b, 0, accent);
	}
}

void Accent_Trackbar(int* r, int* g, int* b, int* a)
{
	if (*r == 0 && *g == 120 && *b == 215)
	{
		SetValues(&r, &g, &b, 0, accent);
	}
	else if (*r == 0 && *g == 122 && *b == 217)
	{
		SetValues(&r, &g, &b, 0, accent);
	}
	else if ((*r == 0 && *g == 60 && *b == 107) || (*r == 0 && *g == 60 && *b == 108))
	{
		SetValues(&r, &g, &b, 0, accentDark2);
	}
}

// spin is the worst
void Accent_Spin(int* r, int* g, int* b, int* a)
{
	if (*r == 86 && *g == 157 && *b == 229)
	{
		SetValues(&r, &g, &b, 0, accentLight1);
	}
	else if (
		(*r == 225 && *g == 239 && *b == 252) ||
		(*r == 227 && *g == 240 && *b == 252) ||
		(*r == 228 && *g == 241 && *b == 252) ||
		(*r == 230 && *g == 241 && *b == 252) ||
		(*r == 231 && *g == 242 && *b == 252) ||
		(*r == 232 && *g == 242 && *b == 252) ||
		(*r == 234 && *g == 243 && *b == 252) ||
		(*r == 235 && *g == 244 && *b == 252) ||
		(*r == 224 && *g == 238 && *b == 252) ||
		(*r == 223 && *g == 238 && *b == 252) ||
		(*r == 222 && *g == 237 && *b == 252) ||
		(*r == 221 && *g == 237 && *b == 252))
	{
		SetValues(&r, &g, &b, 0, accentLight3);
	}
	else if (
		(*r == 126 && *g == 180 && *b == 234) ||
		(*r == 218 && *g == 235 && *b == 252) ||
		(*r == 217 && *g == 235 && *b == 252) ||
		(*r == 215 && *g == 234 && *b == 252) ||
		(*r == 214 && *g == 233 && *b == 252) ||
		(*r == 212 && *g == 232 && *b == 252) ||
		(*r == 210 && *g == 231 && *b == 252) ||
		(*r == 208 && *g == 230 && *b == 252) ||
		(*r == 206 && *g == 229 && *b == 252) ||
		(*r == 204 && *g == 228 && *b == 252) ||
		(*r == 202 && *g == 227 && *b == 252) ||
		(*r == 200 && *g == 226 && *b == 252) ||
		(*r == 198 && *g == 225 && *b == 252) ||
		(*r == 197 && *g == 225 && *b == 252))
	{
		SetValues(&r, &g, &b, 0, accentLight2);
	}
}