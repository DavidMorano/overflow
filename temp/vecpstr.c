/* vecpstr */

/* vector-packed-string object */


#define	CF_DEBUGS	0		/* compile-time debug print-outs */
#define	CF_SAFE1	1		/* safe-level=1 */
#define	CF_SAFE2	1		/* safe-level=2 (more safe) */
#define	CF_STRNLEN	0		/* use 'strnlen(3dam)' */
#define	CF_VSTRSORT	0		/* use |vstrsort()| */


/* revision history:

	= 1998-03-24, David A�D� Morano
        This object module was morphed from some previous one. I do not remember
        what the previous one was.

*/

/* Copyright � 1998 David A�D� Morano.  All rights reserved. */

/*******************************************************************************

	This object module creates and manages a string table object.  This
	string table can later be written to a file or otherwise stored some
	way so that it can be used in-place later.  This is often useful for
	cache files or ELF code object files.

	Arguments:

	stp		pointer to the vecpstr object
	<others>

	Returns:

	>=0		the total length of the filled up vecpstr so far!
	<0		error


	Note: The index table (optionally) generated by this OBJECT using 
	-> hash-linking <- to track down matches.  It does not use 
	-> key-linking <-.  So searching the generated index table must also 
	use hash-linking.


*******************************************************************************/


#define	VECPSTR_MASTER	0


#include	<envstandards.h>

#include	<sys/types.h>
#include	<unistd.h>
#include	<stdlib.h>
#include	<string.h>

#include	<vsystem.h>
#include	<vechand.h>
#include	<localmisc.h>

#ifdef	COMMENT
#include	<vecobj.h>
#include	<hdb.h>
#endif

#include	"vecpstr.h"


/* local defines */

#define	VECPSTR_CHUNKSIZE	512	/* starting table size */
#define	VECPSTR_NSKIP		5
#define	VECPSTR_CHUNK		struct vecpstr_chunk

#define	MODP2(v,n)	((v) & ((n) - 1))


/* external subroutines */

extern uint	nextpowtwo(uint) ;
extern uint	hashelf(const void *,int) ;
extern uint	hashagain(uint,int,int) ;
extern uint	uceil(uint,int) ;

extern int	iceil(int,int) ;
extern int	randlc(int) ;
extern int	nleadstr(const char *,const char *,int) ;

#if	CF_DEBUGS
extern int	debugprintf(const char *,...) ;
extern int	strlinelen(const char *,int,int) ;
#endif

extern char	*strwcpy(char *,const char *,int) ;

#if	CF_VSTRSORT
extern void	vstrsort(char **,int,int (*)()) ;
#endif


/* local structures */

struct strentry {
	uint	khash ;
	uint	hi ;
	uint	si ;
} ;


/* forward references */

int		vecpstr_store(VECPSTR *,const char *,int,const char **) ;

static int	vecpstr_setopts(VECPSTR *,int) ;
static int	vecpstr_finchunks(VECPSTR *) ;
static int	vecpstr_extstr(VECPSTR *,int) ;
static int	vecpstr_newchunk(VECPSTR *,int) ;
static int	vecpstr_extvec(VECPSTR *,int) ;
static int	vecpstr_record(VECPSTR *,cchar *) ;
static int	vecpstr_reset(VECPSTR *) ;

static int chunk_start(VECPSTR_CHUNK *,int,int) ;
static int chunk_finish(VECPSTR_CHUNK *) ;
static int chunk_check(VECPSTR_CHUNK *,int) ;
static int chunk_add(VECPSTR_CHUNK *,cchar *,int,cchar **) ;
static int chunk_addkeyval(VECPSTR_CHUNK *,cchar *,int,cchar *,int,cchar **) ;

static int	indexlen(int) ;
static int	indexsize(int) ;
static int	vcmpdef() ;


/* local variables */


/* exported subroutines */


int vecpstr_start(VECPSTR *op,int n,int chunksize,int opts)
{
	int		rs ;

#if	CF_SAFE1
	if (op == NULL) return SR_FAULT ;
#endif

	if (chunksize < VECPSTR_CHUNKSIZE)
	    chunksize = VECPSTR_CHUNKSIZE ;

	if (n < 0) n = 0 ;

	memset(op,0,sizeof(VECPSTR)) ;
	op->chunksize = chunksize ;
	op->an = n ;

	if ((vecpstr_setopts(op,opts)) >= 0) {
	    const int	ne = MIN(((n * 6) / chunksize),1) ;
	    if ((rs = vechand_start(&op->chunks,ne,0)) >= 0) {
	        op->magic = VECPSTR_MAGIC ;
	    }
	}

	return rs ;
}
/* end subroutine (vecpstr_start) */


