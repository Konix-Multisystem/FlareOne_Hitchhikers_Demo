

wait16.	MACRO
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	ENDM



; The next section contains the DSP program for sample replay

; This bit contains the code for handling sample playback during the head
; invaders game. It plays two samples concurrently, one to the left channel
; and one to the right.
; It should be noted the the time required to get sample data or not to get
; it should take the same time. This is done by padding out with INTRUDEs.

;---------------------------------------------------------------------
;The DSP program/data include file. Firstly defined are the start
;addresses of both code and data

DSP_progst2 equ 0	;DSP program start address.
DSP_datast2 equ 0	;DSP data start address


;---------------------------------------------------------------------
;Now for the templates for the data and program code. The User should
;insert their code/program between the various starts and ends.
;
;
;The ONLY label which should be accessed by the Z80 program which
;includes this file is dsp_chunk.
;

;The DSP program segment

dsp_chunk2	defw DSP_progst2,(prog_end2-prog_st2)/2
prog_org2	org $,DSP_progst2

prog_st2	mov. ax,l_len	; get remaining length for left sample
	sub. _ONE	; if carry then no length left

	mov. ax,branch1	; value is sdfsdf - sdfsdf
	adinc. _no_left	; address to jump to if no left sample
	mov. newpc,az	; save value of new PC

	mov. pc,newpc	; set the pc up
	nop.		; needed after setting PC

	; 6 cycles for above bit

	; This bit sets up the data for the left channel to play
	; It takes 53 cycles

play_left	mov. ax,l_len	; decrement amount of sample left
	sub. _ONE
	mov. l_len,az

	; get sample data

	mov. dma1,l_adrhi

	mov. _junk,dmd	; set DMA to read data
	mov. dma0,l_adrlo
	; now wait 20 cycles for bus latency
	mov. ax,l_adrlo
	add. _TWO
	mov. l_adrlo,az	; increment sample ptr (only changes low word)

	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	mov. _temp,dmd	; get sample word into temporary storage

	mov. ax,_temp
	and. _LOW_BYTE
	mov. l_sample1,az

	mov. mx,mult256
	mov. my,l_sample1

	intrude.
	intrude.
	intrude.
	intrude.
	mov. l_sample1,mz0
	mov. _junk,mz1	; clear multiplier

	mov. ax,l_sample1
	add. xor32768		; invert top bit
	mov. l_sample1,az

	; now calculate the second byte of sample

	mov. ax,_temp
	and. HIGH_BYTE
	mov. l_sample2,az

	mov. ax,l_sample2
	add. xor32768		; invert top bit
	mov. l_sample2,az

	; now go and check the right sample data

	mov. pc,_do_right
	nop.

	; This bit is called if the left channel is quiet
	; it is padded out to 53 cycles

no_left	mov. ax,xor32768		; set playback value for silence
	mov. l_sample1,ax
	mov. l_sample2,ax

	mov. ax,l_repeat		; is this a repeating sample
	sub. _ONE		; carry set if value was zero

	mov. ax,branch2
	adinc. _norep_lft
	mov. newpc,az
	mov. pc,newpc
	nop.

rep_left	mov. ax,l_replo		; set up sample source addr & length
	mov. l_adrlo,ax
	mov. ax,l_rephi
	mov. l_adrhi,ax
	mov. ax,l_replen
	mov. l_len,ax

	; put in sync delay here (INTRUDEs 23)

	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.

	; now go and check the right sample data

	mov. pc,_do_right
	nop.

	; This bit handles the case of no sample and no repeat

norep_left	mov. dma1,l_Z80finhi	; set high word of address

	mov. dmd,_ZERO	; set Z80 left sample finished flag
	mov. dma0,l_Z80finlo
	; now wait 20 cycles for bus latency

	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.


	; put in sync delay here (INTRUDEs)

	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.

	; This bit sets up the data for the right channel to play
	; It takes 53 cycles

do_right	mov. ax,r_len	; get remaining length for right sample
	sub. _ONE	; if carry then no length left

	mov. ax,branch3
	adinc. _no_right	; address to jump to if no right sample
	mov. newpc,az	; save value of new PC

	mov. pc,newpc	; set the pc up
	nop.		; needed after setting PC

	; 6 cycles for above bit

