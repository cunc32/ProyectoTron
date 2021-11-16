#include "Trial.h"

Trial::Trial(bool player)
{
	if (player) 
		trialTex.loadFromFile("Recursos/Trial.png");
	else
		trialTex.loadFromFile("Recursos/TrialRed.png");
	trial.setTexture(trialTex);
	siguiente = NULL;
	anterior = NULL;
}