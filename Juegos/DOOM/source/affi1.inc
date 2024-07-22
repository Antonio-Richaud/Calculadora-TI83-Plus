;------------= DOOM =------------
;10/11/2001 
;Raphaël SIRYANI
;Affichage des murs grace la la liste de points
;version 0.80
;---------------------------------------

Calculdesmurs:
	
										;///////////// vrai debut!
	ld	a,120
	ld	hl,orientation
	sub	(hl)
	ld	(orientation2),a		;360-orientation2
	
	xor	a
	
	

	ld	(increment),a
	
;///////////////////////////////////////
;trouve y du 1er point
;//////////////////////////////////////
	
	ld	hl,listex
	call	lecture_liste
	ld	bc,8
	add	hl,bc
	ld	de,(xperso)
	sbc	hl,de			;listex(compteur)-xperso=variationx(16)
	ld	(variationx),hl
	

	
	ld	a,(increment)
	ld	hl,listez
	call	lecture_liste
	ld	bc,8
	add	hl,bc
	ld	de,(zperso)
	sbc	hl,de			;listez(compteur)-zperso=variationz(16)
	ld	(variationz),hl
	


	call	calcul_x_y
	
	
	
	
	ld	hl,(tempsmur)
	ld	h,a
	ld	(anposmur),hl
	ld	hl,increment
	inc	(hl)
	
		
;///////////////////////////////////////
;fin
;//////////////////////////////////////


	

boucle_1:	
	
	
	
	xor	a
	ld	(tempcouille),a

	call	decouilleur
	ld	a,(increment)
	ld	hl,listex
	call	lecture_liste
	ld	bc,8
	add	hl,bc
	ld	de,(xperso)
	sbc	hl,de			;listex(compteur)-xperso=variationx(16)
	ld	(variationx),hl
	

	
	ld	a,(increment)
	ld	hl,listez
	call	lecture_liste
	ld	bc,8
	add	hl,bc
	ld	de,(zperso)
	sbc	hl,de			;listez(compteur)-zperso=variationz(16)
	ld	(variationz),hl
	
	
	call	calcul_x_y
			
			
	ld	de,(anposmur)	;ancienne position du mur
	
	
	ld	hl,(tempsmur)
	ld	h,a
	ld	(anposmur),hl			;on sauvgarde les postions du mur

	ld	a,(tempcouille)
	or	a
	jp	nz,couilleaff

	push	de
	push	hl
	call  lineClipAndDraw	;on copy les lignes ds le graph
	
	
	pop hl
	pop de
	push	de
	push	hl
couilleaff:
	
	ld	b,l
	ld	a,63
	sub	b
	ld	e,a
	
	
	ld	d,h
	call  lineClipAndDraw		;verticale
	ld	a,(tempcouille)
	or	a
	jp	nz,couilleaff2

	pop hl
	pop de
	
	
	ld	b,l
	ld	a,63
	sub	b
	ld	l,a


	ld	b,e
	ld	a,63
	sub	b
	ld	e,a
	

	call  lineClipAndDraw



couilleaff2:
	
	ld	a,(dimention)
	ld	b,a
	
	ld	a,(increment)
	inc	a
	ld	(increment),a
	
	
	
	cp	b
	jp	m,boucle_1
	
	
     
	ret					;fin boucle
	

;///////////////////////////////////////////////////////////////////

monstres1:
	ld	hl,monstre01
	
	ld	(tempadsp),hl
	jp	suitesaff2
meurt:
	ld	hl,meurt01
	ld	(tempadsp),hl
	ld	a,6
	call	ecrituremat
	jp	suitesaff2

meurts2:
	ld	hl,meurt01
	ld	(tempadsp),hl
	ld	a,7
	call	ecrituremat
	jp	suitesaff2

meurts3:
	ld	hl,meurt01
	ld	(tempadsp),hl
	ld	a,8
	call	ecrituremat
	jp	suitesaff2

meurts4:
	ld	hl,meurt01
	ld	(tempadsp),hl
	ld	a,9
	call	ecrituremat
	jp	suitesaff2

