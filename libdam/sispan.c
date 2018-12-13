/* sispan */

/* find the index of character pass a span of a string */


/* revision history:

	= 1998-03-23, David A­D­ Morano
	This subroutine was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	This subroutine returns the number of characters skipped in the string
	due to belonging to the specified character class.

	Synopsis:

	int sispan(sp,sl,class)
	const char	sp[] ;
	int		sl ;
	const char	class[] ;

	Arguments:

	sp	string to be examined
	sl	length of string of break character to break on
	class	string of characters defining a character class to skip

	Returns:

	>0	number of characters skipped
	==0	no characters were skipped


*******************************************************************************/


#include	<envstandards.h>	/* MUST be first to configure */

#include	<sys/types.h>
#include	<string.h>		/* for |strchr(3c)| but not used */

#include	<localmisc.h>


/* external subroutines */

extern int	strnchr(cchar *,int,int) ;	/* handles ISO-8859-1 */


/* forward references */


/* exported subroutines */


int sispan(cchar *sp,int sl,cchar *class)
{
	int		i ;
	int		ch ;

	for (i = 0 ; sl-- && sp[i] ; i += 1) {
	    ch = MKCHAR(sp[i]) ;
	    if (strnchr(class,-1,ch) != NULL) break ;
	} /* end for */

	return i ;
}
/* end subroutine (sispan) */


