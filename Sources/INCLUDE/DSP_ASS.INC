

;---------------------------------------------------------------------
;MACROs for an ad-hoc DSP assembler. The macros here provide a crude
;DSP assembler which generates DEFWs in a z80 assembly file.
;
;The mnemonics for the DSP opcodes have been changed, due to a
;collision with z80 mnemonics. Hence, all DSP mnemonics are postceded
;by a FULL STOP (.).
;
;13 macros have been used to implement the assembler
;
;USE: to assemble the DSP code at origin dsp_org in the z80 file use
;
;	org $,dsp_org
;
;This assembles it at the current program counter in the z80 program
;space, BUT all labels etc. are generated as though it were
;assembled to dsp_org. SEE org in the PDS manual
;
;The same operation should be used for assembling the DSP data block.
;Assemble at the current pc ($) as if it were at dsp_code_start
;(wherever that may be).
;
;
;NOTE: like Flare Technology's assembler, the INTRUDE. instruction is
;      automatically followed by a NOP instruction.
;
;      Also included for posterities sake (whoever she is ?) is a
;      WAIT. macro. The parameter for this one is the number of
;      NOPs. This macro thus waits around for the parameter number
;      of clock cycles
;
;
;BUG FIXES: All parameters (the addresses for fetching from or writing
;	 to) have to be divided by two. This is because the Z80
;	 assembler treats data as 2 bytes, and the DSP treats them
;	 as 1 word.
;
;NOTE: Because of the above BUGFIX, data which references DSP program
;      space ie. for jumping etc. should contain DSP_CODE_ADDR/2.
;
;NOTE 2: Bracktes are optional around address parameters !
;



;The original mov. had to be split into 3 MACROs, movm, movr and movd
;ARGGGHHHHHHHHHH

;The movr MACRO definition

mov.	MACRO
	IFS [@1] [mx]		;mov. mx,(nn)
	defw 01000h+(@2)/2
	EXITM			;leave this MACRO definition
	ENDIF

	IFS [@1] [my]		;mov. my,(nn)
	defw 01800h+(@2)/2
	EXITM
	ENDIF

	IFS [@1] [ax]		;mov. ax,(nn)
	defw 06800h+(@2)/2
	EXITM
	ENDIF

	IFS [@1] [az]		;mov. az,(nn)
	defw 0b800h+(@2)/2
	EXITM
	ENDIF

	IFS [@1] [pc]		;mov. pc,(nn)
	defw 0e800h+(@2)/2
	EXITM
	ENDIF

	IFS [@2] [mz0]		;mov. (nn),mz0
	defw 00000h+(@1)/2
	EXITM			;leave this macro definition
	ENDIF

	IFS [@2] [mz1]		;mov. (nn),mz1
	defw 00800h+(@1)/2
	EXITM
	ENDIF

	IFS [@2] [cmpr]		;mov. (nn),cmpr
	defw 02000h+(@1)/2
	EXITM
	ENDIF

	IFS [@2] [intra]		;mov. (nn),intra
	defw 05000h+(@1)/2
	EXITM
	ENDIF

	IFS [@2] [pc]		;mov. (nn),pc
	defw 06000h+(@1)/2
	EXITM
	ENDIF

	IFS [@2] [ax]		;mov. (nn),ax
	defw 07000h+(@1)/2
	EXITM
	ENDIF

	IFS [@2] [az]		;mov. (nn),az
	defw 07800h+(@1)/2
	EXITM
	ENDIF

	IFS [@1] [dma0]		;mov. dma0,(nn)
	defw 02800h+(@2)/2
	EXITM
	ENDIF

	IFS [@1] [dma1]		;mov. dma1,(nn)
	defw 03000h+(@2)/2
	EXITM
	ENDIF

	IFS [@1] [dmd]		;mov. dmd,(nn)
	defw 03800h+(@2)/2
	EXITM
	ENDIF

	IFS [@1] [dac0]		;mov. dac0,(nn)
	defw 0c000h+(@2)/2
	EXITM
	ENDIF

	IFS [@1] [dac1]		;mov. dac1,(nn)
	defw 0c800h+(@2)/2
	EXITM
	ENDIF

	IFS [@1] [dac2]		;mov. dac2,(nn)
	defw 0d000h+(@2)/2
	EXITM
	ENDIF

	IFS [@1] [dac12]		;mov. dac12,(nn)
	defw 0d800h+(@2)/2
	EXITM
	ENDIF

	IFS [@2] [dmd]		;mov. (nn),dmd
	defw 04000h+(@1)/2
	EXITM

	ELSE
	ERROR "Invalid mov. parameter for DSP instruction
	ENDM


;--- NOP. mnemonic ---------------------------------------------------

nop.	MACRO
	defw 04800h	;opcode for NOP.
	ENDM


;--- OFFSET. mnemonic ------------------------------------------------

offset.	MACRO
	defw 05800h	;opcode for OFFSET.
	ENDM


;--- ADD. ADDR  mnemonic ---------------------------------------------

add.	MACRO
	defw 08000h+(@1)/2
	ENDM


;--- SUB. ADDR  mnemonic ---------------------------------------------

sub.	MACRO
	defw 08800h+(@1)/2
	ENDM


;--- AND. ADDR  mnemonic ---------------------------------------------

and.	MACRO
	defw 09000h+(@1)/2
	ENDM


;--- OR. ADDR  mnemonic ----------------------------------------------

or.	MACRO
	defw 09800h+(@1)/2
	ENDM


;--- ADC. ADDR  mnemonic ---------------------------------------------

adc.	MACRO
	defw 0a000h+(@1)/2
	ENDM


;--- SBC. ADDR  mnemonic ---------------------------------------------

sbc.	MACRO
	defw 0a800h+(@1)/2
	ENDM


;--- ADinC. ADDR  mnemonic -------------------------------------------

ADinC.	MACRO
	defw 0b000h+(@1)/2
	ENDM


;--- SILENT. (nn)  mnemonic ------------------------------------------

silent.	MACRO
	defw 0c000h+(@1)/2	;perform mov. dac0,(nn) using only (nn) param
	defw 0e000h	;nopa. opcode
	ENDM


;--- RIGHT. (nn)  mnemonic -------------------------------------------

right.	MACRO
	defw 0c000h+(@1)/2	;perform mov. dac0,(nn) using only (nn) param
	defw 0f000h	;nopr. opcode
	ENDM


;--- LEFT. (nn) mnemonic ---------------------------------------------

left.	MACRO
	defw 0c000h+(@1)/2	;perfrom mov. dac0,(nn) using only (nn) param
	defw 04800h	;nop. opcode
	ENDM


;--- INTRUDE.  mnemonic ----------------------------------------------

intrude.	MACRO
	defw 0f800h,04800h	;intrude FOLLOWED by NOP
	ENDM


