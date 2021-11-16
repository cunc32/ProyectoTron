#include "Juego.h"
#include "SFML/Graphics.hpp"
#include "Cycle.h"
#include "VentanaP.h"
#include <iostream>
#include <stdlib.h>



void Juego::loadSprites(RenderWindow& ventana) {
	if (!fondoT.loadFromFile("Recursos/Tablero.jpg")) { std::cout << "IMAGEN DE FONDO NO ENCONTRADA"; }
	if (!fuente.loadFromFile("Recursos/Tr2n.ttf")) { std::cout << "NO ESTA LA FUENTE"; }
	if (!pixel.loadFromFile("Recursos/Pixel.ttf")) { std::cout << "NO ESTA LA FUENTE"; }
	musica.openFromFile("Recursos/Eye.ogg");

	fondo.setTexture(fondoT);
	fondo.setPosition(0, 0);

	musica.setVolume(1);

	Vector2f tamanio;
	tamanio.x = 800;
	tamanio.y = 500;
	base.setPosition(0, 720);
	base.setFillColor(Color::Black);
	base.setSize(tamanio);

	vidas.setString("Vidas: 3");
	vidas.setPosition(500, 740);
	vidas.setFont(pixel);

	puntuacion.setString("Puntuacion: 0");
	puntuacion.setPosition(40, 740);
	puntuacion.setFont(pixel);
}

