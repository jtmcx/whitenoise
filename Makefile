TARGET  = whitenoise
OFILES  = whitenoise.o
CFLAGS  = -std=c89 -pedantic -Wall -Werror -D_DEFAULT_SOURCE
LDFLAGS = -lsndio

$(TARGET): $(OFILES)
	$(CC) -o $@ $(LDFLAGS) $(OFILES)

clean:
	rm -f $(TARGET) $(OFILES)
