#include "Main.h"


void FogBrightenPalettes(hword BrightenIntensity)
{
	byte Weather = *(byte*)(FadeInfo2 + 16);
	if (GetFadeTypeByWeather(Weather) != 2) return; // only brighten if there is fog weather
	byte FadeState = *(byte*)(FadeInfo2 + 6);
	if (FadeState != 3) return; // don't brighten while fading
	hword BrightenColor = TintColor(RGB(28, 31, 28));
	int i;
	for (i = 16; i < 32; i++)
	{
		if (PaletteNeedsFogBrightening(i)) FadePalette(i * 16, 16, BrightenIntensity, BrightenColor);
	}
}

void FogBrightenAndFade(byte PalSlot, byte FadeIntensity, hword FadeColor)
{
	byte BrightenIntensity = AlphaBlendingCoeffA;
	hword BrightenColor = TintColor(RGB(28, 31, 28));
	hword Color;
	byte R, G, B;
	int i;
	for (i = 0; i < 16; i++)
	{
		Color = UnfadedPalettes[PalSlot].Colors[i];
		R = Red(Color);
		G = Green(Color);
		B = Blue(Color);

		R += (Red(BrightenColor) - R) *  BrightenIntensity / 16;
		G += (Green(BrightenColor) - G) *  BrightenIntensity / 16;
		B += (Blue(BrightenColor) - B) *  BrightenIntensity / 16;

		R += (Red(FadeColor) - R) *  FadeIntensity / 16;
		G += (Green(FadeColor) - G) *  FadeIntensity / 16;
		B += (Blue(FadeColor) - B) *  FadeIntensity / 16;

		Palettes[PalSlot].Colors[i] = RGB(R, G, B);
	}
}

byte PaletteNeedsFogBrightening(byte PalSlot) // hook at 0x7A748
{
	return PalRefs[PalSlot - 16].Type == PalTypeAnimation; // only brighten animations
}

void LoadCloudOrSandstormPalette(Palette *Pal) // hook at 0x7ABC0
{
	byte PalSlot;
	PalSlot = AddPalRef(PalTypeWeather, 0x1200);
	if (PalSlot == 0xFF) return;
	LoadOBJPalette(Pal, PalSlot * 16);
	TintOBJPalette(PalSlot);
	MaskPaletteIfFadingIn(PalSlot);
}

hword TintColor(hword Color)
{
	switch (ColorFilter)
	{
	case 1:
	case 3:
		TintGrayscale(&Color, 1);
		break;
	case 2:
		TintSepia(&Color, 1);
		break;
	}
	return Color;
}

byte GetDarkeningTypeBySlot(byte PalSlot) // replaces table at 0x3C2CC0
{
	if (PalSlot < 13) return 1;
	if (PalSlot < 16) return 0;
	byte Type = PalRefs[PalSlot - 16].Type;
	if (Type == PalTypeNPC || Type == PalTypeWeather) return 2;
	if (Type == PalTypeAnimation || Type == PalTypeReflection) return 1;
	return 0;
}

byte GetFadeTypeByWeather(byte Weather)
{
	switch (Weather)
	{
	case 0:
	case 1:
	case 2:
	case 7:
	case 8:
	default:
		return 0; // normal fade
	case 3:
	case 4:
	case 5:
	case 11:
	case 13:
		return 1; // fade and darken
	case 6:
	case 9:
	case 10:
	case 14:
		return 2; // fade and brighten
	case 12:
		return 3; // harsh sunlight
	}
}
