# 🚀 crazypng

**crazypng** est une bibliothèque C minimaliste pour charger des images PNG et accéder directement aux pixels RGBA 8 bits, sans dépendances externes hormis la libc et **libft**.

---

## ✨ Caractéristiques clés

* ✅ Validation automatique de la signature PNG
* ✅ Extraction des métadonnées (dimensions, profondeur, type de couleur)
* ✅ Accès direct à un tableau de pixels RGBA 8 bits
* ✅ API publique réduite à deux fonctions simples

---

## 📦 Prérequis

| Outil | Version minimale | Commentaire          |
| ----- | ---------------- | -------------------- |
| gcc   | 4.8+             | Compatible C99       |
| make  | —                |                      |
| libft | —                | Inclus dans le dépôt |

---

## 🔧 Installation

```bash
# 1. Cloner le dépôt
git clone https://github.com/<utilisateur>/crazypng.git
cd crazypng

# 2. Compiler la bibliothèque
make
```

> Le build génère :
>
> * **libcrazypng.a** : bibliothèque statique
> * **libft.a**       : utilitaires

---

## 🛠️ API publique

Définie dans `includes/crazypng.h` :

```c
#include "crazypng.h"

// Ouvre un fichier PNG et initialise la structure interne
t_png *png_open(const char *file_name);

// Ferme et libère la structure PNG
void png_close(t_png *png);
```

Après `png_open()`, accès à :

```c
// Metadata
uint32_t width      = img->header.width;
uint32_t height     = img->header.height;
uint8_t  bit_depth  = img->header.bit_depth;
uint8_t  color_type = img->header.color_type;

// Pixels RGBA 8 bits (tableau de size width*height)
t_png_pixel8 *pixels = img->pixels_8bit;
```

---

## 🖼️ Exemple simple

```c
#include "crazypng.h"
#include <stdio.h>

int main(void) {
    // Charger l'image
    t_png *img = png_open("image.png");
    if (!img) {
        fprintf(stderr, "⚠️ Échec de l'ouverture du PNG\n");
        return 1;
    }

    // Récupérer dimensions
    uint32_t w = img->header.width;
    uint32_t h = img->header.height;

    // Sauvegarder le flux brut RGBA dans un fichier
    FILE *out = fopen("out.rgba", "wb");
    fwrite(img->pixels_8bit, sizeof(*img->pixels_8bit), w * h, out);
    fclose(out);

    // Libérer
    png_close(img);
    return 0;
}
```

---

## 🧪 Tests

Placez un fichier de test `image.png` puis compilez simplement :

```bash
gcc test.c -lcrazypng -lft -o test_png
./test_png
```

---

## 📜 Licence

Ce projet est sous licence **MIT**. Voir [LICENSE](LICENSE) pour plus de détails.
