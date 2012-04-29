CREATE EXTENSION url_encode;

SELECT url_encode('Hello World');
SELECT url_decode('Hello%20World');