#pragma once

#include "Messages.hpp"

class MessagesFactory
{
public:
    static Messages manager();
    static Messages person();
};