/* free up this vecpstr object */
int vecpstr_finish(VECPSTR *op)
{
	int		rs = SR_OK ;
	int		rs1 ;

#if	CF_SAFE1
	if (op == NULL) return SR_FAULT ;
#endif

#if	CF_SAFE2
	if (op->magic != VECPSTR_MAGIC) return SR_NOTOPEN ;
#endif

	if (op->va != NULL) {
	    rs1 = uc_free(op->va) ;
	    if (rs >= 0) rs = rs1 ;
	    op->va = NULL ;
	}

	rs1 = vecpstr_finchunks(op) ;
	if (rs >= 0) rs = rs1 ;

	rs1 = vechand_finish(&op->chunks) ;
	if (rs >= 0) rs = rs1 ;

	op->magic = 0 ;
	return rs ;
}
/* end subroutine (vecpstr_finish) */


int vecpstr_audit(VECPSTR *op)
{
	int		rs = SR_OK ;
	int		i ;
	int		c = 0 ;
	char		*cp ;

	if (op == NULL) return SR_FAULT ;

	if (op->va == NULL) return SR_NOTOPEN ;

	for (i = 0 ; i < op->i ; i += 1) {
	    if (op->va[i] != NULL) {
		c += 1 ;
	        cp = (char *) op->va[i] ;
	        rs |= *cp ;		/* access might SEGFAULT (as wanted) */
	    }
	} /* end for */

	return (rs >= 0) ? c : rs ;
}
/* end subroutine (vecpstr_audit) */


/* add a character-string */
int vecpstr_add(VECPSTR *op,cchar *sp,int sl)
{

	return vecpstr_store(op,sp,sl,NULL) ;
}
/* end subroutine (vecpstr_add) */


int vecpstr_adduniq(VECPSTR *op,cchar *sp,int sl)
{
	int		sch ;
	int		rs ;
	int		i ;
	int		m ;
	int		f = FALSE ;
	const char	*ep ;

	if (op == NULL) return SR_FAULT ;
	if (sp == NULL) return SR_FAULT ;

#if	CF_SAFE2
	if (op->magic != VECPSTR_MAGIC) return SR_NOTOPEN ;
#endif

	if (sl < 0) sl = strlen(sp) ;

#if	CF_DEBUGS
	debugprintf("vecpstr_adduniq: ent s=>%t<\n",sp,sl) ;
#endif

	    sch = sp[0] ; /* ok: since all get promoted similarly */
	    for (i = 0 ; i < op->i ; i += 1) {
	        ep = op->va[i] ;
	        if (sch == ep[0]) {
	            m = nleadstr(ep,sp,sl) ;
	            f = ((m == sl) && (ep[m] == '\0')) ;
		    if (f) break ;
	        }
	    } /* end for */

#if	CF_DEBUGS
	debugprintf("vecpstr_adduniq: mid f=%u\n",f) ;
#endif

	if (f) {
	    rs = INT_MAX ;
	} else {
	    rs = vecpstr_store(op,sp,sl,NULL) ;
	}

#if	CF_DEBUGS
	debugprintf("vecpstr_adduniq: ret rs=%d f=%u\n",rs,f) ;
#endif

	return rs ;
}
/* end subroutine (vecpstr_adduniq) */


int vecpstr_addkeyval(vecpstr *op,cchar *kp,int kl,cchar *vp,int vl)
{
	int		rs = SR_OK ;
	int		amount = 0 ;
	int		i = 0 ;

	if (op == NULL) return SR_FAULT ;
	if (kp == NULL) return SR_FAULT ;

#if	CF_SAFE2
	if (op->magic != VECPSTR_MAGIC) return SR_NOTOPEN ;
#endif

	if (kl < 0) kl = strlen(kp) ;

	amount += (kl+1) ;
	if (vp != NULL) {
	    if (vl < 0) vl = strlen(vp) ;
	    amount += (vl+1) ;
	}

/* do we need to extend the table? */

	if ((rs = vecpstr_extstr(op,amount)) >= 0) {
	    cchar	*cp ;
	    if ((rs = chunk_addkeyval(op->ccp,kp,kl,vp,vl,&cp)) >= 0) {
	        rs = vecpstr_record(op,cp) ;
	        i = rs ;
	    }
	}

/* update table length */

	if (rs >= 0) op->stsize += amount ;

#if	CF_DEBUGS
	debugprintf("vecpstr_store: ret rs=%d i=%u\n",rs,i) ;
#endif

	return (rs >= 0) ? i : rs ;
}
/* end subroutine (vecpstr_addkeyval) */


