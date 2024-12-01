
;Jons crappy character set !

	defb n_plane
	defb 6,8	;char x and y sizes
	defb 1,255	;num colours and colour
	defb 0	;transparent colour
	defb 32,127	;ASCII characters supported
	defb prop_t	;set proportional spacing flag

	defw 95*3 + 0*8	; pointer for ' '
	defb 6
	defw 94*3 + 1*8	; pointer for '!'
	defb 2
	defw 93*3 + 2*8	; pointer for '"'
	defb 4
	defw 92*3 + 3*8	; pointer for '#'
	defb 6
	defw 91*3 + 4*8	; pointer for '$'
	defb 6
	defw 90*3 + 5*8	; pointer for '%'
	defb 6
	defw 89*3 + 6*8	; pointer for '&'
	defb 6
	defw 88*3 + 7*8	; pointer for '''
	defb 2
	defw 87*3 + 8*8	; pointer for '('
	defb 4
	defw 86*3 + 9*8	; pointer for ')'
	defb 4
	defw 85*3 + 10*8	; pointer for '*'
	defb 6
	defw 84*3 + 11*8	; pointer for '+'
	defb 6
	defw 83*3 + 12*8	; pointer for ','
	defb 3
	defw 82*3 + 13*8	; pointer for '-'
	defb 6
	defw 81*3 + 14*8	; pointer for '.'
	defb 3
	defw 80*3 + 15*8	; pointer for '/'
	defb 6
	defw 79*3 + 16*8	; pointer for '0'
	defb 6
	defw 78*3 + 17*8	; pointer for '1'
	defb 4
	defw 77*3 + 18*8	; pointer for '2'
	defb 6
	defw 76*3 + 19*8	; pointer for '3'
	defb 6
	defw 75*3 + 20*8	; pointer for '4'
	defb 6
	defw 74*3 + 21*8	; pointer for '5'
	defb 6
	defw 73*3 + 22*8	; pointer for '6'
	defb 6
	defw 72*3 + 23*8	; pointer for '7'
	defb 6
	defw 71*3 + 24*8	; pointer for '8'
	defb 6
	defw 70*3 + 25*8	; pointer for '9'
	defb 6
	defw 69*3 + 26*8	; pointer for ':'
	defb 3
	defw 68*3 + 27*8	; pointer for ';'
	defb 3
	defw 67*3 + 28*8	; pointer for '<'
	defb 5
	defw 66*3 + 29*8	; pointer for '='
	defb 6
	defw 65*3 + 30*8	; pointer for '>'
	defb 5
	defw 64*3 + 31*8	; pointer for '?'
	defb 6
	defw 63*3 + 32*8	; pointer for '@'
	defb 6
	defw 62*3 + 33*8	; pointer for 'A'
	defb 6
	defw 61*3 + 34*8	; pointer for 'B'
	defb 6
	defw 60*3 + 35*8	; pointer for 'C'
	defb 6
	defw 59*3 + 36*8	; pointer for 'D'
	defb 6
	defw 58*3 + 37*8	; pointer for 'E'
	defb 6
	defw 57*3 + 38*8	; pointer for 'F'
	defb 6
	defw 56*3 + 39*8	; pointer for 'G'
	defb 6
	defw 55*3 + 40*8	; pointer for 'H'
	defb 6
	defw 54*3 + 41*8	; pointer for 'I'
	defb 4
	defw 53*3 + 42*8	; pointer for 'J'
	defb 6
	defw 52*3 + 43*8	; pointer for 'K'
	defb 6
	defw 51*3 + 44*8	; pointer for 'L'
	defb 6
	defw 50*3 + 45*8	; pointer for 'M'
	defb 6
	defw 49*3 + 46*8	; pointer for 'N'
	defb 6
	defw 48*3 + 47*8	; pointer for 'O'
	defb 6
	defw 47*3 + 48*8	; pointer for 'P'
	defb 6
	defw 46*3 + 49*8	; pointer for 'Q'
	defb 6
	defw 45*3 + 50*8	; pointer for 'R'
	defb 6
	defw 44*3 + 51*8	; pointer for 'S'
	defb 6
	defw 43*3 + 52*8	; pointer for 'T'
	defb 6
	defw 42*3 + 53*8	; pointer for 'U'
	defb 6
	defw 41*3 + 54*8	; pointer for 'V'
	defb 6
	defw 40*3 + 55*8	; pointer for 'W'
	defb 6
	defw 39*3 + 56*8	; pointer for 'X'
	defb 6
	defw 38*3 + 57*8	; pointer for 'Y'
	defb 6
	defw 37*3 + 58*8	; pointer for 'Z'
	defb 6
	defw 36*3 + 59*8	; pointer for '['
	defb 4
	defw 35*3 + 60*8	; pointer for '\'
	defb 6
	defw 34*3 + 61*8	; pointer for ']'
	defb 4
	defw 33*3 + 62*8	; pointer for '^'
	defb 6
	defw 32*3 + 63*8	; pointer for '_'
	defb 6
	defw 31*3 + 64*8	; pointer for '`'
	defb 8
	defw 30*3 + 65*8	; pointer for 'a'
	defb 6
	defw 29*3 + 66*8	; pointer for 'b'
	defb 6
	defw 28*3 + 67*8	; pointer for 'c'
	defb 6
	defw 27*3 + 68*8	; pointer for 'd'
	defb 6
	defw 26*3 + 69*8	; pointer for 'e'
	defb 6
	defw 25*3 + 70*8	; pointer for 'f'
	defb 5
	defw 24*3 + 71*8	; pointer for 'g'
	defb 6
	defw 23*3 + 72*8	; pointer for 'h'
	defb 6
	defw 22*3 + 73*8	; pointer for 'i'
	defb 4
	defw 21*3 + 74*8	; pointer for 'j'
	defb 4
	defw 20*3 + 75*8	; pointer for 'k'
	defb 5
	defw 19*3 + 76*8	; pointer for 'l'
	defb 4
	defw 18*3 + 77*8	; pointer for 'm'
	defb 6
	defw 17*3 + 78*8	; pointer for 'n'
	defb 6
	defw 16*3 + 79*8	; pointer for 'o'
	defb 6
	defw 15*3 + 80*8	; pointer for 'p'
	defb 6
	defw 14*3 + 81*8	; pointer for 'q'
	defb 6
	defw 13*3 + 82*8	; pointer for 'r'
	defb 6
	defw 12*3 + 83*8	; pointer for 's'
	defb 6
	defw 11*3 + 84*8	; pointer for 't'
	defb 5
	defw 10*3 + 85*8	; pointer for 'u'
	defb 6
	defw 9*3 + 86*8	; pointer for 'v'
	defb 6
	defw 8*3 + 87*8	; pointer for 'w'
	defb 6
	defw 7*3 + 88*8	; pointer for 'x'
	defb 6
	defw 6*3 + 89*8	; pointer for 'y'
	defb 6
	defw 5*3 + 90*8	; pointer for 'z'
	defb 6
	defw 4*3 + 91*8	; pointer for '{'
	defb 5
	defw 3*3 + 92*8	; pointer for '|'
	defb 2
	defw 2*3 + 93*8	; pointer for '}'
	defb 5
	defw 1*3 + 94*8	; pointer for '~'
	defb 6
	defw 0*3 + 95*8	; pointer for '/'
	defb 6
	defb 0,0,0,0,0,0,0,0	; ' '
	defb 64,64,64,64,64,0,64,0	; '!'
	defb 80,80,0,0,0,0,0,0	; '"'
	defb 40,40,124,40,124,40,40,0	; '#'
	defb 16,120,20,56,80,60,16,0	; '$'
	defb 76,76,32,16,8,100,100,0	; '%'
	defb 24,36,20,8,84,36,88,0	; '&'
	defb 64,64,0,0,0,0,0,0	; '''
	defb 64,32,16,16,16,32,64,0	; '('
	defb 16,32,64,64,64,32,16,0	; ')'
	defb 16,84,56,124,56,84,16,0	; '*'
	defb 0,16,16,124,16,16,0,0	; '+'
	defb 0,0,0,0,0,64,64,32	; ','
	defb 0,0,0,124,0,0,0,0	; '-'
	defb 0,0,0,0,0,96,96,0	; '.'
	defb 0,64,32,16,8,4,0,0	; '/'
	defb 56,68,100,84,76,68,56,0	; '0'
	defb 32,48,32,32,32,32,112,0	; '1'
	defb 56,68,64,32,16,8,124,0	; '2'
	defb 56,68,64,48,64,68,56,0	; '3'
	defb 32,48,40,36,124,32,32,0	; '4'
	defb 124,4,4,60,64,64,60,0	; '5'
	defb 56,68,4,60,68,68,56,0	; '6'
	defb 124,64,32,16,8,8,8,0	; '7'
	defb 56,68,68,56,68,68,56,0	; '8'
	defb 56,68,68,120,64,68,56,0	; '9'
	defb 0,96,96,0,96,96,0,0	; ':'
	defb 0,96,96,0,96,96,64,32	; ';'
	defb 64,32,16,8,16,32,64,0	; '<'
	defb 0,0,124,0,124,0,0,0	; '='
	defb 8,16,32,64,32,16,8,0	; '>'
	defb 56,68,64,32,16,0,16,0	; '?'
	defb 56,68,64,88,84,84,56,0	; '@'
	defb 56,68,68,124,68,68,68,0	; 'A'
	defb 60,68,68,60,68,68,60,0	; 'B'
	defb 56,68,4,4,4,68,56,0	; 'C'
	defb 60,68,68,68,68,68,60,0	; 'D'
	defb 124,4,4,28,4,4,124,0	; 'E'
	defb 124,4,4,28,4,4,4,0	; 'F'
	defb 56,68,4,4,100,68,56,0	; 'G'
	defb 68,68,68,124,68,68,68,0	; 'H'
	defb 112,32,32,32,32,32,112,0	; 'I'
	defb 124,16,16,16,16,20,8,0	; 'J'
	defb 68,36,20,12,20,36,68,0	; 'K'
	defb 4,4,4,4,4,4,124,0	; 'L'
	defb 68,108,84,68,68,68,68,0	; 'M'
	defb 68,76,84,100,68,68,68,0	; 'N'
	defb 56,68,68,68,68,68,56,0	; 'O'
	defb 60,68,68,60,4,4,4,0	; 'P'
	defb 56,68,68,68,84,36,88,0	; 'Q'
	defb 60,68,68,60,68,68,68,0	; 'R'
	defb 56,68,4,56,64,68,56,0	; 'S'
	defb 124,16,16,16,16,16,16,0	; 'T'
	defb 68,68,68,68,68,68,56,0	; 'U'
	defb 68,68,68,68,68,40,16,0	; 'V'
	defb 68,68,68,68,84,108,68,0	; 'W'
	defb 68,68,40,16,40,68,68,0	; 'X'
	defb 68,68,68,56,16,16,16,0	; 'Y'
	defb 124,64,32,16,8,4,124,0	; 'Z'
	defb 112,16,16,16,16,16,112,0	; '['
	defb 4,4,8,16,32,64,64,0	; '\'
	defb 112,64,64,64,64,64,112,0	; ']'
	defb 48,72,8,28,8,8,124,0	; '^'
	defb 0,0,0,0,0,0,124,0	; '_'
	defb 62,65,89,69,89,65,62,0	; '`'
	defb 0,0,24,32,56,36,88,0	; 'a'
	defb 4,4,60,68,68,68,60,0	; 'b'
	defb 0,0,120,4,4,4,120,0	; 'c'
	defb 64,64,120,68,68,68,120,0	; 'd'
	defb 0,0,56,68,60,4,120,0	; 'e'
	defb 96,16,16,56,16,16,16,0	; 'f'
	defb 0,0,56,68,68,120,64,60	; 'g'
	defb 4,4,60,68,68,68,68,0	; 'h'
	defb 32,0,48,32,32,32,112,0	; 'i'
	defb 64,0,96,64,64,64,64,48	; 'j'
	defb 8,8,72,40,24,40,72,0	; 'k'
	defb 48,32,32,32,32,32,112,0	; 'l'
	defb 0,0,44,84,84,84,84,0	; 'm'
	defb 0,0,60,68,68,68,68,0	; 'n'
	defb 0,0,56,68,68,68,56,0	; 'o'
	defb 0,0,60,68,68,60,4,4	; 'p'
	defb 0,0,120,68,68,120,64,64	; 'q'
	defb 0,0,116,12,4,4,4,0	; 'r'
	defb 0,0,120,4,56,64,60,0	; 's'
	defb 16,16,56,16,16,16,96,0	; 't'
	defb 0,0,36,36,36,36,88,0	; 'u'
	defb 0,0,68,68,68,40,16,0	; 'v'
	defb 0,0,68,68,68,84,40,0	; 'w'
	defb 0,0,68,40,16,40,68,0	; 'x'
	defb 0,0,68,68,68,120,64,60	; 'y'
	defb 0,0,124,32,16,8,124,0	; 'z'
	defb 96,16,16,8,16,16,96,0	; '{'
	defb 64,64,64,64,64,64,64,0	; '|'
	defb 24,32,32,64,32,32,24,0	; '}'
	defb 124,68,68,68,68,68,124,0	; '~'
	defb 64,64,32,16,8,4,4,0	; '/'

