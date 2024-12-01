


;------------------------- Copyright A.t.d. 1988 ---------------------
;
;LOW_INC.INC
;
;Low level routines interface. MACROS which call each low level
;routine with the correct parameters in the correct registers.
;This file is an include file and should be included in all files
;which use the low level routines....
;
;
;Because of the fact that PDS does not link files, there is no need
;for the declaration of GLOBALS or EXTERNAL labels. Hence this also
;means that there is no need for MAC_INC.INC, because this file now
;performs its function
;
;
;Macros:
;	initialise	initialise various blitter blocks. NP
;	draw_blit	NOT AVAILABLE TO USER.
;	del_blit	NOT AVAILABLE TO USER.
;	plot		insert plot blit. B,C=Y,X coords
;	set_pink	set the plotting ink. A=new colour
;          cline		insert COLOUR line. B,C=Y1,X1, D,E=Y2,X2, A= col
;	line		insert line blit. B,C=Y1,X1, D,E=Y2,X2
;	cpline	insert partial line with colour. A= col
;	pline		insert partial line. B,C=Y1,X1, D,E=Y2,X2
;	set_link	set the line drawing ink. A=new colour
;	copy		insert copy blit. AHL=chunk addr, B,C=Y,X pos
;	sprite	insert sprite frame. as above, E=frame number
;	fill		insert fill. B,C=Y,X start, D,E=Y,X size, A=col
;	cls		clear one/both screens. PARAM: which, colour
;	set_border	set the border colour. PARAM: colour
;	window	initialise a window. PARAM: handle, def pointer
;	clw		clear the current window. NP
;	current	set the current window. A=handle
;	paper		set the current windows paper colour. A=colour
;	ink		set current wind ink colour (N-PLANE). A=colour
;	erase_on	enable backgrnd erasing before printing. NP
;	erase_off	disable backgrnd erasing before printing. NP
;	pchar		print a character in current window. C=char
;	pstring	print a string in current window. HL=string ptr
;	word_fit	tests a word for fitting on line. HL=word ptr
;	hcursor	set hi res cursor pos. B,C=Y,X coords
;	cursor	set character cursor pos. B,C=Y,X char coords
;	get_coords	get the cursor position for curr W. BC returned
;	font		set current windows font. HLA=address chunk
;	scroll	scroll Cwin up 1 pixel. AHL=addr of fill data
;	draw_screen	draw screen, erase old AND swap if necessary
;	swaps		NOT AVAILABLE TO USER
;	load_dsp	load DSP with program and data. HL=address chunk
;	run_dsp	run DSP from HL address. HL=address
;	read_dsp	get data from DSP. HL=data address and ret val
;	write_dsp	write data to DSP. hl=12 bit intrude, de=data
;	intrude_at	set intrude address. HL=12 bit address
;	dsp_data	send data to DSP. DE=data for sending
;	dsp_data_inc	send data to DSP with auto-increment. DE=data
;	set_hires	set physical screen mode to hi res. NP
;	set_lores	set physical screen mode to lo res. NP
;	hold_on	enable colour hold mode. NP
;	hold_off	disable colour hold mode. NP
;	blit_run	run blitter prog. NOT AVAILABLE TO THE USER
;	random	return 16/8 bit random number. BC/A=result
;	to_front	set front screen to be SCRBASE
;	bright_pt	set partial line bright point colour to ACC
;	percentage	set the amount of line to be drawn. Acc=length
;	permanent	sets current blitter list as non-deletable.
;	int_line	set the interrupt line. BC=line number
;	copy_some	only copy PARAM lines of a sprite. Acc=param
;	copy_all	Copy all of sprites, all of time. NP
;	re_colour	Set colour value for erasing blits. Acc=colour
;	load_rgb	Load a palette into the palette board
;
;
; ====================================================================
; === Now for the macro definitions which do the BIZ as they say. ====
; ====================================================================
;
;Initialise certain blitter blocks (CLS etc) into RAM for mods.
;
;IN: all registers DESTROYED....
;

initialise	MACRO
	call f_initialise
	ENDM


;---------------------------------------------------------------------
;Run the blitter with the correct blitter list
;
;IN: nowt
;

draw_blit	MACRO
	call f_drawblit
	ENDM


;---------------------------------------------------------------------
;Erase operations just done to the background colour of the screen
;
;IN: nowt
;

del_blit	MACRO
	call f_del_blit
	ENDM


;---------------------------------------------------------------------
;Place a plot template (filled) in the blitter buffer for later
;execution
;
;IN: b=Y coodinate of point, c=X coordinate of point
;

plot	MACRO
	call f_plot
	ENDM


