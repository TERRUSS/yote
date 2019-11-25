#include "header.h"

void print_pawn(SDL_Window* pWindow){
  SDL_Renderer *pRenderer = SDL_CreateRenderer(pWindow,-1,SDL_RENDERER_ACCELERATED); // Création d'un SDL_Renderer utilisant l'accélération matérielle
  SDL_SetRenderDrawColor(pRenderer, 255, 0, 0, 255);

  if ( pRenderer ) {
    SDL_Surface* pSprite = IMG_Load("./assets/block/block.png");

    if ( pSprite ) {
      SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer,pSprite); // Préparation du sprite

      if ( pTexture ) {
        SDL_Rect dest = { 640/2 - pSprite->w/2,480/2 - pSprite->h/2, pSprite->w, pSprite->h};
        SDL_RenderCopy(pRenderer, pTexture, NULL, &dest); // Copie du sprite grâce au SDL_Renderer
        SDL_RenderPresent(pRenderer); // Affichage
        printf("debut\n");
        SDL_Delay(3000); /* Attendre trois secondes, que l'utilisateur voit la fenêtre */
        printf("fin\n");
        SDL_DestroyTexture(pTexture); // Libération de la mémoire associée à la texture

      } else {
        fprintf(stdout,"[SDL CreateTextureFromSurface] (%s)\n",SDL_GetError());
      }

      SDL_FreeSurface(pSprite); // Libération de la ressource occupée par le sprite

    } else {
      fprintf(stdout,"[SDL LoadBMP] (%s)\n",SDL_GetError());
    }

    SDL_DestroyRenderer(pRenderer); // Libération de la mémoire du SDL_Renderer

  } else {
    fprintf(stdout,"Échec de création du renderer (%s)\n",SDL_GetError());
  }
}
