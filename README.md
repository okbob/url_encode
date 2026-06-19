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

# Licence

Copyright (c) Pavel Stehule (pavel.stehule@gmail.com)

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.

# Note

If you like it, send a postcard to address

    Pavel Stehule
    Skalice 12
    256 01 Benesov u Prahy
    Czech Republic


I invite any questions, comments, bug reports, patches on mail address pavel.stehule@gmail.com
