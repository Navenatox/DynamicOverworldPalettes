#define LoadOBJPalette(PalAddress, StartColor)							((void(*)(Palette*, hword))0x80089A0+1)(PalAddress, StartColor)
#define LoadNPCPalette(PalTag, PalSlot)									((void(*)(hword, byte))0x805F538+1)(PalTag, PalSlot)
#define FadePalette(StartColor, ColorCount, FadeIntensity, FadeColor)	((void(*)(hword, hword, byte, hword))0x8045274+1)(StartColor, ColorCount, FadeIntensity, FadeColor)
#define TintOBJPalette(PalSlot)											((void(*)(byte))0x8083598+1)(PalSlot)
#define TintGrayscale(Colors, ColorCount)								((void(*)(hword*, hword))0x8071544+1)(Colors, ColorCount)
#define TintSepia(Colors, ColorCount)									((void(*)(hword*, hword))0x80715F4+1)(Colors, ColorCount)

#define TaskIsRunning(Func)												((byte(*)(TaskFunc))0x8077650+1)(Func)
#define TaskOverworld													((TaskFunc)0x8079E0C+1)
#define OverworldIsActive												TaskIsRunning(TaskOverworld)

#define SetUpDisguise(Arg1, Arg2, PalSlot)								((byte(*)(byte, byte, byte))0x80DCA10+1)(Arg1, Arg2, PalSlot)

void __attribute__ ((noinline)) CpuSet(void *Source, void *Dest, word LengthMode)
{
	asm("swi #0xb");
}

#define CpuSetFill (1 << 24)

