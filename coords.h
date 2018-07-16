#ifndef COORDS_H
#define COORDS_H
#include "latlong.h"
#include <QDebug>
struct Coords
{
     Coords();
     Coords(LatLong lat_, LatLong lon_);
     LatLong mLat;
     LatLong mLon;
     void show();
};

#endif // COORDS_H
