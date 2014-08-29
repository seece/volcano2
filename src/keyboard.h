#ifndef __KEYBOARD_H
#define __KEYBOARD_H

#define SxNONE      0x00
#define SxESC       0x01
#define Sx1         0x02
#define Sx2         0x03
#define Sx3         0x04
#define Sx4         0x05
#define Sx5         0x06
#define Sx6         0x07
#define Sx7         0x08
#define Sx8         0x09
#define Sx9         0x0A
#define Sx0         0x0B
#define SxHYPHEN    0x0C
#define SxEQUAL     0x0D
#define SxBACKSPACE 0x0E
#define SxTAB 0x0F
#define SxQ 0x10
#define SxW 0x11
#define SxE 0x12
#define SxR 0x13
#define SxT 0x14
#define SxY 0x15
#define SxU 0x16
#define SxI 0x17
#define SxO 0x18
#define SxP 0x19
#define SxBRACKETSxLEFT 0x1A
#define SxBRACKETSxRIGHT 0x1B
#define SxENTER 0x1C
#define SxCTRL 0x1D
#define SxA 0x1E
#define SxS 0x1F
#define SxD 0x20
#define SxF 0x21
#define SxG 0x22
#define SxH 0x23
#define SxJ 0x24
#define SxK 0x25
#define SxL 0x26
#define SxSEMICOLON 0x27
#define SxQUOTE 0x28
#define SxBACKQUOTE 0x29
#define SxSHIFTSxLEFT 0x2A
#define SxBACKSLASH 0x2B
#define SxZ 0x2C
#define SxX 0x2D
#define SxC 0x2E
#define SxV 0x2F
#define SxB 0x30
#define SxN 0x31
#define SxM 0x32
#define SxCOMMA 0x33
#define SxPERIOD 0x34
#define SxSLASH 0x35
#define SxSHIFTSxRIGHT 0x36
#define SxKEYPADSxASTERISK 0x37
#define SxALT 0x38
#define SxSPACE 0x39
#define SxCAPSLOCK 0x3A
#define SxF1 0x3B
#define SxF2 0x3C
#define SxF3 0x3D
#define SxF4 0x3E
#define SxF5 0x3F
#define SxF6 0x40
#define SxF7 0x41
#define SxF8 0x42
#define SxF9 0x43
#define SxF10 0x44
#define SxNUMLOCK 0x45
#define SxSCROLLOCK 0x46
#define SxHOME 0x47
#define SxUP 0x48
#define SxPGUP 0x49
#define SxKEYPADSxMINUS 0x4A
#define SxLEFT 0x4B
#define SxKEYPADSx5 0x4C
#define SxRIGHT 0x4D
#define SxKEYPADSxPLUS 0x4E
#define SxEND 0x4F
#define SxDOWN 0x50
#define SxPGDN 0x51
#define SxINSERT 0x52
#define SxDELETE 0x53
#define SxSHIFTSxF1 0x54
#define SxSHIFTSxF2 0x55
#define SxSHIFTSxF3 0x56
#define SxSHIFTSxF4 0x57
#define SxSHIFTSxF5 0x58
#define SxSHIFTSxF6 0x59
#define SxSHIFTSxF7 0x5A
#define SxSHIFTSxF8 0x5B
#define SxSHIFTSxF9 0x5C
#define SxSHIFTSxF10 0x5D
#define SxCTRLSxF1 0x5E
#define SxCTRLSxF2 0x5F
#define SxCTRLSxF3 0x60
#define SxCTRLSxF4 0x61
#define SxCTRLSxF5 0x62
#define SxCTRLSxF6 0x63
#define SxCTRLSxF7 0x64
#define SxCTRLSxF8 0x65
#define SxCTRLSxF9 0x66
#define SxCTRLSxF10 0x67
#define SxALTSxF1 0x68
#define SxALTSxF2 0x69
#define SxALTSxF3 0x6A
#define SxALTSxF4 0x6B
#define SxALTSxF5 0x6C
#define SxALTSxF6 0x6D
#define SxALTSxF7 0x6E
#define SxALTSxF8 0x6F
#define SxALTSxF9 0x70
#define SxALTSxF10 0x71
#define SxCTRLSxPRTSC 0x72
#define SxCTRLSxLEFT 0x73
#define SxCTRLSxRIGHT 0x74
#define SxCTRLSxEND 0x75
#define SxCTRLSxPGDN 0x76
#define SxCTRLSxHOME 0x77
#define SxALTSx1 0x78
#define SxALTSx2 0x79
#define SxALTSx3 0x7A
#define SxALTSx4 0x7B
#define SxALTSx5 0x7C
#define SxALTSx6 0x7D
#define SxALTSx7 0x7E
#define SxALTSx8 0x7F
#define SxALTSx9 0x80
#define SxALTSx0 0x81
#define SxALTSxHYPHEN 0x82
#define SxALTSxEQUAL 0x83
#define SxCTRLSxPGUP 0x84
#define SxF11 0x85
#define SxF12 0x86
#define SxSHIFTSxF11 0x87
#define SxSHIFTSxF12 0x88
#define SxCTRLSxF11 0x89
#define SxCTRLSxF12 0x8A
#define SxALTSxF11 0x8B
#define SxALTSxF12 0x8C
#define SxCTRLSxUP 0x8D
#define SxCTRLSxKEYPADSxMINUS 0x8E
#define SxCTRLSxKEYPADSx5 0x8F
#define SxCTRLSxKEYPADSxPLUS 0x90
#define SxCTRLSxDOWN 0x91
#define SxCTRLSxINS 0x92
#define SxCTRLSxDEL 0x93
#define SxCTRLSxTAB 0x94
#define SxCTRLSxKEYPADSxSLASH 0x95
#define SxCTRLSxKEYPADSxASTERISK 0x96
#define SxALTSxHOME 0x97
#define SxALTSxUP 0x98
#define SxALTSxPGUP 0x99
#define SxALTSxLEFT 0x9B
#define SxALTSxRIGHT 0x9D
#define SxALTSxEND 0x9F
#define SxALTSxDOWN 0xA0
#define SxALTSxPGDN 0xA1
#define SxALTSxINS 0xA2
#define SxALTSxDEL 0xA3
#define SxALTSxSLASH 0xA4
#define SxALTSxTAB 0xA5
#define SxALTSxENTER 0xA6
#define SxCTRLSxENTER 0xE0

