.thumb


DeleteOBJFreeTiles: @ hook at 0x7280
	push {r4-r7,lr}
	mov r5, r0
	ldr r0, [r0,#0x14]
	ldr r1, =0x8231D00 @ template for empty OBJ
	cmp r0, r1
	beq DeleteOBJFreeTiles_Return
	ldrb r0, [r5,#5]
	lsr r0, #4
	bl PalRefDecreaseCount
	
	DeleteOBJFreeTiles_Return:
	mov r0, r5
	add r0, #0x3E
	ldrb r1, [r0]
	ldr r0, =0x8007288+1
	bx r0


DeleteAllOBJs: @ hook at 0x779C
	ldr r1, =0x80073DC+1 @ DeleteOBJ
	bl CallByR1
	bl ClearAllPalRefs
	pop {r4,r5,pc}


DeleteReflection: @ hook at 0xDAF88
	ldrb r0, [r4,#5]
	lsr r0, #4
	bl PalRefDecreaseCount
	mov r2, r4
	add r2, #0x3E
	ldrb r1, [r2]
	mov r0, #2
	neg r0, r0
	and r0, r1
	ldr r1, =0x80DAF94+1
	bx r1


DeleteWarpArrow: @ hook at 0xDB120
	push {lr}
	add r1, r2
	mov r2, r1
	add r2, #0x3E
	ldrb r0, [r2]
	mov r3, #5
	and r0, r3
	cmp r0, #1
	bne DeleteWarpArrow_SetBits @ only decrease count when arrow disappears
	ldrb r0, [r1,#5]
	lsr r0, #4
	push {r2}
	bl PalRefDecreaseCount
	pop {r2}

	DeleteWarpArrow_SetBits:
	ldrb r0, [r2]
	mov r1, #4
	orr r0, r1
	strb r0, [r2]
	pop {pc}


CallByR1:
	bx r1


