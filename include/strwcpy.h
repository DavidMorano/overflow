/* strwcpy INCLUDE */
/* lang=C20 */

/* string-copy variant */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	STRWCPY_INCLUDE
#define	STRWCPY_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<utypedefs.h>
#include	<clanguage.h>
#include	<strwcpyx.h>
#include	<strwcpyxc.h>
#include	<strwcpyxx.h>


#ifdef	__cplusplus

inline char *strwcpy(char *dp,cchar *sp,int sl) noex {
	return strwcpybc(dp,sp,sl) ;
}

#else /* __cplusplus */

static inline char *strwcpy(char *dp,cchar *sp,int sl) noex {
	return strwcpybc(dp,sp,sl) ;
}

#endif /* __cplusplus */


#endif /* STRWCPY_INCLUDE */


