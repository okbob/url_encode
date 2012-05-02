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

	postgres=# select uri_encode('http://hu.wikipedia.org/wiki/São_Paulo');
	                 uri_encode                  
	---------------------------------------------
	 http://hu.wikipedia.org/wiki/S%C3%A3o_Paulo

	postgres=# select uri_decode('http://hu.wikipedia.org/wiki/S%C3%A3o_Paulo');
	               uri_decode               
	----------------------------------------
	 http://hu.wikipedia.org/wiki/São_Paulo
