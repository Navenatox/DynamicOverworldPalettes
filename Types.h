typedef unsigned char	byte;
typedef unsigned short	hword;
typedef unsigned long	word;

typedef struct
{
	byte Type;
	byte Count;
	hword PalTag;
} PalRef;

typedef struct
{
	hword Colors[16];
} Palette;

typedef struct
{
	Palette *Address;
	hword PalTag;
} PalInfo;

typedef void(*TaskFunc)(byte);