;---------------------------------------------------------------------
;Set the ink colour for plotting
;
;IN: accumulator=new colour
;

set_pink	MACRO
	call f_p_ink
	ENDM


;---------------------------------------------------------------------
;Draw a coloured line. As line (below) EXCEPT that the colour of the
;line is also passed as a parameter. The colour is not adjusted on
;mode, that is the users responsibility. NOTE that the system variable
;line_col is affected by this command.
;
;IN: B,C=Y1,X1, D,E=Y2,X2. Accumulator=colour of line
;

cline	MACRO
	call f_cline
	ENDM

;---------------------------------------------------------------------
;Draw a line from start to finish
;
;IN: b=Y start coord, c=X start coord. d=Y finish coord, e= X finish
;

line	MACRO
	call f_line
	ENDM


;---------------------------------------------------------------------
;As partial line, except that the colour of the line is passed as a
;parameter.
;
;IN: see below, A=colour
;

cpline	MACRO
	call f_cpline
	ENDM


;---------------------------------------------------------------------
;Draw part of a line (depending on line_len) and highlight the last
;pixel in a given colour (taken from bright_col)
;
;IN: B,C=Y,X start, D,E=Y,X finish
;

pline	MACRO
	call f_pline
	ENDM


;---------------------------------------------------------------------
;Set the line drawing colour
;
;IN: accumulator=new colour
;

set_link	MACRO
	call f_l_ink
	ENDM


;---------------------------------------------------------------------
;Copy a chunk to the screen
;
;IN: de=address of the block. The block defines the data dimensions
;

copy	MACRO
	call f_copy
	ENDM


;---------------------------------------------------------------------
;Insert a sprite blit into blitter list. E=frame of sprite chunk to
;print to the screen.
;
;IN as above, E=frame number
;

sprite	MACRO
	call f_sprite
	ENDM


;---------------------------------------------------------------------
;Fill a region of memory (usually the screen)
;
;IN: b=Y start, c=X start, d= Y size, e=X size, a=value
;

fill	MACRO
	call f_fill
	ENDM


;---------------------------------------------------------------------
;Clear either back screen, visible screen or both !
;
;IN: b set to which, c set to the colour
;

cls	MACRO
	ld bc,@2+256*@1
	call f_cls
	ENDM


;---------------------------------------------------------------------
;Set the main screen border colour
;
;IN: Accumulator set to border colour
;

set_border	MACRO
	ld a,@1
	out (BORDER),a
	ENDM


;---------------------------------------------------------------------
;Set a windows parameters up i.e. size and error routine
;
;IN: hl points to 8 bytes which define the minimum number of things
;    the window routine pads out the rest.
;

window	MACRO
	ld a,@1
	ld hl,@2
	call f_window
	ENDM


;---------------------------------------------------------------------
;clear the current window to its paper colour
; 
;IN: nowt
;

clw	MACRO
	call f_clw
	ENDM


;---------------------------------------------------------------------
;Set the current window
;
;IN: accumulator=new window number (0->7)
;

current	MACRO
	call f_current
	ENDM


;---------------------------------------------------------------------
;Set the paper colour of the current window
;
;IN: accumulator= new background (paper) colour, ix DESTROYED
;

paper	MACRO
	ld ix,(cur_base)	;get current windows base address
	ld (ix+W_PAPER),a
	ENDM


;---------------------------------------------------------------------
;Set the ink colour for N-PLANE character fonts. Only for use when
;font has 1 palne !
;
;IN: accumulator= new background (ink) colour, ix DESTROYED
;

ink	MACRO
	ld ix,(cur_base)	;get current windows base address
	ld (ix+W_INK),a
	ENDM


;---------------------------------------------------------------------
;Set the flag for erasing BEFORE printing to be ON
;
;IN: ix DESTROYED
;

erase_on	MACRO
	ld ix,(cur_base)		;get current window's base address
	set 7,(ix+W_ERASE)	;set correct bit !
	ENDM


;---------------------------------------------------------------------
;Sets the flag for erasing BEFORE printing to be OFF
;
;IN: ix DESTROYED
;

erase_off	MACRO
	ld ix,(cur_base)		;get current window's base address
	res 7,(ix+W_ERASE)	;reset correct bit !
	ENDM


;---------------------------------------------------------------------
;Print a character in the current window
;
;IN: c=ASCII code of the character to be printed
;

pchar	MACRO
	call f_pchar
	ENDM


;---------------------------------------------------------------------
;Print a string, including word wrap.
;
;IN: hl=address of the string (pointer to the string).
;

pstring	MACRO
	call f_pstring
	ENDM


