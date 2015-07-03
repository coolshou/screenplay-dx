#ifdef _SEQUENT_
# include <sys/types.h>
# include <sys/utsname.h>
#endif
main ()
{
#if defined (sony)
#if defined (MIPSEB)
  /* BFD wants "bsd" instead of "newsos".  Perhaps BFD should be changed,
     I don't know....  */
  printf ("mips-sony-bsd\n"); exit (0);
#else
#include <sys/param.h>
  printf ("m68k-sony-newsos%s\n",
#ifdef NEWSOS4
          "4"
#else
	  ""
#endif
         ); exit (0);
#endif
#endif

#if defined (__arm) && defined (__acorn) && defined (__unix)
  printf ("arm-acorn-riscix"); exit (0);
#endif

#if defined (hp300) && !defined (hpux)
  printf ("m68k-hp-bsd\n"); exit (0);
#endif

#if defined (NeXT)
#if !defined (__ARCHITECTURE__)
#define __ARCHITECTURE__ "m68k"
#endif
  int version;
  version=;
  if (version < 4)
    printf ("%s-next-nextstep%d\n", __ARCHITECTURE__, version);
  else
    printf ("%s-next-openstep%d\n", __ARCHITECTURE__, version);
  exit (0);
#endif

#if defined (MULTIMAX) || defined (n16)
#if defined (UMAXV)
  printf ("ns32k-encore-sysv\n"); exit (0);
#else
#if defined (CMU)
  printf ("ns32k-encore-mach\n"); exit (0);
#else
  printf ("ns32k-encore-bsd\n"); exit (0);
#endif
#endif
#endif

#if defined (__386BSD__)
  printf ("i386-pc-bsd\n"); exit (0);
#endif

#if defined (sequent)
#if defined (i386)
  printf ("i386-sequent-dynix\n"); exit (0);
#endif
#if defined (ns32000)
  printf ("ns32k-sequent-dynix\n"); exit (0);
#endif
#endif

#if defined (_SEQUENT_)
    struct utsname un;

    uname(&un);

    if (strncmp(un.version, "V2", 2) == 0) {
	printf ("i386-sequent-ptx2\n"); exit (0);
    }
    if (strncmp(un.version, "V1", 2) == 0) { /* XXX is V1 correct? */
	printf ("i386-sequent-ptx1\n"); exit (0);
    }
    printf ("i386-sequent-ptx\n"); exit (0);

#endif

#if defined (vax)
#if !defined (ultrix)
  printf ("vax-dec-bsd\n"); exit (0);
#else
  printf ("vax-dec-ultrix\n"); exit (0);
#endif
#endif

#if defined (alliant) && defined (i860)
  printf ("i860-alliant-bsd\n"); exit (0);
#endif

  exit (1);
}
