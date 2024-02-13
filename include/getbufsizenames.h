/* getbufsizenames HEADER */
/* lang=C20 */

/* list the various system buffer-size names (as strings) */
/* version %I% last-modified %G% */

/* revision history:

	= 2001-04-11, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2001 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	This file contains the string names (enumeration names) for
	the various system buffer-sizes, and the array interface
	to access them.


*******************************************************************************/


#ifndef	GETBUFSIZENAMES_INCLUDE
#define	GETBUFSIZENAMES_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<utypedefs.h>
#include	<clanguage.h>


enum getbufsizes {
	getbufsize_ma,		/* max-args */
	getbufsize_mn,		/* max-name */
	getbufsize_mp,		/* max-path */
	getbufsize_ml,		/* max-line */
	getbufsize_nn,		/* node-name */
	getbufsize_hn,		/* host-name */
	getbufsize_un,		/* user-name */
	getbufsize_gn,		/* group-name */
	getbufsize_pn,		/* project-name */
	getbufsize_pw,		/* passwd ent */
	getbufsize_sp,		/* shadow ent */
	getbufsize_ua,		/* user-attr ent */
	getbufsize_gr,		/* group ent */
	getbufsize_pj,		/* project ent */
	getbufsize_pr,		/* protocol-ent */
	getbufsize_nw,		/* network-ent */
	getbufsize_ho,		/* host-ent */
	getbufsize_sv,		/* service-ent */
	getbufsize_zn,		/* zone-name (from Zone-Info) */
	getbufsize_overlast
} ; /* end enum (getbufsizes) */


extern cchar	*getbufsizenames[] ;


#endif /* GETBUFSIZENAMES_INCLUDE */


