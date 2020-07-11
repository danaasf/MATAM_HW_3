//
// Created by danaa on 7/2/2020.
//
#include "Medic.h"
#define ZERO_ATTACKS 0

mtm::Medic::Medic(mtm::units_t health, mtm::units_t ammo ,mtm::units_t range, mtm::units_t power, Team team){
    this->health = health;
    this->ammo = ammo;
    this->range = range;
    this->power = power;
    this->team = team;
    this->steps= 5;
    this->add_ammo = 5;
    this->ammo_count = 1;
}

mtm::units_t mtm::Medic::getHealth() const {
    return health;
}

mtm::units_t mtm::Medic::getAmmo() const {
    return ammo;
}


mtm::units_t mtm::Medic::getPower() const {
    return power;
}

mtm::units_t mtm::Medic::getRange() const {
    return range;
}


mtm::Team mtm::Medic::getTeam() const {
    return team;
}


void mtm::Medic::attack() {
    ammo--;
}

void mtm::Medic::reload() {
    ammo += add_ammo;
}


void mtm::Medic::LowerHealthPoints(mtm::units_t health_points)  {
    health -= health_points;
}

mtm::Character *mtm::Medic::clone() const {
    return new Medic(*this);
}

mtm::units_t mtm::Medic::CalculateMaxSteps() const{
    return steps;
}

mtm::units_t mtm::Medic::CalculateSniperAttack() const {
    return  ZERO_ATTACKS;
}


