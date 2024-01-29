/* nleadkeystr HEADER */
/* lang=C20 */

/* match on the leading part of a string */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright (c) 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	NLEADKEYSTR_INCLUDE
#define	NLEADKEYSTR_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<utypedefs.h>
#include	<clanguage.h>


EXTERNC_begin

extern int nleadkeystr(cchar *,cchar *,int) noex ;

EXTERNC_end


#endif /* NLEADKEYSTR_INCLUDE */


