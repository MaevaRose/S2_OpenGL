#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>

/* Dimensions de la fenetre */
static unsigned int WINDOW_WIDTH = 400;
static unsigned int WINDOW_HEIGHT = 400;

/* Nombre de bits par pixel de la fenetre */
static const unsigned int BIT_PER_PIXEL = 32;

/* Nombre minimal de millisecondes separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 5000 / 60;

typedef struct point_link {
    int x, y; // Position 2D du point
    unsigned char r, g, b; // Couleur du point
    struct point_link *next; // Suivant
} Point, *PointList;


Point* allocPoint(int x, int y, unsigned char r, unsigned char g, unsigned char b){
    Point *point = malloc(sizeof(*point));
    if(point == NULL){
        exit(EXIT_FAILURE);
    }

    point->x=x;
    point->y=y;
    point->r=r;
    point->g=g;
    point->b=b;
    //point->next=NULL;

    return point;
}

void deletePoints(PointList* list) {
     Point *temp;
     Point *temp2;
     temp2=(*list);
     while (temp2 != NULL) {
        temp=(*list)->next;
        free(*list);
        temp2=temp;
    }
}

void addPoint(Point* point, PointList* list) {

    PointList temp = (*list);
    if (*list == NULL) {
        printf("Oh bonjour !\n");
        (*list)=point;
        (*list)->next=NULL;
        return ;
    }
    while((*list)->next != NULL){
        (*list)=(*list)->next;
    }

    point->next=NULL;
    (*list)->next=point;
    (*list)=temp;


}

void drawPoints(PointList list) {
    while(list != NULL){
        glColor3ub(list->r, list->g, list->b);
        
        glVertex2f(
           -1 + 2. * list->x / WINDOW_WIDTH,
           -(-1 + 2. * list->y / WINDOW_HEIGHT));
        list=list->next;
    }
    
}

typedef struct primitive_link {
    GLenum primitiveType; // Type de primitive
    PointList points; // Liste des vertex
    struct primitive_link *next; // Suivant
} Primitive, *PrimitiveList;


Primitive* allocPrimitive(GLenum primitiveType) {
    Primitive *primitive = malloc(sizeof(*primitive));
    if(primitive == NULL){
        exit(EXIT_FAILURE);
    }

    primitive->points=NULL;
    primitive->primitiveType=primitiveType;
    primitive->next=NULL;

    return primitive;
}

void deletePrimitives(PrimitiveList* list) {
     Primitive *temp;
     Primitive *temp2;
     temp2=(*list);
     while (temp2 != NULL) {
        temp=(*list)->next;
        free(*list);
        temp2=temp;
    }
}

void addPrimitive(Primitive* primitive, PrimitiveList* list) {


    if ((*list) == NULL) {
        (*list)=primitive;
        primitive->next=NULL;
        return ;
    }

    primitive->next=(*list);
    (*list)=primitive;

}

void drawPrimitives(PrimitiveList list) {

     while(list != NULL){
        glBegin(list->primitiveType);
        drawPoints(list->points);
        list=list->next;
        glEnd();
    }
}

void reshape(SDL_Surface** surface) {
    SDL_Surface* surface_temp = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE);
    if(NULL == surface_temp) {
        fprintf(stderr,"Erreur lors du redimensionnement de la fenetre.\n");
        exit(EXIT_FAILURE);
    }
    *surface = surface_temp;
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1., 1., -1., 1.);
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
        SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_RESIZABLE);
    if(NULL == surface) 
    {
        fprintf(
            stderr, 
            "Impossible d'ouvrir la fenetre. Fin du programme.\n");
        return EXIT_FAILURE;
    }

    
    
    SDL_WM_SetCaption("Hello", 0);
    glClear(GL_COLOR_BUFFER_BIT);

    PrimitiveList listeprimitives = allocPrimitive(GL_POINTS);
    Point *point;
    Primitive* primitive; 
    /*Primitive *currentprim = allocPrimitive(GL_POINTS);
    addPrimitive(currentprim, &listeprimitives);*/


    /* Boucle principale */
    int loop = 1;
    while(loop)  
    {
        /* Recuperation du temps au debut de la boucle */
        Uint32 startTime = SDL_GetTicks();
        
        /* Placer ici le code de dessin */
        /*void draw(int x, int y, int v, int b){
            glColor3ub(255, v, b);
            glBegin(GL_POINTS);
            glVertex2f(
                -1 + 2. * x / WINDOW_WIDTH,
                -(-1 + 2. * y / WINDOW_HEIGHT));
            // eventuellement d’autres points ...
            glEnd();
        }*/
        glClear(GL_COLOR_BUFFER_BIT);
        drawPrimitives(listeprimitives);
        
        /* Echange du front et du back buffer : mise a jour de la fenetre */
        SDL_GL_SwapBuffers();
        //glClear(GL_COLOR_BUFFER_BIT);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 0);

        
        /* Boucle traitant les evenements */
        SDL_Event e;
        while(SDL_PollEvent(&e)) 
        {

            //glClear(GL_COLOR_BUFFER_BIT);
            /* L'utilisateur ferme la fenetre : */
            if(e.type == SDL_QUIT) 
            {
                loop = 0;
                break;
            }
            
            /* Quelques exemples de traitement d'evenements : */
            switch(e.type) 
            {
                /* Clic souris */
                case SDL_MOUSEBUTTONUP:
                    printf("clic en (%d, %d)\n", e.button.x, e.button.y);
                    point = allocPoint(e.button.x, e.button.y, 255, 255, 255);
                    printf("%d %d %c %c %c\n", e.button.x, e.button.y, 255, 255, 255);
                    addPoint(point, &listeprimitives->points);
                    
                    
                    //glClearColor((e.button.x%255)/255.0, (e.button.y%255)/255.0, 0, 1);
                    //draw(e.button.x, e.button.y, 0, 0);
                    break;

                /* Mouvement souris */
                case SDL_MOUSEMOTION:
                    //glClearColor((e.motion.x%surface->w), 0, (e.motion.y%surface->h), 1);
                    //draw(e.motion.x, e.motion.y, (e.motion.x%255), (e.motion.y%255));
                    break;
                
                /* Touche clavier */
                case SDL_KEYDOWN: 
                    if (e.key.keysym.sym == SDLK_q) exit(EXIT_SUCCESS);
                    if (e.key.keysym.sym == SDLK_p) {
                        primitive = allocPrimitive(GL_POINTS);
                       addPrimitive(primitive, &listeprimitives);
                    }
                    if (e.key.keysym.sym == SDLK_l) {
                        primitive = allocPrimitive(GL_LINES);
                        addPrimitive(primitive, &listeprimitives);
                    }
                    if (e.key.keysym.sym == SDLK_t) {
                        primitive = allocPrimitive(GL_TRIANGLES);
                       addPrimitive(primitive, &listeprimitives);
                    }
                 

                    printf("touche pressee (code = %d)\n", e.key.keysym.sym);
                    break;

                case SDL_VIDEORESIZE:
                    WINDOW_HEIGHT=e.resize.h;
                    WINDOW_WIDTH=e.resize.w;
                    reshape(&surface);
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

    
    deletePoints(&listeprimitives->points);
    deletePrimitives(&listeprimitives);

    /* Liberation des ressources associees a la SDL */ 
    SDL_Quit();
    
    return EXIT_SUCCESS;
}
