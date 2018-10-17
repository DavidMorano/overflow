/* wsirchr */

/* reverse search for a wide-character in a wide-string */


#define	CF_DEBUGS	0		/* compile-time debugging */


/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

	= 2018-10-17, David A.D. Morano
	Update for subordinate interface change.

*/

/* Copyright © 2000,2018 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Reverse search for a character in a wide-string returning an index into
	string of location found, otherwise returns negative.

	Synopsis:

	int wsirchr(const wchar_t *wsp,int wsl,int sch)

	Arguments:

	wsp	the source wide-string that is to be copied
	wsl	length of wide-string
	sch	the search character (as an integer)

	Returns:

	<0	character not found in given string
	>=0	character was found and this in the string index where


*******************************************************************************/


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>
#include	<stddef.h>		/* for 'wchar_t' */
#include	<localmisc.h>


/* external subroutines */

extern int	wsinul(const wchar_t *,int) ;


/* exported subroutines */


int wsirchr(const wchar_t *wsp,int wsl,int sch)
{
	int		i ;
	int		f = FALSE ;
	if (wsl < 0) wsl = wsinul(wsp,-1) ;
	for (i = (wsl-1) ; i >= 0 ; i -= 1) {
	    f = (wsp[i] == sch) ;
	    if (f) break ;
	} /* end for */
	return (f) ? i : -1 ;
}
/* end subroutine (wsirchr) */


