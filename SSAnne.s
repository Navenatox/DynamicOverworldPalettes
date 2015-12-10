.thumb


SetPalSSAnneWake: @ hook at 0x15D4E8
	push {r1}
	ldr r0, =0x1115
	bl FindOrLoadNPCPalette
	pop {r1}
	lsl r0, #4
	ldrb r2, [r1,#5]
	mov r3, #0xD
	neg r3, r3
	and r2, r3
	mov r3, #8
	orr r2, r3
	mov r3, #0xF
	and r2, r3
	orr r0, r2
	ldr r2, =0x815D4FC+1
	bx r2


SetPalSSAnneSmoke: @ hook at 0x15D600
	push {r0}
	ldr r0, =0x1115
	bl FindOrLoadNPCPalette
	lsl r1, r0, #4
	pop {r0}
	ldrb r2, [r0,#5]
	mov r3, #0xF
	and r2, r3
	orr r1, r2
	ldr r2, =0x815D60A+1
	bx r2


