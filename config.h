/*
 * Copyright (c) 2010 Ryan Flannery <ryan.flannery@gmail.com>
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

#ifndef CONFIG_H
#define CONFIG_H

/* hard-coded defaults for various things.  self explanatory. */
const int DEFAULT_LIBRARY_WINDOW_WIDTH = 18;

playmode DEFAULT_PLAYER_MODE = PLAYER_MODE_LOOP;
char *DEFAULT_PLAYER_PATH = "/usr/local/bin/mplayer";
char *DEFAULT_PLAYER_ARGS[] = { "mplayer", "-slave", "-idle", "-quiet", "-msglevel", "cplayer=0:ao=0:vo=0:decaudio=0:decvideo=0:demuxer=0", NULL };


/*
 * List of command-mode commands.  See input_handlers.h for cmd struct.
 * All of these functions are defined in input_handlers.*
 * XXX Note that commands that accept a '!' after their names are handled
 * in 'match_cmd_name' in input_handlers.c.  Also see that for handling of
 * abbreviations.
 * XXX Note that the '!' used to execute an external command is handled in
 * the enter_cmd_mode() function.
 */
const cmd CommandPath[] = {
   {  "bind",     cmd_bind },
   {  "color",    cmd_color },
   {  "display",  cmd_display },
   {  "filter",   cmd_filter },
   {  "mode",     cmd_mode },
   {  "new",      cmd_new },
   {  "q",        cmd_quit },
   {  "reload",   cmd_reload },
   {  "set",      cmd_set },
   {  "sort",     cmd_sort },
   {  "unbind",   cmd_unbind },
   {  "w",        cmd_write }
};
const int CommandPathSize = (sizeof(CommandPath) / sizeof(cmd));

#endif
