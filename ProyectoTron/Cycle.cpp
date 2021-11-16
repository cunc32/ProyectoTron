#include "Cycle.h"
#include <iostream>

Cycle::Cycle(RenderWindow& ventana, bool player, int x, int y)
{
	initX = x;
	initY = y;
	this->player = player;
	load(ventana);
	this->addTrial();

	if (!gameO)
		ventana.draw(moto);	
}

Cycle::Cycle(RenderWindow& ventana, bool player, int x, int y, int rot)
{
	this->x = x;
	this->y = y;
	this->rot = rot;
	this->player = player;
	load(ventana);
	this->addTrial();
	op = +2;

	if (!gameO)
		ventana.draw(moto);
}

void Cycle::draw(RenderWindow& ventana)
{
	if (!gameO) {
		Trial* aux = primero;
		ventana.draw(actual->trial);
		while (aux->siguiente != NULL)
		{
			ventana.draw(aux->trial);
			aux = aux->siguiente;
		}
		ventana.draw(moto);
	}
}

bool Cycle::contains(FloatRect bounds)
{
	if (!gameO) {
		Trial* aux = primero;
		while (aux->siguiente != NULL)
		{
			if (aux->trial.getGlobalBounds().intersects(bounds)) {
				return true;
			}
			aux = aux->siguiente;
		}
	}
	return false;
}

void Cycle::autoSkip(Trial* cola)
{
	if (moto.getRotation() == 90) {
		FloatRect predCuadro = moto.getGlobalBounds();
		int prediccionY = moto.getGlobalBounds().top - 40;
		int prediccionX = moto.getGlobalBounds().left + 40;
		predCuadro.top = prediccionY;
		Trial* aux = cola;
		while (aux != NULL && aux->siguiente != NULL)
		{
			if (aux->trial.getGlobalBounds().intersects(predCuadro) && !upSkip) {
				predCuadro.left = prediccionX;
				upSkip = true;
				aux = cola;
				while (aux != NULL && aux->siguiente != NULL) {
					if (aux->trial.getGlobalBounds().intersects(predCuadro))
						this->izquierda();
					else
						this->derecha();
					aux = aux->siguiente;
				}
			}
			aux = aux->siguiente;
		}
	}
	if (moto.getRotation() == 270) {
		FloatRect predCuadro = moto.getGlobalBounds();
		int prediccionY = moto.getGlobalBounds().top + 40;
		int prediccionX = moto.getGlobalBounds().left + 40;
		predCuadro.top = prediccionY;
		Trial* aux = cola;
		while (aux != NULL && aux->siguiente != NULL)
		{
			if (aux->trial.getGlobalBounds().intersects(predCuadro) && !downSkip) {
				predCuadro.left = prediccionX;
				downSkip = true;
				aux = cola;
				while (aux != NULL && aux->siguiente != NULL) {
					std::cout << "Skip";
					if (aux->trial.getGlobalBounds().intersects(predCuadro))
						this->izquierda();
					else 
						this->derecha();
					if (aux->siguiente == NULL || aux == NULL)
						break;
					aux = aux->siguiente;
				}
			}
			aux = aux->siguiente;
		}
	}
	if (moto.getRotation() == 180) {
		FloatRect predCuadro = moto.getGlobalBounds();
		int prediccionY = moto.getGlobalBounds().top + 40;
		int prediccionX = moto.getGlobalBounds().left + 40;
		predCuadro.left = prediccionX;
		Trial* aux = cola;
		while (aux != NULL && aux->siguiente != NULL)
		{
			if (aux->trial.getGlobalBounds().intersects(predCuadro) && !rightSkip) {
				std::cout << "Skip C";
				predCuadro.top = prediccionY;
				rightSkip = true;
				aux = cola;
				while (aux != NULL && aux->siguiente != NULL) {
					if (aux->trial.getGlobalBounds().intersects(predCuadro))
						this->arriba();
					else
						this->abajo();
					aux = aux->siguiente;
				}
			}
			aux = aux->siguiente;
		}
	}
	if (moto.getRotation() == 0) {
		FloatRect predCuadro = moto.getGlobalBounds();
		int prediccionY = moto.getGlobalBounds().top + 40;
		int prediccionX = moto.getGlobalBounds().left - 40;
		predCuadro.left = prediccionX;
		Trial* aux = cola;
		while (aux != NULL && aux->siguiente != NULL)
		{
			if (aux->trial.getGlobalBounds().intersects(predCuadro) && !leftSkip) {
				predCuadro.top = prediccionY;
				leftSkip = true;
				aux = cola;
				while (aux != NULL && aux->siguiente != NULL) {
					if (aux->trial.getGlobalBounds().intersects(predCuadro))
						this->arriba();
					else
						this->abajo();
					aux = aux->siguiente;
				}
			}
			aux = aux->siguiente;
		}

		if (downSkip) {
			FloatRect predCuadro = moto.getGlobalBounds();
			int prediccionY = moto.getGlobalBounds().top + 40;
			predCuadro.top = prediccionY;
			Trial* aux = cola;
			while (aux != NULL && aux->siguiente != NULL)
			{
				std::cout << "SkipB";
				if (!aux->trial.getGlobalBounds().intersects(predCuadro)) {
					downSkip = false;
				}
				aux = aux->siguiente;
			}
		}

	}
}

