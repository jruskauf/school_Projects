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
	.importzp	_InputPort1
	.importzp	_InputPort2
	.import		_WaitFrame
	.export		_PALETTES
	.export		_i
	.export		_j
	.export		_STATE
	.export		_START1_X
	.export		_START1_Y
	.export		_START2_X
	.export		_START2_Y
	.export		_SPEED
	.export		_SPEED2
	.export		_SCORE1
	.export		_SCORE2
	.export		_B_TOP
	.export		_B_BOT
	.export		_B_RGT
	.export		_B_LFT
	.export		_P1_TOP
	.export		_P1_BOT
	.export		_P1_RGT
	.export		_P1_LFT
	.export		_P2_TOP
	.export		_P2_BOT
	.export		_P2_RGT
	.export		_P2_LFT
	.export		_tmp_sprite
	.export		_ppu_addr
	.export		_ppu_data
	.export		_ppu_data_size
	.export		_player1
	.export		_player2
	.export		_score1
	.export		_score2
	.export		_ResetScroll
	.export		_EnablePPU
	.export		_WritePPU
	.export		_DrawArena
	.export		_Title_Setup
	.export		_Title_Loop
	.export		_Game_Setup
	.export		_Game_Loop
	.export		_main

.segment	"RODATA"

_PALETTES:
	.byte	$0F
	.byte	$16
	.byte	$27
	.byte	$18
	.byte	$00
	.byte	$00
	.byte	$00
	.byte	$00
	.byte	$00
	.byte	$00
	.byte	$00
	.byte	$00
	.byte	$00
	.byte	$00
	.byte	$00
	.byte	$00
	.byte	$22
	.byte	$16
	.byte	$27
	.byte	$18
	.byte	$0F
	.byte	$28
	.byte	$1A
	.byte	$12
	.byte	$00
	.byte	$20
	.byte	$28
	.byte	$17
	.byte	$00
	.byte	$00
	.byte	$00
	.byte	$00

.segment	"BSS"

.segment	"ZEROPAGE"
_i:
	.res	1,$00
_j:
	.res	1,$00
_STATE:
	.res	1,$00
_START1_X:
	.res	1,$00
_START1_Y:
	.res	1,$00
_START2_X:
	.res	1,$00
_START2_Y:
	.res	1,$00
_SPEED:
	.res	1,$00
_SPEED2:
	.res	1,$00
_SCORE1:
	.res	1,$00
_SCORE2:
	.res	1,$00
_B_TOP:
	.res	1,$00
_B_BOT:
	.res	1,$00
_B_RGT:
	.res	1,$00
_B_LFT:
	.res	1,$00
_P1_TOP:
	.res	1,$00
_P1_BOT:
	.res	1,$00
_P1_RGT:
	.res	1,$00
_P1_LFT:
	.res	1,$00
_P2_TOP:
	.res	1,$00
_P2_BOT:
	.res	1,$00
_P2_RGT:
	.res	1,$00
_P2_LFT:
	.res	1,$00
_tmp_sprite:
	.res	1,$00
_ppu_addr:
	.res	2,$00
_ppu_data:
	.res	2,$00
_ppu_data_size:
	.res	1,$00
.segment	"OAM"
_player1:
	.res	4,$00
_player2:
	.res	4,$00
_score1:
	.res	4,$00
_score2:
	.res	4,$00

; ---------------------------------------------------------------
; void __near__ ResetScroll (void)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_ResetScroll: near

.segment	"CODE"

;
; PPU_SCROLL = 0x00;
;
	lda     #$00
	sta     $2005
;
; PPU_SCROLL = 0x00;
;
	sta     $2005
;
; }
;
	rts

.endproc

; ---------------------------------------------------------------
; void __near__ EnablePPU (void)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_EnablePPU: near

.segment	"CODE"

;
; PPU_CTRL = PPUCTRL_NAMETABLE_0 | PPUCTRL_BPATTERN_0 | PPUCTRL_NMI_ON;
;
	lda     #$80
	sta     $2000
;
; PPUMASK_SSHOW       | PPUMASK_L8_SSHOW;;
;
	lda     #$1E
	sta     $2001
;
; }
;
	rts

.endproc

; ---------------------------------------------------------------
; void __near__ WritePPU (void)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_WritePPU: near

.segment	"CODE"

;
; PPU_ADDRESS = (uint8_t)(ppu_addr >> 8);
;
	lda     _ppu_addr+1
	sta     $2006
;
; PPU_ADDRESS = (uint8_t)(ppu_addr);
;
	lda     _ppu_addr
	sta     $2006
;
; for (i = 0; i < ppu_data_size; ++i) 
;
	lda     #$00
	sta     _i
L031A:	lda     _i
	cmp     _ppu_data_size
	bcs     L0042
;
; PPU_DATA = ppu_data[i];
;
	lda     _ppu_data
	ldx     _ppu_data+1
	ldy     _i
	sta     ptr1
	stx     ptr1+1
	lda     (ptr1),y
	sta     $2007
;
; for (i = 0; i < ppu_data_size; ++i) 
;
	inc     _i
	jmp     L031A
;
; }
;
L0042:	rts

.endproc

