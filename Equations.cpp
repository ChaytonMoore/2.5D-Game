#include "Equations.h"
#include <iostream>


#define pdd pair<double, double>

inline double Det(double a, double b, double c, double d)
{
	return a * d - b * c;
}

/// Calculate intersection of two lines.
///\return true if found, false if not found or error
bool LineLineIntersect(double x1, double y1, // Line 1 start
	double x2, double y2, // Line 1 end
	double x3, double y3, // Line 2 start
	double x4, double y4, // Line 2 end
	double& ixOut, double& iyOut) // Output 
{
	double detL1 = Det(x1, y1, x2, y2);
	double detL2 = Det(x3, y3, x4, y4);
	double x1mx2 = x1 - x2;
	double x3mx4 = x3 - x4;
	double y1my2 = y1 - y2;
	double y3my4 = y3 - y4;

	double denom = Det(x1mx2, y1my2, x3mx4, y3my4);
	if (denom == 0.0) // Lines don't seem to cross
	{
		ixOut = NAN;
		iyOut = NAN;
		return false;
	}

	double xnom = Det(detL1, x1mx2, detL2, x3mx4);
	double ynom = Det(detL1, y1my2, detL2, y3my4);
	ixOut = xnom / denom;
	iyOut = ynom / denom;
	if (!isfinite(ixOut) || !isfinite(iyOut)) // Probably a numerical issue
		return false;

	return true; //All OK
}

struct Point
{
	float x, y;

	Point(sf::Vector2f a)
	{
		x = a.x;
		y = a.y;
	}
	Point()
	{

	}
};

Point* intersection(Point p1, Point p2, Point p3, Point p4) {
	// Store the values for fast access and easy
	// equations-to-code conversion
	float x1 = p1.x, x2 = p2.x, x3 = p3.x, x4 = p4.x;
	float y1 = p1.y, y2 = p2.y, y3 = p3.y, y4 = p4.y;

	float d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
	// If d is zero, there is no intersection
	if (d == 0) return NULL;

	// Get the x and y
	float pre = (x1 * y2 - y1 * x2), post = (x3 * y4 - y3 * x4);
	float x = (pre * (x3 - x4) - (x1 - x2) * post) / d;
	float y = (pre * (y3 - y4) - (y1 - y2) * post) / d;

	// Check if the x and y coordinates are within both lines
	if (x < std::min(x1, x2) || x > std::max(x1, x2) ||
		x < std::min(x3, x4) || x > std::max(x3, x4)) return NULL;
	if (y < std::min(y1, y2) || y > std::max(y1, y2) ||
		y < std::min(y3, y4) || y > std::max(y3, y4)) return NULL;

	// Return the point of intersection
	Point* ret = new Point();
	ret->x = x;
	ret->y = y;
	return ret;
}


sf::Vector2f Intersect(Line a, Line b)
{
	
	double x, y;
	Point* r;
	r = intersection(Point(a.Side1),Point(a.Side2),Point(b.Side1),Point(b.Side2));
	


	if (r != NULL)
	{
		x = r->x;
		y = r->y;
		delete r;
		return sf::Vector2f(x,y);
	}
	else
	{
		delete r;
		return sf::Vector2f(NULL, NULL);
	}
	



}
