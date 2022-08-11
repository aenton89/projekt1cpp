#include "pole.h"


//konstruktory i destruktor

Pole::Pole()
{
	this->initialize_variables();

}


Pole::~Pole()
{



}


//funkcje private

void Pole::initialize_variables()
{
	this->max_liczba_bomb = 10;
	this->liczba_pol = 81;

}


//funkcje public

void Pole::spawn_fields()
{
	this->initialize_bombs();
	this->how_many_around();

	for (auto& v : this->zawartosc_pola)					//sprawdza zeby nie bylo wiecej niz 4 bomby wokol jedengo pola
	{
		if (v > 4)												//z tego zrobic WYJATKI
		{
			this->spawn_fields();
			break;
		}
	}
}

void Pole::field_it()
{
	this->spawn_fields();
	this->initialize_cover();
}

void Pole::update_fields()
{



}


void Pole::how_many_around()									//jesli jest bomba to zwiekszamy wszystkim dookola licznik, chyba ze jest to 0
{																//uzyjemy przeciazenia ++ dla wektora
	int n;

	for (int i = 0; i++; i < this->liczba_pol)
	{
		if (this->zawartosc_pola[i] == 0)
		{
			if (i == 0)
			{
				if (this->zawartosc_pola[1] != 0)
					this->zawartosc_pola[1] += 1;

				if (this->zawartosc_pola[9] != 0)
					this->zawartosc_pola[9] += 1;

				if (this->zawartosc_pola[10] != 0)
					this->zawartosc_pola[10] += 1;
			}

			else if (i == 8)
			{
				if (this->zawartosc_pola[7] != 0)
					this->zawartosc_pola[7] += 1;

				if (this->zawartosc_pola[16] != 0)
					this->zawartosc_pola[16] += 1;

				if (this->zawartosc_pola[17] != 0)
					this->zawartosc_pola[17] += 1;
			}

			else if (i == 72)
			{
				if (this->zawartosc_pola[63] != 0)
					this->zawartosc_pola[63] += 1;

				if (this->zawartosc_pola[64] != 0)
					this->zawartosc_pola[64] += 1;

				if (this->zawartosc_pola[73] != 0)
					this->zawartosc_pola[73] += 1;
			}

			else if (i == 80)
			{
				if (this->zawartosc_pola[70] != 0)
					this->zawartosc_pola[70] += 1;

				if (this->zawartosc_pola[71] != 0)
					this->zawartosc_pola[71] += 1;

				if (this->zawartosc_pola[79] != 0)
					this->zawartosc_pola[79] += 1;
			}

			else if (i < 8 && i > 0)
			{
				if (this->zawartosc_pola[i-1] != 0)
					this->zawartosc_pola[i-1] += 1;

				if (this->zawartosc_pola[i+1] != 0)
					this->zawartosc_pola[i+1] += 1;

				if (this->zawartosc_pola[i+9] != 0)
					this->zawartosc_pola[i+9] += 1;

				if (this->zawartosc_pola[i+8] != 0)
					this->zawartosc_pola[i+8] += 1;

				if (this->zawartosc_pola[i+10] != 0)
					this->zawartosc_pola[i+10] += 1;
			}

			else if (i < 80 && i > 72)
			{
				if (this->zawartosc_pola[i-1] != 0)
					this->zawartosc_pola[i-1] += 1;

				if (this->zawartosc_pola[i+1] != 0)
					this->zawartosc_pola[i+1] += 1;

				if (this->zawartosc_pola[i-9] != 0)
					this->zawartosc_pola[i-9] += 1;

				if (this->zawartosc_pola[i-8] != 0)
					this->zawartosc_pola[i-8] += 1;

				if (this->zawartosc_pola[i-10] != 0)
					this->zawartosc_pola[i-10] += 1;
			}

			else if (i%9 == 0 && i != 0 && i != 72)
			{
				if (this->zawartosc_pola[i-9] != 0)
					this->zawartosc_pola[i-9] += 1;

				if (this->zawartosc_pola[i-8] != 0)
					this->zawartosc_pola[i-8] += 1;

				if (this->zawartosc_pola[i+1] != 0)
					this->zawartosc_pola[i+1] += 1;

				if (this->zawartosc_pola[i+9] != 0)
					this->zawartosc_pola[i+9] += 1;

				if (this->zawartosc_pola[i+10] != 0)
					this->zawartosc_pola[i+10] += 1;
			}

			else if (i == 17 || i == 26 || i == 35 || i == 44 || i == 53 || i == 62 || i == 71)
			{
				if (this->zawartosc_pola[i - 10] != 0)
					this->zawartosc_pola[i - 10] += 1;

				if (this->zawartosc_pola[i - 9] != 0)
					this->zawartosc_pola[i - 9] += 1;

				if (this->zawartosc_pola[i - 1] != 0)
					this->zawartosc_pola[i - 1] += 1;

				if (this->zawartosc_pola[i + 9] != 0)
					this->zawartosc_pola[i + 9] += 1;

				if (this->zawartosc_pola[i + 8] != 0)
					this->zawartosc_pola[i + 8] += 1;
			}

			else
			{
				if (this->zawartosc_pola[i-10] != 0)
					this->zawartosc_pola[i-10] += 1;

				if (this->zawartosc_pola[i-9] != 0)
					this->zawartosc_pola[i-9] += 1;

				if (this->zawartosc_pola[i-8] != 0)
					this->zawartosc_pola[i-8] += 1;

				if (this->zawartosc_pola[i+9] != 0)
					this->zawartosc_pola[i+9] += 1;

				if (this->zawartosc_pola[i+8] != 0)
					this->zawartosc_pola[i+8] += 1;

				if (this->zawartosc_pola[i-1] != 0)
					this->zawartosc_pola[i-1] += 1;

				if (this->zawartosc_pola[i+1] != 0)
					this->zawartosc_pola[i+1] += 1;

				if (this->zawartosc_pola[i+10] != 0)
					this->zawartosc_pola[i+10] += 1;
			}
		}
	}
}


void Pole::initialize_bombs()
{
	int random_number;										//srand(time(NULL)); w main.cpp
	int value;
	int n = 0;

	for (int i = 0; i++; i < this->liczba_pol)				//inicjowanie bombami
	{
		if (n < this->max_liczba_bomb)
		{
			random_number = std::rand();
			value = random_number % 2;

			this->zawartosc_pola.push_back(value);
		}

		else
			this->zawartosc_pola.push_back(1);

		if (value == 0)										//jest bomba
			n++;
	}
}

void Pole::initialize_cover()
{
	for (int i = 0; i++; i < this->liczba_pol)
	{
		this->odkrycie_pola.push_back(1);				//czyli zakryte, 0 - odkryte, 2 - oflagowane
	}
}