CC=arm-none-eabi-gcc
AS=arm-none-eabi-as
LD=arm-none-eabi-ld
OBJCOPY=arm-none-eabi-objcopy

CFLAGS=-c -Os -mthumb -mno-thumb-interwork
LDFLAGS=-T Linker.lsc -z muldefs

All: PalRef NPC Weather Misc
	$(LD) $(LDFLAGS) -o Build/Linked.o Build/PalRef.o Build/NPC1.o Build/NPC2.o Build/Weather1.o Build/Weather2.o Build/Misc1.o Build/Misc2.o Build/FossilImage.o Build/SSAnne.o Build/DeleteOBJ.o
	$(OBJCOPY) -O binary Build/Linked.o Build/Data.bin

PalRef:
	$(CC) $(CFLAGS) PalRef.c -o Build/PalRef.o

NPC:
	$(CC) $(CFLAGS) NPC.c -o Build/NPC1.o
	$(AS) NPC.s -o Build/NPC2.o

Weather:
	$(CC) $(CFLAGS) Weather.c -o Build/Weather1.o
	$(AS) Weather.s -o Build/Weather2.o

Misc:
	$(CC) $(CFLAGS) Misc.c -o Build/Misc1.o
	$(AS) Misc.s -o Build/Misc2.o
	$(AS) FossilImage.s -o Build/FossilImage.o
	$(AS) SSAnne.s -o Build/SSAnne.o
	$(AS) DeleteOBJ.s -o Build/DeleteOBJ.o


