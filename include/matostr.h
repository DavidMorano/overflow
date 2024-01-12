/* matostr HEADER */
/* lang=C++20 */

/* Match-Option-String */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright (c) 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	MATOSTR_INCLUDE
#define	MATOSTR_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<utypedefs.h>
#include	<clanguage.h>
#include	<localmisc.h>


EXTERNC_begin

extern int matobasestr(mainv,int,cchar *,int) noex ;
extern int matocasestr(mainv,int,cchar *,int) noex ;
extern int matofoldstr(mainv,int,cchar *,int) noex ;

EXTERNC_end

#ifdef	__cplusplus
inline int matostr(mainv bs,int n,cchar *sp,int sl = -1) noex {
	return matobasestr(bs,n,sp,sl) ;
}
#else
static inline int matostr(mainv bs,int n,cchar *sp,int sl) noex {
	return matobasestr(bs,n,sp,sl) ;
}
#endif /* __cplusplus */


#endif /* MATOSTR_INCLUDE */


