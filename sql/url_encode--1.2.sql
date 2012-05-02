/* contrib/url_encode/url_encode--1.2.sql */

-- complain if script is sourced in psql, rather than via CREATE EXTENSION
\echo Use "CREATE EXTENSION url_encode" to load this file. \quit

---------------------------------------------------
CREATE FUNCTION url_encode(text)
	RETURNS text
	AS 'MODULE_PATHNAME'
	LANGUAGE C
	IMMUTABLE STRICT;
CREATE FUNCTION url_decode(text)
	RETURNS text
	AS 'MODULE_PATHNAME'
	LANGUAGE C
	IMMUTABLE STRICT;

CREATE FUNCTION uri_encode(text)
	RETURNS text
	AS 'MODULE_PATHNAME'
	LANGUAGE C
	IMMUTABLE STRICT;
CREATE FUNCTION uri_decode(text)
	RETURNS text
	AS 'MODULE_PATHNAME'
	LANGUAGE C
	IMMUTABLE STRICT;
