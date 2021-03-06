#ifndef PLAYER_H
#define PLAYER_H

#include "Creature.h"
#include "Location.h"
#include <memory>
#include <string>

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
    std::shared_ptr<Location> m_location;
    char m_direction;

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

    int calcAttack(int str);

    int calcDefense(int con);

    double calcProbCrit(int dex);

    double calcProbDodge(int agi);

    Player(std::string &name, int char_class, std::shared_ptr<Location> pos);

    void levelUp();

    int getLevel() const { return m_level; }

    std::string getClass() const { return m_class; }

    int getStr() const { return m_strength; }

    int getInt() const { return m_intelligence; }

    int getWis() const { return m_wisdom; }

    int getDex() const { return m_dexterity; }

    int getCon() const { return m_constitution; }

    int getAgi() const { return m_agility; }

    std::shared_ptr<Location>& getLocation() { return m_location; }

    char getDirection() const { return m_direction; }

    void setAttack(int str);

    void setDefense(int con);

    void setProbCrit(int dex);

    void setProbDodge(int agi);

    char left();

    char right();

    char behind();

    // accepts char 'l' or 'r' or 'b'
    void changeDirection(char turn);

    void movePlayer();

};

#endif // PLAYER_H
