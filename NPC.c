#include "Main.h"


byte FindOrLoadNPCPalette(hword PalTag)
{
	byte PalSlot;
	PalSlot = FindPalRef(PalTypeNPC, PalTag);
	if (PalSlot != 0xFF) return PalRefIncreaseCount(PalSlot);
	PalSlot = AddPalRef(PalTypeNPC, PalTag);
	if (PalSlot == 0xFF) return PalRefIncreaseCount(0);
	LoadNPCPalette(PalTag, PalSlot);
	MaskPaletteIfFadingIn(PalSlot);
	return PalRefIncreaseCount(PalSlot);
}

byte FindOrCreateReflectionPalette(byte PalSlotNPC)
{
	byte PalSlot;
	hword PalTag = PalRefs[PalSlotNPC].PalTag;
	PalSlot = FindPalRef(PalTypeReflection, PalTag);
	if (PalSlot != 0xFF) return PalRefIncreaseCount(PalSlot);
	PalSlot = AddPalRef(PalTypeReflection, PalTag);
	if (PalSlot == 0xFF) return PalRefIncreaseCount(0);
	LoadNPCPalette(PalTag, PalSlot);
	FadePalette((PalSlot + 16) * 16, 16, 6, RGB(12, 20, 27)); // make it blueish
	BrightenReflection(PalSlot); // and a little brighter
	TintOBJPalette(PalSlot);
	MaskPaletteIfFadingIn(PalSlot);
	return PalRefIncreaseCount(PalSlot);
}

void BrightenReflection(byte PalSlot)
{
	Palette *Pal = &Palettes[PalSlot + 16];
	hword Color;
	byte R, G, B;
	int i;
	for (i = 0; i < 16; i++)
	{
		Color = Pal->Colors[i];
		R = Red(Color) + 5;
		G = Green(Color) + 5;
		B = Blue(Color) + 10;
		if (R > 31) R = 31;
		if (G > 31) G = 31;
		if (B > 31) B = 31;
		Pal->Colors[i] = RGB(R, G, B);
	}
	CpuSet(Pal, &UnfadedPalettes[PalSlot + 16], 16);
}

byte SetUpTreeDisguise() // hook at 0xDC9E0
{
	return SetUpDisguise(0x1C, 0x18, FindOrLoadNPCPalette(0x1105));
}

byte SetUpRockDisguise() // hook at 0xDC9F0
{
	return SetUpDisguise(0x1D, 0x19, FindOrLoadNPCPalette(0x1104));
}

byte SetUpWeirdDisguise() // hook at 0xDCA00
{
	return SetUpDisguise(0x24, 0x1C, FindOrLoadNPCPalette(0x1103));
}

