#pragma once
#include "structures.h"
#include "checkParameters.h"
#include "randomEvents.h"

float getEfficiency(int enregy)
{
    if (enregy >= 80)
        return 1;
    if (enregy >= 40)
        return .75;
    else return .5;
}

void applyActivity(GameState* g,
    int hoursCost,
    int knowledgeGain,
    int energyChange,
    int mentalityChange,
    int moneyChange)
{
    g->hours -= hoursCost;

    float efficiency = getEfficiency(g->player.energy);

    g->player.knowledge += knowledgeGain * efficiency;
    g->player.energy += energyChange * efficiency;
    g->player.mentality += mentalityChange * efficiency;
    g->player.money += moneyChange;
    checkParameters(g->player.energy, g->player.knowledge, g->player.mentality);
}

void goingToLectures(GameState* g)
{
    applyActivity(g, 3, 20, -20, -10, 0);
}

void studyingAtHome(GameState* g)
{
    applyActivity(g, 5, 15, -15, -20, 0);
    randomAfterStudy(g->player);
}

void studyingWithFriends(GameState* g)
{
    applyActivity(g, 4, 5, -10, 10, 0);
}

void eating(GameState* g)
{
    applyActivity(g, 1, 0, 20, 5, -10);
    randomAfterEating(g->player);
}

void goingOut(GameState* g)
{
    applyActivity(g, 2, 0, -15, 40, -25);
}

void goToDisco(GameState* g)
{
    applyActivity(g, 4, 0, -30, 60, -40);
    randomAfterParty(g->player);
}

void resting(Person* p)
{
    p->energy += 25;
    p->mentality += 5;
    checkParameters(p->energy, p->knowledge, p->mentality);
}

void sleeping(GameState* g)
{
    if (g->hours < 8)
    {
        resting(&(g->player));
    }
    else
    {
        applyActivity(g, g->hours, 0, 50, 10, 0);
    }
}

void shiftWork(GameState* g)
{
    applyActivity(g, 6, 0, -20, -10, 40);
}