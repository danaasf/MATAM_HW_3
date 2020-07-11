//
// Created by danaa on 7/1/2020.
//

#include "Game.h"
#include "Auxiliaries.h"
#include "Exceptions.h"
#include <memory>
#include <cmath>


mtm::Game::Game(int height, int width) : game_board(mtm::Dimensions(1,1),nullptr){
    if(height <= 0 || width <= 0) {
        throw IllegalArgument();
    }
    game_board = Matrix<std::shared_ptr<Character>>(mtm::Dimensions(height,width),nullptr);
}


mtm::Game::Game(const mtm::Game &other) : game_board(Dimensions(other.game_board.height(),other.game_board.width()),nullptr) {
    int i=0,j=0;
    for (i=0; i <other.game_board.height(); i++) {
        for (j=0; j <other.game_board.width(); j++) {
            if (other.game_board(i,j) != nullptr){
                std::shared_ptr<Character> character(other.game_board(i,j)->clone());
                game_board(i,j)=character;
            }
        }
    }
}

mtm::Game &mtm::Game::operator=(const mtm::Game &other){
    if (&other != this) {
        game_board=Matrix<std::shared_ptr<Character>>(mtm::Dimensions(other.game_board.height(),other.game_board.width()));
        int i=0,j=0;
        for (i=0; i<other.game_board.height(); i++) {
            for (j=0; j<other.game_board.width(); j++){
                if (other.game_board(i,j) != nullptr) {
                    std::shared_ptr<Character> character(other.game_board(i,j)->clone());
                    game_board(i,j) = character;
                }
            }
        }
    }
    return *this;
}

void mtm::Game::addCharacter(const mtm::GridPoint &coordinates, std::shared_ptr<Character> character) {
    if (coordinates.col< 0 || coordinates.row <0 || coordinates.col >= game_board.width() || coordinates.row >= game_board.height()) {
        throw IllegalCell();
    }
    if(game_board(coordinates.row,coordinates.col) != nullptr){
        throw CellOccupied();
    }
    game_board(coordinates.row,coordinates.col) = character;
}

std::shared_ptr<mtm::Character>
mtm::Game::makeCharacter(mtm::CharacterType type, mtm::Team team, mtm::units_t health, mtm::units_t ammo, mtm::units_t range, mtm::units_t power) {
    if(health<= 0 || ammo<0 || range< 0 || power<0){
        throw IllegalArgument();
    }
    std::shared_ptr<Character> current_character;
    //checking current character type
    if(type == SOLDIER){
        std::shared_ptr<Character> new_character(new Soldier(health,ammo,range,power,team));
        current_character=new_character;
    } else {
        if(type == MEDIC) {
            std::shared_ptr<Character> new_character(new Medic(health,ammo,range,power,team));
            current_character= new_character;
        } else {
            std::shared_ptr<Character> new_character(new Sniper(health,ammo,range,power,team));
            current_character=new_character;
        }
    }
    return current_character;
}


void mtm::Game::move(const mtm::GridPoint &src_coordinates, const mtm::GridPoint &dst_coordinates) {
    if(dst_coordinates.col < 0 || dst_coordinates.row <0 || src_coordinates.col < 0 || src_coordinates.row <0
    || src_coordinates.row >= game_board.height() || src_coordinates.col >= game_board.width()
    || dst_coordinates.col >= game_board.width() || dst_coordinates.row >= game_board.height() ) {
        throw IllegalCell();
    }
    //the order like in the pdf?
    //check empty
    if(game_board(src_coordinates.row,src_coordinates.col) == nullptr){
        throw CellEmpty();
    }
    if(mtm::GridPoint::distance(src_coordinates,dst_coordinates) > game_board(src_coordinates.row,src_coordinates.col)->CalculateMaxSteps()){
        throw MoveTooFar();
    }
    //check occupied
    if(game_board(dst_coordinates.row,dst_coordinates.col) != nullptr){
        throw CellOccupied();
    }


    //placing 
    game_board(dst_coordinates.row,dst_coordinates.col) = game_board(src_coordinates.row,src_coordinates.col);
    game_board(src_coordinates.row,src_coordinates.col) = nullptr;
}

void mtm::Game::checkExceptions(const mtm::GridPoint &src_coordinates, const mtm::GridPoint &dst_coordinates) {
        //exceptions should be thrown in order ?
        if (mtm::GridPoint::distance(src_coordinates, dst_coordinates) >
            game_board(src_coordinates.row, src_coordinates.col)->getRange()) {
            throw OutOfRange();
        } else {
            if (game_board(src_coordinates.row, src_coordinates.col)->getAmmo() == 0) {
                throw OutOfAmmo();
            }
        }
}


