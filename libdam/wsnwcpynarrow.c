/* wsnwcpynarrow */

/* copy a narrow source string to a wide-string destination */


#define	CF_DEBUGS	0		/* compile-time debugging */


/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2000 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	We copy a narrow source string to a wide-string destination.

	Synopsis:

	int wsnwcpynarrow(dp,dl,sp,sl)
	wchar_t		*dp ;
	int		dl ;
	cchar		*sp ;
	int		sl ;

	Arguments:

	dp	wide-string buffer that receives the copy
	dl	size of destrination buffer
	sp	the source narrow-string that is to be copied
	sl	the maximum length of the source string to be copied

	Returns:

	<0	error (buffer overflow?)
	>=0	number of characters copied


*******************************************************************************/


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>
#include	<stddef.h>		/* for 'wchar_t' */
#include	<vsystem.h>
#include	<localmisc.h>		/* for |MKCHAR(3dam)| */


/* exported subroutines */


int wsnwcpynarrow(wchar_t *rarr,int rlen,cchar *sp,int sl)
{
	int		rs = SR_OK ;
	int		i ;
	int		ch ;
	for (i = 0 ; (i < rlen) && (i < sl) && sp[i] ; i += 1) {
	    ch = MKCHAR(sp[i]) ;
	    rarr[i] = ch ;
	}
	rarr[i] = '\0' ;
	if ((i < sl) && (sp[i] != '\0')) rs = SR_OVERFLOW ;
	return (rs >= 0) ? i : rs ;
}
/* end subroutine (wsnwcpynarrow) */


