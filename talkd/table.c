/* table */



/*	Copyright (c) 1984, 1986, 1987, 1988, 1989 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#ident	"@(#)table.c	1.3	96/05/03 SMI"	/* SVr4.0 1.1	*/

/*
 * +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * 		PROPRIETARY NOTICE (Combined)
 * 
 * This source code is unpublished proprietary information
 * constituting, or derived under license from AT&T's UNIX(r) System V.
 * In addition, portions of such source code were derived from Berkeley
 * 4.3 BSD under license from the Regents of the University of
 * California.
 * 
 * 
 * 
 * 		Copyright Notice 
 * 
 * Notice of copyright on this source code product does not indicate 
 * publication.
 * 
 * 	(c) 1986,1987,1988.1989  Sun Microsystems, Inc
 * 	(c) 1983,1984,1985,1986,1987,1988,1989  AT&T.
 * 	          All rights reserved.
 *  
 */


/******************************************************************************

 routines to handle insertion, deletion, etc on the table
   of requests kept by the daemon. Nothing fancy here, linear
   search on a double-linked list. A time is kept with each 
   entry so that overly old invitations can be eliminated.

   Consider this a mis-guided attempt at modularity.

******************************************************************************/



#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <netdb.h>
#include <malloc.h>
#include <string.h>
#include <stdio.h>

#include "ctl.h"



/* local defines */

#define MAX_ID 16000 /* << 2^15 so I don't have sign troubles */

#define NIL ( (TABLE_ENT *) 0)



extern int debug;

struct timeval tp;

typedef struct table_ent TABLE_ENT;

struct table_ent {
    CTL_MSG request;
    long time;
    TABLE_ENT *next;
    TABLE_ENT *last;
} ;

TABLE_ENT *table = NIL;

CTL_MSG *find_request(CTL_MSG *request);
static void delete(TABLE_ENT *ptr);

extern void print_error(char *string);
extern void print_request(CTL_MSG *request);


/* forward references */

int new_id(void);




    /*
     * Look in the table for an invitation that matches the current
     * request looking for an invitation
     */

CTL_MSG *
find_match(CTL_MSG *request)
{
    TABLE_ENT *ptr;
    long current_time;


    gettimeofday(&tp, (struct timezone *) 0);
    current_time = tp.tv_sec;

    ptr = table;

    if (debug) {
	printf("Entering Look-Up with : \n");
	print_request(request);
    }

    while (ptr != NIL) {

	if ( (ptr->time - current_time) > MAX_LIFE ) {

		/* the entry is too old */
	    if (debug) printf("Deleting expired entry : \n");
	    if (debug) print_request(&ptr->request);
	    delete(ptr);
	    ptr = ptr->next;
	    continue;
	}

	if (debug) print_request(&ptr->request);

	if ( strcmp(request->l_name, ptr->request.r_name) == 0 &&
	     strcmp(request->r_name, ptr->request.l_name) == 0 &&
	     ptr->request.type == LEAVE_INVITE ) {
	    return(&ptr->request);
	}
	
	ptr = ptr->next;
    }
    
    return((CTL_MSG *) 0);
}
/* end subroutine (find_match) */


    /*
     * look for an identical request, as opposed to a complimentary
     * one as find_match does 
     */

CTL_MSG *
find_request(CTL_MSG *request)
{
    TABLE_ENT *ptr;
    long current_time;


    gettimeofday(&tp, (struct timezone *) 0);
    current_time = tp.tv_sec;

	/* See if this is a repeated message, and check for
	   out of date entries in the table while we are it.
	 */

    ptr = table;

    if (debug) {
	printf("Entering find_request with : \n");
	print_request(request);
    }

    while (ptr != NIL) {

	if ( (ptr->time - current_time) > MAX_LIFE ) {
		/* the entry is too old */
	    if (debug) printf("Deleting expired entry : \n");
	    if (debug) print_request(&ptr->request);
	    delete(ptr);
	    ptr = ptr->next;
	    continue;
	}

	if (debug) print_request(&ptr->request);

	if ( strcmp(request->r_name, ptr->request.r_name) == 0 &&
	     strcmp(request->l_name, ptr->request.l_name) == 0 &&
	     request->type == ptr->request.type &&
	     request->pid == ptr->request.pid) {
	    
		/* update the time if we 'touch' it */
	    ptr->time = current_time;
	    return(&ptr->request);
	}

	ptr = ptr->next;
    }

    return((CTL_MSG *) 0);
}


void
insert_table(CTL_MSG *request, CTL_RESPONSE *response)
{
    TABLE_ENT *ptr;
    long current_time;


    gettimeofday(&tp, (struct timezone *) 0);
    current_time = tp.tv_sec;

    response->id_num = request->id_num = new_id();

	/* insert a new entry into the top of the list */
    
    ptr = (TABLE_ENT *) malloc(sizeof(TABLE_ENT));

    if (ptr == NIL) {
	print_error("malloc in insert_table");
    }

    ptr->time = current_time;
    ptr->request = *request;

    ptr->next = table;
    if (ptr->next != NIL) {
	ptr->next->last = ptr;
    }
    ptr->last = NIL;
    table = ptr;
}


    /* generate a unique non-zero sequence number */

int
new_id(void)
{
    static int current_id = 0;


    current_id = (current_id + 1) % MAX_ID;

	/* 0 is reserved, helps to pick up bugs */

    if (current_id == 0) current_id = 1;

    return(current_id);
}
/* end subroutine (new_id) */


    /* delete the invitation with id 'id_num' */

int
delete_invite(int id_num)
{
    TABLE_ENT *ptr;


    ptr = table;

    if (debug) printf("Entering delete_invite with %d\n", id_num);

    while (ptr != NIL && ptr->request.id_num != id_num) {
	if (debug) print_request(&ptr->request);
	ptr = ptr->next;
    }
	
    if (ptr != NIL) {
	delete(ptr);
	return(SUCCESS);
    }
    
    return(NOT_HERE);
}


    /* classic delete from a double-linked list */

static void
delete(TABLE_ENT *ptr)
{


    if (debug) printf("Deleting : ");

    if (debug) print_request(&ptr->request);

    if (table == ptr) {
	table = ptr->next;
    } else if (ptr->last != NIL) {
	ptr->last->next = ptr->next;
    }

    if (ptr->next != NIL) {
	ptr->next->last = ptr->last;
    }

    free(ptr);
}



