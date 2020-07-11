//
// Created by danaa on 7/2/2020.
//
#include "Soldier.h"
#define ZERO_ATTACKS 0

mtm::Soldier::Soldier(mtm::units_t health, mtm::units_t ammo ,mtm::units_t range, mtm::units_t power, Team team){
    this->health = health;
    this->ammo = ammo;
    this->range = range;
    this->power = power;
    this->team = team;
    this->steps= 3;
    this->add_ammo = 3;
    this->ammo_count = 1;

}

mtm::units_t mtm::Soldier::getHealth() const {
    return health;
}

mtm::units_t mtm::Soldier::getAmmo() const {
    return ammo;
}


mtm::units_t mtm::Soldier::getPower() const {
    return power;
}

mtm::units_t mtm::Soldier::getRange() const {
    return range;
}


mtm::Team mtm::Soldier::getTeam() const {
    return team;
}


void mtm::Soldier::attack() {
    ammo--;
}

void mtm::Soldier::reload() {
    ammo += add_ammo;
}


void mtm::Soldier::LowerHealthPoints(mtm::units_t health_points)  {
    health -= health_points;
}

mtm::Character *mtm::Soldier::clone() const {
    return new Soldier(*this);
}

mtm::units_t mtm::Soldier::CalculateMaxSteps() const {
    return steps;
}

mtm::units_t mtm::Soldier::CalculateSniperAttack() const {
    return ZERO_ATTACKS;
}



