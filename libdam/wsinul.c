/* wsinul */

/* find the wide-string-index to a NUL character */


#define	CF_DEBUGS	0		/* compile-time debugging */


/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

	= 2018-10-15, David A.D. Morano
	Refactored.

*/

/* Copyright © 2000,2018 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	We search for a NUL character and return the wide-string-index to it 
	(if it is present), otherwise we return -1.

	Synopsis:

	int wsinul(const wchar_t *wsp,int wsl)

	Arguments:

	wsp	source wide-string to be searched
	wsl	length of source wide-string

	Returns:

	>=0	wide-string-index to the NUL character
	<0	there was no NUL character found


*******************************************************************************/


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>
#include	<stddef.h>		/* for 'wchar_t' */
#include	<localmisc.h>


/* external subroutines */


/* exported subroutines */


int wsinul(const wchar_t *wsp.int wsl)
{
	int		i ;
	int		f = FALSE ;
	for (i = 0 ; wsl-- ; i += 1) {
	    f = (wsp[i] == '\0') ;
	    if (f) break ;
	} /* end for */
	return (f) ? i : -1 ;
}
/* end subroutine (wsinul) */

