#include "gra.h"


//konstruktory i destruktor

Gra::Gra()
{
	this->initialize_variables();
	this->initialize_window();

}


Gra::~Gra()
{
	delete this->okno_aplikacji;

}


//funkcje private

void Gra::initialize_variables()
{
	this->okno_aplikacji = nullptr;

}


void Gra::initialize_window()
{
	this->okno_aplikacji = new sf::RenderWindow(sf::VideoMode(800, 800, 32), "Saper");
	this->okno_aplikacji->setFramerateLimit(60);

}


//funkcje public

void Gra::update()
{
	this->poll_event();								//sprawdzanie eventów

	this->update_mouse_postion();

}


void Gra::render()
{
	this->okno_aplikacji->clear(sf::Color::Black);

													//miejsce na .draw 

	this->okno_aplikacji->display();
}


const bool Gra::is_game_running() const
{
	return this->okno_aplikacji->isOpen();
}


void Gra::poll_event()
{
	while (this->okno_aplikacji->pollEvent(this->zdarzenie))
	{
		if ((this->zdarzenie.type == sf::Event::Closed) || ((this->zdarzenie.type == sf::Event::KeyPressed) && (this->zdarzenie.key.code == sf::Keyboard::Escape)))
			this->okno_aplikacji->close();
	}

}


void Gra::update_mouse_postion()
{
	this->polozenie_myszy = sf::Mouse::getPosition(*this->okno_aplikacji);
}


void Gra::render_fields()
{


}