/* store a string into the table */
int vecpstr_store(VECPSTR *op,cchar *sp,int sl,cchar **rpp)
{
	int		rs = SR_OK ;
	int		amount ;
	int		i = 0 ;
	cchar		*cp = NULL ;

	if (op == NULL) return SR_FAULT ;
	if (sp == NULL) return SR_FAULT ;

#if	CF_SAFE2
	if (op->magic != VECPSTR_MAGIC) return SR_NOTOPEN ;
#endif

	if (sl < 0) sl = strlen(sp) ;

#if	CF_DEBUGS
	debugprintf("vecpstr_store: s=>%t<\n",
	    sp,strlinelen(sp,sl,50)) ;
#endif

/* do we need to extend the table? */

	amount = (sl + 1) ;
	if ((rs = vecpstr_extstr(op,amount)) >= 0) {
	    if ((rs = chunk_add(op->ccp,sp,sl,&cp)) >= 0) {
	        rs = vecpstr_record(op,cp) ;
	        i = rs ;
	    }
#if	CF_DEBUGS
	debugprintf("vecpstr_store: _record() rs=%d\n",rs) ;
#endif
	}

/* update table length */

	if (rs >= 0) op->stsize += amount ;

	if (rpp != NULL) {
	    *rpp = (rs >= 0) ? cp : NULL ;
	}

#if	CF_DEBUGS
	debugprintf("vecpstr_store: ret rs=%d\n",rs) ;
#endif

	return (rs >= 0) ? i : rs ;
}
/* end subroutine (vecpstr_store) */


/* is a given string already represented? */
int vecpstr_already(VECPSTR *op,cchar *sp,int sl)
{
	int		sch ;
	int		rs = SR_NOTFOUND ;
	int		m ;
	int		i ;
	const char	*ep ;

#if	CF_SAFE1
	if (op == NULL) return SR_FAULT ;
#endif
	if (sp == NULL) return SR_FAULT ;

#if	CF_SAFE2
	if (op->magic != VECPSTR_MAGIC) return SR_NOTOPEN ;
#endif

#if	CF_STRNLEN
	sl = strnlen(sp,sl) ;
#else
	if (sl < 0) sl = strlen(sp) ;
#endif

/* do we have it already? */

	sch = sp[0] ; /* ok: since all get promoted similarly */
	for (i = 0 ; i < op->i ; i += 1) {
	    ep = op->va[i] ;
	    if (sch == ep[0]) {
		m = nleadstr(ep,sp,sl) ;
		if ((m == sl) && (ep[m] == '\0')) break ;
	    }
	} /* end for */
	if (i < op->i) rs = i ;

	return rs ;
}
/* end subroutine (vecpstr_already) */


/* get a string by its record-number */
int vecpstr_get(VECPSTR *op,int i,cchar **rpp)
{
	int		rs = SR_OK ;

#if	CF_SAFE1
	if (op == NULL) return SR_FAULT ;
#endif

#if	CF_SAFE2
	if (op->magic != VECPSTR_MAGIC) return SR_NOTOPEN ;
#endif

	if ((i < 0) || (i >= op->i)) {
	    rs = SR_NOTFOUND ;
	}

	if (rpp != NULL) {
	    *rpp = (rs >= 0) ? op->va[i] : NULL ;
	}

	return rs ;
}
/* end subroutine (vecpstr_get) */


/* delete by index */
int vecpstr_del(vecpstr *op,int i)
{
	int		f_fi = FALSE ;

	if (op == NULL) return SR_FAULT ;

#if	CF_SAFE2
	if (op->magic != VECPSTR_MAGIC) return SR_NOTOPEN ;
#endif

	if (op->va == NULL) return SR_NOTOPEN ;

	if ((i < 0) || (i >= op->i)) return SR_NOTFOUND ;

/* delete the entry (adjust container object data to reflect) */

	if ((op->va)[i] != NULL) {

	    op->c -= 1 ;		/* decrement list count */
	    if (op->f.stsize) {
	        op->stsize -= (strlen((op->va)[i]) + 1) ;
	    }

	} /* end if (freeing the actual string data) */

/* apply the appropriate deletion based on management policy */

	if (op->f.ostationary) {

	    (op->va)[i] = NULL ;
	    if (i == (op->i - 1)) op->i -= 1 ;
	    f_fi = TRUE ;

	} else if (op->f.issorted || op->f.oordered) {

	    if (op->f.ocompact) {
		int	j ;

	        op->i -= 1 ;
	        for (j = i ; j < op->i ; j += 1) {
	            (op->va)[j] = (op->va)[j + 1] ;
		}
	        (op->va)[op->i] = NULL ;

	    } else {

	        (op->va)[i] = NULL ;
	        if (i == (op->i - 1)) op->i -= 1 ;
	        f_fi = TRUE ;

	    } /* end if */

	} else {

	    if ((op->f.oswap || op->f.ocompact) && (i < (op->i - 1))) {

	        (op->va)[i] = (op->va)[op->i - 1] ;
	        (op->va)[--op->i] = NULL ;
	        op->f.issorted = FALSE ;

	    } else {

	        (op->va)[i] = NULL ;
	        if (i == (op->i - 1)) op->i -= 1 ;
	        f_fi = TRUE ;

	    } /* end if */

	} /* end if */

	if (op->f.oconserve) {

	    while (op->i > i) {
	        if (op->va[op->i - 1] != NULL) break ;
	        op->i -= 1 ;
	    } /* end while */

	} /* end if */

	if (f_fi && (i < op->fi)) {
	    op->fi = i ;
	}

	return op->c ;
}
/* end subroutine (vecpstr_del) */


