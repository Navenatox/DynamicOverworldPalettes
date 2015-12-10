#include "Main.h"


byte FindPalRef(byte Type, hword PalTag)
{
	int i;
	for (i = 0; i < 16; i++)
	{
		if (PalRefs[i].Type == Type && PalRefs[i].PalTag == PalTag) return i;
	}
	return 0xFF; // not found
}

byte AddPalRef(byte Type, hword PalTag)
{
	int i;
	for (i = 0; i < 16; i++)
	{
		if (PalRefs[i].Type == PalTypeUnused)
		{
			PalRefs[i].Type = Type;
			PalRefs[i].PalTag = PalTag;
			return i;
		}
	}
	return 0xFF; // no more space
}

byte FindPalTag(hword PalTag)
{
	int i;
	if (PalTagsStart >= 16) return 0xFF;
	for (i = PalTagsStart; i < 16; i++)
	{
		if (PalTags[i] == PalTag) return i;
	}
	return 0xFF; // not found
}

byte AddPalTag(hword PalTag)
{
	int i;
	if (PalTagsStart >= 16) return 0xFF;
	for (i = PalTagsStart; i < 16; i++)
	{
		if (PalTags[i] == 0xFFFF)
		{
			PalTags[i] = PalTag;
			return i;
		}
	}
	return 0xFF; // no more space
}

byte PalRefIncreaseCount(byte PalSlot)
{
	PalRefs[PalSlot].Count++;
	return PalSlot;
}

void PalRefDecreaseCount(byte PalSlot)
{
	if (PalRefs[PalSlot].Count != 0) PalRefs[PalSlot].Count--;
	if (PalRefs[PalSlot].Count == 0)
	{
		PalRefs[PalSlot].Type = 0;
		PalRefs[PalSlot].PalTag = 0;
	}
}

void ClearAllPalettes() // hook at 0x5F574
{
	int Fill = 0;
	CpuSet(&Fill, PalRefs, 32 | CpuSetFill);
	CpuSet(&Fill, &UnfadedPalettes[16], 256 | CpuSetFill);
}

