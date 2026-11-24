#include "machine.h"

int main() {
    Machine machine;

    if (initMachine(&machine))
        exit(1);

    while (machine.running) {
        machineHandleEvents(&machine);
        machineUpdate(&machine);
        machineRender(&machine);
    }

    machineClear(&machine);
    return EXIT_SUCCESS;
}