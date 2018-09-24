#ifndef ROOM_H
#define ROOM_H

#include "Location.h"

class Room: public Location
{
public:
    virtual void whereAmI();

};

#endif // ROOM_H
