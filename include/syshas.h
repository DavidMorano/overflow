/* syshas INCLUDE */
/* lang=C20 */


/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

	= 2017-08-01, David A­D­ Morano
	Updated for lack of interfaces in MacOS Darwin

	= 2023-10-06, David A­D­ Morano
	I updated this to include an additional item that many of
	these operating systems (Darwin and Linux) do not have have;
	namely |strlcpy(3c)| and |strlen(3c)|.

*/

/* Copyright © 2000,2017,2023 David A­D­ Morano.  All rights reserved. */

#ifndef	SYSHAS_INCLUDE
#define	SYSHAS_INCLUDE


/******************************************************************************/
#if	defined(OSNAME_SunOS) && (OSNAME_SunOS > 0)

/* Solaris®: system has shadow password DB */
#define	SYSHAS_SHADOW		1

/* Solaris®: projects */
#define	SYSHAS_PROJECT		1

/* Solaris®: system has 'statvfs(2)' call and friends */
#define	SYSHAS_STATVFS		1

/* Solaris®: system has 'poll(2)' call and friends */
#define	SYSHAS_POLL		1

/* Solaris®: system has STREAMS framework */
#define	SYSHAS_STREAMS		1

/* Solaris®: has POSIX real-time timers */
#define	SYSHAS_TIMER		1

/* Solaris®: system has ACL framework */
#define	SYSHAS_ACL		1

/* Solaris®: system has user attributes framework */
#define	SYSHAS_USERATTR		1

/* Solaris®: system has Security-Database framework */
#define	SYSHAS_SECDB		1

/* Solaris®: has these two stupid environment manipulation subroutines */
#define	SYSHAS_SETENV		0
#define	SYSHAS_UNSETENV		0

/* Solaris®: system information header for 'sysinfo(2)' */
#define	SYSHAS_SYSINFO		1

/* Solaris®: system has a 'offset_t' data type (assumed to be 64 bits) */
#define	SYSHAS_OFFSET		1

/* Solaris®: getcwd(3c) */
#define	SYSHAS_GETCWD		1

/* Solaris®: AIO */
#define	SYSHAS_AIO		1

/* Solaris®: typedefs */
#define	SYSHAS_USHORT		0
#define	SYSHAS_UINT		0

/* Solaris®: tasks */
#define	SYSHAS_TASK		1

/* Solaris®: UTMPX */
#define	SYSHAS_UTMPX		1

/* Solaris®: UTMP-name */
#define	SYSHAS_UTMPNAME		1
#define	SYSHAS_UTMPXNAME	1

/* Solaris®: loadavg(3c) */
#define	SYSHAS_LOADAVG		1
#define	SYSHAS_LOADAVGINT	1

/* Solaris®: gethrtime(3c) */
#define	SYSHAS_HRTIME		1

/* Solaris®: readdir_r(3c) */
#define	SYSHAS_READDIRR		1

/* Solaris®: getpwxxx_r(3c) */
#define	SYSHAS_GETPWXXXR	1	/* any of the others (logical OR) */
#define	SYSHAS_GETPWGNUR	0	/* has GNU (GLIBC) interface */
#define	SYSHAS_GETPWENTR	1
#define	SYSHAS_GETPWNAMR	1
#define	SYSHAS_GETPWUIDR	1

/* Solaris®: getspxxx_r(3c) */
#define	SYSHAS_GETSPXXXR	1	/* any of the others (logical OR) */
#define	SYSHAS_GETSPGNUR	0	/* has GNU (GLIBC) interface */
#define	SYSHAS_GETSPENTR	1
#define	SYSHAS_GETSPNANR	1

/* Solaris®: getgrxxx_r(3c) */
#define	SYSHAS_GETGRXXXR	1	/* any of the others (logical OR) */
#define	SYSHAS_GETGRGNUR	0	/* has GNU (GLIBC) interface */
#define	SYSHAS_GETGRENTR	1
#define	SYSHAS_GETGRNAMR	1
#define	SYSHAS_GETGRGIDR	1

/* Solaris®: getpjxxx_r(3c) */
#define	SYSHAS_GETPJXXXR	1	/* any of the others (logical OR) */
#define	SYSHAS_GETPJGNUR	0	/* has GNU (GLIBC) interface */
#define	SYSHAS_GETPJENTR	1
#define	SYSHAS_GETPJNAMR	1
#define	SYSHAS_GETPJPIDR	1

