/* matstr INCLUDE */
/* lang=C++20 */

/* Match a String */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright (c) 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	MATSTR_INCLUDE
#define	MATSTR_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<utypedefs.h>
#include	<clanguage.h>
#include	<localmisc.h>


#ifdef	__cplusplus
extern "C" {
#endif

extern int matbasestr(cchar *const *,cchar *,int) noex ;
extern int matcasestr(cchar *const *,cchar *,int) noex ;
extern int matfoldstr(cchar *const *,cchar *,int) noex ;

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#ifdef	__cplusplus
inline int matstr(cchar *const *bs,cchar *sp,int sl = -1) noex {
	return matbasestr(bs,sp,sl) ;
}
#else
static inline int matstr(cchar *const *bs,cchar *sp,int sl) noex {
	return matbasestr(bs,sp,sl) ;
}
#endif /* __cplusplus */


#endif /* MATSTR_INCLUDE */


