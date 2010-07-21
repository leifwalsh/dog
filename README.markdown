dog
===

the inverse of `cat`

SYNOPSIS
--------

Writes everything it receives on standard in to a temp file, and prints the name
of that file.

USAGE
-----

Any options are an error.  Use like this:

    % firefox $(cat /var/log/messages | my_html_generator.pl | dog)

BUGS
----

There are none.  Really, try to find one.  I'll bake you some cookies if you
find one.

TODO
----

* Implement as a fifo, not a temp file.
* Find a better use of my time.

AUTHORS
-------

* Leif Walsh <leif.walsh@gmail.com>

COPYING
-------

Do whatever you want.
