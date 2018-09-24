#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <array>
#include <memory>
#include "Creature.h"
#include "Monster.h"
#include "Player.h"
#include "Location.h"
#include "Tunnel.h"
#include "Room.h"
#include "Shop.h"
#include "TreasureRoom.h"
#include "Nest.h"


int getRandomNumber(int min, int max)
{
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
	return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

// combat
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
        std::cout << "You dodged the attack!\n";
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

//input class at setup
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

	//build dungeon
    constexpr unsigned int dungeon_size = 25;
    std::array<std::shared_ptr<Location>, dungeon_size> dungeon { std::make_shared<Shop>(), std::make_shared<Room>(),
        std::make_shared<Tunnel>(), std::make_shared<TreasureRoom>(), std::make_shared<Room>(), std::make_shared<Tunnel>(),
        std::make_shared<Tunnel>(), std::make_shared<Tunnel>(), std::make_shared<Room>(), std::make_shared<Tunnel>(),
        std::make_shared<Tunnel>(), std::make_shared<Room>(), std::make_shared<Tunnel>(), std::make_shared<Tunnel>(),
        std::make_shared<Tunnel>(), std::make_shared<Tunnel>(), std::make_shared<Tunnel>(), std::make_shared<Tunnel>(),
        std::make_shared<Tunnel>(), std::make_shared<Tunnel>(), std::make_shared<Shop>(), std::make_shared<Room>(),
        std::make_shared<Tunnel>(), std::make_shared<Tunnel>(), std::make_shared<Nest>() };

    //connect rooms
    dungeon.at(0)->initLocation(dungeon,-1,-1,1,-1);
    dungeon.at(1)->initLocation(dungeon,-1,6,2,0);
    dungeon.at(2)->initLocation(dungeon,-1,-1,3,1);
    dungeon.at(3)->initLocation(dungeon,-1,-1,-1,2);
    dungeon.at(4)->initLocation(dungeon,-1,9,-1,-1);
    dungeon.at(5)->initLocation(dungeon,-1,10,6,-1);
    dungeon.at(6)->initLocation(dungeon,1,-1,7,5);
    dungeon.at(7)->initLocation(dungeon,-1,12,8,6);
    dungeon.at(8)->initLocation(dungeon,-1,13,9,7);
    dungeon.at(9)->initLocation(dungeon,4,-1,-1,8);
    dungeon.at(10)->initLocation(dungeon,5,-1,11,-1);
    dungeon.at(11)->initLocation(dungeon,-1,16,12,10);
    dungeon.at(12)->initLocation(dungeon,7,-1,-1,11);
    dungeon.at(13)->initLocation(dungeon,8,-1,14,-1);
    dungeon.at(14)->initLocation(dungeon,-1,19,-1,13);
    dungeon.at(15)->initLocation(dungeon,-1,-1,16,-1);
    dungeon.at(16)->initLocation(dungeon,11,21,17,15);
    dungeon.at(17)->initLocation(dungeon,-1,-1,18,16);
    dungeon.at(18)->initLocation(dungeon,-1,-1,19,17);
    dungeon.at(19)->initLocation(dungeon,14,-1,-1,18);
    dungeon.at(20)->initLocation(dungeon,-1,-1,21,-1);
    dungeon.at(21)->initLocation(dungeon,16,-1,22,20);
    dungeon.at(22)->initLocation(dungeon,-1,-1,23,21);
    dungeon.at(23)->initLocation(dungeon,-1,-1,24,22);
    dungeon.at(24)->initLocation(dungeon,-1,-1,-1,23);


	// create character
	std::cout << "Name your character: ";
	std::string name;
	std::cin >> name;
    int char_class = inputClass();
    Player p(name, char_class, dungeon[15]);
	std::cout << "\nYou are the " <<  p.getClass() << " " << p.getName() << ".\n";
    std::cout << "Stats: Str: " << p.getStr() << " Int: " << p.getInt() << " Wis: " << p.getWis() << " Dex: " << p.getDex() << " Con: " << p.getCon() <<
    " Agi: " << p.getAgi() << " Attack: " << p.getAttack() << " Defense: " << p.getDefense() << '\n';

    // begin!
    p.getLocation()->whereAmI();
    do
    {
        p.movePlayer();
        //fightMonster(p);
    } while (!p.isDead());

if (p.isDead())
    {
        std::cout << "You died at level " << p.getLevel() << " and with " << p.getGold() << " gold.\n";
        std::cout << "You can only hope that finding the treasure you left behind will become a small part of some greater hero's legend!";
    }

    return 0;
}
