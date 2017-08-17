CREATE EXTENSION url_encode;

SELECT url_encode('Hello World');
SELECT url_decode('Hello%20World');

SELECT url_encode(unnest) from unnest(string_to_array('http://hu.wikipedia.org/wiki/São_Paulo','/'));

SELECT uri_encode('http://hu.wikipedia.org/wiki/São_Paulo');
SELECT md5(uri_decode('http://hu.wikipedia.org/wiki/S%C3%A3o_Paulo'));

SELECT md5(url_decode('%u6D6A%u82B1%u4E00%u6735%u6735%20%u7B2C8%u96C6%20-%20%u89C6%u9891%u5728%u7EBF%u89C2%u770B%20-%20%u6D6A%u82B1%u4E00%u6735%u6735%20-%20%u8292%u679CTV'));
