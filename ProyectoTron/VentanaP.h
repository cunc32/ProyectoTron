#pragma once

#ifndef VENTANAP_H
#define VENTANAP_H

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
using namespace sf;

class VentanaP {

public:
	VentanaP(void);
	VentanaP(RenderWindow&);
	
private:
	void loadSprites();

	Font	fuente;

	Text	titulo,							iniciar,  salir;
	Sprite	fondoTitulo,		fondo,		bIniciar, bSalir;
	Texture tituloTexture,		fondoT,		botones;
	Music	musica;


	Event	evento;

};

#endif // !VENTANAP_H

