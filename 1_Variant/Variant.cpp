#include <iostream>
#include <variant>
#include <string>
#include <vector>
#include <sstream>
#include <llans/json.hpp>

using json = nlohmann::json;

class Variant{
public:
    enum class Type { Number, String, List };
    explicit Variant(double num) : value(num), type(Type::Number) {}
    explicit Variant(std::string str) : value(str), type(Type::String) {}
    explicit Variant(std::vector<Variant> list) : value(list), type(Type::List) {}


};