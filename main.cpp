#include <SDL2/SDL.h>
#include <iostream>
#include <cmath>

class Kvadrat {
    int a, x, y;
    Uint8 r,g,b;

public:
    Kvadrat();
    Kvadrat(int);
    int get_a();
    int get_x();
    int get_y();
    void add_x(int);
    void add_y(int);
    void setColor(SDL_Renderer*);
    void refreshCoords(SDL_Rect&);
};

// class methods definitions
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
Kvadrat::Kvadrat() { a = 50; r = 255, g = b = 0; x = y = 300; }
Kvadrat::Kvadrat(int a) { this->a = a; r = 255, g = b = 0; x = y = 20; }
int Kvadrat::get_a() { return a; }
int Kvadrat::get_x() { return x; }
int Kvadrat::get_y() { return y; }
void Kvadrat::add_x(int x) { this->x += x; }
void Kvadrat::add_y(int y) { this->y += y; }
void Kvadrat::setColor(SDL_Renderer *renderer) { SDL_SetRenderDrawColor(renderer, r, g, b, 255); }
void Kvadrat::refreshCoords(SDL_Rect &rect) {
    rect.x = this->x;
    rect.y = this->y;
    if(rect.x < -1) rect.x = 1;
    if(rect.x+a > 801) rect.x = 800-a-1;
    if(rect.y < -1) rect.y = 1;
    if(rect.y+a > 601) rect.y = 600-a-1;
}

// other functions definitions
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-

void resetColor(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
}

void update_movement(SDL_Rect &rect, int dest_x, int dest_y) {
    int distance_x = dest_x - (rect.x + rect.w/2),
        distance_y = dest_y - (rect.y + rect.h/2);// glede na sredino pravokotnika
    double angle = atan2(distance_y, distance_x) * 180.0 / M_PI;
    std::cout << "Kot je " << angle << "deg\n";
}

int main(int argc, char *argv[]) {
    const int w = 800, h = 600;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Nou okn", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);
    if(window == nullptr) {
        std::cout << "Failed to open the window: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == nullptr) {
        std::cout << "Failed to create the renderer: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }
    
    Kvadrat kvadrat;
    SDL_Rect pravokotnik;
    pravokotnik.w = kvadrat.get_a();
    pravokotnik.h = kvadrat.get_a();


    bool quit = false;
    SDL_Event kb_event, w_event; //keyboard event, window event
    // main loop
    const Uint8 *stanja_tipk = nullptr;
    while(!quit) {
        while(SDL_PollEvent(&w_event)) { //check events
            if(w_event.type == SDL_QUIT) {
                std::cout << "Exiting the program...\n";
                quit = true;
            }
            else if(w_event.type == SDL_MOUSEBUTTONDOWN) {
                if(w_event.button.button == SDL_BUTTON_LEFT) {
                    int mouse_x, mouse_y;
                    SDL_GetMouseState(&mouse_x, &mouse_y);
                    printf("x: %d, y: %d\n", mouse_x, mouse_y);
                    update_movement(pravokotnik, mouse_x, mouse_y);
                }
            }
        }
    	kvadrat.refreshCoords(pravokotnik);

        //modra barva za ozadje
        resetColor(renderer);
        SDL_RenderClear(renderer);
        //rdeca barva za kvadrat
        kvadrat.setColor(renderer);
        SDL_RenderFillRect(renderer, &pravokotnik);
        SDL_RenderPresent(renderer);

        SDL_Delay(1);
    } 


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}



/*
? KEYBOARD MOVEMENT
        stanja_tipk = SDL_GetKeyboardState(nullptr);

        if(stanja_tipk[SDL_SCANCODE_W]) {
            kvadrat.add_y(-1);
        }
        if(stanja_tipk[SDL_SCANCODE_A]) {
            kvadrat.add_x(-1);
        }
        if(stanja_tipk[SDL_SCANCODE_S]) {
            kvadrat.add_y(1);
        }
        if(stanja_tipk[SDL_SCANCODE_D]) {
            kvadrat.add_x(1);
        }
        if(stanja_tipk[SDL_SCANCODE_Q]) {
            quit = true;
        } 
*/