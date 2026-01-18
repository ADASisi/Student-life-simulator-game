#include <iostream>
#include <windows.h>
#include <fstream>
#include "interfaces.h"
#include "structures.h"
#include "checkParameters.h"
#include "randomEvents.h"
#include "actions.h"

const int TOTAL_DAYS = 45;
const int EASY_BEG_VAL_KNOWLADGE = 80;
const int EASY_BEG_VAL = 100;
const int NORMAL_BEG_VAL_KNOWLADGE = 50;
const int NORMAL_BEG_VAL = 80;
const int HARD_BEG_VAL_KNOWLADGE = 35;
const int HARD_BEG_VAL = 60;
const int HARD_BEG_VAL_MENTALITY = 40;

size_t myStrlen(const char* str) {
    if (!str)
        return 0;

    unsigned result = 0;

    while (*str) {
        result++;
        str++;
    }

    return result;
}

void myStrcpy(char* dest, const char* source) {
    if (!source)
        return;

    while (*source) {
        *dest = *source;
        dest++;
        source++;
    }

    *dest = '\0';
}

void myStrcat(char* dest, const char* source) {
    if (!dest || !source)
        return;

    size_t firstLen = myStrlen(dest);
    dest += firstLen;
    myStrcpy(dest, source);
}

void takingExam(Person* p) {
    p->energy -= 20;
}

void enterExamDays(GameState* gs) {
    gs->examsDays[0] = 8;
    gs->examsDays[1] = 17;
    gs->examsDays[2] = 26;
    gs->examsDays[3] = 26 + rand() % 20;
    gs->examsDays[4] = 45;
}

bool losingGame(GameState g) {
    if (g.player.mentality <= 0) {
        printLosingGameBeacauseOfMentality();
        return 1;
    }
    if (g.player.money <= 0) {
        printLosingGameBeacauseOfMoney();
        return 1;
    }
    if (g.currentDay == TOTAL_DAYS && g.player.examsPassed < 5) {
        printLosingGameBeacauseOfExams();
        return 1;
    }
    return 0;
}

bool winningGame(GameState g) {
    if (g.player.examsPassed == 5 && g.currentDay == 45)
        return 1;
    return 0;
}

int getExamNumber(GameState g) {
    for (int i = 0; i < 5; i++) {
        if (g.examsDays[i] == g.currentDay) {
            return i + 1;
        }
    }
    return 0;
}

double successRateExam(GameState g) {
    int penelty = (getExamNumber(g) - 1) * 5;
    return g.player.energy * 0.1 + g.player.knowledge * 0.75 +
        g.player.mentality * 0.1 + (rand() % 101) * 0.2 - penelty;
}

bool passExam(GameState* g) {
    double successRate = successRateExam(*g);
    if (successRate >= 75) {
        g->player.examsPassed++;
        g->player.mentality += 20;
        g->player.energy -= 20;
        checkParameters(g->player.energy, g->player.knowledge, g->player.mentality);
        int retentionRate = 40 + (rand() % 31);
        g->player.knowledge = (g->player.knowledge * retentionRate) / 100;
        return 1;
    }
    else {
        g->player.mentality -= 30;
        g->player.energy -= 20;
        checkParameters(g->player.energy, g->player.knowledge, g->player.mentality);
        return 0;
    }
}

void skipDay(GameState* g) {
    if (g->player.energy < 0) {
        std::cout << "Твоята енергия е твърде ниска! Пропускаш деня, за да се възстановиш.\n";
        g->player.energy = 40;
        g->player.mentality -= 10;
        checkParameters(g->player.energy, g->player.knowledge, g->player.mentality);
        g->currentDay++;
    }
}

void chooseStudying(GameState* g) {
    int studyingChoice;
    std::cout << "Как искаш да учиш днес? \n 1 - Ходиш на лекции \n 2 - Учиш вкъщи \n 3 - Учиш с приятели \n";
    std::cin >> studyingChoice;
    switch (studyingChoice) {
    case 1:
        goingToLectures(g);
        break;
    case 2:
        studyingAtHome(g);
        break;
    case 3:
        studyingWithFriends(g);
        break;
    default:
        break;
    }
}

void setParametersForDifficulty(GameState* gameState, int knowledge, int mentality, int energy, int money) {
    gameState->player.knowledge = knowledge;
    gameState->player.mentality = mentality;
    gameState->player.energy = energy;
    gameState->player.money = money;
}

void chooseDifficulty(int diff, GameState* gameState) {
    switch (diff) {
    case 1:
        setParametersForDifficulty(gameState, EASY_BEG_VAL_KNOWLADGE, EASY_BEG_VAL, EASY_BEG_VAL, EASY_BEG_VAL);
        break;
    case 2:
        setParametersForDifficulty(gameState, NORMAL_BEG_VAL_KNOWLADGE, NORMAL_BEG_VAL, NORMAL_BEG_VAL, NORMAL_BEG_VAL);
        break;
    case 3:
        setParametersForDifficulty(gameState, HARD_BEG_VAL_KNOWLADGE, HARD_BEG_VAL_MENTALITY, HARD_BEG_VAL, HARD_BEG_VAL);
        break;
    default:
        std::cout << "Невалиден избор!";
    }
}

