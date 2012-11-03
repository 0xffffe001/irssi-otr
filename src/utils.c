/*
 * Off-the-Record Messaging (OTR) modules for IRC
 *
 * Copyright (C) 2008  Uli Meis <a.sporto+bee@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 51
 * Franklin Street, Fifth Floor, Boston, MA 02110-1301,USA
 */

#include <string.h>

#include "otr.h"
#include "utils.h"

void utils_io_explode_args(const char *args, char ***argvp, char ***argv_eolp,
		int *argcp)
{
	char **argv, **argv_eol;
	char *s = (char *) args;
	int argc = 1, i;

	while ((s = strchr(s + 1, ' '))) {
		argc++;
	}

	argv = (char **) malloc(argc * sizeof(char *));
	argv_eol = (char **) malloc(argc * sizeof(char *));

	s = (char *) args;
	argv_eol[0] = strdup(args);
	i = 0;

	while (++i < argc) {
		argv_eol[i] = strchr(argv_eol[i - 1], ' ') + 1;
	}

	argv[0] = strtok(strdup(args), " ");
	i = 1;
	while (i < argc) {
		argv[i++] = strtok(NULL, " ");
		otr_logst(MSGLEVEL_CRAP, "arg %d: %s", i, argv[i - 1]);
	}

	*argvp = argv;
	*argv_eolp = argv_eol;
	*argcp = argc;
}