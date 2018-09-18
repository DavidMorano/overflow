/* openshmtmp */

/* open a temproary file in shared memory (really private) */
/* last modified %G% version %I% */


#define	CF_DEBUGS	0		/* compile-time debugging */
#define	CF_DEBUGN	0		/* special debugging */


/* revision history:

	= 1998-07-10, David A­D­ Morano
	This subroutine was originally written.

	= 2018-09-13, David A.D. Morano
	Changed the construction of random numbers from using just seconds to
	instead using both seconds and microseconds. We did this by replacing a
	a call to |time(2)| with |gettimeofday(3c)|.
	
*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	This subroutine creates and opens a POSIX® shared-memory temporary
	object.  If a non-NULL result buffer is supplied by the caller,
	then the POSIX® SHM-type name of the object created is returned to
	the caller in that result buffer, and the associated SHM object remains
	available for future access by the name.  If a NULL result buffer is 
	supplied, then the SHM object name that is created is deleted from 
	further possible access, but the SHM object itself remains open 
	(captured by the returned FD).

	Synopsis:

	int openshmtmp(rbuf,rlen,operm)
	char		rbuf[] ;
	int		rlen ;
	mode_t		operm ;

	Arguments:

	rbuf		suppled buffer to receive the resulting SHM name
	rlen		length of suppled buffer; should be at least SHMNAMELEN
	operm		SHM object creation opermissions

	Returns:

	>=0		file descriptor to program STDIN and STDOUT
	<0		error

	Notes on SHM object names:
	The resulting SHM object names (whether returned or deleted) take the
	form of:
		/tmpXXXXXXXXXX
	where the X's represent hexadeciaml digits. Since ten hexadecial digits
	are used, we use a random ULONG (64-bit integer) value to create them.
	The resulting name is 14 characters long and meets the most restrictive
	POSIX requirements for POSIX SHM named objects.


*******************************************************************************/


#include	<envstandards.h>	/* MUST be first to configure */

#include	<sys/types.h>
#include	<sys/param.h>
#include	<sys/time.h>		/* for |gettimeofday(3c)| */
#include	<unistd.h>
#include	<fcntl.h>
#include	<time.h>
#include	<stdlib.h>
#include	<string.h>

#include	<vsystem.h>
#include	<ugetpid.h>
#include	<cthex.h>
#include	<sigblock.h>
#include	<localmisc.h>


/* local defines */

#ifndef	SHMNAMELEN
#define	SHMNAMELEN	MAXNAMELEN
#endif

#define	EBUFLEN		(2*sizeof(ULONG)) /* buffer for int64_t in HEX */

#define	NTRIES		1000

#define	NDF		"openshmtmp.deb"


/* external subroutines */

extern int	sncpy2(char *,int,const char *,const char *) ;
extern int	sncpy3(char *,int,const char *,const char *,const char *) ;
extern int	mkpath2(char *,const char *,const char *) ;

#if	CF_DEBUGN
extern int	nprintf(cchar *,cchar *,...) ;
#endif


/* external variables */


/* forward reference */

static int	randinit(ULONG *) ;
static int	mkshmname(char *,int,ULONG) ;


/* local variables */


/* exported subroutines */


int openshmtmp(char *rbuf,int rlen,mode_t om)
{
	int		rs = SR_OK ;
	int		rs1 ;
	int		fd_shm = -1 ;
	int		f_bufalloc = FALSE ;

	if ((rbuf != NULL) && (rlen >= 0) && (rlen < SHMNAMELEN))
	    return SR_OVERFLOW ;

#if	CF_DEBUGN
	nprintf(NDF,"openshmtmp: ent\n") ;
	if (rbuf != NULL) {
	    nprintf(NDF,"openshmtmp: rbuf=%s\n",rbuf) ;
	}
#endif

	if (rbuf == NULL) {
	    rlen = (SHMNAMELEN + 1) ;
	    if ((rs = uc_malloc(rlen,&rbuf)) >= 0) {
	    	f_bufalloc = TRUE ;
	    }
	}

	if (rs >= 0) {
	    ULONG	rv ;
	    if ((rs = randinit(&rv)) >= 0) {
	        SIGBLOCK	b ;
		rbuf[0] = '\0' ;
	        if ((rs = sigblock_start(&b,NULL)) >= 0) {
	            const int	of = (O_CREAT | O_EXCL | O_RDWR) ;
	            const int	ntries = NTRIES ;
		    int		i ;

	            for (i = 0 ; i < ntries ; i += 1) {
	                if ((rs = mkshmname(rbuf,rlen,rv++)) >= 0) {
	                    rs = uc_openshm(rbuf,of,om) ;
	                    fd_shm = rs ;
	                }
		        if (rs != SR_EXISTS) break ;
	            } /* end for */

#if	CF_DEBUGN
		    nprintf(NDF,"openshmtmp: loop-out rs=%d\n",rs) ;
#endif

	            if ((rs >= 0) && f_bufalloc) {
		        uc_unlinkshm(rbuf) ;
			rbuf[0] = '\0' ;
	 	    }

	            rs1 = sigblock_finish(&b) ;
		    if (rs >= 0) rs = rs1 ;
	        } /* end if (sigblock) */
		if ((rs < 0) && (fd_shm >= 0) && (rbuf[0] != '\0')) {
		    uc_unlinkshm(rbuf) ;
		    rbuf[0] = '\0' ;
		}
	    } /* end if (randinit) */
	} /* end if (ok) */

	if (f_bufalloc && (rbuf != NULL)) {
	    rs1 = uc_free(rbuf) ;
	    if (rs >= 0) rs = rs1 ;
	} /* end if (buffer was not supplied by the caller) */

	if ((rs < 0) && (fd_shm >= 0)) {
	    u_closse(fd_shm) ;
	}

#if	CF_DEBUGN
	nprintf(NDF,"openshmtmp: ret rs=%d fd=%d\n",rs,fd_shm) ;
#endif

	return (rs >= 0) ? fd_shm : rs ;
}
/* end subroutine (openshmtmp) */


/* local subroutines */


static int randinit(ULONG *rvp)
{
	struct timeval	now ;
	ULONG		rv = 0 ;
	int		rs ;
	if ((rs = uc_gettimeofday(&now,NULL)) >= 0) {
	    ULONG	sv ;
	    const pid_t	pid = ugetpid() ;
	    sv = (ULONG) now.tv_sec ;
	    rv += (sv << 8) ;
	    sv = (ULONG) now.tv_usec ;
	    rv += sv ;
	    sv = (ULONG) pid ;
	    rv += sv ;
	}
	*rvp = rv ;
	return rs ;
}
/* end subroutine (randinit) */


static int mkshmname(char *rbuf,int rlen,ULONG rv)
{
	const int	elen = EBUFLEN ;
	int		rs ;
	char		ebuf[EBUFLEN+1] ;

	if ((rs = cthexull(ebuf,elen,rv)) >= 0) {
	    int	i = (rs >= 10) ? (rs-10) : 0 ;
	    rs = sncpy2(rbuf,rlen,"/tmp",(ebuf+i)) ;
	}

	return rs ;
}
/* end subroutine (mkshmname) */

