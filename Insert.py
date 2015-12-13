import os
import sys
import subprocess
import glob
import struct

NM = 'arm-none-eabi-nm'
OBJDUMP = 'arm-none-eabi-objdump'


def get_insertion_offset():
	output = subprocess.check_output([OBJDUMP, '-t', 'Build/Linked.o'])
	lines = output.decode().split('\n')
	
	for line in lines:
		if not line.strip().endswith('.text'):
			continue
		
		offset = int(line.strip().split(' ')[0], 16) - 0x8000000
		if (offset < 0 or offset > 0x2000000):
			print 'The address in the linker script is unsuitable. Please fix it.'
			sys.exit()
		
		return offset
	
	print 'Could not find \'.text\' symbol.'
	sys.exit()

def get_symbols():
	output = subprocess.check_output([NM, 'Build/Linked.o'])
	lines = output.strip().split('\n')
	list = {}
	
	for line in lines:
		columns = line.strip().split(' ')
		list[columns[2]] = int(columns[0], 16)
	
	return list

def insert_data(rom, offset):
	f = open('Build/Data.bin', 'rb')
	data = f.read()
	rom.seek(offset)
	rom.write(data)
	f.close()

def insert_hook(rom, offset, register, pointer):
	data = bytearray([0, 0x48 | register, register << 3, 0x47]) + bytearray(struct.pack('I', pointer + 1))
	rom.seek(offset)
	rom.write(data)

def insert_fix(rom, offset, bytes):
	rom.seek(offset)
	rom.write(bytes)

if not os.path.exists('Build'):
    os.makedirs('Build')

subprocess.call(['make'])

roms = glob.glob('*.gba')
rom = open(roms[0], 'r+b')
symbols = get_symbols()

print 'Inserting data...'

insert_data(rom, get_insertion_offset())

print 'Inserting hooks...'

insert_hook(rom, 0x5f574,  0, symbols['ClearAllPalettes'])
insert_hook(rom, 0x89e8,  1, symbols['FindPalette'])
insert_hook(rom, 0x8928,  1, symbols['FindOrLoadPalette'])
insert_hook(rom, 0xdc9e0,  3, symbols['SetUpTreeDisguise'])
insert_hook(rom, 0xdc9f0,  3, symbols['SetUpRockDisguise'])
insert_hook(rom, 0xdca00,  3, symbols['SetUpWeirdDisguise'])
insert_hook(rom, 0x7a748,  1, symbols['PaletteNeedsFogBrightening'])
insert_hook(rom, 0x7abc0,  1, symbols['LoadCloudOrSandstormPalette'])
insert_hook(rom, 0x5e6b0,  0, symbols['SetPalNPC1'])
insert_hook(rom, 0x5ef78,  0, symbols['SetPalNPC2'])
insert_hook(rom, 0x5eab0,  0, symbols['SetPalNPC3'])
insert_hook(rom, 0x5ebc0,  0, symbols['SetPalNPC4'])
insert_hook(rom, 0xdadb4,  2, symbols['SetPalReflection'])
insert_hook(rom, 0xdc410,  2, symbols['SetPalSurf'])
insert_hook(rom, 0x87188,  1, symbols['SetPalFly'])
insert_hook(rom, 0x12d2ac, 0, symbols['RefreshFameCheckerNPCs'])
insert_hook(rom, 0x71b8,  0, symbols['SetPalMisc'])
insert_hook(rom, 0x82664,  3, symbols['SetPalEmotionBubble'])
insert_hook(rom, 0xdb1ac,  3, symbols['SetPalWarpArrow'])
insert_hook(rom, 0x13f434,  0, symbols['SetPalItemfinderArrow'])
insert_hook(rom, 0x12d7a8,  1, symbols['SetPalFameCheckerUnknown'])
insert_hook(rom, 0x7a2d0,  0, symbols['GetDarkeningType1'])
insert_hook(rom, 0x7a428,  0, symbols['GetDarkeningType2'])
insert_hook(rom, 0x7a544,  0, symbols['GetDarkeningType3'])
insert_hook(rom, 0x7aec4,  1, symbols['FogBrightenAll'])
insert_hook(rom, 0x7aaac,  0, symbols['FogBrightenOnStep'])
insert_hook(rom, 0x7a644,  0, symbols['FogBrightenAndFadeIn'])
insert_hook(rom, 0x7a0a8,  1, symbols['GetFadeType1'])
insert_hook(rom, 0x7a860,  2, symbols['GetFadeType2'])
insert_hook(rom, 0x9d5a8,  2, symbols['SetPalFossilImage'])
insert_hook(rom, 0x9d538,  1, symbols['LoadPalFossilImage'])
insert_hook(rom, 0x9d568,  1, symbols['LoadPalFossilImage'])
insert_hook(rom, 0x15d4e8,  2, symbols['SetPalSSAnneWake'])
insert_hook(rom, 0x15d600,  2, symbols['SetPalSSAnneSmoke'])
insert_hook(rom, 0x7280,  1, symbols['DeleteOBJ'])
insert_hook(rom, 0xdaf88,  0, symbols['DeleteReflection'])
insert_hook(rom, 0xdb120,  0, symbols['DeleteWarpArrow'])

print 'Inserting fixes...'

# don't auto-load NPC palettes into slot 0 or 0xA
insert_fix(rom, 0x5f5e8, bytearray([0x70, 0x47]))
insert_fix(rom, 0x5f658, bytearray([0x70, 0x47]))
insert_fix(rom, 0xdaec4, bytearray([0x70, 0x47]))
insert_fix(rom, 0xdaf20, bytearray([0x70, 0x47]))
insert_fix(rom, 0x5f093, bytearray([0xe0]))

# don't reset pal slot during player animation or reflection
insert_fix(rom, 0x5f114, bytearray([0x0, 0x0]))
insert_fix(rom, 0xdafb8, bytearray([0x0, 0x0]))

# don't load rain palette on entering map
insert_fix(rom, 0x79c18, bytearray([0x0 ,0x25, 0xe, 0xe0]))

# don't load sand palette on healing
insert_fix(rom, 0x1d9895, bytearray([0x7, 0x9c, 0xbe, 0x3c, 0x8, 0x8d, 0x3b, 0x8, 0x8, 0x4]))

# don't treat slot 0xC as weather palette
insert_fix(rom, 0x7a31f, bytearray([0xe0]))

# don't record brightened slots
insert_fix(rom, 0x7aae7, bytearray([0xe0]))

# pal slot of scroll arrow in Fame Checker
insert_fix(rom, 0x45fd52, bytearray([0x9]))

# make it compatible with daniilS' snowflakes routine
insert_fix(rom, 0x7a85e, bytearray([0x80, 0x18]))
insert_fix(rom, 0x7a872, bytearray([0x1, 0x22, 0x5, 0xe0]))

print 'Done!'

rom.close()
