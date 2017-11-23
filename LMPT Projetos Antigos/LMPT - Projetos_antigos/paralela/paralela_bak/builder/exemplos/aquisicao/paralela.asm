	.386p
	ifdef ??version
	if    ??version GT 500H
	.mmx
	endif
	endif
	model flat
	ifndef	??version
	?debug	macro
	endm
	endif
	?debug	S "C:\paghi\paralela\exemplos\aquisicao\paralela.cpp"
	?debug	T "C:\paghi\paralela\exemplos\aquisicao\paralela.cpp"
_TEXT	segment dword public use32 'CODE'
_TEXT	ends
_DATA	segment dword public use32 'DATA'
_DATA	ends
_BSS	segment dword public use32 'BSS'
_BSS	ends
$$BSYMS	segment byte public use32 'DEBSYM'
$$BSYMS	ends
$$BTYPES	segment byte public use32 'DEBTYP'
$$BTYPES	ends
$$BNAMES	segment byte public use32 'DEBNAM'
$$BNAMES	ends
$$BROWSE	segment byte public use32 'DEBSYM'
$$BROWSE	ends
$$BROWFILE	segment byte public use32 'DEBSYM'
$$BROWFILE	ends
DGROUP	group	_BSS,_DATA
_TEXT	segment dword public use32 'CODE'
@OutPortB$quiui	segment virtual
@@OutPortB$quiui	proc	near
?live16385@0:
	?debug L 1
	push      ebp
	mov       ebp,esp
	?debug L 3
@1:
	mov       dx,word ptr [ebp+8]
	?debug L 4
	mov       ax,word ptr [ebp+12]
	?debug L 10
	out	 dx, al
	?debug L 12
@2:
	pop       ebp
	ret 
	?debug L 0
@@OutPortB$quiui	endp
@OutPortB$quiui	ends
_TEXT	ends
$$BSYMS	segment byte public use32 'DEBSYM'
	db	2
	db	0
	db	0
	db	0
	dw	62
	dw	517
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dd	?patch1
	dd	?patch2
	dd	?patch3
	df	@@OutPortB$quiui
	dw	0
	dw	4096
	dw	0
	dw	1
	dw	0
	dw	0
	dw	0
	db	15
	db	64
	db	79
	db	117
	db	116
	db	80
	db	111
	db	114
	db	116
	db	66
	db	36
	db	113
	db	117
	db	105
	db	117
	db	105
	dw	18
	dw	512
	dw	8
	dw	0
	dw	117
	dw	0
	dw	2
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	12
	dw	0
	dw	117
	dw	0
	dw	3
	dw	0
	dw	0
	dw	0
?patch1	equ	@2-@@OutPortB$quiui+2
?patch2	equ	0
?patch3	equ	@2-@@OutPortB$quiui
	dw	2
	dw	6
$$BSYMS	ends
_TEXT	segment dword public use32 'CODE'
@InPortB$qui	segment virtual
@@InPortB$qui	proc	near
?live16386@0:
	?debug L 14
	push      ebp
	mov       ebp,esp
	?debug L 16
@3:
	mov       dx,word ptr [ebp+8]
	?debug L 22
	in	 al, dx
	?debug L 25
	mov	 ah, 000H
	?debug L 29
	movzx     eax,ax
	?debug L 30
@5:
@4:
	pop       ebp
	ret 
	?debug L 0
@@InPortB$qui	endp
@InPortB$qui	ends
_TEXT	ends
$$BSYMS	segment byte public use32 'DEBSYM'
	dw	59
	dw	517
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dd	?patch4
	dd	?patch5
	dd	?patch6
	df	@@InPortB$qui
	dw	0
	dw	4098
	dw	0
	dw	4
	dw	0
	dw	0
	dw	0
	db	12
	db	64
	db	73
	db	110
	db	80
	db	111
	db	114
	db	116
	db	66
	db	36
	db	113
	db	117
	db	105
	dw	18
	dw	512
	dw	8
	dw	0
	dw	117
	dw	0
	dw	5
	dw	0
	dw	0
	dw	0
?patch4	equ	@5-@@InPortB$qui+2
?patch5	equ	0
?patch6	equ	@5-@@InPortB$qui
	dw	2
	dw	6
$$BSYMS	ends
_TEXT	segment dword public use32 'CODE'
_TEXT	ends
$$BSYMS	segment byte public use32 'DEBSYM'
	dw	?patch7
	dw	1
	db	3
	db	1
	db	0
	db	24
	db	9
	db	66
	db	67
	db	67
	db	51
	db	50
	db	32
	db	53
	db	46
	db	53
?patch7	equ	16
$$BSYMS	ends
$$BTYPES	segment byte public use32 'DEBTYP'
	db        2,0,0,0,14,0,8,0,3,0,0,0,0,0,2,0
	db        1,16,0,0,12,0,1,2,2,0,117,0,0,0,117,0
	db        0,0,14,0,8,0,117,0,0,0,0,0,1,0,3,16
	db        0,0,8,0,1,2,1,0,117,0,0,0
$$BTYPES	ends
$$BNAMES	segment byte public use32 'DEBNAM'
	db	8,'OutPortB'
	db	8,'Endereco'
	db	4,'Dado'
	db	7,'InPortB'
	db	8,'Endereco'
$$BNAMES	ends
	?debug	D "C:\paghi\paralela\exemplos\aquisicao\paralela.cpp" 10913 31043
	end
