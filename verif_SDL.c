#include <SDL2/SDL.h>
#include <stdio.h>

/********************************************/
/* Vérification de l'installation de la SDL */
/********************************************/

int main(int argc, char **argv) {
  (void)argc;
  (void)argv;
  SDL_version nb;
  SDL_VERSION(&nb);

  printf("Version de la SDL : %d.%d.%d\n", nb.major, nb.minor, nb.patch);
  return 0;
}
