# checksum
File checksum using Adler32 algorithm.

## Introduction

This project aims to compare the performance, pros and cons of reading a file as a stream or with mapped memory.

*Checksum* reads a file to calculate its Adler32 checksum. We can select the reading method:

- Open the file as a stream and read it into memory.
- Map the file into memory.

## Build

Just checkout this project and run `make`.

```
make [ BLOCKSIZE=x ]
```

|Option|Description|Range|Default|
|---|---|---|---|
|`BLOCKSIZE`|Stream reader block size.|Positive number.|65536|

### Clean project

```
make clean
```

## Run

```
checksum [ -h ] [ -m ] [ file ]
```

If no file specified or file "-" is given, checksum reads _stdin_.

|Option|Description|
|---|---|
|`-h`|Show help.|
|`-m`|Use memory mapping method.|

## Performance test

### Version 0.1

|Method|500 MB file|1500 MB file|
|---|---|---|
|File streaming|6.817 s|_Memory error._|
|Memory mapping|2.830 s|8.367 s|

### Version 0.2

|Method|500 MB file|1500 MB file|
|---|---|---|
|File streaming|2.366 s|7.483 s|
|Memory mapping|2.966 s|8.640 s|

## References

- Wikipedia: [Adler-32](https://en.wikipedia.org/wiki/Adler-32)
