#pragma once


#define _MKSW_WIDTH 60
#define _MKSW_HEIGHT 30

#define _MKSD_REGISTERBUFFER {{0,0}, { _MKSW_WIDTH ,_MKSW_HEIGHT },TRUE}
#define _MKSD_OUTPUTBUFFER {{ _MKSW_WIDTH,0}, { _MKSW_WIDTH/2 ,_MKSW_HEIGHT },TRUE}

// Default Buffer Count
#define _MKSW_BUFFERS 2


#define _MKSW_INDEX(CD,CS) (int)((((COORD)CD).Y*((COORD)CS).X)+((COORD)CD).X)


#define _MKS_REGKEY (ULLI)(137*173)


//How many Registers
#define _MKSR_REGISTERS 8

#define _MKSR_R_KEEPALIVE 0
#define _MKSR_R_REGISTERBUFFER 1
#define _MKSR_R_UNLOCKED 2
#define _MKSR_R_OUTPUTBUFFER 3
#define _MKSR_R_WATCHINGON 4
#define _MKSR_R_FILEHOOKED 5 // 1 if a File is beeing read from buffer
#define _MKSR_R_FILEINDEX 6 //  defines pointer position in file

//How many Register functions
#define _MKSR_REGFUNCTIONS 9

#define _MKSS_UNKNOW 0xEEE
#define _MKSS_KNOW 0xFAF
#define _MKSS_UNKNOWF 0xFEF
#define _MKSS_GOOD	 0xAAA
#define _MKSS_FAILED 0xFFF

#define _MKSS_BUFFERSIZE 64

#define _MKSC_BACKGROUND (0)
#define _MKSC_COLOR_FAILED 12
#define _MKSC_COLOR_UNKNOW 11
#define _MKSC_COLOR_GOOD 10
#define _MKSC_COLOR_CMD 15
#define _MKSC_COLOR_NAME 13
#define _MKSC_COLOR_INPUT 15
#define _MKSC_COLOR_OUTPUT 14
#define _MKSC_COLOR_BORDER 7