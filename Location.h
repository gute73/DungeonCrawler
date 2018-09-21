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

    bool validLocation(char dir);

    loc_ptr& getLocation(char dir);

    //pass a negative value if there is no path
    template<unsigned int size>
    void initLocation(std::array<std::shared_ptr<Location>, size>& dungeon, int n, int s, int e, int w)
    {
        if (n >= 0)
            m_north = dungeon.at(n);
        if (s >= 0)
            m_south = dungeon.at(s);
        if (e >= 0)
            m_east = dungeon.at(e);
        if (w >= 0)
            m_west = dungeon.at(w);
    }

};

#endif // LOCATION_H
