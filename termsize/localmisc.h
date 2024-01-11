/* localmisc HEADER */
/* lang=C20 */

/* miscellaneous stuff which essentially every program wants! */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-02-15, David A­D­ Morano
	This code was started to make life easier on the outside (outside of
	Lucent Technologies).  This file largely contains those things
	(defines) that I have found to be either useful or problematic in the
	past.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	LOCALMISC_INCLUDE
#define	LOCALMISC_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>
#include	<sys/param.h>
#include	<sys/socket.h>
#include	<netinet/in.h>
#include	<limits.h>
#include	<clanguage.h>



#ifndef	TRUE
#define	TRUE		1
#endif

#ifndef	FALSE
#define	FALSE		0
#endif

#ifndef	YES
#define	YES		1
#endif

#ifndef	NO
#define	NO		0
#endif

#ifndef	OK
#define	OK		0
#endif

#ifndef	BAD
#define	BAD		-1
#endif


#ifndef	MIN
#define	MIN(a,b)	(((a) < (b)) ? (a) : (b))
#endif

#ifndef	MAX
#define	MAX(a,b)	(((a) > (b)) ? (a) : (b))
#endif

#ifndef	UMIN
#define	UMIN(a,b)	((((unsigned long) (a)) < ((unsigned long) (b))) \
				 ? (a) : (b))
#endif

#ifndef	UMAX
#define	UMAX(a,b)	((((unsigned long) (a)) > ((unsigned long) (b))) \
				? (a) : (b))
#endif

#ifndef	ABS
#define	ABS(a)		(((a) < 0) ? (- (a)) : (a))
#endif

#ifndef	LEQUIV /* should be operator » !^^ « */
#define	LEQUIV(a,b)	(((a) && (b)) || ((! (a)) && (! (b))))
#endif

#ifndef	LXOR /* should be operator » ^^ « */
#define	LXOR(a,b)	(((a) && (! (b))) || ((! (a)) && (b)))
#endif

#ifndef	BFLOOR
#define	BFLOOR(v,m)	((v) & (~ ((m) - 1)))
#endif

#ifndef	BCEIL
#define	BCEIL(v,m)	(((v) + ((m) - 1)) & (~ ((m) - 1)))
#endif

#ifndef	CEILINT
#define	CEILINT(v)	BCEIL((v),sizeof(int))
#endif

#ifndef	CMSG_SPACE
#define	CMSG_SPACE(len)	(CEILINT(sizeof(struct cmsghdr)) + CEILINT(len))
#endif

#ifndef	CMSG_LEN
#define	CMSG_LEN(len)	(CEILINT(sizeof(struct cmsghdr)) + (len))
#endif

#ifndef	MKCHAR
#define	MKCHAR(ch)	((ch) & 0xff)
#endif

#ifndef	MKBOOL
#define	MKBOOL(ch)	((ch)!=0)
#endif

#ifndef	UC
#define	UC(ch)		((unsigned char) (ch))
#endif


/* basic scalar types */

#ifndef	LONG
#define	LONG		long
#endif

#ifndef	SCHAR
#define	SCHAR		signed char
#endif

#ifndef	UCHAR
#define	UCHAR		unsigned char
#endif

#ifndef	USHORT
#define	USHORT		unsigned short
#endif

#ifndef	UINT
#define	UINT		unsigned int
#endif

#ifndef	ULONG
#define	ULONG		unsigned long
#endif

#ifndef	TYPEDEF_SCHAR
#define	TYPEDEF_SCHAR
typedef signed char		schar ;
#endif /* TYPEDEF_SCHAR */

#ifndef	TYPEDEF_CSCHAR
#define	TYPEDEF_CSCHAR
typedef const signed char	cschar ;
#endif /* TYPEDEF_SCHAR */

#ifndef	TYPEDEF_UCHAR
#define	TYPEDEF_UCHAR
typedef unsigned char		uchar ;
#endif /* TYPEDEF_UCHAR */

#ifndef	TYPEDEF_CUCHAR
#define	TYPEDEF_CUCHAR
typedef const unsigned char	cuchar ;
#endif /* TYPEDEF_UCHAR */

#ifndef	TYPEDEF_CSHORT
#define	TYPEDEF_CSHORT
typedef const short		cshort ;
#endif /* TYPEDEF_CSHORT */

#ifndef	TYPEDEF_CINT
#define	TYPEDEF_CINT
typedef const int		cint ;
#endif /* TYPEDEF_CINT */

