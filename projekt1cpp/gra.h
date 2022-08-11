#pragma once

#include "szablon.h"
#include "pole.h"

#include <SFML/Graphics.hpp>


class Gra : public Szablon_Klasy				//dziedziczenie
{
	friend class Pole;							//daje dostep do prywatnych elementow klasy Pole


	private:
//zmienne private
		sf::RenderWindow* okno_aplikacji;
		sf::Event zdarzenie;

		sf::Vector2i polozenie_myszy;					


//funkcje private
		void initialize_variables();
		void initialize_window();


	public:
//konstruktory i destruktor
		Gra();
		virtual ~Gra();							//dzieki temu zawsze bedzie wykonana dla rzeczywistego typu wskaznika


//funkcje public -- WYBRAC KTORE DAC DO PUBLIC A KTORE DO PRIVATE
		void render();
		void update();
		const bool is_game_running() const;		//const za metoda sprawia ze nie zmienia sie stan obiektu(np. liczba przechowywanych danych)
		void poll_event();
		void update_mouse_postion();
		void render_fields();					//rysuje pola -- bedzie korzystac ze skladowych klasy Pole


};