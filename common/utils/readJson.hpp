#pragma once

#include <fstream>
#include "json.hpp"

nlohmann::json readJson(const std::string &path)
{
    std::ifstream file(path);

    if (!file)
    {
        throw std::runtime_error("Cannot open config file");
    }

    nlohmann::json j;
    file >> j;

    return j;
}