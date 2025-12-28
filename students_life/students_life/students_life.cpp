#include <iostream>

const int TOTAL_DAYS = 45;
const int EASY_BEG_VAL_KNOWLADGE = 80;
const int EASY_BEG_VAL = 100;
const int NORMAL_BEG_VAL_KNOWLADGE = 50;
const int NORMAL_BEG_VAL = 80;
const int HARD_BEG_VAL_KNOWLADGE = 35;
const int HARD_BEG_VAL = 60;
const int HARD_BEG_VAL_MENTALITY = 40;

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

void enterExamDays(GameState* gs)
{
    gs->examsDays[0] = 8;
    gs->examsDays[1] = 17;
    gs->examsDays[2] = 26;
    gs->examsDays[3] = 30 + rand() % 10;
    gs->examsDays[4] = 45;
}

void printStatus(GameState g) 
{
    std::cout << "\n╔═══════════════════════════╗\n";
    std::cout << "║ Ден " << g.currentDay << " от 45\n";
    std::cout << "║ Пари: " << g.player.money << " лв\n";
    std::cout << "║ Енергия: " << g.player.energy << " ⚡\n";
    std::cout << "║ Психика: " << g.player.mentality << " 🧠\n";
    std::cout << "║ Знания: " << g.player.knowledge << " 📚\n";
    std::cout << "║ Взети изпити: " << g.player.examsPassed << " 🎓\n";
    std::cout << "╚═══════════════════════════╝\n";
}

bool losingGame(GameState g)
{
    if (g.player.mentality < 0)
        return 1;
    if (g.player.money < 0)
        return 1;
	return 0;
}


bool winningGame(GameState g)
{
    if (g.player.examsPassed == 5 && g.currentDay == 45)
        return 1;
    return 0;
}


int main()
{
	GameState gameState;
	enterExamDays(&gameState);

    std::cout << "Избери ниво на трудност: \n 1 - Лесно \n 2 - Нормално \n 3 - Трудно";

	int difficulty;
	std::cin >> difficulty;
    switch (difficulty)
    {
        case 1:
            gameState.player.knowledge = EASY_BEG_VAL_KNOWLADGE;
            gameState.player.mentality = EASY_BEG_VAL;
            gameState.player.energy = EASY_BEG_VAL;
            gameState.player.money = EASY_BEG_VAL;
		    break;
        case 2:
			gameState.player.knowledge = NORMAL_BEG_VAL_KNOWLADGE;
			gameState.player.mentality = NORMAL_BEG_VAL;
			gameState.player.energy = NORMAL_BEG_VAL;
			gameState.player.money = NORMAL_BEG_VAL;
            break;
		case 3:
			gameState.player.knowledge = HARD_BEG_VAL_KNOWLADGE;    
            gameState.player.mentality = HARD_BEG_VAL_MENTALITY;
            gameState.player.energy = HARD_BEG_VAL;
            gameState.player.money = HARD_BEG_VAL;
			break;
        default:
            std::cout << "Невалиден избор!";
			return 0;
    }





    return 0;
}


