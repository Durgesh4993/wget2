/*
 * Copyright(c) 2012 Tim Ruehsen
 *
 * This file is part of MGet.
 *
 * Mget is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Mget is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Mget.  If not, see <http://www.gnu.org/licenses/>.
 *
 *
 * Header file for IRI/URI routines
 *
 * Changelog
 * 25.04.2012  Tim Ruehsen  created
 *
 * Resources:
 * RFC3986 / RFC3987
 *
 */

#ifndef _MGET_IRI_H
#define _MGET_IRI_H

#include <stddef.h>

typedef struct {
	const char
		*uri,      // pointer to original URI string
		*display,
		*scheme,
		*userinfo,
		*password,
		*host,
		*port,
		*path,
		*query,
		*fragment;
} IRI;

void
	iri_test(void),
	iri_free(IRI **iri);
int
	iri_isgendelim(char c),
	iri_issubdelim(char c),
	iri_isreserved(char c),
	iri_isunreserved(char c);
IRI
	*iri_parse(const char *s);
char
	*iri_get_connection_part(IRI *iri, char *tag, size_t tagsize),
	*iri_relative_to_absolute(IRI *iri, const char *tag, const char *val, size_t len, char *dst, size_t dst_size);

#endif /* _MGET_IRI_H */