; ---------------------------------------------------------------
; void __near__ DrawArena (void)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_DrawArena: near

.segment	"CODE"

;
; PPU_DATA = BORDER_TL;
;
	lda     #$04
	sta     $2007
;
; for(i = 0; i < (NUM_COLS - 2); ++i)
;
	lda     #$00
	sta     _i
L031B:	lda     _i
	cmp     #$1E
	bcs     L031C
;
; PPU_DATA = BORDER_T;
;
	lda     #$07
	sta     $2007
;
; for(i = 0; i < (NUM_COLS - 2); ++i)
;
	inc     _i
	jmp     L031B
;
; PPU_DATA = BORDER_TR;
;
L031C:	lda     #$05
	sta     $2007
;
; PPU_DATA = BORDER_L;
;
	lda     #$06
	sta     $2007
;
; for (j = 0; j < ((NUM_COLS / 2) - 7); j++)
;
	lda     #$00
	sta     _j
L031D:	lda     _j
	cmp     #$09
	bcs     L031E
;
; PPU_DATA = BLANK_TILE;
;
	lda     #$00
	sta     $2007
;
; for (j = 0; j < ((NUM_COLS / 2) - 7); j++)
;
	inc     _j
	jmp     L031D
;
; tmp_sprite = 0xA0;
;
L031E:	lda     #$A0
	sta     _tmp_sprite
;
; for (j = 0; j < (12); j++)
;
	lda     #$00
	sta     _j
L031F:	lda     _j
	cmp     #$0C
	bcs     L0320
;
; PPU_DATA = tmp_sprite;
;
	lda     _tmp_sprite
	sta     $2007
;
; tmp_sprite++;
;
	inc     _tmp_sprite
;
; for (j = 0; j < (12); j++)
;
	inc     _j
	jmp     L031F
;
; for (j = 0; j < ((NUM_COLS / 2) - 7); j++)
;
L0320:	lda     #$00
	sta     _j
L0321:	lda     _j
	cmp     #$09
	bcs     L0322
;
; PPU_DATA = BLANK_TILE;
;
	lda     #$00
	sta     $2007
;
; for (j = 0; j < ((NUM_COLS / 2) - 7); j++)
;
	inc     _j
	jmp     L0321
;
; PPU_DATA = BORDER_R;
;
L0322:	lda     #$16
	sta     $2007
;
; PPU_DATA = BORDER_L;
;
	lda     #$06
	sta     $2007
;
; for (j = 0; j < ((NUM_COLS / 2) - 7); j++)
;
	lda     #$00
	sta     _j
L0323:	lda     _j
	cmp     #$09
	bcs     L0324
;
; PPU_DATA = BLANK_TILE;
;
	lda     #$00
	sta     $2007
;
; for (j = 0; j < ((NUM_COLS / 2) - 7); j++)
;
	inc     _j
	jmp     L0323
;
; tmp_sprite = 0xB0;
;
L0324:	lda     #$B0
	sta     _tmp_sprite
;
; for (j = 0; j < (12); j++)
;
	lda     #$00
	sta     _j
L0325:	lda     _j
	cmp     #$0C
	bcs     L0326
;
; PPU_DATA = tmp_sprite;
;
	lda     _tmp_sprite
	sta     $2007
;
; tmp_sprite++;
;
	inc     _tmp_sprite
;
; for (j = 0; j < (12); j++)
;
	inc     _j
	jmp     L0325
;
; for (j = 0; j < ((NUM_COLS / 2) - 7); j++)
;
L0326:	lda     #$00
	sta     _j
L0327:	lda     _j
	cmp     #$09
	bcs     L0328
;
; PPU_DATA = BLANK_TILE;
;
	lda     #$00
	sta     $2007
;
; for (j = 0; j < ((NUM_COLS / 2) - 7); j++)
;
	inc     _j
	jmp     L0327
;
; PPU_DATA = BORDER_R;
;
L0328:	lda     #$16
	sta     $2007
;
; for (i = 0; i < (NUM_ROWS - 4); ++i)
;
	lda     #$00
	sta     _i
L0329:	lda     _i
	cmp     #$18
	bcs     L032C
;
; PPU_DATA = BORDER_L;
;
	lda     #$06
	sta     $2007
;
; for (j = 0; j < (NUM_COLS - 2); ++j)
;
	lda     #$00
	sta     _j
L032A:	lda     _j
	cmp     #$1E
	bcs     L032B
;
; PPU_DATA = BLANK_TILE;
;
	lda     #$00
	sta     $2007
;
; for (j = 0; j < (NUM_COLS - 2); ++j)
;
	inc     _j
	jmp     L032A
;
; PPU_DATA = BORDER_R;
;
L032B:	lda     #$16
	sta     $2007
;
; for (i = 0; i < (NUM_ROWS - 4); ++i)
;
	inc     _i
	jmp     L0329
;
; PPU_DATA = BORDER_BL;
;
L032C:	lda     #$14
	sta     $2007
;
; for(i = 0; i < (NUM_COLS - 2); ++i)
;
	lda     #$00
	sta     _i
L032D:	lda     _i
	cmp     #$1E
	bcs     L032E
;
; PPU_DATA = BORDER_B;
;
	lda     #$17
	sta     $2007
