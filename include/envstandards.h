/* envstandards (Darwin) */


/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

	= 2023-10-09, David A­D­ Morano
	I had to experiment with the preprocessor define named 
	'_XOPEN_SOURCE' in order to get a reasonably working 
	system.  See below.

*/

/* Copyright © 2000,2023 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	This file is included in pretty much all other user-created
	header files.  The reason is so that the name, type, and
	version of the operating system (made available through
	some C-C++ pre-processor defines) and some compilation
	options (also made available through some C-C++ pre-processor
	defines) can be made available to user code.

*******************************************************************************/

/* these are user-settable compile-time switches */

#ifndef	ENVSTANDARDS_INCLUDE
#define	ENVSTANDARDS_INCLUDE

/* general operating-system definitions */

#ifndef	OSNAME
#define	OSNAME				Darwin
#endif

#ifndef	OSNAME_Darwin
#define	OSNAME_Darwin			19
#endif

#ifndef	OSNUM
#define	OSNUM				19
#endif

#ifndef	OSTYPE_SYSV
#define	OSTYPE_SYSV			0
#endif

/* compilation environment definitions */

/* POSIX phread semantics (where differ from non-pthread usage) */
#define	_POSIX_PTHREAD_SEMANTICS	1

/****
On (messed-up) Darwin OS, one must define the preprocessor symbol
'_ANSI_SOURCE' in order to get the declaration for the kernel
subroutine |waitid(2)|.  But if we do so (on messed-up Darwin)
we get all hell breaking loose with many other declarions being
missing (for whatever messed-up reason). So we instead are
careful top NOT define that preprocessior sysmbol. 
Long live the messed-up Darwin OS!
Oh, and thanks so much for making me take hours to figure out
how this messed-up envronment works on Darwin.
****/

#ifdef	COMMENT /* messed-up brain-damaged Darwin */
#ifndef _ANSI_SOURCE
#define	_ANSI_SOURCE
#endif
#endif

/****
On (the messed-up) Darwin OS, if we define the preprocessor symbol
'_XOPEN_SOURCE' to anything at all (rather than a blank definition)
we get all hell breaking loose with many other declarions being
missing (for whatever messed-up reaoson). So we instead are
careful to NOT define with any sort of value.
Long live the messed-up Darwin OS!
Oh, and thanks so much for making me take hours to figure out
how this messed-up system works on Darwin.
****/

#ifdef	COMMENT /* messed-up brain-damaged Darwin */
#ifndef	_XOPEN_SOURCE
#define	_XOPEN_SOURCE			500
#endif
#endif /* COMMENT */

#ifndef	_XOPEN_SOURCE
#define	_XOPEN_SOURCE
#endif

#ifndef	_DARWIN_C_SOURCE
#define	_DARWIN_C_SOURCE
#endif

#ifndef	_REENTRANT
#define	_REENTRANT
#endif

/* operating system capabilities */

#include	<syshas.h>


#endif /* ENVSTANDARDS_INCLUDE */