meurts5:
	ld	hl,meurt01
	ld	(tempadsp),hl
	ld	a,-2
	call	ecrituremat
	jp	suitesaff2

cadavre:
	ld	hl,cadavre01
	ld	(tempadsp),hl
	jp	suitesaff2

arbre:
	ld	hl,arbre01
	ld	(tempadsp),hl
	jp	suitesaff2

tonneaux:
	ld	hl,tonneaux01
	ld	(tempadsp),hl
	jp	suitesaff2

soins:
	ld	hl,soins01
	ld	(tempadsp),hl
	jp	suitesaff2
munitionss:
	ld	hl,munitions01
	ld	(tempadsp),hl
	jp	suitesaff2
;mtire:
;	ld	hl,tire01
;	ld	(tempadsp),hl
;	jp	suitesaff2
drapeau:
	ld	hl,drapeau01
	ld	(tempadsp),hl
	jp	suitesaff2
spritesaff:
	ld	de,(tempmonstre)
		
	ld	h,0
	ld	l,d	
	add	hl,hl
	add	hl,hl
	add	hl,hl
	add	hl,hl		;on met x*16 dans hl
	ld	bc,8
	add	hl,bc
	ld	bc,(xperso)
	sbc	hl,bc			;x-xperso=variationx(16)
	ld	(variationx),hl
	

	
	ld	h,0
	ld	l,e	
	add	hl,hl
	add	hl,hl
	add	hl,hl
	add	hl,hl		; on met z*16 dans hl
	ld	bc,8
	add	hl,bc
	ld	bc,(zperso)
	sbc	hl,bc			;z-zperso=variationz(16)
	ld	(variationz),hl
spriteaff2v:
	ld	a,(matnum)
	cp	15
	jp	z,monstres1
	;cp	26
	;jp	z,mtire
	;cp	27
	;jp	z,mtire
	;cp	28
	;jp	z,mtire
	;cp	29
	;jp	z,mtire
	cp	5
	jp	z,meurt
	cp	6
	jp	z,meurts2
	cp	7
	jp	z,meurts3
	cp	8
	jp	z,meurts4
	cp	9
	jp	z,meurts5
	cp	10
	jp	z,arbre
	cp	11
	jp	z,tonneaux
	cp	-2
	jp	z,cadavre
	cp	-3
	jp	z,soins
	cp	-4
	jp	z,munitionss
	cp	-50
	jp	z,drapeau
	
	ret
	
suitesaff2:
	
	
	
	call	calcul_x_y		; dans tempsmur on a y dans "a" on a x
	
	
	
	ld	d,a
	ld	hl,(tempsmur)
	
	ld	a,l
	cp	-41
	ret	m
	or	a
	jp	m,sprite1
	cp	3
	jp	m,sprite2
	cp	8
	jp	m,sprite3
	cp	10
	jp	m,sprite4
	cp	13
	jp	m,sprite5
	cp	16
	jp	m,sprite6
	cp	19
	jp	m,sprite7
	cp	21
	jp	m,sprite8
	cp	24
	jp	m,sprite9
	ld	a,18
	ld	(spritenum),a

spritesuiteaff:
	
	call	lectureinfo
	;or	a
	;ret	z
	ld	(tempxt),a		;taillex/2
	sub	d
	neg
	or	a
	ret	m	
	
	;cp	-16			;virer
	;ret	m
	ld	e,a
	ld	a,(tempxt)
	sla	a
	add	a,e
	cp	96
	ret	p

	ld	a,(tempxt)
	sub	d
	neg

	push	hl
	push	af
	push	bc
	call	largesprite
	pop	bc
	pop	af
	pop	hl

	ld	b,a
	ld	a,(puissance)
	cp	1
	call	p,veriftire

	

	
	ret

