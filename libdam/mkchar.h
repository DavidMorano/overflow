/* mkchar INCLUDE */

/* make a character out of an integer */


/* revision history:

  = 2000-05-14, David A­D­ Morano
	This was written for Rightcore Network Services (RNS).
 
  = 2018-11-27, David A.D. Morano
  I created an inline version for the C language. We will likely do
  something for C++ at some other time.
  
*/

/* Copyright © 1998,2018 David A­D­ Morano.  All rights reserved. */

#ifndef	MKCHAR_INCLUDE
#define	MKCHAR_INCLUDE	1


#include	<envstandards.h>	/* MUST be first to configure */


#if	(! defined(MKCHAR_MASTER)) || (MKCHAR_MASTER == 0)

#ifdef	__cplusplus
extern "C" int mkchar(int) ;
#else
inline int mkchar(int ch)
{
	return (ch & 255) ;
}
/* end subroutine (mkchar) */
#endif /* _cplusplus */

#endif /* MKCHAR_MASTER */

#endif /* MKCHAR_INCLUDE */

