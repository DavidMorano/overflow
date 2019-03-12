/* sihyphen */

/* find a hyphen (a fake hyphen of two minus characters) in a string */


#define	CF_STRNCHR	0		/* use |strnchr(3dam)| */


/* revision history:

	= 1998-03-23, David A­D­ Morano
	This subroutine was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	This finds the string-index of a fake hyphen in the given string.
	A fake hyphen is two minus characters in a row.

	Synopsis:

	int sihyphen(sp,sl)
	const char	*sp ;
	int		sl ;

	Arguments:

	sp	string to be examined
	sl	length of string to be examined

	Returns:

	>=0	index of found hyphen
	-1	hyphen not found


*******************************************************************************/


#include	<envstandards.h>	/* MUST be first to configure */

#include	<sys/types.h>
#include	<string.h>

#include	<localmisc.h>


/* local defines */


/* external subroutines */

extern int	strnchr(cchar *,int,int) ;


/* exported subroutines */


#if	CF_STRNCHR

int sihyphen(const char *sp,int sl)
{
	int		si = 0 ;
	int		f = FALSE ;
	cchar		*tp ;

	if (sl < 0) sl = strlen(sp) ;

	while ((sl >= 2) && ((tp = strnchr(sp,sl,'-')) != NULL) {
	    si += (tp-sp) ;
	    f = (((tp-sp)+1) < sl) && (tp[1] == '-') ;
	    if (f) break ;
	    si += 1 ;
	    sl -= ((tp+1)-sp) ;
	    sp = (tp+1) ;
	} /* end while */

	return (f) ? si : -1 ;
}
/* end subroutine (sihyphen) */
		    
#else /* CF_STRNCHR */

int sihyphen(const char *sp,int sl)
{
	int		i ;
	int		f = FALSE ;

	if (sl < 0) sl = strlen(sp) ;

	for (i = 0 ; (i < (sl-1)) && sp[i] ; i += 1) {
	    f = (sp[i] == '-') && (sp[i + 1] == '-') ;
	    if (f) break ;
	} /* end for */

	return (f) ? i : -1 ;
}
/* end subroutine (sihyphen) */

#endif /* CF_STRNCHR */


