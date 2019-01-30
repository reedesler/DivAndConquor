//
// Created by Dmitry on 2019-01-25.
//

#include "draw_context.h"

DrawContext::DrawContext(SDL_Renderer* Renderer, int xScale, int yScale) : Renderer(Renderer), xScale(xScale),
                                                                           yScale(yScale) {
}

void DrawContext::clear(SDL_Color color) {
    SDL_SetRenderDrawColor(this->Renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(this->Renderer);
}

void DrawContext::present() {
    SDL_RenderPresent(this->Renderer);
}

void DrawContext::drawTexture(SDL_Texture* tex, SDL_Rect* src, SDL_Rect* dest) {
    SDL_RenderCopy(this->Renderer, tex, src, dest);
}

void DrawContext::drawLine(int x1, int y1, int x2, int y2, SDL_Color color) {
    SDL_SetRenderDrawColor(this->Renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawLine(this->Renderer, x1, y1, x2, y2);
}

void DrawContext::drawRect(SDL_Rect rect, SDL_Color color) {
    SDL_Rect screenRect = screenToPixel(rect);
    SDL_SetRenderDrawColor(this->Renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(this->Renderer, &screenRect);
}

void DrawContext::setViewport(SDL_Rect rect) {
    SDL_Rect screenRect = screenToPixel(rect);
    SDL_RenderSetViewport(this->Renderer, &screenRect);
}

SDL_Point DrawContext::screenToPixel(SDL_Point p) {
    return {p.x * xScale, p.y * yScale};
}

SDL_Rect DrawContext::screenToPixel(SDL_Rect r) {
    SDL_Point pos = {r.x, r.y};
    SDL_Point screenPos = screenToPixel(pos);
    SDL_Point wh = {r.w, r.h};
    SDL_Point screenWH = screenToPixel(wh);
    return {screenPos.x, screenPos.y, screenWH.x, screenWH.y};
}
