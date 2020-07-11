//
// Created by danaa on 7/1/2020.
//

#ifndef EX3_GAME_H
#define EX3_GAME_H

#include "Auxiliaries.h"
#include "Matrix.h"
#include "Exceptions.h"
#include "Character.h"
#include "Soldier.h"
#include "Medic.h"
#include "Sniper.h"
#include <string>
#include <memory>
#include <iostream>

namespace mtm {
    class Game {

        Matrix<std::shared_ptr<Character>> game_board;
    public:

        /**
         * constructor that creates a new game starting with an empty game board
         * @param height : of the board
         * @param width : of the board
         */
        explicit Game(int height, int width);

        /**
         * a virtual default destructor
         */

        virtual ~Game() = default;

        /**
         *
         * @param copy constructor
         */
        Game(const Game& other);

        /**
         * operating =
         * @param other
         * @return the game after placement
         */

        Game& operator=(const Game& other);

        /**
         *adds to the board a new character
         * @param coordinates: the coordinates of the character
         * @param character: the given character
         */

        void addCharacter(const GridPoint& coordinates, std::shared_ptr<Character> character);


        /**
         *
         * @param type : type of the charcater
         * @param team : the team
         * @param health : health of the charcater
         * @param ammo : ammo of the charcater
         * @param range : range of the charcater
         * @param power : power points of the charcater
         * @return a new character with the previous properties
         */
        static std::shared_ptr<Character> makeCharacter(CharacterType type, Team team, units_t health, units_t ammo, units_t range, units_t power);

        /**
         * a method that moves the character in the board according to the given coordinates
         * @param src_coordinates : original placement
         * @param dst_coordinates : wanted placement
         */
        void move(const GridPoint & src_coordinates, const GridPoint & dst_coordinates);


        //static helping functions for attacking characters
        void attackSoldier(const mtm::GridPoint &src_coordinates, const mtm::GridPoint &dst_coordinates);
        void attackMedic(const mtm::GridPoint &src_coordinates, const mtm::GridPoint &dst_coordinates);
        void attackSniper(const mtm::GridPoint &src_coordinates, const mtm::GridPoint &dst_coordinates);

        /**
        * a method that in which the character in the source placement attacks the one in the destination placement
        * @param src_coordinates : place of attacker
        * @param dst_coordinates :place of the one getting attacked
        */

        void attack(const GridPoint & src_coordinates, const GridPoint & dst_coordinates);

        /**
         * reloads the ammo of the character in the correct coordinates as given
         * @param coordinates
         */
        void reload(const GridPoint & coordinates);

        /**
         * boardFilling : helper function to fill the board
         * @param game
         * @return board
         */
        static std::string boardFilling (const Game &game);

        //printing operator , friend because we need access to private fields in the class
        friend std::ostream &operator<<(std::ostream &os, const Game &game);//operator << uses the printing function in Auxiliaries

        /**
         * a method that check if a victory accured
         * @param winningTeam
         * @return if it won true otherwise false
         */
        bool isOver(Team* winningTeam=NULL) const;


        void checkExceptions(const GridPoint & src_coordinates, const GridPoint & dst_coordinates);

    };
    // needs to be defined outside the class as well
    std::ostream &operator<<(std::ostream &os, const Game &game);
}

#endif //EX3_GAME_H
