;+--------------------------+
;|	D O O M   8 3 	    |
;+--------------------------+
;|Routine de déplacement du |
;|personnage. Permet de se  |
;|déplacer dans toutes les  |
;|directions de straffer    |
;|et de courir...           |
;+-------------------+------+
;|Alexis GUINAMARD   | v 1.0|
;+-------------------+------+



deplacement:
	exx
	push	af
	ld	a,(compteurinterrup)
	dec	a
	ld	(compteurinterrup),a
	jp	nz,findep2

	ld	hl,(xperso_v)
	ld	(xpersovieux),hl		;sauvegarde les anciennes coordonnées du perso
	ld	hl,(zperso_v)
	ld	(zpersovieux),hl

;gestion des touches pressées par le direct input


		
	
	ld	a,0FFh
	out	(1),a
	ld	a,0BFh
	out	(1),a
	in	a,(1)
	bit	5,a
	call	z,tirer				;pour tirer [2nd]
	bit	1,a
	call	z,straffg			;straff à gauche [Y=]
	bit	0,a
	call	z,straffd			;straff à droite [WINDOW]
	
	bit	4,a
	call	z,arme1				;arme 1 [Y=]
	bit	3,a
	call	z,arme2				;arme 2 [WINDOW]
	
	ld	a,$FF
	out	(1),a
	ld	a,0feh
	out	(1),a
	in	a,(1)				;gestion de plusieurs touches simultanément
	bit	0,a				;ici, c'est la gestion du déplacement (flèches)
	call	z,bas				;[bas]
	bit	1,a
	call	z,droite			;[->]
	bit	2,a
	call	z,gauche			;[<-]
	bit	3,a
	call	z,haut				;[haut]


	
	ld	hl,(xperso_v)
	srl	h	
	rr	l
	srl	h
	rr	l
	srl	h
	rr	l
	srl	h
	rr	l
	ld	(xperso),hl			;met à jour xperso et zperso pour 
	ld	hl,(zperso_v)			;la routine d'affichage
	srl	h	
	rr	l
	srl	h
	rr	l
	srl	h
	rr	l
	srl	h
	rr	l
	ld	(zperso),hl

	ld	a,$FF
	out	(1),a				;pour courir [ALPHA]
	ld	a,$DF
	out	(1),a
	in	a,(1)
	sll	a				;cp 127
	jp	nc,courir
	ld	a,10
	ld	(compteurinterrup),a

						
findep2:

	ld	a,$08				; je sais pas si ca sert le 1er out 
	out	($03),a
	ld	a,$0F	
	out	($03),a	
		
	pop	af
	exx
	ei
	reti
	;jp	$38			;fin de la routine de deplacement
tirer:
	push	af
	ld	a,(munitionsv)
	or	a
	jp	z,fintire
	
rechargement:
	ld	a,(tire)
rechargement1:
	cp	-10
	jp	p,fintire
rechargement2:
	ld	a,2
	ld	(tire),a
	ld	hl,munitionsv
	dec	(hl)
rechargement3:
	
	ld	a,2
	ld	(puissance),a
fintire:
	pop	af
	ret
;////code genere
arme1:
	ld	hl,rechargement1+1
	ld	(hl),-9
	ld	hl,rechargement2+1
	ld	(hl),4
	ld	hl,rechargement3+1
	ld	(hl),2

	ld	hl,idle+1
	ld	(hl),-9
	ld	hl,idlecinq+1
	ld	(hl),-10

	ld	hl,idle2+1
	ld	(hl),33
	inc	hl
	inc	hl
	ld	(hl),46
	inc	hl
	inc	hl
	ld	(hl),18
	inc	hl
	inc	hl
	ld	(hl),2
	inc	hl
	inc	hl
	inc	hl
	ld	de,pistol
	ld	(hl),e
	inc	hl
	ld	(hl),d

	ld	hl,feu2+1
	ld	(hl),27
	inc	hl
	inc	hl
	ld	(hl),38
	inc	hl
	inc	hl
	ld	(hl),26
	inc	hl
	inc	hl
	ld	(hl),3
	inc	hl
	inc	hl
	inc	hl
	ld	de,pistol2
	ld	(hl),e
	inc	hl
	ld	(hl),d

	ret
	