int vecpstr_delall(VECPSTR *op)
{
	int		rs = SR_OK ;
	int		rs1 ;

	rs1 = vecpstr_finchunks(op) ;
	if (rs >= 0) rs = rs1 ;
	op->ccp = NULL ;

	rs1 = vechand_delall(&op->chunks) ;
	if (rs >= 0) rs = rs1 ;

	if (op->va != NULL) {
	    rs1 = uc_free(op->va) ;
	    if (rs >= 0) rs = rs1 ;
	    op->va = NULL ;
	}

	if (rs >= 0) {
	    rs = vecpstr_reset(op) ;
	}

	return rs ;
}
/* end subroutine (vecpstr_delall) */


/* get the string count in the table */
int vecpstr_count(VECPSTR *op)
{

#if	CF_SAFE1
	if (op == NULL) return SR_FAULT ;
#endif

#if	CF_SAFE2
	if (op->magic != VECPSTR_MAGIC) return SR_NOTOPEN ;
#endif

	return op->c ;
}
/* end subroutine (vecpstr_count) */


/* sort the strings in the vector list */
int vecpstr_sort(VECPSTR *op,int (*vcmpfunc)())
{

	if (op == NULL) return SR_FAULT ;

	if (op->va == NULL) return SR_NOTOPEN ;

#if	CF_DEBUGS
	debugprintf("vecpstr_sort: ent issorted=%u\n",op->f.issorted) ;
#endif

	if (vcmpfunc == NULL)
	    vcmpfunc = vcmpdef ;

	if ((! op->f.issorted) && (op->i > 1)) {

#if	CF_VSTRSORT
	    vstrsort(op->va,op->i,vcmpfunc) ;
#else
	    qsort(op->va,op->i,sizeof(char *),vcmpfunc) ;
#endif /* CF_VSTRSORT */

	} /* end if (sorting) */

	op->f.issorted = TRUE ;
	return op->i ;
}
/* end subroutine (vecpstr_sort) */


/* search for a string in the vector list */
int vecpstr_search(VECPSTR *op,cchar sp[],int (*vcmpfunc)(),cchar **rpp)
{
	int		rs ;
	int		i ;
	const char	**rpp2 ;

	if (op == NULL) return SR_FAULT ;

	if (op->va == NULL) return SR_NOTOPEN ;

	if (vcmpfunc == NULL)
	    vcmpfunc = vcmpdef ;

#ifdef	COMMENT
	if (! op->f.issorted) {
	    op->f.issorted = TRUE ;
	    if (op->i > 1) {
	        qsort(op->va,op->i,sizeof(char *),vcmpfunc) ;
	    }
	} /* end if (sorting) */
#endif /* COMMENT */

	if (op->f.issorted) {
	    const int	esize = sizeof(char *) ;

	    rpp2 = (cchar **) bsearch(&sp,op->va,op->i,esize,vcmpfunc) ;

	    rs = SR_NOTFOUND ;
	    if (rpp2 != NULL) {
	        i = rpp2 - op->va ;
	        rs = SR_OK ;
	    }

	} else {

	    for (i = 0 ; i < op->i ; i += 1) {
	        rpp2 = (op->va + i) ;
	        if (*rpp2 != NULL) {
	            if ((*vcmpfunc)(&sp,rpp2) == 0) break ;
		}
	    } /* end for */
	    rs = (i < op->i) ? SR_OK : SR_NOTFOUND ;

	} /* end if (sorted or not) */

	if (rpp != NULL) {
	    *rpp = (rs >= 0) ? op->va[i] : NULL ;
	}

	return (rs >= 0) ? i : rs ;
}
/* end subroutine (vecpstr_search) */


int vecpstr_findn(VECPSTR *op,cchar sp[],int sl)
{

	return vecpstr_already(op,sp,sl) ;
}
/* end subroutine (vecpstr_findn) */