/* Solaris®: getprotobyxxx_r(3c) */
#define	SYSHAS_GETPRXXXR	1
#define	SYSHAS_GETPRGNUR	0	/* has GNU (GLIBC) interface */

/* Solaris®: getnetbyxxx_r(3c) */
#define	SYSHAS_GETNWXXXR	1
#define	SYSHAS_GETNWGNUR	0	/* has GNU (GLIBC) interface */

/* Solaris®: gethostbyxxx_r(3c) */
#define	SYSHAS_GETHPXXXR	1
#define	SYSHAS_GETHPGNUR	0	/* has GNU (GLIBC) interface */

/* Solaris®: getservbyxxx_r(3c) */
#define	SYSHAS_GETSVXXXR	1
#define	SYSHAS_GETSVGNUR	0	/* has GNU (GLIBC) interface */

/* Solaris®: localtime_r(3c) */
#define	SYSHAS_LOCALTIMER	1

/* Solaris®: gmtime_r(3c) */
#define	SYSHAS_GMTIMER		1

/* Solaris®: ttyname_r(3c) */
#define	SYSHAS_TTYNAMER		1

/* Solaris®: postix_openpt(3c) */
#define	SYSHAS_OPENPT		0

/* Solaris®: ptmx(9) */
#define	SYSHAS_PTMX		1

/* Solaris®: POSIX shared memory ('shm(3rt)') */
#define	SYSHAS_PSHM		1

/* Solaris®: POSIX regular semaphores ('sem(3rt)') */
#define	SYSHAS_PSEM		1

/* Solaris: POSIX named semaphores ('sem(3rt)') */
#define	SYSHAS_NSEM		1

/* Solaris®: POSIX message queues ('mq(3rt)') */
#define	SYSHAS_PMQ		1

/* Solaris®: AUDIT - part of Solaris® Basic-Security-Module (BSM) */
#define	SYSHAS_AUDIT		1

/* Solaris®: get-directory-entries ('getdents(2)') */
#define	SYSHAS_GETDENTS		1

/* Solaris®: XTI */
#define	SYSHAS_XTI		1

/* Solaris®: robust mutexes */
#define	SYSHAS_MUTEXROBUST	1

/* Solaris®: strnlen(3c) */
#define	SYSHAS_STRNLEN		0

/* Solaris®: strlcpy(3c) */
#define	SYSHAS_STRLCPY		1

/* Solaris®: sigsend(2) */
#define	SYSHAS_SIGSEND		1

/* Solaris®: sigwait(2) */
#define	SYSHAS_SIGWAIT		1

/* Solaris®: ucontext */
#define	SYSHAS_UCONTEXT		1

/* Solaris®: getcontext(3c) */
#define	SYSHAS_GETCONTEXT	1

/* Solaris®: Relative-Timed-Wait feature */
#define	SYSHAS_RELTIMEDWAIT	1

/* Solaris®: System-Auxillary-Information feature */
#define	SYSHAS_SYSAUXINFO	1

/* Solaris®: Memory |memcntl(2)| */
#define	SYSHAS_MEMCNTL		1

/* Solaris®: Memory |plock(2)| */
#define	SYSHAS_MEMPLOCK		1


/******************************************************************************/
#elif	defined(OSNAME_Darwin) && (OSNAME_Darwin > 0)

/* Darwin: system has shadow password DB */
#define	SYSHAS_SHADOW		0

/* Darwin: projects */
#define	SYSHAS_PROJECT		0

/* Darwin: system has 'statvfs(2)' call and friends */
#if	defined(OSNUM) && (OSNUM >= 8)
#define	SYSHAS_STATVFS		1
#else
#define	SYSHAS_STATVFS		0
#endif

/* Darwin: system has 'poll(2)' call and friends */
#if	defined(OSNUM) && (OSNUM >= 8)
#define	SYSHAS_POLL		1
#else
#define	SYSHAS_POLL		0
#endif

/* Darwin: STREAMS */
#define	SYSHAS_STREAMS		0

/* Darwin: does *not* have POSIX real-time timers */
#define	SYSHAS_TIMER		0

/* Darwin: system has ACL framework */
#define	SYSHAS_ACL		0

/* Darwin: system has user attributes framework */
#define	SYSHAS_USERATTR		0

/* Darwin: system has Security-Database framework */
#define	SYSHAS_SECDB		0

