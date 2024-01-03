/* matkeystr HEADER */
/* lang=C++20 */

/* match the key part of a string */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright (c) 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	MATKEYSTR_INCLUDE
#define	MATKEYSTR_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<utypedefs.h>
#include	<clanguage.h>
#include	<localmisc.h>


#ifndef	TYPEDEF_MAINV
#define	TYPEDEF_MAINV
typedef const char *const	*mainv ;
#endif


#ifdef	__cplusplus
extern "C" {
#endif

extern int matkeystr(mainv,cchar *,int) noex ;

#ifdef	__cplusplus
}
#endif /* __cplusplus */


#endif /* MATKEYSTR_INCLUDE */


