//
// Created by danaa on 7/2/2020.
//

#include "Exceptions.h"
#include <iostream>
#include <string>

// should they be in order?

const char *mtm::GameException::what() const noexcept {
    return "A game related error has occurred: ";
}

//illegal argument
char const *mtm::IllegalArgument::what() const noexcept {
    return error_message.c_str();
}

mtm::IllegalArgument::IllegalArgument() {
    error_message = std::string(GameException::what()) + "IllegalArgument";
}

//illegal cell
char const *mtm::IllegalCell::what() const noexcept {

    return error_message.c_str();
}


mtm::IllegalCell::IllegalCell() {
    error_message = std::string(GameException::what()) + "IllegalCell";
}

//cell empty
char const *mtm::CellEmpty::what() const noexcept {
    return error_message.c_str();
}

mtm::CellEmpty::CellEmpty() {
    error_message = std::string(GameException::what()) + "CellEmpty";
}

//move too far
char const *mtm::MoveTooFar::what() const noexcept {
    return error_message.c_str();
}

mtm::MoveTooFar::MoveTooFar() {
    error_message = std::string(GameException::what()) + "MoveTooFar";
}

//cell occupied
char const *mtm::CellOccupied::what() const noexcept {
    return error_message.c_str();
}

mtm::CellOccupied::CellOccupied() {
    error_message = std::string(GameException::what()) + "CellOccupied";
}

//out of range
char const *mtm::OutOfRange::what() const noexcept {
    return error_message.c_str();
}

mtm::OutOfRange::OutOfRange() {
    error_message = std::string(GameException::what()) + "OutOfRange";
}

//out of ammo
char const *mtm::OutOfAmmo::what() const noexcept {
    return error_message.c_str();
}

mtm::OutOfAmmo::OutOfAmmo() {
    error_message = std::string(GameException::what()) + "OutOfAmmo";
}

//illegal target

char const *mtm::IllegalTarget::what() const noexcept {
    return error_message.c_str();
}

mtm::IllegalTarget::IllegalTarget() {
    error_message = std::string(GameException::what()) + "IllegalTarget";
}