spriteaffv:
	
	ld	a,(indexia)

	

	ld	hl,monstres_xe
	
	ld	b,0
	ld	c,a
	add	hl,bc
	ld	a,(hl)
	
	

	ld	d,a
	
	ld	bc,monstres_vie-ia_identliste
	add	hl,bc
	ld	a,(hl)
	

	ld	e,a
	ex	de,hl
	
	srl	h
	rr	l
	srl	h
	rr	l
	srl	h
	rr	l
	srl	h
	rr	l				;div hl par 16

	
	ld	bc,(xperso)
	sbc	hl,bc			;x-xperso=variationx(16)
	ld	(variationx),hl

	ld	a,(indexia)
	
	ld	hl,monstres_ze
	ld	b,0
	ld	c,a
	add	hl,bc
	ld	a,(hl)
	ld	d,a
	
	ld	bc,monstres_vie-ia_identliste
	add	hl,bc
	ld	a,(hl)
	ld	e,a
	ex	de,hl

	srl	h
	rr	l
	srl	h
	rr	l
	srl	h
	rr	l
	srl	h
	rr	l				;div hl par 16

	ld	bc,(zperso)
	sbc	hl,bc			;z-zperso=variationz(16)
	ld	(variationz),hl

	jp	spriteaff2v
veriftire:
	ld	a,(matnum)			;ds b on a x 
	cp	15
	ret	m
	ld	a,(tempxt)
 	sla	a		;lageur sprite
	add	a,b
	ld	c,a
	cp	40
	jp	p,droitetouche
	ret

droitetouche:
	ld	a,b
	cp	40
	jp	m,monstretouche
	ret

monstretouche:
	;ld	bc,(tempmonstre)	;coordonnes du monstre
	ld	a,c
	sub	3
	inc	l
	inc	l
	inc	l
	
	
	ld	b,5
	ld	c,1
	ld	ix,sang1 
	call	largesprite
	ld	a,(indexia)
	ld	d,a
	ld	hl,monstres_vie
	ld	b,0
	ld	c,a
	add	hl,bc
	ld	a,(puissance)				;ds (hl) vie du monstre
	ld	e,a
	sub	6
	or	a
	call	m,zeropui
	ld	(puissance),a
	
	ld	a,(hl)
	
	sub	e			;vie-puissance
	ld	(hl),a
	or	a
	

	jp	m,monstremort
	ret
zeropui:
	xor	a
	ret
monstremort:
	
	ld	hl,ia_identliste
	ld	e,d
	ld	d,0
	add	hl,de
	xor	a
	ld	(hl),a
	ld	a,5				;hl=monde+ c*20+b
	
ecrituremat:
	ld	bc,(tempmonstre)			;entree	a
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
	ld	(hl),a	
	ret

;///////////////////////////////////////////////////////////////////
lectureinfo:
	;ld	a,(matnum)
	;sub	2
	;ld	c,a
	;ld	b,0
	;ld	hl,spriteliste
	

	;add	hl,bc
	ld	hl,(tempadsp)
	
	;ld	c,(hl)
	;inc	hl
	;ld	b,(hl)
	ld	a,(spritenum)
	ld	c,a
	ld	b,0
	
	add	hl,bc

	ld	a,h
	ld	b,a
	ld	a,l
	ld	c,a
	
	ld	a,(bc)
	ld	l,a
	inc	bc
	ld	a,(bc)
	ld	h,a
	ld	b,(hl)	;height,nbr colonnes,ypos,xdecalage à corriger

	
	inc	hl
	ld	c,(hl)
	inc	hl
	ld	e,(hl)
	inc	hl
	ld	a,(hl)
	inc	hl
	
	ld	(tempsprite),hl
	ld	l,e
	ld	ix,(tempsprite)
	ret

sprite1:
	xor	a
	ld	(spritenum),a
	jp	spritesuiteaff

sprite2:
	ld	a,2
	ld	(spritenum),a
	jp	spritesuiteaff
	
sprite3:
	ld	a,4
	ld	(spritenum),a
	jp	spritesuiteaff

sprite4:
	ld	a,6
	ld	(spritenum),a
	jp	spritesuiteaff
sprite5:
	ld	a,8
	ld	(spritenum),a
	jp	spritesuiteaff
