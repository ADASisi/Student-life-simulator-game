#pragma once
#include <iostream>
#include"structures.h"

void randomDailyEvent(Person& p, bool& skipActionToday)
{
    int chance = rand() % 30;
    if (chance != 0) return;

    int event = rand() % 4;
    std::cout << "\n🎲 Случайно събитие!\n";

    if (event == 0) {
        std::cout << "Мама и тате ти пращат пари ❤️\n";
        p.money += 30;
    }
    else if (event == 1) {
        std::cout << "Приятел те черпи кафе ☕\n";
        p.mentality += 10;
    }
    else if (event == 2) {
        std::cout << "Разболял си се 🤒\n";
        p.energy -= 20;
    }
    else {
        std::cout << "Няма ток в блока ⚡\n";
        std::cout << "Пропускаш деня.\n";
        skipActionToday = false;
    }
    checkParameters(p.energy, p.knowledge, p.mentality);
}

void randomAfterEating(Person& p)
{
    int chance = rand() % 12;
    if (chance != 0) return;

    std::cout << "🤢 Дюнерът беше развален!\n";
    p.energy -= 20;
}

void randomAfterStudy(Person& p)
{
    int chance = rand() % 10;

    if (chance == 0)
    {
        std::cout << "📚 Намери стари записки – вдъхновение!\n";
        p.knowledge += 10;
        p.mentality += 5;
        checkParameters(p.energy, p.knowledge, p.mentality);
    }
}

void randomAfterParty(Person& p)
{
    int chance = rand() % 8;

    if (chance == 0)
    {
        std::cout << "🍻 Черпиха те цяла вечер!\n";
        p.money += 10;
    }
    else if (chance == 1)
    {
        std::cout << "🤕 Прекали малко...\n";
        p.energy -= 20;
    }
}