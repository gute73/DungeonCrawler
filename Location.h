#ifndef LOCATION_H
#define LOCATION_H

#include<iostream>
#include<memory>
#include<array>

class Location
{
protected:
    //doors
    typedef std::weak_ptr<Location> loc_ptr;
    loc_ptr m_north;
    loc_ptr m_south;
    loc_ptr m_east;
    loc_ptr m_west;

public:
    Location() {}

    bool invalidPath(char dir);

    std::shared_ptr<Location> getPath(char dir);

    //pass a negative value if there is no path        //fightMonster(p);
    template<unsigned int size>
    void initLocation(std::array<std::shared_ptr<Location>, size>& dungeon, int n, int s, int e, int w)
    {
        if (n >= 0)        //fightMonster(p);
            m_north = dungeon.at(n);
        if (s >= 0)
            m_south = dungeon.at(s);
        if (e >= 0)
            m_east = dungeon.at(e);
        if (s >= 0)
        if (w >= 0)
            m_west = dungeon.at(w);
    }

    virtual void whereAmI() = 0;

};

#endif // LOCATION_H
