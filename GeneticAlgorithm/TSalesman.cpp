#include "TSalesman.h"
#include "City.h"
#include "Utility.h"
#include <iostream>

TSalesman::TSalesman()
{
	body = sf::CircleShape(20);
	body.setOrigin(sf::Vector2f(20, 20));
	body.setPosition(100, 100);
	body.setFillColor(sf::Color::Cyan);
	type = TYPE_TSALESMAN;
	speed = 100;
}

TSalesman::~TSalesman()
{
}

void TSalesman::HandleEvents(sf::Event event)
{

}

void TSalesman::Draw(sf::RenderWindow* window)
{
	sf::CircleShape target = sf::CircleShape(10);
	target.setOrigin(sf::Vector2f(10, 10));
	target.setFillColor(sf::Color::Red);
	target.setPosition(currentDestination->body.getPosition());
	window->draw(path);
	window->draw(target);
	window->draw(body);
}

void TSalesman::DoCollision(GameObject* other)
{

}

void TSalesman::SetHitbox()
{
	hitbox = body.getGlobalBounds();
}

void TSalesman::Update(float deltaTime)
{
	if (travelling)
	{
		if (tour.GetSize() <= 0)
			return;
		TravelTowardsDestination(deltaTime);
		if (DestinationReached())
			MoveToNextDestination();
	}
	GameObject::Update(deltaTime);
}

void TSalesman::TravelTowardsDestination(float dt)
{
	sf::Vector2f dir = currentDestination->body.getPosition() - body.getPosition();
	dir = Utility::Normalized(dir);
	if (std::isnan(dir.x) || std::isnan(dir.y))
		return;

	body.move(dir * speed * dt);
}

void TSalesman::MoveToNextDestination()
{
	if (cityIndex + 1 < ga.GetNrOfCities())
		++cityIndex;
	else
		cityIndex = 0;
	currentDestination = ga.GetCity(tour.GetValue(cityIndex));
}

void TSalesman::StartTravel()
{
	if (tour.GetSize() <= 0)
	{
		std::cout << "Error: Tour not calculated" << std::endl;
		return;
	}

	cityIndex = 0;
	travelling = true;
	currentDestination = ga.GetCity(tour.GetValue(cityIndex));
	body.setPosition(currentDestination->body.getPosition());
	CreateGraph();
}

void TSalesman::CreateGraph()
{
	path = sf::VertexArray(sf::LinesStrip, tour.GetSize() + 1);
	for (size_t i = 0; i < tour.GetSize(); i++)
	{
		path[i].position = ga.GetCity(tour.GetValue(i))->body.getPosition();
	}
	path[tour.GetSize()].position = ga.GetCity(tour.GetValue(0))->body.getPosition();
}

bool TSalesman::DestinationReached()
{
	return Utility::DistanceBetweenVectors(currentDestination->body.getPosition(), body.getPosition()) < 5.f;
}

Tour TSalesman::CalculateTour(int generations, int popSize)
{
	tour = ga.CalculateGeneticTour(generations, popSize);
	return tour;
}

void TSalesman::SetTour(Tour tour)
{
	this->tour = tour;
}