/* search for a string in the vector list */
int vecpstr_finder(VECPSTR *op,cchar sp[],int (*vcmpfunc)(),cchar **rpp)
{
	int		rs = SR_NOTFOUND ;
	int		i ;

	if (op == NULL) return SR_FAULT ;

	if (op->va == NULL) return SR_NOTOPEN ;

	if (vcmpfunc == NULL)
	    vcmpfunc = vcmpdef ;

	if (rpp != NULL)
	    *rpp = NULL ;

	for (i = 0 ; i < op->i ; i += 1) {
	    if (op->va[i] != NULL) {
	        if ((*vcmpfunc)(&sp,(op->va + i)) == 0) break ;
	    }
	} /* end for */

	if (i < op->i) {
	    rs = i ;
	    if (rpp != NULL) {
	        *rpp = op->va[i] ;
	    }
	}

	return rs ;
}
/* end subroutine (vecpstr_finder) */


/* find if a string is already in the vector list */

/*
	This method (subroutine) is really just:

		vecpstr_finder(lp,string,NULL,NULL)

	but is shorter.

*/

int vecpstr_find(VECPSTR *op,cchar sp[])
{
	int		sch ;
	int		rs = SR_NOTFOUND ;
	int		i ;
	const char	*ep ;

	if (op == NULL) return SR_FAULT ;
	if (sp == NULL) return SR_FAULT ;

	if (op->va == NULL) return SR_NOTOPEN ;

	sch = sp[0] ; /* ok: since all get promoted similarly */
	for (i = 0 ; i < op->i ; i += 1) {
	    ep = op->va[i] ;
	    if (ep == NULL) continue ;
	    if ((sch == ep[0]) && (strcmp(sp,ep) == 0)) break ;
	} /* end for */

	if (i < op->i) rs = i ;

	return rs ;
}
/* end subroutine (vecpstr_find) */


int vecpstr_findaddr(VECPSTR *op,cchar addr[])
{
	int		rs = SR_NOTFOUND ;
	int		i ;
	const char	*ep ;

	if (op == NULL) return SR_FAULT ;

	if (op->va == NULL) return SR_NOTOPEN ;

#ifdef	COMMENT
	if (addr == NULL)
	    return SR_FAULT ;
#endif

	for (i = 0 ; i < op->i ; i += 1) {
	    ep = op->va[i] ;
	    if ((ep != NULL) && (addr == ep)) {
	        rs = i ;
	        break ;
	    }
	} /* end for */

	return rs ;
}
/* end subroutine (vecpstr_findaddr) */


int vecpstr_getsize(VECPSTR *op)
{
	int		size = 0 ;

#if	CF_SAFE1
	if (op == NULL) return SR_FAULT ;
#endif

#if	CF_SAFE2
	if (op->magic != VECPSTR_MAGIC) return SR_NOTOPEN ;
#endif

	if (op->stsize > 0) size = (op->stsize-1) ;

	return size ;
}
/* end subroutine (vecpstr_getsize) */


int vecpstr_strsize(VECPSTR *op)
{
	int		size ;

#if	CF_SAFE1
	if (op == NULL) return SR_FAULT ;
#endif

#if	CF_SAFE2
	if (op->magic != VECPSTR_MAGIC) return SR_NOTOPEN ;
#endif

	if (! op->f.stsize) {
	    int		i ;
	    for (i = 0 ; op->va[i] != NULL ; i += 1) {
	        if (op->va[i] != NULL) {
	            size += (strlen(op->va[i]) + 1) ;
		}
	    } /* end for */
	    op->stsize = size ;
	    op->f.stsize = TRUE ;
	} /* end if (calculating size) */

	size = uceil(op->stsize,sizeof(int)) ;

	return size ;
}
/* end subroutine (vecpstr_strsize) */


/* make the string table */
int vecpstr_strmk(VECPSTR *op,char *tab,int tabsize)
{
	int		rs = SR_OK ;
	int		size ;
	int		c = 0 ;

#if	CF_SAFE1
	if (op == NULL) return SR_FAULT ;
#endif

#if	CF_SAFE2
	if (op->magic != VECPSTR_MAGIC) return SR_NOTOPEN ;
#endif

	if (tab == NULL) return SR_FAULT ;

	size = uceil(op->stsize,sizeof(int)) ;

	if (tabsize >= size) {
	    VECPSTR_CHUNK	*ccp ;
	    int		i ;
	    char	*bp = tab ;
	    for (i = 0 ; vechand_get(&op->chunks,i,&ccp) >= 0 ; i += 1) {
	        if (ccp != NULL) {
	            if (ccp->tab != NULL) {
	                c += 1 ;
	                memcpy(bp,ccp->tab,ccp->tablen) ;
	                bp += ccp->tablen ;
	            }
		}
	    } /* end for */
	    while (bp < (tab + tabsize)) {
	        *bp++ = '\0' ;
	    }
	} else {
	    rs = SR_OVERFLOW ;
	}

	return (rs >= 0) ? c : rs ;
}
/* end subroutine (vecpstr_strmk) */


