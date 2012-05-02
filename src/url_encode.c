/*-------------------------------------------------------------------------
 *
 * url_encode
 *	  PostgreSQL functions for url code support
 *
 * Author:	Pavel Stehule
 * Portions Copyright (c) 1996-2012, PostgreSQL Global Development Group
 *
 * IDENTIFICATION
 *	  contrib/url_encode/url_encode.c
 *
 *-------------------------------------------------------------------------
 */

#include "postgres.h"

#include "fmgr.h"
#include "mb/pg_wchar.h"
#include "utils/builtins.h"


PG_MODULE_MAGIC;

PG_FUNCTION_INFO_V1(url_encode);
PG_FUNCTION_INFO_V1(url_decode);
PG_FUNCTION_INFO_V1(uri_encode);
PG_FUNCTION_INFO_V1(uri_decode);

Datum url_encode(PG_FUNCTION_ARGS);
Datum url_decode(PG_FUNCTION_ARGS);
Datum uri_encode(PG_FUNCTION_ARGS);
Datum uri_decode(PG_FUNCTION_ARGS);


static const char *hex_chars = "0123456789ABCDEF";

static const int8 hexlookup[128] = {
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, -1, -1, -1, -1, -1, -1,
	-1, 10, 11, 12, 13, 14, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, 10, 11, 12, 13, 14, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
};

static inline unsigned char
get_hex(char c)
{
	int			res = -1;

	if (c > 0 && c < 127)
		res = hexlookup[(unsigned char) c];

	if (res < 0)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 errmsg("invalid hexadecimal digit: \"%c\"", c)));

	return (char) res;
}

static text *
encode(text *in_text, const char *unreserved_special)
{
	int	   len;
	text		*result;
	char		*read_ptr;
	char		*write_ptr;
	int		real_len;
	int	processed;
	int				i;

	len = VARSIZE(in_text) - VARHDRSZ;
	read_ptr = VARDATA(in_text);

	/* preallocation max 3 times of size */
	result = (text *) palloc(sizeof(3 * len) + VARHDRSZ);
	write_ptr = VARDATA(result);
	processed = 0;
	real_len = 0;
	while (processed < len)
	{
		int mblen = pg_mblen(read_ptr);

		if (mblen == 1)
		{
			char	c = *read_ptr;

			if ((c >='0' && c <= '9') ||
			    (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
			    (strchr(unreserved_special, c) != NULL))
			    //(c == '.' || c == '-' || c == '~' || c == '_'))
			{
				*write_ptr++ = c;
				real_len += 1;
				processed += 1;
				read_ptr += 1;

				continue;
			}
		}

		for (i = 0; i < mblen; i++)
		{
			unsigned char b = ((unsigned char *) read_ptr)[i];

			*write_ptr++ = '%';
			*write_ptr++ = hex_chars[(b >> 4) & 0xF];
			*write_ptr++ = hex_chars[b & 0xF];
			real_len += 3;
		}

		processed += mblen;
		read_ptr += mblen;
	}

	SET_VARSIZE(result, real_len + VARHDRSZ);

	return result;
}

static text *
decode(text *in_text, const char *unreserved_special)
{
	text	   *result;
	char		*read_ptr = VARDATA(in_text);
	char		*write_ptr;
	int		len =VARSIZE(in_text) - VARHDRSZ;
	int		real_len;
	int		processed;

	real_len = 0;
	result = (text *) palloc(len + VARHDRSZ);
	write_ptr = VARDATA(result);

	processed = 0;
	while (processed < len)
	{
		if (*read_ptr != '%')
		{
			char	c = *read_ptr;

			if ((c >='0' && c <= '9') ||
			    (c >= 'a' && c <= 'z') ||
			    (c >= 'A' && c <= 'Z') ||
			    (strchr(unreserved_special, c) != NULL))
			{
				*write_ptr++ = c;
				real_len += 1;
				processed += 1;
				read_ptr += 1;
			}
			else
				elog(ERROR, "unaccepted chars in url code");
		}
		else
		{
			/* next two chars should be utf8 digits */
			if (processed + 3 > len)
				elog(ERROR, "incomplete input string");

			*((unsigned char *) write_ptr++) = (get_hex(read_ptr[1]) << 4) | get_hex(read_ptr[2]);
			real_len += 1;
			processed += 3;
			read_ptr += 3;
		}
	}

	SET_VARSIZE(result, real_len + VARHDRSZ);

	return result;
}


/*
 * encode input string to url encode
 *
 */
Datum
url_encode(PG_FUNCTION_ARGS)
{
	PG_RETURN_TEXT_P(encode(PG_GETARG_TEXT_P(0), ".-~_"));
}

/*
 * decode input string from url encode
 *
 */
Datum
url_decode(PG_FUNCTION_ARGS)
{
	PG_RETURN_TEXT_P(decode(PG_GETARG_TEXT_P(0), ".-~_"));
}

Datum
uri_encode(PG_FUNCTION_ARGS)
{
	PG_RETURN_TEXT_P(encode(PG_GETARG_TEXT_P(0), ".-~_/?:@&=+$#"));
}

Datum
uri_decode(PG_FUNCTION_ARGS)
{
	PG_RETURN_TEXT_P(decode(PG_GETARG_TEXT_P(0), ".-~_/?:@&=+$#"));
}
