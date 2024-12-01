
; The following are special wait macros necessary due to the crappy
; macro facilities included in PDS.

WAIT7.	MACRO
	nop.
	nop.
	nop.
	nop.
	nop.
	nop.
	nop.
	ENDM


WAIT11.	MACRO
	nop.
	nop.
	nop.
	nop.
	nop.
	nop.
	nop.
	nop.
	nop.
	nop.
	nop.
	ENDM


WAIT17.	MACRO
	nop.
	nop.
	nop.
	nop.
	nop.
	nop.
	nop.
	nop.
	nop.
	nop.
	nop.
	nop.
	nop.
	nop.
	nop.
	nop.
	nop.
	ENDM


;---------------------------------------------------------------------
;The DSP program/data include file. Firstly defined are the start
;addresses of both code and data

DSP_progst	equ 0		;DSP program start address.
DSP_datast	equ 0		;DSP data start address


;---------------------------------------------------------------------
;Now for the templates for the data and program code. The User should
;insert their code/program between the various starts and ends.
;
;
;The ONLY label which should be accessed by the Z80 program which
;includes this file is dsp_chunk.
;

;The DSP program segment

dsp_chunk	defw DSP_progst,(prog_end-prog_st)/2
prog_org	org $,DSP_progst

prog_st	mov. ax,vsrc	; set up temporary DMA read/write addresses
	mov. rdma,ax
	mov. ax,vdest
	mov. wdma,ax

	mov. dma1,codebank	; Set DMA high word address
	mov. ax,codebank
	mov. wdmah,ax		; Write them back to z80 memory.

	mov. junk,dmd	; set DMA to read data
	mov. dma0,rdma
	; now wait 20 cycles for bus latency
	mov. ax,rdma
	add. TWO
	mov. rdma,az
	wait17.
	mov. sX,dmd	; get value for sin(X)

	mov. dma0,rdma
	; now wait 20 cycles for bus latency
	mov. ax,rdma
	add. TWO
	mov. rdma,az
	wait17.
	mov. cX,dmd	; get value for cos(X)

	mov. dma0,rdma
	; now wait 20 cycles for bus latency
	mov. ax,rdma
	add. TWO
	mov. rdma,az
	wait17.
	mov. sY,dmd	; get value for sin(Y)

	mov. dma0,rdma
	; now wait 20 cycles for bus latency
	mov. ax,rdma
	add. TWO
	mov. rdma,az
	wait17.
	mov. cY,dmd	; get value for cos(Y)

	mov. dma0,rdma
	; now wait 20 cycles for bus latency
	mov. ax,rdma
	add. TWO
	mov. rdma,az
	wait17.
	mov. scale,dmd	; get value for the enlarging scale factor

	mov. dma0,rdma
	; now wait 20 cycles for bus latency
	mov. ax,rdma
	add. TWO
	mov. rdma,az
	wait17.
	mov. vnum,dmd	; get number of vertices to calculate

;	MARTIN'S KLUDGE

	mov. dma0,rdma
	; now wait 20 cycles for bus latency
	mov. ax,rdma
	add. TWO
	mov. rdma,az
	wait17.
	mov. temp,dmd	; get new address of input vertices.

	mov. dma0,rdma
	; now wait 20 cycles for bus latency
	mov. ax,rdma
	add. TWO
	mov. rdma,az
	wait17.
	mov. rdmah,dmd	; get high word of vertex addresses.

	mov.	ax,temp	; change the read address used for 		
	mov.	rdma,ax    ; fetching vertices.


; Now calculate the coefficients for the rotation matrix

	mov. junk,mz1	; clear multiplier result

	mov. mx,cX	; calculate cos(X)*sin(Y)
	mov. my,sY
	wait7.	; wait for result
	mov. cXsY,mz0

	mov. junk,mz1	; clear multiplier result

	mov. mx,sX	; calculate sin(X)*sin(Y)
	mov. my,sY
	wait7.	; wait for result
	mov. sXsY,mz0

	mov. junk,mz1	; clear multiplier result

	mov. mx,cX	; calculate cos(X)*cos(Y)
	mov. my,cY
	wait7.	; wait for result
	mov. cXcY,mz0

	mov. junk,mz1	; clear multiplier result

	mov. mx,sX	; calculate sin(X)*cos(Y)
	mov. my,cY

; While waiting for the result lets negate sin(X) and sin(Y)
; In 16 bit signed -x = 65536-x = 0-x !!!!!!!!!

	mov. ax,NEGATE
	sub. sX
	mov. sX,az	; put the negated sin(X) back
	mov. ax,NEGATE
	sub. sY
	mov. sY,az

	nop.		; wait for result of the last multiply
	mov. sXcY,mz0

