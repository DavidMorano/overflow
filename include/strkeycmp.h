/* strkeycmp HEADER */
/* lang=C++20 */

/* make a character out of an integer */
/* version %I% last-modified %G% */


/* revision history:

  = 2000-05-14, David A-D- Morano
	This was written for Rightcore Network Services (RNS).
 
  = 2018-11-27, David A-D- Morano
  I created an inline version for the C language. We will likely do
  something for C++ at some other time.
  
*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	STRKEYCMP_INCLUDE
#define	STRKEYCMP_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<utypedefs.h>
#include	<clanguage.h>


EXTERNC_begin

extern int strkeycmp(cchar *,cchar *) noex ;
extern int strnkeycmp(cchar *,cchar *,int) noex ;

EXTERNC_end


#endif /* STRKEYCMP_INCLUDE */


