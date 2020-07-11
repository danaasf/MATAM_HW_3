//
// Created by danaa on 7/2/2020.
//

#ifndef EX3_EXEPTIONS_H
#define EX3_EXEPTIONS_H
#include <iostream>

// ask if should be in order

namespace mtm {
    class Exceptions : public std::exception {
    public:
        virtual const char *what() const noexcept = 0;
    };


    class GameException :  public Exceptions {
    protected:
        std::string error_message;
    public:
        const char *what() const noexcept override;
    };

    class IllegalArgument : public GameException {
    public:
        explicit IllegalArgument();
        char const *what() const noexcept override;
    };

    class IllegalCell : public GameException{
    public:
        explicit IllegalCell();
        char const *what() const noexcept override;
    };

    class CellEmpty : public GameException {
    public:
        explicit CellEmpty();
        char const *what() const noexcept override;
    };

    class MoveTooFar : public GameException {
    public:
        explicit MoveTooFar();
        char const *what() const noexcept override;
    };

    class CellOccupied : public GameException {
    public:
        explicit CellOccupied();
        char const *what() const noexcept override;
    };

    class OutOfRange : public GameException {
    public:
        explicit OutOfRange();
        char const *what() const noexcept override;
    };

    class OutOfAmmo : public GameException {
    public:
        explicit OutOfAmmo();
        char const *what() const noexcept override;
    };

    class IllegalTarget : public GameException {
    public:
        explicit IllegalTarget();
        char const *what() const noexcept override;
    };
}



#endif //EX3_EXEPTION_H
