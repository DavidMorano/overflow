/* utimeotdefs HEADER */
/* lang=C20 */

/* manage UNIX® kernal-call (and std-c library) timeouts */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

	= 2023-10-23, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998,2023 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Timeout values for various UNIX system and UNX C-library
	services are initialized early (as early as possible from
	module-load time) with the default values below.  All timeout
	values are in seconds. These values can be changed at
	run-time (repeatedly if desired) for those processes that
	really know what they are doing. One limitation on what can
	be achieved with the present initialization problem is that
	we want the array of timeout values to be accessible to the
	C-language as a normal array of inrger values. This requirement
	is for legacy reasons since much of both the kernel calls
	and C-language (std-c library) calls are written in the
	C-language (and not in C++).  This means that these values
	cannot be located within a non-POD *class* structure of the
	C++ language.

	Notes:
	1. Due to initialization limitations (in both the C and C++
	lanmaguags) I had to use the facilities of each language
	(C and C++) to the best of what they each offer. Sadly,
	only assembly language would provide the type of initialization
	that I really want, but I do not really want to go there
	in this day-and-age like I would have almost twenty years
	ago.  I use the C-language to establish the initial values
	of the system timeouts with the values below. And then I
	used the C++ language to establish another detfault value
	for those timeout values that are not set by the defaults
	below.
	2. This is an update (for this very note documentation here)
	for 2023. I have been investigating using some new features
	of C++20 for initialization purposes.  There are some
	improvements to what C++20 can do in terms of intialization,
	but it is not enough (like what assembly-language would
	offer). Because the timeout values (held in an array of
	integers) needs to be a global located in the static-data
	memory segment, C++20 does not help us with any more clever
	initialization than we had at the beginning of this particular
	saga (back in 1098). So there are no code changes to any
	of these related subroutines for 2023 (as one might have
	expected there would be due to C++20 coming into vogue).

*******************************************************************************/

#ifndef	UTIMEOUTDEFS_INCLUDE
#define	UTIMEOUTDEFS_INCLUDE


/* all time-intervals below are in seconds */

#define	UTO_AGAIN	10
#define	UTO_INTR	(10 * 60)
#define	UTO_NOMEM	(5 * 60)
#define	UTO_BUSY	5
#define	UTO_GET		3
#define	UTO_DEADLOCK	50
#define	UTO_IO		60
#define	UTO_DQUOT	(5 * 60)
#define	UTO_NOSPC	(5 * 60)
#define	UTO_DIAL	30
#define	UTO_OPEN	10
#define	UTO_READ	(1*60)
#define	UTO_MFILE	5
#define	UTO_NFILE	5
#define	UTO_NOSR	(5 * 60)
#define	UTO_POLL	10
#define	UTO_NOLCK	10
#define	UTO_CAPURE	5

#define	UTO_DEFAULT	(5*60)


#endif /* UTIMEOUTDEFS_INCLUDE */