;
; for(i = 0; i < (NUM_COLS - 2); ++i)
;
	inc     _i
	jmp     L032D
;
; PPU_DATA = BORDER_BR;
;
L032E:	lda     #$15
	sta     $2007
;
; }
;
	rts

.endproc

; ---------------------------------------------------------------
; void __near__ Title_Setup (void)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_Title_Setup: near

.segment	"CODE"

;
; START1_X = (MAX_X / 2) - (SPRITE_WIDTH  / 2) - 50;
;
	lda     #$4A
	sta     _START1_X
;
; START1_Y = (MAX_Y / 2) - (SPRITE_HEIGHT / 2);
;
	lda     #$6F
	sta     _START1_Y
;
; START2_X = (MAX_X / 2) - (SPRITE_WIDTH  / 2) + 50;
;
	lda     #$AE
	sta     _START2_X
;
; START2_Y = (MAX_Y / 2) - (SPRITE_HEIGHT / 2);
;
	lda     #$6F
	sta     _START2_Y
;
; SCORE1 = 0;
;
	lda     #$00
	sta     _SCORE1
;
; WritePPU();
;
	jsr     _WritePPU
;
; player1.x           = START1_X; 
;
	lda     _START1_X
	sta     _player1+3
;
; player1.y           = START1_Y;
;
	lda     _START1_Y
	sta     _player1
;
; player1.tile_index  = SPRITE_RIGHT;
;
	lda     #$11
	sta     _player1+1
;
; player1.attributes  = player1.attributes & 0x00;
;
	lda     #$00
	sta     _player1+2
;
; player2.x           = START2_X;
;
	lda     _START2_X
	sta     _player2+3
;
; player2.y           = START2_Y;
;
	lda     _START2_Y
	sta     _player2
;
; player2.tile_index  = SPRITE_LEFT;
;
	lda     #$12
	sta     _player2+1
;
; player2.attributes  = player2.attributes & 0x00;
;
	lda     #$00
	sta     _player2+2
;
; player2.attributes  = player2.attributes | 0x01;
;
	lda     #$01
	sta     _player2+2
;
; ResetScroll();
;
	jsr     _ResetScroll
;
; EnablePPU();
;
	jmp     _EnablePPU

.endproc

; ---------------------------------------------------------------
; void __near__ Title_Loop (void)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_Title_Loop: near

.segment	"CODE"

;
; while(SCORE1 == 0)
;
	jmp     L0330
;
; WaitFrame();
;
L0114:	jsr     _WaitFrame
;
; ResetScroll();
;
	jsr     _ResetScroll
;
; if(InputPort1 & BUTTON_START)
;
	lda     _InputPort1
	and     #$10
	beq     L032F
;
; SCORE1++;
;
	inc     _SCORE1
;
; if(InputPort2 & BUTTON_START)
;
L032F:	lda     _InputPort2
	and     #$10
	beq     L0330
;
; SCORE1++;
;
	inc     _SCORE1
;
; while(SCORE1 == 0)
;
L0330:	lda     _SCORE1
	beq     L0114
;
; }
;
	rts

.endproc

; ---------------------------------------------------------------
; void __near__ Game_Setup (void)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_Game_Setup: near

.segment	"CODE"

;
; B_TOP = MIN_Y + SPRITE_HEIGHT;
;
	lda     #$10
	sta     _B_TOP
;
; B_BOT = MAX_Y - (SPRITE_HEIGHT + SPRITE_HEIGHT);
;
	lda     #$D7
	sta     _B_BOT
;
; B_RGT = MAX_X - (SPRITE_WIDTH + SPRITE_WIDTH);
;
	lda     #$F0
	sta     _B_RGT
;
; B_LFT = MIN_X + SPRITE_WIDTH;
;
	lda     #$08
	sta     _B_LFT
;
; START1_X = (MAX_X / 2) - (SPRITE_WIDTH  / 2) - 50;
;
	lda     #$4A
	sta     _START1_X
;
; START1_Y = (MAX_Y / 2) - (SPRITE_HEIGHT / 2);
;
	lda     #$6F
	sta     _START1_Y
;
; START2_X = (MAX_X / 2) - (SPRITE_WIDTH  / 2) + 50;
;
	lda     #$AE
	sta     _START2_X
;
; START2_Y = (MAX_Y / 2) - (SPRITE_HEIGHT / 2);
;
	lda     #$6F
	sta     _START2_Y
;
; SPEED =  SPRINT;
;
	lda     #$03
	sta     _SPEED
;
; SPEED2 = SPRINT;
;
	sta     _SPEED2
;
; SCORE1 = 0;
;
	lda     #$00
	sta     _SCORE1
;
; SCORE2 = 0;
;
	sta     _SCORE2
;
; player1.x           = START1_X; 
;
	lda     _START1_X
	sta     _player1+3
;
; player1.y           = START1_Y;
;
	lda     _START1_Y
	sta     _player1
;
; player1.tile_index  = SPRITE_RIGHT;
;
	lda     #$11
	sta     _player1+1
;
; player1.attributes  = player1.attributes & 0x00;
;
	lda     #$00
	sta     _player1+2
