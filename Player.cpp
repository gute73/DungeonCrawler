#include "Player.h"

int Player::calcAttack(int str)
{
    if (str <= 4)
        return 1;
    else if (str <= 6)
        return 2;
    else if (str <= 8)
        return 3;
    else if (str <= 10)
        return 4;
    else if (str <= 12)
        return 5;
    else if (str <= 14)
        return 6;
    else if (str == 15)
        return 7;
    else if (str == 16)
        return 8;
    else if (str == 17)
        return 9;
    else if (str == 18)
        return 10;
    else if (str == 19)
        return 12;
    else
        return str/2 + 4;
    }

int Player::calcDefense(int con)
{
    if (con <= 6)
        return 1;
    else if (con <= 10)
        return 2;
    else if (con <= 12)
        return 3;
    else if (con <= 14)
        return 4;
    else if (con <= 16)
        return 5;
    else if (con == 17)
        return 6;
    else if (con == 18)
        return 7;
    else if (con == 19)
        return 8;
    else
        return con/2;
}

double Player::calcProbCrit(int dex)
{
    return dex*0.015;
}

double Player::calcProbDodge(int agi)
{
    return agi*0.02;
}

Player::Player(std::string name, int char_class)
    : Creature(name, 25, calcAttack(class_data[char_class].strength), calcDefense(class_data[char_class].constitution),
        calcProbCrit(class_data[char_class].dexterity), calcProbDodge(class_data[char_class].agility), 0), m_level(1), m_class(class_data[char_class].class_name), m_strength(class_data[char_class].strength),
        m_intelligence(class_data[char_class].intelligence), m_wisdom(class_data[char_class].wisdom), m_dexterity(class_data[char_class].dexterity),
        m_constitution(class_data[char_class].constitution), m_agility(class_data[char_class].agility) {}

void Player::levelUp()
{
    ++m_level;
    ++m_defense;
}

void Player::setAttack(int str)
{
    m_attack = Player::calcAttack(str);
}

void Player::setDefense(int con)
{
    m_defense = Player::calcDefense(con);
}

void Player::setProbCrit(int dex)
{
    m_prob_crit = Player::calcProbCrit(dex);
}

void Player::setProbDodge(int agi)
{
    m_prob_dodge = Player::calcProbDodge(agi);
}

Player::ClassData Player::class_data[Player::CLASS_MAX_CLASSES]
{
    { "warrior", 16, 8, 7, 10, 15, 10 },
    { "mage", 8, 16, 15, 8, 10, 12 },
    { "ninja", 12, 14, 12, 16, 12, 16 },
    { "paladin", 14, 10, 12, 10, 14, 10 }
};
