#ifndef UTILS_H
#define UTILS_H

#define DATS_RAISE_ERROR(X) __dats_raise_error(X, __FILE__, __LINE__)
#define DATS_OOM_GUARD(X) __dats_oom_guard(X, __FILE__, __LINE__)

void __dats_raise_error(const char *message, const char *filename, int line);

void *__dats_oom_guard(void *ptr, const char *filename, int line);

#endif