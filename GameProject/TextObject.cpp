#include "TextObject.h"



TextObject::TextObject()
{
    str_val = "";
    text_color = { 255, 255 ,255 };
}

TextObject ::~TextObject()
{

}

bool TextObject :: LoadText(std::string path, SDL_Renderer* screen)
{
    TTF_Font* font = TTF_OpenFont(path.c_str(), 24); // Thay đổi đường dẫn và kích thước font theo nhu cầu

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, str_val.c_str(), text_color);
    if (textSurface == nullptr) {
        return false;
    }

    p_object_ = SDL_CreateTextureFromSurface(screen, textSurface);
    SDL_FreeSurface(textSurface);
    return true;
}