;
; player2.x           = START2_X;
;
	lda     _START2_X
	sta     _player2+3
;
; player2.y           = START2_Y;
;
	lda     _START2_Y
	sta     _player2
;
; player2.tile_index  = SPRITE_LEFT;
;
	lda     #$12
	sta     _player2+1
;
; player2.attributes  = player2.attributes & 0x00;
;
	lda     #$00
	sta     _player2+2
;
; player2.attributes  = player2.attributes | 0x01;
;
	lda     #$01
	sta     _player2+2
;
; score1.x = MIN_X + SPRITE_WIDTH;
;
	lda     #$08
	sta     _score1+3
;
; score1.y = MIN_Y + SPRITE_HEIGHT;
;
	lda     #$10
	sta     _score1
;
; score1.tile_index   = 0x55;
;
	lda     #$55
	sta     _score1+1
;
; score1.attributes   = player1.attributes & 0x00;
;
	lda     #$00
	sta     _score1+2
;
; score2.x = MAX_X - SPRITE_WIDTH - SPRITE_WIDTH;
;
	lda     #$F0
	sta     _score2+3
;
; score2.y = MIN_Y + SPRITE_HEIGHT;
;
	lda     #$10
	sta     _score2
;
; score2.tile_index   = 0x55;
;
	lda     #$55
	sta     _score2+1
;
; score2.attributes   = score2.attributes & 0x00;
;
	lda     #$00
	sta     _score2+2
;
; }
;
	rts

.endproc

; ---------------------------------------------------------------
; void __near__ Game_Loop (void)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_Game_Loop: near

.segment	"CODE"

;
; while (SCORE1 < 5 && SCORE2 < 5)
;
	jmp     L0168
;
; P1_TOP = player1.y + SPRITE_HEIGHT;
;
L034F:	lda     _player1
	clc
	adc     #$08
	sta     _P1_TOP
;
; P1_BOT = player1.y - SPRITE_HEIGHT;
;
	lda     _player1
	sec
	sbc     #$08
	sta     _P1_BOT
;
; P1_RGT = player1.x + SPRITE_HEIGHT;
;
	lda     _player1+3
	clc
	adc     #$08
	sta     _P1_RGT
;
; P1_LFT = player1.x - SPRITE_HEIGHT;
;
	lda     _player1+3
	sec
	sbc     #$08
	sta     _P1_LFT
;
; P2_TOP = player2.y + SPRITE_HEIGHT;
;
	lda     _player2
	clc
	adc     #$08
	sta     _P2_TOP
;
; P2_BOT = player2.y - SPRITE_HEIGHT;
;
	lda     _player2
	sec
	sbc     #$08
	sta     _P2_BOT
;
; P2_RGT = player2.x + SPRITE_HEIGHT;
;
	lda     _player2+3
	clc
	adc     #$08
	sta     _P2_RGT
;
; P2_LFT = player2.x - SPRITE_HEIGHT;
;
	lda     _player2+3
	sec
	sbc     #$08
	sta     _P2_LFT
;
; if(InputPort1 & BUTTON_START)
;
	lda     _InputPort1
	and     #$10
	beq     L0350
;
; STATE++;
;
	inc     _STATE
;
; if (InputPort1 & BUTTON_UP)
;
L0350:	lda     _InputPort1
	and     #$08
	jeq     L0359
;
; player1.tile_index  = SPRITE_UP;
;
	lda     #$13
	sta     _player1+1
;
; if (player1.y > B_TOP)
;
	lda     _player1
	sec
	sbc     _B_TOP
	jcc     L0373
	jeq     L0373
;
; if (player1.y >= player2.y)
;
	lda     _player1
	cmp     _player2
	bcc     L0358
;
; if( P1_RGT >= player2.x &&
;
	lda     _P1_RGT
	cmp     _player2+3
	bcc     L0357
;
; P1_LFT <= player2.x)
;
	lda     _P1_LFT
	sec
	sbc     _player2+3
	bcc     L0353
	bne     L0357
;
; if(P1_BOT <= player2.y)
;
L0353:	lda     _P1_BOT
	sec
	sbc     _player2
	sta     tmp1
	lda     tmp1
	beq     L0354
	bcs     L0358
;
; if(player2.tile_index != SPRITE_DOWN)
;
L0354:	lda     _player2+1
	cmp     #$10
	beq     L0355
;
; SCORE1++;
;
	inc     _SCORE1
;
; score2.tile_index = score2.tile_index - 1;
;
	lda     _score2+1
	sec
	sbc     #$01
	sta     _score2+1
;
; player1.x = START1_X;
;
L0355:	lda     _START1_X
	sta     _player1+3
;
; player1.y = START1_Y;
;
	lda     _START1_Y
	sta     _player1
;
; player1.tile_index = SPRITE_RIGHT;
;
	lda     #$11
	sta     _player1+1
;
; player2.x = START2_X;
;
	lda     _START2_X
	sta     _player2+3
;
; player2.y = START2_Y;
;
	lda     _START2_Y
	sta     _player2
;
; player2.tile_index = SPRITE_LEFT;
;
	lda     #$12
	sta     _player2+1
;
; else 
;
	jmp     L0373