/* Darwin: has these two stupid environment manipulation subroutines */
#define	SYSHAS_SETENV		0
#define	SYSHAS_UNSETENV		0

/* Darwin: system information header for 'sysinfo(2)' */
#define	SYSHAS_SYSINFO		0

/* Darwin: system has a 'offset_t' data type (assumed to be 64 bits) */
#define	SYSHAS_OFFSET		0

/* Darwin: getcwd(3c) */
#define	SYSHAS_GETCWD		1

/* Darwin: AIO */
#if	defined(OSNUM) && (OSNUM >= 8)
#define	SYSHAS_AIO		1
#else
#define	SYSHAS_AIO		0
#endif

/* Darwin: typedefs */
#define	SYSHAS_USHORT		1
#define	SYSHAS_UINT		1

/* Darwin: tasks */
#define	SYSHAS_TASK		0

/* Darwin: UTMPX */
#if	defined(OSNUM) && (OSNUM >= 8)
#define	SYSHAS_UTMPX		1
#else
#define	SYSHAS_UTMPX		0
#endif

/* Darwin: UTMP-name */
#define	SYSHAS_UTMPNAME		0
#if	defined(OSNUM) && (OSNUM >= 9)
#define	SYSHAS_UTMPXNAME	1
#else
#define	SYSHAS_UTMPXNAME	0
#endif

/* Darwin: loadavg(3c) */
#define	SYSHAS_LOADAVG		1
#define	SYSHAS_LOADAVGINT	0

/* Darwin: gethrtime(3c) */
#define	SYSHAS_HRTIME		0

/* Darwin: readdir_r(3c) */
#define	SYSHAS_READDIRR		1

/* Darwin: getpwxxx_r(3c) */
#define	SYSHAS_GETPWXXXR	1	/* any of the others (logical OR) */
#define	SYSHAS_GETPWGNUR	0	/* has GNU (GLIBC) interface */
#define	SYSHAS_GETPWENTR	0
#define	SYSHAS_GETPWNAMR	1
#define	SYSHAS_GETPWUIDR	1

/* Darwin: getspxxx_r(3c) */
#define	SYSHAS_GETSPXXXR	0	/* any of the others (logical OR) */
#define	SYSHAS_GETSPGNUR	0	/* has GNU (GLIBC) interface */
#define	SYSHAS_GETSPENTR	0
#define	SYSHAS_GETSPNAMR	0

/* Darwin: getgrxxx_r(3c) */
#define	SYSHAS_GETGRXXXR	1	/* any of the others (logical OR) */
#define	SYSHAS_GETGRGNUR	0	/* has GNU (GLIBC) interface */
#define	SYSHAS_GETGRENTR	0	
#define	SYSHAS_GETGRNAMR	1
#define	SYSHAS_GETGRGIDR	1

/* Darwin: getpjxxx_r(3c) */
#define	SYSHAS_GETPJXXXR	0	/* any of the others (logical OR) */
#define	SYSHAS_GETPJGNUR	0	/* has GNU (GLIBC) interface */
#define	SYSHAS_GETPJENTR	0
#define	SYSHAS_GETPJNAMR	0
#define	SYSHAS_GETPJPIDR	0

/* Darwin: getprotobyxxx_r(3c) */
#define	SYSHAS_GETPRXXXR	0
#define	SYSHAS_GETPRGNUR	0	/* has GNU (GLIBC) interface */

/* Darwin: getnetbyxxx_r(3c) */
#define	SYSHAS_GETNWXXXR	0
#define	SYSHAS_GETNWGNUR	0	/* has GNU (GLIBC) interface */

/* Darwin: gethostbyxxx_r(3c) */
#define	SYSHAS_GETHPXXXR	0
#define	SYSHAS_GETHPGNUR	0	/* has GNU (GLIBC) interface */

/* Darwin: getservbyxxx_r(3c) */
#define	SYSHAS_GETSVXXXR	0
#define	SYSHAS_GETSVGNUR	0	/* has GNU (GLIBC) interface */

/* Darwin: localtime_r(3c) */
#define	SYSHAS_LOCALTIMER	1

/* Darwin: gmtime_r(3c) */
#define	SYSHAS_GMTIMER		1

/* Darwin: ttyname_r(3c) */
#define	SYSHAS_TTYNAMER		0

/* Darwin: postix_openpt(3c) */
#define	SYSHAS_OPENPT		1

/* Darwin: ptmx(9) */
#define	SYSHAS_PTMX		1

