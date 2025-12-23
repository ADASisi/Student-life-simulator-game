#include <iostream>

const int TOTAL_DAYS = 45;
const int BEGINNIG_VALUE = 100;

struct Person
{
    int knowledge;
    int mentality;
    int energy;
    int money;
    int examsPassed = 0;
};

struct GameState
{
    const int totalDays = 45;
    int currentDay = 1;
	Person player;
    int examsDays[5];
};

float getEfficiency(int enregy)
{
    if (enregy >= 80)
        return 1;
    if (enregy >= 40)
        return .75;
    else return .5;
}

void goingToLetures(Person *p)
{
    float efficiency = getEfficiency(p->energy);
    p->knowledge += 20 * efficiency;
    p->energy -= 20;
    p->mentality -= 10;
}

void studyingAtHome(Person* p)
{
    float efficiency = getEfficiency(p->energy);
    p->knowledge += 15 * efficiency;
    p->energy -= 15 * efficiency;
    p->mentality -= 20 * efficiency;
}

void studyingWithFriends(Person* p)
{
    float efficiency = getEfficiency(p->energy);
    p->knowledge += 5 * efficiency;
    p->energy -= 10 * efficiency;
    p->mentality += 10 * efficiency;
}

void eating(Person* p)
{
    float efficiency = getEfficiency(p->energy);
    p->mentality += 5 * efficiency;
    p->energy += 20 * efficiency;
    p->money -= 10 * efficiency;
}

void goingOut(Person* p)
{
    float efficiency = getEfficiency(p->energy);
    p->mentality += 40 * efficiency;
    p->energy -= 15 * efficiency;
    p->money -= 25 * efficiency;
}

void sleeping(Person* p)
{
    p->energy += 50;
    p->mentality += 10;
}

void shiftWork(Person* p)
{
    float efficiency = getEfficiency(p->energy);
    p->mentality -= 10 * efficiency;
    p->energy -= 20 * efficiency;
    p->money += 40 * efficiency;
}

void takingExam(Person* p)
{
    p->energy -= 20;
}

int main()
{

    Person *p;
    return 0;
}