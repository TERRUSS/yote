
#include <SDL2/SDL.h>
#include <stdio.h>

int main(int argc, char** argv)
{
	SDL_Window* pWindow = NULL;
	SDL_Event event;
	int cont=1;
	pWindow = SDL_CreateWindow("YOTE",SDL_WINDOWPOS_UNDEFINED,
															  SDL_WINDOWPOS_UNDEFINED,
															  780,
															  520,
															  SDL_WINDOW_SHOWN);

	if( pWindow )
	{
		SDL_Surface* pSprite = SDL_LoadBMP("board.bmp");
		if ( pSprite )
		{
			//Positionnement de plateau
			SDL_Rect dest = { 780/2 - pSprite->w/2,520/2 - pSprite->h/2, 0, 0};
			SDL_BlitSurface(pSprite,NULL,SDL_GetWindowSurface(pWindow),&dest); 
			SDL_UpdateWindowSurface(pWindow); // Mise à jour de la fenêtre 
			
			 while ( cont != 0 )
			{
				while ( SDL_PollEvent(&event) )
				{
					/* Traitement de l'événement */
					switch (event.type) 
					{
						case SDL_QUIT: // Clic sur la croix
						cont = 0;
						break;
						case SDL_KEYDOWN:
					  
							if ( event.key.keysym.scancode == SDL_SCANCODE_ESCAPE )
							{
								cont = 0;
							}
							break;
					}
				}
			}
			
		SDL_FreeSurface(pSprite); // Libération de la ressource occupée par le sprite
		}
		else
		{
			fprintf(stdout,"Échec de chargement du sprite (%s)\n",SDL_GetError());
		}
		
	SDL_DestroyWindow(pWindow); // Destruction de la fenêtre
	}
	else
	{
			fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());
	}
	SDL_Quit();

		return 0;
}
