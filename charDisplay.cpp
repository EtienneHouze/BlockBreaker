#include <SDL2/SDL.h>
#include <vector>
#include<string>

/**
 * @brief A small usefull 7-segment display.
 * 
 */
namespace charDisplay{

    /**
     * @brief Display a single character.
     * 
     * @param renderer a pointer to the SDL renderer.
     * @param rect A pointer to ther rectangle in which the char will be displayed
     * @param toWrite the character to write.
     */
    void display_char_in_rect(SDL_Renderer* renderer, SDL_Rect* rect, char toWrite){
        SDL_Rect top,top_right,top_left,bottom,bottom_right,bottom_left,middle;
        top = SDL_Rect();
        top.x = rect->x;
        top.y = rect->y;
        top.w = rect->w;
        top.h = (rect->h)*0.2;
        middle = SDL_Rect(top);
        middle.y += (rect->h)*(0.4);
        bottom = SDL_Rect(top);
        bottom.y += (rect->h)*(0.85);
        top_left = SDL_Rect(top);
        top_left.h = (rect->h)*0.5;
        top_left.w = (rect->h)*0.22;
        top_right = SDL_Rect(top_left);
        top_right.x += (rect->w)*(0.75);
        bottom_left = SDL_Rect(top_left);
        bottom_left.y += (rect->h)*0.5;
        bottom_right = SDL_Rect(bottom_left);
        bottom_right.x += (rect->w)*(0.75);
        switch (toWrite)
        {
            case '0':
                SDL_RenderFillRect(renderer,&top);
                SDL_RenderFillRect(renderer,&bottom_right);
                SDL_RenderFillRect(renderer,&top_right);
                SDL_RenderFillRect(renderer,&top_left);
                SDL_RenderFillRect(renderer,&bottom_left);
                SDL_RenderFillRect(renderer,&bottom);
                break;
            case '1':
                SDL_RenderFillRect(renderer,&top_right);
                SDL_RenderFillRect(renderer,&bottom_right);
                break;
            case '2':
                SDL_RenderFillRect(renderer,&top);
                SDL_RenderFillRect(renderer,&top_right);
                SDL_RenderFillRect(renderer,&middle);
                SDL_RenderFillRect(renderer,&bottom_left);
                SDL_RenderFillRect(renderer,&bottom);
                break;
            case '3':
                SDL_RenderFillRect(renderer,&top);
                SDL_RenderFillRect(renderer,&top_right);
                SDL_RenderFillRect(renderer,&middle);
                SDL_RenderFillRect(renderer,&bottom_right);
                SDL_RenderFillRect(renderer,&bottom);
                break;
            case '4':
                SDL_RenderFillRect(renderer,&top_left);
                SDL_RenderFillRect(renderer,&top_right);
                SDL_RenderFillRect(renderer,&middle);
                SDL_RenderFillRect(renderer,&bottom_right);
                break;
            case '5':
                SDL_RenderFillRect(renderer,&top);
                SDL_RenderFillRect(renderer,&top_left);
                SDL_RenderFillRect(renderer,&middle);
                SDL_RenderFillRect(renderer,&bottom_right);
                SDL_RenderFillRect(renderer,&bottom);
                break;
            case '6':
                SDL_RenderFillRect(renderer,&top);
                SDL_RenderFillRect(renderer,&top_left);
                SDL_RenderFillRect(renderer,&middle);
                SDL_RenderFillRect(renderer,&bottom_left);
                SDL_RenderFillRect(renderer,&bottom_right);
                SDL_RenderFillRect(renderer,&bottom);
                break;
            case '7':
                SDL_RenderFillRect(renderer,&top);
                SDL_RenderFillRect(renderer,&top_right);
                SDL_RenderFillRect(renderer,&bottom_right);
                break;
            case '8':
                SDL_RenderFillRect(renderer,&top);
                SDL_RenderFillRect(renderer,&top_left);
                SDL_RenderFillRect(renderer,&top_right);
                SDL_RenderFillRect(renderer,&middle);
                SDL_RenderFillRect(renderer,&bottom_left);
                SDL_RenderFillRect(renderer,&bottom_right);
                SDL_RenderFillRect(renderer,&bottom);
                break;
            case '9':
                SDL_RenderFillRect(renderer,&top);
                SDL_RenderFillRect(renderer,&top_left);
                SDL_RenderFillRect(renderer,&top_right);
                SDL_RenderFillRect(renderer,&middle);
                SDL_RenderFillRect(renderer,&bottom_right);
                SDL_RenderFillRect(renderer,&bottom);
                break;
            case 'O':
                SDL_RenderFillRect(renderer,&top);
                SDL_RenderFillRect(renderer,&bottom_right);
                SDL_RenderFillRect(renderer,&top_right);
                SDL_RenderFillRect(renderer,&top_left);
                SDL_RenderFillRect(renderer,&bottom_left);
                SDL_RenderFillRect(renderer,&bottom);
                break;
            case 'S':
                SDL_RenderFillRect(renderer,&top);
                SDL_RenderFillRect(renderer,&top_left);
                SDL_RenderFillRect(renderer,&middle);
                SDL_RenderFillRect(renderer,&bottom_right);
                SDL_RenderFillRect(renderer,&bottom);
                break;
            case 'C':
                SDL_RenderFillRect(renderer,&top);
                SDL_RenderFillRect(renderer,&top_left);
                SDL_RenderFillRect(renderer,&bottom_left);
                SDL_RenderFillRect(renderer,&bottom);
                break;
            case 'R':
                SDL_RenderFillRect(renderer,&top);
                SDL_RenderFillRect(renderer,&top_left);
                SDL_RenderFillRect(renderer,&top_right);
                SDL_RenderFillRect(renderer,&middle);
                SDL_RenderFillRect(renderer,&bottom_left);
                SDL_RenderFillRect(renderer,&bottom_right);
                break;
            case 'E' :
                SDL_RenderFillRect(renderer,&top);
                SDL_RenderFillRect(renderer,&top_left);
                SDL_RenderFillRect(renderer,&middle);
                SDL_RenderFillRect(renderer,&bottom_left);
                SDL_RenderFillRect(renderer,&bottom);
                break;
            case '-':
                SDL_RenderFillRect(renderer,&middle);
            default:
                break;
        }
    }

