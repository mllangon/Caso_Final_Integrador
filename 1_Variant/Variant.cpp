#include <iostream>
#include <variant>
#include <string>
#include <vector>
#include <sstream>

class Variant{
public:
    enum class Type { Number, String, List };
    explicit Variant(double num) : value(num), type(Type::Number) {}
    explicit Variant(std::string str) : value(str), type(Type::String) {}
    explicit Variant(std::vector<Variant> list) : value(list), type(Type::List) {}

    std::string to_string() const {
        switch (type) {
            case Type::Number:
                return std::to_string(std::get<double>(value));
            case Type::String:
                return std::get<std::string>(value);
            case Type::List:
                return list_to_string();
        }
        return "";
    }


};