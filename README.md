# get_next_line

Une fonction en C permettant de lire le contenu d'un descripteur de fichier ligne par ligne, de manière efficace et avec une taille de tampon configurable.

## Présentation

`get_next_line` lit un descripteur de fichier (`fd`) et retourne une ligne à chaque appel, incluant le caractère de retour à la ligne (`\n`) lorsqu'il est présent. L'état de lecture est conservé entre deux appels grâce à une variable statique (`stash`), ce qui permet de lire aussi bien des fichiers que l'entrée standard (`stdin`).

Le projet propose deux versions :
- **Version standard** : gestion d'un descripteur de fichier à la fois.
- **Version multi-descripteurs (`bonus`)** : gestion simultanée de plusieurs descripteurs de fichiers (jusqu'à `4096`), permettant d'alterner les lectures entre plusieurs fichiers sans perdre le fil de chaque lecture.

## Prototype

```c
char *get_next_line(int fd);
```

### Paramètre
- `fd` : le descripteur de fichier depuis lequel lire.

### Valeur de retour
- La ligne lue (allouée dynamiquement avec `malloc`), terminée par `\n` si présent.
- `NULL` lorsque la fin du fichier est atteinte ou qu'une erreur survient.

> **Gestion de la mémoire** : chaque ligne retournée est allouée sur le tas. L'appelant est responsable de la libérer avec `free()`.

## Structure du projet

| Fichier | Description |
| --- | --- |
| `get_next_line.h` | En-tête de la version standard (prototypes et définition par défaut de `BUFFER_SIZE`) |
| `get_next_line.c` | Implémentation principale pour un descripteur de fichier |
| `get_next_line_utils.c` | Fonctions utilitaires (`ft_strlen`, `ft_strchr`, `ft_strdup`, `ft_strjoin`, `ft_calloc`) |
| `get_next_line_bonus.h` | En-tête de la version multi-descripteurs |
| `get_next_line_bonus.c` | Implémentation supportant jusqu'à 4096 descripteurs simultanés |
| `get_next_line_utils_bonus.c` | Fonctions utilitaires pour la version multi-descripteurs |

## Fonctionnement interne

1. **Lecture par blocs (`ft_get_all`)** : lit depuis `fd` par morceaux de `BUFFER_SIZE` octets et concatène les données dans `stash` jusqu'à rencontrer un `\n` ou atteindre la fin du fichier.
2. **Extraction de la ligne (`ft_cut_end`)** : isole et retourne la ligne courante (jusqu'au `\n` inclus).
3. **Conservation du reste (`ft_get_end`)** : met à jour `stash` avec les caractères restants après le `\n` pour l'appel suivant, ou libère `stash` s'il ne reste rien.

## Compilation

La taille du tampon (`BUFFER_SIZE`) vaut `1` par défaut et peut être redéfinie à la compilation avec l'option `-D`.

### Version standard

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=64 main.c get_next_line.c get_next_line_utils.c -o gnl
```

### Version multi-descripteurs

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=64 main.c get_next_line_bonus.c get_next_line_utils_bonus.c -o gnl_bonus
```

## Exemples d'utilisation

### Lecture d'un fichier

```c
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

int main(void)
{
    int     fd;
    char    *line;

    fd = open("exemple.txt", O_RDONLY);
    if (fd < 0)
        return (1);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

### Lecture simultanée de plusieurs fichiers (version bonus)

```c
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line_bonus.h"

int main(void)
{
    int     fd1;
    int     fd2;
    char    *line1;
    char    *line2;

    fd1 = open("fichier1.txt", O_RDONLY);
    fd2 = open("fichier2.txt", O_RDONLY);
    if (fd1 < 0 || fd2 < 0)
        return (1);
    line1 = get_next_line(fd1);
    line2 = get_next_line(fd2);
    if (line1)
    {
        printf("Fichier 1 : %s", line1);
        free(line1);
    }
    if (line2)
    {
        printf("Fichier 2 : %s", line2);
        free(line2);
    }
    close(fd1);
    close(fd2);
    return (0);
}
```

## Prérequis

- Un compilateur C compatible POSIX (`cc`, `gcc` ou `clang`)
- Bibliothèques standard C/POSIX (`<unistd.h>`, `<stdlib.h>`, `<stdio.h>`)
