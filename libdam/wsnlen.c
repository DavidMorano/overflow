/* wsnlen */

/* get length of a wide-string */


#define	CF_DEBUGS	0		/* compile-time debugging */


/* revision history:

	= 2018-11-27, David A.D. Morano
	Originally written for Rightcore Network Services.
  
*/

/* Copyright © 2018 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Calculate the length of a wide-string.

	Synopsis:
	int wsnlen(const wchar_t *wsp,int wsl)

	Arguments:
	wsp	source string to be searched
	wsl	length of source string

	Returns:
	-	the length of the given wide-string

*******************************************************************************/


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>
#include	<stddef.h>		/* for 'wchar_t' */
#include	<localmisc.h>


/* external subroutines */


/* exported subroutines */


int wsnlen(const wchar_t *wsp.int wsl)
{
	int		i ;
	if (wsl >= 0) {
	    for (i = 0 ; wsl-- && wsp[i] ; i += 1) ;
	} else {
	    for (i = 0 ; wsp[i] ; i += 1) ;
	}
	return i ;
}
/* end subroutine (wsnlen) */


int wslen(const wchar_t *wsp)
{
	return wsnlen(wsp,-1) ;
}
/* end subroutine (wslen) */

