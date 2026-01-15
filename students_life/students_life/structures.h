#pragma once
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
    int hours = 24;
    Person player;
    int examsDays[5];
};