#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class TextDraw
{
public:
	TextDraw()
	{
		if (!font.loadFromFile("TextFiles\\ARIBL0.ttf"))
		{
			cerr << "Error loading font" << endl;
		}

		text.setFont(font);
		text.setCharacterSize(24);
		text.setFillColor(Color::Black);
	};

	void setString(string inString)
	{
		text.setString("Score: "+inString);
	}

	Text getText()
	{
		return text;
	}

private:
	Text text;
	Font font;
};


