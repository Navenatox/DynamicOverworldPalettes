.thumb


SetPalFossilImage: @ hook at 0x9D5A8
	push {r0}
	mov r0, #5
	ldr r1, =0x20370C0 @ var 8004
	ldrh r1, [r1]
	bl FindPalRef
	lsl r1, r0, #4
	pop {r0}
	ldrb r2, [r0,#5]
	mov r3, #0xF
	and r2, r3
	orr r1, r2
	ldr r2, =0x809D5B2+1
	bx r2


LoadPalFossilImage: @ hook at 0x9D538, 0x9D568
	push {r0}
	mov r0, #5
	ldr r1, =0x20370C0 @ var 8004
	ldrh r1, [r1]
	bl AddPalRef
	mov r1, r0
	pop {r0}
	cmp r1, #0xFF @ no more space
	beq LoadPalFossilImage_End
	lsl r1, #4
	ldr r2, =0x80089A0+1 @ LoadOBJPalette
	bl CallByR2

	LoadPalFossilImage_End:
	ldr r1, =0x809D572+1
	bx r1


CallByR2:
	bx r2