    /**
     * @brief Given the right most position, writes in it and return a rectangle containing the whole text.
     * 
     * @param renderer 
     * @param rightMost 
     * @param text 
     * @return SDL_Rect 
     */
    void display_from_right(SDL_Renderer* renderer, SDL_Rect* rightMost,std::string text){
        double spacing = 0.5 * rightMost->w;
        int lengthOfText = text.size();
        std::vector<SDL_Rect> allRects = std::vector<SDL_Rect>(lengthOfText,SDL_Rect());
        allRects[lengthOfText-1] = SDL_Rect(*rightMost);
        for (int i = lengthOfText -2; i >= 0; --i){
            allRects[i].w = allRects[i+1].w;
            allRects[i].h = allRects[i+1].h;
            allRects[i].x = allRects[i+1].x - allRects[i+1].w - spacing;
            allRects[i].y = allRects[i+1].y;
        }
        SDL_SetRenderDrawColor(renderer,0xFF,0xFF,0xFF,0xFF);
        for (int i = 0; i < lengthOfText; ++i){
            display_char_in_rect(renderer,&(allRects[i]),text[i]);
        }
    }

    void display_from_left(SDL_Renderer* renderer, SDL_Rect* leftMost,const std::string& text){
        double spacing = 0.5 * leftMost->w;
        int lengthOfText = text.size();
        std::vector<SDL_Rect> allRects = std::vector<SDL_Rect>(lengthOfText,SDL_Rect());
        allRects[0] = SDL_Rect(*leftMost);
        for (int i = 1; i < lengthOfText; ++i){
            allRects[i].w = allRects[i-1].w;
            allRects[i].h = allRects[i-1].h;
            allRects[i].x = allRects[i-1].x + allRects[i-1].w + spacing;
            allRects[i].y = allRects[i-1].y;
        }
        for (int i = 0; i < lengthOfText; ++i){
            display_char_in_rect(renderer,&(allRects[i]),text[i]);
        }
    }
}



