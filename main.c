#include "header.h"
#include "vue/header.h"

int main(void) {

  //axe(x) & axe(y)
  int plateau[6][5] = {0};

  IGE_init();

  IGE_displayBoard((int*)plateau, 6, 5);

  IGE_render();
  SDL_Delay(5000);

  IGE_quit();

  return 0;
}
