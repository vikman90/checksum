# June 2, 2019
# make [ options ] [ all ]  Compile sources.
# make clean                Clean binary and objects.
#   Options:
#     BLOCKSIZE             Block size for stream reader.

DEFINES = -D_XOPEN_SOURCE -D_DEFAULT_SOURCE
CFLAGS = -O2 -std=c99 -pipe -Wall -Wextra $(DEFINES)
LFLAGS = -O2

ifdef BLOCKSIZE
CFLAGS += -DBLOCKSIZE="$(BLOCKSIZE)"
endif

TARGET = checksum
SOURCES = $(wildcard src/*.c)
OBJECTS = $(SOURCES:.c=.o)
HEADERS = $(wildcard src/*.h)

all: $(TARGET)

clean:
	$(RM) $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(LFLAGS) -o $@ $^

$(OBJECTS): $(HEADERS)
