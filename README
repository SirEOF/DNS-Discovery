### Introduction

copy from https://github.com/m0nad/DNS-Discovery

DNS-Discovery is a multithreaded subdomain bruteforcer meant to be
used by pentesters during the initial stages of testing.
It uses a wordlist that concatenates with a given domain to search for
subdomains.

DNS-Discovery resolve and display IPv4 and IPv6.  It's similar to others
tools, like dnsmap, but multithreaded.
It was tested in GNU/Linux 2.6.38 and FreeBSD 8.1-STABLE.



### Compiling

$ make 

### Usage

usage: ./dns-discovery <domain> [options]
options:
	-w <wordlist file> (default : wordlist.wl)
	-t <threads> (default : 10000)
	-r <regular report file>
	-c <csv report file>

ex:
$ ./dns-discovery google.com -w wordlist -t 5 -r reportfile



### 我的修改

1、将默认线程数改为10000，并且添加了一些注释说明

2、【TODO】支持一次性跑多个域名

3、更新默认字典为大字典