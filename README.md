Whitenoise
==========

Sometimes jams are too dank, and I want to listen to some white noise.

Building
--------

```
$ make
```

Running
-------

```
$ ./whitenoise
```

This program uses [`sndio(7)`](http://man.openbsd.org/sndio)
as an audio interface. `Sndio` is the audio framework for
[OpenBSD](https://www.openbsd.org/), and has been ported to Linux,
FreeBSD, and NetBSD. See the [`sndio` homepage](http://www.sndio.org/)
and related man pages for more information.
