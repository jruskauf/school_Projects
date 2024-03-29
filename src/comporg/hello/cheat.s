;
; File generated by cc65 v 2.17 - Debian 2.17-1
;
	.fopt		compiler,"cc65 v 2.17 - Debian 2.17-1"
	.setcpu		"6502"
	.smart		on
	.autoimport	on
	.case		on
	.debuginfo	off
	.importzp	sp, sreg, regsave, regbank
	.importzp	tmp1, tmp2, tmp3, tmp4, ptr1, ptr2, ptr3, ptr4
	.macpack	longbranch
	.forceimport	__STARTUP__
	.export		_i
	.export		_TEXT
	.export		_PALETTE
	.export		_main

.segment	"RODATA"

_TEXT:
	.byte	$47,$6F,$6F,$64,$62,$79,$65,$20,$57,$6F,$72,$6C,$64,$2E,$2E,$2E
	.byte	$00
_PALETTE:
	.byte	$0F
	.byte	$16
	.byte	$16
	.byte	$16

.segment	"BSS"

.segment	"ZEROPAGE"
_i:
	.res	2,$00

; ---------------------------------------------------------------
; void __near__ main (void)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_main: near

.segment	"CODE"

;
; PPU_ADDRESS = 0x3f;
;
	lda     #$3F
	sta     $2006
;
; PPU_ADDRESS = 0x00;
;
	lda     #$00
	sta     $2006
;
; for ( i = 0; i < sizeof(PALETTE); ++i ) {
;
	sta     _i
	sta     _i+1
L000F:	lda     _i+1
	cmp     #$00
	bne     L0017
	lda     _i
	cmp     #$04
L0017:	bcs     L0010
;
; PPU_DATA = PALETTE[i];
;
	lda     #<(_PALETTE)
	sta     ptr1
	lda     #>(_PALETTE)
	clc
	adc     _i+1
	sta     ptr1+1
	ldy     _i
	lda     (ptr1),y
	sta     $2007
;
; for ( i = 0; i < sizeof(PALETTE); ++i ) {
;
	inc     _i
	bne     L000F
	inc     _i+1
	jmp     L000F
;
; PPU_ADDRESS = 0x21;
;
L0010:	lda     #$21
	sta     $2006
;
; PPU_ADDRESS = 0xc8;
;
	lda     #$C8
	sta     $2006
;
; for ( i = 0; i < sizeof(TEXT); ++i ) {
;
	lda     #$00
	sta     _i
	sta     _i+1
L0024:	lda     _i+1
	cmp     #$00
	bne     L002C
	lda     _i
	cmp     #$11
L002C:	bcs     L0025
;
; PPU_DATA = (uint8_t) TEXT[i];
;
	lda     #<(_TEXT)
	sta     ptr1
	lda     #>(_TEXT)
	clc
	adc     _i+1
	sta     ptr1+1
	ldy     _i
	lda     (ptr1),y
	sta     $2007
;
; for ( i = 0; i < sizeof(TEXT); ++i ) {
;
	inc     _i
	bne     L0024
	inc     _i+1
	jmp     L0024
;
; PPU_SCROLL = 0x00;
;
L0025:	lda     #$00
	sta     $2005
;
; PPU_SCROLL = 0x00;
;
	sta     $2005
;
; PPU_CTRL = 0x80;
;
	lda     #$80
	sta     $2000
;
; PPU_MASK = 0x1e;
;
	lda     #$1E
	sta     $2001
;
; while (1) {};
;
L0043:	jmp     L0043

.endproc

