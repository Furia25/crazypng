## 🏞️ crazypng

**crazypng** is a minimalist C library for loading PNG images and directly accessing 8-bit RGBA pixels, with no external dependencies other than the C standard library.

---

## ✨ Key Features

* ✅ Automatic PNG signature validation
* ✅ Metadata extraction (dimensions, bit depth, color type)
* ✅ Direct access to an 8-bit RGBA pixel array
* ✅ Public API reduced to two simple functions

---

## 📦 Prerequisites

| Tool  | Minimum Version | Notes            |
| ----- | --------------- | ---------------- |
| gcc   | 4.8+            | C99-compatible   |
| make  | —               |                  |
| libft | —               | Included in repo |

---

## 🔧 Installation

```bash
# 1. Clone the repository
$ git clone https://github.com/Furia25/crazypng.git
$ cd crazypng

# 2. Build the library
$ make
```

> The build produces:
>
> * **libcrazypng.a** : static library
> * **libft.a**       : utility library

---

## 🛠️ Public API

Defined in `includes/crazypng.h`:

```c
#include "crazypng.h"

// Opens a PNG file and initializes internal structures
t_png *png_open(const char *file_name);

// Closes and frees the PNG structure
void png_close(t_png *png);
```

After calling `png_open()`, you can access:

```c
// Metadata
uint32_t width      = img->header.width;
uint32_t height     = img->header.height;
uint8_t  bit_depth  = img->header.bit_depth;
uint8_t  color_type = img->header.color_type;

// 8-bit RGBA pixels (array of length width*height)
t_png_pixel8 *pixels = img->pixels_8bit;
```

---

## 🖼️ Simple Example

```c
#include "crazypng.h"
#include <stdio.h>

int main(void) {
    // Load the image
    t_png *img = png_open("image.png");
    if (!img) {
        fprintf(stderr, "⚠️ Failed to open PNG\n");
        return 1;
    }

    // Get dimensions
    uint32_t w = img->header.width;
    uint32_t h = img->header.height;

    // Write the raw RGBA stream to a file
    FILE *out = fopen("out.rgba", "wb");
    fwrite(img->pixels_8bit, sizeof(*img->pixels_8bit), w * h, out);
    fclose(out);

    // Free resources
    png_close(img);
    return 0;
}
```

---

## 🧪 Testing

Place a test file named `image.png` then compile:

```bash
$ gcc test.c -lcrazypng -lft -o test_png
$ ./test_png
```

---

## 📜 License

This project is licensed under the **MIT** License. See [LICENSE](LICENSE) for details.
