#pragma once

#ifndef JUEGO_H
#define JUEGO_H

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
using namespace sf;

class Juego {

public:
	Juego(RenderWindow&, int, int, int);

private:
	void loadSprites(RenderWindow&);
	int lvl, punct = 0, life = 3;

	Font	fuente,		pixel;

	RectangleShape base;
	Text	puntuacion, vidas;
	Sprite	fondo;
	Texture	fondoT;
	Music	musica;

	Event	evento;
};

#endif // !JUEGO_H