/* calculate the index table length (entries) */
int vecpstr_recsize(VECPSTR *op)
{
	int		size ;

#if	CF_SAFE1
	if (op == NULL) return SR_FAULT ;
#endif

#if	CF_SAFE2
	if (op->magic != VECPSTR_MAGIC) return SR_NOTOPEN ;
#endif

	size = (op->i + 2) * sizeof(int) ;
	return size ;
}
/* end subroutine (vecpstr_recsize) */


/* make the record table and the string table simultaneously */
int vecpstr_recmkstr(VECPSTR *op,int *rec,int recsize,char *tab,int tabsize)
{
	int		rs = SR_OK ;
	int		size ;
	int		c = 0 ;

	if (op == NULL) return SR_FAULT ;
	if (tab == NULL) return SR_FAULT ;
	if (rec == NULL) return SR_FAULT ;

	if (op->va == NULL) return SR_NOTOPEN ;

/* check supplied tabsize */

	size = iceil(op->stsize,sizeof(int)) ;

	if (tabsize >= size) {
	    size = (op->i + 2) * sizeof(int) ;
	    if (recsize >= size) {
		int	i ;
		char	*bp = tab ;		/* table pointer */
	        rec[c++] = 0 ;
	        *bp++ = '\0' ;
	        for (i = 0 ; op->va[i] != NULL ; i += 1) {
	            if (op->va[i] != NULL) {
	                rec[c++] = (bp - tab) ;
	                bp = (strwcpy(bp,op->va[i],-1) + 1) ;
		    }
	        } /* end for */
	        rec[c] = -1 ;
	    } else {
	        rs = SR_OVERFLOW ;
	    }
	} else {
	    rs = SR_OVERFLOW ;
	}

	return (rs >= 0) ? c : rs ;
}
/* end subroutine (vecpstr_recmkstr) */


int vecpstr_recmk(VECPSTR *op,int rec[],int recsize)
{
	int		rs = SR_OK ;
	int		size ;
	int		c = 0 ;

	if (op == NULL) return SR_FAULT ;
	if (rec == NULL) return SR_FAULT ;

	if (op->va == NULL) return SR_NOTOPEN ;

/* check supplied size */

	size = (op->i + 2) * sizeof(int) ;

	if (recsize >= size) {
	    int		i ;
	    int		si = 0 ;
	    rec[c++] = si ;
	    si += 1 ;
	    for (i = 0 ; op->va[i] != NULL ; i += 1) {
	        if (op->va[i] != NULL) {
	            rec[c++] = si ;
	            si += (strlen(op->va[i]) + 1) ;
		}
	    } /* end for */
	    rec[c] = -1 ;
	} else {
	    rs = SR_OVERFLOW ;
	}

	return (rs >= 0) ? c : rs ;
}
/* end subroutine (vecpstr_recmk) */


/* calculate the index table length (entries) */
int vecpstr_indlen(VECPSTR *op)
{
	int		il ;

#if	CF_SAFE1
	if (op == NULL) return SR_FAULT ;
#endif

#if	CF_SAFE2
	if (op->magic != VECPSTR_MAGIC) return SR_NOTOPEN ;
#endif

	il = indexlen(op->i + 1) ;

#if	CF_DEBUGS
	debugprintf("vecpstr_indlen: ret il=%u\n",il) ;
#endif

	return il ;
}
/* end subroutine (vecpstr_indlen) */


/* calculate the index table size */
int vecpstr_indsize(VECPSTR *op)
{
	int		il ;
	int		isize ;

#if	CF_SAFE1
	if (op == NULL) return SR_FAULT ;
#endif

#if	CF_SAFE2
	if (op->magic != VECPSTR_MAGIC) return SR_NOTOPEN ;
#endif

	il = indexlen(op->i + 1) ;

	isize = indexsize(il) ;

	return isize ;
}
/* end subroutine (vecpstr_indsize) */


/* get the vector array address */
int vecpstr_getvec(VECPSTR *op,cchar ***rppp)
{
	int		rs ;

	if (op == NULL) return SR_FAULT ;
	if (rppp == NULL) return SR_FAULT ;

	if ((rs = vecpstr_extvec(op,1)) >= 0) {
	    *rppp = op->va ;
	}

	return (rs >= 0) ? op->i : rs ;
}
/* end subroutine (vecpstr_getvec) */


/* private subroutines */


static int vecpstr_setopts(VECPSTR *op,int options)
{

	memset(&op->f,0,sizeof(struct vecpstr_flags)) ;

	if (options & VECPSTR_OREUSE) op->f.oreuse = 1 ;
	if (options & VECPSTR_OSWAP) op->f.oswap = 1 ;
	if (options & VECPSTR_OSTATIONARY) op->f.ostationary = 1 ;
	if (options & VECPSTR_OCOMPACT) op->f.ocompact = 1 ;
	if (options & VECPSTR_OSORTED) op->f.osorted = 1 ;
	if (options & VECPSTR_OORDERED) op->f.oordered = 1 ;
	if (options & VECPSTR_OCONSERVE) op->f.oconserve = 1 ;
	if (options & VECPSTR_OSTSIZE) op->f.stsize = 1 ;

	return SR_OK ;
}
/* end subroutine (vecpstr_setopts) */


