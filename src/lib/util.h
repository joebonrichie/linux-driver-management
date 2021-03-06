/*
 * This file is part of linux-driver-management.
 *
 * Copyright © 2016-2017 Ikey Doherty
 *
 * linux-driver-management is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation; either version 2.1
 * of the License, or (at your option) any later version.
 */

#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

/**
 * Shut up the compiler
 */
#define __ldm_unused__ __attribute__((unused))

/**
 * Taken from libnica and about fourteen of my previous projects..
 */

#define DEF_AUTOFREE(N, C)                                                                         \
        static inline void _autofree_func_##N(void *p)                                             \
        {                                                                                          \
                if (p && *(N **)p) {                                                               \
                        C(*(N **)p);                                                               \
                        (*(void **)p) = NULL;                                                      \
                }                                                                                  \
        }

/**
 * Make use of __attribute__((cleanup(x))) functionality with a previously
 * declared autofree handler, by way of DEF_AUTOFREE
 */
#define autofree(N) __attribute__((cleanup(_autofree_func_##N))) N

/**
 * Determine size of static arrays
 */
#define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))

DEF_AUTOFREE(char, free)
DEF_AUTOFREE(FILE, fclose)

/**
 * Allocate a string or abort
 */
char *string_printf(const char *s, ...) __attribute__((format(printf, 1, 2)));

/**
 * Determine if two strings are equal, accounting also for NULL strings
 */
static inline bool streq(const char *a, const char *b)
{
        if (!a || !b) {
                return false;
        }
        return (strcmp(a, b) == 0);
}

bool mkdir_p(const char *path, mode_t mode);

/*
 * Editor modelines  -  https://www.wireshark.org/tools/modelines.html
 *
 * Local variables:
 * c-basic-offset: 8
 * tab-width: 8
 * indent-tabs-mode: nil
 * End:
 *
 * vi: set shiftwidth=8 tabstop=8 expandtab:
 * :indentSize=8:tabSize=8:noTabs=true:
 */
