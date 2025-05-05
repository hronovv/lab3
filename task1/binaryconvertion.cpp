#include "binaryconvertion.h"


void binaryInt(int number, std::ostringstream& result) {
    if (number > 1) {
        binaryInt(number >> 1, result);
    }
    result << (number % 2);
}


void binaryDouble(double number, std::ostringstream& result) {
    number *= 2;
    if (number == 0) {
        return;
    }
    if (number > 1) {
        result << 1;
        binaryDouble(number - static_cast<int>(number), result);
    } else {
        result << 0;
        binaryDouble(number, result);
    }
}

std::string Binary(double number) {
    std::ostringstream result;


    if (number < 0) {
        result << "-";
        number *= -1;
    }

    int number_int = static_cast<int>(number);
    binaryInt(number_int, result);


    if (number != number_int) {
        result << '.';
        binaryDouble(number - number_int, result);
    }

    return result.str();
}