/* free up all of the chunks */
static int vecpstr_finchunks(VECPSTR *op)
{
	VECPSTR_CHUNK	*ccp ;
	int		rs = SR_OK ;
	int		rs1 ;
	int		i ;
	int		c = 0 ;

	for (i = 0 ; vechand_get(&op->chunks,i,&ccp) >= 0 ; i += 1) {
	    if (ccp != NULL) {
	        c += 1 ;
	        rs1 = chunk_finish(ccp) ;
	        if (rs >= 0) rs = rs1 ;
	        rs1 = uc_free(ccp) ;
	        if (rs >= 0) rs = rs1 ;
	    }
	} /* end for */

#if	CF_DEBUGS
	debugprintf("vecpstr_finchunks: cs=%u chunks_freed=%u\n",
	    op->chunksize,c) ;
#endif

	op->ccp = NULL ;
	return (rs >= 0) ? c : rs ;
}
/* end subroutine (vecpstr_finchunks) */


/* extend the string table */
static int vecpstr_extstr(VECPSTR *op,int amount)
{
	int		rs = SR_OK ;

	if (op->ccp != NULL) {
	    if (chunk_check(op->ccp,amount) > 0) op->ccp = NULL ;
	} /* end if (check if could add to existing chunk) */

	if ((rs >= 0) && (amount > 0) && (op->ccp == NULL)) {
	    rs = vecpstr_newchunk(op,amount) ;
	}

	return rs ;
}
/* end subroutine (vecpstr_extstr) */


static int vecpstr_newchunk(VECPSTR *op,int amount)
{
	const int	size = sizeof(VECPSTR_CHUNK) ;
	int		rs ;
	int		start = 0 ;
	void		*p ;

#if	CF_DEBUGS
	debugprintf("vecpstr_newchunk: ent\n") ;
#endif

	op->ccp = NULL ;
	if ((rs = uc_malloc(size,&p)) >= 0) {
	    op->ccp = p ;
	    if (op->stsize == 0) {
	        op->stsize = 1 ;
	        start = 1 ;
	    }
	    if (amount < op->chunksize) amount = op->chunksize ;
	    if ((rs = chunk_start(op->ccp,amount,start)) >= 0) {
	        rs = vechand_add(&op->chunks,op->ccp) ;
		if (rs < 0)
		    chunk_finish(op->ccp) ;
	    } /* end if (chunk) */
	    if (rs < 0) {
	        uc_free(op->ccp) ;
	        op->ccp = NULL ;
	    }
	} /* end if (memory-allocation) */

	return rs ;
}
/* end subroutine (vecpstr_newchunk) */


static int vecpstr_extvec(VECPSTR *op,int n)
{
	int		rs = SR_OK ;

	if ((op->i + 1) > op->n) {
	    int		nn, size ;
	    void	*np ;

	    if (op->va == NULL) {
	        const int	dn = (n > 0) ? n : VECPSTR_DEFENTS ;

	        nn = op->an ;
	        if (nn < dn) nn = dn ;
	        size = (nn + 1) * sizeof(char **) ;
	        rs = uc_malloc(size,&np) ;

	    } else {

	        nn = (op->n + 1) * 2 ;
	        size = (nn + 1) * sizeof(char **) ;
	        rs = uc_realloc(op->va,size,&np) ;
	        op->va = NULL ;

	    } /* end if */

	    if (rs >= 0) {
	        op->va = (const char **) np ;
	        op->va[op->i] = NULL ;
	        op->n = nn ;
	    }

	} /* end if */

	return rs ;
}
/* end subroutine (vecpstr_extvec) */


static int vecpstr_record(VECPSTR *op,cchar *sp)
{
	int		rs = SR_OK ;
	int		i = 0 ;

	if ((op->i + 1) > op->n) {
	    rs = vecpstr_extvec(op,-1) ;
	}

	if (rs >= 0) {
	    i = op->i ;
	    (op->va)[(op->i)++] = sp ;
	    (op->va)[op->i] = NULL ;
	    op->c += 1 ;
	}

	return (rs >= 0) ? i : rs ;
}
/* end subroutine (vecpstr_record) */


static int vecpstr_reset(VECPSTR *op)
{
	op->c = 0 ;
	op->i = 0 ;
	op->n = 0 ;
	op->fi = 0 ;
	op->stsize = 0 ;
	return SR_OK ;
}
/* end subroutine (vecpstr_reset) */


