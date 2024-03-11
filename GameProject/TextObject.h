#ifndef TEXT_OBJECT_H
#define TEXT_OBJECT_H


#include "BaseObject.h"



class TextObject : public BaseObject
{
public:
	TextObject();
	~TextObject();
	void SetText(const std::string& text) { str_val = text; }
	void SetColor_W() { text_color = {255 , 255, 255}; }
	void SetColor_R() { text_color = { 255 , 153, 153 }; }



	bool LoadText(std::string path, SDL_Renderer* screen);

private:
	std::string str_val;
	SDL_Color text_color;


	
};
#endif // !TEXT_OBJECT_H