; Now multiply sin(X), cos(X), sin(Y), cos(Y) by 128 to put them on the
; same level as cXsY etc.

	mov. junk,mz1	; clear multiplier result

	mov. mx,LSL7	; calculate sin(X)*128
	mov. my,sX
	wait7.	; wait for result
	mov. sX,mz0

	mov. junk,mz1	; clear multiplier result

	mov. mx,LSL7	; calculate cos(X)*128
	mov. my,cX
	wait7.	; wait for result
	mov. cX,mz0

	mov. junk,mz1	; clear multiplier result

	mov. mx,LSL7	; calculate sin(Y)*128
	mov. my,sY
	wait7.	; wait for result
	mov. sY,mz0

	mov. junk,mz1	; clear multiplier result

	mov. mx,LSL7	; calculate cos(Y)*128
	mov. my,cY
	wait7.	; wait for result
	mov. cY,mz0

; This is the main loop and is used to get, calculate and then write
; the vertices.

loop	mov. junk,dmd	; set DMA to read
	mov. dma1,rdmah	; MARTIN WOZ HERE
	mov. dma0,rdma
	; now wait 20 cycles for bus latency
	mov. ax,rdma
	add. TWO
	mov. rdma,az
	wait17.
	mov. x3,dmd	; get the x coordinate

	mov. dma0,rdma
	; now wait 20 cycles for bus latency
	mov. ax,rdma
	add. TWO
	mov. rdma,az
	wait17.
	mov. y3,dmd	; get the y coordinate

	mov. dma0,rdma
	; now wait 20 cycles for bus latency
	mov. ax,rdma
	add. TWO
	mov. rdma,az
	wait17.
	mov. z3,dmd	; get the z coordinate

; Calculate the rotated x coordinate

	mov. mx,x3	; - cos(Y)*X
	mov. my,cY
	wait7.

	mov. mx,y3	; + sin(X)*sin(Y)*Y
	mov. my,sXsY
	wait7.

	mov. mx,z3	; + cos(X)*sin(Y)*Z
	mov. my,cXsY
	wait7.

	; Now add .5 (8192 effectively) and shift up 2 bits
	
	mov. resultlo,mz0
	mov. resulthi,mz1

	mov. ax,resultlo
	add. resultlo
	mov. resultlo,az
	mov. ax,resulthi
	adc. resulthi
	mov. resulthi,az		; result * 2

	mov. ax,resultlo
	add. resultlo
	mov. resultlo,az
	mov. ax,resulthi
	adc. resulthi
	mov. newx3,az		; result * 4

; Calculate the rotated y coordinate

	mov. mx,y3	; + cos(X)*Y
	mov. my,cX
	wait7.

	mov. mx,z3	; - sin(X)*Z
	mov. my,sX
	wait7.

	; Now shift up 2 bits
	
	mov. resultlo,mz0
	mov. resulthi,mz1

;	mov. ax,resultlo		; add in 8192(0.5) (14 bit fractions)
;	add. HALF
;	mov. resultlo,az
;	mov. ax,resulthi
;	adc. ZERO
;	mov. resulthi,az

	mov. ax,resultlo
	add. resultlo
	mov. resultlo,az
	mov. ax,resulthi
	adc. resulthi
	mov. resulthi,az		; result * 2

	mov. ax,resultlo
	add. resultlo
	mov. resultlo,az
	mov. ax,resulthi
	adc. resulthi
	mov. newy3,az		; result * 4

; Calculate the rotated z coordinate

	mov. mx,x3	; - sin(Y)*X
	mov. my,sY
	wait7.

	mov. mx,y3	; + sin(X)*cos(Y)*Y
	mov. my,sXcY
	wait7.

	mov. mx,z3	; + cos(X)*cos(Y)*Z
	mov. my,cXcY
	wait7.

	; Now shift up 2 bits
	
	mov. resultlo,mz0
	mov. resulthi,mz1

;	mov. ax,resultlo		; add in 8192(0.5) (14 bit fractions)
;	add. HALF
;	mov. resultlo,az
;	mov. ax,resulthi
;	adc. ZERO
;	mov. resulthi,az

	mov. ax,resultlo
	add. resultlo
	mov. resultlo,az
	mov. ax,resulthi
	adc. resulthi
	mov. resulthi,az		; result * 2

	mov. ax,resultlo
	add. resultlo
	mov. resultlo,az
	mov. ax,resulthi
	adc. resulthi
	mov. newz3,az		; result * 4

; The next bit will do a perspective transformation soon (I HOPE!!!!!!!!!)
; Calculation is not quite true perspective but uses a vanishing point
; rather than a view point to avoid nasty divisions that the DSP can't
; handle. Equation is (x*(z+256+enlarging_factor))/256. Same for y.

	mov. mx,divvanp	; vanp = 512 so mult 128 since 65536/512 = 128
	mov. my,newx3	; since words *128 = /512 if you take top word

	mov. ax,vanp	; while waiting calc the nasty number
	add. scale
	mov. junk,az	; 512+enlarging_factor
	mov. ax,junk
	add. newz3
	mov. junk,az	; z+512+enlarging_factor
	nop.		; wait for multiply to finish
	mov. resultlo,mz0
	mov. junk1,mz1	; clear multiplier

	mov. mx,junk	; now do final multiplication
	mov. my,resultlo
	wait7.	; wait for it to finish
	mov. newx3,mz1	; put the result back
			; now do it for the y coord

	mov. mx,divvanp	; vanp = 512
	mov. my,newy3	; since words *128 = /512 if you take top word
	wait7.
	mov. resultlo,mz0
	mov. junk1,mz1	; clear multiplier

	mov. mx,junk	; now do final multiplication
	mov. my,resultlo
	wait7.	; wait for it to finish
	mov. newy3,mz1

