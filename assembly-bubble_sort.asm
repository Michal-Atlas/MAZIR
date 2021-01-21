			mov		R0, #0x10000
			bl		load
			
			;		r5+6 for comparisons
			;		r4 to hold
			;		r3 is success throughout program, end if 1 at end of cycle
			
			sub		r1, r0, #4 ; records endpoint of array
			
begin_loop
			mov		r0, #0x10000 ;  resets pointer to beginning of array
			mov		r3,#1 ; sets progressive success checking to true
begin_iter
			
			ldr		r5, [r0, #0] ; load tuple to compate
			ldr		r6, [r0, #4]
			bl		switch ; switch tuple if out of order
			
			str		r5, [r0, #0] ; write swapped tuple back
			str		r6, [r0, #4]
			add		r0, r0, #4 ; move pointer by 1
			cmp		r0, r1 ; check if at end
			bne		begin_iter
			cmp		r3,#0 ; check if at end with success
			beq		begin_loop
			
			mov		r0, #0x10000
			bl		check
			end
			
switch
			cmp		r5,r6
			movlt	pc,lr
			mov		r7, r6
			mov		r6,r5
			mov		r5,r7
			mov		r3,#0
			mov		pc,lr
			
load ; first arg - addr where data should be placed
			mov		r1, #32
			str		r1, [r0], #4
			mov		r1, #24
			str		r1, [r0], #4
			mov		r1, #16
			str		r1, [r0], #4
			mov		r1, #21
			str		r1, [r0], #4
			mov		r1, #36
			str		r1, [r0], #4
			mov		r1, #22
			str		r1, [r0], #4
			mov		r1, #15
			str		r1, [r0], #4
			mov		r1, #28
			str		r1, [r0], #4
			mov		r1, #3
			str		r1, [r0], #4
			mov		r1, #19
			str		r1, [r0], #4
			mov		r1, #1
			str		r1, [r0], #4
			mov		r1, #14
			str		r1, [r0], #4
			mov		r1, #5
			str		r1, [r0], #4
			mov		r1, #44
			str		r1, [r0], #4
			mov		r1, #40
			str		r1, [r0], #4
			mov		r1, #43
			str		r1, [r0], #4
			mov		r1, #47
			str		r1, [r0], #4
			mov		r1, #4
			str		r1, [r0], #4
			mov		r1, #10
			str		r1, [r0], #4
			mov		r1, #8
			str		r1, [r0], #4
			mov		pc, lr
			
check ; first arg - addr where data is located, returns 0 if check was successfull
			ldr		r1, [r0], #4
			cmp		r1, #1
			bne		error
			ldr		r1, [r0], #4
			cmp		r1, #3
			bne		error
			ldr		r1, [r0], #4
			cmp		r1, #4
			bne		error
			ldr		r1, [r0], #4
			cmp		r1, #5
			bne		error
			ldr		r1, [r0], #4
			cmp		r1, #8
			bne		error
			ldr		r1, [r0], #4
			cmp		r1, #10
			bne		error
			ldr		r1, [r0], #4
			cmp		r1, #14
			bne		error
			ldr		r1, [r0], #4
			cmp		r1, #15
			bne		error
			ldr		r1, [r0], #4
			cmp		r1, #16
			bne		error
			ldr		r1, [r0], #4
			cmp		r1, #19
			bne		error
			ldr		r1, [r0], #4
			cmp		r1, #21
			bne		error
			ldr		r1, [r0], #4
			cmp		r1, #22
			bne		error
			ldr		r1, [r0], #4
			cmp		r1, #24
			bne		error
			ldr		r1, [r0], #4
			cmp		r1, #28
			bne		error
			ldr		r1, [r0], #4
			cmp		r1, #32
			bne		error
			ldr		r1, [r0], #4
			cmp		r1, #36
			bne		error
			ldr		r1, [r0], #4
			cmp		r1, #40
			bne		error
			ldr		r1, [r0], #4
			cmp		r1, #43
			bne		error
			ldr		r1, [r0], #4
			cmp		r1, #44
			bne		error
			ldr		r1, [r0], #4
			cmp		r1, #47
			bne		error
			mov		r0, #0
			mov		pc, lr
error
			mov		r0, #1
			mov		pc, lr