sprite6:
	ld	a,10
	ld	(spritenum),a
	jp	spritesuiteaff
sprite7:
	ld	a,12
	ld	(spritenum),a
	jp	spritesuiteaff
sprite8:
	ld	a,14
	ld	(spritenum),a
	jp	spritesuiteaff
sprite9:
	ld	a,16
	ld	(spritenum),a
	call	lectureinfo
	jp	spritesuiteaff


calcul_x_y:

	call	lecture_sin
	ld	hl,(variationz)
	call	multhl_par_a		;variationz*sin(orientation2)
	


	ld	b,h
	ld	c,l	

	call	lecture_cos
	ld	hl,(variationx)
	call	multhl_par_a		;variationx*cos(orientation2)
	
	
		
	sbc	hl,bc				;variationx*cos(orientation2)-variationz*sin(orientation2)
	call	divhlpar16
	ld	(varE),hl
	

		
	call hauteur_tab			;on a y du mur dans l	et dans tempsmur
	ld	h,0
	ld	(tempsmur),hl	
	
	
	
		
	call	lecture_cos		;dans a
	

	

	ld	hl,(variationz)
	call	multhl_par_a		;variationz*cos(orientation2)dans bc
	ld	b,h
	ld	c,l	
	
	


	call	lecture_sin
	ld	hl,(variationx)
	call	multhl_par_a		;variationx*sin(orientation2)
	
	
	
	


	add	hl,bc				;variationx*sin(orientation2)+variationz*cos(orientation2)
	call	divhlpar16
		

	ld	d,h
	ld	e,l
	

	ld	bc,(varE)			;de/bc	
	
	
	call	div_bc_par_de		;dans a on a x mur
	add	a,40
	ret


;///////////////////////////////////////////////////////////////////////////
;-----------------------------HL*A+HL--------------------------------------
;A,H,L,D,E,b detruits
;--------------------------------------------------------------------------
;**************************************************************************



multhl_par_a:		;hl*a=hl	utilise de
	cp	1
	ret	z
	or	a
	jp	z,zero
	bit	7,h		;test si hl est negatif
	jp	nz,hl_neg
	bit	7,a		;test si a est negatif
	jp	nz,a_neg
mult:
	ld	d,h
	ld	e,l
	dec	a

boucle_mult:
	add	hl,de
	dec	a
	or	a
	jp	nz,boucle_mult
	ret


hl_neg:
	bit	7,a		;test si a est negatif
	jp	nz,a_neg2
	ex	de,hl		;prend l'oppose de h
	ld	hl,0
	sbc	hl,de
	ld	d,h
	ld	e,l
	dec	a

boucle_mult2:
		
	add	hl,de
	dec	a
	or	a
	jp	nz,boucle_mult2
	ex	de,hl		;prend l'oppose de h
	ld	hl,0
	sbc	hl,de
	ret
	
a_neg:
	neg		;prend la valeur absolue de a
	cp	1
	jp	z,oppose_de_hl
	ld	d,h
	ld	e,l
	dec	a

boucle_mult3:
	add	hl,de
	dec	a
	or	a
	jp	nz,boucle_mult3
	ex	de,hl		;prend l'oppose de hl
	ld	hl,0
	sbc	hl,de
	ret

a_neg2:
	neg		;prend la valeur absolue de a et hl
	cp	1
	jp	z,oppose_de_hl
	ex	de,hl
	ld	hl,0
	sbc	hl,de
	inc	hl
	jp	mult	
zero:
	ld	hl,0
	ret

oppose_de_hl:
	ex	de,hl
	ld	hl,0
	sbc	hl,de
	ret

;//////////////////////////////////////////////////////////////////////////////////////////////////////



;//////////////////////////////////////////////////////////////////////////////////////////////////////

;+----------------------------+
;|	 D O O M   8 3	      |
;+----------------------------+
;|Calcule bc/de*40	      |
;|bc et de étant compris      |
;|entre -160 et 160. Résultat |
;|compris entre 0 et 40 dans a|
;+----------------------+-----+
;|Alexis GUINAMARD	|v 1.0|
;+----------------------+-----+