;---------------------------------------------------------------------
;Tests a word for fitting on current line when printing text. If it
;will not then prints a newline character.
;
;IN: hl points to word. ALL REGISTERS DESTROYED
;

word_fit	MACRO
	call f_word_fit
	ENDM


;---------------------------------------------------------------------
;Set the window coords for printing in pixel coords
;
;IN: b=Y coord, c=X coord (in pixels)
;

hcursor	MACRO
	ld ix,(cur_base)
	ld (ix+W_CURSX),c
	ld (ix+W_CURSY),b
	ENDM


;---------------------------------------------------------------------
;Set the window coords for printing, in CHARACTER coords
;
;IN: b=Ychar coord, c=X char coord
;

cursor	MACRO
	call f_cursor
	ENDM


;---------------------------------------------------------------------
;Get the current coords (in pixels !) from the current window
;
;IN: nowt, B,C returned as Y,X position
;

get_coords	MACRO
	ld ix,(cur_base)
	ld b,(ix+W_CURSY)
	ld c,(ix+W_CURSX)
	ENDM


;---------------------------------------------------------------------
;Set the font for the current window
;
;IN: hla=20 bit address of the font in question
;

font	MACRO
	call f_font
	ENDM


;---------------------------------------------------------------------
;Scroll the current window upward C pixels. Line at bottom cleared
;to correct paper colour
;
;IN: C=number of pixels
;

scroll	MACRO
	call f_scroll
	ENDM


;---------------------------------------------------------------------
;This routine draws the current blitter list, erases the old one,
;synchronises drawing/swapping of the screens and generally does
;EVERYTHING ! depending on whether or not screen swapping is enabled
;
;IN: nowt
;

draw_screen MACRO
	call f_draw_screen
	ENDM


;---------------------------------------------------------------------
;Swap visible flag, and operative blit buffer. If swapping enabled
;then change the screen pointer.
;
;IN: nowt
;

swaps	MACRO
	call f_swaps
	ENDM


;---------------------------------------------------------------------
;Load the DSP with program and data
;
;IN: hl=address of DSP chunk. Program/data definitions is internal
;

load_dsp	MACRO
	call f_load_dsp
	ENDM


;---------------------------------------------------------------------
;Run the DSP from a given address
;
;IN: hl=address to be run from, accumulator destroyed
;

run_dsp	MACRO
	xor a
	out (RUNST),a	;BUGFIX -stop the blitter first
	ld a,l
	out (PROGRAM),a	;tell it the program start address
	ld a,h
	out (PROGRAM),a
	in a,(RUNST)	;set it running
	set 0,a
	out (RUNST),a
	ENDM


;---------------------------------------------------------------------
;Synchronise with the DSP
;
;IN: hl=12 bit address to get a data value from, also the returned value
;

read_dsp	MACRO
	call f_read_dsp
	ENDM


;---------------------------------------------------------------------
;Synchronise with the DSP, then write data to intrude address
;
;IN: hl=12 bit address to write to, de=16 bit data write value
;

write_dsp	MACRO
	call f_write_dsp
	ENDM


;---------------------------------------------------------------------
;Set the intrude address for the DSP.
;
;IN: hl=12 bit address to write to intrude register
;

intrude_at	MACRO
	ld a,l
	out (INTRA),a
	ld a,h
	out (INTRA),a 
	ENDM


;---------------------------------------------------------------------
;Send data to the DSP intrude register, without auto incrementing.
;
;IN: de=word of data
;

dsp_data	MACRO
	ld a,e
	out (INTRD),a	;send word to correct port, LOW
	ld a,d
	out (INTRD),a	;then HIGH
	ENDM


;---------------------------------------------------------------------
;Send data to the DSP intrude register, with auto increment ON.
;
;IN: de=word of data
;

dsp_data_inc MACRO
	ld a,e
	out (INTRDP),a	;send to POST increment port
	ld a,d
	out (INTRDP),a 
	ENDM


;---------------------------------------------------------------------
;Set the Physical screen to hires i.e. 256*200 in 256 colours
;
;IN: accumulator DESTROYED
;

set_hires	MACRO
	ld a,(cmd2m)	;tell the flare about it
	set 0,a
	ld (cmd2m),a
	out (CMD2),a
	ENDM


;---------------------------------------------------------------------
;Set the physical screen to lores i.e. 256*200 in 16 colours
;
;IN: accumulator DESTROYED
;

set_lores	MACRO 
	ld a,(cmd2m)	;tell the Flare about it !
	res 0,a
	ld (cmd2m),a
	out (CMD2),a
	ENDM


