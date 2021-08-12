#include "Data.h"



Line::Line(float a, float b, float c, float d)
{
	Side1 = sf::Vector2f(a, b);
	Side2 = sf::Vector2f(c, d);
}

Line::Line(sf::Vector2f a, float b, float c)
{
	Side1 = a;
	Side2 = sf::Vector2f(b,c);
}

Wall::Wall(int a, int b, int c, int d) : Line(0, 0, 0, 0) 
{
	
	Side1 = sf::Vector2f(a, b);
	Side2 = sf::Vector2f(c, d);
}



float Distance(sf::Vector2f a, sf::Vector2f b)
{
	return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

float TaxiDistance(sf::Vector2f a, sf::Vector2f b)
{
	return abs(a.x - b.x) + abs(a.y + b.y);
}

std::vector<std::string> SplitString(const std::string& str, const std::string& delim)
{
	std::vector<std::string> tokens;
	size_t prev = 0, pos = 0;
	do
	{
		pos = str.find(delim, prev);
		if (pos == std::string::npos) pos = str.length();
		std::string token = str.substr(prev, pos - prev);
		if (!token.empty()) tokens.push_back(token);
		prev = pos + delim.length();
	} while (pos < str.length() && prev < str.length());
	return tokens;
}

