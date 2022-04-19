#include "VIPCargo.h"

VIPCargo::VIPCargo(int i):Cargo(i)
{
}

int VIPCargo::getPriority()
{
    return 1;
}
