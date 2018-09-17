#include "Monster.h"

int getRandomNumber(int min, int max);

Monster::Monster(Monster::MonsterType type) : Creature(monsterData[type].name, monsterData[type].health, monsterData[type].attack,
    monsterData[type].defense, monsterData[type].prob_crit, monsterData[type].prob_dodge, monsterData[type].gold) {}

Monster Monster::getRandomMonster()
{
    return Monster(static_cast<Monster::MonsterType>(getRandomNumber(0, Monster::MONSTERTYPE_MAX_TYPES-1)));
}


Monster::MonsterData Monster::monsterData[Monster::MONSTERTYPE_MAX_TYPES]
{
	{ "wyvern", 20, 6, 5, 0.2, 0.3, 30 },
	{ "orc", 10, 5, 2, 0.15, 0.1, 20 },
	{ "slime", 5, 4, 2, 0.1, 0.2, 10 }
};