/* Darwin: POSIX shared memory ('shm(3rt)') */
#define	SYSHAS_PSHM		1

/* Darwin: POSIX unnamed semaphores ('sem(3rt)') */
#define	SYSHAS_PSEM		0

/* Darwin: POSIX named semaphores ('sem(3rt)') */
#define	SYSHAS_NSEM		1

/* Darwin: POSIX message queues ('mq(3rt)') */
#define	SYSHAS_PMQ		0

/* Darwin: AUDIT - part of Solaris® Basic-Security-Module (BSM) */
#define	SYSHAS_AUDIT		0

/* Darwin: get-directory-entries ('getdents(2)') */
#define	SYSHAS_GETDENTS		0

/* Darwin: XTI */
#define	SYSHAS_XTI		0

/* Darwin: robust mutexes */
#define	SYSHAS_MUTEXROBUST	0

/* Darwin: strnlen(3c) */
#define	SYSHAS_STRNLEN		1

/* Darwin: strlcpy(3c) */
#define	SYSHAS_STRLCPY		1

/* Darwin: sigsend(2) */
#define	SYSHAS_SIGSEND		0

/* Darwin: sigwait(2) */
#define	SYSHAS_SIGWAIT		0

/* Darwin: ucontext */
#define	SYSHAS_UCONTEXT		1

/* Darwin: getcontext(3c) */
#define	SYSHAS_GETCONTEXT	1

/* Darwin: Relative-Timed-Wait feature */
#define	SYSHAS_RELTIMEDWAIT	0

/* Darwin: System-Auxillary-Information feature */
#define	SYSHAS_SYSAUXINFO	1

/* Darwin: Memory |memcntl(2)| */
#define	SYSHAS_MEMCNTL		0

/* Darwin: Memory |plock(2)| */
#define	SYSHAS_MEMPLOCK		0

/******************************************************************************/
#elif	defined(OSNAME_Linux) && (OSNAME_Linux > 0)

/* Linux: system has shadow password DB */
#define	SYSHAS_SHADOW		1

/* Linux: projects */
#define	SYSHAS_PROJECT		0

/* Linux: system has 'statvfs(2)' call and friends */
#define	SYSHAS_STATVFS		1

/* Linux: system has 'poll(2)' call and friends */
#define	SYSHAS_POLL		1

/* Linux: system has STREAMS framework */
#define	SYSHAS_STREAMS		1

/* Linux: has POSIX real-time timers */
#define	SYSHAS_TIMER		1

/* Linux: system has ACL framework */
#define	SYSHAS_ACL		1

/* Linux: system has user attributes framework */
#define	SYSHAS_USERATTR		0

/* Linux: system has Security-Database framework */
#define	SYSHAS_SECDB		0

/* Linux: has these two stupid environment manipulation subroutines */
#define	SYSHAS_SETENV		0
#define	SYSHAS_UNSETENV		0

/* Linux: system information header for 'sysinfo(2)' */
#define	SYSHAS_SYSINFO		1

/* Linux: system has a 'offset_t' data type (assumed to be 64 bits) */
#define	SYSHAS_OFFSET		1

/* Linux: getcwd(3c) */
#define	SYSHAS_GETCWD		1

/* Linux: AIO */
#define	SYSHAS_AIO		1

/* Linux: typedefs */
#define	SYSHAS_USHORT		0
#define	SYSHAS_UINT		0

/* Linux: tasks */
#define	SYSHAS_TASK		1

/* Linux: UTMPX */
#define	SYSHAS_UTMPX		1

/* Linux: UTMP-name */
#define	SYSHAS_UTMPNAME		1
#define	SYSHAS_UTMPXNAME	1

/* Linux: loadavg(3c) */
#define	SYSHAS_LOADAVG		1
#define	SYSHAS_LOADAVGINT	0

/* Linux: gethrtime(3c) */
#define	SYSHAS_HRTIME		0

/* Linux: readdir_r(3c) */
#define	SYSHAS_READDIRR		1

/* Linux: getpwxxx_r(3c) */
#define	SYSHAS_GETPWXXXR	1	/* any of the others (logical OR) */
#define	SYSHAS_GETPWGNUR	1	/* has GNU (GLIBC) interface */
#define	SYSHAS_GETPWENTR	1
#define	SYSHAS_GETPWNAMR	1
#define	SYSHAS_GETPWUIDR	1

