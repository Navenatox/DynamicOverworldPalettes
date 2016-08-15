#include "Main.h"


byte FindPalette(hword PalTag) // hook at 0x89E8
{
	if (OverworldIsActive || PalTag == 0x1200) return FindPalRef(GetPalTypeByPalTag(PalTag), PalTag); // 0x1200 is for weather sprites
	else return FindPalTag(PalTag);
}

byte FindOrLoadPalette(PalInfo *Pal) // hook at 0x8928
{
	byte PalSlot;
	hword PalTag = Pal->PalTag;
	if (OverworldIsActive || PalTag == 0x1200) // 0x1200 is for weather sprites
	{
		PalSlot = FindPalRef(GetPalTypeByPalTag(PalTag), PalTag);
		if (PalSlot != 0xFF) return PalSlot;
		PalSlot = AddPalRef(GetPalTypeByPalTag(PalTag), PalTag);
		if (PalSlot == 0xFF) return 0xFF;
	}
	else
	{
		PalSlot = FindPalTag(PalTag);
		if (PalSlot != 0xFF) return PalSlot;
		PalSlot = AddPalTag(PalTag);
		if (PalSlot == 0xFF) return 0xFF;
	}
	LoadOBJPalette(Pal->Address, PalSlot * 16);
	return PalSlot;
}

byte GetPalTypeByPalTag(hword PalTag)
{
	if (PalTag >= 0x1000 && PalTag <= 0x1010) return PalTypeAnimation;
	if (PalTag == 0x1200) return PalTypeWeather;
	return PalTypeOther;
}

byte GetPalSlotMisc(word OBJData)
{
	byte PalSlot;
	hword PalTag = *(hword*)(OBJData + 2);
	if (PalTag == 0xFFFF) return 0xFF;
	PalSlot = FindPalette(PalTag);
	if (PalSlot != 0xFF) return PalRefIncreaseCount(PalSlot);
	if (PalTag != 0x1200) return 0xFF;

	// load the rain palette
	PalSlot = AddPalRef(PalTypeWeather, PalTag);
	if (PalSlot == 0xFF) return 0xFF;
	LoadOBJPalette((Palette*)0x83C2CE0, PalSlot * 16);
	TintOBJPalette(PalSlot);
	MaskPaletteIfFadingIn(PalSlot);
	return PalRefIncreaseCount(PalSlot);
}

void MaskPaletteIfFadingIn(byte PalSlot) // prevent the palette from flashing briefly before fading starts
{
	byte FadeState = *(byte*)(FadeInfo2 + 6);
	byte AboutToFadeIn = *(byte*)(FadeInfo2 + 10);
	if (FadeState == 1 && AboutToFadeIn)
	{
		hword FadeColor = *(hword*)(FadeInfo2 + 4);
		CpuSet(&FadeColor, &Palettes[PalSlot + 16], 16 | CpuSetFill);
	}
}
