# checksum

[![Build Status](https://travis-ci.com/vikman90/checksum.svg?branch=master)](https://travis-ci.com/vikman90/checksum)
[![Coverage Status](https://coveralls.io/repos/github/vikman90/checksum/badge.svg?branch=master)](https://coveralls.io/github/vikman90/checksum?branch=master)

File checksum using Adler32 algorithm.

## Introduction

This project aims to compare the performance, pros and cons of reading a file as a stream or with mapped memory.

*Checksum* reads a file to calculate its Adler32 checksum. We can select the reading method:

- Open the file as a stream and read it into memory.
- Map the file into memory.

## Build

```
autoreconf -vi
./configure [ OPTIONS ]
make
```

### Optional features

|Feature|Description|
|---|---|
|`--disable-assert`|Turn off assertions.|
|`--enable-sanitize`|Enable AddressSanitizer.|
|`--enable-coverage`|Enable coverage test.|

### Environment variables

|Option|Description|Range|Default|
|---|---|---|---|
|`BLOCKSIZE`|Stream reader block size.|Positive number.|65536|

## Install

- Standard installation:

```
make install
```

- Optimize installation:

```
make install-strip
```

## Uninstall

```
make uninstall
```

## Clean project

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
|`-c`|Compare two files.|
|`-h`|Show help.|
|`-m`|Use memory mapping method.|
|`-s`|Use SHA-1 hash algorithm.|

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

### Version 0.3

|Method|500 MB file|1500 MB file|
|---|---|---|
|File streaming|0.682 s|2.076 s|
|Memory mapping|1.032 s|3.502 s|

### Version 0.4

Analyzing file comparison times.

#### Best case: different files

|Method|500 MB file|1500 MB file|
|---|---|---|
|File streaming|0.001 s|0.001 s|
|Memory mapping|1.073 s|3.436 s|

#### Worst case: similar files

|Method|500 MB file|1500 MB file|
|---|---|---|
|File streaming|0.482 s|1.845 s|
|Memory mapping|1.568 s|5.639 s|

## References

- Wikipedia: [Adler-32](https://en.wikipedia.org/wiki/Adler-32)
