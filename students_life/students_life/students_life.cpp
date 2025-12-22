#include <iostream>

const int TOTAL_DAYS = 45;
const int BEGINNIG_VALUE = 100;

struct Person
{
    int knowledge = BEGINNIG_VALUE;
    int mentality = BEGINNIG_VALUE;
    int energy = BEGINNIG_VALUE;
    int money = BEGINNIG_VALUE;
    int examsPassed = 0;
};

struct Game
{
    const int totalDays = 45;
    int currentDay = 1;

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
    p->energy -= 15;
    p->mentality -= 20;
}

void studyingWithFriends(Person* p)
{
    float efficiency = getEfficiency(p->energy);
    p->knowledge += 5 * efficiency;
    p->energy -= 10;
    p->mentality += 10;
}

int main()
{
    Person *p;
    return 0;
}