/* pwentry */

/* some miscellaneous PWENTRY subroutines */
/* version %I% last modified %G% */


#define	CF_DEBUGS	0		/* non-switchable debugging */


/* revision history:

	= 1998-09-01, David A­D­ Morano
	This program was originally written.

	= 2018-12-21, David A.D. Morano
	Added |getpwentrybufsize(3dam)|.

*/

/* Copyright © 1998,2018 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	We provide some miscelleneous utility subroutines for the PWENTRY
	object.

	Synopsis:
	int getpwentrybufsize(void)

	Arguments:
	-

	Returns:
	>=0		size of necessary buffer to hold the data for 
			a PWENTRY object
	<0		error (yes, due to error from |getbufsize(3uc)|).


*******************************************************************************/


#define	PWENTRY_MASTER	0


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>
#include	<sys/param.h>		/* for MAXNAMELEN */
#include	<vsystem.h>
#include	<getbufsize.h>
#include	<localmisc.h>

#include	"pwentry.h"


/* local defines */


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */


/* local variables */


/* exported subroutines */


int getpwentrybufsize()
{
	int		rs ;
	if ((rs = getbufsize(getbufsize_pw)) >= 0) {
	    rs += MAXNAMELEN ; /* additional size for some extra stuff */
	}
	return rs ;
}
/* end subroutine (pwentry_bufsize) */


/* legacy only */
int pwentry_bufsize()
{
	return getpwentrybufsize() ;
}


