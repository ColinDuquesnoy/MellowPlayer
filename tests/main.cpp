#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include <QString>

std::ostream& operator << ( std::ostream& os, const QString& value ) {
    os << value.toStdString();
    return os;
}