# QR-Gen
* Simple tool to encode text as a [QR Code](https://en.wikipedia.org/wiki/QR_code).
* Leverages [QR-Code-generator](https://github.com/nayuki/QR-Code-generator) as a submodule.

![Sample QR Code](qr.png)

## Requirements
* [libpng](http://www.libpng.org/pub/png/libpng.html) 1.6.0+
## Building
* Simply run `make`
## Usage
* `./qr-gen <"text"> [scale]`
* Output writes to `qr.png`