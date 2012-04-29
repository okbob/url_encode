url_encode
==========

url_encode, url_decode functions for PostgreSQL

## Instalation
* Compile
* CREATE EXTENSION url_encode


## Usage

	CREATE EXTENSION url_encode;
	CREATE EXTENSION
	
	postgres=# SELECT url_encode('Ahoj Světe'), url_encode('Hello World');
	    url_encode     │  url_encode   
	───────────────────┼───────────────
	 Ahoj%20Sv%C4%9Bte │ Hello%20World
	(1 row)
	
	 postgres=# SELECT url_decode('Ahoj%20Sv%C4%9Bte'), url_decode('Hello%20World');
	 url_decode │ url_decode  
	────────────┼─────────────
	 Ahoj Světe │ Hello World
	(1 row)

	postgres=# with x as (select url_encode(unnest(string_to_array('http://hu.wikipedia.org/wiki/São_Paulo','/'))))
				select string_agg(url_encode, '/') from x;
	                  string_agg                   
	───────────────────────────────────────────────
	http%3A//hu.wikipedia.org/wiki/S%C3%A3o_Paulo

	postgres=# select url_encode('http://hu.wikipedia.org/wiki/São_Paulo');
	                      url_encode                       
	───────────────────────────────────────────────────────
	 http%3A%2F%2Fhu.wikipedia.org%2Fwiki%2FS%C3%A3o_Paulo