static int chunk_start(VECPSTR_CHUNK *ccp,int chunksize,int start)
{
	int		rs ;

#if	CF_DEBUGS
	debugprintf("chunk_start: start=%u\n",start) ;
#endif

	chunksize = iceil(chunksize,8) ;

	memset(ccp,0,sizeof(VECPSTR_CHUNK)) ;

	if ((rs = uc_malloc(chunksize,&ccp->tab)) >= 0) {
	    ccp->tabsize = chunksize ;
	    ccp->tab[0] = '\0' ;
	    ccp->tablen = start ;
#ifdef	COMMENT
	    if (start > 1) { /* start: baroque safety procedure */
	        int	ml = MIN(start,ccp->tabsize) ;
	        memset(ccp->tab,0,ml) ;
	        if (ccp->tablen > ml)
	            ccp->tablen = ml ;
	    } /* end: baroque safety procedure */
#endif /* COMMENT */
	} /* end if (memory-allocation) */

	return rs ;
}
/* end subroutine (chunk_start) */


static int chunk_finish(VECPSTR_CHUNK *ccp)
{
	int		rs = SR_OK ;
	int		rs1 ;

	if (ccp->tab != NULL) {
	    rs1 = uc_free(ccp->tab) ;
	    if (rs >= 0) rs = rs1 ;
	    ccp->tab = NULL ;
	}

	ccp->tabsize = 0 ;
	return rs ;
}
/* end subroutine (chunk_finish) */


static int chunk_check(VECPSTR_CHUNK *ccp,int amount)
{
#if	CF_DEBUGS
	debugprintf("vecpstr/chunk_check: amount=%d\n",amount) ;
	debugprintf("vecpstr/chunk_check: rem=%d\n",
		(ccp->tabsize - ccp->tablen)) ;
#endif
	return (amount > (ccp->tabsize - ccp->tablen)) ;
}
/* end subroutine (chunk_check) */


static int chunk_add(VECPSTR_CHUNK *ccp,cchar *sp,int sl,cchar **rpp)
{
	int		rs = SR_OK ;
	int		amount = (sl + 1) ;

#if	CF_DEBUGS
	debugprintf("vecpstr/chunk_add: tabsize=%u\n",ccp->tabsize) ;
	debugprintf("vecpstr/chunk_add: tablen=%u\n",ccp->tablen) ;
	debugprintf("vecpstr/chunk_add: amount=%d\n",amount) ;
	debugprintf("vecpstr/chunk_add: rem=%d\n",
		(ccp->tabsize - ccp->tablen)) ;
	debugprintf("vecpstr/chunk_add: s=%t\n",
		sp,strlinelen(sp,sl,50)) ;
#endif

	if (amount <= (ccp->tabsize - ccp->tablen)) {
	    char	*bp = (ccp->tab + ccp->tablen) ;
	    strwcpy(bp,sp,sl) ;
	    ccp->tablen += amount ;
	    ccp->count += 1 ;
	    *rpp = bp ;
	} else {
	    rs = SR_BUGCHECK ;
	}

	return rs ;
}
/* end subroutine (chunk_add) */


static int chunk_addkeyval(VECPSTR_CHUNK *ccp,cchar *kp,int kl,
		cchar *vp,int vl,cchar **rpp)
{
	const int	amount = (kl+1+vl+1) ;
	int		rs = SR_OK ;

	if (amount <= (ccp->tabsize - ccp->tablen)) {
	    char	*bp = (ccp->tab + ccp->tablen) ;
	    bp = strwcpy(bp,kp,kl) ;
	    *bp++ = '=' ;
	    if (vp != NULL) {
	        strwcpy(bp,vp,vl) ;
	    } else {
		*bp++ = '\0' ;
	    }
	    ccp->tablen += amount ;
	    ccp->count += 1 ;
	    *rpp = bp ;
	} else {
	    rs = SR_BUGCHECK ;
	}

	return rs ;
}
/* end subroutine (chunk_addeyval) */


static int indexlen(int n)
{
	int		il = nextpowtwo(n) ;
	return il ;
}
/* end subroutine (indexlen) */


static int indexsize(int il)
{
	int		isize = ((il + 1) * 3 * sizeof(int)) ;
	return isize ;
}
/* end subroutine (indexsize) */


static int vcmpdef(cchar **e1pp,cchar **e2pp)
{
	int		rc = 0 ;
	if ((*e1pp != NULL) || (*e2pp != NULL)) {
	    if (*e1pp != NULL) {
	        if (*e2pp != NULL) {
	            rc = strcmp(*e1pp,*e2pp) ;
	        } else
	            rc = -1 ;
	    } else
	        rc = 1 ;
	}
	return rc ;
}
/* end subroutine (vcmpdef) */


