/* mkpathx INCLUDE */
/* lang=C20 */

/* make a file-path from multiple component c-strings */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	MKPATHX_INCLUDE
#define	MKPATHX_INCLUDE


#include	<envstandards.h>
#include	<usystem.h>
#include	<mkpathxw.h>
#include	<mknpathx.h>
#include	<mknpathxw.h>


#ifndef	TYPEDEF_CC
#define	TYPEDEF_CC
typedef const char	cc ;
#endif

#ifdef	__cplusplus
extern "C" {
#endif

extern int mkpath1(char *,cc *) noex ;
extern int mkpath2(char *,cc *,cc *) noex ;
extern int mkpath3(char *,cc *,cc *,cc *) noex ;
extern int mkpath4(char *,cc *,cc *,cc *,cc *) noex ;
extern int mkpath5(char *,cc *,cc *,cc *, cc *,cc *) noex ;
extern int mkpath6(char *,cc *,cc *,cc *,cc *,cc *,cc *) noex ;

#ifdef	__cplusplus
}
#endif

#ifdef	__cplusplus

template<typename ... Args>
inline int mkpath(char *dp,Args ... args) noex {
	cint	na = npack(Args) ;
	return mknpathx(dp,-1,na,args ...) ;
}

#endif /* __cplusplus */


#endif /* MKPATHX_INCLUDE */


