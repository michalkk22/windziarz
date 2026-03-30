#include "RequestsHandler.hpp"

#include <memory>
#include <string>
// TODO: delete logs
#include <iostream>

#include "fifo/FifoFactory.hpp"

RequestsHandler::RequestsHandler(Messages<CallElevatorMessage> *messages, States *shm, std::atomic<bool> &running)
    : messages(messages), shm(shm), running(running) {}

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
    std::cout << "Sending elevator: " << msg.floor << " to pipe " << pipe << std::endl;
    std::unique_ptr<FifoChannel> fifo =
        FifoFactory::createSender(pipe);
    fifo->sendInt(elevator);
    std::cout << "Handler sent elevator " << msg.floor << " to pipe " << pipe << std::endl;
};