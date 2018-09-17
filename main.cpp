#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include "Creature.h"
#include "Monster.h"
#include "Player.h"
#include "Location.h"


int getRandomNumber(int min, int max)
{
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
	return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

//build dungeon
Location locationArray[25];



void attackMonster(Player &p, Monster &m)
{
    bool is_crit = p.critHit();
    int damage = p.damageDealt(m, is_crit);
    bool dodged = m.dodgeHit();
    if (!dodged)
    {
        m.reduceHealth(damage);
        if (is_crit)
            std::cout << "Critical hit! ";
        std::cout << "You hit the " << m.getName() << " for " << damage << " damage.\n";
    }
    else
        std::cout << "The " << m.getName() << " dodged your attack!\n";

    if (p.getAgi() >= 18)
    {
        if (!dodged)
        {
            is_crit = p.critHit();
            damage = p.damageDealt(m, is_crit);
            m.reduceHealth(damage);
            if (is_crit)
                std::cout << "Critical hit! ";
            std::cout << "You hit the " << m.getName() << " for " << damage << " damage.\n";
        }
    }
    else
        std::cout << "The " << m.getName() << " dodged your attack!\n";
}

void attackPlayer(Player &p, Monster &m)
{
    bool dodged = p.dodgeHit();
    if (!dodged)
    {
        bool is_crit = m.critHit();
        int damage = m.damageDealt(p, is_crit);
        p.reduceHealth(damage);
        if (is_crit)
            std::cout << "Critical hit! ";
        std::cout << "The " << m.getName() << " hit you for " << damage << " damage.\n";
    }
    else
        std::cout << "You dodged the attack!";
}

void fightMonster(Player &p)
{
    Monster m = Monster::getRandomMonster();
    std::cout << "You have encountered a " << m.getName() << ".\n";
    while(!p.isDead() && !m.isDead())
    {
        char fight_or_flight;
        do
        {
            std::cout << "(R)un or (F)ight: ";
            std::cin >> fight_or_flight;
        } while (((fight_or_flight != 'F') && (fight_or_flight != 'f')) && ((fight_or_flight != 'R') && (fight_or_flight != 'r')));

        if ((fight_or_flight == 'R') || (fight_or_flight == 'r'))
        {
            if (getRandomNumber(0, 1))
            {
                std::cout << "You successfully fled.\n";
                return;
            }
            else
                attackPlayer(p, m);
        }
        else
        {
            attackMonster(p, m);
            if (!m.isDead())
                attackPlayer(p, m);
        }
    }
    if (m.isDead())
    {
        std::cout << "You killed the " << m.getName() << ".\n";
// Gain XP?       p.levelUp();
//        std::cout << "You are now level " << p.getLevel() << ".\n";
        std::cout << "You found " << m.getGold() << " gold.\n";
        p.addGold(m.getGold());
    }
}

int inputClass()
{
    std::string class_selection;
	do
    {
        std::cout << "Choose a class: Warrior, Mage, Ninja, or Paladin: ";
        std::cin >> class_selection;
        class_selection[0] = tolower(class_selection[0]);
    } while ((class_selection != "warrior") && (class_selection != "mage") && (class_selection != "ninja") && (class_selection != "paladin"));
    if (class_selection == "warrior")
        return Player::CLASS_WARRIOR;
    else if (class_selection == "mage")
        return Player::CLASS_MAGE;
    else if (class_selection == "ninja")
        return Player::CLASS_NINJA;
    else
        return Player::CLASS_PALADIN;
}

int main()
{
	srand(static_cast<unsigned int>(time(0)));
	rand();

	// create character
	std::cout << "Name your character: ";
	std::string name;
	std::cin >> name;
    int char_class = inputClass();
    Player p(name, char_class);
	std::cout << "\nYou are the " <<  p.getClass() << " " << p.getName() << ".\n";
    std::cout << "Stats: Str: " << p.getStr() << " Int: " << p.getInt() << " Wis: " << p.getWis() << " Dex: " << p.getDex() << " Con: " << p.getCon() <<
    " Agi: " << p.getAgi() << " Attack: " << p.getAttack() << " Defense: " << p.getDefense() << '\n';

    // fight!
    do
    {
        fightMonster(p);
    } while (/*!p.hasWon() && */!p.isDead());

    // victory or defeat
/*    if (p.hasWon())
    {
        std::cout << "You have claimed final victory over your foes!\n";
        std::cout << "With " << p.getGold() << " gold, you have more than enough to begin building your own kingdom!\n";
    }
    else */ if (p.isDead())
    {
        std::cout << "You died at level " << p.getLevel() << " and with " << p.getGold() << " gold.\n";
        std::cout << "You can only hope that finding the treasure you left behind will become a small part of some greater hero's legend!";
    }

    return 0;
}
