
#include <SDL2/SDL.h>
#include <stdio.h>

typedef struct
{
	SDL_Surface* image;
	SDL_Rect position;
}img; //les pions,le plateau ect sont des objets de type image

#define TAILLE_OBJ 5 //nbr d'images qu'on a 

typedef int bool ;  //définition du type booléen,
#define false  0 /* affectation des valeurs conventionnelles*/,
#define true  1.

//fct ou on va load toutes les images d'objets
void load_objects(img* TabObj)
{
	TabObj[0].image = SDL_LoadBMP("/home/user/yote/assets/graphics/board.bmp");      //0:fond
	TabObj[1].image = SDL_LoadBMP("/home/user/yote/assets/graphics/pionrouge.bmp");  //1:pion rouge
	TabObj[2].image = SDL_LoadBMP("/home/user/yote/assets/graphics/pionwhite.bmp");  //2:pion blanc
	TabObj[3].image = SDL_LoadBMP("/home/user/yote/assets/graphics/jaugered.bmp");   //3:Jauge score rouge
	TabObj[4].image = SDL_LoadBMP("/home/user/yote/assets/graphics/jaugewhite.bmp"); //4:Jauge score blanche
	TabObj[4].image = SDL_LoadBMP("/home/user/yote/assets/graphics/jaugewhite.bmp"); //4:Jauge score blanche
	TabObj[5].image = SDL_LoadBMP("/home/user/yote/assets/graphics/lightredpawn.bmp"); //5:pion rouge highlighté 
}
// init les positions des objects
void init_pos_objects(img* TabObj)
{
    TabObj[0].position.x= 780/2 - TabObj[0].image->w/2;         //bg
    TabObj[0].position.y=520/2 - TabObj[0].image->h/2 ;						  
	TabObj[3].position.x=14;                                    //JAUGE SCORE ROUGE
	TabObj[3].position.y=10;
	TabObj[4].position.x=750;							        //Jauge score blanc
	TabObj[4].position.y=346;
}
//fct ou on va faire les blit 
void print_objects(img* TabObj,SDL_Rect* tabRed,SDL_Rect* tabWhite,SDL_Window* pWindow)
{
	int i;
	SDL_BlitSurface(TabObj[0].image,NULL,SDL_GetWindowSurface(pWindow),&(TabObj[0].position)); 
	SDL_BlitSurface(TabObj[3].image,NULL,SDL_GetWindowSurface(pWindow),&(TabObj[3].position)); 
	SDL_BlitSurface(TabObj[4].image,NULL,SDL_GetWindowSurface(pWindow),&(TabObj[4].position)); 
	//affichage de la reserve
	for(i=0;i<12;i++)
	{ 				
		SDL_BlitSurface(TabObj[1].image,NULL,SDL_GetWindowSurface(pWindow),&(tabRed[i]));
		SDL_BlitSurface(TabObj[2].image,NULL,SDL_GetWindowSurface(pWindow),&(tabWhite[i]));
	}
}

//tableau qui contient les pos init des pions(reserve)
void init_pos_reserve(SDL_Rect* reserveR,SDL_Rect* reserveW)
{
	int i;
	
	reserveR[0].x = 95; // pos du premier pion de la reserve rouge
    reserveR[0].y = 170; 
    reserveW[0].x = 642;// pos du premier pion de la reserve blanche
    reserveW[0].y = 334;

	for(i=1;i<12;i++) //pos reste des pions
	{
		reserveR[i].x=reserveR[i-1].x+20;
		reserveR[i].y=reserveR[i-1].y-10;
		reserveW[i].x=reserveW[i-1].x-20;
		reserveW[i].y=reserveW[i-1].y+10; 
	}
}

bool verif_mouse_pawn(int xmouse,int ymouse,SDL_Rect* tab) //verif si le cruseur est sur un pion 
{ 
	bool verif = 0;
	int i;
	for(i=0;i<12;i++)
	{
		if ((xmouse > tab[i].x && xmouse < tab[i].x+50) && (ymouse > tab[i].y && ymouse < tab[i].y+50))
		{
			//fprintf(stdout,"dessus!!\n");
			verif=true;
		}
	}
	return verif;
}

void liberation_memoire(img* TabObj)
{
	int i;
	for (i=0;i<TAILLE_OBJ;i++)
	{
		SDL_FreeSurface(TabObj[i].image);
	}
}

int main(int argc, char** argv)
{
	SDL_Window* pWindow = NULL;
	SDL_Event event;
	int cont=1;
	SDL_Rect tabRed[12];        //tableau contenant tt les pions rouges
	SDL_Rect tabWhite[12];		//tableau contenant tt les pions blancs
	img tobjects[TAILLE_OBJ];   //tab contenant tt les objets
	//objects
	img pGamebg;                //fond

	//init fenetre
 	pWindow = SDL_CreateWindow("YOTE",SDL_WINDOWPOS_UNDEFINED,
															  SDL_WINDOWPOS_UNDEFINED,
															  780,
															  520,
															  SDL_WINDOW_SHOWN);

	if( pWindow )
	{   //Initialisations
		load_objects(tobjects);
		init_pos_objects(tobjects);
		pGamebg= tobjects[0];
		init_pos_reserve(tabRed,tabWhite);
		//determination de la surface de la reserve 
		if ( pGamebg.image )
		{
			print_objects(tobjects,tabRed,tabWhite,pWindow);
			SDL_UpdateWindowSurface(pWindow);					 // Mise à jour de la fenêtre 

			while ( cont != 0 )									
			{
				int xmouse=0;                  						  //coordonées de la souris
				int ymouse=0;
				Uint32 boutons = SDL_GetMouseState(&xmouse,&ymouse);
				if (verif_mouse_pawn(xmouse,ymouse,tabRed)==true && boutons==1)
				{
					printf("t'as selectionné un pion rouge\n");
				}
				if (verif_mouse_pawn(xmouse,ymouse,tabWhite)==true && boutons==1)
				{
					printf("t'as selectionné un pion blanc\n");
				}
				
				while ( SDL_PollEvent(&event) )
				{
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
			liberation_memoire(tobjects);
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
