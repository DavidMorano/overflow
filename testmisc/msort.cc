/* msort */
/* lang=C++11 */


#define	CF_DEBUGS	0		/* compile-time debugging */


/* revision history:

	= 2013-05-23, David A­D­ Morano
	Originally written for Rightcore Network Services.

	= 2018-10-10, David A.D. Morano
	I made the memory allocations in a constructor a little more
	exception-safe. Yes, (there was a question) this code requires C++11.

*/

/* Copyright © 2013,2018 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Our version of Quick Sort (sort of the daddy of all sorts, mostly).

	Everyone has their own, right?

	Synopsis:

	typedef int	(*msortcmp)(const void *,const void *) ;
	void msort(void *base,int nelem,int esize,msortcmp cmp)

	Arguments:

	base		pointer to base of array to sort
	nelem		number of elements in array
	esize		size in bytes of an array element
	cmp		comparison function

	Returns:

	-		nothing (sorted array in place)


*******************************************************************************/


#include	<envstandards.h>
#include	<sys/types.h>
#include	<climits>
#include	<cstring>
#include	<new>
#include	<initializer_list>
#include	<utility>
#include	<functional>
#include	<algorithm>
#include	<vsystem.h>
#include	<localmisc.h>


/* local defines */


/* name-spaces */

using namespace	std ;


/* type-defs */

typedef "C" int	(*msortcmp)(const void *,const void *) ;
typedef "C" int	(*partpred)(const void *,const void *) ;


/* external subroutines */

extern "C" int	msort(void *,int,int,msortcmp) ;

extern "C" int	partitionai(int *,int,partpred,int) ;

#if	CF_DEBUGS
extern "C" int	debugprintf(cchar *,...) ;
extern "C" int	strlinelen(cchar *,cchar *,int) ;
#endif


/* local structures */

struct msort_data {
	char		*base = NULL ;
	int		n ;		/* number of elements */
	int		es ;		/* element size */
	int		(*cmpfun)(const void *,const void *) ;
	char		*tmp = NULL ;
	char		*pvp = NULL ;
	char		*a = NULL ;
	msort_data(char *baser,int nelem,int esize,msortcmp cmp) 
		: base(baser), n(ne), es(esize), cmpfun(cmp) {
	    const int	tsize = (esize+1) ;
	    const int	psize = (esize+1) ;
	    int		asize = (tsize + psize) ;
	    a = new char[asize] ;
	    tmp = (a + 0) ;
	    pvp = (a + tsize) ;
	} ;
	~msort_data() {
	    if (a) {
		delete [] a ;
		a = NULL ;
	    }
	}
	void swap(int i1,int i2) {
	    char	*i1p = (base+(i1*es)) ;
	    char	*i2p = (base+(i2*es)) ;
 	    memcpy(tmp,i1p,es) ;
 	    memcpy(i1p,i2p,es) ;
 	    memcpy(i2p,tmp,es) ;
	} ;
	int dosort(int,int) ;
	int docmp(int i1,int i2) {
	    const void	*i1p = (base+(i1*es)) ;
	    const void	*i2p = (base+(i2*es)) ;
	    return (*cmpfun)(i1p,i2p) ;
	} ;
	void loadpivot(int i) {
	    const char	*ip = (base+(i*es)) ;
	    memcpy(pvp,ip,es) ;
	} ;
	int getpivot(int,int) ;
} ;


/* forward references */

static int	partpred1(int,int) ;
static int	partpred2(int,int) ;


/* exported subroutines */


int msort(void *base,int n,int es,msortcmp cmp)
{
	msort_data	data(base,n,es,cmp) ;
	return data.dosort(0,n) ;
}
/* end subroutine (msort) */


/* local subroutines */


msort_data::int dosort(int first,int last)
{
	int		ff = FALSE ;
#if	CF_DEBUGS
	debugprintf("msort_data::dosort: ent f=%u l=%u\n",first,last) ;
#endif
	if ((last-first) == 2) {
	    if (docmp(first,last-1) > 0) swap(first,(last-1)) ;
	    ff = TRUE ;
	} else if ((last-first) > 2) {
	    int		m1, m2 ;
	    int		pvi ;
	    ff = TRUE ;
#if	CF_DEBUGS
	    debugprintf("msort_data::dosort: pv=%u\n",pv) ;
#endif
	    pvi = getpivot(first,(last-first)) ;
	    m1 = partitionai(a+first,(last-first),partpred1,a[pv]) + first ;
	    m2 = partitionai(a+m1,(last-m1),partpred2,a[pv]) + m1 ;
#if	CF_DEBUGS
	    debugprintf("msort_data::dosort: m1=%u m2=%u\n",m1,m2) ;
#endif
	    if ((m1-first) > 1) dosort(first,m1) ;
	    if ((last-m2) > 1) dosort(m2,last) ;
	}
#if	CF_DEBUGS
	debugprintf("msort_data::dosort: ret f=%u\n",ff) ;
#endif
	return ff ;
}
/* end method (msort_data::dosort) */


int msort_data::getpivot(int first,int al)
{
	int	pvi = (al/2) ;
	if (pvi == 0) {
	    if (al > 1) pvi = 1 ;
	}
	loadpivot(first+pvi) ;
	return pvi ;
}
/* end method (msort_data::getpivot) */


static int partpred1(int e,int pv)
{
	return (e < pv) ;
}


static int partpred2(int e,int pv)
{
	return (e <= pv) ;
}

