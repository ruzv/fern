#include <stdio.h>
#include <stdlib.h>

const int char_width = 8;
const int char_height = 16;

typedef struct CHARECTER_IMAGE {
    int pixel_width, pixel_height;
    int img_width, img_height;
    int* img;
} chr_img;

chr_img new_chr_img(int w, int h) {
    chr_img img;

    img.pixel_width = w;
    img.pixel_height = h;

    img.img_width = (img.pixel_width / char_width) + 1;
    img.img_height = (img.pixel_height / char_height) + 1;

    img.img = malloc(sizeof(int) * img.img_width * img.img_height);

    for (int i=0; i<img.img_width * img.img_height; i++) {
        img.img[i] = 0;
    }

    return img;
}

void plot(chr_img* img, int x, int y) {
    x /= char_width;
    y /= char_height;

    if (x < 0 || x >= img->img_width) {
        return;
    }

    if (y < 0 || y >= img->img_height) {
        return;
    }

    if (img->img[(y * img->img_width) + x] >= 9) {
        return;
    }

    img->img[(y * img->img_width) + x] += 1;
}

void print(chr_img* img) {
    char* steps =  " .:-=+*#%@";

    for (int y=0; y<img->img_height; y++) {
        for (int x=0; x<img->img_width; x++) {
            putc(steps[img->img[(y*img->img_width) + x]], stdout);
        }

        putc('\n', stdout);
    }
}

double random_double() {
    return (double)rand() / (double)RAND_MAX;
}

int main(int argc, char const* argv[]) {
    chr_img img = new_chr_img(500, 1020);

    double scale = 100;
    double x = 0;
    double y = 0;

    double nx, ny, r;

    for (int i=0; i<15000; i++) {
        plot(&img, 235 + (int)(x * scale),  (int)(y * scale));

        r = random_double();

        if (r < 0.01) {
            nx =  0;
            ny =  0.16 * y;
        } else if (r < 0.86) {
            nx =  0.85 * x + 0.04 * y;
            ny = -0.04 * x + 0.85 * y + 1.6;
        } else if (r < 0.93) {
            nx =  0.20 * x - 0.26 * y;
            ny =  0.23 * x + 0.22 * y + 1.6;
        } else {
            nx = -0.15 * x + 0.28 * y;
            ny =  0.26 * x + 0.24 * y + 0.44;
        }

        x = nx;
        y = ny;
    }

    print(&img);

    free(img.img);

    return 0;
}
