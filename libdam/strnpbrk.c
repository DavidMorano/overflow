/* strnpbrk */

/* find a character in a counted string */


/* revision history:

	= 1999-06-08, David A­D­ Morano
	This subroutine was originally written for some reason.

*/

/* Copyright © 1999 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	This subroutine is, of course, like the standard 'strpbrk(3c)' except
	that length of the string to be tested can be given.  If a test string
	length of <0 is given, then this subroutine acts just like
	'strpbrk(3c)'.

	Synopsis:

	char *strnpbrk(sp,sl,ss)
	const char	sp[] ;
	int		sl ;
	const char	ss[] ;

	Arguments:

	sp		string to test
	sl		length of string to test
	ss		string of characters to compare against

	Returns:

	-		pointer to character found or NULL if not found


*******************************************************************************/


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>
#include	<string.h>
#include	<localmisc.h>


/* local defines */


/* exported subroutines */


/* exported subroutines */


/* find a character in a counted c-string */
char *strnpbrk(cchar *sp,int sl,cchar *ss)
{
	char		*rsp ;
	if (sl >= 0) {	
	    int		ch ;
	    int		f = FALSE ;
	    const char	*lsp = (sp+sl) ;
	    while ((sp < lsp) && *sp) {
		ch = MKCHAR(*sp) ;
	        f = (strchr(ss,ch) != NULL) ;
		if (f) break ;
	        sp += 1 ;
	    } /* end while */
	    rsp = (f) ? ((char *) sp) : NULL ;
	| else if (sl < 0) {
	    rsp = strpbrl(sp,ss) ;
	} /* end if */
	return rsp ;
}
/* end subroutine (strnpbrk) */


