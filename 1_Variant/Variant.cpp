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

    std::string to_json_string() const {
        nlohmann::json j;
        switch (type) {
            case Type::Number:
                j = std::get<double>(value);
                break;
            case Type::String:
                j = std::get<std::string>(value);
                break;
            case Type::List:
                for (const auto& elem : std::get<std::vector<Variant>>(value)) {
                    j.push_back(nlohmann::json::parse(elem.to_json_string()));
                }
                break;
        }
        return j.dump();
    }


};