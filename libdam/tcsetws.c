/* tcsetws */

/* UNIX® terminal-control Set Window-Size */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Set the window size on the terminal.

	Synopsis:

	int tcsetws(fd,wsp)
	int		fd ;
	struct winsize	*wsp ;

	Arguments:

	fd		file-descriptor of termainal
	wsp		pointer to window size

	Returns:

	>=0		success (previous number of lines)
	<0		error


*******************************************************************************/


#include	<envstandards.h>	/* MUST be first to configure */

#include	<sys/types.h>
#include	<sys/param.h>
#include	<unistd.h>
#include	<termios.h>

#include	<vsystem.h>
#include	<localmisc.h>


/* exported subroutines */


int tcsetws(int fd,struct winsize *wsp)
{
	int		rs = SR_OK ;
	if (wsp != NULL) {
	    if (fd >= 0) {
	        rs = u_ioctl(fd,TIOCSWINSZ,wsp) ;
	    } else {
	        rs = SR_NOTOPEN ;
	    }
	} else {
	    rs = SR_FAULT ;
	}
	return rs ;
}
/* end subroutine (tcsetws) */


