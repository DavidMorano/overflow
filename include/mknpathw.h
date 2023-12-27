/* mknpathxw INCLUDE */
/* lang=C20 */

/* make a file-path using multople component c-strings */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	MKNPATHXW_INCLUDE
#define	MKNPATHXW_INCLUDE


#include	<envstandards.h>
#include	<usystem.h>


#ifdef	__cplusplus
extern "C" {
#endif

extern int mknpathxw(char *,int,int,...) noex ;

extern int mknpath1w(char *,int,cc *,int) noex ;
extern int mknpath2w(char *,int,cc *,cc *,int) noex ;
extern int mknpath3w(char *,int,cc *,cc *,cc *,int) noex ;
extern int mknpath4w(char *,int,cc *,cc *,cc *,cc *,int) noex ;
extern int mknpath5w(char *,int,cc *,cc *,cc *,cc *,cc *,int) noex ;

#ifdef	__cplusplus
}
#endif

#ifdef	__cplusplus

inline int mknpathw(char *pp,int pl,cc *s1,int sl) noex {
	return mknpathxw(pp,pl,1,s1,sl) ;
}
inline int mknpathw(char *pp,int pl,cc *s1,cc *s2,int sl) noex {
	return mknpathxw(pp,pl,2,s1,s2,sl) ;
}
inline int mknpathw(char *pp,int pl,cc *s1,cc *s2,cc *s3,int sl) noex {
	return mknpathxw(pp,pl,3,s1,s2,s3,sl) ;
}
inline int mknpathw(char *pp,int pl,cc *s1,cc *s2,cc *s3,cc *s4,int sl) noex {
	return mknpathxw(pp,pl,4,s1,s2,s3,s4,sl) ;
}
inline int mknpathw(char *pp,int pl,cc *s1,cc *s2,cc *s3,cc *s4,
		cc *s5,int sl) noex {
	return mknpathxw(pp,pl,5,s1,s2,s3,s4,s5,sl) ;
}

#endif /* __cplusplus */


#endif /* MKNPATHXW_INCLUDE */


