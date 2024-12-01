


;--------------------- Copyright A.t.d. 1988 -------------------------
;
;The Z80 equivalent of #defines for various thingees, commented.
;
; THESE ONES ARE FOR THE USER
;
;Contains some of the F.INC definitions, the only usable ones from the
;original F.INC
;
;


; Port addresses

VID     EQU     00h             ; base address of video chip
READYP  EQU     22h             ; ready port
GPO     EQU     22h             ; general purpose output port

DSP     EQU     10h             ; base address of DSP chip
ADC     EQU     40h             ; video ADC

; Video chip registers

BANK0   EQU     VID + 0         ; bank registers
BANK1   EQU     VID + 1
BANK2   EQU     VID + 2
BANK3   EQU     VID + 3
HCOUNT  EQU     VID + 4         ; horizontal counter port
LPEN1   EQU     VID + 4         ; horizontal lightpen register
VCOUNT  EQU     VID + 5         ; vertical counter port
LPEN2   EQU     VID + 5         ; vertical lightpen register
BAUD    EQU     VID + 6         ; baud rate register
LPEN3   EQU     VID + 6         ; combined lightpen register
INTREG  EQU     VID + 7         ; interupt position register
INTACK  EQU     VID + 7         ; interupt acknowledge port (read)
CMD1    EQU     VID + 8         ; command register #1
INT9    EQU     4               ; bit 8 of interupt position
HCOUNT9 EQU     8               ; bit 8 of horizontal counter
HCOUNTA EQU     10H             ; bit 9 of horizontal counter
VCOUNT9 EQU     20H             ; bit 8 of vertical counter
SCR1    EQU     40H             ; screen 1 select
GENLOCK EQU     80H             ; enable genlocking
CMD2    EQU     VID + 9         ; command register #2
HIRES   EQU     1               ; 512 pixel mode bit
INCEN   EQU     2               ; incrust enable bit
BINCEN  EQU     4               ; border incrust enable
HOLD    EQU     8               ; enables colour hold mode
MASK7   EQU     20h             ; masks msb of each pixel
MASK6   EQU     40h             ; masks top two bits of lo res pixels
VARM    EQU     80h             ; mode depends on bit 7 of byte
BORDER  EQU     VID + 10        ; border colour register
SCRLH   EQU     VID + 11        ; horizontal scroll register
SCRLV   EQU     VID + 12        ; vertical scroll register
TRANS   EQU     VID + 13        ; colour used as transparent in colour
                                ; hold mode
MAG     EQU     VID + 14        ; colour which replaces magenta in hi res
YEL     EQU     VID + 15        ; colour which replaces yellow in hi res

; Blitter IO Definitions

BLPC0   EQU     18h
BLPC1   EQU     19h
BLPC2   EQU     1Ah
BLCMD   EQU     20h
STOP_DST_L	equ 20h
STOP_DST_H equ 21h

; DSP IO Definitions

INTRD   EQU     DSP+0
INTRDP  EQU     DSP+1
INTRA   EQU     DSP+2
MPROG   EQU     DSP+3
RUNST   EQU     DSP+4
PROGRAM EQU     DSP+5

CPMPAGE EQU     4	; Base of ROM2

;Offsets in blitter program of command bytes

SRCAD0          EQU     0               ; Source Address byte 0
SRCAD1          EQU     1               ; Source Address byte 1
SRCAD2          EQU     2               ; Source Address byte 2
DSTAD0          EQU     3               ; Dest Address byte 0
DSTAD1          EQU     4               ; Dest Address byte 1
DSTAD2          EQU     5               ; Dest Address byte 2
MODE            EQU     6               ; Mode control
LOG_CMP         EQU     7               ; Logic and comparator control
OUTER           EQU     8               ; Outer Counter
INNER           EQU     9               ; Inner Counter
STEP            EQU     10              ; Step
PATTERN         EQU     11              ; Pattern
NEXT_COM        EQU     12              ; next command

