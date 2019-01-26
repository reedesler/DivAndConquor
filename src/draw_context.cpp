//
// Created by Dmitry on 2019-01-25.
//

#include "draw_context.h"

DrawContext::DrawContext(SDL_Renderer *Renderer) : Renderer(Renderer) {


}

void DrawContext::clear(SDL_Color color) {
    SDL_SetRenderDrawColor(this->Renderer, color.r, color.g, color.b,color.a);
    SDL_RenderClear(this->Renderer);
}

void DrawContext::present() {
    SDL_RenderPresent(this->Renderer);
}

void DrawContext::drawTexture(SDL_Texture *tex, SDL_Rect *src, SDL_Rect *dest) {
    SDL_RenderCopy(this->Renderer, tex,src, dest);
}

void DrawContext::drawLine(int x1, int y1, int x2, int y2, SDL_Color color) {
    SDL_SetRenderDrawColor(this->Renderer, color.r, color.g, color.b,color.a);
    SDL_RenderDrawLine(this->Renderer,x1,y1,x2,y2);
}

void DrawContext::drawRect(SDL_Rect *rect, SDL_Color color) {
    SDL_SetRenderDrawColor(this->Renderer, color.r, color.g, color.b,color.a);
    SDL_RenderDrawRect(this->Renderer,rect);
}
