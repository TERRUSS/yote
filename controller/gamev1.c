
#include <SDL2/SDL.h>
#include <stdio.h>

int main(int argc, char** argv)
{
	SDL_Window* pWindow = NULL;
	SDL_Event event;
	int cont=1;
	int i;
	int pospawnx = 95;
	int pospawny = 170;
	int pospawnxb = 642;
	int pospawnyb = 334;
	pWindow = SDL_CreateWindow("YOTE",SDL_WINDOWPOS_UNDEFINED,
															  SDL_WINDOWPOS_UNDEFINED,
															  780,
															  520,
															  SDL_WINDOW_SHOWN);

	if( pWindow )
	{
		SDL_Surface* pGamebg= SDL_LoadBMP("/home/user/yote/assets/graphics/board.bmp");
		SDL_Surface* redpawn= SDL_LoadBMP("/home/user/yote/assets/graphics/pionrouge.bmp");
		SDL_Surface* whitepawn= SDL_LoadBMP("/home/user/yote/assets/graphics/pionwhite.bmp");
		SDL_Surface* jaugered= SDL_LoadBMP("/home/user/yote/assets/graphics/jaugered.bmp");
		SDL_Surface* jaugewhite= SDL_LoadBMP("/home/user/yote/assets/graphics/jaugewhite.bmp");
		
		if ( pGamebg )
		{
			//Positionnement de plateau
			SDL_Rect dest = { 780/2 - pGamebg->w/2,520/2 - pGamebg->h/2, 0, 0};
			SDL_BlitSurface(pGamebg,NULL,SDL_GetWindowSurface(pWindow),&dest); 
			SDL_Rect destJsRed = {14,10, 0, 0};
			SDL_Rect destJswhite = { 750,346, 0, 0};
			SDL_BlitSurface(jaugered,NULL,SDL_GetWindowSurface(pWindow),&destJsRed); 
			SDL_BlitSurface(jaugewhite,NULL,SDL_GetWindowSurface(pWindow),&destJswhite); 
			//Positionnement de la reserve
			for(i=0;i<12;i++)
			{
			SDL_Rect destpawnr = { pospawnx,pospawny, 0, 0};
			SDL_Rect destpawnb = { pospawnxb,pospawnyb, 0, 0};
			SDL_BlitSurface(redpawn,NULL,SDL_GetWindowSurface(pWindow),&destpawnr);
			SDL_BlitSurface(whitepawn,NULL,SDL_GetWindowSurface(pWindow),&destpawnb);
			pospawnx=(pospawnx+20);
			pospawny=(pospawny-10); 
			pospawnxb=(pospawnxb-20);
			pospawnyb=(pospawnyb+10); 
			
			}
			
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
		// Libération de la ressource occupée par le sprite	
		SDL_FreeSurface(pGamebg);
		SDL_FreeSurface(redpawn);
		SDL_FreeSurface(whitepawn);
		SDL_FreeSurface(jaugered);
		SDL_FreeSurface(jaugewhite);
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
