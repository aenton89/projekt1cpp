#include "game.h"


Game::Game()
{
	this->initialize_variables();
	this->initialize_window();
    this->initialize_font_n_text();
    this->initialize_enemies();
    this->initialize_sprites();
}

Game::~Game()
{
	delete this->okno_aplikacji;
    std::cout << "Destruktor obiektu klasy Game" << std::endl;
}


void Game::initialize_variables()
{
	this->okno_aplikacji = nullptr;

    this->liczba_wrogow = 8;
    this->max_liczba_wrogow = 8;

    this->punkty = 0;
    this->zycia = 8;
    this->predkosc = 2.f;

    this->max_czas_spawnu = 4.f;
    this->czas_spawnu = 0.f;

    this->pierwsza_petla = true;
    this->tekst_startowy = true;

    this->trzymanie_myszy = false;

    this->koniec = false;
    this->zwyciestwo = false;
}

void Game::initialize_window()
{
	this->okno_aplikacji = new sf::RenderWindow(sf::VideoMode(460, 720), "GRA", sf::Style::Close | sf::Style::Titlebar);
    this->okno_aplikacji->setFramerateLimit(60);
}

void Game::initialize_font_n_text()
{
    if (!this->czcionka.loadFromFile("FONTS/Forque.ttf"))
        std::cout << "ERROR: wczytywanie czcionki" << std::endl;

    this->tekst.setFont(this->czcionka);
    this->tekst.setCharacterSize(32);
    this->tekst.setFillColor(sf::Color::White);
    this->tekst.setPosition(sf::Vector2f(8.f, 140.f));

    this->tekst.setString("UZBIERANIE 300 PUNKTOW - WYGRANIE GRY\nSTRACENIE 8 HP - PRZEGRANIE GRY\nFLAGA - PRZYSPIESZA SPADANIE\nPUSTE - JAK SPADNIE - 1 HP\nZAKRYTY - JAK SPADNIE - 2 HP\nBOMBA - KLIKNIECIE - 8 HP\n1 - 4 - DODAJE 1 - 4 PUNKTY\n\n\n     WCISNIJ *ENTER* ABY KONTYNUOWAC");
}

void Game::initialize_enemies()
{
    for (int i = 0; i < this->max_liczba_wrogow; i++)
        this->wrogowie.push_back(Enemy(i));

    if (!this->enemies.loadFromFile("texture.png"))
        std::cout << "ERROR: wczytywanie tekstury wrogow" << std::endl;
}

void Game::initialize_sprites()
{
    if(!this->gameover.loadFromFile("gameover.png"))
        std::cout << "ERROR: wczytywanie tekstury konca gry" << std::endl;

    if(!this->gamewon.loadFromFile("gamewon.png"))
        std::cout << "ERROR: wczytywanie tekstury wygrania gry" << std::endl;
    
    if(!this->hp.loadFromFile("hp.png"))
        std::cout << "ERROR: wczytywanie tekstury hp" << std::endl;

    this->sprajt.setTexture(this->hp);
}

void Game::update()
{
    this->update_events();

    if (this->koniec == false && this->zwyciestwo == false)
    {
        this->update_mouse();

        this->update_text();
        this->update_enemies();
    }

    if (this->zycia < 1)
        this->koniec = true;

    else if (this->punkty >= 300)
        this->zwyciestwo = true;
}

void Game::update_events()
{
    while (this->okno_aplikacji->pollEvent(this->zdarzenie))
    {
        if (this->zdarzenie.type == sf::Event::Closed)
            this->okno_aplikacji->close();

        else if (this->zdarzenie.type == sf::Event::KeyPressed)
        {
            if (this->zdarzenie.key.code == sf::Keyboard::Escape)
                this->okno_aplikacji->close();
        }
    }
}

void Game::update_mouse()
{
    this->polozenie_myszy_ekran = sf::Mouse::getPosition(*this->okno_aplikacji);
    this->polozenie_myszy_widok = this->okno_aplikacji->mapPixelToCoords(this->polozenie_myszy_ekran);
}

void Game::update_text()
{
    if (this->tekst_startowy)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
            this->tekst_startowy = false;
    }

    else
    {
        std::stringstream ciag_znakow;
        ciag_znakow << "PUNKTY: " << this->punkty;

        this->tekst.setString(ciag_znakow.str());
        this->tekst.setPosition(5.f, 630.f);
    }

}

void Game::update_enemies()
{
    if(this->pierwsza_petla == true)
    { 
        this->pierwsza_petla = false;
    
        for (int i = 0; i < this->max_liczba_wrogow; i++)
            this->set_enemy(i);
    }

    else
    {
        this->check_number_enemies();

        if (this->liczba_wrogow < this->max_liczba_wrogow)
        {
            if (this->czas_spawnu >= this->max_czas_spawnu)
            {
                this->spawn_enemy();
                this->czas_spawnu = 1.f;
            }
        //    WAZNE ------------------------------------------------------ ponizej mozna uzyc przeciazenia operatora ++ na przyklad
            else
                this->czas_spawnu = this->czas_spawnu + 1.f;
        }

        for (int i = 0; i < this->max_liczba_wrogow; i++)
        {
            this->sprajt_wrogow.at(i).move(0.f, this->predkosc);
            this->sprajt_wrogow.at(i).rotate(1.f);

            this->is_fallen(i);
        }

        this->is_clicked();
    }
}

