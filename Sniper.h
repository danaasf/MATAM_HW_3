//
// Created by danaa on 02/07/2020.
//

#ifndef HW3_SNIPER_H
#define HW3_SNIPER_H

#include "Character.h"

#include <iostream>
#include <string>

namespace mtm{
class Sniper: public mtm::Character{

    //we need the number of attacks for the sniper
        units_t attacks;

    public:
        Sniper(units_t health,units_t ammo,units_t range,units_t power,Team team);

        ~Sniper() override = default;

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

#endif //HW3_SNIPER_H
