/*
 * Copyright (c) 2010, 2011, 2012 Ryan Flannery <ryan.flannery@gmail.com>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include "ecmd.h"

int
ecmd_exec(const char *ecmd, int argc, char **argv)
{
   /* set of e-commands */
   static const struct ecmd *ecmdtab[] = {
      &ecmd_add,
      &ecmd_addurl,
      &ecmd_check,
      &ecmd_flush,
      &ecmd_help,
      &ecmd_init,
      &ecmd_rmfile,
      &ecmd_tag,
      &ecmd_update,
   };
   static const int ecmdtab_size = sizeof ecmdtab / sizeof ecmdtab[0];
   int              i;

   /* search for e-command (first by name and then by alias) */
   for (i = 0; i < ecmdtab_size; i++) {
      if (strcmp(ecmd, ecmdtab[i]->name) == 0)
         break;
      if (ecmdtab[i]->alias != NULL && strcmp(ecmd, ecmdtab[i]->alias) == 0)
         break;
   }
   /* not found; bail out */
   if (i == ecmdtab_size)
      return -1;

   ecmdtab[i]->exec(argc, argv);
   return 0;
}
