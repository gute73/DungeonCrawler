#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cctype>


int getRandomNumber(int min, int max)
{
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
	return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

class Location
{
protected:


public:

};

class Tunnel: public Location
{

};

class Room: public Location
{

};

class Shop: public Location
{

};

class TreasureRoom: public Location
{

};

class Nest: public Location
{

};

//build dungeon
Location locationArray[25];

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
    Creature(std::string name, int health, int attack, int defense, double prob_crit, double prob_dodge, int gold)
    : m_name(name), m_health(health), m_attack(attack), m_defense(defense), m_prob_crit(prob_crit), m_prob_dodge(prob_dodge), m_gold(gold) {}

    std::string& getName() { return m_name; }

    int getHealth() const { return m_health; }

    int getAttack() const { return m_attack; }

    int getDefense() const { return m_defense; }

    int getGold() const { return m_gold; }

    void reduceHealth(int reduce)
    {
        m_health -= reduce;
    }

    int damageDealt(Creature &c, bool is_crit)
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

    bool critHit()
    {
        return (getRandomNumber(1, 100) <= m_prob_crit*100);
    }

    bool dodgeHit()
    {
        return (getRandomNumber(1, 100) <= m_prob_dodge*100);
    }

    bool isDead()
    {
        return (m_health <= 0);
    }

    void addGold(int gold)
    {
        m_gold += gold;
    }

};

class Player: public Creature
{
private:
    int m_level;
    std::string m_class;
    int m_strength;
    int m_intelligence;
    int m_wisdom;
    int m_dexterity;
    int m_constitution;
    int m_agility;

public:
    enum CharClass
    {
        CLASS_WARRIOR,
        CLASS_MAGE,
        CLASS_NINJA,
        CLASS_PALADIN,
        CLASS_MAX_CLASSES
    };

    struct ClassData
    {
        std::string class_name;
        int strength;
        int intelligence;
        int wisdom;
        int dexterity;
        int constitution;
        int agility;
    };

    static ClassData class_data[CLASS_MAX_CLASSES];

    int calcAttack(int str)
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

    int calcDefense(int con)
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

    double calcProbCrit(int dex)
    {
        return dex*0.015;
    }

    double calcProbDodge(int agi)
    {
        return agi*0.02;
    }


    Player(std::string name, int char_class)
    : Creature(name, 25, calcAttack(class_data[char_class].strength), calcDefense(class_data[char_class].constitution),
        calcProbCrit(class_data[char_class].dexterity), calcProbDodge(class_data[char_class].agility), 0), m_level(1), m_class(class_data[char_class].class_name), m_strength(class_data[char_class].strength),
        m_intelligence(class_data[char_class].intelligence), m_wisdom(class_data[char_class].wisdom), m_dexterity(class_data[char_class].dexterity),
        m_constitution(class_data[char_class].constitution), m_agility(class_data[char_class].agility) {}

    void levelUp()
    {
        ++m_level;
        ++m_defense;
    }

    int getLevel() const { return m_level; }

    std::string getClass() const { return m_class; }

    int getStr() const { return m_strength; }

    int getInt() const { return m_intelligence; }

    int getWis() const { return m_wisdom; }

    int getDex() const { return m_dexterity; }

    int getCon() const { return m_constitution; }

    int getAgi() const { return m_agility; }

    void setAttack(int str)
    {
        m_attack = calcAttack(str);
    }

    void setDefense(int con)
    {
        m_defense = calcDefense(con);
    }

    void setProbCrit(int dex)
    {
        m_prob_crit = calcProbCrit(dex);
    }

    void setProbDodge(int agi)
    {
        m_prob_dodge = calcProbDodge(agi);
    }

//    bool hasWon() { return (m_level >= 20); }

};

Player::ClassData Player::class_data[Player::CLASS_MAX_CLASSES]
{
    { "warrior", 16, 8, 7, 10, 15, 10 },
    { "mage", 8, 16, 15, 8, 10, 12 },
    { "ninja", 12, 14, 12, 16, 12, 16 },
    { "paladin", 14, 10, 12, 10, 14, 10 }
};

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

    Monster(MonsterType type)
    : Creature(monsterData[type].name, monsterData[type].health, monsterData[type].attack, monsterData[type].defense, monsterData[type].prob_crit,
               monsterData[type].prob_dodge, monsterData[type].gold) {}

    static Monster getRandomMonster()
    {
        return Monster(static_cast<MonsterType>(getRandomNumber(0, MONSTERTYPE_MAX_TYPES-1)));
    }
};

Monster::MonsterData Monster::monsterData[Monster::MONSTERTYPE_MAX_TYPES]
{
	{ "wyvern", 20, 6, 5, 0.2, 0.3, 30 },
	{ "orc", 10, 5, 2, 0.15, 0.1, 20 },
	{ "slime", 5, 4, 2, 0.1, 0.2, 10 }
};

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
