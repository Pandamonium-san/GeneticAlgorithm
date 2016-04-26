#pragma once
//#include <SFML/Graphics/RenderWindow.hpp>
//#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>
#include <list>

class TSalesman;
class GameObject;
class GA;

class Game{
public:
	Game(int width, int height, std::string name);
	void RunGameLoop();
	void Initialize();
	void HandleEvents();
	void Update();
	void Draw();
	void PostGameObj(GameObject* obj);
	void FindAllGameObjOfType(int type, std::list<GameObject*>& list);

	void AddCity(float x, float y);

	sf::RenderWindow* window;
	sf::Clock clock;
	float dt;
	std::list<GameObject*> gameObjects;

	TSalesman* tsm;
};

extern Game game;