.386

_TEXT SEGMENT

ASSUME CS:_TEXT,DS:NOTHING
	  PUBLIC  RMP2Available

RMP2Available PROC
	  mov   ah,0E2h
	  mov   al,0
	  int   15h
	  movzx eax,ax
	  retf
RMP2Available ENDP

_TEXT ENDS

END