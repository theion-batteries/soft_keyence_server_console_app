#include "client.h"

client::client(/* args */)
{
     // shared ptr
    objS=std::make_shared<DerivedA>();
    objS->add(1,2);
    objS->getSum();
    objS=std::make_shared<DerivedB>();
    objS->add(1,3);
    objS->getSum();
 
}

client::~client()
{
}