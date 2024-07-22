;initialisation
#ifdef TI83P	
	in	a,(6)
	ld	(mempage1+1),a
	in	a,(7)
	ld	(mempage2+1),a
#endif

	ld	(sp-2),sp
	pop	hl
	push	hl
	ld	(tempreturn),hl
	ld	a,(contrast)
	ld	(cont),a



	di
	ld	hl,interrupt_table
	ld	de,interrupt_table+1
	ld	bc,256
	ld	(hl),interrupt
	ldir					;installation de
	ld	hl,interrupt_adresse
	ld	(hl),$C3
	ld	de,deplacement
	inc	hl				;l'interruption pour
	ld	(hl),e
	inc	hl				;le déplacement
	ld	(hl),d
	
	ld	a,interrupt_table2
	ld	i,a
	im	2
	


	xor	a
	ld	(orientation),a
	ld	(nmonstres),a
	ld	(tire),a
	ld	(niveau),a
	ld	hl,$100
	ld	(xperso_v),hl
	ld	(zperso_v),hl
	ld	hl,16
	ld	(xperso),hl
	ld	(zperso),hl

	ld	a,30
	ld	(vie),a
	ld	(munitionsv),a
	
	ld	hl,monde1
	ld	de,monde
	ld	bc,32*20
	ldir
	ld	bc,12
	ld	hl,ia_identliste
	xor	a
	ld	(hl),a
	ld	de,ia_identliste+1
	ldir

	ei

.end