;Il n'y a pour le moment pas de bug connu avec cette routine si vous 
;en trouvez un, doom83@fr.st


;recherche du signe du résultat
div_bc_par_de:

	
	push	bc
	push	de
	pop	bc
	pop	de

	xor	a
	cp	e
	call	z,divtest0
	bit	7,b
	jp	nz,bcneg_div
	bit	7,d
	jp	nz,deneg_div
	jp	positif

bcneg_div:
	ld	hl,0
	sbc	hl,bc
	
	ld	b,h
	ld	c,l
	bit	7,d
	jp	z,negatif
	jp	bcdeneg

deneg_div:

	ld	hl,0
	sbc	hl,de
	ld	d,h
	ld	e,l

negatif:

	ld	hl,1
	push	hl
	jp	suite_div

bcdeneg:

	ld	hl,0
	sbc	hl,de
	ld	d,h
	ld	e,l

positif:

	ld	hl,0
	push	hl

; Trouve le groupe auquel appartien |de| puis |bc|

	
suite_div:
	ld	h,b
	ld	l,c
	add	hl,hl
	add	hl,hl
	add	hl,hl
	push	hl
	add	hl,hl
	pop	bc
	add	hl,hl
	add	hl,bc	
Divide:
	ld c,l
	ld a,h
	ld hl,0 ;hl = remainder
	ld b,16 ;16 bits in dividend
	or a ;clear carry

DivLoop:
	rl c
	rla
	rl l
	rl h
	push hl
	sbc hl,de
	ccf
	jr c, Drop
	ex (sp),hl
Drop:
	inc sp
	inc sp
	djnz DivLoop
	ex de,hl
	rl c
	ld l,c
	rla
	ld h,a
	or a
	
	push	hl
	ld	de,80
	sbc	hl,de
	pop	hl
	call	p,divmax
	ld	a,l
	


	pop	hl
	bit	0,l
	jp	nz,neg_div
	ret
divmax:
	ld	l,80
	ret
neg_div:
	neg
	ret	
divtest0:
	cp	d
	jr	z,divtest02
	ret
divtest02:
	ld	a,80
	pop	hl
	ret





;/////////////////////////////////////////////////////////////////////////////////////////////////


lecture_cos:
	ld	hl,cosinus
  	ld	a,(orientation2)
	ld	e,a      	;a position//utilise e,d,h,l,a
  	ld	d,0     
  	add	hl,de   	; ajoute la position dans la liste 
 	ld	a,(hl)   	; va chercher la valeur et la met dans l
 	ret 

lecture_sin:
	ld	hl,sinus
  	ld	a,(orientation2)
	ld	e,a      	;a position//utilise e,d,h,l,a
  	ld	d,0     
  	add	hl,de   	; ajoute la position dans la liste 
 	ld	a,(hl)   	; va chercher la valeur et la met dans l
 	ret 

lecture_liste:
	
  	ld	e,a      	;a position//utilise e,d,h,l,a
  	ld	d,0     
  	add	hl,de   	; ajoute la position dans la liste 
 	ld	l,(hl)   	; va chercher la valeur et la met dans l
 	ld	h,0		;hl*16 44 cycles!
	add	hl,hl
	add	hl,hl
	add	hl,hl
	add	hl,hl		;on a la valeur dans hl
	ret

hauteur_tab:
	bit	7,h		;test si hl est negatif
	jp	nz,hl_neg_haut
	ld	e,l      	;a position//utilise e,d,h,l,a
  	ld	d,0     
  	ld	hl,hauteurdesmurs
	add	hl,de   	; ajoute la position dans la liste 
 	ld	l,(hl)   	; va chercher la valeur et la met dans l
	ret

hl_neg_haut:
	ex	de,hl		;prend l'oppose de hl
	ld	hl,0
	sbc	hl,de
	ld	e,l      	;a position//utilise e,d,h,l,a
  	ld	d,0     
  	ld	hl,hauteurdesmurs
	add	hl,de   	; ajoute la position dans la liste 
 	ld	l,(hl)   	; va chercher la valeur et la met dans l
	ret


