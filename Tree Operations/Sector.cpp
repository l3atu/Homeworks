#include "Sector.h"
#include <cmath>

// Constructor implementation

Sector::Sector(int x, int y, int z) : x(x), y(y), z(z), left(nullptr), right(nullptr), parent(nullptr), color(RED) {

    distance_from_earth=sqrt(pow(x,2)+pow(y,2)+pow(z,2));
    int distance = static_cast<int>(distance_from_earth);
    sector_code=std::to_string(distance);

    if (x==0){
        sector_code+="S";
    }if (x>0){
        sector_code+="R";
    }if (x<0){
        sector_code+="L";
    }if (y==0){
        sector_code+="S";
    }if (y>0){
        sector_code+="U";
    }if (y<0){
        sector_code+="D";
    }if (z==0){
        sector_code+="S";
    }if (z>0){
        sector_code+="F";
    }if (z<0){
        sector_code+="B";
    }


        // TODO: Calculate the distance to the Earth, and generate the sector code
}

Sector::~Sector() {
    // TODO: Free any dynamically allocated memory if necessary
}

Sector& Sector::operator=(const Sector& other) {
    if (this != &other) {
        x = other.x;
        y = other.y;
        z = other.z;
    }

    // TODO: Overload the assignment operator
    return *this;
}

bool Sector::operator==(const Sector& other) const {
    return (x == other.x && y == other.y && z == other.z);
}

bool Sector::operator!=(const Sector& other) const {
    return !(*this == other);
}