void mtm::Game::attackSoldier(const mtm::GridPoint &src_coordinates, const mtm::GridPoint &dst_coordinates) {
    if(game_board(src_coordinates.row,src_coordinates.col)->CalculateMaxSteps() == 3) {
        checkExceptions(src_coordinates,dst_coordinates);
        if ((src_coordinates.row != dst_coordinates.row && src_coordinates.col != dst_coordinates.col)) {
            throw IllegalTarget();
        }
    game_board(src_coordinates.row, src_coordinates.col)->attack();
    if ((game_board(dst_coordinates.row, dst_coordinates.col) != nullptr) &&
        (game_board(dst_coordinates.row, dst_coordinates.col)->getTeam() != game_board(src_coordinates.row, src_coordinates.col)->getTeam())) {
                game_board(dst_coordinates.row, dst_coordinates.col)->LowerHealthPoints( game_board(src_coordinates.row, src_coordinates.col)->getPower());
                if (game_board(dst_coordinates.row, dst_coordinates.col)->getHealth() <= 0) {
                    game_board(dst_coordinates.row, dst_coordinates.col) = nullptr;
                }
            }

    int i=0,j=0;
    for (i=0; i <game_board.height(); i++) {
        for (j=0; j < game_board.width(); j++) {
            if (mtm::GridPoint::distance(dst_coordinates, GridPoint(i, j)) <=
                ceil((double) game_board(src_coordinates.row, src_coordinates.col)->getRange() / 3)) {
                if ((game_board(i, j) != nullptr) &&
                    (game_board(i, j)->getTeam() != game_board(src_coordinates.row, src_coordinates.col)->getTeam())) {
                    game_board(i, j)->LowerHealthPoints(
                            ceil((double) game_board(src_coordinates.row, src_coordinates.col)->getPower() / 2));
                    if (game_board(i, j)->getHealth() <= 0) {
                        game_board(i, j) = nullptr;
                    }
                }
            }
        }
    }
    }
}


void mtm::Game::attackMedic (const mtm::GridPoint &src_coordinates, const mtm::GridPoint &dst_coordinates) {
    if(game_board(src_coordinates.row,src_coordinates.col)->CalculateMaxSteps() == 5) {
        mtm::Game::checkExceptions(src_coordinates, dst_coordinates);
        if (game_board(dst_coordinates.row, dst_coordinates.col) == nullptr ||
            mtm::GridPoint::distance(src_coordinates, dst_coordinates) == 0) {
            throw IllegalTarget();
        }
        if (game_board(dst_coordinates.row, dst_coordinates.col)->getTeam() !=
            game_board(src_coordinates.row, src_coordinates.col)->getTeam()) {
            game_board(src_coordinates.row, src_coordinates.col)->attack();
            game_board(dst_coordinates.row, dst_coordinates.col)->LowerHealthPoints(
                    game_board(src_coordinates.row, src_coordinates.col)->getPower());
            if (game_board(dst_coordinates.row, dst_coordinates.col)->getHealth() <= 0) {
                game_board(dst_coordinates.row, dst_coordinates.col) = nullptr;
            }
        } else {
            game_board(dst_coordinates.row, dst_coordinates.col)->LowerHealthPoints(
                    game_board(src_coordinates.row, src_coordinates.col)->getPower() * (-1));
        }
    }
}


void mtm::Game::attackSniper (const mtm::GridPoint &src_coordinates, const mtm::GridPoint &dst_coordinates) {
    if(game_board(src_coordinates.row,src_coordinates.col)->CalculateMaxSteps() == 4) {
        if (mtm::GridPoint::distance(src_coordinates, dst_coordinates) >
            game_board(src_coordinates.row, src_coordinates.col)->getRange() ||
            mtm::GridPoint::distance(src_coordinates, dst_coordinates) <
            ceil((double) game_board(src_coordinates.row, src_coordinates.col)->getRange() / 2)) {
            throw OutOfRange();
        }
        if (game_board(src_coordinates.row, src_coordinates.col)->getAmmo() == 0) {
            throw OutOfAmmo();
        }
        if (game_board(dst_coordinates.row, dst_coordinates.col) == nullptr ||
            game_board(dst_coordinates.row, dst_coordinates.col)->getTeam() ==
            game_board(src_coordinates.row, src_coordinates.col)->getTeam()) {
            throw IllegalTarget();
        }
        game_board(src_coordinates.row, src_coordinates.col)->attack();
        if (game_board(src_coordinates.row, src_coordinates.col)->CalculateSniperAttack() % 3 == 0) {
            game_board(dst_coordinates.row, dst_coordinates.col)->LowerHealthPoints(
                    game_board(src_coordinates.row, src_coordinates.col)->getPower() * 2);
        } else {
            game_board(dst_coordinates.row, dst_coordinates.col)->LowerHealthPoints(
                    game_board(src_coordinates.row, src_coordinates.col)->getPower());
        }
        if (game_board(dst_coordinates.row, dst_coordinates.col)->getHealth() <= 0) {
            game_board(dst_coordinates.row, dst_coordinates.col) = nullptr;
        }
    }
}