play_right	mov. ax,r_len	; decrement amount of sample left
	sub. _ONE
	mov. r_len,az

	; get sample data

	mov. dma1,r_adrhi

	mov. _junk,dmd	; set DMA to read data
	mov. dma0,r_adrlo
	; now wait 20 cycles for bus latency
	mov. ax,r_adrlo
	add. _TWO
	mov. r_adrlo,az	; increment sample ptr (only changes low word)

	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	mov. _temp,dmd	; get sample word into temporary storage

	mov. ax,_temp
	and. _LOW_BYTE
	mov. r_sample1,az

	mov. mx,mult256
	mov. my,r_sample1

	intrude.
	intrude.
	intrude.
	intrude.
	mov. r_sample1,mz0
	mov. _junk,mz1	; clear multiplier

	mov. ax,r_sample1
	add. xor32768		; invert top bit
	mov. r_sample1,az

	; now calculate the second byte of sample

	mov. ax,_temp
	and. HIGH_BYTE
	mov. r_sample2,az

	mov. ax,r_sample2
	add. xor32768		; invert top bit
	mov. r_sample2,az

	; now go and play the samples

	mov. pc,_play
	nop.

	; This bit is called if the right channel is quiet
	; it is padded out to 53 cycles

no_right	mov. ax,xor32768		; set playback value for silence
	mov. r_sample1,ax
	mov. r_sample2,ax

	mov. ax,r_repeat		; is this a repeating sample
	sub. _ONE		; carry set if value was zero

	mov. ax,branch4
	adinc. _norep_rgt
	mov. newpc,az
	mov. pc,newpc
	nop.

rep_rght	mov. ax,r_replo		; set up sample source addr & length
	mov. r_adrlo,ax
	mov. ax,r_rephi
	mov. r_adrhi,ax
	mov. ax,r_replen
	mov. r_len,ax

	; put in sync delay here (INTRUDEs 23)

	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.

	; now go and play the samples

	mov. pc,_play
	nop.

	; This bit handles the case of no sample and no repeat

norep_rght	mov. dma1,r_Z80finhi	; set high word of address

	mov. dmd,_ZERO	; set Z80 right sample finished flag
	mov. dma0,r_Z80finlo
	; now wait 20 cycles for bus latency

	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.

	; put in sync delay here (INTRUDEs)

	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.

	; play samples at 9.25kHz

play	wait16.
	wait16.
	wait16.
	wait16.
	wait16.
	wait16.
	wait16.
	wait16.
	wait16.
	wait16.
	wait16.
	wait16.
	wait16.
	wait16.
	wait16.
	wait16.
	LEFT. l_sample1		; write out the low byte of sample

	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	RIGHT. r_sample1		; do the same for the right channel

	wait16.
	wait16.
	wait16.
	wait16.
	wait16.
	wait16.
	wait16.
	wait16.
	wait16.
	wait16.
	wait16.
	wait16.
	wait16.
	wait16.
	wait16.
	wait16.
	wait16.
	wait16.
	wait16.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	LEFT. l_sample2		; write out the high byte of sample

	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	intrude.
	RIGHT. r_sample2		; do the same for the right channel


	; now go back and do it all over again

	mov. pc,_prog_st
	nop.


;Reset the Z80 pc temporarily, DSP chunk data info -------------------

prog_end2	defw DSP_datast2,(data_end2-data_st2)/2
	org $-DSP_progst2+prog_org2


;Now for the DSP data segment ----------------------------------------

data_org2	org $,DSP_datast2
data_st2	defw 0	; DATA HERE !!!!

mult256	defw 256
xor32768	defw 32768

_ZERO	defw 0	; used for flagging the end of a sample
_TWO	defw 2	; for incrementing DMA
_ONE	defw 1	; for incrementing data pointer
HIGH_BYTE	defw 0ff00h
_LOW_BYTE	defw 000ffh

_junk	defw 0	; junk (often used in clearing the multiplier)
_temp	defw 0	; temporary storage


; Data storage for jump addresses and branch offsets

newpc	defw 0	; storage for pc calculated after a branch

_prog_st	defw prog_st2/2
_play_left	defw play_left/2
_do_right	defw do_right/2
_no_left	defw no_left/2
_norep_lft	defw norep_left/2
_play_rght	defw play_right/2
_no_right	defw no_right/2
_norep_rgt	defw norep_rght/2
_play	defw play/2

; Branch values

branch1	defw play_left/2-no_left/2
branch2	defw rep_left/2-norep_left/2
branch3	defw play_right/2-no_right/2
branch4	defw rep_rght/2-norep_rght/2

; Data for the left sample

l_len	defw 0
l_adrlo	defw 0
l_adrhi	defw 0
l_repeat	defw 0
l_replen	defw 0
l_replo	defw 0
l_rephi	defw 0
l_sample1	defw 0
l_sample2	defw 0

l_Z80finhi	defw cpmpage	; pointer to left channel sample finish code
l_Z80finlo	defw l_Z80fin

; Data for the right sample

r_len	defw 0
r_adrlo	defw 0
r_adrhi	defw 0
r_repeat	defw 0
r_replen	defw 0
r_replo	defw 0
r_rephi	defw 0
r_sample1	defw 0
r_sample2	defw 0

r_Z80finhi	defw cpmpage	; pointer to right channel sample finish code
r_Z80finlo	defw r_Z80fin

;Reset the Z80 program counter for following code/data ---------------

data_end2	org $-DSP_datast2+data_org2



