//
// Created by danaa on 7/2/2020.
//

#ifndef EX3_CHARACTER_H
#define EX3_CHARACTER_H
#include "Auxiliaries.h"
#include "Exceptions.h"
#include <iostream>
#include <string>

namespace mtm {
    class Character {
    protected:
        units_t health;
        units_t ammo;
        units_t range;
        units_t power;
        units_t add_ammo;
        units_t steps;
        units_t ammo_count ;
        Team team;
    public:

        Character() = default;

        virtual ~Character()= default;

        /**
         * getHealth
         * @return health
         */

        virtual units_t getHealth() const = 0;//pure virtual

        /**
         * getAmmo
         * @return ammo
         */

        virtual units_t getAmmo() const = 0;//pure virtual

        /**
         * getRange
         * @return range
         */

        virtual units_t getRange() const = 0;//pure virtual

        /**
         * getPower
         * @return power
         */

        virtual units_t getPower() const = 0;//pure virtual

        /**
         * getTeam
         * @return team
         */
        virtual Team getTeam() const = 0;

        /**
         * CalculateSniperAttack
         * @return the number of the attack of the sniper (used to to know when to double the health)
         */

        virtual units_t CalculateSniperAttack() const = 0;//pure virtual
        /**
         * attack: lowers the ammo
         */
        virtual void attack() = 0; //pure virtual

        /**
         * reloads the ammo
         */
        virtual void reload() = 0;//pure virtual

        /** LowerHealthPoints
         * lowers the health points
         * @param health_points
         */
        virtual void LowerHealthPoints(units_t health_points) = 0; //pure virtual

        /**
         * clone
         * @return character clone
         */
        virtual Character* clone() const = 0;//pure virtual

        /**
         * CalculateMaxSteps
         * @return max steps of a character
         */
        virtual units_t CalculateMaxSteps() const = 0; //pure virtual


    };
}




#endif //EX3_CHARACTER_H