;
; player1.y = player1.y - SPEED;
;
L0357:	lda     _player1
	sec
	sbc     _SPEED
	sta     _player1
;
; else 
;
	jmp     L0373
;
; player1.y = player1.y - SPEED;
;
L0358:	lda     _player1
	sec
	sbc     _SPEED
	sta     _player1
;
; else if (InputPort1 & BUTTON_DOWN)  
;
	jmp     L0373
L0359:	lda     _InputPort1
	and     #$04
	jeq     L0362
;
; player1.tile_index  = SPRITE_DOWN; 
;
	lda     #$10
	sta     _player1+1
;
; if (player1.y < B_BOT)
;
	lda     _player1
	cmp     _B_BOT
	jcs     L0373
;
; if (player1.y <= player2.y)
;
	sec
	sbc     _player2
	sta     tmp1
	lda     tmp1
	beq     L035A
	bcs     L0361
;
; if(P1_RGT >= player2.x &&
;
L035A:	lda     _P1_RGT
	cmp     _player2+3
	bcc     L0360
;
; P1_LFT <= player2.x)
;
	lda     _P1_LFT
	sec
	sbc     _player2+3
	bcc     L035D
	bne     L0360
;
; if(P1_TOP >= player2.y)
;
L035D:	lda     _P1_TOP
	cmp     _player2
	bcc     L0361
;
; if(player2.tile_index != SPRITE_UP)
;
	lda     _player2+1
	cmp     #$13
	beq     L035E
;
; SCORE1++;
;
	inc     _SCORE1
;
; score2.tile_index = score2.tile_index - 1;
;
	lda     _score2+1
	sec
	sbc     #$01
	sta     _score2+1
;
; player1.x = START1_X;
;
L035E:	lda     _START1_X
	sta     _player1+3
;
; player1.y = START1_Y;
;
	lda     _START1_Y
	sta     _player1
;
; player1.tile_index = SPRITE_RIGHT;
;
	lda     #$11
	sta     _player1+1
;
; player2.x = START2_X;
;
	lda     _START2_X
	sta     _player2+3
;
; player2.y = START2_Y;
;
	lda     _START2_Y
	sta     _player2
;
; player2.tile_index = SPRITE_LEFT;
;
	lda     #$12
	sta     _player2+1
;
; else 
;
	jmp     L0373
;
; player1.y = player1.y + SPEED;
;
L0360:	lda     _player1
	clc
	adc     _SPEED
	sta     _player1
;
; else 
;
	jmp     L0373
;
; player1.y = player1.y + SPEED;
;
L0361:	lda     _player1
	clc
	adc     _SPEED
	sta     _player1
;
; else if (InputPort1 & BUTTON_LEFT)  
;
	jmp     L0373
L0362:	lda     _InputPort1
	and     #$02
	jeq     L036A
;
; player1.tile_index  = SPRITE_LEFT; 
;
	lda     #$12
	sta     _player1+1
;
; if (player1.x > B_LFT)
;
	ldx     #$00
	lda     _player1+3
	sec
	sbc     _B_LFT
	jcc     L0373
	jeq     L0373
;
; if (player1.x >= player2.x)
;
	lda     _player1+3
	cmp     _player2+3
	jcc     L0369
;
; if(player1.y + SPRITE_HEIGHT >= player2.y &&
;
	lda     _player1
	clc
	adc     #$08
	bcc     L01E5
	inx
L01E5:	cmp     _player2
	txa
	sbc     #$00
	ldx     #$00
	bcc     L0368
;
; player1.y - SPRITE_HEIGHT <= player2.y)
;
	lda     _player1
	sec
	sbc     #$08
	bcs     L034E
	dex
	sec
L034E:	sbc     _player2
	sta     tmp1
	txa
	sbc     #$00
	ora     tmp1
	bcc     L01E4
	bne     L0368
;
; if(P1_LFT <= player2.x)
;
L01E4:	lda     _P1_LFT
	sec
	sbc     _player2+3
	sta     tmp1
	lda     tmp1
	beq     L0365
	bcs     L0367
;
; if(player2.tile_index != SPRITE_RIGHT)
;
L0365:	lda     _player2+1
	cmp     #$11
	beq     L0366
;
; SCORE1++;
;
	inc     _SCORE1
;
; score2.tile_index = score2.tile_index - 1;
;
	lda     _score2+1
	sec
	sbc     #$01
	sta     _score2+1
;
; player1.x = START1_X; 
;
L0366:	lda     _START1_X
	sta     _player1+3
;
; player1.y = START1_Y;
;
	lda     _START1_Y
	sta     _player1
;
; player1.tile_index = SPRITE_RIGHT;
;
	lda     #$11
	sta     _player1+1
;
; player2.x = START2_X;
;
	lda     _START2_X
	sta     _player2+3
;
; player2.y = START2_Y;
;
	lda     _START2_Y
	sta     _player2
;
; player2.tile_index = SPRITE_LEFT;
;
	lda     #$12
	sta     _player2+1
;
; else 
;
	jmp     L0373
;
; player1.x = player1.x - SPEED;
;
L0367:	lda     _player1+3
	sec
	sbc     _SPEED
;
; else
;
	jmp     L0349
