//
// Created by danaa on 7/2/2020.
//

#ifndef EX3_SOLDIER_H
#define EX3_SOLDIER_H
#include <iostream>
#include <string>
#include "Character.h"

namespace mtm{
class Soldier: public mtm::Character {
    public:

public:
    Soldier(units_t health,units_t ammo,units_t range,units_t power,Team team);

    ~Soldier() override = default;

    units_t getHealth() const override;

    units_t getAmmo() const override;

    units_t getRange() const override;

    units_t getPower() const override;

    Team getTeam() const override;

    void attack() override;

    void reload() override;

    void LowerHealthPoints (units_t health_points) override;

    Character *clone() const override;

    units_t CalculateMaxSteps() const override;

    units_t CalculateSniperAttack() const override;
};
}

#endif //EX3_SOLDIER_H
