cmd_miscutils/less.o := /opt/mips-4.3/bin//mipsel-linux-gcc -Wp,-MD,miscutils/.less.o.d   -std=gnu99 -Iinclude -Ilibbb  -I/root/projects/SMP/GPL-1.02.24/core_repos/src/libs/busybox-1.10.0/libbb -include include/autoconf.h -D_GNU_SOURCE -DNDEBUG -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64 -D"BB_VER=KBUILD_STR(1.10.0)" -DBB_BT=AUTOCONF_TIMESTAMP -D_FORTIFY_SOURCE=2  -Wall -Wshadow -Wwrite-strings -Wundef -Wstrict-prototypes -Wunused -Wunused-parameter -Wold-style-definition -Wmissing-prototypes -Wmissing-declarations -Os -fno-builtin-strlen -finline-limit=0 -fomit-frame-pointer -ffunction-sections -fdata-sections -fno-guess-branch-probability -funsigned-char -static-libgcc -falign-functions=1 -falign-jumps=1 -falign-labels=1 -falign-loops=1  -Wdeclaration-after-statement -Wno-pointer-sign    -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(less)"  -D"KBUILD_MODNAME=KBUILD_STR(less)" -c -o miscutils/less.o miscutils/less.c

deps_miscutils/less.o := \
  miscutils/less.c \
    $(wildcard include/config/feature/less/regexp.h) \
    $(wildcard include/config/feature/less/flagcs.h) \
    $(wildcard include/config/feature/less/maxlines.h) \
    $(wildcard include/config/feature/less/marks.h) \
    $(wildcard include/config/ture/less/regexp.h) \
    $(wildcard include/config/feature/less/flags.h) \
    $(wildcard include/config/feature/less/brackets.h) \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/sched.h \
    $(wildcard include/config/.h) \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/features.h \
    $(wildcard include/config/c99.h) \
    $(wildcard include/config/c95.h) \
    $(wildcard include/config/ix.h) \
    $(wildcard include/config/ix2.h) \
    $(wildcard include/config/ix199309.h) \
    $(wildcard include/config/ix199506.h) \
    $(wildcard include/config/en.h) \
    $(wildcard include/config/en/extended.h) \
    $(wildcard include/config/x98.h) \
    $(wildcard include/config/en2k.h) \
    $(wildcard include/config/gefile.h) \
    $(wildcard include/config/gefile64.h) \
    $(wildcard include/config/e/offset64.h) \
    $(wildcard include/config/d.h) \
    $(wildcard include/config/c.h) \
    $(wildcard include/config/ile.h) \
    $(wildcard include/config/ntrant.h) \
    $(wildcard include/config/tify/level.h) \
    $(wildcard include/config/i.h) \
    $(wildcard include/config/ern/inlines.h) \
    $(wildcard include/config/ern/inlines/in/libc.h) \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/bits/predefs.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/sys/cdefs.h \
    $(wildcard include/config/espaces.h) \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/bits/wordsize.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/gnu/stubs.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/bits/types.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/bits/typesizes.h \
  /opt/mips-4.3/bin/../lib/gcc/mips-linux-gnu/4.3.2/include/stddef.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/time.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/bits/sched.h \
  include/libbb.h \
    $(wildcard include/config/selinux.h) \
    $(wildcard include/config/locale/support.h) \
    $(wildcard include/config/feature/shadowpasswds.h) \
    $(wildcard include/config/lfs.h) \
    $(wildcard include/config/feature/buffers/go/on/stack.h) \
    $(wildcard include/config/buffer.h) \
    $(wildcard include/config/ubuffer.h) \
    $(wildcard include/config/feature/buffers/go/in/bss.h) \
    $(wildcard include/config/feature/ipv6.h) \
    $(wildcard include/config/feature/check/names.h) \
    $(wildcard include/config/feature/prefer/applets.h) \
    $(wildcard include/config/busybox/exec/path.h) \
    $(wildcard include/config/getopt/long.h) \
    $(wildcard include/config/feature/pidfile.h) \
    $(wildcard include/config/feature/syslog.h) \
    $(wildcard include/config/feature/individual.h) \
    $(wildcard include/config/route.h) \
    $(wildcard include/config/gunzip.h) \
    $(wildcard include/config/bunzip2.h) \
    $(wildcard include/config/ktop.h) \
    $(wildcard include/config/ioctl/hex2str/error.h) \
    $(wildcard include/config/feature/editing.h) \
    $(wildcard include/config/feature/editing/history.h) \
    $(wildcard include/config/ture/editing/savehistory.h) \
    $(wildcard include/config/feature/editing/savehistory.h) \
    $(wildcard include/config/feature/tab/completion.h) \
    $(wildcard include/config/feature/username/completion.h) \
    $(wildcard include/config/feature/editing/vi.h) \
    $(wildcard include/config/inux.h) \
    $(wildcard include/config/feature/topmem.h) \
    $(wildcard include/config/pgrep.h) \
    $(wildcard include/config/pkill.h) \
    $(wildcard include/config/feature/devfs.h) \
  include/platform.h \
    $(wildcard include/config/werror.h) \
    $(wildcard include/config///.h) \
    $(wildcard include/config/nommu.h) \
    $(wildcard include/config//nommu.h) \
    $(wildcard include/config//mmu.h) \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/byteswap.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/bits/byteswap.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/endian.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/bits/endian.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/arpa/inet.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/netinet/in.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/stdint.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/bits/wchar.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/sys/socket.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/sys/uio.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/sys/types.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/sys/select.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/bits/select.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/bits/sigset.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/bits/time.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/sys/sysmacros.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/bits/pthreadtypes.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/bits/uio.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/bits/socket.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/bits/sockaddr.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/asm/socket.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/asm/sockios.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/asm/ioctl.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/bits/socket2.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/bits/in.h \
  /opt/mips-4.3/bin/../lib/gcc/mips-linux-gnu/4.3.2/include/stdbool.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/sys/mount.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/sys/ioctl.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/bits/ioctls.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/asm/ioctls.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/bits/ioctl-types.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/sys/ttydefaults.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/ctype.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/xlocale.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/dirent.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/bits/dirent.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/bits/posix1_lim.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/bits/local_lim.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/linux/limits.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/errno.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/bits/errno.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/linux/errno.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/asm/errno.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/asm-generic/errno-base.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/fcntl.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/bits/fcntl.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/sgidefs.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/sys/stat.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/bits/stat.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/bits/fcntl2.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/inttypes.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/netdb.h \
    $(wildcard include/config/3/ascii/rules.h) \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/rpc/netdb.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/bits/siginfo.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/bits/netdb.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/setjmp.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/bits/setjmp.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/signal.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/bits/signum.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/bits/sigaction.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/bits/sigcontext.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/bits/sigstack.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/sys/ucontext.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/bits/sigthread.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/stdio.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/libio.h \
    $(wildcard include/config/a.h) \
    $(wildcard include/config/ar/t.h) \
    $(wildcard include/config//io/file.h) \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/_G_config.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/wchar.h \
  /opt/mips-4.3/bin/../lib/gcc/mips-linux-gnu/4.3.2/include/stdarg.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/bits/stdio_lim.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/bits/sys_errlist.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/bits/stdio2.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/stdlib.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/bits/waitflags.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/bits/waitstatus.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/alloca.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/bits/stdlib.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/string.h \
    $(wildcard include/config/ing/inlines.h) \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/bits/string3.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/sys/poll.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/bits/poll.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/sys/mman.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/bits/mman.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/sys/time.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/sys/wait.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/sys/resource.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/bits/resource.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/termios.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/bits/termios.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/unistd.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/bits/posix_opt.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/bits/environments.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/bits/confname.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/getopt.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/bits/unistd.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/utime.h \
  /opt/mips-4.3/bin/../lib/gcc/mips-linux-gnu/4.3.2/include-fixed/el/limits.h \
  /opt/mips-4.3/bin/../lib/gcc/mips-linux-gnu/4.3.2/include-fixed/el/syslimits.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/limits.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/bits/posix2_lim.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/bits/xopen_lim.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/sys/param.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/linux/param.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/asm/param.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/mntent.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/paths.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/sys/statfs.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/bits/statfs.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/locale.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/bits/locale.h \
  include/pwd_.h \
    $(wildcard include/config/use/bb/pwd/grp.h) \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/pwd.h \
  include/grp_.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/grp.h \
  include/shadow_.h \
    $(wildcard include/config/use/bb/shadow.h) \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/shadow.h \
  include/xatonum.h \
  include/xregex.h \
  /opt/mips-4.3/bin/../mips-linux-gnu/libc/usr/include/regex.h \

miscutils/less.o: $(deps_miscutils/less.o)

$(deps_miscutils/less.o):