divhlpar16:
	bit	7,h		;test si hl est negatif
	jp	nz,hl_neg16
	srl	h
	rr	l
	srl	h
	rr	l
	srl	h
	rr	l
	srl	h
	rr	l
	ret

hl_neg16:
	ex	de,hl	;prend l'oppose
	ld	hl,0
	sbc	hl,de
	srl	h
	rr	l
	srl	h
	rr	l
	srl	h
	rr	l
	srl	h
	rr	l
	ex	de,hl	;prend l'oppose
	ld	hl,0
	sbc	hl,de
	ret


decouilleur:
	;ld	hl,(variationx)	;quand on est trop loing on desactive le decouilleur
	;ld	de,112


				;bcall(_cphlde)
	;sbc	hl,de
	;ret	p
	
	;ld	hl,(variationz)
	;sbc	hl,de		;bcall(_cphlde)
	;ret	p
	
	
	ld	hl,listex	;on est pas trop loing...
	ld	a,(increment)
	cp	1
	ret	m
	ld	e,a      	;a position//utilise e,d,h,l,a	
	
  	ld	d,0     
  	add	hl,de   	; ajoute la position dans la liste 
 	ld	c,(hl)   	; va chercher la valeur et la met dans c
	
	dec	hl
	ld	a,(hl)
	;or	a
	;ret	z
		

	sub	c
	bit	7,a
	call	nz,neg_div

	ld	b,a

	
	
	
	ld	hl,listez
	ld	a,(increment)	
	ld	e,a      	;a position//utilise e,d,h,l,a
  	ld	d,0     
  	add	hl,de   	; ajoute la position dans la liste 
 	ld	c,(hl)   	; va chercher la valeur et la met dans c
	
	dec	hl
	ld	a,(hl)
	;or	a
	;ret	z
		

	sub	c
	bit	7,a
	call	nz,neg_div
	add	a,b
	
	
	cp	2
	jp	z,couille_verif	
	jp	p,couille	
	
	ret

couille:
	

	ld	a,1
	ld	(tempcouille),a
	ret

couille_verif:					;il faut savoir si c'est sur x ou sur z qu'on a une couille

	ld	hl,listex	
	ld	a,(increment)
	ld	e,a      	;a position//utilise e,d,h,l,a
  	ld	d,0     
  	add	hl,de   	; ajoute la position dans la liste 
 	ld	c,(hl)   	; va chercher la valeur et la met dans c
	
	dec	hl
	ld	a,(hl)
	ld	e,a

	sub	c
	bit	7,a
	call	nz,neg_div
	cp	2
	jp	z,couille_x
	


	ld	a,c		
	ld	b,a	

	
	
	ld	hl,listez	
	ld	a,(increment)	
	ld	e,a      	;a position//utilise e,d,h,l,a
  	ld	d,0     
  	add	hl,de   	; ajoute la position dans la liste		
	ld	a,(hl)
	dec	hl
	ld	c,(hl)

	ld	e,a

	sub	c		;on verifie si ça couille sur z
	bit	7,a
	call	nz,neg_div
	cp	2
	ret	nz
	ld	a,e

	add	a,c
	sra	a	
	ld	c,a
	
suite_couille:
	call lecturemonde	;dans bc on a les coordonnées	
	cp	1
	ret	z
	ld	a,1
	ld	(tempcouille),a
	ret

couille_x:
	
	ld	a,e
	add	a,c	
	sra	a	
	ld	b,a	
	
	
	ld	hl,listez	
	ld	a,(increment)	
	ld	e,a      	;a position//utilise e,d,h,l,a
  	ld	d,0     
  	add	hl,de   	; ajoute la position dans la liste 
	ld	a,(hl)	
	ld	c,a
	
	jp	suite_couille
SQUOT:
 .db 0
SREM:
  .db 0

	.end
