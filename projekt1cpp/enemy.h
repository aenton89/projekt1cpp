#pragma once

#define BOMBA 0
#define ZAKRYTE 5
#define PUSTE 6
#define FLAGA 7

#include "szablon.h"

#include <iostream>
#include <ctime>

/*		
		UZBIERANIE 300 PUNKTOW		- WYGRANIE GRY
		STRACENIE 8 HP				- PRZEGRANIE GRY

		FLAGA		- PRZYSPIESZA SPADANIE
		PUSTE		- JAK SPADNIE -1 HP
		ZAKRYTY		- JAK SPADNIE -2 HP
		BOMBA		- KLIKNIECIE -8 HP
		1-4			- DODAJE 1-4 PUNKTY
*/

class Enemy : public szablon				//dziedziczenie
{
	friend class Game;

	private:
		int typ;
		float pozycja;
		float obrot;

		int ile_jeszcze_klikniec;
		bool spadlo;
		bool nowy;


		void initialize_variables();


	public:
		Enemy(int i);
		~Enemy();


		void make_it_new();
			void random_position();
			void random_type();
			void random_rotation();

		bool is_gone();
};