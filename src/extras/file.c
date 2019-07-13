#include <extras/file.h>

// int
// fgetc (FILE *fp)
// {
//   int result;
//   CHECK_FILE (fp, EOF);
//   if (!_IO_need_lock (fp))
//     return _IO_getc_unlocked (fp);
//   _IO_acquire_lock (fp);
//   result = _IO_getc_unlocked (fp);
//   _IO_release_lock (fp);
//   return result;
// }