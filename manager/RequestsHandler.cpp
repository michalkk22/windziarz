#include "RequestsHandler.hpp"

#include <memory>
#include <string>
// TODO: delete logs
#include <iostream>

#include "fifo/FifoFactory.hpp"

RequestsHandler::RequestsHandler(Messages<CallElevatorMessage> *messages, States *states, std::atomic<bool> &running)
    : messages(messages), states(states), running(running) {}

void RequestsHandler::run()
{
    std::cout << "Handler started run." << std::endl;

    CallElevatorMessage msg;
    while (running)
    {
        msg = messages->receive();
        if (msg.floor != -1)
        {
            handle(msg);
        }
    }
}

void RequestsHandler::handle(CallElevatorMessage &msg)
{
    // TODO:
    // choose and send Elevator

    int elevator = 2;

    // answer Person
    std::string pipe(msg.pipe.data());
    std::cout << "Sending elevator: " << elevator << " to flor " << msg.floor << " to pipe " << pipe << std::endl;
    std::unique_ptr<FifoChannel> fifo =
        FifoFactory::createSender(pipe);
    fifo->sendInt(elevator);
};