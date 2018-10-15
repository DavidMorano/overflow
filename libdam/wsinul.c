/* wsinul */

/* get length of a wide-string */


#define	CF_DEBUGS	0		/* compile-time debugging */


/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

	= 2018-10-15, David A.D. Morano
	Refactoed to call |wsichr(3dam)| instead.

*/

/* Copyright © 2000,2018 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Calculate the length of a wide-string.

	Synopsis:

	int wsinul(const wchar_t *wsp,int wsl)

	Arguments:

	wsp	source string to be searched
	wsl	length of source string

	Returns:

	-	the length of the given wide-string (also index to NUL)


*******************************************************************************/


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>
#include	<stddef.h>		/* for 'wchar_t' */
#include	<localmisc.h>


/* external subroutines */

int wsirchr(const wchar_t *,int,int) ;


/* exported subroutines */


int wsinul(const wchar_t *wsp.int wsl)
{
	return wsirchr(wsp,wsl,0) ;
}
/* end subroutine (wsinul) */

