#include "header.h"

void print_pawn(SDL_Window* pWindow){
	SDL_Renderer *pRenderer = SDL_CreateRenderer(pWindow,-1,SDL_RENDERER_ACCELERATED); // Création d'un SDL_Renderer utilisant l'accélération matérielle
	// SDL_SetRenderDrawColor(pRenderer, 255, 0, 0, 255);

	if ( pRenderer ) {
		SDL_Surface* pSprite = IMG_Load("./assets/block/block.png");
		printf("Sprite : w=%d, d=%d, dest = %dx%d\n", pSprite->w, pSprite->h, 800/2 - pSprite->w/2,600/2 - pSprite->h/2);
		SDL_Delay(50);

		if ( pSprite ) {
			SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pSprite); // Préparation du sprite

			if ( pTexture ) {
				SDL_Rect dest = { 800/2 - pSprite->w/2, 600/2 - pSprite->h/2, pSprite->w, pSprite->h};

				SDL_RenderCopy(pRenderer, pTexture, NULL, &dest); // Copie du sprite grâce au SDL_Renderer
				SDL_RenderPresent(pRenderer); // Affichage

				printf("debut\n");
				SDL_Delay(1000); /* Attendre trois secondes, que l'utilisateur voit la fenêtre */
				printf("fin\n");

				SDL_DestroyTexture(pTexture); // Libération de la mémoire associée à la texture

			} else {
				fprintf(stdout,"[SDL CreateTextureFromSurface] (%s)\n",SDL_GetError());
			}

			SDL_FreeSurface(pSprite); // Libération de la ressource occupée par le sprite

		} else {
			fprintf(stdout,"[SDL Load Sprite] (%s)\n",SDL_GetError());
		}

		SDL_DestroyRenderer(pRenderer); // Libération de la mémoire du SDL_Renderer

	} else {
		fprintf(stdout,"[SDL Renderer] (%s)\n",SDL_GetError());
	}
}
