#include "Location.h"

    bool Location::validLocation(char dir)
    {
        if (dir == 'n')
            return !(m_north.lock());
        else if (dir == 's')
            return !(m_south.lock());
        else if (dir == 'e')
            return !(m_east.lock());
        else if (dir == 'w')
            return !(m_west.lock());
    }

    Location::loc_ptr& Location::getLocation(char dir)
    {
         if (dir == 'n')
            return m_north;
        else if (dir == 's')
            return m_south;
        else if (dir == 'e')
            return m_east;
        else if (dir == 'w')
            return m_west;
    }
