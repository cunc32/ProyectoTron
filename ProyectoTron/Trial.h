#pragma once

#ifndef TRIAL_H
#define TRIAL_H

#include "SFML/Graphics.hpp"

using namespace sf;

class Trial
{

public:
	Trial(bool);
	Sprite trial;
	Trial* siguiente;
	Trial* anterior;

private:

	Texture trialTex;

};

#endif // !TRIAL_H