/* Linux: getspxxx_r(3c) */
#define	SYSHAS_GETSPXXXR	1	/* any of the others (logical OR) */
#define	SYSHAS_GETSPGNUR	1	/* has GNU (GLIBC) interface */
#define	SYSHAS_GETSPENTR	1
#define	SYSHAS_GETSPNAMR	1

/* Linux: getgrxxx_r(3c) */
#define	SYSHAS_GETGRXXXR	1	/* any of the others (logical OR) */
#define	SYSHAS_GETGRGNUR	1	/* has GNU (GLIBC) interface */
#define	SYSHAS_GETGRENTR	1
#define	SYSHAS_GETGRNAMR	1
#define	SYSHAS_GETGRGIDR	1

/* Linux: getpjxxx_r(3c) */
#define	SYSHAS_GETPJXXXR	0	/* any of the others (logical OR) */
#define	SYSHAS_GETPJGNUR	0	/* has GNU (GLIBC) interface */
#define	SYSHAS_GETPJENTR	0
#define	SYSHAS_GETPJNAMR	0
#define	SYSHAS_GETPJPIDR	0

/* Linux: getprotobyxxx_r(3c) */
#define	SYSHAS_GETPRXXXR	1	/* has a reentrant interface */
#define	SYSHAS_GETPRGNUR	1	/* has GNU (GLIBC) interface */

/* Linux: getnetbyxxx_r(3c) */
#define	SYSHAS_GETNWXXXR	1	/* has a reentrant interface */
#define	SYSHAS_GETNWGNUR	1	/* has GNU (GLIBC) interface */

/* Linux: gethostbyxxx_r(3c) */
#define	SYSHAS_GETHPXXXR	1	/* has a reentrant interface */
#define	SYSHAS_GETHPGNUR	1	/* has GNU (GLIBC) interface */

/* Linux: getservbyxxx_r(3c) */
#define	SYSHAS_GETSVXXXR	1	/* has a reentrant interface */
#define	SYSHAS_GETSVGNUR	1	/* has GNU (GLIBC) interface */

/* Linux: localtime_r(3c) */
#define	SYSHAS_LOCALTIMER	1

/* Linux: gmtime_r(3c) */
#define	SYSHAS_GMTIMER		1

/* Linux: ttyname_r(3c) */
#define	SYSHAS_TTYNAMER		1

/* Linux: postix_openpt(3c) */
#define	SYSHAS_OPENPT		0

/* Linux: ptmx(9) */
#define	SYSHAS_PTMX		1

/* Linux: POSIX shared memory ('shm(3rt)') */
#define	SYSHAS_PSHM		1

/* Linux: POSIX regular semaphores ('sem(3rt)') */
#define	SYSHAS_PSEM		1

/* Linux: POSIX named semaphores ('sem(3rt)') */
#define	SYSHAS_NSEM		1

/* Linux: POSIX message queues ('mq(3rt)') */
#define	SYSHAS_PMQ		1

/* Linux: AUDIT - part of Linux Basic-Security-Module (BSM) */
#define	SYSHAS_AUDIT		1

/* Linux: get-directory-entries ('getdents(2)') */
#define	SYSHAS_GETDENTS		1

/* Linux: XTI */
#define	SYSHAS_XTI		1

/* Linux: robust mutexes */
#define	SYSHAS_MUTEXROBUST	1

/* Linux: strnlen(3c) */
#define	SYSHAS_STRNLEN		0

/* Linux: strlcpy(3c) */
#define	SYSHAS_STRLCPY		0

/* Linux: sigsend(2) */
#define	SYSHAS_SIGSEND		1

/* Linux: sigwait(2) */
#define	SYSHAS_SIGWAIT		1

/* Linux: ucontext */
#define	SYSHAS_UCONTEXT		1

/* Linux: getcontext(3c) */
#define	SYSHAS_GETCONTEXT	1

/* Linux: Relative-Timed-Wait feature */
#define	SYSHAS_RELTIMEDWAIT	0

/* Linux: System-Auxillary-Information feature */
#define	SYSHAS_SYSAUXINFO	0

/* Linux: Memory |memcntl(2)| */
#define	SYSHAS_MEMCNTL		0

/* Linux: Memory |plock(2)| */
#define	SYSHAS_MEMPLOCK		0

/******************************************************************************/
#endif /* OSNAME */


#endif /* SYSHAS_INCLUDE */


