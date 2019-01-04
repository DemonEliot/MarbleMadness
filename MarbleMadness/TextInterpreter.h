#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "Spawner.h"

using namespace std;

class TextInterpreter
{
public:
	TextInterpreter(GenericSpawner* spawner_ptr) { filePath = new string("$(ProjectDir)\\TextFiles\\"); spawner = spawner_ptr; };
	TextInterpreter(string* newFilePath, GenericSpawner* spawner) { filePath = newFilePath; };
	~TextInterpreter() {};

	void initializeTextFiles();
	void interpretTextFile(string* name);
	string* getFilePath();
	string* setFilePath(string* newFilePath);

private:
	ifstream* textFile;
	string* filePath;
	string* fileName;
	string line; 
	string tempString;
	size_t stringPos;
	size_t stringPos2;
	float x;
	float y;
	size_t subPos;
	vector <float> fVector;
	string sColor;
	Color color;
	GenericSpawner* spawner;

	void createWallText();
	void createMarbleText();
	Color stringToColor(string sColor);
};

void TextInterpreter::initializeTextFiles()
{

}

void TextInterpreter::interpretTextFile(string* name)
{
	textFile->open(*filePath);
	if (!textFile) 
	{ 
		cerr << "Text file unable to open" << endl;
		exit(1);
	}

	stringPos = 0;

	while (getline(*textFile, line))
	{
		if (!line.empty)
		{
			stringPos = line.find("(", stringPos);
			if (stringPos != string::npos)
			{
				stringPos2 = line.find(")", stringPos);
				if (stringPos2 != string::npos)
				{
					tempString = line.substr(stringPos + 1, stringPos2 - stringPos - 2);
					
					// Using if ladder because of c++ lack of switch/string functionality
					if (tempString == "Wall") { createWallText(); }
					else if (tempString == "Marble") { createMarbleText(); }
					else 
					{	cerr << "Text file contains error" << endl; 
						exit(1); 
					}
				}
			}
		}
	}

	textFile->close;
}

void TextInterpreter::createWallText()
{

	for (int i = 0; i < 3; i++ )
	{
		subPos = NULL;
		stringPos = line.find("(", stringPos2 + 1);
		stringPos2 = line.find(")", stringPos);
		if (stringPos2 != string::npos)
		{
			tempString = line.substr(stringPos + 1, stringPos2 - stringPos - 2);

			// Very hardcoded right here. I'm using the fact I know the text files go Floats, Floats, Color.
			if (i != 2)
			{
				x = stof(tempString, &subPos);
				y = stof(tempString.substr(subPos));
				fVector.push_back(x);
				fVector.push_back(y);
			}
			else if (i == 2)
			{
				sColor = tempString;
				color = stringToColor(sColor);
			}
		}
		else
		{
			break;
		}
	}
	spawner->createFromText("Wall", fVector, color);
	fVector.clear;
}

void TextInterpreter::createMarbleText()
{

	for (int i = 0; i < 3; i++)
	{
		subPos = NULL;
		stringPos = line.find("(", stringPos2 + 1);
		stringPos2 = line.find(")", stringPos);
		if (stringPos2 != string::npos)
		{
			tempString = line.substr(stringPos + 1, stringPos2 - stringPos - 2);

			// Very hardcoded right here. I'm using the fact I know the text files go Floats, Float, Color.
			if (i == 0)
			{
				x = stof(tempString, &subPos);
				y = stof(tempString.substr(subPos));
				fVector.push_back(x);
				fVector.push_back(y);
			}
			else if (i == 1)
			{
				x = stof(tempString);
				fVector.push_back(x);
			}
			else if (i == 2)
			{
				sColor = tempString;
				color = stringToColor(sColor);
			}
		}
		else
		{
			break;
		}
	}
	spawner->createFromText("Marble", fVector, color);
	fVector.clear;
}

Color TextInterpreter::stringToColor(string sColor)
{
	//This is painful, but I can't just insert a string for the color, so I'm going to have to manually if ladder...
	if (sColor == "White")
	{
		return Color::White;
	}
	if (sColor == "Yellow")
	{
		return Color::Yellow;
	}
	if (sColor == "Cyan")
	{
		return Color::Cyan;
	}
	if (sColor == "Green")
	{
		return Color::Green;
	}
	if (sColor == "Blue")
	{
		return Color::Blue;
	}
	if (sColor == "Magenta")
	{
		return Color::Magenta;
	}
	if (sColor == "Black")
	{
		return Color::Black;
	}
	if (sColor == "Red")
	{
		return Color::Red;
	}
	cerr << "Error with parsing text of color, will assign magenta" << endl;
	return Color::Magenta;
}

string* TextInterpreter::getFilePath()
{
	return filePath;
}

string* TextInterpreter::setFilePath(string* newFilePath)
{
	filePath = newFilePath;
}