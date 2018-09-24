#include "Location.h"

    bool Location::invalidPath(char dir)
    {
        switch (dir)
        {
            case 'n':
                return !(m_north.lock());
            case 's':
                return !(m_south.lock());
            case 'e':
                return !(m_east.lock());
            default:
                return !(m_west.lock());
        }
    }

    std::shared_ptr<Location> Location::getPath(char dir)
    {
        switch (dir)
        {
            case 'n':
                return m_north.lock();
            case 's':
                return m_south.lock();
            case 'e':
                return m_east.lock();
            default:
                return m_west.lock();
        }
    }

