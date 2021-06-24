#include <SFML/Graphics.hpp>
#pragma once

struct Line
{
	sf::Vector2f Side1;
	sf::Vector2f Side2;


	Line(float a, float b, float c, float d);

	Line(sf::Vector2f a, float b, float c);

};


struct Wall  : public Line
{
	float Height = 100;
	sf::Vector2f Side1;
	sf::Vector2f Side2;

	Wall(int a, int b, int c, int d);
};


float Distance(sf::Vector2f a, sf::Vector2f b);


std::vector<std::string> SplitString(const std::string& str, const std::string& delim);