void saveIntoFile(GameState g, const char filename[]) {
    std::ofstream file(filename, std::ios::out | std::ios::in);

    if (!file) {
        file.open(filename);
    }

    file.seekp(0, std::ios::end);
    file << g.currentDay << " " << g.hours << " " << g.player.money << " "
        << g.player.energy << " " << g.player.mentality << " "
        << g.player.knowledge << " " << g.player.examsPassed << " "
        << g.examsDays[0] << " " << g.examsDays[1] << " "
        << g.examsDays[2] << " " << g.examsDays[3] << " "
        << g.examsDays[4] << "\n";
    file.close();
}

bool loadGameFromFile(GameState* g, char fileName[]) {
    std::ifstream file(fileName);
    if (!file) return false;

    while (file >> g->currentDay
        >> g->hours
        >> g->player.money
        >> g->player.energy
        >> g->player.mentality
        >> g->player.knowledge
        >> g->player.examsPassed
        >> g->examsDays[0]
        >> g->examsDays[1]
        >> g->examsDays[2]
        >> g->examsDays[3]
        >> g->examsDays[4]) {
    }

    file.close();
    return true;
}

void chooseHowToStartGame(GameState* gameState, char* fileName) {
    printStartMenu();
    int option;
    std::cin >> option;
    switch (option) {
    case 1: {
        int difficulty;
        std::cout << "Избери ниво на трудност: \n 1 - Лесно \n 2 - Нормално \n 3 - Трудно\n";
        std::cin >> difficulty;
        chooseDifficulty(difficulty, gameState);
        std::cout << "В кой файл искаш да пишеш?\n";
        std::cin.ignore(100, '\n');
        std::cin.getline(fileName, 100);
        myStrcat(fileName, ".txt");
        break;
    }
    case 2:
        std::cout << "От кой файл искаш да четеш?\n";
        std::cin.ignore(100, '\n');
        std::cin.getline(fileName, 100);
        myStrcat(fileName, ".txt");
        if (!loadGameFromFile(gameState, fileName)) {
            std::cout << "Грешка при зареждане на файла!\n";
        }
        if (gameState->hours <= 0) {
            printSleep(gameState);
            sleeping(gameState);
            gameState->currentDay++;
        }
        break;
    default:
        std::cout << "Невалиден избор";
        break;
    }
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    GameState gameState;
    enterExamDays(&gameState);
    char fileName[100];

    chooseHowToStartGame(&gameState, fileName);

    while (gameState.currentDay <= TOTAL_DAYS) {
        if (gameState.examsDays[getExamNumber(gameState) - 1] == gameState.currentDay) {
            std::cout << "Днес имаш изпит!\n";
        }

        bool skipActionToday = true;
        randomDailyEvent(gameState.player, skipActionToday);
        if (!skipActionToday) {
            gameState.currentDay++;
            continue;
        }

        while (gameState.hours > 0) {
            printStatus(gameState);
            printChooseAction();

            int action;
            std::cin >> action;
            switch (action) {
            case 1:
                chooseStudying(&gameState);
                break;
            case 2:
                eating(&gameState);
                break;
            case 3:
                goingOut(&gameState);
                break;
            case 4: {
                int restTime;
                std::cout << "Кoлко часа искаш да си починеш? ";
                std::cin >> restTime;
                gameState.hours -= restTime;
                resting(&gameState.player);
                break;
            }
            case 5:
                shiftWork(&gameState);
                break;
            case 6:
                goToDisco(&gameState);
                break;
            case 7:
                if (gameState.examsDays[getExamNumber(gameState) - 1] != gameState.currentDay) {
                    std::cout << "Днес няма изпит!\n";
                }
                takingExam(&gameState.player);
                if (passExam(&gameState))
                    std::cout << "Успешно издържа изпита!\n";
                else
                    std::cout << "Не успя да издържиш изпита.\n";
                break;
            case 11:
                std::cout << "Излизане от играта...\n";
                return 0;
            default:
                std::cout << "Невалиден избор!\n";
                break;
            }

            skipDay(&gameState);
            if (losingGame(gameState)) return 0;

            if (gameState.hours <= 8) {
                printSleep(&gameState);
                sleeping(&gameState);
                gameState.currentDay++;
                gameState.hours = 24;
                continue;
            }

            saveIntoFile(gameState, fileName);
        }
    }

    if (winningGame(gameState)) {
        printWinningGame();
    }

    return 0;
}
