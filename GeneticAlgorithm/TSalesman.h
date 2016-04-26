#pragma once
#include "GameObject.h"
#include "GA.h"

class GA;
class City;
class Tour;

class TSalesman: public GameObject
{
public:
	TSalesman();
	~TSalesman();
	void HandleEvents(sf::Event event) override;
	void Update(float deltaTime) override;
	void Draw(sf::RenderWindow* window) override;
	void DoCollision(GameObject* other) override;
	void SetHitbox() override;

	Tour CalculateTour(int generations, int popSize);
	void SetTour(Tour tour);
	void StartTravel();
	GA ga;

private:
	void MoveToNextDestination();
	void TravelTowardsDestination(float dt);
	bool DestinationReached();
	void CreateGraph();

	sf::CircleShape body;
	sf::VertexArray path;
	Tour tour;
	City* currentDestination;
	int cityIndex = 0;
	bool travelling;
	float speed;
};