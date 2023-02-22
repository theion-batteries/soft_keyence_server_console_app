#pragma once
#include "class.h"

class client
{
private:
    std::shared_ptr<ICLASS> objS = GetInterfaceSharedPtr();
 
public:
    client(/* args */);
    ~client();
};


