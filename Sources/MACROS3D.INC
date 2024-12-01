; The following are the MACROS for the 3d graphics.

; Macro to set Partial line drawing on or off

part_3d	MACRO
	ifs [@1] [off]
	xor a
	endif
	ifs [@1] [on]
	ld a,1
	endif
	ld (part_flag),a
	ENDM


; This macro calls the routine that sets up the data for the cubes
; rotation and then sets the DSP going.

calc_3d	MACRO
	call clc_3d
	ENDM


; This macro calls the routine that waits for the DSP to finish the 3d work

wait_3d	MACRO
	call w_3d
	ENDM


; Macro to call the routine to generate the blitter list

draw_3d	MACRO
	ld de,@1	; Pointer to the face information
	call drw_3d
	ENDM


; Macro to set PC on a word boundary (used for DSP transfer and data areas)

wordb	MACRO
	if $ & 1 	; set data on a word boundary
	defb 0
	endif
	ENDM


; Macro to set the enlarging scale factor for the 3D routines

scale_fac	MACRO
	ld (enlarge),hl
	ENDM

