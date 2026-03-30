#include "MessagesFactory.hpp"

#include "mqNames.hpp"

Messages<CallElevatorMessage> MessagesFactory::manager()
{
    std::string name{MQ_MANAGER_REQUESTS};
    return Messages<CallElevatorMessage>(name,
                                         sizeof(CallElevatorMessage),
                                         O_CREAT | O_RDONLY,
                                         true);
}

Messages<CallElevatorMessage> MessagesFactory::person()
{
    std::string name{MQ_MANAGER_REQUESTS};
    return Messages<CallElevatorMessage>(name, sizeof(CallElevatorMessage), O_WRONLY);
}