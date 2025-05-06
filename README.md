# 🚀 CrazyPNG Library=

**CrazyPNG** est un décompresseur PNG léger, écrit en **C**, sans aucune dépendance externe. Parfait pour comprendre le format PNG et expérimenter l’algorithme DEFLATE tout en gardant le contrôle total sur le code !

---

## ✨ Fonctionnalités

* 🔍 **Parsing** complet des chunks PNG : IHDR, PLTE, IDAT, IEND, etc.
* 🎨 **Support couleur** : grayscale, RGB, palette, grayscale+alpha, RGBA
* ⚙️ **Décompression DEFLATE** (LZ77 + Huffman) conforme au RFC-1951
* 🏗️ **Flux bit-à-bit** et gestion de buffers personnalisés
* 📚 **Libft** intégrée pour les utilitaires (chaînes, mémoire, listes…)

## 🛠️ Prérequis

* **Compilateur C** (GCC, Clang…)
* **Make**
* **Linux** ou **macOS**

## 🚀 Installation rapide

```bash
# 1. Cloner le dépôt
git clone https://github.com/votre-utilisateur/crazypng.git
cd crazypng

# 2. (Optionnel) Compiler libft
cd libft && make && cd ..

# 3. Compiler le projet
make
```

## 🎯 Utilisation

```bash
# Décompresse un PNG
./crazypng path/to/image.png
```

Le programme analyse le fichier, décompresse les données IDAT et restitue les pixels dans un buffer interne : idéal pour vos tests ou pipelines de traitement d’images.

## 📂 Structure du dépôt

```
CrazyPNG/
├── test_files/         # Ressources graphiques pour les tests
├── includes/           # En-têtes (bitstream, deflate, huffman, png, utils)
├── libft/              # Bibliothèque utilitaire personnelle
├── src/                # Code source principal
│   ├── bitstream/      # Lecture bit-à-bit
│   ├── deflate/        # LZ77 + Huffman
│   ├── huffman/        # Tables et décodage
│   ├── png/            # Parsing et orchestration
│   └── utils/          # Helpers (buffers, fichiers)
├── test_main.c         # Exemple de tests
├── Makefile            # Règles de compilation
├── deflate_doc.txt     # Documentation DEFLATE
└── to_do               # Prochaines améliorations
```

## 📜 Licence

Distribué sous la licence **MIT**. Consulte le fichier [LICENSE](LICENSE) pour plus de détails.

---