void Game::is_clicked()
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (this->trzymanie_myszy == false)
        {
            this->trzymanie_myszy = true;                                   //te dwie zmienne bool zapobiegaja ciaglemu trzymaniu myszy
            bool kliknieto_w = false;

            for (int i = 0; (i < this->max_liczba_wrogow && kliknieto_w == false); i++)
            {
                if (this->sprajt_wrogow.at(i).getGlobalBounds().contains(this->polozenie_myszy_widok))
                {
                    kliknieto_w = true;
                    this->wrogowie.at(i).ile_jeszcze_klikniec = this->wrogowie.at(i).ile_jeszcze_klikniec - 1;

                    if (this->wrogowie.at(i).typ >= 1 && this->wrogowie.at(i).typ <= 4)
                        this->punkty = this->punkty + this->wrogowie.at(i).typ;

                    else if (this->wrogowie.at(i).typ == FLAGA)
                        this->predkosc = this->predkosc + 1.f;

                    else if (this->wrogowie.at(i).typ == BOMBA)
                        this->zycia = this->zycia - 8;

                    else if (this->wrogowie.at(i).typ == ZAKRYTE)
                    {
                        if (this->wrogowie.at(i).ile_jeszcze_klikniec == 1)
                        {
                            this->sprajt_wrogow.at(i).setTextureRect(sf::IntRect(50, 0, 50, 50));
                            this->wrogowie.at(i).typ = PUSTE;
                        }
                    }
                }
            }
        }
    }

    else
        this->trzymanie_myszy = false;
}

void Game::is_fallen(int i)
{
    if (this->wrogowie.at(i).ile_jeszcze_klikniec > 0)
    {
        if (this->sprajt_wrogow.at(i).getPosition().y > 630)
        {
            this->wrogowie.at(i).spadlo = true;

            if(this->wrogowie.at(i).typ == ZAKRYTE)
                this->zycia = static_cast<int>(this->zycia - 0.5);

            else if(this->wrogowie.at(i).typ == PUSTE)
                this->zycia = static_cast<int>(this->zycia - 0.25);
        }
    }
}

void Game::check_number_enemies()
{
    for (Enemy& v : this->wrogowie)
    {
        if (v.is_gone() == true)
        this->liczba_wrogow = this->liczba_wrogow - 1;
    }
}

void Game::spawn_enemy()
{
    for (int i = 0; i < this->max_liczba_wrogow; i++)
    {
        if (this->wrogowie.at(i).is_gone() == true)
        {
            this->wrogowie.at(i).make_it_new();
            this->set_enemy(i);

            this->liczba_wrogow = this->liczba_wrogow + 1;
        }
    }
}

void Game::set_enemy(int i)
{
    int ktora_tekstura;
    float polozenie = this->wrogowie.at(i).pozycja;
    float rotacja = this->wrogowie.at(i).obrot;


    if (this->wrogowie.at(i).typ == BOMBA)
        ktora_tekstura = 350;
    else if (this->wrogowie.at(i).typ >= ZAKRYTE)
        ktora_tekstura = (this->wrogowie.at(i).typ - 5) * 50;
    else
        ktora_tekstura = this->wrogowie.at(i).typ * 50 + 100;

    this->sprajt_wrogow.at(i).setTexture(this->enemies);
    this->sprajt_wrogow.at(i).setTextureRect(sf::IntRect(ktora_tekstura, 0, 50, 50));

    this->sprajt_wrogow.at(i).setPosition(polozenie, 0.f);
    this->sprajt_wrogow.at(i).setRotation(rotacja);
}

void Game::render()
{
    this->okno_aplikacji->clear();

    //tu rysujemy
    this->render_enemies(*this->okno_aplikacji);
    this->render_hp(*this->okno_aplikacji);

    if (this->koniec)
    {
        this->sprajt_konca.setTexture(this->gameover);
        this->sprajt_konca.setTextureRect(sf::IntRect(0, 0, 300, 100));
        this->sprajt_konca.setPosition(80.f, 300.f);
        this->okno_aplikacji->draw(sprajt_konca);
    }

    else if (this->zwyciestwo)
    {
        this->sprajt_konca.setTexture(this->gamewon);
        this->sprajt_konca.setTextureRect(sf::IntRect(0, 0, 300, 100));
        this->sprajt_konca.setPosition(80.f, 300.f);
        this->okno_aplikacji->draw(sprajt_konca);
    }

    this->render_text(*this->okno_aplikacji);
    //koniec rysowania

    this->okno_aplikacji->display();
}

void Game::render_enemies(sf::RenderWindow& cel_rysowania)
{
    for (int i = 0; i < this->max_liczba_wrogow; i++)
    {
        if (!(this->wrogowie.at(i).is_gone()))
        {
            cel_rysowania.draw(this->sprajt_wrogow.at(i));
        }
    }
}

void Game::render_text(sf::RenderWindow& cel_rysowania)
{
    cel_rysowania.draw(this->tekst);
}

void Game::render_hp(sf::RenderWindow& cel_rysowania)
{
    for (int i = 0; i < this->zycia; i++)
    {
        this->sprajt.setPosition((i * 50.f), 670.f);
        cel_rysowania.draw(this->sprajt);
    }
}

const bool Game::is_game_running() const
{
	return this->okno_aplikacji->isOpen();
}