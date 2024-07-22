;+---------------------------+
;|       D O O M  8 3        |
;+---------------------------+
;|Routine de tracé de rayons.|
;|Elle utilise l'algorithme  |
;|de Bresenheim pour tracer  |
;|des rayons du personnage à |
;|une distance de 10 u sur un|
;|champ de vision de 90°.    |
;+----------------------+----+
;|Alexis GUINAMARD      |v0.9|
;+----------------------+----+

rayons:
	ld	hl,(xperso_v)		;prend les coordonnées entières du perso
	ld	a,h
	ld	(xperso_e),a
	ld	hl,(zperso_v)
	ld	a,h
	ld	(zperso_e),a
	xor	a			;initialise le numéro du rayon
	ld	(numrayon),a
	ld	a,(orientation)		;initialise l'angle du rayon
	sub	16
	or	a
	jp	m,retangle
	ld	(anglerayon),a

choixroutine:
	ld	a,(anglerayon)		;choisit la routine à utiliser 
	cp	15
	jp	m,moinsque15
	cp	30			;en fonction de l'angle du rayon
	jp	m,moinsque30
	cp	45
	jp	m,moinsque45	
	cp	60			
	jp	m,moinsque60
	cp	75
	jp	m,moinsque75
	cp	90
	jp	m,moinsque90
	cp	105
	jp	m,moinsque105
	jp	plusque105

;^°¤.¤°^°¤.¤°^°¤.¤°^°¤.¤° Moins que 15 u °^°¤.¤°^°¤.¤°^°¤.¤°^°¤.
moinsque15:
	ld	hl,matricemonde
	ld	a,h
	ld	(incx_15+2),a
	ld	a,l
	ld	(incx_15+1),a
	jp	routine1
;^°¤.¤°^°¤.¤°^°¤.¤°^°¤.¤° Moins que 30 u °^°¤.¤°^°¤.¤°^°¤.¤°^°¤.
moinsque30:
	ld	hl,matricemonde
	ld	a,h
	ld	(incz_30+2),a
	ld	a,l
	ld	(incz_30+1),a
	jp	routine2
;^°¤.¤°^°¤.¤°^°¤.¤°^°¤.¤° Moins que 45 u °^°¤.¤°^°¤.¤°^°¤.¤°^°¤.
moinsque45:
	ld	hl,matricemonde60
	ld	a,h
	ld	(incz_30+2),a
	ld	a,l
	ld	(incz_30+1),a
	jp	routine2
;^°¤.¤°^°¤.¤°^°¤.¤°^°¤.¤° Moins que 60 u °^°¤.¤°^°¤.¤°^°¤.¤°^°¤.
moinsque60:
	ld	hl,matricemonde60
	ld	a,h
	ld	(incx_15+2),a
	ld	a,l
	ld	(incx_15+1),a
	jp	routine1
;^°¤.¤°^°¤.¤°^°¤.¤°^°¤.¤° Moins que 75 u °^°¤.¤°^°¤.¤°^°¤.¤°^°¤.
moinsque75:
	ld	hl,matricemonde90
	ld	a,h
	ld	(incx_15+2),a
	ld	a,l
	ld	(incx_15+1),a
	jp	routine1
;^°¤.¤°^°¤.¤°^°¤.¤°^°¤.¤° Moins que 90 u °^°¤.¤°^°¤.¤°^°¤.¤°^°¤.
moinsque90:
	ld	hl,matricemonde90
	ld	a,h
	ld	(incz_30+2),a
	ld	a,l
	ld	(incz_30+1),a
	jp	routine2
;^°¤.¤°^°¤.¤°^°¤.¤°^°¤.¤° Moins que 105 u °^°¤.¤°^°¤.¤°^°¤.¤°^°¤.
moinsque105:
	ld	hl,matricemonde120
	ld	a,h
	ld	(incz_30+2),a
	ld	a,l
	ld	(incz_30+1),a
	jp	routine2
