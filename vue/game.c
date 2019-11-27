#include "header.h"

void print_pawn(int x, int y){
  SDL_Texture* pTexture = SDL_CreateTextureFromSurface(renderer, pawn_sprite); // Préparation du pawn_sprite

  if ( pTexture ) {
    SDL_Rect dest = { x, y, SPRITE_WIDTH, SPRITE_WIDTH};

    SDL_RenderCopy(renderer, pTexture, NULL, &dest); // Copie du pawn_sprite grâce au SDL_Renderer

    SDL_DestroyTexture(pTexture); // Libération de la mémoire associée à la texture

  } else {
    IGE_log(IGE_STEP_ERROR, SDL_GetError());
  }
}

void IGE_displayBoard(int * board, int w, int h){
  IGE_log(IGE_LOGGING_TASK, "Displaying Board");

  for (int j = 0; j < h; ++j) {
    for (int i = 0; i < w; ++i) {
      print_pawn(10+SPRITE_WIDTH*i + j*SPRITE_WIDTH/2 , 10+(SPRITE_WIDTH*j/1.4));
    }
  }

  IGE_log(IGE_FINISHED_TASK, "Ok");
}

void IGE_backgroundColor(r, g, b){
  SDL_SetRenderDrawColor(renderer, r, b, b, 255);
  SDL_Rect rectangle;

  rectangle.x = 0;
  rectangle.y = 0;
  rectangle.w = 800;
  rectangle.h = 600;
  SDL_RenderFillRect(renderer, &rectangle);
}

void IGE_init(){
  IGE_log(IGE_LOGGING_TASK, "Starting Initialisation");
  window = 0;

  if(SDL_Init(SDL_INIT_VIDEO) < 0){
    IGE_log(IGE_LOGGING_STEP, "Window Creation ERROR : ");
    IGE_quit();
  } else {
    IGE_log(IGE_LOGGING_STEP, "Window Created");
  }

  window = SDL_CreateWindow("Yoté", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if ( renderer ) {
    IGE_log(IGE_LOGGING_STEP, "Renderer Created");
  } else {
    IGE_log(IGE_LOGGING_STEP, "Renderer Creation ERROR : ");
    IGE_log(IGE_STEP_ERROR, SDL_GetError());
    IGE_quit();
  }

  pawn_sprite = IMG_Load("./assets/block/block.png");
  if ( pawn_sprite ) {
    IGE_log(IGE_LOGGING_STEP, "Asset Loaded");
    SDL_Delay(50);
  } else {
    IGE_log(IGE_LOGGING_STEP, "Loading assets ERROR : ");
    IGE_log(IGE_STEP_ERROR, SDL_GetError());
    IGE_quit();
  }

  IGE_log(IGE_FINISHED_TASK, "Initialisation Completed");
}

void IGE_render(){
  SDL_RenderPresent(renderer); // Affichage
}

void IGE_quit(){
  SDL_FreeSurface(pawn_sprite); // Libération de la ressource occupée par le sprite
  SDL_DestroyRenderer(renderer); // Libération de la mémoire du SDL_Renderer

  SDL_DestroyWindow(window);
  SDL_Quit();
}

void IGE_log(int importance, const char* message){

  switch(importance){
    case IGE_LOGGING_TASK:
      print_label("[IGE INTERNAL]", BOLD);
      printf(" === %s ===\n", message);
    break;
    case IGE_LOGGING_STEP:
      print_label("[IGE INTERNAL]", BOLD);
      printf("    %s\n", message);
    break;
    case IGE_STEP_ERROR:
      print_label("[IGE INTERNAL ERROR]", ERROR);
      printf(" %s\n", message);
    break;
    case IGE_FINISHED_TASK:
      print_label("[IGE INTERNAL]", BOLD);
      printf(" --- %s ---\n\n", message);
    break;
  }

  return;
}

void print_label(const char * label, int display){
  switch(display){
    case BOLD:
      printf("\033[1;32m%s\033[0m", label);
    break;
    case ERROR:
      printf("\033[1;31m%s\033[0m", label);
    break;
  }
}
