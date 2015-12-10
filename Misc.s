.thumb


SetPalMisc: @ hook at 0x71B8
	mov r0, r8
	bl GetPalSlotMisc
	cmp r0, #0xFF
	beq SetPalMisc_DoNotSet
	ldr r1, =0x80071CA+1
	bx r1

	SetPalMisc_DoNotSet:
	ldr r0, =0x80071D6+1
	bx r0


SetPalEmotionBubble: @ hook at 0x82664
	push {r0-r2}
	ldr r0, =0x1100
	bl FindOrLoadNPCPalette
	lsl r1, r0, #4
	pop {r0}
	ldrb r3, [r0,#5]
	mov r2, #0xF
	and r2, r3
	mov r3, #0xD
	neg r3, r3
	and r2, r3
	mov r3, #4
	orr r2, r3
	orr r2, r1
	strb r2, [r0,#5]
	pop {r1,r2}
	ldr r3, =0x8082670+1
	bx r3


SetPalWarpArrow: @ hook at 0xDB1AC
	push {r2}
	ldr r0, =0x1100
	bl FindOrLoadNPCPalette
	pop {r2}
	lsl r0, #4
	ldrb r3, [r2,#5]
	mov r1, #0xF
	and r1, r3
	orr r0, r1
	strb r0, [r2,#5]
	mov r3, r2
	add r3, #0x3E
	ldrb r1, [r3]
	mov r0, #5
	neg r0, r0
	and r0, r1
	ldr r1, =0x80DB1B6+1
	bx r1


SetPalItemfinderArrow: @ hook at 0x13F434
	ldr r0, =0x1100
	bl FindOrLoadNPCPalette
	lsl r0, #4
	ldrb r1, [r4,#5]
	mov r2, #0xF
	and r1, r2
	orr r0, r1
	strb r0, [r4,#5]
	mov r0, r4
	ldr r1, =0x813F43C+1
	bx r1


SetPalFameCheckerUnknown: @ hook at 0x12D7A8
	push {r0}
	ldr r0, =0x1103
	push {r2}
	bl FindOrLoadNPCPalette
	pop {r2}
	lsl r0, #4
	ldrb r3, [r2,#5]
	mov r1, #0xD
	neg r1, r1
	and r1, r3
	mov r3, #8
	orr r1, r3
	mov r3, #0xF
	and r1, r3
	orr r1, r0
	pop {r0}
	ldr r3, =0x812D7BA+1
	bx r3


