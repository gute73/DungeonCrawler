#ifndef MONSTER_H
#define MONSTER_H

#include "Creature.h"

class Monster: public Creature
{
public:
    enum MonsterType
    {
        MONSTERTYPE_DRAGON,
        MONSTERTYPE_ORC,
        MONSTERTYPE_SLIME,
        MONSTERTYPE_MAX_TYPES
    };

    struct MonsterData
    {
        std::string name;
        int health;
        int attack;
        int defense;
        double prob_crit;
        double prob_dodge;
        int gold;
    };

    static MonsterData monsterData[MONSTERTYPE_MAX_TYPES];

    Monster(MonsterType type);

    static Monster getRandomMonster();

};

#endif // MONSTER_H