void Cycle::speed(float velocidad)
{
	vel = velocidad;
}

int Cycle::positionX()
{
	return moto.getPosition().x;
}

int Cycle::positionY()
{
	return moto.getPosition().y;
}

FloatRect Cycle::globalBounds()
{
	return moto.getGlobalBounds();
}

void Cycle::mover(RenderWindow& ventana)
{
	if (!gameO) {
		int rotacion = moto.getRotation();
		escala += .021f;
		switch (rotacion)
		{
		case 0:
			x -= 1 * vel;
			actual->trial.setScale((escala * vel), .2f);
			break;

		case 90:
			y -= 1 * vel;
			actual->trial.setScale((escala * vel), .2f);
			break;

		case 180:
			x += 1 * vel;
			actual->trial.setScale((escala * vel), .2f);
			break;

		case 270:
			y += 1 * vel;
			actual->trial.setScale((escala * vel), .2f);
			break;
		}
		moto.setPosition(x, y);
		if (positionX() < 79 || positionY() < 79 ||
			positionX() > 721 || positionY() > 721) {
			moto.setTexture(none); draw(ventana);
			gameO = true;
		}
		if (this->contains(moto.getGlobalBounds()) &&
			!moto.getGlobalBounds().intersects(actual->anterior->trial.getGlobalBounds()) &&
			actual->anterior != NULL) {
			gameO = true;
			moto.setTexture(none); draw(ventana);
		}
	}
}

void Cycle::addTrial()
{
	actual = new Trial(player);
	if (player)
		actual->trial.setOrigin(50, 25);
	else
		actual->trial.setOrigin(0, 25);
	actual->trial.setPosition(moto.getPosition());
	actual->trial.setRotation(moto.getRotation());

	if (primero == NULL) {
		primero = actual;
		primero->siguiente = NULL;
		primero->anterior = NULL;
		ultimo = primero;
	}
	else {
		ultimo->siguiente = actual;
		actual->anterior = ultimo;
		ultimo = actual;
	}
}

void Cycle::derecha()
{
	if (moto.getRotation() != 0 && moto.getRotation() != 180 && !rightSkip) {
		moto.setRotation(180);
		if (actual->trial.getScale().x < 0.3) {
			actual->trial.setScale(0.7f, 0.2f);
		}
	}
	this->addTrial();
	escala = 0;
}

void Cycle::izquierda()
{
	if (moto.getRotation() != 0 && moto.getRotation() != 180 && !leftSkip)
		moto.setRotation(0);
	this->addTrial();
	escala = 0;
}

void Cycle::arriba()
{
	if (moto.getRotation() != 90 && moto.getRotation() != 270 && !upSkip)
		moto.setRotation(90);
	this->addTrial();
	escala = 0;
}

void Cycle::abajo()
{
	if (moto.getRotation() != 90 && moto.getRotation() != 270 && !downSkip) 
		moto.setRotation(270);
	this->addTrial();
	escala = 0;
}

void Cycle::load(RenderWindow&)
{
	if (player)
		motoT.loadFromFile("Recursos/Tron_Cycle.png");
	else
		motoT.loadFromFile("Recursos/Clu_Cycle.png");
	none.loadFromFile("Recursos/None.png");

	moto.setTexture(motoT);
	moto.setPosition(x, y);
	moto.setOrigin(360, 132);
	moto.setScale(0.08f, 0.08f);
	moto.setRotation(rot);
}
