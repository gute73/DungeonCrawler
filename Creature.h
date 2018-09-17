#ifndef CREATURE_H
#define CREATURE_H

#include <string>

class Creature
{
protected:
    std::string m_name;
    int m_health;
    int m_attack;
    int m_defense;
    double m_prob_crit;
    double m_prob_dodge;
    int m_gold;

public:
    Creature(std::string name, int health, int attack, int defense, double prob_crit, double prob_dodge, int gold);

    std::string& getName() { return m_name; }

    int getHealth() const { return m_health; }

    int getAttack() const { return m_attack; }

    int getDefense() const { return m_defense; }

    int getGold() const { return m_gold; }

    void reduceHealth(int reduce);

    int damageDealt(Creature &c, bool is_crit);

    bool critHit();

    bool dodgeHit();

    bool isDead();

    void addGold(int gold);
};

#endif // CREATURE_H
