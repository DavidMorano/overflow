/* wsichr */

/* search for a character in a wide-string */


#define	CF_DEBUGS	0		/* compile-time debugging */


/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

	= 2018-10-17, David A.D. Morano
	Update for subordinate interface change.

	= 2018-10-18, David A.D. Morano
	Maybe starting to get my head screwed on! There is no need to get the
	wstring length first.

*/

/* Copyright © 2000,2018 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

        Search for a character in a wide-string, returning an index of the found
        location, if found, and -1 otherwise.

	Synopsis:

	int wsichr(const wchar_t *sp,int sl,int sch)

	Arguments:

	sp	the source wide-string that is to be copied
	sl	length of wide-string
	sch	the search character (as an integer)

	Returns:

	>=0	the index into the given string where character was found
	<0	character was not found


*******************************************************************************/


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>
#include	<stddef.h>		/* for 'wchar_t' */
#include	<localmisc.h>


/* external subroutines */


/* exported subroutines */


int wsichr(const wchar_t *wsp,int wsl,int sch)
{
	int		i ;
	int		f = FALSE ;
	if (wsl >= 0) {
	    for (i = 0 ; wsl-- && wsp[i] ; i += 1) {
	        f = (wsp[i] == sch) ;
	       if (f) break ;
	   } /* end for */
	} else {
	    for (i = 0 ; wsp[i] ; i += 1) {
	        f = (wsp[i] == sch) ;
	       if (f) break ;
	   } /* end for */
	}
	return (f) ? i : -1 ;
}
/* end subroutine (wsichr) */

