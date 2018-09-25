#include "Player.h"
#include <iostream>

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

Player::Player(std::string &name, int char_class, std::shared_ptr<Location> pos)
    : Creature(name, 25, calcAttack(class_data[char_class].strength), calcDefense(class_data[char_class].constitution),
        calcProbCrit(class_data[char_class].dexterity), calcProbDodge(class_data[char_class].agility), 0), m_level(1), m_class(class_data[char_class].class_name), m_strength(class_data[char_class].strength),
        m_intelligence(class_data[char_class].intelligence), m_wisdom(class_data[char_class].wisdom), m_dexterity(class_data[char_class].dexterity),
        m_constitution(class_data[char_class].constitution), m_agility(class_data[char_class].agility), m_location(pos), m_direction('e') {}

void Player::levelUp()
{
    ++m_level;
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

char Player::left()
{
    switch (m_direction)
    {
        case 'n':
            return 'w';
        case 'e':
            return 'n';
        case 's':
            return 'e';
        default:
            return 's';
    }
}

char Player::right()
{
    switch (m_direction)
    {
        case 'n':
            return 'e';
        case 'e':
            return 's';
        case 's':
            return 'w';
        default:
            return 'n';
    }
}

char Player::behind()
{
    switch (m_direction)
    {
        case 'n':
            return 's';
        case 'e':
            return 'w';
        case 's':
            return 'n';
        default:
            return 'e';
    }
}

void Player::changeDirection(char turn)
{
    if (turn == 'l')
        m_direction = left();
    else if (turn == 'r')
        m_direction = right();
    else
        m_direction = behind();
}

void Player::movePlayer()
{
    bool inv_ahead = m_location->invalidPath(m_direction);
    bool inv_left = m_location->invalidPath(left());
    bool inv_right = m_location->invalidPath(right());
    bool inv_behind = m_location->invalidPath(behind());
    char choice;
    bool valid;
    do
    {
        if (!inv_ahead)
            std::cout << "There is a pathway straight ahead. ";
        if (!inv_left)
        {
            if (!inv_right)
                std::cout << "There are paths to the left and the right. ";
            else
                std::cout << "There is a path to the left. ";
        }
        else if (!inv_right)
            std::cout << "There is a path to the right.\n";
        std::cout << "Enter 'a' to move ahead, 'l' to move left, 'r' to move right, or 'b' to turn around and move back.\n";
        std::cin >> choice;
        valid = true;
        switch (choice)
        {
            case 'a': case 'A':
                if (inv_ahead)
                {
                    std::cout << "That is not a valid direction.\n";
                    valid = false;
                }
                break;
            case 'l': case 'L':
                if (inv_left)
                {
                    std::cout << "That is not a valid direction.\n";
                    valid = false;
                }
                break;
            case 'r': case 'R':
                if (inv_right)
                {
                    std::cout << "That is not a valid direction.\n";
                    valid = false;
                }
                break;
            case 'b': case 'B':
                if (inv_behind)
                {
                    std::cout << "That is not a valid direction.\n";
                    valid = false;
                }
                break;
        }
    } while ((choice != 'a') && (choice != 'A') && (choice != 'l') && (choice != 'L') && (choice != 'r')
             && (choice != 'R') && (choice != 'b') && (choice != 'B') && (!valid));

    switch (choice)
    {
        case 'a': case 'A':
            m_location = m_location->getPath(m_direction);
            break;
        case 'l': case 'L':
            changeDirection('l');
            m_location = m_location->getPath(m_direction);
            break;
        case 'r': case 'R':
            changeDirection('r');
            m_location = m_location->getPath(m_direction);
            break;
        case 'b': case 'B':
            changeDirection('b');
            m_location = m_location->getPath(m_direction);
            break;
    }

    m_location->whereAmI();
}

Player::ClassData Player::class_data[Player::CLASS_MAX_CLASSES]
{
    { "warrior", 16, 8, 7, 10, 15, 10 },
    { "mage", 8, 16, 15, 8, 10, 12 },
    { "ninja", 12, 14, 12, 16, 12, 16 },
    { "paladin", 14, 10, 12, 10, 14, 10 }
};