; Now adjust the y coord for the aspect ratio of the screen y = y * 5 / 4

	mov. mx,FIVE
	mov. my,newy3
	wait7.
	mov. newy3,mz0	; y * 5
	mov. junk,mz1	; clear multiplier

	mov. mx,newy3
	mov. my,DIVFOUR
	wait7.
	mov. newy3,mz1	; y * 5 / 4

; Now add the offset into the screen of the origin and mask out the top byte

	mov. ax,newx3
	add. OFFSET_X
	mov. x2,az

	mov. ax,newy3
	add. OFFSET_Y
	mov. y2,az

	mov. ax,x2
	and. LOW_BYTE
	mov. x2,az

	mov. ax,y2
	and. LOW_BYTE
	mov. y2,az

; Now send the new coords to the Z80's memory

	mov. dmd,x2
	mov. dma1,wdmah
	mov. dma0,wdma
	mov. ax,wdma
	add. TWO
	mov. wdma,az
	wait17.

	mov. dmd,y2
	mov. dma0,wdma
	mov. ax,wdma
	add. TWO
	mov. wdma,az
	wait17.

; Now send the Z coordinate for the normals

	mov. ax,newz3
	and. LOW_BYTE
	mov. junk,az

	mov. dmd,junk
	mov. dma0,wdma
	mov. ax,wdma
	add. TWO
	mov. wdma,az

; Check to see if we have finished

	mov. ax,vnum	; number of vertices left to do
	sub. ONE
	mov. vnum,az

	mov. ax,loopdiff	; loopdiff = cont - fin
	adinc. _fin
	mov. junk,az

	wait11.	; wait for bus latency (17 - above cycles)

	mov. pc,junk
	nop.

; Now send the finished code to the Z80's memory

fin	mov. dmd,TERM_CODE
	mov. dma0,wdma

finish	mov. pc,_finish
	nop.

cont	mov. pc,_loop
	nop.


;Reset the Z80 pc temporarily, DSP chunk data info -------------------

prog_end	defw DSP_datast,(data_end-data_st)/2
	org $-DSP_progst+prog_org


;Now for the DSP data segment ----------------------------------------

data_org	org $,DSP_datast
data_st	defw 0	; DATA HERE !!!!
junk	defw 0	; just a junk word (like RUBBISH!!!!!!!)
junk1	defw 0

resultlo	defw 0
resulthi	defw 0

ZERO	defw 0	; used for adding carry only
HALF	defw 8192	; equals 0.5 in 14 bit maths!!!
TWO	defw 2	; for incrementing DMA
ONE	defw 1	; for incrementing data pointer
NEGATE	defw 0	; used in negating sines
LSL7	defw 128	; used to shift left 7 bits
LOW_BYTE	defw 255	; used to mask out rubbish in coord results
OFFSET_X	defw w1_xs+(w1_xz/2)	; X offset to origin on the screen
OFFSET_Y	defw w1_ys+(w1_yz/2)	; Y offset to origin on the screen

TERM_CODE	defw 65535	; code to tell the Z80 that the DSP has finished
_fin	defw fin/2
_finish	defw finish/2	; address to leave the DSP at when its done
_loop	defw loop/2	; address for looping
loopdiff	defw (cont-fin)/2	; used for end of loop conditional jump

temp	defw 0	; MARTIN's 
vsrc	defw dsp_src	; Source address for 3d vertices
vdest	defw dsp_dest	; Destination address for 2d vertices
rdma	defw 0	; DMA read address
rdmah 	defw 0	; DMA read address high
wdma	defw 0	; DMA write address
wdmah	defw 0	; DMA write address high
codebank	defw 4	; bank of memory that contains the code

FIVE	defw 5	; used in y * 5/4
DIVFOUR	defw 16384	; as above
vanp	defw 512	; vanishing point for perspective
divvanp	defw 128	; 65536/vanp = 128
scale	defw 0	; used for increasing the size of the cube

vnum	defw 0	; number of vertices

x3	defw 0	; 3d X coordinate
y3	defw 0	; 3d Y coordinate
z3	defw 0	; 3d Z coordinate

newx3	defw 0	; rotated 3d X coordinate
newy3	defw 0	; rotated 3d Y coordinate
newz3	defw 0	; rotated 3d Z coordinate

x2	defw 0	; 2d X coordinate
y2	defw 0	; 2d Y coordinate

cX	defw 0	; value of cos(X)
cY	defw 0	; value of cos(Y)
sX	defw 0	; value of sin(X) (negate for actual use)
sY	defw 0	; value of sin(Y) (negate for actual use)
cXsY	defw 0	; value of cos(X)*sin(Y)
sXsY	defw 0	; value of sin(X)*sin(Y)
cXcY	defw 0	; value of cos(X)*cos(Y)
sXcY	defw 0	; value of sin(X)*cos(Y)



;Reset the Z80 program counter for following code/data ---------------

data_end	org $-DSP_datast+data_org


