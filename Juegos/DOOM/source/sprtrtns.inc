largeSprite:
	di
	ex	af,af'
	ld	a,c
	push	af
	ex	af,af'
	ld	e,l
	ld	h,$00
	ld	d,h
	add	hl,de
	add	hl,de
	add	hl,hl
	add	hl,hl
	ld	e,a
	and	$07
	ld	c,a
	srl	e
	srl	e
	srl	e
	add	hl,de
	ld	de,gbuf
	add	hl,de
largeSpriteLoop1:
	push	hl
largeSpriteLoop2:
	ld	d,(ix)
	ld	e,$00
	ld	a,c
	or	a
	jr	z,largeSpriteSkip1
largeSpriteLoop3:
	srl	d
	rr	e
	dec	a
	jr	nz,largeSpriteLoop3
largeSpriteSkip1:
	ld	a,(hl)
	or	d
	ld	(hl),a
	inc	hl
	ld	a,(hl)
	or	e
	ld	(hl),a
	inc	ix
	ex	af,af'
	dec	a
	push	af
	ex	af,af'
	pop	af
	jr	nz,largeSpriteLoop2
	pop	hl
	pop	af
	push	af
	ex	af,af'
	ld	de,$0C
	add	hl,de
	djnz	largeSpriteLoop1
	pop	af
	ex	af,af'
	ei
	ret

largeSprite2:
	di
	ex	af,af'
	ld	a,c
	push	af
	ex	af,af'
	ld	e,l
	ld	h,$00
	ld	d,h
	add	hl,de
	add	hl,de
	add	hl,hl
	add	hl,hl
	ld	e,a
	and	$07
	ld	c,a
	srl	e
	srl	e
	srl	e
	add	hl,de
	ld	de,gbuf
	add	hl,de
largeSpriteLoop12:
	push	hl
largeSpriteLoop22:
	ld	d,(ix)
	ld	e,$00
	ld	a,c
	or	a
	jr	z,largeSpriteSkip12
largeSpriteLoop32:
	srl	d
	rr	e
	dec	a
	jr	nz,largeSpriteLoop32
largeSpriteSkip12:
	ld	a,(hl)
	ld	a,d		;
	ld	(hl),a
	inc	hl
	ld	a,(hl)
	or	e		;
	ld	(hl),a
	inc	ix
	ex	af,af'
	dec	a
	push	af
	ex	af,af'
	pop	af
	jr	nz,largeSpriteLoop22
	pop	hl
	pop	af
	push	af
	ex	af,af'
	ld	de,$0C
	add	hl,de
	djnz	largeSpriteLoop12
	pop	af
	ex	af,af'
	ei
	ret

fastCopy:
	
	ld	a,$80				; 7
	out	($10),a				; 11
	ld	hl,gbuf-12-(-(12*64)+1)		; 10
	ld	a,$20				; 7
	ld	c,a				; 4
	inc	hl				; 6 waste
	dec	hl				; 6 waste
fastCopyAgain:
	ld	b,64				; 7
	inc	c				; 4
	ld	de,-(12*64)+1			; 10
	out	($10),a				; 11
	add	hl,de				; 11
	ld	de,10				; 10
fastCopyLoop:
	add	hl,de				; 11
	inc	hl				; 6 waste
	inc	hl				; 6 waste
	inc	de				; 6
	ld	a,(hl)				; 7
	out	($11),a				; 11
	dec	de				; 6
	djnz	fastCopyLoop			; 13/8
	ld	a,c				; 4
	cp	$2B+1				; 7
	jr	nz,fastCopyAgain		; 10/1
	ret

getPixel:
	ld	d,$00
	ld	h,d
	ld	l,e
	add	hl,de
	add	hl,de
	add	hl,hl
	add	hl,hl
	ld	de,gbuf
	add	hl,de
	ld	b,$00
	ld	c,a
	and	%00000111
	srl	c
	srl	c
	srl	c
	add	hl,bc
	ld	b,a
	inc	b
	ld	a,%00000001
getPixelLoop:
	rrca
	djnz	getPixelLoop
	ret


.end

