#include "VentanaP.h"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <iostream>
#include "Juego.h"

void VentanaP::loadSprites() {
	if (!fondoT.loadFromFile("Recursos/FondoTron.jpg")) { std::cout << "IMAGEN DE FONDO NO ENCONTRADA"; }
	if (!tituloTexture.loadFromFile("Recursos/FondoTitulo.png")) { std::cout << "IMAGEN DE FONDO NO ENCONTRADA"; }
	if (!botones.loadFromFile("Recursos/Botones.png")) { std::cout << "IMAGEN DE BOTONES NO ENCONTRADA"; }
	if (!fuente.loadFromFile("Recursos/Tr2n.ttf")) { std::cout << "NO ESTA LA FUENTE"; }
	if (!musica.openFromFile("Recursos/Magic.ogg")) { std::cout << "NO ESTA LA CANCION MAGIC"; }

	musica.play();
	musica.setVolume(1);

	fondoTitulo.setTexture(tituloTexture);
	fondoTitulo.setPosition(25, 100);
	fondoTitulo.setScale(.75f, .75f);

	fondo.setTexture(fondoT);
	fondo.setPosition(-373, 0);
	fondo.setScale(.4f, .4f);

	bIniciar.setTexture(botones);
	bIniciar.setScale(.4f, .4f);
	bIniciar.setPosition(200, 380);

	iniciar.setFont(fuente);
	iniciar.setString("iniciar");
	iniciar.setLetterSpacing(2);
	iniciar.setFillColor(Color::White);
	iniciar.setPosition(242, 385);
	iniciar.setCharacterSize(70);

	bSalir.setTexture(botones);
	bSalir.setScale(.4f, .4f);
	bSalir.setPosition(200, 510);

	salir.setFont(fuente);
	salir.setString("salir");
	salir.setLetterSpacing(2);
	salir.setFillColor(Color::White);
	salir.setPosition(277, 515);
	salir.setCharacterSize(70);

	titulo.setFont(fuente);
	titulo.setString("T R O N");
	titulo.setFillColor(Color::White);
	titulo.setPosition(82, 125);
	titulo.setLetterSpacing(2);
	titulo.setScale(1.068f, 1);
	titulo.setCharacterSize(105);
}

VentanaP::VentanaP(void) {

	RenderWindow ventana(VideoMode(800, 800), "Tron Light Cycle", Style::Titlebar | Style::Close);

	ventana.setFramerateLimit(60);
	loadSprites();

	ventana.setKeyRepeatEnabled(false);

	while (ventana.isOpen()) {
		while (ventana.pollEvent(this->evento)) {
			Cursor hand; hand.loadFromSystem(Cursor::Hand);
			Cursor def; def.loadFromSystem(Cursor::Arrow);

			Vector2i mousePos = Mouse::getPosition(ventana);
			Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

			switch (evento.type)
			{
			case Event::Closed:
				ventana.close();
				break;

			case Event::MouseMoved:
				if (bIniciar.getGlobalBounds().contains(mousePosF)) {
					ventana.setMouseCursor(hand);
				}
				else if (bSalir.getGlobalBounds().contains(mousePosF)) {
					ventana.setMouseCursor(hand);
				}
				else {
					ventana.setMouseCursor(def);
				}
				break;

			case Event::MouseButtonPressed:
				if (bIniciar.getGlobalBounds().contains(mousePosF)) {
					musica.stop();
					ventana.clear();
					ventana.display();
					ventana.setMouseCursor(def);
					Juego juego(ventana, 1, 0, 3);
				}
				else if (bSalir.getGlobalBounds().contains(mousePosF)) {
					ventana.close();
				}
				break;

			case Event::KeyPressed:

				if (evento.key.code == Keyboard::Right) {
				}
				else if (evento.key.code == Keyboard::Left) {
				}
				break;

			default:
				break;
			}

		}

		ventana.clear(Color::Black);
		ventana.draw(this->fondo);
		ventana.draw(this->fondoTitulo);
		ventana.draw(this->titulo);
		ventana.draw(this->bIniciar);
		ventana.draw(this->iniciar);
		ventana.draw(this->bSalir);
		ventana.draw(this->salir);
		ventana.display();
	}

}

VentanaP::VentanaP(RenderWindow& ventana)
{
	ventana.setFramerateLimit(60);
	loadSprites();

	ventana.setKeyRepeatEnabled(false);

	while (ventana.isOpen()) {
		while (ventana.pollEvent(this->evento)) {
			Cursor hand; hand.loadFromSystem(Cursor::Hand);
			Cursor def; def.loadFromSystem(Cursor::Arrow);

			Vector2i mousePos = Mouse::getPosition(ventana);
			Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

			switch (evento.type)
			{
			case Event::Closed:
				ventana.close();
				break;

			case Event::MouseMoved:
				if (bIniciar.getGlobalBounds().contains(mousePosF)) {
					ventana.setMouseCursor(hand);
				}
				else if (bSalir.getGlobalBounds().contains(mousePosF)) {
					ventana.setMouseCursor(hand);
				}
				else {
					ventana.setMouseCursor(def);
				}
				break;

			case Event::MouseButtonPressed:
				if (bIniciar.getGlobalBounds().contains(mousePosF)) {
					musica.stop();
					ventana.clear();
					ventana.display();
					ventana.setMouseCursor(def);
					Juego juego(ventana, 1, 0, 3);
				}
				else if (bSalir.getGlobalBounds().contains(mousePosF)) {
					ventana.close();
				}
				break;

			case Event::KeyPressed:

				if (evento.key.code == Keyboard::Right) {
				}
				else if (evento.key.code == Keyboard::Left) {
				}
				break;

			default:
				break;
			}

		}

		ventana.clear(Color::Black);
		ventana.draw(this->fondo);
		ventana.draw(this->fondoTitulo);
		ventana.draw(this->titulo);
		ventana.draw(this->bIniciar);
		ventana.draw(this->iniciar);
		ventana.draw(this->bSalir);
		ventana.draw(this->salir);
		ventana.display();
	}
}
