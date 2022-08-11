#pragma once

#include "szablon.h"
#include "gra.h"

#include <SFML/Graphics.hpp>

#include <vector>
#include <ctime>
#include <cstdlib>


class Pole : public Szablon_Klasy						//dziedziczenie
{
	private:
//zmienne private
		unsigned max_liczba_bomb;						//maksymalna ilosc bomb -- zainicjalizowane w init_variables narazie jako 10
		unsigned liczba_pol;							//plansza 9x9

		std::vector<int> zawartosc_pola;				//wektor zawierajacy pola
		std::vector<int> odkrycie_pola;					//czy pole jest odkryte/zakryte/oflagowane


//funkcje private
		void initialize_variables();


	public:
//konstruktory i destruktor
		Pole();
		virtual ~Pole();								//dzieki temu zawsze bedzie wykonana dla rzeczywistego typu wskaznika


//funkcje public -- WYBRAC KTORE DAC DO PUBLIC A KTORE DO PRIVATE
		void spawn_fields();							//spawnuje zawartosc pola na planszy
		void update_fields();							//updatuje ktore sa juz odsloniete
		void how_many_around();							//sprawdza ile jest bomb dookola
		void initialize_bombs();
		void initialize_cover();						//zakrywa wszystkie pola
		void field_it();								//spawn_fields; initialize_cover
};