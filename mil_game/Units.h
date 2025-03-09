#ifndef UNIT_TYPES_H
#define UNIT_TYPES_H 
#include <string>
#include <unordered_map>

enum class UnitCategory {
    Infantry,
    Mechanized,
    Armored,
    Artillery,
    SurfaceNavy,
    SubSurfaceNavy,
    Airforce,
    Space
};

enum class DamageTypes {
    LightDamage,            // heavily inspired by HOI4 here
    HeavyDamage,
    AntiAirDamage,
};

class Unit {
    public: 
    UnitCategory category;
    std::string name;
    int health;
    int armor;
    private: int cohesion = 100;           //basically org from HOI4, starting cohesion should work like a percentage
    std::unordered_map<DamageTypes, int> attack_pwr_by_type;
    std::unordered_map<DamageTypes, int> type_resistance;
    
    Unit(UnitCategory category, std::string name, int health, int armor,
    std::unordered_map<DamageTypes, int> attack_pwr_by_type, std:: unordered_map
    <DamageTypes, int> type_resistance) {}


};

class Infantry : public Unit {
    UnitCategory category = UnitCategory::Infantry;
    int health = 100;
    int armor = 25;
    private: int cohesion = 100;
};


#endif 