arme2:
	ld	hl,rechargement1+1
	ld	(hl),-1
	ld	hl,rechargement2+1
	ld	(hl),2
	ld	hl,rechargement3+1
	ld	(hl),6

	
	ld	hl,idle+1
	ld	(hl),-1
	ld	hl,idlecinq+1
	ld	(hl),-2

	ld	hl,idle2+1
	ld	(hl),35
	inc	hl
	inc	hl
	ld	(hl),52
	inc	hl
	inc	hl
	ld	(hl),12
	inc	hl
	inc	hl
	ld	(hl),2
	inc	hl
	inc	hl
	inc	hl
	ld	de,mitra
	ld	(hl),e
	inc	hl
	ld	(hl),d

	ld	hl,feu2+1
	ld	(hl),21
	inc	hl
	inc	hl
	ld	(hl),33
	inc	hl
	inc	hl
	ld	(hl),31
	inc	hl
	inc	hl
	ld	(hl),5
	inc	hl
	inc	hl
	inc	hl
	ld	de,mitrafeu
	ld	(hl),e
	inc	hl
	ld	(hl),d

	ret


haut:
;fait avancer le personnage.
	push	af
	ld	a,(orientation)
	cp	30
	jp	m,haut30
	cp	60
	jp	m,haut60
	cp	90
	jp	m,haut90
	jp	haut120
	
bas:
;fait reculer le personnage.
	push	af
	ld	a,(orientation)
	cp	30
	jp	m,haut90
	cp	60
	jp	m,haut120
	cp	90
	jp	m,haut30
	jp	haut60

straffd:
;fait straffer le personnage (droite).
	push	af
	ld	a,(orientation)
	add	a,30
	cp	120
	call	p,retangle_straff
	cp	30
	jp	m,haut30
	cp	60
	jp	m,haut60
	cp	90
	jp	m,haut90
	jp	haut120

straffg:
;fait straffer le personnage (gauche).
	push	af
	ld	a,(orientation)
	add	a,30
	cp	120
	call	p,retangle_straff
	cp	30
	jp	m,haut90
	cp	60
	jp	m,haut120
	cp	90
	jp	m,haut30
	jp	haut60


haut30:
	ld	hl,cosinus_ns
	ld	c,a
	ld	b,0
	add	hl,bc	
	ld	a,(hl)
	ld	h,b
	ld	l,a
	ld	de,(xperso_v)
	add	hl,de
	ld	(xperso_v),hl
	ld	hl,sinus_ns
	add	hl,bc
	ld	a,(hl)
	ld	h,b
	ld	l,a
	ld	de,(zperso_v)
	add	hl,de
	ld	(zperso_v),hl
	jp	verifdeplacement

haut60:
	ld	hl,cosinus_ns
	ld	c,a
	ld	b,0
	add	hl,bc	
	ld	a,(hl)
	ld	d,b
	ld	e,a
	ld	hl,(xperso_v)
	sbc	hl,de
	ld	(xperso_v),hl
	ld	hl,sinus_ns
	add	hl,bc
	ld	a,(hl)
	ld	h,b
	ld	l,a
	ld	de,(zperso_v)
	add	hl,de
	ld	(zperso_v),hl
	jp	verifdeplacement

haut90:
	ld	hl,cosinus_ns
	ld	c,a
	ld	b,0
	add	hl,bc	
	ld	a,(hl)
	ld	d,b
	ld	e,a
	ld	hl,(xperso_v)
	sbc	hl,de
	ld	(xperso_v),hl
	ld	hl,sinus_ns
	add	hl,bc
	ld	a,(hl)
	ld	d,b
	ld	e,a
	ld	hl,(zperso_v)
	sbc	hl,de
	ld	(zperso_v),hl
	jp	verifdeplacement

haut120:
	ld	hl,cosinus_ns
	ld	c,a
	ld	b,0
	add	hl,bc	
	ld	a,(hl)
	ld	d,b
	ld	e,a
	ld	hl,(xperso_v)
	add	hl,de
	ld	(xperso_v),hl
	ld	hl,sinus_ns
	add	hl,bc
	ld	a,(hl)
	ld	d,b
	ld	e,a
	ld	hl,(zperso_v)
	sbc	hl,de
	ld	(zperso_v),hl
	jp	verifdeplacement

	
