# checksum
File checksum using Adler32 algorithm

## Introduction

This project aims to compare the performance, pros and cons of reading a file as a stream or with mapped memory.

*Checksum* reads a file to calculate its Adler32 checksum. We can select the reading method:

- Open the file as a stream and read it into memory.
- Map the file into memory.

## Build

Just checkout this project and run `make`.

## Run

```
checksum [ -h ] [ -m ] <file>
```

|Option|Description|
|---|---|
|`-h`|Show help.|
|`-m`|Use memory mapping method.|

## Performance test

1. 500 MB file checksum.

|Method|Time|
|---|---|
|File streaming|6.817 s|
|Memory mapping|2.830 s|

2. 1.5 GB file checksum.

|Method|Time|
|---|---|
|File streaming|_Memory error._|
|Memory mapping|8.367 s|

## References

- Wikipedia: [Adler-32](https://en.wikipedia.org/wiki/Adler-32)
