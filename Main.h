#include "Types.h"
#include "RAM.h"
#include "Functions.h"
#include "Color.h"


#define PalTypeUnused 0
#define PalTypeNPC 1
#define PalTypeAnimation 2
#define PalTypeWeather 3
#define PalTypeReflection 4
#define PalTypeOther 5

byte FindPalRef(byte, hword);
byte AddPalRef(byte, hword);
byte FindPalTag(hword);
byte AddPalTag(hword);
byte PalRefIncreaseCount(byte);
void PalRefDecreaseCount(byte);
void ClearAllPalettes();

byte FindPalette(hword);
byte FindOrLoadPalette(PalInfo*);
byte GetPalTypeByPalTag(hword);
byte GetPalSlotMisc(word);
void MaskPaletteIfFadingIn(byte);

byte FindOrLoadNPCPalette(hword);
byte FindOrCreateReflectionPalette(byte);
void BrightenReflection(byte);
byte SetUpTreeDisguise();
byte SetUpRockDisguise();
byte SetUpWeirdDisguise();

void FogBrightenPalettes(hword);
void FogBrightenAndFade(byte, byte, hword);
byte PaletteNeedsFogBrightening(byte);
void LoadCloudOrSandstormPalette(Palette*);
hword TintColor(hword);
byte GetDarkeningTypeBySlot(byte);
byte GetFadeTypeByWeather(byte);

