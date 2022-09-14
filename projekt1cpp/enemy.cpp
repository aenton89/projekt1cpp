#include "enemy.h"


Enemy::Enemy(int i) : typ(i)
{
	this->initialize_variables();
}

Enemy::~Enemy()
{
	std::cout << "Destruktor obiektu klasy Enemy" << std::endl;
}


void Enemy::initialize_variables()
{
	this->spadlo = false;
	this->nowy = true;
	this->random_position();
	this->random_rotation();

	if (this->typ == ZAKRYTE)
		this->ile_jeszcze_klikniec = 2;

	else
		this->ile_jeszcze_klikniec = 1;
}


void Enemy::make_it_new()
{	
	this->random_type();

	this->initialize_variables();
}

void Enemy::random_position()
{
	this->pozycja = static_cast<float>(rand() % 411);
}

void Enemy::random_type()
{
	this->typ = (rand() % 8);
}

void Enemy::random_rotation()
{ 
	if (rand() % 2 == 1)
		this->obrot = static_cast<float>(rand() % 361);
	else
		this->obrot = 0.f;
}


bool Enemy::is_gone()
{
	if (this->ile_jeszcze_klikniec <= 0)
		return true;

	else if (this->spadlo == true)
		return true;

	else
		return false;
}