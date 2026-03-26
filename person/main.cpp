#include "Person.hpp"
#include <string>

int main(int argc, char const *argv[])
{
    // initialize
    unsigned int currentFloor, destinationFloor;
    currentFloor = atoi(argv[1]);
    destinationFloor = atoi(argv[2]);
    Direction direction = currentFloor < destinationFloor ? Direction::Up : Direction::Down;
    // here put position in shared memory
    Position position{currentFloor, direction};
    Person me{&position, destinationFloor};

    while (currentFloor != destinationFloor)
    {
        // call elevator by sending request to manager

        // receive elevator data

        // wait for elevator

        // request floor

        // exit
    }

    return 0;
}
