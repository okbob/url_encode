CREATE EXTENSION url_encode;

SELECT url_encode('Hello World');
SELECT url_decode('Hello%20World');

SELECT url_encode(unnest) from unnest(string_to_array('http://hu.wikipedia.org/wiki/São_Paulo','/'));
