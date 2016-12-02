/*
 * Copyright(c) 2015-2016 Free Software Foundation, Inc.
 *
 * This file is part of libwget.
 *
 * Libwget is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Libwget is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with libwget.  If not, see <http://www.gnu.org/licenses/>.
 *
 *
 * Testing 'base' html tag
 *
 */

#if HAVE_CONFIG_H
# include <config.h>
#endif

#include <stdlib.h> // exit()
#include "libtest.h"

int main(void)
{
	wget_test_url_t urls[]={
		{	.name = "/1.txt",
			.code = "200 Dontcare",
			.body = "FFFFFFF4\nGarbage",
			.headers = {
				"Content-Type: text/plain",
				"Transfer-Encoding: chunked",
			}
		},
		{	.name = "/2.txt",
			.code = "200 Dontcare",
			.body = "FFFFFFF4\r\nGarbage",
			.headers = {
				"Content-Type: text/plain",
				"Transfer-Encoding: chunked",
			}
		},
		{	.name = "/3.txt",
			.code = "200 Dontcare",
			.body = "FFFFFFFFFFFFFFF4\r\nGarbage",
			.headers = {
				"Content-Type: text/plain",
				"Transfer-Encoding: chunked",
			}
		},
	};

	// functions won't come back if an error occurs
	wget_test_start_server(
		WGET_TEST_RESPONSE_URLS, &urls, countof(urls),
		0);

	// test negative chunk size (32bit system only)
	wget_test(
		WGET_TEST_KEEP_TMPFILES, 1,
		WGET_TEST_OPTIONS, "",
		WGET_TEST_REQUEST_URLS, "1.txt", "2.txt", "3.txt", NULL,
		WGET_TEST_EXPECTED_ERROR_CODE, 0,
		WGET_TEST_EXPECTED_FILES, &(wget_test_file_t []) {
			{ urls[0].name + 1, "" },
			{ urls[1].name + 1, "Garbage" },
			{ urls[2].name + 1, "Garbage" },
			{	NULL } },
		0);

	exit(0);
}
