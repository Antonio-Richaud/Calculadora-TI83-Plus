;------------------------=Affiche_a v0.8=--------------------------------
;Par Alexis GUINAMARD
;Cette routine affiche la valeur de a en décimal dans le graphbuffer
;sans passer par les rom calls utilisant les op et autres disphl dans
;une jolie police à chasse fixe de 7*4 pixels
;ENTREE:

; a=valeur à convertir en décimal et à afficher
; b=coodronnée X 
; c=coordonnée Y

SORTIE:

;La valeur de a est dans le graph buffer aux coordonnées demandées

;Cette routine nécessite la routine ionputsprite
;---------------------------------------------------------------------
affiche_a:

	push	bc
	ld	l,a
	ld	h,0
	ld	e,100
	ld	d,h
	call	divhlparde
	

	ld	a,l
	ld	(aff_codegen+1),a
	ld	a,c
	ld	b,a
	add	a,a
	add	a,a
	add	a,a
	sub	b
	ld	l,a
	ld	h,0
	ld	de,police
	add	hl,de
	push	hl
	pop	ix
	ld	b,7
	pop	hl
	ld	a,5
	add	a,h
	ld	h,a
	push	hl
	call	putsprite
	ld	h,0
aff_codegen:	ld	l,$00

suiteaffcommun:
	ld	de,10
	call	divhlparde
	ld	a,l
	ld	(aff_codegen2+1),a
	ld	a,c
	ld	b,a
	add	a,a
	add	a,a
	add	a,a
	sub	b
	ld	l,a
	ld	h,0
	ld	de,police
	add	hl,de
	push	hl
	pop	ix
	ld	b,7
	pop	hl
	ld	a,5
	add	a,h
	ld	h,a
	push	hl
	call	putsprite
	ld	h,0
aff_codegen2:	ld	a,$00
	ld	b,a
	add	a,a
	add	a,a
	add	a,a
	sub	b
	ld	l,a
	ld	h,0	
	ld	de,police
	add	hl,de
	push	hl
	pop	ix
	ld	b,7
	pop	hl
	ld	a,5
	add	a,h
	call	putsprite
	ret

divhlparde:
	or a        
	ld bc,0      
DivhlbyDE:
	sbc hl,de   
	jp c,nomore  
	inc bc       
	jp z,suite   
	jp DivhlbyDE 
nomore:
	add hl,de     
	ret
suite:
	ld	hl,0
	ret

putSprite:
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
putSpriteLoop1:
sl1:	ld	d,(ix)
	ld	e,$00
	ld	a,c
	or	a
	jr	z,putSpriteSkip1
putSpriteLoop2:
	srl	d
	rr	e
	dec	a
	jr	nz,putSpriteLoop2
putSpriteSkip1:
	ld	a,(hl)
	xor	d
	ld	(hl),a
	inc	hl
	ld	a,(hl)
	xor	e
	ld	(hl),a
	ld	de,$0B
	add	hl,de
	inc	ix
	djnz	putSpriteLoop1
	ret

police:
	.db %11100000
	.db %10010000
	.db %10010000
	.db %10010000
	.db %10010000
	.db %10010000
	.db %01110000

	.db %01100000
	.db %00100000
	.db %00100000
	.db %00100000
	.db %00100000
	.db %00110000
	.db %01110000

	.db %01100000
	.db %10010000
	.db %00010000
	.db %00100000
	.db %01000000
	.db %10000000
	.db %11110000

	.db %11100000
	.db %00010000
	.db %00010000
	.db %01100000
	.db %00010000
	.db %00010000
	.db %11100000

	.db %10000000
	.db %10000000
	.db %10000000
	.db %10100000
	.db %11110000
	.db %00100000
	.db %00100000

	.db %11110000
	.db %10000000
	.db %11100000
	.db %00010000
	.db %00010000
	.db %00100000
	.db %11000000

	.db %10000000
	.db %10000000
	.db %10000000
	.db %11110000
	.db %10010000
	.db %10010000
	.db %11110000

	.db %11110000
	.db %10010000
	.db %00010000
	.db %00010000
	.db %00010000
	.db %00010000
	.db %00010000

	.db %11110000
	.db %10010000
	.db %10010000
	.db %01100000
	.db %10010000
	.db %10010000
	.db %11110000

	.db %11110000
	.db %10010000
	.db %10010000
	.db %11110000
	.db %00010000
	.db %00010000
	.db %00010000

.end