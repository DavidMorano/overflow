/* bufsizevar HEADER */
/* lang=C++20 */

/* this provides a variable with a buffer-size */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Recommended usage within source code:
		#include	<bufsizevar.hh>
		#define		DEFVAL	(4*104)
		bufsizevar	maxpathlen(getbufsize_mp,DEFVAL) ;
		if ((rs = maxpathlen) >= 0) {
			* do something w/ value in 'rs' *
		}


*******************************************************************************/

#ifndef	BUFSIZEVAR_INCLUDE
#define	BUFSIZEVAR_INCLUDE
#ifdef	__cplusplus /* everything is C++ only */


#include	<envstandards.h>	/* ordered first to configure */
#include	<usystem.h>
#include	<getbufsize.h>
#include	<localmisc.h>


class bufsizevar {
	cint		name ;
	int		def ;
	int		val = 0 ;
public:
	constexpr bufsizevar(int n,int d = 0) noex : name(n), def(d) { 
	    if (def == 0) def = (4*1024) ;
	} ;
	bufsizevar() = delete ;
	bufsizevar &operator = (const bufsizevar &) = delete ;
	operator int () noex ;
} ; /* end class (bufsizevar) */


#endif	/* __cplusplus */
#endif /* BUFSIZEVAR_INCLUDE */


