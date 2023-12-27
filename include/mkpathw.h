/* mkpathxw INCLUDE */
/* lang=C20 */

/* make a file-path from multiple component c-strings */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	MKPATHXW_INCLUDE
#define	MKPATHXW_INCLUDE


#include	<envstandards.h>
#include	<usystem.h>
#include	<mknpathxw.h>


#ifdef	__cplusplus
extern "C" {
#endif

extern int mkpath1w(char *,cc *,int) noex ;
extern int mkpath2w(char *,cc *,cc *,int) noex ;
extern int mkpath3w(char *,cc *,cc *,cc *,int) noex ;
extern int mkpath4w(char *,cc *,cc *,cc *,cc *,int) noex ;
extern int mkpath5w(char *,cc *,cc *,cc *,cc *,cc *,int) noex ;
extern int mkpath6w(char *,cc *,cc *,cc *,cc *,cc *,cc *,int) noex ;

#ifdef	__cplusplus
}
#endif

#ifdef	__cplusplus

inline int mkpathw(char *pp,cc *s1,int sl) noex {
	return mknpathxw(pp,-1,1,s1,sl) ;
}
inline int mkpathw(char *pp,cc *s1,cc *s2,int sl) noex {
	return mknpathxw(pp,-1,2,s1,s2,sl) ;
}
inline int mkpathw(char *pp,cc *s1,cc *s2,cc *s3,int sl) noex {
	return mknpathxw(pp,-1,3,s1,s2,s3,sl) ;
}
inline int mknpathw(char *pp,cc *s1,cc *s2,cc *s3,cc *s4,int sl) noex {
	return mknpathxw(pp,-1,4,s1,s2,s3,s4,sl) ;
}
inline int mknpathw(char *pp,cc *s1,cc *s2,cc *s3,cc *s4,
		cc *s5,int sl) noex {
	return mknpathxw(pp,-1,5,s1,s2,s3,s4,s5,sl) ;
}
inline int mknpathw(char *pp,cc *s1,cc *s2,cc *s3,cc *s4,
		cc *s5,cc *s6,int sl) noex {
	return mknpathxw(pp,-1,6,s1,s2,s3,s4,s5,s6,sl) ;
}

#endif /* __cplusplus */


#endif /* MKPATHXW_INCLUDE */


