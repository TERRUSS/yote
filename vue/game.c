#include "header.h"

void print_pawn(){
	SDL_Renderer *pRenderer = SDL_CreateRenderer(pWindow,-1,SDL_RENDERER_ACCELERATED); // Création d'un SDL_Renderer utilisant l'accélération matérielle
	if ( pRenderer )
	{
		SDL_Surface* pSprite = SDL_LoadBMP("./data/dvp.bmp");
		if ( pSprite )
		{
			SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer,pSprite); // Préparation du sprite
			if ( pTexture )
			{
				SDL_Rect dest = { 640/2 - pSprite->w/2,480/2 - pSprite->h/2, pSprite->w, pSprite->h};
				SDL_RenderCopy(pRenderer,pTexture,NULL,&dest); // Copie du sprite grâce au SDL_Renderer
				
				SDL_RenderPresent(pRenderer); // Affichage
				SDL_Delay(3000); /* Attendre trois secondes, que l'utilisateur voit la fenêtre */
				
				SDL_DestroyTexture(pTexture); // Libération de la mémoire associée à la texture
			}
			else
			{
				fprintf(stdout,"Échec de création de la texture (%s)\n",SDL_GetError());
			}
			
			SDL_FreeSurface(pSprite); // Libération de la ressource occupée par le sprite
		}
		else
		{
			fprintf(stdout,"Échec de chargement du sprite (%s)\n",SDL_GetError());
		}
		
		SDL_DestroyRenderer(pRenderer); // Libération de la mémoire du SDL_Renderer
	}
	else
	{
		fprintf(stdout,"Échec de création du renderer (%s)\n",SDL_GetError());
	}
}