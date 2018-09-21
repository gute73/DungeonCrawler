#include "Creature.h"

int getRandomNumber(int min, int max);

Creature::Creature(std::string &name, int health, int attack, int defense, double prob_crit, double prob_dodge, int gold)
    : m_name(name), m_health(health), m_attack(attack), m_defense(defense), m_prob_crit(prob_crit), m_prob_dodge(prob_dodge), m_gold(gold) {}

void Creature::reduceHealth(int reduce)
{
    m_health -= reduce;
}

int Creature::damageDealt(Creature &c, bool is_crit)
{
    int base_damage = m_attack - c.getDefense();
    if (is_crit)
    {
        int crit_mod = getRandomNumber(5, 20) * .1 * (base_damage);
        return base_damage + ((crit_mod > 1) ? crit_mod : 1);
    }
    else
        return base_damage;
}

bool Creature::critHit()
{
    return (getRandomNumber(1, 100) <= m_prob_crit*100);
}

bool Creature::dodgeHit()
{
    return (getRandomNumber(1, 100) <= m_prob_dodge*100);
}

bool Creature::isDead()
{
    return (m_health <= 0);
}

void Creature::addGold(int gold)
{
    m_gold += gold;
}
