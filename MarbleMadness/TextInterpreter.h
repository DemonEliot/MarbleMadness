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
	TextInterpreter(GenericSpawner* spawner_ptr) { filePath = new string("TextFiles\\"); spawner = spawner_ptr; };
	TextInterpreter(string* newFilePath, GenericSpawner* spawner_ptr) { filePath = newFilePath; spawner = spawner_ptr; };
	~TextInterpreter() {};

	void initializeTextFiles();
	void interpretLevelFile();
	string* getFilePath();
	void setFilePath(string* newFilePath);
	bool levelsCheck();

private:
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
	string levelsPath = "TextFiles\\Levels.txt";
	vector <string> levelVector;
	int levelCounter = 0;

	void createWallText();
	void createMarbleText();
	Color stringToColor(string sColor);
};

void TextInterpreter::initializeTextFiles()
{
	ifstream* textFile = new ifstream(levelsPath, ifstream::in);
	if (!textFile->is_open())
	{
		cerr << "Text file unable to open" << endl;
	}

	while (getline(*textFile, line))
	{
		if (line != "")
		{
			levelVector.push_back(line);
		}
	}
	textFile->close();
	delete textFile;
}

void TextInterpreter::interpretLevelFile()
{
	
	ifstream* textFile = new ifstream(*filePath + levelVector[levelCounter] + ".txt", ifstream::in);
	if (!textFile->is_open())
	{ 
		cerr << "Text file unable to open" << endl;
	}

	levelCounter++;
	stringPos = 0;

	while (getline(*textFile, line))
	{
		stringPos = line.find("(", stringPos);
		if (stringPos != string::npos)
		{
			stringPos2 = line.find(")", stringPos);
			if (stringPos2 != string::npos)
			{
				tempString = line.substr(stringPos + 1, stringPos2 - stringPos - 1);
					
				// Using if ladder because of c++ lack of switch/string functionality
				if (tempString == "Wall") { createWallText(); }
				else if (tempString == "Marble") { createMarbleText(); }
				else 
				{	cerr << "Text file contains error" << endl; 
				}
			}
		}
		stringPos = 0;
		stringPos2 = 0;
	}

	textFile->close();
	delete textFile;
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
			tempString = line.substr(stringPos + 1, stringPos2 - stringPos - 1);

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
	fVector.clear();
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
			tempString = line.substr(stringPos + 1, stringPos2 - stringPos - 1);

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
	fVector.clear();
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

void TextInterpreter::setFilePath(string* newFilePath)
{
	filePath = newFilePath;
}

bool TextInterpreter::levelsCheck()
{
	if (levelCounter >= levelVector.size())
	{
		return false;
	}
	else
	{
		return true;
	}
}