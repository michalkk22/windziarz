#include "MessagesFactory.hpp"

Messages MessagesFactory::manager()
{
    return Messages(O_CREAT | O_RDONLY, true);
}

Messages MessagesFactory::person()
{
    return Messages(O_WRONLY);
}