;^°¤.¤°^°¤.¤°^°¤.¤°^°¤.¤° Plus que 105 u °^°¤.¤°^°¤.¤°^°¤.¤°^°¤.
plusque105:
	ld	hl,matricemonde120
	ld	a,h
	ld	(incx_15+2),a
	ld	a,l
	ld	(incx_15+1),a
	jp	routine1

;^°¤.¤°^°¤.¤°^°¤.¤°^°¤.¤° Routine n° 1 °^°¤.¤°^°¤.¤°^°¤.¤°^°¤.¤°
routine1:
	xor	a
	ld	(zray),a
	ld	(xray),a
	ld	a,(anglerayon)
	ld	hl,dxrayon_l
	ld	d,0
	ld	e,a
	add	hl,de
	ld	a,(hl)			;va chercher les accroissements dx et dz
	ld	(dx),a			;du rayon à tracer et calcule S=-dx/2
	sra	a
	neg
	ld	(S),a
	ld	hl,dzrayon_l
	sbc	hl,de
	ld	a,(hl)
	ld	(dz),a
trace15:
	ld	a,(xray)
	ld	b,a
	ld	a,(dx)			;while xray<dx do goto sub_30
	cp	b
	jp	p,incx_15
	jp	nouveaurayon
incx_15:
	call	$0000			;valeur générée en fonction de l'angle (matricemondexx)
	ld	hl,xray		;vérifier si a, b ou c...est utilisé dans matricemonde
	inc	(hl)			; xray=xray+1
	ld	hl,S
	ld	a,(dz)			;S=S+dz
	add	a,(hl)
	ld	(hl),a
	or	a
	jp	m,trace15
incy_15:
	ld	hl,zray
	inc	(hl)			;zray=zray+1
	ld	a,(dx)
	ld	b,a
	ld	a,(S)			;S=S-dx
	sub	b
	ld	(S),a
	jp	trace15

;^°¤.¤°^°¤.¤°^°¤.¤°^°¤.¤°Routine n° 2 °^°¤.¤°^°¤.¤°^°¤.¤°^°¤.¤°
routine2:
	xor	a			;initialise z et xray à 0
	ld	(zray),a
	ld	(xray),a
	ld	a,(anglerayon)
	ld	hl,dxrayon_l
	ld	d,0
	ld	e,a
	add	hl,de
	ld	a,(hl)			;va chercher les accroissements dx et dz
	ld	(dx),a			;du rayon à tracer et calcule S=-dz/2
	ld	hl,dzrayon_l-1
	sbc	hl,de
	ld	a,(hl)
	ld	(dz),a
	sra	a
	neg
	ld	(S),a
trace30:
	ld	a,(zray)
	ld	b,a
	ld	a,(dz)			;while zray<dz do goto sub_30
	cp	b
	jp	p,incz_30
	jp	nouveaurayon
incz_30:
	call	$0000			;valeur générée en fonction de l'angle (matricemondexx)
	ld	hl,zray			;vérifier si a, b ou c...est utilisé dans matricemonde
	inc	(hl)			; zray=zray+1
	ld	hl,S
	ld	a,(dx)			;S=S+dx
	add	a,(hl)
	ld	(hl),a
	or	a
	jp	m,trace30
incx_30:
	ld	hl,xray
	inc	(hl)			;xray=xray+1
	ld	a,(dz)
	ld	b,a
	ld	a,(S)			;S=S-dz
	sub	b
	ld	(S),a
	jp	trace30

;^°¤.¤°^°¤.¤°^°¤.¤°^°¤.¤°Routines diverses °^°¤.¤°^°¤.¤°^°¤.¤°^°¤.¤°
nouveaurayon:
	ld	hl,numrayon
	inc	(hl)
	ld	a,32
	cp	(hl)
	jp	m,finrayons
	ld	a,(n_sprite)		;réinitialisation de l'ordonnée de la liste des
	ld	(n_spritea),a		;sprites (pour ne pas afficher 2* la même...)
	or	a
	jp	z,suite_nouveaurayon
	ld	b,0
	ld	c,4
	push	bc
	ld	hl,listex_sprite
	ld	de,listex_sprite2
	ldir				;copie les coordonnées des sprites du rayon actuel 
	pop	bc			;dans la liste 2 (dernier rayon)
	push	bc
	ld	hl,listez_sprite
	ld	de,listez_sprite2
	ldir
	pop	bc			;dans la liste 2 (dernier rayon)
	ld	hl,listesprite_ident
	ld	de,listesprite_ident2
	ldir


