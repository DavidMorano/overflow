/* wstr INCLUDE */


/* revision history:

	= 2018-11-27, David A­D­ Morano
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

extern int wslen(const wchar_t *) ;
extern int wsnlen(const wchar_t *,int) ;
extern int wsncols(const wchar_t *,int) ;

extern int wsfnext(const wchar_t *,int,const wchar_t **) ;

extern int wsinul(const wchar_t *,int) ;
extern int wsichar(const wchar_t *,int) ;
extern int wsirchar(const wchar_t *,int) ;

extern int wsnwcpynarrow(wchar_t *,int,const char *,int) ;

#ifdef	__cplusplus
}
#endif

#endif /* WSTR_INCLUDE	*/

