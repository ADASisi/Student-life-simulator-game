#pragma once
#include <iostream>
#include "structures.h"

void printStartMenu() {
    std::cout << "\n╔══════════════════════════════╗\n";
    std::cout << "║ 🎓 ПОЗДРАВЛЕНИЯ!             ║\n";
    std::cout << "║[1] Започване на нова игра    ║\n";
    std::cout << "║[2] Зареждане на игра от файл ║\n";
    std::cout << "╚══════════════════════════════╝\n";
}

void printWinningGame() {
    std::cout << "\n╔═════════════════════════════╗\n";
    std::cout << "║ 🎓 ПОЗДРАВЛЕНИЯ!            ║\n";
    std::cout << "║ Взе всички изпити и оцеля   ║\n";
    std::cout << "║ в сесията на живота си!     ║\n";
    std::cout << "╚═════════════════════════════╝\n";
}

void printLosingGameBeacauseOfMentality() {
    std::cout << "\n╔═════════════════════════════╗\n";
    std::cout << "║ 💥 ИГРАТА ПРИКЛЮЧИ!         ║\n";
    std::cout << "║ Твоята психика не издържа   ║\n";
    std::cout << "║ и си напуснал университета  ║\n";
    std::cout << "╚═════════════════════════════╝\n";
}

void printLosingGameBeacauseOfMoney() {
    std::cout << "\n╔═════════════════════════════╗\n";
    std::cout << "║ 💥 ИГРАТА ПРИКЛЮЧИ!         ║\n";
    std::cout << "║ Ти изгуби всичките си пари  ║\n";
    std::cout << "╚═════════════════════════════╝\n";
}

void printLosingGameBeacauseOfExams() {
    std::cout << "\n╔═════════════════════════════╗\n";
    std::cout << "║ 💥 ИГРАТА ПРИКЛЮЧИ!         ║\n";
    std::cout << "║ Ти не успя да вземеш        ║\n";
    std::cout << "║ всичките си изпити          ║\n";
    std::cout << "╚═════════════════════════════╝\n";
}

void printChooseAction() {
    std::cout << "\n Какво искаш да направиш днес? \n";
    std::cout << "[1] Учиш \n";
    std::cout << "[2] Храниш се \n";
    std::cout << "[3] Излизаш \n";
    std::cout << "[4] Почиваш \n";
    std::cout << "[5] Работиш \n";
    std::cout << "[6] Ходиш на дискотека \n";
    std::cout << "[7] Явяваш се на изпит \n";
    std::cout << "[11] Излез от играта \n";
    std::cout << "> ";
}

void printSpaces(int count) {
    for (int i = 0; i < count; i++) {
        std::cout << " ";
    }
}

int getDigits(int n) {
    if (n == 0) return 1;
    if (n < 0) n = -n;
    int count = 0;
    while (n > 0) {
        n /= 10;
        count++;
    }
    return count;
}

void drawLine(const char* label, int value, const char* suffix, int labelWidth, int totalWidth) {
    std::cout << "║ " << label << value << suffix;

    int spaces = totalWidth - labelWidth - getDigits(value);

    printSpaces(spaces);
    std::cout << "║\n";
}

void printStatus(GameState g) {
    const int width = 30;

    std::cout << "\n╔";
    for (int i = 0; i < width; i++) std::cout << "═";
    std::cout << "╗\n";

    drawLine("Ден: ", g.currentDay, " от 45", 12, width);
    drawLine("Оставащи часове: ", g.hours, " часа", 23, width);
    drawLine("Пари: ", g.player.money, " лв", 10, width);
    drawLine("Енергия: ", g.player.energy, " ⚡ ", 14, width);
    drawLine("Психика: ", g.player.mentality, " 🧠 ", 14, width);
    drawLine("Знания: ", g.player.knowledge, " 📚 ", 13, width);
    drawLine("Изпити: ", g.player.examsPassed, " 🎓 ", 13, width);

    std::cout << "╚";
    for (int i = 0; i < width; i++) std::cout << "═";
    std::cout << "╝\n";
}

void printSleep(GameState* g) {
    std::cout << "\n╔═════════════════════════════╗\n";
    std::cout << "║ Време за сън  🌙            ║\n";
    std::cout << "║ Спа " << g->hours << " часа                  ║\n";
    std::cout << "║ СУПЕР ТИ ОЦЕЛЯ И ТОЗИ ДЕН!  ║\n";
    std::cout << "╚═════════════════════════════╝\n";
}