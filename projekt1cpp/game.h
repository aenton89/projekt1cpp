#pragma once

#include <SFML/Graphics.hpp>
#include "enemy.h"

#include <vector>
#include <array>
#include <iostream>
#include <sstream>


class Game : public szablon					//dziedziczenie
{
	private:
		sf::RenderWindow* okno_aplikacji;
		sf::Event zdarzenie;

		sf::Font czcionka;
		sf::Text tekst;

		std::vector<Enemy> wrogowie;
		std::array<sf::Sprite, 8> sprajt_wrogow;

		sf::Texture gameover, gamewon, hp, enemies;
		sf::Sprite sprajt, sprajt_konca;

		sf::Vector2i polozenie_myszy_ekran;
		sf::Vector2f polozenie_myszy_widok;

		unsigned punkty;
		int zycia;
		float predkosc;

		int max_liczba_wrogow;
		int liczba_wrogow;

		float czas_spawnu;
		float max_czas_spawnu;

		bool pierwsza_petla;
		bool tekst_startowy;

		bool trzymanie_myszy;

		bool koniec;
		bool zwyciestwo;


		void initialize_variables();
		void initialize_window();
		void initialize_enemies();
		void initialize_font_n_text();
		void initialize_sprites();


	public:
		Game();
		~Game();


		const bool is_game_running() const;			//informuje ze nie zmieni sie stan obiektu (np.liczba danych przechowywanych przez obiekt)

		void update();
			void update_events();
			void update_mouse();
			void update_enemies();
				void check_number_enemies();
				void spawn_enemy();
				void is_fallen(int i);
				void is_clicked();
				void set_enemy(int i);
			void update_text();

		void render();
			void render_enemies(sf::RenderWindow& cel_rysowania);
			void render_text(sf::RenderWindow& cel_rysowania);
			void render_hp(sf::RenderWindow& cel_rysowania);
};