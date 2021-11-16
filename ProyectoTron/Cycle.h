#pragma once

#ifndef CYCLE_H
#define CYCLE_H

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Trial.h"

using namespace sf;

class Cycle {

public:
	Cycle(RenderWindow&, bool, int, int);
	Cycle(RenderWindow&, bool, int, int, int);
	void draw(RenderWindow&);
	bool contains(FloatRect), gameO = false;
	void autoSkip(Trial*);
	Trial* primero = NULL;

	FloatRect globalBounds();
	void speed(float), mover(RenderWindow&), addTrial();
	int positionX(), positionY();

	void derecha(), izquierda(), arriba(), abajo();

private:
	void load(RenderWindow&);
	bool player, downSkip, leftSkip, rightSkip, upSkip;
	float escala = 0;
	float vel = 1;
	int x = 400, y = 630, initX, initY, rot = 90, op;
	Sprite moto; Texture motoT, none;
	Sound avanzando, direccion, muerte;

	Trial*	actual;
	Trial*	ultimo = NULL;

};

#endif // !CYCLE_H

