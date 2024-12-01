

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
prog_st	nop.


;Reset the Z80 pc temporarily, DSP chunk data info -------------------

prog_end	defw DSP_datast,(data_end-data_st)/2
	org $-DSP_progst+prog_org


;Now for the DSP data segment ----------------------------------------

data_org	org $,DSP_datast
data_st	defw 0		;DATA HERE !!!!


;Reset the Z80 program counter for following code/data ---------------

data_end	org $-DSP_datast+data_org


