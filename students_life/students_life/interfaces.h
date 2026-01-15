#pragma once
#include <iostream>
void printStartMenu()
{
    std::cout << "\n╔══════════════════════════════╗\n";
    std::cout << "║ 🎓 ПОЗДРАВЛЕНИЯ!             ║\n";
    std::cout << "║[1] Започване на нова игра    ║\n";
    std::cout << "║[2] Зареждане на игра от файл ║\n";
    std::cout << "╚══════════════════════════════╝\n";
}

void printWinningGame()
{
    std::cout << "\n╔═════════════════════════════╗\n";
    std::cout << "║ 🎓 ПОЗДРАВЛЕНИЯ!            ║\n";
    std::cout << "║ Взе всички изпити и оцеля   ║\n";
    std::cout << "║ в сесията на живота си!     ║\n";
    std::cout << "╚═════════════════════════════╝\n";
}

void printLosingGameBeacauseOfMentality()
{
    std::cout << "\n╔═════════════════════════════╗\n";
    std::cout << "║ 💥 ИГРАТА ПРИКЛЮЧИ!         ║\n";
    std::cout << "║ Твоята психика не издържа   ║\n";
    std::cout << "║ и си напуснал университета  ║\n";
    std::cout << "╚═════════════════════════════╝\n";
}

void printLosingGameBeacauseOfMoney()
{
    std::cout << "\n╔═════════════════════════════╗\n";
    std::cout << "║ 💥 ИГРАТА ПРИКЛЮЧИ!         ║\n";
    std::cout << "║ Ти изгуби всичките си пари  ║\n";
    std::cout << "╚═════════════════════════════╝\n";
}

void printChooseAction()
{
    std::cout << "\n Какво искаш да направиш днес? \n";
    std::cout << "[1] Учиш \n";
    std::cout << "[2] Храниш се \n";
    std::cout << "[3] Излизаш \n";
    std::cout << "[4] Почиваш \n";
    std::cout << "[5] Работиш \n";
    std::cout << "[6] Явяваш се на изпит \n";
    std::cout << "[11] Излез от играта \n";
    std::cout << "> ";
}