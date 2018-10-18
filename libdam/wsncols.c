/* wsncols */

/* calculate the number of columns used by a wide-string */


#define	CF_DEBUGS	0		/* compile-time debug print-outs */


/* revision history:

	= 2009-04-10, David A­D­ Morano
	This subroutine was originally written.

	= 2018-10-18, David A.D. Morano
	Fix for proper current column.

*/

/* Copyright © 2009,2018 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	This subroutine calculates the number of columns that a wide-string
	uses given a horizontal position in a line of columns.

	Synopsis:

	int wsncols(int ntab,int scol,const wchar_t *wsp,int wsl)

	Arguments:

	ntab		maximum number of columns in a TAB character
	scol		starting current column number
	wsp		wide-string pointer
	wsl		wide-string length (in characters)

	Returns:

	-		number of columns used up


*******************************************************************************/


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>
#include	<stddef.h>		/* for 'wchar_t' */
#include	<ascii.h>
#include	<localmisc.h>


/* local defines */


/* external subroutines */

extern int	tabcols(int,int) ;


/* external variables */


/* local structures */


/* forward references */


/* local variables */


/* exported subroutines */


int wsncols(int ntab,int scol,const wchar_t *wsp,int wsl)
{
	int		col = scol ;
	while (wsl-- && *wsp) {
	    if (*wsp == CH_TAB) {
		col += tabcols(ntab,col) ;
	    } else {
		col += 1 ;
	    }
	} /* end while */
	return (col-scol) ;
}
/* end subroutine (wsncols) */


int wscols(int ntab,int scol,const wchar_t *wsp)
{
	return wsncols(ntab,scol,wsp,-1) ;
}
/* end subroutine (wscols) */