INNER2          EQU     12              ; Inner 2 counter when PARRD enabled
STEP2           EQU     13              ; Step 2 when PARRD enabled
PATTERN2        EQU     14              ; Pattern 2 when PARRD enabled
NEXT_COM2       EQU     15              ; next command when PARRD enabled


; Physical Address Definitions
; ----------------------------

PROGBASE        EQU     04h             ; Top part of Z80 address
SCRBASE         EQU     02h             ; Top part of screen address
SCRBASE2        EQU     03h             ; Second screen.


;---------------------------------------------------------------------
;Now for my defines !
;

CODE_START equ 1024	;the lowest address from which a program can run
ORG_DATA	equ 49152	;address where pages paged into. ORG for DATA !

copy_   equ 4	;marker for blitter list kept in a separate
fill_   equ 3	;table, denoting the blitter command at that point
line_   equ 2
point_  equ 1
null_   equ 0	;Initial value placed in damage buffers

front   equ 1	;which screen needs clearing ?
back    equ 2
both    equ 3

true    equ 1	;general purpose
false   equ 0

black   equ 0	;black's colour value
white   equ 255	;white's colour value


dsp_hlt equ 0	;to stop the dsp (for LOADing prog etc)

NEWLINE equ 13	;the newline character
SPACE_CH equ 32	;ascii SPACE char

TOP_PAGE equ 19	;the STANDARD top 16k of z80 address memory

;---------------------------------------------------------------------
;These defines are for the chunk data types, and chunk formats. They
;cover:
;       character fonts,
;       sprites and
;       copy blocks
;

n_plane	equ 0		;n-plane image
b_img_n	equ 1		;bit image, -nibble format
b_img_b	equ 2		;bit image, -byte format
run_lc	equ 3		;run length coded type
pos_mask	equ 127	;test for type without testing for pos encoded
e_pos	equ 128	;position of image stored within image
pos_nplane	equ n_plane+e_pos	;n-plane with position
pos_img_n	equ b_img_n+e_pos	;nibble format with position encoding
pos_img_b	equ b_img_b+e_pos	;byte format with position encoding

prop_t  equ 1	;proportional spacing enabled
prop_f  equ 0	;proportional spacing off (fixed width)


;---------------------------------------------------------------------
;These defines are for the LOW LEVEL only. The user should not use
;these ones
;
;


screen1 equ 0	;screen numbers (used in deciding which is on show)
screen2 equ 1


; The following are AND values for cmd2m to read various modes of screen
; operation on the Flare. If the result of the AND is non-zero then the
; mode is operative !

hold_and equ 8	;and value with cmd2m to obtain hold ON/OFF info
mode_and equ 1	;and value with cmd2m to obtain HI/LO res info
parrd_and equ 4	;and value to obtain PARRD information ! for partial lines


;window block parameter offsets now follow !

W_EXISTS equ 0	;window exists AND erase backgrnd of character b4 printing
W_ERASE  equ 0	;these two offsets exist for clarity
W_TOPX   equ 1
W_TOPY   equ 2
W_XSIZE  equ 3
W_YSIZE  equ 4
W_PAPER  equ 5
W_INK    equ 6
W_CURSX  equ 7
W_CURSY  equ 8
W_FONTL  equ 9
W_FONTH  equ 10
W_FONTP  equ 11
W_CHARX  equ 12
W_CHARY  equ 13
W_ERROR  equ 14

it_exists	equ 1		;bit 0, W_EXISTS indicates the window exists
flag_eras	equ 128	;bit 7, indicates that erasing b4 printing reqd

WINSIZE  equ 16	;current size of window def block
MAXWIN   equ 8	;maximum number of windows
BLITSIZE equ 13	;current size of a blitter program !
BYTE     equ 1	;size of a byte
WORD     equ 2	;word size !


;---------------------------------------------------------------------
;Now for memory allocation in RAM (for use in 8088 versions)....
;
;NOT FOR ACCESS BY THE USER.
;

SYS_VAR	MACRO			;macro for allocating memory to
@1	equ var_pc		;system variables, without overlap
var_pc	= var_pc+@2		;or reference to last variable.
	ENDM


;Now lets give one to the users ! PERVERT

