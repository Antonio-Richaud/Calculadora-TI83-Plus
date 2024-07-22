
	jr	retourmenuplus		;initialise nmenu
bouclemenu:
	bcall(_cleargbuf)
	ld	a,24			;sprite du menu
	ld	l,0
	ld	b,64
	ld	c,6
	ld	ix,spritemenu
	call	largesprite
	
	ld	a,(nmenu)
	add	a,a
	add	a,a			;a=17+12*nmenu
	ld	b,a
	add	a,a
	add	a,b
	add	a,17
	ld	l,a
	ld	a,11
	ld	b,a			;hauteur =11
	ld	c,2
	ld	ix,tete
	call	largesprite

	call	fastcopy

	bcall(_getkey)
	sub	3
	jr	z,menumoins
	dec	a
	jp	z,menuplus
	dec	a
	jp	z,menuok
	jr	bouclemenu

menuplus:
	ld	a,(nmenu)
	cp	3
	jr	z,retourmenuplus
	inc	a
	ld	(nmenu),a
	jr	bouclemenu
menumoins:
	ld	a,(nmenu)
	or	a
	jr	z,retourmenumoins
	dec	a
	ld	(nmenu),a
	jr	bouclemenu
retourmenuplus:
	xor	a
	ld	(nmenu),a
	jr	bouclemenu
retourmenumoins:
	ld	a,3
	ld	(nmenu),a
	jr	bouclemenu

menuok:
	ld	a,(nmenu)
	or	a
	jp	z,jeu_init	;jouer!
	dec	a
	jp	z,multi
	dec	a
	jr	z,options
	ret	


options:
	xor	a
	ld	(moptions),a
options_b:
	bcall(_clrlcdf)
	ld	hl,0
	ld	(currow),hl
	ld	hl,0
	ld	(curcol),hl
	ld	hl,optionst1		;"options"
	bcall(_puts)


	ld	hl,2
	ld	(currow),hl
	ld	hl,11
	ld	(curcol),hl
	ld	a,(contmax)
	sub	$f6			;pour avoir une valeur entre
	ld	l,a			;0 et 10
	ld	h,0
	bcall(_disphl)
	ld	hl,2
	ld	(currow),hl
	ld	hl,1
	ld	(curcol),hl
	ld	hl,optionst2		;"contraste"
	bcall(_puts)


	ld	hl,4
	ld	(currow),hl
	ld	hl,1
	ld	(curcol),hl
	ld	hl,optionst3		;difficulté
	bcall(_puts)
	ld	hl,5
	ld	(currow),hl
	ld	hl,0
	ld	(curcol),hl
	ld	a,(difficulte)
	or	a
	jr	z,facile
	dec	a
	jr	z,moyen
	jr	dur
facile:
;code generé pour rendre le jeu facile
	ld	hl,optionst4
	jr	suiteboucleoptions
moyen:
	ld	hl,optionst5
	jr	suiteboucleoptions
dur:
	ld	hl,optionst6

suiteboucleoptions:
	bcall(_puts)			;affiche la difficulté
	ld	a,(moptions)
	add	a,a
	add	a,2			;a=a*2+2
	ld	l,a
	ld	h,0
	ld	(currow),hl
	ld	hl,0
	ld	(curcol),hl
	ld	hl,optionst7
	bcall(_puts)



	bcall(_getkey)
	dec	a
	jr	z,optioninc
	dec	a
	jr	z,optiondec
	dec	a
	jp	z,optionplus
	dec	a
	jp	z,optionmoins
	dec	a
	jp	z,bouclemenu
	jp	options_b
	
optioninc:
	ld	a,(moptions)
	or	a
	jr	z,inccont

incdiff:
	ld	a,(difficulte)
	cp	2
	jp	z,options_b
	inc	a
	ld	(difficulte),a
	jp	options_b


optiondec:
	ld	a,(moptions)
	or	a
	jp	z,deccont
decdiff:
	ld	a,(difficulte)
	or	a
	jp	z,options_b
	dec	a
	ld	(difficulte),a
	jp	options_b
deccont:
	ld	a,(contmax)
	cp	$F6
	jp	z,options_b
	dec	a
	ld	(contmax),a
	ld	hl,sombre+1		;code generé pour le contraste
	ld	(hl),a
	jp	options_b
inccont:
	ld	a,(contmax)
	cp	$FF
	jp	z,options_b
	inc	a
	ld	(contmax),a
	ld	hl,sombre+1		;code generé pour le contraste
	ld	(hl),a
	jp	options_b
optionplus:
	ld	a,(moptions)
	or	a
	jp	z,options_b
	dec	a
	ld	(moptions),a
	jp	options_b
optionmoins:
	ld	a,(moptions)
	cp	1
	jp	z,options_b
	inc	a
	ld	(moptions),a
	jp	options_b

jouer:
multi:
	jp	bouclemenu


spritemenu:

