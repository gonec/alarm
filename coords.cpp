#include "coords.h"

Coords::Coords(){}
Coords::Coords(LatLong lat_, LatLong lon_){
    mLat = lat_;
    mLon = lon_;
}
void Coords::show(){
   mLat.show();
   mLon.show();
}
