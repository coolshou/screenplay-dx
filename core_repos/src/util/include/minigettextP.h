/* This file is copy and paste from glibc-2.3.2 by Charles Wang <cwang@redsonic.com>. */
#ifndef __MINIGETTEXTP_H__
#define __MINIGETTEXTP_H__

#include  <stddef.h>

#ifndef PARAMS
# if __STDC__ || defined __GNUC__ || defined __SUNPRO_C || defined __cplusplus || __PROTOTYPES
#  define PARAMS(args) args
# else
#  define PARAMS(args) ()
# endif
#endif

#ifndef internal_function
# define internal_function
#endif

#ifndef attribute_hidden
# define attribute_hidden
#endif

#ifndef HAVE_BUILTIN_EXPECT
# define __builtin_expect(expr, val) (expr)
#endif

#ifndef W
# define W(flag, data) ((flag) ? SWAP (data) : (data))
#endif

typedef unsigned nls_uint32;

static nls_uint32 SWAP PARAMS ((nls_uint32 i));

static inline nls_uint32
SWAP (i)
     nls_uint32 i;
{
  return (i << 24) | ((i & 0xff00) << 8) | ((i >> 8) & 0xff00) | (i >> 24);
}

#define freea(p) /* nothing */

#define _MAGIC 0x950412de
#define _MAGIC_SWAPPED 0xde120495

/* In-memory representation of system dependent string.  */
struct sysdep_string_desc
{
  /* Length of addressed string, including the trailing NUL.  */
  size_t length;
  /* Pointer to addressed string.  */
  const char *pointer;
};

/* The representation of an opened message catalog.  */
struct loaded_domain
{
  /* Pointer to memory containing the .mo file.  */
  const char *data;
  /* 1 if the memory is mmap()ed, 0 if the memory is malloc()ed.  */
  int use_mmap;
  /* Size of mmap()ed memory.  */
  size_t mmap_size;
  /* 1 if the .mo file uses a different endianness than this machine.  */
  int must_swap;
  /* Pointer to additional malloc()ed memory.  */
  void *malloced;

  /* Number of static strings pairs.  */
  nls_uint32 nstrings;
  /* Pointer to descriptors of original strings in the file.  */
  const struct string_desc *orig_tab;
  /* Pointer to descriptors of translated strings in the file.  */
  const struct string_desc *trans_tab;

  /* Number of system dependent strings pairs.  */
  nls_uint32 n_sysdep_strings;
  /* Pointer to descriptors of original sysdep strings.  */
  const struct sysdep_string_desc *orig_sysdep_tab;
  /* Pointer to descriptors of translated sysdep strings.  */
  const struct sysdep_string_desc *trans_sysdep_tab;

  /* Size of hash table.  */
  nls_uint32 hash_size;
  /* Pointer to hash table.  */
  const nls_uint32 *hash_tab;
  /* 1 if the hash table uses a different endianness than this machine.  */
  int must_swap_hash_tab;

  int codeset_cntr;
};

/* Header for binary .mo file format.  */
struct mo_file_header
{
  /* The magic number.  */
  nls_uint32 magic;
  /* The revision number of the file format.  */
  nls_uint32 revision;

  /* The following are only used in .mo files with major revision 0.  */

  /* The number of strings pairs.  */
  nls_uint32 nstrings;
  /* Offset of table with start offsets of original strings.  */
  nls_uint32 orig_tab_offset;
  /* Offset of table with start offsets of translated strings.  */
  nls_uint32 trans_tab_offset;
  /* Size of hash table.  */
  nls_uint32 hash_tab_size;
  /* Offset of first hash table entry.  */
  nls_uint32 hash_tab_offset;

  /* The following are only used in .mo files with minor revision >= 1.  */

  /* The number of system dependent segments.  */
  nls_uint32 n_sysdep_segments;
  /* Offset of table describing system dependent segments.  */
  nls_uint32 sysdep_segments_offset;
  /* The number of system dependent strings pairs.  */
  nls_uint32 n_sysdep_strings;
  /* Offset of table with start offsets of original sysdep strings.  */
  nls_uint32 orig_sysdep_tab_offset;
  /* Offset of table with start offsets of translated sysdep strings.  */
  nls_uint32 trans_sysdep_tab_offset;
};

/* Descriptor for static string contained in the binary .mo file.  */
struct string_desc
{
  /* Length of addressed string, not including the trailing NUL.  */
  nls_uint32 length;
  /* Offset of string in file.  */
  nls_uint32 offset;
};

/* The following are only used in .mo files with minor revision >= 1.  */

/* Descriptor for system dependent string segment.  */
struct sysdep_segment
{
  /* Length of addressed string, including the trailing NUL.  */
  nls_uint32 length;
  /* Offset of string in file.  */
  nls_uint32 offset;
};

/* Descriptor for system dependent string.  */
struct sysdep_string
{
  /* Offset of static string segments in file.  */
  nls_uint32 offset;
  /* Alternating sequence of static and system dependent segments.
     The last segment is a static segment, including the trailing NUL.  */
  struct segment_pair
  {
    /* Size of static segment.  */
    nls_uint32 segsize;
    /* Reference to system dependent string segment, or ~0 at the end.  */
    nls_uint32 sysdepref;
  } segments[1];
};

/* Marker for the end of the segments[] array.  This has the value 0xFFFFFFFF,
   regardless whether 'int' is 16 bit, 32 bit, or 64 bit.  */
#define SEGMENTS_END ((nls_uint32) ~0)

struct loaded_l10nfile
{
  const char *filename;
  int decided;

  const void *data;
};


#endif