USER_VAR	MACRO
@1	equ var_pc		;same label, different MACRO name
var_pc	= var_pc+@2
	ENDM


;---------------------------------------------------------------------

var_pc	= 51200		;set the SYSTEM variables address

	SYS_VAR cls_blit,BLITSIZE	;blitter program for clearing the screen
	SYS_VAR visible,BYTE	;which screen is on show (IF swapping)
	SYS_VAR scrn_col,BYTE	;background colour of the screen

	SYS_VAR cur_win,BYTE	;which window is the current one
	SYS_VAR cur_base,WORD	;address of base of current window
	SYS_VAR win_base,WINSIZE*MAXWIN	;base for window info blocks

	SYS_VAR randno,WORD	;random number seed ?

	SYS_VAR blit_ptr,WORD	;pointer into one of two blit buffers
	SYS_VAR mark_ptr,WORD	;pointer into damage tables (dodgy 1&2)
	SYS_VAR cmd_b1,BYTE	;command for first buffer
	SYS_VAR blitbuf1,BLITNUM*BLITSIZE	;first 256 OR more blit buffer
	SYS_VAR cmd_b2,BYTE	;command for second buffer
	SYS_VAR blitbuf2,BLITNUM*BLITSIZE	;second 256 OR more blit buffer
	SYS_VAR dodgy1,BLITNUM	;bad blit marker buffer
	SYS_VAR dodgy2,BLITNUM	;for other blitter buffer
	SYS_VAR dam_blit,BLITSIZE	;blitter program for copying to bufs
	SYS_VAR pt_blit,BLITSIZE	;point blitter program

	SYS_VAR plot_col,BYTE	;colour for plotting points
	SYS_VAR line_col,BYTE	;colour for drawing lines
	SYS_VAR bright_col,BYTE	;colour of bright point in partial
	SYS_VAR line_len,BYTE	;how much of line to be drawn
	SYS_VAR clw_blit,BLITSIZE	;blitter for CLWing

	SYS_VAR flag_er1,BYTE	;erase blitter list just doen flag
	SYS_VAR flag_er2,BYTE	;MUST follow on from flag_er1

	SYS_VAR scrl_blt,BLITSIZE*2	;2 blits for scrolling !


;---------------------------------------------------------------------
;There now follows character painting blitter programs. For:
;
;       nibble blocks
;       byte blocks
;       n_plane blocks
;

	SYS_VAR chr_copy,BLITSIZE	;blit copies RAM template to RAM !
	SYS_VAR chr_temp,BLITSIZE	;template to insert into chr_blit
	SYS_VAR chr_eras,BLITSIZE	;erase blit for n-plane painting
	SYS_VAR chr_blit,BLITSIZE*7	;7 for n-plane painting

	SYS_VAR era_nblk,BLITSIZE	;erase blit for nibble block
	SYS_VAR chr_nblk,BLITSIZE	;nibble blocks
	SYS_VAR era_bblk,BLITSIZE	;erase blit for byte block
	SYS_VAR chr_bblk,BLITSIZE	;byte blocks

	SYS_VAR width_ch,BYTE	;width of character just painted

	SYS_VAR cmd1m,BYTE	;copy of video chip cmd1 register
	SYS_VAR cmd2m,BYTE	;copy of video chip cmd2 register
	SYS_VAR gpom,BYTE		;copy of GPO register

	SYS_VAR b_chunk,2		;chunk address storage (COPY BLOCKS)
	SYS_VAR b_page,1		;page for chunk address
	SYS_VAR b_trans,1		;transparent colour
	SYS_VAR n_colours,7	;COPY block colour table (n-plane)

	SYS_VAR cpy_temp,BLITSIZE	;copy block blitter template
	SYS_VAR cpy_copy,BLITSIZE	;copy copy blitter program

	SYS_VAR last_char,BYTE	;last char printed by WORD_FIT
	SYS_VAR to_copy,BYTE	;how much of a sprite is to be updated


;---------------------------------------------------------------------
;Memory allocated to the user follows on from the system memory. The
;same variable counter is used, in a different macro
;

