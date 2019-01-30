///
// Created by Dmitry on 2019-01-25.
//

#ifndef DIVCONQ_DRAWCONTEXT_H
#define DIVCONQ_DRAWCONTEXT_H

#include <SDL.h>

class DrawContext {
public:
    SDL_Renderer *Renderer;

    explicit DrawContext(SDL_Renderer *Renderer);

    void clear(SDL_Color color);

    void present();

    void drawTexture(SDL_Texture *tex, SDL_Rect *src, SDL_Rect *dest);

    void drawLine(int x1, int y1, int x2, int y2, SDL_Color color);

    void drawRect(SDL_Rect *rect, SDL_Color color);
};


#endif //DIVCONQ_DRAWCONTEXT_H