suite_nouveaurayon:
	xor	a
	ld	(n_sprite),a
	ld	hl,anglerayon
	inc	(hl)
	ld	a,120
	cp	(hl)
	jp	z,nouveauray_2		;incremente l'angle sauf si il est égal à 120, dans ce 
	jp	choixroutine		;cas, anglerayon=1 
nouveauray_2:
	xor	a
	ld	(hl),a			;réinitialise anglerayon=0
	jp	moinsque30
	
retangle:
	ld	b,120
	add	a,b			;réinitialise anglerayon
	ld	(anglerayon),a
	jp	choixroutine

matricemonde:
	ld	hl,xray
	ld	a,(xperso_e)
	add	a,(hl)
	ld	b,a
	ld	hl,zray
	ld	a,(zperso_e)
	add	a,(hl)
	ld	c,a
	call	lecturemonde
	call	verifmur
	ret

matricemonde60:
	ld	a,(xray)
	ld	b,a
	ld	a,(xperso_e)
	sub	b
	ld	b,a
	ld	hl,zray
	ld	a,(zperso_e)
	add	a,(hl)
	ld	c,a
	call	lecturemonde
	call	verifmur
	ret

matricemonde90:
	ld	a,(xray)	
	ld	b,a
	ld	a,(xperso_e)
	sub	b
	ld	b,a
	ld	a,(zray)
	ld	c,a
	ld	a,(zperso_e)
	sub	c
	ld	c,a
	call	lecturemonde
	call	verifmur
	ret

matricemonde120:
	ld	hl,xray
	ld	a,(xperso_e)
	add	a,(hl)
	ld	b,a
	ld	a,(zray)
	ld	c,a
	ld	a,(zperso_e)
	sub	c
	ld	c,a
	call	lecturemonde
	call	verifmur
	ret

;^°¤.¤°^°¤.¤°^°¤.¤°^°¤.¤°Lecture monde °^°¤.¤°^°¤.¤°^°¤.¤°^°¤.¤°
lecturemonde:
	push	bc				;hl=monde+ c*20+b					
	ld	e,c
	ld	d,0
	ld	h,d
	ld	l,e
	add	hl,hl
	add	hl,hl
	push	hl
	add	hl,hl
	add	hl,hl
	pop	de
	add	hl,de
	ld	c,b
	ld	b,0
	add	hl,bc
	ex	de,hl
	ld	hl,monde
	add	hl,de
	ld	a,(hl)
	pop	de
	ret

verifmur:
	or	a
	ret	z
	ld	(tempmonstre),de
	ld	(matnum),a
	cp	1
	jp	z,aff_mur
	cp	32
	jp	p,monstre_aff_gest
	jp	sprite_aff
	
aff_mur:
	ld	hl,(tempcoo)
	bcall(_cphlde)
	jp	z,fin1

suiteaff_mur:
	ld	(tempcoo),de
	ld	hl,listex
	ld	a,(dimention)
	ld	b,0
	ld	c,a
	add	hl,bc
	ld	a,d
	ld	(hl),a
	ld	hl,listez
	add	hl,bc
	ld	a,e
	ld	(hl),a
	ld	hl,dimention
	inc	(hl)
fin1:
	pop	hl
	pop	hl
	jp	nouveaurayon

sprite_aff:
	ld	a,(n_spritea)
	or	a
	jp	z,suiteaffsprite
	ld	hl,listex_sprite2
	ld	b,a
	ld	a,d
sprite_aff2:
	cp	(hl)
	jp	z,suiteverifsprite
sprite_aff22:
	inc	hl
	djnz	sprite_aff2
suiteaffsprite:
	call	ecriturelistesprite
	jp	spritesaff
