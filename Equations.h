#include <SFML/Graphics.hpp>
#include "Data.h"
#pragma once

bool LineLineIntersect(double x1, double y1, 
	double x2, double y2, 
	double x3, double y3,
	double x4, double y4,
	double& ixOut, double& iyOut);


sf::Vector2f Intersect(Line a, Line b);

