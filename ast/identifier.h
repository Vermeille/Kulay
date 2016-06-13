#pragma once

#include <string>

class Identifier {
    std::string name_;

    public:
        Identifier(const std::string& str) : name_(str) {}
        const std::string& str() const { return name_; }
};