char * Keyboardname[]=
{
 "NONE",
 "ESC",
 "1",
 "2",
 "3",
 "4",
 "5",
 "6",
 "7",
 "8",
 "9",
 "0",
 "HYPHEN",
 "EQUAL",
 "BACKSPACE",
 "TAB",
 "Q",
 "W",
 "E",
 "R",
 "T",
 "Y",
 "U",
 "I",
 "O",
 "P",
 "BRACKETS LEFT",
 "BRACKET RIGHT",
 "ENTER",
 "CTRL",
 "A",
 "S",
 "D",
 "F",
 "G",
 "H",
 "J",
 "K",
 "L",
 "SEMICOLON",
 "QUOTE",
 "BACKQUOTE",
 "SHIFTS LEFT",
 "BACKSLASH",
 "Z",
 "X",
 "C",
 "V",
 "B",
 "N",
 "M",
 "COMMA",
 "PERIOD",
 "SLASH",
 "SHIFT RIGHT",
 "KEYPAD ASTERISK",
 "ALT",
 "SPACE",
 "CAPSLOCK",
 "F1",
 "F2",
 "F3",
 "F4",
 "F5",
 "F6",
 "F7",
 "F8",
 "F9",
 "F10",
 "NUMLOCK",
 "SCROLLOCK",
 "HOME",
 "UP",
 "PGUP",
 "KEYPAD MINUS",
 "LEFT",
 "KEYPAD 5",
 "RIGHT",
 "KEYPAD PLUS",
 "END",
 "DOWN",
 "PGDN",
 "INSERT",
 "DELETE",
 "SHIFT F1",
 "SHIFT F2",
 "SHIFT F3",
 "SHIFT F4",
 "SHIFT F5",
 "SHIFT F6",
 "SHIFT F7",
 "SHIFT F8",
 "SHIFT F9",
 "SHIFT F10",
 "CTRL F1",
 "CTRL F2",
 "CTRL F3",
 "CTRL F4",
 "CTRL F5",
 "CTRL F6",
 "CTRL F7",
 "CTRL F8",
 "CTRL F9",
 "CTRL F10",
 "ALT F1",
 "ALT F2",
 "ALT F3",
 "ALT F4",
 "ALT F5",
 "ALT F6",
 "ALT F7",
 "ALT F8",
 "ALT F9",
 "ALT F10",
 "CTRL PRTSC",
 "CTRL LEFT",
 "CTRL RIGHT",
 "CTRL END",
 "CTRL PGDN",
 "CTRL HOME",
 "ALT 1",
 "ALT 2",
 "ALT 3",
 "ALT 4",
 "ALT 5",
 "ALT 6",
 "ALT 7",
 "ALT 8",
 "ALT 9",
 "ALT 0",
 "ALT HYPHEN",
 "ALT EQUAL",
 "CTRL PGUP",
 "F11",
 "F12",
 "SHIFT F11",
 "SHIFT F12",
 "CTRL F11",
 "CTRL F12",
 "ALT F11",
 "ALT F12",
 "CTRL UP",
 "CTRL KEYPAD MINUS",
 "CTRL KEYPAD 5",
 "CTRL KEYPAD PLUS",
 "CTRL DOWN",
 "CTRL INS",
 "CTRL DEL",
 "CTRL TAB",
 "CTRL KEYPAD SLASH",
 "CTRL KEYPAD ASTERISK",
 "ALT HOME",
 "ALT UP",
 "ALT PGUP",
 "ALT LEFT",
 "ALT RIGHT",
 "ALT END",
 "ALT DOWN",
 "ALT PGDN",
 "ALT INS",
 "ALT DEL",
 "ALT SLASH",
 "ALT TAB",
 "ALT ENTER",
 "CTRL ENTER",

};


#endif
