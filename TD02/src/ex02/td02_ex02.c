#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/* Dimensions et titre de la fenetre */
static unsigned int WINDOW_WIDTH = 800;
static unsigned int WINDOW_HEIGHT = 800;
static const char WINDOW_TITLE[] = "TD02 Ex02";

/* Nombre de bits par pixel de la fenetre */
static const unsigned int BIT_PER_PIXEL = 32;

/* Nombre minimal de millisecondes separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;


void reshape(SDL_Surface** surface)
{
	SDL_Surface* surface_temp = SDL_SetVideoMode(
        WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, 
        SDL_OPENGL | SDL_RESIZABLE);
	if(NULL == surface_temp) 
	{
    	fprintf(
            stderr, 
            "Erreur lors du redimensionnement de la fenetre.\n");
    	return;
	}
	*surface = surface_temp;
	
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-5., 5., -5., 5.);
}

void drawOrigin(){
    glColor3ub(255, 0, 0);
    glBegin(GL_LINES);
    glVertex2f(0, 0);
    glVertex2f(1, 0);
    glColor3ub(0, 255, 0);
    glVertex2f(0, 0);
    glVertex2f(0, 1);
    // eventuellement d’autres points ...
    glEnd();
    //printf("Hello World\n");
}

void drawSquare(int full){
    if(full != 0 && full != 1) exit(EXIT_FAILURE);
    if (full == 1){
        glBegin(GL_QUADS);
    }
    else {
        glBegin(GL_LINE_LOOP);
    }
    

    glColor3ub(255, 255, 255);
    glVertex2f(-0.5, -0.5);
    glVertex2f(-0.5, 0.5);
    glVertex2f(0.5, 0.5);
    glVertex2f(0.5, -0.5);

    glEnd();
}

void drawCircle(int full){
    if(full != 0 && full != 1) exit(EXIT_FAILURE);
    if (full == 1){
        glBegin(GL_POLYGON);
    }
    else {
        glBegin(GL_LINE_STRIP);
    }

    glColor3ub(255, 255, 255);

    for ( float i = 0 ; i < 10 ; i=i+0.1){
        glVertex2f(cos(i), sin(i));
    }

    glEnd();
}



int main(int argc, char** argv) 
{
    /* Initialisation de la SDL */
    if(-1 == SDL_Init(SDL_INIT_VIDEO)) 
    {
        fprintf(
            stderr, 
            "Impossible d'initialiser la SDL. Fin du programme.\n");
        return EXIT_FAILURE;
    }
  
    /* Ouverture d'une fenetre et creation d'un contexte OpenGL */
    SDL_Surface* surface;
    surface = SDL_SetVideoMode(
        WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, 
        SDL_OPENGL | SDL_GL_DOUBLEBUFFER);
    if(NULL == surface) 
    {
        fprintf(
            stderr, 
            "Impossible d'ouvrir la fenetre. Fin du programme.\n");
        return EXIT_FAILURE;
    }

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-5., 5., -5., 5.);

    /* Initialisation du titre de la fenetre */
    SDL_WM_SetCaption(WINDOW_TITLE, NULL);
    
  
    /* Boucle principale */
    int loop = 1;
    while(loop) 
    {
        /* Recuperation du temps au debut de la boucle */
        Uint32 startTime = SDL_GetTicks();
        
        /* Placer ici le code de dessin */
        glClear(GL_COLOR_BUFFER_BIT);
        int full = 0;
        
        //drawCircle(1);
        drawOrigin();

        /* Echange du front et du back buffer : mise a jour de la fenetre */
        
        /* Boucle traitant les evenements */
        SDL_Event e;
        while(SDL_PollEvent(&e)) 
        {
            /* L'utilisateur ferme la fenetre : */
            if(e.type == SDL_QUIT) 
            {
                loop = 0;
                break;
            }

            /* L'utilisateur ferme la fenetre : */
			if(e.type == SDL_QUIT) 
			{
				loop = 0;
				break;
			}


		
			if(	e.type == SDL_KEYDOWN 
				&& (e.key.keysym.sym == SDLK_q || e.key.keysym.sym == SDLK_ESCAPE))
			{
				loop = 0; 
				break;
			}
            
            /* Quelques exemples de traitement d'evenements : */
            switch(e.type) 
            {
                /* Redimensionnement fenetre */
				case SDL_VIDEORESIZE:
					WINDOW_WIDTH = e.resize.w;
					WINDOW_HEIGHT = e.resize.h;
					reshape(&surface);
					break;

                /* Clic souris */
                case SDL_MOUSEBUTTONUP:
                    printf("clic en (%d, %d)\n", e.button.x, e.button.y);
                    break;
                
                /* Touche clavier */
                case SDL_KEYDOWN:
                    printf("touche pressee (code = %d)\n", e.key.keysym.sym);
                    if (e.key.keysym.sym == SDLK_s) {
                        drawSquare(full);
                        SDL_GL_SwapBuffers();
                    }
                    if (e.key.keysym.sym == SDLK_c) {
                        drawCircle(full);
                        SDL_GL_SwapBuffers();
                    }
                    break;
                    
                default:
                    break;
            }
        }

        /* Calcul du temps ecoule */
        Uint32 elapsedTime = SDL_GetTicks() - startTime;
        /* Si trop peu de temps s'est ecoule, on met en pause le programme */
        if(elapsedTime < FRAMERATE_MILLISECONDS) 
        {
            SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
        }
    }

    /* Liberation des ressources associees a la SDL */ 
    SDL_Quit();
    
    return EXIT_SUCCESS;
}
