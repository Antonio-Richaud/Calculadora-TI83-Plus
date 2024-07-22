nouveau_monde:
	push	af
	bcall(_clrlcdf)
	ld	bc,12
	ld	hl,ia_identliste
	xor	a
	ld	(hl),a
	ld	de,ia_identliste+1
	ldir
	pop	af
	cp	1
	jp	z,nouveaumonde2
	cp	2
	jp	z,nouveaumonde3
	;jp	p,nouveaumonde4
	ld	hl,04
	ld	(currow),hl
	ld	(curcol),hl
	ld	hl,niveau2
	bcall(_puts)
	ld	de,monde
	ld	hl,monde2
	ld	bc,32*20
	ldir
	ld	hl,$0100
	ld	(xperso_v),hl
	ld	(zperso_v),hl
	ld	a,30
	ld	(orientation),a
	ld	a,1
	ld	(niveau),a

	call	temporisateur
	im	2
	jp	boucle_principalle

nouveaumonde2:
	ld	hl,04
	ld	(currow),hl
	ld	(curcol),hl
	ld	hl,niveau3
	bcall(_puts)
	ld	de,monde
	ld	hl,monde3
	ld	bc,32*20
	ldir
	ld	hl,$0100
	ld	(xperso_v),hl
	ld	(zperso_v),hl
	ld	a,30
	ld	(orientation),a
	ld	a,2
	ld	(niveau),a
	call	temporisateur
	im	2
	jp	boucle_principalle

nouveaumonde3:
	ld	hl,04
	ld	(currow),hl
	ld	(curcol),hl
	ld	hl,niveau3
	bcall(_puts)
	ld	de,monde
	ld	hl,monde4
	ld	bc,32*20
	ldir
	ld	hl,$0100
	ld	(xperso_v),hl
	ld	(zperso_v),hl
	ld	a,30
	ld	(orientation),a
	ld	a,3
	ld	(niveau),a
	call	temporisateur
	im	2
	jp	boucle_principalle


temporisateur:
	ld	de,20000
	ld	hl,0
tempo:
	inc	hl
	bcall(_cphlde)
	jr	nz,tempo
	ret
.end