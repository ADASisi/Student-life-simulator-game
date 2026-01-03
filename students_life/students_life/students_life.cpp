#include <iostream>
#include <windows.h>

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

void clearConsole()
{
    system("cls");
}

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
    std::cout << "\n╔═════════════════════╗\n";
    std::cout << "║ Ден " << g.currentDay << " от 45         ║ \n";
    std::cout << "║ Пари: " << g.player.money << " лв      ║\n";
    std::cout << "║ Енергия: " << g.player.energy << " ⚡     ║\n";
    std::cout << "║ Психика: " << g.player.mentality << " 🧠     ║\n";
    std::cout << "║ Знания: " << g.player.knowledge << " 📚       ║\n";
    std::cout << "║ Взети изпити: " << g.player.examsPassed << " 🎓  ║\n";
    std::cout << "╚═════════════════════╝\n";
}

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

void printLosingGame()
{
    std::cout << "\n╔═════════════════════════════╗\n";
    std::cout << "║ 💥 ИГРАТА ПРИКЛЮЧИ!         ║\n";
    std::cout << "║ Твоята психика не издържа   ║\n";
    std::cout << "║ и си напуснал университета  ║\n";
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

bool losingGame(GameState g)
{
    if (g.player.mentality <= 0)
        return 1;
    if (g.player.money <= 0)
        return 1;
	return 0;
}


bool winningGame(GameState g)
{
    if (g.player.examsPassed == 5 && g.currentDay == 45)
        return 1;
    return 0;
}

int getExamNumber(GameState g)
{
    for (int i = 0; i < 5; i++)
    {
        if (g.examsDays[i] == g.currentDay)
        {
            return i + 1;
        }
    }
	return 0;
}

double sucessRateExam(GameState g)
{
	int penelty = (getExamNumber(g) - 1) * 5;
    return g.player.energy * 0.1 + g.player.knowledge * 0.75 + g.player.mentality * 0.1 + rand() % 100 + penelty;
}

bool passExam(GameState* g)
{
    double successRate = sucessRateExam(*g);
    if (successRate >= 75)
    {
        g->player.examsPassed += 1;
        return 1;
    }
    else
    {
		g->player.mentality -= 30;
		g->player.energy -= 20;
        return 0;
    }
}

void randomDailyEvent(Person& p, bool &skipActionToday) 
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
}

void skipDay(GameState* g)
{
    if (g->player.energy < 0)
    {
		std::cout << "Твоята енергия е твърде ниска! Пропускаш деня, за да се възстановиш.\n";
        g->player.energy = 40;
		g->player.mentality -= 10;
        g->currentDay++;
    }
}

void chooseDifficulty(int diff, GameState* gameState)
{
    switch (diff)
    {
    case 1:
        gameState->player.knowledge = EASY_BEG_VAL_KNOWLADGE;
        gameState->player.mentality = EASY_BEG_VAL;
        gameState->player.energy = EASY_BEG_VAL;
        gameState->player.money = EASY_BEG_VAL;
        break;
    case 2:
        gameState->player.knowledge = NORMAL_BEG_VAL_KNOWLADGE;
        gameState->player.mentality = NORMAL_BEG_VAL;
        gameState->player.energy = NORMAL_BEG_VAL;
        gameState->player.money = NORMAL_BEG_VAL;
        break;
    case 3:
        gameState->player.knowledge = HARD_BEG_VAL_KNOWLADGE;
        gameState->player.mentality = HARD_BEG_VAL_MENTALITY;
        gameState->player.energy = HARD_BEG_VAL;
        gameState->player.money = HARD_BEG_VAL;
        break;
    default:
        std::cout << "Невалиден избор!";
    }
}



int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
	GameState gameState;
	enterExamDays(&gameState);

    printStartMenu();

	int option;
	std::cin >> option;

    switch (option)
    {
        case 1:
            std::cout << "Избери ниво на трудност: \n 1 - Лесно \n 2 - Нормално \n 3 - Трудно\n";
            int difficulty;
            std::cin >> difficulty;
            chooseDifficulty(difficulty, &gameState);
			break;
        case 2:
            std::cout << "Функцията за зареждане от файл все още не е реализирана.\n";
			return 0;
            break;
        default:
            std::cout << "Невалиден избор";
            break;
    }

    while (gameState.currentDay < TOTAL_DAYS)
    {
        startDay:
		printStatus(gameState);
		printChooseAction();

        int action;
        bool skipActionToday = true;
        randomDailyEvent(gameState.player, skipActionToday);
        if (!skipActionToday)
        {
            gameState.currentDay++;
            continue;
        }
        std::cin >> action;
        switch (action)
        {
        case 1:
			int studyingChoice;
			std::cout << "Как искаш да учиш днес? \n 1 - Ходиш на лекции \n 2 - Учиш вкъщи \n 3 - Учиш с приятели \n";
			std::cin >> studyingChoice;
            switch (studyingChoice)
            {
                case 1:
                    goingToLetures(&gameState.player);
				    break;
                case 2:
					studyingAtHome(&gameState.player);
                    break;
				case 3:
                    studyingWithFriends(&gameState.player);
					break;
                default:
                    break;
            }
            break;
        case 2:
            eating(&gameState.player);
            break;
        case 3:
            goingOut(&gameState.player);
            break;
        case 4:
            sleeping(&gameState.player);
            break;
        case 5:
            shiftWork(&gameState.player);
            break;
        case 6:
            if(gameState.examsDays[getExamNumber(gameState)-1] != gameState.currentDay)
            {
                std::cout << "Днес няма изпит!\n";
                goto startDay;
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
            continue;
        }
        printStatus(gameState);
		skipDay(&gameState);
        if (losingGame(gameState))
        {
            printLosingGame();
            break;
        }
        if (winningGame(gameState))
        {
            printWinningGame();
            break;
        }
		gameState.currentDay++;
        //clearConsole();
    }
    
    return 0;
}