Juego::Juego(RenderWindow& ventana, int lvl, int puntos, int _vidas) {

	Cycle player(ventana, true, 400, 600);
	Cycle enemy1(ventana, false, 400, 200, 270);
	Cycle enemy2(ventana, false, 200, 200, 270);
	Cycle enemy3(ventana, false, 600, 200, 270);

	life = _vidas;
	punct = puntos;
	player.speed(2);
	enemy1.speed(lvl * 0.1 + 1);
	enemy2.speed(lvl * 0.1 + 1);
	enemy3.speed(lvl * 0.1 + 1);
	Clock wait;
	loadSprites(ventana);

	ventana.setKeyRepeatEnabled(false);

	while (ventana.isOpen()) {
		while (ventana.pollEvent(this->evento)) {


			switch (evento.type)
			{
			case Event::Closed:
				ventana.close();
				break;

			case Event::KeyPressed:

				switch (evento.key.code)
				{
				case Keyboard::Up:
				case Keyboard::W:
					while (player.positionX() % 40 != 0)
					{
						player.mover(ventana);
						if (player.positionX() % 40 == 1) break;
					}
					player.arriba();
					break;

				case Keyboard::Down:
				case Keyboard::S:
					while (player.positionX() % 40 != 0)
					{
						player.mover(ventana);
						if (player.positionX() % 40 == 1) break;
					}
					player.abajo();
					break;

				case Keyboard::Left:
				case Keyboard::A:
					while (player.positionY() % 40 != 0)
					{
						player.mover(ventana);
						if (player.positionY() % 40 == 1) break;
					}
					player.izquierda();
					break;

				case Keyboard::Right:
				case Keyboard::D:
					while (player.positionY() % 40 != 0)
					{
						player.mover(ventana);
						if (player.positionY() % 40 == 1) break;
					}
					player.derecha();
					break;

				default:
					break;
				}
				break;

			default:
				break;
			}

		}

		if (wait.getElapsedTime().asMilliseconds() > 750 && musica.getStatus() != 2) {
			musica.play();
		}

		if (!enemy1.gameO) {
			if (!enemy1.gameO && enemy1.contains(player.globalBounds()))
				player.gameO = true;
			if (!player.gameO && player.contains(enemy1.globalBounds()))
				enemy1.gameO = true;
			if (!enemy2.gameO && enemy2.contains(enemy1.globalBounds()))
				enemy1.gameO = true;
			if (!enemy3.gameO && enemy3.contains(enemy1.globalBounds()))
				enemy1.gameO = true;
		}
		if (lvl > 2) {
			if (!enemy2.gameO) {
				if (!enemy2.gameO && enemy2.contains(player.globalBounds()))
					player.gameO = true;
				if (!player.gameO && player.contains(enemy2.globalBounds()))
					enemy2.gameO = true;
				if (!enemy1.gameO && enemy1.contains(enemy2.globalBounds()))
					enemy2.gameO = true;
				if (!enemy3.gameO && enemy3.contains(enemy2.globalBounds()))
					enemy2.gameO = true;
			}

		}

		if (lvl > 5) {
			if (!enemy3.gameO) {
				if (!enemy3.gameO && enemy3.contains(player.globalBounds()))
					player.gameO = true;
				if (!player.gameO && player.contains(enemy3.globalBounds()))
					enemy3.gameO = true;
				if (!enemy1.gameO && enemy1.contains(enemy3.globalBounds()))
					enemy3.gameO = true;
				if (!enemy2.gameO && enemy2.contains(enemy3.globalBounds()))
					enemy3.gameO = true;
			}
		}

		// std::cout << player.positionX() << ", " << player.positionY() << std::endl;
		player.mover(ventana);
		
		enemy1.mover(ventana);
		if (lvl > 2)
			enemy2.mover(ventana);
		if (lvl > 5)
			enemy3.mover(ventana);
		ventana.clear(Color::Black);
		ventana.draw(this->fondo);
		player.draw(ventana);
		enemy1.draw(ventana);
		if (lvl > 2)
			enemy2.draw(ventana);
		if (lvl > 5)
			enemy3.draw(ventana);

		std::cout << "x: " << enemy1.globalBounds().left << " y: " << enemy1.globalBounds().top << std::endl;

		int difX;
		int difY;
		if (!enemy1.gameO) {
			difX = (player.positionX() - enemy1.positionX());
			difY = (player.positionY() - enemy1.positionY());
			if (std::abs(difX) > std::abs(difY)) {
				if (difX > 0) {
					while (!enemy1.gameO && enemy1.positionY() % 40 != 0)
					{
						enemy1.mover(ventana);
						if (enemy1.positionY() % 40 == 1) break;
					}
					enemy1.derecha();
				}
				else {
					while (enemy1.positionY() % 40 != 0)
					{
						enemy1.mover(ventana);
						if (enemy1.positionY() % 40 == 1) break;
					}
					enemy1.izquierda();
				}
			}
			else {
				if (difY > 0) {
					while (enemy1.positionX() % 40 != 0)
					{
						enemy1.mover(ventana);
						if (enemy1.positionX() % 40 == 1) break;
					}
					enemy1.abajo();
				}
				else {
					while (enemy1.positionX() % 40 != 0)
					{
						enemy1.mover(ventana);
						if (enemy1.positionX() % 40 == 1) break;
					}
					enemy1.arriba();
				}
			}
		}

		if (!enemy2.gameO) {
			difX = (player.positionX() - enemy2.positionX());
			difY = (player.positionY() - enemy2.positionY());
			if (std::abs(difX) > std::abs(difY)) {
				if (difX > 0) {
					while (enemy2.positionY() % 40 != 0)
					{
						enemy2.mover(ventana);
						if (enemy2.positionY() % 40 == 1) break;
					}
					enemy2.derecha();
				}
				else {
					while (enemy2.positionY() % 40 != 0)
					{
						enemy2.mover(ventana);
						if (enemy2.positionY() % 40 == 1) break;
					}
					enemy2.izquierda();
				}
			}
			else {
				if (difY > 0) {
					while (enemy2.positionX() % 40 != 0)
					{
						enemy2.mover(ventana);
						if (enemy2.positionX() % 40 == 1) break;
					}
					enemy2.abajo();
				}
				else {
					while (enemy2.positionX() % 40 != 0)
					{
						enemy2.mover(ventana);
						if (enemy2.positionX() % 40 == 1) break;
					}
					enemy2.arriba();
				}
			}
		}

		if (!enemy3.gameO) {
			difX = (player.positionX() - enemy3.positionX());
			difY = (player.positionY() - enemy3.positionY());
			if (std::abs(difX) > std::abs(difY)) {
				if (difX > 0) {
					while (enemy3.positionY() % 40 != 0)
					{
						enemy3.mover(ventana);
						if (enemy3.positionY() % 40 == 1) break;
					}
					enemy3.derecha();
				}
				else {
					while (enemy3.positionY() % 40 != 0)
					{
						enemy3.mover(ventana);
						if (enemy3.positionY() % 40 == 1) break;
					}
					enemy3.izquierda();
				}
			}
			else {
				if (difY > 0) {
					while (enemy3.positionX() % 40 != 0)
					{
						enemy3.mover(ventana);
						if (enemy3.positionX() % 40 == 1) break;
					}
					enemy3.abajo();
				}
				else {
					while (enemy3.positionX() % 40 != 0)
					{
						enemy3.mover(ventana);
						if (enemy3.positionX() % 40 == 1) break;
					}
					enemy3.arriba();
				}
			}
		}

		if (player.gameO) {
			musica.stop();
			if (life > 1)
				Juego restart(ventana, lvl, punct, life - 1);
			else
				VentanaP inicio(ventana);
			
		}
		if (enemy1.gameO && lvl < 3) {
			musica.stop();
			punct += 20;
			Juego nxtLvl(ventana, lvl + 1, punct, life);
		}
		if (enemy1.gameO && enemy2.gameO && lvl < 6 && lvl > 2) {
			musica.stop();
			punct += 20;
			Juego nxtLvl(ventana, lvl + 1, punct, life);
		}
		if (enemy1.gameO && enemy2.gameO && enemy3.gameO && lvl >= 6) {
			musica.stop();
			punct += 20;
			Juego nxtLvl(ventana, lvl + 1, punct, life);
		}
		puntuacion.setString("Puntuacion: "+ std::to_string(punct));
		vidas.setString("Vidas: " + std::to_string(life));
		ventana.draw(base);
		ventana.draw(puntuacion);
		ventana.draw(vidas);
		ventana.display();
	} // LOOP VENTANA

}
