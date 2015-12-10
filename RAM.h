#define PalRefs					((PalRef*)0x203FF00) // shamelessly assuming this is unused space
#define PalTags					((hword*)0x3000DE8)

#define Palettes				((Palette*)0x20375F8)
#define UnfadedPalettes			((Palette*)0x20371F8)

#define PalTagsStart			*((byte*)0x3003E58)
#define ColorFilter				*((byte*)0x2036E28)
#define FadeInfo2				((void*)0x2037F34+0x6C0)
#define AlphaBlendingCoeffA		*((byte*)0x3000052)