;---------------------------------------------------------------------
;Set colour hold on
;
;IN: transparent colour in Accumulator, accumulator DESTROYED
;

hold_on	MACRO
	out (TRANS),a	;tell it the transparent colour
	ld a,(cmd2m)	;switch it on !
	set 3,a
	ld (cmd2m),a
	out (CMD2),a 
	ENDM


;---------------------------------------------------------------------
;Turn colour hold off
;
;IN: nowt, accumulator DESTROYED
;

hold_off	MACRO
	ld a,(cmd2m)	;switch colour hold off
	res 3,a
	ld (cmd2m),a
	out (CMD2),a
	ENDM


;---------------------------------------------------------------------
;Run a blitter program macro. NOT AVAILABLE FOR USER USE.
;only for low level use !
;
;IN: hla=address of blitter program, accumulator set to bits 16-23
;	then the command to set it going.
;

blit_run	MACRO page,cmd
	ld a,l
	out (BLPC0),a	;send the address in correct order
	ld a,h
	out (BLPC1),a
	ld a,page
	out (BLPC2),a

	ld a,cmd	;send the command now
	out (BLCMD),a
	ENDM


;---------------------------------------------------------------------
;Returns a 16 bit random number
;
;IN: nowt, bc=number returned, accumulator points to c also
;

random 	MACRO
	call f_random
	ENDM


;---------------------------------------------------------------------
;Sets scrbase to be the visible screen. Also initialises visible
;
;IN: nowt, acc DESTROYED, hl DESTROYED
;

to_front	MACRO
	xor a
	ld (visible),a

	ld hl,cmd1m
	res 6,(hl)	;res bit 6. scrbase to be visible
	ld a,(hl)
	out (CMD1),a

	ld hl,gpom
	res 6,(hl)
	ld a,(hl)
	out (GPO),a
	ENDM


;---------------------------------------------------------------------
;This MACRO sets the colour for the bright point which moves infront
;of lines when partial line drawing is employed.
;
;IN: accumulator= colour
;

bright_pt	MACRO
	ld (bright_col),a	;set it !
	ENDM


;---------------------------------------------------------------------
;Sets the number of pixels of each line that are to be drawn. If this
;value is greater than the line length then the line is drawn without
;the preceeding bright dot, and at its max length
;
;IN acc=length to be drawn
;

percentage	MACRO
	ld (line_len),a
	ENDM


;---------------------------------------------------------------------
;Set the current blitter list (NOT the last one) as non-deletable
;
;IN: nowt, accumulator destroyed.
;

permanent	MACRO
	ld a,true	;flag_er1 scrolled to flag_er2 for testing
	ld (flag_er1),a	;next time an erase performed.
	ENDM


;---------------------------------------------------------------------
;Set the interrupt line for the video chip. Must be in range 0-311 inc
;The active display area is 33-288.
;
;IN: bc=video line. ACC destroyed
;

int_line	MACRO
	di
	ld a,c
	out (INTREG),a	;bottom 8 bits
	ld a,b
	add a,a
	add a,a	;bit 2 <- bit 0 
	and 4
	ld b,a
	ld a,(cmd1m)	;get the memory copy
	and 251
	or b
	ld (cmd1m),a
	out (CMD1),a	;send it
	ei
	ENDM


;---------------------------------------------------------------------
;Set a flag, so that only part of sprites are copied.
;
;IN: A=number of lines to be copied (0== copy_all)
;

copy_some	MACRO
	ld (to_copy),a
	ENDM


;---------------------------------------------------------------------
;Set flag to COPY all of sprite lines onto the screen.
;
;IN: nowt, A DESTROYED
;

copy_all	MACRO
	xor a
	ld (to_copy),a
	ENDM


;---------------------------------------------------------------------
;Set erase colour for erasing blits to.
;
;IN: A=colour
;

re_colour	MACRO
	ld (scrn_col),a
	ENDM


;---------------------------------------------------------------------
;Load the palette into the palette board.
;
;IN: hl=pointer to a palette chunk
;

load_rgb	MACRO
	call f_load_rgb
	ENDM


;---------------------------------------------------------------------
;Enables the variable resolution mode for character painting
;
;IN nowt, A destroyed
;

variable_on MACRO
	ld a,(cmd2m)
	set 7,a	;enable it
	ld (cmd2m),a
	out (CMD2),a
	ENDM


;---------------------------------------------------------------------
;Disables variable resolution mode for character painting
;
;IN nowt, A destroyed
;

variable_off MACRO
	ld a,(cmd2m)
	res 7,a	;disable it
	ld (cmd2m),a
	out (CMD2),a
	ENDM


