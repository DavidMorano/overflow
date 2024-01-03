/* toxc HEADER */
/* lang=C20 */

/* convert a single character to a given case */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-10, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright (c) 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	TOXC_INCLUDE
#define	TOXC_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<utypedefs.h>
#include	<clanguage.h>
#include	<char.h>


#ifdef	__cplusplus

inline int tobc(int ch) noex {
	return ch ;
}
inline int tolc(int ch) noex {
	return CHAR_TOLC(ch) ;
}
inline int touc(int ch) noex {
	return CHAR_TOUC(ch) ;
}
inline int tofc(int ch) noex {
	return CHAR_TOFC(ch) ;
}

#else /* __cplusplus */
#define	TOXC_STATICINLINE

static inline int tobc(int ch) noex {
	return ch ;
}
static inline int tolc(int ch) noex {
	return CHAR_TOLC(ch) ;
}
static inline int touc(int ch) noex {
	return CHAR_TOUC(ch) ;
}
static inline int tofc(int ch) noex {
	return CHAR_TOFC(ch) ;
}

#endif /* __cplusplus */


#endif /* TOXC_INCLUDE */


