.thumb


SetPalNPC1: @ hook at 0x5E6B0, for regular NPCs
	ldrh r0, [r6,#2]
	bl FindOrLoadNPCPalette
	lsl r1, r0, #4
	ldrb r2, [r4,#5]
	ldr r0, =0x805E6B8+1
	bx r0


SetPalNPC2: @ hook at 0x5EF78, for regular NPCs when returning to the map
	ldrh r0, [r5,#2]
	bl FindOrLoadNPCPalette
	lsl r1, r0, #4
	ldrb r2, [r4,#5]
	mov r0, #0xF
	and r0, r0, r2
	ldr r2, =0x805EF82+1
	bx r2


SetPalNPC3: @ hook at 0x5EAB0, for script command 0xAA createsprite
	ldrh r0, [r4,#2]
	bl FindOrLoadNPCPalette
	lsl r1, r0, #4
	ldrb r3, [r5,#5]
	mov r2, #0xF
	ldr r0, =0x805EAB8+1
	bx r0


SetPalNPC4: @ hook at 0x5EBC0, for Fame Checker NPCs
	mov r0, r4
	ldr r1, =0x80079FC+1 @ LoadAnimFrame, needed for instant refreshing
	bl CallByR1
	ldrh r0, [r7,#2]
	bl FindOrLoadNPCPalette
	lsl r1, r0, #4
	ldrb r3, [r4,#5]
	mov r2, #0xF
	ldr r0, =0x805EBC8+1
	bx r0


SetPalReflection: @ hook at 0xDADB4
	lsr r0, r1, #4
	bl FindOrCreateReflectionPalette
	ldrb r1, [r7,#5]
	ldr r2, = 0x80DADBC+1
	bx r2


SetPalSurf: @ hook at 0xDC410
	push {r1}
	strb r0, [r3]
	ldr r0, =0x1100
	bl FindOrLoadNPCPalette
	pop {r1}
	lsl r0, #4
	ldrb r3, [r1,#5]
	mov r2, #0xF
	and r2, r3
	orr r0, r2
	ldr r2, =0x80DC418+1
	bx r2


SetPalFly: @ hook at 0x87188
	push {r0}
	ldr r0, =0x1100
	push {r2}
	bl FindOrLoadNPCPalette
	pop {r2}
	lsl r0, #4
	ldrb r3, [r2,#5]
	mov r1, #0xF
	and r1, r3
	mov r3, #0xD
	neg r3, r3
	and r1, r3
	orr r1, r0
	pop {r0}
	ldr r3, =0x8087192+1
	bx r3


RefreshFameCheckerNPCs: @ hook at 0x12D2AC, needed for instant refreshing
	ldr r0, =0x0812c5ab
	ldr r1, [sp,#0x14]
	cmp r0, r1
	bne RefreshFameCheckerNPCs_DoNotColor
	push {r4}
	mov r0, #0x10
	lsl r0, #4
	mov r1, #0x60
	mov r2, #0x10
	mov r3, #0
	ldr r4, =0x8045274+1 @ FadePalette, color palettes black if fading in
	bl CallByR4
	pop {r4}

	RefreshFameCheckerNPCs_DoNotColor:
	ldr r1, =0x8006BA8+1 @ RefreshOBJs
	bl CallByR1
	cmp r5, #1
	bne RefreshFameCheckerNPCs_Return2
	ldr r3, =0x203B0FC
	ldr r2, [r3]
	ldrb r0, [r2,#7]
	ldr r1, =0x812D2B4+1
	bx r1

	RefreshFameCheckerNPCs_Return2:
	ldr r0, =0x812D2E0+1
	bx r0


CallByR1:
	bx r1


CallByR4:
	bx r4

