/* nleadstr HEADER */
/* lang=C20 */

/* match on the leading part of a string */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	NLEADSTR_INCLUDE
#define	NLEADSTR_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<utypedefs.h>
#include	<clanguage.h>


EXTERNC_begin

extern int nleadbasestr(cchar *,cchar *,int) noex ;
extern int nleadcasestr(cchar *,cchar *,int) noex ;
extern int nleadfoldstr(cchar *,cchar *,int) noex ;

EXTERNC_end

#ifdef	__cplusplus
inline int nleadstr(cchar *bs,cchar *sp,int sl) noex {
	return nleadbasestr(bs,sp,sl) ;
}
#else
static inline int nleadstr(cchar *bs,cchar *sp,int sl) noex {
	return nleadbasestr(bs,sp,sl) ;
}
#endif /* __cplusplus */


#endif /* NLEADSTR_INCLUDE */


