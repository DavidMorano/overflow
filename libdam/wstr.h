/* wstr INCLUDE */


/* revision history:

	= 2018-1127, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.
	
*/

/* Copyright © 2018 David A­D­ Morano.  All rights reserved. */

#ifndef	WSTR_INCLUDE
#define	WSTR_INCLUDE	1


#include	<envstandards.h>	/* must be first to configure */
#include	<sys/types.h>
#include	<stddef.h>		/* for 'wchar_t' */
#include	<localmisc.h>		/* for extra unsigned types */


#ifdef	__cplusplus
extern "C" {
#endif

extern int wslen(wchar_t *) ;
extern int wsnlen(wchar_t *,int) ;
extern int wsncols(wchar_t *,int) ;
extern int wsnwcpynarrow(wchar_t *,int,char *,int) ;

extern int wsfnext(wchar_t *,int) ;

extern int wsinul(wchar_t *,int) ;
extern int wsichar(wchar_t *,int) ;
extern int wsirchar(wchar_t *,int) ;

#ifdef	__cplusplus
}
#endif

#endif /* WSTR_INCLUDE	*/

