#include "MessagesFactory.hpp"

Messages MessagesFactory::manager()
{
    return Messages(O_CREAT | O_RDONLY);
}

Messages MessagesFactory::person()
{
    return Messages(O_WRONLY);
}