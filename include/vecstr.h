/* vecstr HEADER */
/* lang=C20 */

/* vector-string container (Vector-String) */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-02-01, David A­D­ Morano
	This subroutine was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	This object implements a vector of strings. This are C-styled strings
	(of course, and as it should be).


*******************************************************************************/

#ifndef	VECSTR_INCLUDE
#define	VECSTR_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>
#include	<utypedefs.h>
#include	<clanguage.h>
#include	<localmisc.h>


/* object defines */

#define	VECSTR			struct vecstr_head
#define	VECSTR_FL		struct vecstr_flags
#define	VECSTR_DEFENTS		5

/* options */

#define	VECSTR_ODEFAULT		0
#define	VECSTR_OREUSE		(1 << 0)	/* reuse empty slots */
#define	VECSTR_OCOMPACT		(1 << 1)	/* means NOHOLES */
#define	VECSTR_OSWAP		(1 << 2)	/* use swapping */
#define	VECSTR_OSTATIONARY	(1 << 3)	/* entries should not move */
#define	VECSTR_OCONSERVE	(1 << 4)	/* conserve space */
#define	VECSTR_OSORTED		(1 << 5)	/* keep sorted */
#define	VECSTR_OORDERED		(1 << 6)	/* keep ordered */


struct vecstr_flags {
	uint		issorted:1 ;
	uint		oreuse:1 ;
	uint		onoholes:1 ;
	uint		oswap:1 ;
	uint		ostationary:1 ;
	uint		ocompact:1 ;
	uint		osorted:1 ;
	uint		oordered:1 ;
	uint		oconserve:1 ;
	uint		stsize:1 ;		/* not option (just flag) */
} ; /* end struct (vecstr_flags) */

struct vecstr_head {
	cchar		**va ;
	VECSTR_FL	f ;
	int		c ;		/* count of items in list */
	int		i ;		/* overlast index */
	int		n ;		/* current extent of array */
	int		fi ;		/* free index */
	int		stsize ;	/* total string-table length */
} ; /* end struct (vecstr_head) */

#ifdef	__cplusplus
enum vecstrmems {
	vecstrmem_count,
	vecstrmem_delall,
	vecstrmem_strsize,
	vecstrmem_recsize,
	vecstrmem_audit,
	vecstrmem_finish,
	vecstrmem_overlast
} ;
struct vecstr_iter {
	cchar		**va = nullptr ;
	int		i = -1 ;
	int		ii = -1 ;
	vecstr_iter() = default ;
	vecstr_iter(cchar **ov,int oi,int oii) noex : va(ov), i(oi) {
	    ii = oii ;
	} ;
	vecstr_iter(const vecstr_iter &oit) noex {
	    if (this != &oit) {
		va = oit.va ;
		i = oit.i ;
		ii = oit.ii ;
	    }
	} ;
	vecstr_iter &operator = (const vecstr_iter &oit) noex {
	    if (this != &oit) {
		va = oit.va ;
		i = oit.i ;
		ii = oit.ii ;
	    }
	    return *this ;
	} ;
	bool operator != (const vecstr_iter &) noex ;
	bool operator == (const vecstr_iter &) noex ;
	cchar *operator * () noex {
	    cchar	*rp = nullptr ;
	    if (i < ii) rp = va[i] ;
	    return rp ;
	} ;
	vecstr_iter operator + (int) const noex ;
	vecstr_iter operator += (int) noex ;
	vecstr_iter operator ++ () noex ; /* pre */
	vecstr_iter operator ++ (int) noex ; /* post */
	void increment(int = 1) noex ;
} ; /* end struct vecstr_iter) */
struct vecstr ;
struct vecstr_co {
	vecstr		*op = nullptr ;
	int		w = -1 ;
	void operator () (vecstr *p,int m) noex {
	    op = p ;
	    w = m ;
	} ;
	operator int () noex ;
	int operator () () noex { 
	    return operator int () ;
	} ;
} ; /* end struct (vecstr_co) */
struct vecstr : vecstr_head {
	vecstr_co	count ;
	vecstr_co	delall ;
	vecstr_co	strsize ;
	vecstr_co	recsize ;
	vecstr_co	audit ;
	vecstr_co	finish ;
	vecstr() noex {
	    count(this,vecstrmem_count) ;
	    delall(this,vecstrmem_delall) ;
	    strsize(this,vecstrmem_strsize) ;
	    recsize(this,vecstrmem_recsize) ;
	    audit(this,vecstrmem_audit) ;
	    finish(this,vecstrmem_finish) ;
	} ;
	vecstr(const vecstr &) = delete ;
	vecstr &operator = (const vecstr &) = delete ;
	int start(int = 0,int = 0) noex ;
	int add(cchar *,int = -1) noex ;
	int adduniq(cchar *,int = -1) noex ;
	int insert(int,cchar *,int = -1) noex ;
	int del(int = -1) noex ;
	vecstr_iter begin() noex {
	    vecstr_iter		it(va,0,i) ;
	    return it ;
	} ;
	vecstr_iter end() noex {
	    vecstr_iter		it(va,i,i) ;
	    return it ;
	} ;
	void dtor() noex ;
	~vecstr() noex {
	    dtor() ;
	} ;
} ; /* end struct (vecstr) */
#else	/* __cplusplus */
typedef struct vecstr_head	vecstr ;
#endif /* __cplusplus */

#ifdef	__cplusplus
extern "C" {
#endif

typedef int (*vecstr_vcmp)(cchar **,cchar **) noex ;

extern int vecstr_start(vecstr *,int,int) noex ;
extern int vecstr_add(vecstr *,cchar *,int) noex ;
extern int vecstr_adduniq(vecstr *,cchar *,int) noex ;
extern int vecstr_addkeyval(vecstr *,cchar *,int,cchar *,int) noex ;
extern int vecstr_insert(vecstr *,int,cchar *,int) noex ;
extern int vecstr_store(vecstr *,cchar *,int,cchar **) noex ;
extern int vecstr_get(vecstr *,int,cchar **) noex ;
extern int vecstr_getlast(vecstr *,cchar **) noex ;
extern int vecstr_del(vecstr *,int) noex ;
extern int vecstr_delall(vecstr *) noex ;
extern int vecstr_count(vecstr *) noex ;
extern int vecstr_sort(vecstr *,vecstr_vcmp) noex ;
extern int vecstr_search(vecstr *,cchar *,vecstr_vcmp,cchar **) noex ;
extern int vecstr_searchl(vecstr *,cchar *,int,vecstr_vcmp,cchar **) noex ;
extern int vecstr_find(vecstr *,cchar *) noex ;
extern int vecstr_findn(vecstr *,cchar *,int) noex ;
extern int vecstr_finder(vecstr *,cchar *,vecstr_vcmp,cchar **) noex ;
extern int vecstr_findaddr(vecstr *,cchar *) noex ;
extern int vecstr_getvec(vecstr *,cchar ***) noex ;
extern int vecstr_strsize(vecstr *) noex ;
extern int vecstr_strmk(vecstr *,char *,int) noex ;
extern int vecstr_recsize(vecstr *) noex ;
extern int vecstr_recmk(vecstr *,int *,int) noex ;
extern int vecstr_recmkstr(vecstr *,int *,int,char *,int) noex ;
extern int vecstr_audit(vecstr *) noex ;
extern int vecstr_finish(vecstr *) noex ;

#ifdef	__cplusplus
}
#endif


#endif /* VECSTR_INCLUDE */


