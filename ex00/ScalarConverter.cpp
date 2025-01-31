#include "ScalarConverter.hpp"


ScalarConverter::ScalarConverter() {

}
ScalarConverter::~ScalarConverter() {

}
ScalarConverter::ScalarConverter(const ScalarConverter&) {

}
ScalarConverter& ScalarConverter::operator=(const ScalarConverter&) {
     return *this; }

bool ScalarConverter::isPseudoLiteral(const std::string& input) {
    return (input == "nan" || input == "+inf" || input == "-inf" ||
            input == "nanf" || input == "+inff" || input == "-inff");
}

bool ScalarConverter::isChar(const std::string& input) {
    return (input.length() == 1 && isprint(input[0]) && !isdigit(input[0]));
}

bool ScalarConverter::isInt(const std::string& input) {
    char* end;
    long num = std::strtol(input.c_str(), &end, 10);
    return (*end == '\0' && num >= std::numeric_limits<int>::min() && num <= std::numeric_limits<int>::max());
}

bool ScalarConverter::isFloat(const std::string& input) {
    if (input[input.length() - 1] != 'f') return false;
    char* end;
    std::strtof(input.c_str(), &end);
    return (*end == 'f' && *(end + 1) == '\0');
}

bool ScalarConverter::isDouble(const std::string& input) {
    char* end;
    std::strtod(input.c_str(), &end);
    return (*end == '\0');
}

void ScalarConverter::printPseudoLiterals(const std::string& input) {
    std::string cleaninput = input;
    if (input == "nanf") cleaninput = "nan";
    if (input == "+inff") cleaninput = "+inf";
    if (input == "-inff") cleaninput = "-inf";

    std::cout << "char: impossible\n";
    std::cout << "int: impossible\n";
    std::cout << "float: " << cleaninput << "f\n";
    std::cout << "double: " << cleaninput << std::endl;
}

void ScalarConverter::convert(const std::string& input) {
    if (isPseudoLiteral(input)) {
        printPseudoLiterals(input);
        return;
    }

    if (isChar(input)) {
        char c = input[0];
        printChar(c);
        printInt(static_cast<int>(c));
        printFloat(static_cast<float>(c));
        printDouble(static_cast<double>(c));
        return;
    }

    if (isInt(input)) {
        long num = std::strtol(input.c_str(), NULL, 10);
        if (num < std::numeric_limits<int>::min() || num > std::numeric_limits<int>::max()) {
            std::cout << "char: impossible\nint: impossible\nfloat: impossible\ndouble: impossible" << std::endl;
            return;
        }
        int i = static_cast<int>(num);
        printChar(static_cast<char>(i));
        printInt(i);
        printFloat(static_cast<float>(i));
        printDouble(static_cast<double>(i));
        return;
    }

    if (isFloat(input)) {
        float f = std::strtof(input.c_str(), NULL);
        printChar(static_cast<char>(f));
        printInt(static_cast<int>(f));
        printFloat(f);
        printDouble(static_cast<double>(f));
        return;
    }

    if (isDouble(input)) {
        double d = std::strtod(input.c_str(), NULL);
        printChar(static_cast<char>(d));
        printInt(static_cast<int>(d));
        printFloat(static_cast<float>(d));
        printDouble(d);
        return;
    }

    std::cout << "char: impossible\nint: impossible\nfloat: impossible\ndouble: impossible" << std::endl;
}

void ScalarConverter::printChar(char c) {
    if (!isprint(c))
        std::cout << "char: Non displayable" << std::endl;
    else
        std::cout << "char: '" << c << "'" << std::endl;
}

void ScalarConverter::printInt(int i) {
    std::cout << "int: " << i << std::endl;
}

void ScalarConverter::printFloat(float f) {
    if (std::isnan(f) || std::isinf(f))
        std::cout << "float: " << f << "f" << std::endl;
    else
        std::cout << "float: " << std::fixed << std::setprecision(1) << f << "f" << std::endl;
}

void ScalarConverter::printDouble(double d) {
    if (std::isnan(d) || std::isinf(d))
        std::cout << "double: " << d << std::endl;
    else
        std::cout << "double: " << std::fixed << std::setprecision(1) << d << std::endl;
}
