#include "machine.h"

int main() {
    Machine machine;

    if (initMachine(&machine)) //INIT MACHINE
        exit(1);

    while (machine.running) { //LOOP
        machineHandleEvents(&machine);
        machineUpdate(&machine);
        machineRender(&machine);
    }

    machineClear(&machine); //CLEAR
    return EXIT_SUCCESS;
}