;
; player1.x = player1.x - SPEED;
;
L0368:	lda     _player1+3
	sec
	sbc     _SPEED
;
; else 
;
	jmp     L0349
;
; player1.x = player1.x - SPEED;
;
L0369:	lda     _player1+3
	sec
	sbc     _SPEED
;
; else if (InputPort1 & BUTTON_RIGHT)  
;
	jmp     L0349
L036A:	lda     _InputPort1
	and     #$01
	beq     L0373
;
; player1.tile_index  = SPRITE_RIGHT;
;
	lda     #$11
	sta     _player1+1
;
; if (player1.x < B_RGT)   
;
	lda     _player1+3
	cmp     _B_RGT
	bcs     L0373
;
; if (player1.x <= player2.x)
;
	sec
	sbc     _player2+3
	sta     tmp1
	lda     tmp1
	beq     L036B
	bcs     L0372
;
; if(P1_TOP >= player2.y &&
;
L036B:	lda     _P1_TOP
	cmp     _player2
	bcc     L0372
;
; P1_BOT <= player2.y)
;
	lda     _P1_BOT
	sec
	sbc     _player2
	bcc     L036E
	bne     L0372
;
; if(P1_RGT >= player2.x)
;
L036E:	lda     _P1_RGT
	cmp     _player2+3
	bcc     L0372
;
; if(player2.tile_index != SPRITE_LEFT)
;
	lda     _player2+1
	cmp     #$12
	beq     L036F
;
; SCORE1++;
;
	inc     _SCORE1
;
; score2.tile_index = score2.tile_index - 1;
;
	lda     _score2+1
	sec
	sbc     #$01
	sta     _score2+1
;
; player1.x = START1_X; 
;
L036F:	lda     _START1_X
	sta     _player1+3
;
; player1.y = START1_Y;
;
	lda     _START1_Y
	sta     _player1
;
; player1.tile_index = SPRITE_RIGHT;
;
	lda     #$11
	sta     _player1+1
;
; player2.x = START2_X;
;
	lda     _START2_X
	sta     _player2+3
;
; player2.y = START2_Y;
;
	lda     _START2_Y
	sta     _player2
;
; player2.tile_index = SPRITE_LEFT;                          
;
	lda     #$12
	sta     _player2+1
;
; else 
;
	jmp     L0373
;
; player1.x = player1.x + SPEED;
;
L0372:	lda     _player1+3
	clc
	adc     _SPEED
L0349:	sta     _player1+3
;
; if (InputPort2 & BUTTON_UP)
;
L0373:	lda     _InputPort2
	and     #$08
	jeq     L037C
;
; player2.tile_index  = SPRITE_UP;
;
	lda     #$13
	sta     _player2+1
;
; if (player2.y > B_TOP)
;
	lda     _player2
	sec
	sbc     _B_TOP
	jcc     L0397
	jeq     L0397
;
; if (player2.y >= player1.y)
;
	lda     _player2
	cmp     _player1
	bcc     L037B
;
; if( P2_RGT >= player1.x &&
;
	lda     _P2_RGT
	cmp     _player1+3
	bcc     L037A
;
; P2_LFT <= player1.x)
;
	lda     _P2_LFT
	sec
	sbc     _player1+3
	bcc     L0376
	bne     L037A
;
; if(P2_BOT <= player1.y)
;
L0376:	lda     _P2_BOT
	sec
	sbc     _player1
	sta     tmp1
	lda     tmp1
	beq     L0377
	bcs     L037B
;
; if(player1.tile_index != SPRITE_DOWN)
;
L0377:	lda     _player1+1
	cmp     #$10
	beq     L0378
;
; SCORE2++;
;
	inc     _SCORE2
;
; score1.tile_index = score1.tile_index - 1;
;
	lda     _score1+1
	sec
	sbc     #$01
	sta     _score1+1
;
; player1.x = START1_X;
;
L0378:	lda     _START1_X
	sta     _player1+3
;
; player1.y = START1_Y;
;
	lda     _START1_Y
	sta     _player1
;
; player1.tile_index = SPRITE_RIGHT;
;
	lda     #$11
	sta     _player1+1
;
; player2.x = START2_X;
;
	lda     _START2_X
	sta     _player2+3
;
; player2.y = START2_Y;
;
	lda     _START2_Y
	sta     _player2
;
; player2.tile_index = SPRITE_LEFT;
;
	lda     #$12
	sta     _player2+1
;
; else 
;
	jmp     L0397
;
; player2.y = player2.y - SPEED2;
;
L037A:	lda     _player2
	sec
	sbc     _SPEED2
	sta     _player2
;
; else 
;
	jmp     L0397
;
; player2.y = player2.y - SPEED2;
;
L037B:	lda     _player2
	sec
	sbc     _SPEED2
	sta     _player2
;
; else if (InputPort2 & BUTTON_DOWN)  
;
	jmp     L0397
L037C:	lda     _InputPort2
	and     #$04
	jeq     L0385
;
; player2.tile_index  = SPRITE_DOWN; 
;
	lda     #$10
	sta     _player2+1
;
; if (player2.y < B_BOT)
;
	lda     _player2
	cmp     _B_BOT
	jcs     L0397
