/* usysdefs INCLUDE */
/* lang=C20 */

/* define the various system buffer sizes */
/* version %I% last-modified %G% */


/* revision history:

	= 2001-04-11, David D-A- Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 2001 David D-A- Morano.  All rights reserved. */

/*******************************************************************************

	Description:
	This file defines various preprocessor variables for use
	in setting up the UNIX®-system default for various buffer
	sizes.  The real run-time system buffer sizes are (indeed)
	determined at runtime where they may exist.

	Usage:
	Among the most important uses for the data contained herein
	is the BUFSIZE management facility. It uses the data below
	to set default buffer sizes for those systems that do not 
	have dynamicly managed buffer size support in the system kernel.

*******************************************************************************/

#ifndef	USYSDEFS_INCLUDE
#define	USYSDEFS_INCLUDE


#include	<envstandards.h>
#include	<sys/types.h>
#include	<sys/utsname.h>
#include	<limits.h>
#include	<unistd.h>
#include	<unistd.h>
#include	<pwd.h>
#if	defined(SYSHAS_SHADOW) && (SYSHAS_SHADOW > 0)
#include	<shadow.h>
#endif


#ifndef	SIZE_MAX
#define	SIZE_MAX	ULONG_MAX
#endif

#ifndef	SSIZE_MAX
#define	SSIZE_MAX	LONG_MAX
#endif

/* arguments (and environment) */
#ifndef	ARBUFLEN
#ifdef	ARG_MAX
#define	ARBUFLEN	ARG_MAX
#else
#define	ARBUFLEN	(2*1024*1024)	/* default for many systems */
#endif
#endif

/* max-name */
#ifndef	MNBUFLEN
#ifdef	NAME_LEN
#define	MNBUFLEN	NAME_LEN
#else
#define	MNBUFLEN	(1*1024)
#endif
#endif

/* max-path */
#ifndef	MPBUFLEN
#ifdef	MAXPATHLEN
#define	MPBUFLEN	MAXPATHLEN
#else
#define	MPBUFLEN	(4*1024)
#endif
#endif

/* max-line */
#ifndef	MLBUFLEN
#define	MLBUFLEN	(2*2048)
#endif

/* node-name */
#ifndef	NNBUFLEN
#ifdef	_POSIX_HOST_NAME_MAX
#define	NNBUFLEN	(_POSIX_HOST_NAME_MAX-1)
#else
#ifdef	SYS_NMLN
#define	NNBUFLEN	(SYS_NMLN-1)
#else
#define	NNBUFLEN	256
#endif
#endif
#endif

/* host-name */
#ifndef	HNBUFLEN
#define	HNBUFLEN	(1*1024)
#endif

/* user-name */
#ifndef	UNBUFLEN
#ifdef	_POSIX_LOGIN_NAME_MAX
#define	UNBUFLEN	_POSIX_LOGIN_NAME_MAX
#else
#define	UNBUFLEN	32
#endif
#endif

/* group-name */
#ifndef	GNBUFLEN
#define	GNBUFLEN	32
#endif

/* project-name */
#ifndef	PNBUFLEN
#define	PNBUFLEN	32
#endif

/* password entry */
#ifndef	PWBUFLEN
#ifdef	_SC_GETPW_R_SIZE_MAX
#define	PWBUFLEN	_SC_GETPW_R_SIZE_MAX
#else
#define	PWBUFLEN	1024		/* Solaris® _SC_GETPW_R_SIZE_MAX */
#endif
#endif

/* shadow-password entry */
#ifndef	SPBUFLEN
#define	SPBUFLEN	1024		/* same as PWBUFLEN for now */
#endif

/* user-attribute entry */
#ifndef	UABUFLEN
#define	UABUFLEN	(2*1024)	/* this is just a suggestion */
#endif

/* group entry */
#ifndef	GRBUFLEN
#ifdef	_SC_GETGR_R_SIZE_MAX
#define	GRBUFLEN	_SC_GETGR_R_SIZE_MAX
#else
#define	GRBUFLEN	7296		/* Solaris® _SC_GETGR_R_SIZE_MAX */
#endif
#endif

/* project entry */
#ifndef	PJBUFLEN
#define	PJBUFLEN	(4 * 1024)	/* Solaris® recommends (4*1024) */
#endif

/* protocol entry */
#ifndef	PRBUFLEN
#define	PRBUFLEN	256
#endif

/* network entry */
#ifndef	NWBUFLEN
#define	NWBUFLEN	(4 * 1024)
#endif

/* host entry */
#ifndef	HOBUFLEN
#define	HOBUFLEN	(8 * 1024)
#endif

/* service entry */
#ifndef	SVBUFLEN
#define	SVBUFLEN	256
#endif

/* zone-name (from Zone-Info) */
#ifndef	ZNBUFLEN
#define	ZNBUFLEN	128
#endif

#ifndef	CLUSTERNAMELEN
#if	defined(NODENAMELEN)
#define	CLUSTERNAMELEN	NODENAMELEN
#else
#define	CLUSTERNAMELEN	256
#endif
#endif

#ifndef	NODENAMELEN
#if	defined(SYS_NMLN)
#define	NODENAMELEN	(SYS_NMLN-1)	/* usually 256 for SVR4! */
#else
#define	NODENAMELEN	256		/* should be at least 256 for SVR4! */
#endif
#endif

#ifndef	USERNAMELEN
#ifdef	LOGNAME_MAX
#define	USERNAMELEN	LOGNAME_MAX
#else
#define	USERNAMELEN	32
#endif
#endif

#ifndef	GROUPNAMELEN
#ifdef	LOGNAME_MAX
#define	GROUPNAMELEN	LOGNAME_MAX
#else
#define	GROUPNAMELEN	32
#endif
#endif

/* Solaris® project name */
#ifndef	PROJNAMELEN
#ifdef	LOGNAME_MAX
#define	PROJNAMELEN	LOGNAME_MAX
#else
#define	PROJNAMELEN	32
#endif
#endif

#ifndef	LOGNAMELEN
#ifdef	LOGNAME_MAX
#define	LOGNAMELEN	LOGNAME_MAX
#else
#define	LOGNAMELEN	32
#endif
#endif

#ifndef	PASSWORDLEN
#define	PASSWORDLEN	8
#endif

/* service name */
#ifndef	SVCNAMELEN
#define	SVCNAMELEN	32
#endif


#endif /* USYSDEFS_INCLUDE */


