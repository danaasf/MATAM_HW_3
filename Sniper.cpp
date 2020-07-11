//
// Created by danaa on 02/07/2020.
//
#include "Sniper.h"

mtm::Sniper::Sniper(mtm::units_t health, mtm::units_t ammo, mtm::units_t range, mtm::units_t power, Team team) {
    this->health = health;
    this->ammo = ammo;
    this->range = range;
    this->power = power;
    this->team = team;
    this->attacks= 0;
    this->steps= 4;
    this->add_ammo = 2;
    this->ammo_count = 1;

}

mtm::units_t mtm::Sniper::getHealth() const {
    return health;
}

mtm::units_t mtm::Sniper::getAmmo() const {
    return ammo;
}


mtm::units_t mtm::Sniper::getPower() const {
    return power;
}

mtm::units_t mtm::Sniper::getRange() const {
    return range;
}


mtm::Team mtm::Sniper::getTeam() const {
    return team;
}


void mtm::Sniper::attack() {
    attacks++;
    ammo--;
}

void mtm::Sniper::reload() {
    ammo += add_ammo;
}


void mtm::Sniper::LowerHealthPoints(mtm::units_t health_points)  {
health -= health_points;
}

mtm::Character *mtm::Sniper::clone() const {
    return new Sniper(*this);
}

mtm::units_t mtm::Sniper::CalculateMaxSteps() const{
    return steps;
}

mtm::units_t mtm::Sniper::CalculateSniperAttack() const {
    return attacks;
}