;
; if (player2.y <= player1.y)
;
	sec
	sbc     _player1
	sta     tmp1
	lda     tmp1
	beq     L037D
	bcs     L0384
;
; if(P2_RGT >= player1.x &&
;
L037D:	lda     _P2_RGT
	cmp     _player1+3
	bcc     L0383
;
; P2_LFT <= player1.x)
;
	lda     _P2_LFT
	sec
	sbc     _player1+3
	bcc     L0380
	bne     L0383
;
; if(P2_TOP >= player1.y)
;
L0380:	lda     _P2_TOP
	cmp     _player1
	bcc     L0384
;
; if(player1.tile_index != SPRITE_UP)
;
	lda     _player1+1
	cmp     #$13
	beq     L0381
;
; SCORE2++;
;
	inc     _SCORE2
;
; score1.tile_index = score1.tile_index - 1;
;
	lda     _score1+1
	sec
	sbc     #$01
	sta     _score1+1
;
; player1.x = START1_X;
;
L0381:	lda     _START1_X
	sta     _player1+3
;
; player1.y = START1_Y;
;
	lda     _START1_Y
	sta     _player1
;
; player1.tile_index = SPRITE_RIGHT;
;
	lda     #$11
	sta     _player1+1
;
; player2.x = START2_X;
;
	lda     _START2_X
	sta     _player2+3
;
; player2.y = START2_Y;
;
	lda     _START2_Y
	sta     _player2
;
; player2.tile_index = SPRITE_LEFT;
;
	lda     #$12
	sta     _player2+1
;
; else 
;
	jmp     L0397
;
; player2.y = player2.y + SPEED2;
;
L0383:	lda     _player2
	clc
	adc     _SPEED2
	sta     _player2
;
; else 
;
	jmp     L0397
;
; player2.y = player2.y + SPEED2;
;
L0384:	lda     _player2
	clc
	adc     _SPEED2
	sta     _player2
;
; else if (InputPort2 & BUTTON_LEFT)  
;
	jmp     L0397
L0385:	lda     _InputPort2
	and     #$02
	jeq     L038E
;
; player2.tile_index  = SPRITE_LEFT; 
;
	lda     #$12
	sta     _player2+1
;
; if (player2.x > B_LFT)
;
	lda     _player2+3
	sec
	sbc     _B_LFT
	jcc     L0397
	jeq     L0397
;
; if (player2.x >= player1.x)
;
	lda     _player2+3
	cmp     _player1+3
	bcc     L038D
;
; if(P2_TOP >= player1.y &&
;
	lda     _P2_TOP
	cmp     _player1
	bcc     L038C
;
; P2_BOT <= player1.y)
;
	lda     _P2_BOT
	sec
	sbc     _player1
	bcc     L0388
	bne     L038C
;
; if(P2_LFT <= player1.x)
;
L0388:	lda     _P2_LFT
	sec
	sbc     _player1+3
	sta     tmp1
	lda     tmp1
	beq     L0389
	bcs     L038B
;
; if(player1.tile_index != SPRITE_RIGHT)
;
L0389:	lda     _player1+1
	cmp     #$11
	beq     L038A
;
; SCORE2++;
;
	inc     _SCORE2
;
; score1.tile_index = score1.tile_index - 1;
;
	lda     _score1+1
	sec
	sbc     #$01
	sta     _score1+1
;
; player1.x = START1_X; 
;
L038A:	lda     _START1_X
	sta     _player1+3
;
; player1.y = START1_Y;
;
	lda     _START1_Y
	sta     _player1
;
; player1.tile_index = SPRITE_RIGHT;
;
	lda     #$11
	sta     _player1+1
;
; player2.x = START2_X;
;
	lda     _START2_X
	sta     _player2+3
;
; player2.y = START2_Y;
;
	lda     _START2_Y
	sta     _player2
;
; player2.tile_index = SPRITE_LEFT;
;
	lda     #$12
	sta     _player2+1
;
; else 
;
	jmp     L0397
;
; player2.x = player2.x - SPEED2;
;
L038B:	lda     _player2+3
	sec
	sbc     _SPEED2
;
; else
;
	jmp     L034D
;
; player2.x = player2.x - SPEED2;
;
L038C:	lda     _player2+3
	sec
	sbc     _SPEED2
;
; else 
;
	jmp     L034D
;
; player2.x = player2.x - SPEED2;
;
L038D:	lda     _player2+3
	sec
	sbc     _SPEED2
;
; else if (InputPort2 & BUTTON_RIGHT)  
;
	jmp     L034D
L038E:	lda     _InputPort2
	and     #$01
	beq     L0397
;
; player2.tile_index  = SPRITE_RIGHT;
;
	lda     #$11
	sta     _player2+1
;
; if (player2.x < B_RGT)   
;
	lda     _player2+3
	cmp     _B_RGT
	bcs     L0397
;
; if (player2.x <= player1.x)
;
	sec
	sbc     _player1+3
	sta     tmp1
	lda     tmp1
	beq     L038F
	bcs     L0396
;
; if(P2_TOP >= player1.y &&
;
L038F:	lda     _P2_TOP
	cmp     _player1
	bcc     L0396
;
; P2_BOT <= player1.y)
;
	lda     _P2_BOT
	sec
	sbc     _player1
	bcc     L0392
	bne     L0396
