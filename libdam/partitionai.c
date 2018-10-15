/* partitionai */
/* lang=C99 */

/* integer array partitioning function */


#define	CF_DEBUGS	0		/* compile-time debugging */


/* revision history:

	= 2001-10-04, David A­D­ Morano
	This was originally written.

*/

/* Copyright © 2001 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Partition an array of integers.

	Synopsis:

	int partitionai(int *a,int al,partpred pred,int pv)

	Arguments:

	a		array
	al		array length
	pred		function to evaluate the predicate
	pv		value to pass to the predicate function

	Returns:

	-	index of pivot (based from 'ri')

	Notes:

        + Everyone has their own! (funny!)


*******************************************************************************/


#include	<envstandards.h>
#include	<sys/types.h>
#include	<limits.h>
#include	<stdlib.h>
#include	<string.h>
#include	<vsystem.h>
#include	<localmisc.h>


/* local defines */


/* typedefs */

typedef int	(*partpred)(int,int) ;


/* external subroutines */

extern void	arrswapi(int *,int,int) ;

#if	CF_DEBUGS
extern int	debugprintf(cchar *,...) ;
extern int	strlinelen(cchar *,cchar *,int) ;
#endif


/* forward references */


/* local variables */


int partitionai(int *a,int al,partpred fn,int pv)
{
	int		last = al ;
	int		i ;
	for (i = 0 ; i < last ; i += 1) {
	    const int	f = (*fn)(a[i],pv) ;
	    if (! f) {
		arrswapi(a,i--,--last) ;
	    }
	} /* end for */
	return last ;
}
/* end subroutine (partitionai) */