; Width:48 Height:64 (384 bytes)
	.db %11111111,%11001111,%11111100,%11111111,%11001111,%00001111
	.db %11111111,%11001111,%11111100,%11111111,%11001111,%10011111
	.db %11111111,%11001111,%11111100,%11111111,%11001111,%10011111
	.db %11100001,%11001110,%00011100,%11100001,%11001111,%11111111
	.db %11100001,%11001110,%00011100,%11100001,%11001111,%11111111
	.db %11100001,%11001110,%00011100,%11100001,%11001111,%01101111
	.db %10100001,%01001010,%00010100,%10100001,%01001001,%00001111
	.db %10100001,%01001010,%00010100,%10100001,%01001001,%00001001
	.db %10100110,%01001001,%11100100,%10011110,%01001001,%00001001
	.db %10101000,%10000100,%00001000,%01000000,%10000101,%00001001
	.db %10110011,%00000011,%00110000,%00110011,%00000011,%00001001
	.db %10000100,%00000000,%11001110,%11001100,%00000000,%00001001
	.db %10001000,%00000000,%00001010,%00100000,%00000000,%00001001
	.db %10110000,%00000000,%00000100,%01000000,%00000000,%00000101
	.db %11000000,%00000000,%00001010,%00100000,%00000000,%00000011
	.db %10000000,%00000000,%00001110,%11000000,%00000000,%00000001
	.db %00000000,%00000000,%00000000,%00000000,%00000000,%00000000
	.db %00111111,%11000111,%10001100,%00110011,%11111001,%11111000
	.db %00111111,%11001111,%11001100,%00110111,%11111011,%11111100
	.db %00000001,%10001100,%11001100,%00110110,%00000011,%00001100
	.db %00000001,%10011000,%01101100,%00110110,%00000011,%00001100
	.db %00000001,%10011000,%01101100,%00110111,%11110011,%11111100
	.db %00000001,%10011000,%01101100,%00110111,%11110011,%11111000
	.db %00000001,%10011000,%01101100,%00110110,%00000011,%11100000
	.db %00000001,%10011000,%01101100,%00110110,%00000011,%01110000
	.db %00110001,%10001100,%11001100,%00110110,%00000011,%00111000
	.db %00011111,%00001111,%11000111,%11100111,%11111011,%00011100
	.db %00001110,%00000111,%10000011,%11000011,%11111011,%00001100
	.db %00000000,%00000000,%00000000,%00000000,%00000000,%00000000
	.db %00011000,%01101100,%00110110,%00000011,%11111100,%11110000
	.db %00000000,%00000000,%00000000,%00000000,%00000000,%00000000
	.db %00011111,%11101100,%00110110,%00000010,%01100100,%01100000
	.db %00000000,%00000000,%00000000,%00000000,%00000000,%00000000
	.db %00011000,%01101100,%00110110,%00000000,%01100000,%01100000
	.db %00000000,%00000000,%00000000,%00000000,%00000000,%00000000
	.db %00011000,%01101100,%00110110,%00000000,%01100000,%01100000
	.db %00000000,%00000000,%00000000,%00000000,%00000000,%00000000
	.db %00011000,%01101100,%00110110,%00000000,%01100000,%01100000
	.db %00000000,%00000000,%00000000,%00000000,%00000000,%00000000
	.db %00011000,%01100011,%11000011,%11111000,%11110000,%11110000
	.db %00000000,%00000000,%00000000,%00000000,%00000000,%00000000
	.db %00111100,%01111110,%01111111,%10111100,%01111000,%11000011
	.db %01111110,%01111111,%01111111,%10111100,%11111100,%11100011
	.db %01100110,%01100011,%01001100,%10011000,%11001100,%11100011
	.db %11000011,%01100011,%00001100,%00011001,%10000110,%11110011
	.db %11000011,%01111111,%00001100,%00011001,%10000110,%11010011
	.db %11000011,%01111110,%00001100,%00011001,%10000110,%11011011
	.db %11000011,%01100000,%00001100,%00011001,%10000110,%11001011
	.db %11000011,%01100000,%00001100,%00011001,%10000110,%11001111
	.db %01100110,%01100000,%00001100,%00011000,%11001100,%11000111
	.db %01111110,%01110000,%00011110,%00111100,%11111100,%11000111
	.db %00111100,%01110000,%00011110,%00111100,%01111000,%11000011
	.db %00000000,%00000000,%00000000,%00000000,%00000000,%00000000
	.db %00000000,%00111100,%01100001,%10011110,%01111111,%10000000
	.db %00000000,%01111110,%01100001,%10011110,%01111111,%10000000
	.db %00000000,%01100110,%01100001,%10001100,%01001100,%10000000
	.db %00000000,%11000011,%01100001,%10001100,%00001100,%00000000
	.db %00000000,%11000011,%01100001,%10001100,%00001100,%00000000
	.db %00000000,%11000011,%01100001,%10001100,%00001100,%00000000
	.db %00000000,%11000011,%01100001,%10001100,%00001100,%00000000
	.db %00000000,%11001111,%01100001,%10001100,%00001100,%00000000
	.db %00000000,%01101110,%01100001,%10001100,%00001100,%00000000
	.db %00000000,%01111111,%00111111,%00011110,%00011110,%00000000
	.db %00000000,%00111011,%00011110,%00011110,%00011110,%00000000

tete:
; Width:11 Height:11 (22 bytes)
	.db %00011111,%00000000
	.db %00100000,%10000000
	.db %01000000,%01000000
	.db %01011011,%01000000
	.db %01011011,%01000000
	.db %01000100,%01000000
	.db %00100100,%10000000
	.db %00110001,%10000000
	.db %00011111,%00000000
	.db %00010001,%00000000
	.db %00001110,%00000000

contmax:
	.db $FB
difficulte:
	.db 1
optionst1:
	.db "OPTIONS DE DOOM:",0
optionst2:
	.db "Contraste max:",0
optionst3:
	.db "Difficult",$96,":",0
optionst4:
	.db "Too young to die",0
optionst5:
	.db "Hurt me plenty.",0
optionst6:
	.db "Ultra-Violence.",0
optionst7:
	.db $1c,0 ;->
.end