;
; if(P2_RGT >= player1.x)
;
L0392:	lda     _P2_RGT
	cmp     _player1+3
	bcc     L0396
;
; if(player1.tile_index != SPRITE_LEFT)
;
	lda     _player1+1
	cmp     #$12
	beq     L0393
;
; SCORE2++;
;
	inc     _SCORE2
;
; score1.tile_index = score1.tile_index - 1;
;
	lda     _score1+1
	sec
	sbc     #$01
	sta     _score1+1
;
; player1.x = START1_X; 
;
L0393:	lda     _START1_X
	sta     _player1+3
;
; player1.y = START1_Y;
;
	lda     _START1_Y
	sta     _player1
;
; player1.tile_index = SPRITE_RIGHT;
;
	lda     #$11
	sta     _player1+1
;
; player2.x = START2_X;
;
	lda     _START2_X
	sta     _player2+3
;
; player2.y = START2_Y;
;
	lda     _START2_Y
	sta     _player2
;
; player2.tile_index = SPRITE_LEFT;                          
;
	lda     #$12
	sta     _player2+1
;
; else 
;
	jmp     L0397
;
; player2.x = player2.x + SPEED2;
;
L0396:	lda     _player2+3
	clc
	adc     _SPEED2
L034D:	sta     _player2+3
;
; if (SCORE1 == 5)
;
L0397:	lda     _SCORE1
	cmp     #$05
	bne     L0399
;
; score1.tile_index = 0x77;
;
	lda     #$77
	sta     _score1+1
;
; score2.tile_index = 0x6C;
;
	lda     #$6C
	sta     _score2+1
;
; if(InputPort1 & BUTTON_START)
;
L02DD:	lda     _InputPort1
	and     #$10
	beq     L0398
;
; Game_Setup();
;
	jsr     _Game_Setup
;
; break;
;
	jmp     L0399
;
; else if (InputPort2 & BUTTON_START)
;
L0398:	lda     _InputPort2
	and     #$10
	beq     L02E5
;
; Game_Setup();
;
	jsr     _Game_Setup
;
; break;
;
	jmp     L0399
;
; WaitFrame();
;
L02E5:	jsr     _WaitFrame
;
; ResetScroll();
;
	jsr     _ResetScroll
;
; while(1)
;
	jmp     L02DD
;
; if(SCORE2 == 5)
;
L0399:	lda     _SCORE2
	cmp     #$05
	bne     L02F1
;
; score1.tile_index = 0x6C;
;
	lda     #$6C
	sta     _score1+1
;
; score2.tile_index = 0x77;
;
	lda     #$77
	sta     _score2+1
;
; if(InputPort1 & BUTTON_START)
;
L02F0:	lda     _InputPort1
	and     #$10
	beq     L039A
;
; Game_Setup();
;
	jsr     _Game_Setup
;
; break;
;
	jmp     L02F1
;
; else if (InputPort2 & BUTTON_START)
;
L039A:	lda     _InputPort2
	and     #$10
	beq     L02F8
;
; Game_Setup();
;
	jsr     _Game_Setup
;
; break;
;
	jmp     L02F1
;
; WaitFrame();
;
L02F8:	jsr     _WaitFrame
;
; ResetScroll();
;
	jsr     _ResetScroll
;
; while(1)
;
	jmp     L02F0
;
; WaitFrame();
;
L02F1:	jsr     _WaitFrame
;
; ResetScroll();
;
	jsr     _ResetScroll
;
; while (SCORE1 < 5 && SCORE2 < 5)
;
L0168:	lda     _SCORE1
	cmp     #$05
	bcs     L039B
	lda     _SCORE2
	cmp     #$05
	jcc     L034F
L039B:	rts

.endproc

; ---------------------------------------------------------------
; void __near__ main (void)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_main: near

.segment	"CODE"

;
; ppu_addr           = PPU_PALETTE;
;
	ldx     #$3F
	lda     #$00
	sta     _ppu_addr
	stx     _ppu_addr+1
;
; ppu_data           = PALETTES;
;
	lda     #<(_PALETTES)
	sta     _ppu_data
	lda     #>(_PALETTES)
	sta     _ppu_data+1
;
; ppu_data_size      = sizeof(PALETTES);
;
	lda     #$20
	sta     _ppu_data_size
;
; PPU_ADDRESS = (uint8_t)((PPU_NAMETABLE_0 + NAMETABLE_OFFSET) >> 8);
;
	sta     $2006
;
; PPU_ADDRESS = (uint8_t) (PPU_NAMETABLE_0 + NAMETABLE_OFFSET);
;
	sta     $2006
;
; DrawArena();
;
	jsr     _DrawArena
;
; Title_Setup();
;
	jsr     _Title_Setup
;
; Title_Loop();
;
	jsr     _Title_Loop
;
; Game_Setup();
;
	jsr     _Game_Setup
;
; ResetScroll();
;
	jsr     _ResetScroll
;
; EnablePPU();
;
	jsr     _EnablePPU
;
; Game_Loop();
;
	jmp     _Game_Loop

.endproc

