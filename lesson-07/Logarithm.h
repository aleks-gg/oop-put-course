#pragma once
#include <iostream>
#include <cmath>

#include "CustomExc.h"

class Logarithm {
public:
    Logarithm(double base, double argument) {
        base_ = base;
        argument_ = argument;
    }

    double Calculate() const {
        if (argument_ <= 0) {
            throw CustomException("Argument is invalid!");
        }
        else if (base_ <= 0 || base_ == 1) {
            throw CustomException("Base is invalid!");
        }
        return std::log(argument_) / std::log(base_);
    }

private:
    double base_;
    double argument_;
};