#include <SFML/Graphics.hpp>
#include "Data.h"
#include "Equations.h"
#include <vector>
#include <iostream>
#include "files.h"
#include "WallTexturestore.h"

//Wolfenstien engine

sf::RectangleShape R1(sf::Vector2f(1000, 300));
sf::RectangleShape R2(sf::Vector2f(1000, 300));

sf::Vector2f PlayerLocation = sf::Vector2f(0,0);
int fov = 90;
float PlayerRotation= 0;

std::vector<sf::RectangleShape*> WallLines;// < Probably only a temporary solution

std::vector<Line> WallData;

WallTextureStore* Textures = new WallTextureStore();





void SetUpRender()
{
	//this stuff will set up the basic rendering stuff
	R2.setPosition(sf::Vector2f(0, 300));
	R1.setFillColor(sf::Color(56,56,56));
	R2.setFillColor(sf::Color(112,112,112));


	//This will initate the texture library
	//Textures->MountTextures();

}

void CeilingFloorRender(sf::RenderWindow* window)
{
	//This function is the first path of rendering.
	//It divides the screen in two and renders different colours on each part


	window->draw(R1);
	window->draw(R2);

}

void WallCleanUp()
{
	for (sf::RectangleShape* p: WallLines)
	{
		delete p;
	}
}



void RenderVerticleLine(int Position,int TextureID,int StartingHeight)
{
	//firstly just get the texture we are using
	sf::Image* Texture = Textures->WallT1;




}


bool RenderWalls(sf::RenderWindow* window)
{
	if (WallLines.size() > 0)
	{
		WallCleanUp();
	}
	WallLines.clear();
	//for testing a wingle wall will be used

	
	//For each column on the screen

	//The first is for negative values of x
	float A;
	float xTemp;
	float yTemp;
	int LineShade;
	Line TempLine = Line(0,0,0,0);

	sf::Vector2f Intercept;
	float WallDistance;


	for (size_t n = 0; n < WallData.size(); n++)
	{


		
			for (size_t i = 0; i < 500; i++)
			{
				A = ((float)i / 636.6);



				xTemp = 1000 * sin(A + PlayerRotation);


				yTemp = 1000 * cos(A + PlayerRotation);

				TempLine = Line(PlayerLocation, xTemp, yTemp);
				//TempLine = Line(PlayerLocation, (xTemp*cos(PlayerRotation))+yTemp*sin(PlayerRotation), (yTemp*cos(PlayerRotation))+xTemp*sin(PlayerRotation));


				Intercept = Intersect(TempLine, WallData[n]);

				
				if (Intercept.x != NULL)
				{
					//WallDistance = Distance(Intercept, PlayerLocation);

					WallDistance = (abs(Intercept.x - PlayerLocation.x) * sin(PlayerRotation)) + (abs(Intercept.y - PlayerLocation.y) * cos(PlayerRotation));
					

					LineShade = 255 - ((WallDistance * 60) > 255) * 255 - ((WallDistance * 60) <= 255) * (WallDistance * 60);
					WallLines.push_back(new sf::RectangleShape(sf::Vector2f(1, (200 / WallDistance))));
					WallLines.back()->setPosition(sf::Vector2f(i + 500, 300 - (100 / WallDistance)));


					WallLines.back()->setFillColor(sf::Color(LineShade, LineShade, LineShade));


				}
			}

			for (size_t i = 0; i < 500; i++)
			{
				A = ((float)i / 636.6);



				xTemp = -1000 * sin(A+PlayerRotation);


				yTemp = 1000 * cos(A + PlayerRotation);

				TempLine = Line(PlayerLocation, xTemp, yTemp);
				//TempLine = Line(PlayerLocation, (xTemp * cos(PlayerRotation)) + yTemp * sin(PlayerRotation), (yTemp * cos(PlayerRotation)) + xTemp * sin(PlayerRotation));


				Intercept = Intersect(TempLine, WallData[n]);

				
				if (Intercept.x != NULL)
				{
					//WallDistance = Distance(Intercept, PlayerLocation);
					WallDistance = (abs(Intercept.x - PlayerLocation.x) * sin(PlayerRotation)) + (abs(Intercept.y - PlayerLocation.y) * cos(PlayerRotation));


					LineShade = 255 - ((WallDistance * 60) > 255) * 255 - ((WallDistance * 60) <= 255) * (WallDistance * 60);
					WallLines.push_back(new sf::RectangleShape(sf::Vector2f(1, (200 / WallDistance))));
					WallLines.back()->setPosition(sf::Vector2f(500-i, 300 - (100 / WallDistance)));

					WallLines.back()->setFillColor(sf::Color(LineShade, LineShade, LineShade));




				}
			}







			for (size_t i = 0; i < WallLines.size(); i++)
			{
				window->draw(*WallLines[i]);

			}
		
	}

	return true;
}


bool Render(sf::RenderWindow* window)
{
	window->clear();

	bool RenderSuccess = true;

	CeilingFloorRender(window);
	RenderWalls(window);





	window->display();
	return RenderSuccess;
}


void PlayerMovement(sf::Event event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		
		if (event.key.code == sf::Keyboard::D)
		{
			PlayerLocation += sf::Vector2f(0.1*cos(PlayerRotation), 0.1*sin(PlayerRotation));
			
		}

		if (event.key.code == sf::Keyboard::A)
		{
			PlayerLocation += sf::Vector2f(-0.1 * cos(PlayerRotation), -0.1 * sin(PlayerRotation));

		}

		if (event.key.code == sf::Keyboard::S)
		{
			PlayerLocation += sf::Vector2f(-0.1 * sin(PlayerRotation), -0.1 * cos(PlayerRotation));

		}

		if (event.key.code == sf::Keyboard::W)
		{
			PlayerLocation += sf::Vector2f(0.1 * sin(PlayerRotation), 0.1 * cos(PlayerRotation));

		}

		if (event.key.code == sf::Keyboard::Q)
		{
			PlayerRotation += 0.05;
			if (PlayerRotation > 6.283)
			{
				PlayerRotation = 0;
			}

		}

		if (event.key.code == sf::Keyboard::E)
		{
			PlayerRotation -= 0.05;
			if (PlayerRotation < 0)
			{
				PlayerRotation = 6.283;
			}
		}
	}

}

int main()
{
	sf::RenderWindow window(sf::VideoMode(1000, 600), "Game");
	
	SetUpRender();

	WallData = LoadWallsText("Maps/1/Walls.txt");

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{

			if (event.type == sf::Event::Closed)
				window.close();

			PlayerMovement(event);


		}

		
		Render(&window);


	}

	

	return 0;
}
