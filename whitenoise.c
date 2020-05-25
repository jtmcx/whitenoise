#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sndio.h>

static void
usage(FILE *f, const char *argv0)
{
	fprintf(f, "usage: %s [-F device]\n", argv0);
}

static void
panic(const char *fmt, ...)
{
	va_list vl;
	va_start(vl, fmt);
	fprintf(stderr, "panic: ");
	vfprintf(stderr,  fmt, vl);
	fprintf(stderr, "\n");
	fprintf(stderr, "For more details, try running with SNDIO_DEBUG=2\n");
	va_end(vl);
	exit(1);
}

static void
init_sio(struct sio_hdl *sio)
{
	struct sio_par par;

	sio_initpar(&par);

	par.pchan = 1;       /* One channels */
	par.sig   = 0;       /* Unsigned samples */
	par.bits  = 8;
	par.le    = 1;
	par.rate  = 44100;

	/* Set parameters */
	if (sio_setpar(sio, &par) != 1)
		panic("failed to get audio parameters");

	/* Verify parameters */
	if (par.pchan != 1)
		panic("failed to set the number of channels");
	if (par.bits != 8)
		panic("Failed to set the sample precision");
	if (par.rate != 44100)
		panic("Failed to set the sample rate");
}

static void
whitenoise(struct sio_hdl *sio)
{
	int i;
	char buf[1024];

	for (;;) {
		for (i = 0; i < 1024; i++)
			buf[i] = rand() % 128;
		/* Since it's random data, we don't care if the write
		 * is truncated; no need to check the return value */
		sio_write(sio, buf, 1024);
	}
}

int
main(int argc, char *argv[])
{
	struct sio_hdl *sio;
	const char *device = SIO_DEVANY;
	char c;

	while ((c = getopt(argc, argv, "F:")) != -1) {
		switch (c) {
		case 'F':
			device = optarg;
			break;
		default:
			usage(stderr, argv[0]);
			exit(1);
		}
	}

	if ((sio = sio_open(device, SIO_PLAY, 0)) == NULL)
		panic("failed to open sndio device");

	init_sio(sio);

	if (sio_start(sio) != 1)
		panic("failed to start sndio");

	whitenoise(sio);

	if (sio_stop(sio) != 1)
		panic("failed to stop sndio");

	return 0;
}
