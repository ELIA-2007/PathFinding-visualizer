#include "machine.h"

int main() {
    Machine machine;
    initMachine(&machine);
    while (machine.running) {
        machineHandleEvents(&machine);
        machineUpdate(&machine);
        machineRender(&machine);
    }
    machineClear(&machine);
    return EXIT_SUCCESS;
}