suiteverifsprite:
	push	hl
	push	bc
	ld	bc,listez_sprite2-listex_sprite2
	add	hl,bc
	ld	a,e
	cp	(hl)
	pop	bc				;inversion hl<=>bc virée
	pop	hl
	jp	z,ecriturelistesprite
	ld	a,d
	jp	sprite_aff22
ecriturelistesprite:
	ld	a,(n_sprite)
	ld	hl,listex_sprite
	ld	c,a
	ld	b,0
	add	hl,bc
	ld	(hl),d
	ld	hl,listez_sprite
	add	hl,bc
	ld	(hl),e
	ld	hl,listesprite_ident
	add	hl,bc
	ld	(hl),b					;(hl)=b=0
	inc	a
	ld	(n_sprite),a
retoursprite:
finrayons:
	ret

monstre_aff_gest:
	;ld	h,a
	ld	a,(n_spritea)
	or	a
	jp	z,monstre_verifia
	ld	c,a					;vérification de la présence du monstre sur
 	ld	b,0					;le dernier rayon
	ld	a,(matnum)
	ld	hl,listesprite_ident
	cpir
	jp	z,ecriturelistemonstre
	

monstre_verifia:
	xor	a
	ld	a,(nmonstres)
	ld	b,monstres_vie-ia_identliste-1
	
	;inc	a
	;ld	c,(nmonstres)	;?????????????
			;vérification de la gestion du monstre 					;dans l'IA
	ld	a,(matnum)
	ld	c,a
	ld	hl,ia_identliste
boucleia:
	ld	a,(hl)
	or	a
	jp	z,placelibre
	cp	c
	jp	z,affmonstresansia
retplace:
	inc	hl
	djnz	boucleia				;le monstre n'est pas encore geré dans l'IA
	ld	a,(nmonstres)
	or	a
	ret	z
	
affmonstreia:
	;ld	a,(nmonstres)
	;ld	hl,ia_identliste
	;ld	c,a
	;ld	b,0
	;add	hl,bc
	ld	hl,(placelibrepointer)
	ld	a,(matnum)
	ld	(hl),a					;intégration de l'identité
	ld	bc,monstres_vie-ia_identliste	;intégration du monstre dans l'IA
	add	hl,bc
	ld	a,12					;initialise la vie du monstre
	ld	(hl),a

	add	hl,bc
	ld	a,$80					;initialise les coordonnées du monstre
	ld	(hl),d
	add	hl,bc
	ld	(hl),a
	add	hl,bc
	ld	(hl),e
	add	hl,bc
	ld	(hl),a
	add	hl,bc					;ini	sprite
	ld	(hl),15
	;ld	hl,nmonstres
	;ld	(hl),9
monstre_aff:	
	
	call	ecriturelistemonstre
	ld	a,4
	ld	(matnum),a
	jp	spritesaff

affmonstresansia:
	ld	a,monstres_vie-ia_identliste-1
	sub	b
	ld	(indexia),a				;place de ce monstre
	;ld	hl,spritemonstre
	;ld	b,0
	;ld	c,a
	;add	hl,bc
	;ld	a,(hl)
	;ld	(matnum),a
	call	ecriturelistemonstre
	ld	a,(indexia)
	ld	hl,spritemonstre
	ld	b,0
	ld	c,a
	add	hl,bc
	ld	a,(hl)
	ld	(matnum),a	
	jp	spriteaffv

ecriturelistemonstre:
	ld	a,(n_sprite)
	ld	hl,listex_sprite
	ld	c,a
	ld	b,0
	add	hl,bc
	ld	(hl),d
	ld	hl,listez_sprite
	add	hl,bc
	ld	(hl),e
	ld	hl,listesprite_ident
	add	hl,bc
	ld	a,(matnum)
	ld	(hl),a					;(hl)=a=monstrident
	inc	c
	ld	a,c
	ld	(n_sprite),a
	ret
placelibre:
	ld	(placelibrepointer),hl
	push	af
	ld	a,10
	ld	(nmonstres),a
	pop	af
	jp	retplace
.end
