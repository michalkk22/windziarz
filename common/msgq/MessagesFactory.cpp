#include "MessagesFactory.hpp"

#include "mqNames.hpp"

Messages<CallElevatorMessage> MessagesFactory::manager()
{
    return Messages<CallElevatorMessage>(MQ_MANAGER_REQUESTS,
                                         sizeof(CallElevatorMessage),
                                         O_CREAT | O_RDONLY,
                                         true);
}

Messages<CallElevatorMessage> MessagesFactory::person()
{
    return Messages<CallElevatorMessage>(MQ_MANAGER_REQUESTS,
                                         sizeof(CallElevatorMessage),
                                         O_WRONLY);
}

Messages<FloorRequestMessage> MessagesFactory::createElevatorRequests(const std::string &id)
{
    return Messages<FloorRequestMessage>(MQ_ELEVATOR_PREFIX + id,
                                         sizeof(FloorRequestMessage),
                                         O_CREAT | O_RDONLY,
                                         true);
}

Messages<FloorRequestMessage> MessagesFactory::joinElevatorRequests(const std::string &id)
{
    return Messages<FloorRequestMessage>(MQ_ELEVATOR_PREFIX + id,
                                         sizeof(FloorRequestMessage),
                                         O_WRONLY);
}