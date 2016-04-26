#include <iostream>
#include <iterator>
#include <algorithm>
#include "Game.h"
#include "GameObject.h"
#include "GA.h"
#include "City.h"
#include "TSalesman.h"
#include <time.h>
#include <fstream>
//#include "Utility.h"


Game::Game(int width, int height, std::string name)
{
	srand(time(NULL));
	window = new sf::RenderWindow(sf::VideoMode(width, height), name);
	window->setFramerateLimit(60);

	Initialize();
}

void Game::RunGameLoop()
{
	while (window->isOpen())
	{
		HandleEvents();
		Update();
		Draw();
	}
}

void Game::Initialize()
{
	clock.restart();

	{
		AddCity(509, 222);
		AddCity(110, 99);
		AddCity(339, 149);
		AddCity(711, 134);
		AddCity(280, 309);
		AddCity(438, 144);
		AddCity(466, 524);
		AddCity(706, 195);
		AddCity(424, 99);
		AddCity(136, 109);
		AddCity(721, 512);
		AddCity(608, 237);
		AddCity(411, 75);
		AddCity(448, 414);
		AddCity(151, 546);
		AddCity(619, 484);
		AddCity(564, 269);
		AddCity(195, 227);
		AddCity(261, 297);
		AddCity(418, 548);
		AddCity(211, 251);
		AddCity(397, 68);
		AddCity(121, 448);
		AddCity(575, 236);
		AddCity(246, 461);
		AddCity(368, 415);
		AddCity(468, 132);
		AddCity(389, 202);
		AddCity(374, 497);
		AddCity(503, 493);
	}

	//Random city map
	/*for (size_t i = 0; i < 30; i++)
	{
		int x = rand() % 700 + 50;
		int y = rand() % 500 + 50;
		AddCity(x, y);
	}*/
	tsm = new TSalesman();
	PostGameObj(tsm);
	
	tsm->CalculateTour(100, 100);
	tsm->StartTravel();

	//if (!font.loadFromFile("Content/arial.ttf"))
	//{
	//	std::cout << "Could not load font";
	//}
}

void Game::PostGameObj(GameObject* obj)
{
	gameObjects.push_back(obj);
}

void Game::AddCity(float x, float y)
{
	City* city = new City(sf::Vector2f(x, y));
	PostGameObj(city);
}

bool RemoveNotActive(GameObject* obj)
{
	if (!obj->isActive)
	{
		delete obj;
		return true;
	}
	return false;
}

void Game::HandleEvents()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		window->setKeyRepeatEnabled(false);
		if (event.type == sf::Event::Closed)
			window->close();

		std::list<GameObject*>::iterator list1;
		for (list1 = gameObjects.begin(); list1 != gameObjects.end(); ++list1)
		{
			if ((*list1)->isActive)
			{
				(*list1)->HandleEvents(event);
			}
			else continue;
		}
	}
}
void Game::Update()
{
	sf::Time time = clock.getElapsedTime();
	dt = time.asSeconds();
	clock.restart();

	std::list<GameObject*>::iterator list1;
	for (list1 = gameObjects.begin(); list1 != gameObjects.end(); ++list1)
	{
		if ((*list1)->isActive)
		{
			(*list1)->Update(dt);
		}
		else continue;

		std::list<GameObject*>::iterator list2;
		for (list2 = gameObjects.begin(); list2 != gameObjects.end(); ++list2)
		{
			//obj may have already collided, turning it inactive
			if (!(*list1)->isActive)
				continue;
			if (list1 == list2)
				continue;

			if ((*list2)->isActive && (*list1)->IsColliding(*list2))
			{
				(*list1)->DoCollision(*list2);
			}
		}

	}

	std::list<GameObject*>::iterator end = gameObjects.end();
	std::list<GameObject*>::iterator newEnd = remove_if(gameObjects.begin(), gameObjects.end(), RemoveNotActive);
	if (newEnd != end)
		gameObjects.erase(newEnd, end);
}

void Game::Draw()
{
	/*sf::Text text("hello", font, 24);
	sf::Time time = clock.getElapsedTime();

	text.setString(Utility::ToString(dt));
	text.setPosition(200, 400);*/

	window->clear();

	std::list<GameObject*>::iterator list;
	for (list = gameObjects.begin(); list != gameObjects.end(); ++list)
	{
		if ((*list)->isActive)
			(*list)->Draw(window);
	}

	window->display();
}

void Game::FindAllGameObjOfType(int type, std::list<GameObject*>& list)
{
	std::list<GameObject*>::iterator itr;
	for (itr = gameObjects.begin(); itr != gameObjects.end(); ++itr)
	{
		if (!(*itr)->isActive)
			continue;

		if ((*itr)->type == type)
			list.push_back(*itr);
	}
}
