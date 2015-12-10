.thumb


GetDarkeningType1: @ hook at 0x7A2D0
	mov r0, r4
	bl GetDarkeningTypeBySlot
	cmp r0, #0
	ldr r1, =0x807A2D8+1
	bx r1


GetDarkeningType2: @ hook at 0x7A428
	mov r0, r4
	bl GetDarkeningTypeBySlot
	ldr r1, =0x807A430+1
	bx r1


GetDarkeningType3: @ hook at 0x7A544
	mov r0, r4
	bl GetDarkeningTypeBySlot
	ldr r1, =0x807A54C+1
	bx r1


FogBrightenAll: @ hook at 0x7AEC4, dynamically brighten or un-brighten palettes when fog emerges or vanishes
	mov r1, #3
	and r1, r3
	cmp r1, #0
	bne FogBrightenAll_End
	lsr r2, #24
	cmp r2, #0
	bne FogBrightenAll_End
	bl FogBrightenPalettes
	
	FogBrightenAll_End:
	ldr r0, =0x732
	add r0, r5
	ldrh r1, [r0]
	lsl r1, #8
	ldr r0, =0x807AECC+1
	bx r0


FogBrightenOnStep: @ hook at 0x7AAAC
	add r2, #10
	add r0, r1, r2
	ldrb r0, [r0]
	push {r1,r2}
	bl GetFadeTypeByWeather
	pop {r1,r2}
	cmp r0, #2
	beq FogBrightenOnStep_Brighten @ only brighten if there is fog weather
	ldr r0, =0x807AAB6+1
	bx r0

	FogBrightenOnStep_Brighten:
	mov r0, r4
	mov r1, #0
	mov r2, #0
	bl FogBrightenAndFade
	ldr r0, =0x807AB68+1
	bx r0


FogBrightenAndFadeIn: @ hook at 0x7A644
	mov r0, r4
	mov r1, r7
	ldrh r2, [sp]
	bl FogBrightenAndFade
	add r0, r4, #1
	mov r9, r0
	ldr r0, =0x807A6F8+1
	bx r0


GetFadeType1: @ hook at 0x7A0A8, call the correct fade-in function for all fog types
	push {r2}
	ldrb r0, [r0]
	bl GetFadeTypeByWeather
	pop {r2}
	lsl r0, #2
	ldr r1, =GetFadeType1_ReturnTable
	add r0, r1
	ldr r0, [r0]
	bx r0

	.align 2, 0
	GetFadeType1_ReturnTable:
	.word 0x807A16C+1
	.word 0x807A0F8+1
	.word 0x807A144+1
	.word 0x807A120+1


GetFadeType2: @ hook at 0x7A860, copy palettes before fading out for all fog types
	push {r1}
	ldrb r0, [r0]
	bl GetFadeTypeByWeather
	pop {r1}
	cmp r0, #0
	beq GetFadeType2_NormalFade
	ldr r0, =0x807A872+1
	bx r0

	GetFadeType2_NormalFade:
	ldr r0, =0x807A880+1
	bx r0


