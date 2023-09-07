#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <png.h>

#include "qrcodegen.h"

int main(int argc, char ** argv) {
    if (argc != 2 && argc != 3) {
        fprintf(stderr, "usage: %s <\"text\"> [scale]\n", argv[0]);
        return 1;
    }

    uint8_t qrcode[qrcodegen_BUFFER_LEN_MAX];
    uint8_t temp[qrcodegen_BUFFER_LEN_MAX];

    bool success = qrcodegen_encodeText(argv[1], temp, qrcode, qrcodegen_Ecc_LOW,
        qrcodegen_VERSION_MIN, qrcodegen_VERSION_MAX, qrcodegen_Mask_AUTO, true);

    if (!success) {
        fprintf(stderr, "failed to encode text\n");
        return 2;
    }

    int qrSize = qrcodegen_getSize(qrcode);

    int scale = 8;
    if (argc == 3) {
        int arg = atoi(argv[2]);

        if (arg <= 0) {
            fprintf(stderr, "invalid scale, defaulting to %d\n", scale);
        } else {
            scale = arg;
        }
    }

    png_image image = { 0 };
    image.version = PNG_IMAGE_VERSION;
    image.format = PNG_FORMAT_GRAY;
    image.width = scale * (2 + qrSize);
    image.height = scale * (2 + qrSize);

    png_bytep texels = malloc(PNG_IMAGE_SIZE(image));

    for (int i = 0; i < scale; ++i) {
        memset(texels + i * image.width, 0xff, image.width);
        memset(texels + i * image.width + image.width * (image.height - scale), 0xff, image.width);
    }

    for (png_uint_32 row = scale, y = 0; row < image.height - scale; row += scale, ++y) {
        for (int r = 0; r < scale; ++r) {
            memset(texels + (row + r) * image.width, 0xff, scale);
            memset(texels + (row + r + 1) * image.width - scale, 0xff, scale);
        }

        for (png_uint_32 col = scale, x = 0; col < image.width - scale; col += scale, ++x) {
            bool isFilled = qrcodegen_getModule(qrcode, x, y);

            for (int r = 0; r < scale; ++r) {
                for (int c = 0; c < scale; ++c) {
                    texels[(row + r) * image.width + col + c] = isFilled ? 0 : 0xff;
                }
            }
        }
    }

    png_image_write_to_file(&image, "qr.png", 0, texels, 0, NULL);
    free(texels);

    return 0;
}