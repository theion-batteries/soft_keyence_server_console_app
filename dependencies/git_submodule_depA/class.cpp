#include "class.h"

int DerivedA::add(int a, int b)
{
    std::cout<<"A sum a+b: "<<a+b<<std::endl;
    return sum=a+b;
}
int DerivedB::add(int a, int b)
{
    std::cout<<"B sum a+b: "<<a+b<<std::endl;
    return sum=a+b;
}

int DerivedA::getSum()
{
    std::cout<<"A internal sum: "<<sum<<std::endl;
    return sum;
}
int DerivedB::getSum()
{
    std::cout<<"B internal sum: "<<sum<<std::endl;
    return sum;
}

CLASS_API std::shared_ptr<ICLASS> GetInterfaceSharedPtr()
{
    std::shared_ptr<ICLASS> S;
    return S;
}
CLASS_API std::unique_ptr<ICLASS> GetInterfaceUniquePtr()
{
    std::unique_ptr<ICLASS> U;
    return U;
}







// Cstyle
extern "C"
{
    CLASS_API ICLASS* GetDerivedAClass()
    {
        return new DerivedA();
    }
}
extern "C"
{
    CLASS_API ICLASS* GetDerivedBClass()
    {
        return new DerivedB();
    }
}
extern "C"
{
    CLASS_API ICLASS* GetInterfacePtr()
    {
        ICLASS* InterfacePtr=nullptr;
        return InterfacePtr;
    }
}