#ifndef	TYPEDEF_CLONG
#define	TYPEDEF_CLONG
typedef const long		clong ;
#endif /* TYPEDEF_CLONG */

#ifndef	TYPEDEF_CUINT
#define	TYPEDEF_CUINT
typedef const unsigned int	cuint ;
#endif /* TYPEDEF_CUINT */


#ifndef	TYPEDEF_USTIME
#define	TYPEDEF_USTIME
typedef unsigned int		ustime_t ;
#endif

#ifndef	TYPEDEF_UTIME
#define	TYPEDEF_UTIME
#if	defined(_LP64)
typedef unsigned long		utime_t ;
#else
typedef unsigned long long	utime_t ;
#endif
#endif /* TYPEDEF_UTIME */

#ifndef	TYPEDEF_UNIXTIME
#define	TYPEDEF_UNIXTIME
#if	defined(_LP64)
typedef long			unixtime_t ;
#else
typedef long long		unixtime_t ;
#endif
#endif /* TYPEDEF_UNIXTIME */

#ifndef	TYPEDEF_CC
#define	TYPEDEF_CC
typedef const char	cc ;
#endif

/* C-language limits */

#ifndef	INT64_MIN
#define	INT64_MIN	(-9223372036854775807L-1LL)
#endif

#ifndef	INT64_MAX
#define	INT64_MAX	9223372036854775807LL
#endif

#ifndef	UINT64_MAX
#define	UINT64_MAX	18446744073709551615ULL
#endif

/* it would be nice if the implemenation had these */

#ifndef	SHORT_MIN
#ifdef	SHRT_MIN
#define	SHORT_MIN	SHRT_MIN
#else
#define	SHORT_MIN	(-32768)	/* min value of a "short int" */
#endif
#endif

#ifndef	SHORT_MAX
#ifdef	SHRT_MAX
#define	SHORT_MAX	SHRT_MAX
#else
#define	SHORT_MAX	32767		/* max value of a "short int" */
#endif
#endif

#ifndef	USHORT_MAX
#ifdef	USHRT_MAX
#define	USHORT_MAX	USHRT_MAX
#else
#define	USHORT_MAX	65535		/* max value of "unsigned short int" */
#endif
#endif


/* parameters */

#ifndef	MAXPATHLEN
#ifdef	PATH_MAX
#define	MAXPATHLEN	PATH_MAX
#else
#define	MAXPATHLEN	1024
#endif
#endif

#ifndef	MAXNAMELEN
#ifdef	NAME_MAX
#define	MAXNAMELEN	NAME_MAX
#else
#define	MAXNAMELEN	256
#endif
#endif

#ifndef	MAXLINELEN
#ifdef	LINE_MAX
#define	MAXLINELEN	LINE_MAX
#else
#define	MAXLINELEN	(2*1024)
#endif
#endif

#ifndef	NODENAMELEN
#define	NODENAMELEN	256
#endif

#ifndef	HOSTNAMELEN
#define	HOSTNAMELEN	1024
#endif

#ifndef	MSGBUFLEN
#define	MSGBUFLEN	2048
#endif

/* timezone (zoneinfo) name */
#ifndef	TZNAMELEN
#define	TZNAMELEN	32
#endif

/* timezone abbreviation */
#ifndef	ZNAMELEN
#define	ZNAMELEN	8
#endif

/* timezone abbreviation */
#ifndef	TZABBRLEN
#define	TZABBRLEN	8
#endif

/* log-ID (for logging) */
#ifndef	LOGIDLEN
#define	LOGIDLEN	15
#endif

/* mail address */
#ifndef	MAILADDRLEN
#define	MAILADDRLEN	(3 * MAXHOSTNAMELEN)
#endif

#ifndef	DIGBUFLEN
#define	DIGBUFLEN	80		/* can hold |int256_t| in decimal */
#endif

#ifndef	HEXBUFLEN
#define	HEXBUFLEN	64		/* can hold |int256_t| in hexadecimal */
#endif

#ifndef	REALNAMELEN
#define	REALNAMELEN	100
#endif

#ifndef	TIMEBUFLEN
#define	TIMEBUFLEN	80
#endif

#ifndef	COLUMNS
#define	COLUMNS		80
#endif

#ifndef	NOFILE
#define	NOFILE		20
#endif

#ifndef	NULLFNAME
#define	NULLFNAME	"/dev/null"
#endif

#ifndef	POLLINTMULT
#define	POLLINTMULT	1000		/* poll-time multiplier */
#endif


#define	eol		'\n'


#endif /* LOCALMISC_INCLUDE */