void mtm::Game::attack(const mtm::GridPoint &src_coordinates, const mtm::GridPoint &dst_coordinates) {
    if(src_coordinates.col < 0 || src_coordinates.row <0 || dst_coordinates.col < 0 || dst_coordinates.row <0 || src_coordinates.row >= game_board.height() || src_coordinates.col >= game_board.width()
       || dst_coordinates.col >= game_board.width() || dst_coordinates.row >= game_board.height() ){
        throw IllegalCell();
    }
    if(game_board(src_coordinates.row,src_coordinates.col) == nullptr){
        throw CellEmpty();
    }
    attackSoldier(src_coordinates,dst_coordinates);
    attackMedic(src_coordinates,dst_coordinates);
    attackSniper(src_coordinates,dst_coordinates);
}


void mtm::Game::reload(const mtm::GridPoint &coordinates) {
    if(coordinates.col < 0 || coordinates.row <0 || coordinates.col >= game_board.width() || coordinates.row >= game_board.height()){
        throw IllegalCell();
    }
    if(game_board(coordinates.row,coordinates.col) == nullptr){
        throw CellEmpty();
    }
    game_board(coordinates.row,coordinates.col)->reload();
}

bool mtm::Game::isOver(mtm::Team *winningTeam) const {
    int cpp=0,python=0;
    int i=0,j=0;
    for (i=0; i<game_board.height(); i++) {
        for (j=0; j<game_board.width(); j++) {
            if(game_board(i,j) != nullptr){
                if(game_board(i,j)->getTeam() == CPP){
                    cpp++;
                }
                else {
                    python++;
                }
            }
        }
    }
    //no winner
    if(cpp==python || (cpp!=0 && python!=0)) {
        return false;
    }
    //there's a winner
    if(winningTeam != nullptr){
        if(cpp == 0){
            *winningTeam = PYTHON;
        } else {
            *winningTeam = CPP;
        }
    }
    return true;
}

 std::string mtm::Game::boardFilling(const mtm::Game &game) {
    std::string board = std::string(game.game_board.size(), ' ');
    int i=0,j=0;
    for (i=0; i<game.game_board.height(); i++){
        for(j=0; j<game.game_board.width(); j++){
            if(game.game_board(i,j) == nullptr){
                board[i*game.game_board.width() + j] = ' ';
            }
            else {
                if(game.game_board(i,j)->getTeam() == CPP){
                    if(game.game_board(i,j)->CalculateMaxSteps() == 3){ //soldier
                        board[i*game.game_board.width() + j] = 'S';
                    } else {
                        if(game.game_board(i,j)->CalculateMaxSteps() == 5){ //medic
                            board[i * game.game_board.width() + j] = 'M';
                        } else { //sniper
                            board[i * game.game_board.width() + j] = 'N';
                        }
                    }
                }

                else {
                    if(game.game_board(i,j)->getTeam() == PYTHON){
                        if(game.game_board(i,j)->CalculateMaxSteps() == 3){ //soldier
                            board[i * game.game_board.width() + j] = 's';
                        } else {
                            if(game.game_board(i,j)->CalculateMaxSteps() == 5){ //medic
                                board[i*game.game_board.width() + j] = 'm';
                            } else { //sniper
                                board[i*game.game_board.width() + j] = 'n';
                            }
                        }
                    }
                }
            }
        }
    }
    return board;
}


std::ostream &mtm::operator<<(std::ostream &os, const mtm::Game &game) {
    std::string board= mtm::Game::boardFilling(game);
    return mtm::printGameBoard(os,board.c_str(),board.c_str() + game.game_board.size(),game.game_board.width());
}