gauche:

	push	af
	ld	a,(orientation)
	cp	120
	jp	z,retorientation_1
	jp	p,retorientation_1
	inc	a
	ld	(orientation),a
	pop	af
	ret

droite:
	
	push	af
	ld	a,(orientation)
	dec	a
	jp	z,retorientation_2
	jp	m,retorientation_2
	ld	(orientation),a
	pop	af
	ret

courir:
	ld	a,6
	ld	(compteurinterrup),a
	jp	findep2

	
;.¤°^°¤.¤°^°¤.¤°^°¤. Routines diverses.¤°^°¤.¤°^°¤.¤°^°¤.¤°^°¤.

retorientation_1:
	
	ld	a,2
	ld	(orientation),a
	pop	af
	ret

retorientation_2:

	ld	a,120
	ld	(orientation),a
	pop	af
	ret

retangle_straff:
	sub	120
	ret

verifdeplacement
	xor	a
	ld	(vardepl),a
	ld	hl,(zperso_v)
	ld	c,h
	ld	hl,(zpersovieux)
	ld	a,h
	cp	c
	call	nz,verifzperso
verifdepl2:
	ld	hl,(xperso_v)
	ld	b,h
	ld	hl,(xpersovieux)
	ld	a,h
	cp	b
	call	nz,verifxperso	

verifdepl3:
	ld	a,(vardepl)
	or	a
	jp	z,finverifdepl
	call	lecturemonde
	or	a
	jp	z,finverifdepl
	jp	p,retcoordonnées
	cp	-3
	jp	z,addvie
	cp	-4
	jp	z,addmuni
	cp	-50
	jp	z,gagner
	cp	-6
	jp	z,sombre
	cp	-5
	jp	z,lumineux
finverifdepl:
	pop	af	
	ret

addvie:
	
	ld	a,(vie)
	cp	30
	jp	p,finverifdepl
	ld	(hl),0
	add	a,5
	ld	(vie),a
	pop	af	
	ret

addmuni:
	ld	a,(munitionsv)
	or	a
	jp	m,finverifdepl
	ld	(hl),0
	add	a,20
	ld	(munitionsv),a
	pop	af
	ret
verifxperso:

	ld	hl,vardepl
	set	1,(hl)
	ret

verifzperso:

	ld	hl,vardepl
	set	2,(hl)
	ret

retcoordonnées:

	ld	a,(vardepl)
	bit	1,a
	call	nz,retxperso
	bit	2,a
	call	nz,retzperso
	jp	finverifdepl

retxperso:
	ld	hl,(xpersovieux)
	ld	b,a
	ld	a,l
	and	%11110000			;ne garde que les 4 premiers bits de la virgule
	ld	l,a
	ld	de,(xperso_v)
	ld	a,e
	and	%00001111
	add	a,l
	ld	l,a
	ld	(xperso_v),hl
	ld	a,b
	ret
retzperso:
	ld	hl,(zpersovieux)
	ld	a,l
	and	%11110000			;ne garde que les 4 premiers bits de la virgule
	ld	l,a
	ld	de,(zperso_v)
	ld	a,e
	and	%00001111
	add	a,l
	ld	l,a
	ld	(zperso_v),hl
	ret


sombre:
	ld	a,$FB
	out	($10),a
	pop	af
	ret
lumineux:
	ld	a,(cont)
	add	a,216
	;or	$C0
	out	($10),a
	pop	af
	ret

gagner:
	;por être sur que les pages mémoire entre 4000 et cfff sont
	;bien la ram....
#ifdef TI83P

mempage1: ld	a,$0
	out	(6),a
mempage2:ld	a,$0
	out	(7),a 
#endif

	pop	hl
	ld	hl,gagné2
	push	hl
	reti

gagnét:
	.db "GAGNE !!",0
niveau2:
	.db "NIVEAU 2",0
niveau3:
	.db "NIVEAU 3",0

.end