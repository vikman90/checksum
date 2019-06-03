# June 2, 2019
# make [ options ] [ all ]  Compile sources.
# make clean                Clean binary and objects.
#   Options:
#     BLOCKSIZE             Block size for stream reader.
#     DEBUG                 Enable debug mode.

DEFINES = -D_XOPEN_SOURCE -D_DEFAULT_SOURCE
CFLAGS = -std=c99 -pipe $(DEFINES)

ifdef BLOCKSIZE
CFLAGS += -DBLOCKSIZE="$(BLOCKSIZE)"
endif

ifdef DEBUG
CFLAGS += -g -Wall -Wextra
else
CFLAGS += -DNDEBUG -O2
LFLAGS += -O2
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
