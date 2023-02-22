/**
 * @file class.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-01-20
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include <iostream>
#include <memory>
// convention: HEADER_EXPORTS
#define CLASS_EXPORTS
#ifdef  CLASS_EXPORTS
#define  CLASS_API __declspec(dllexport)
#else
#define  CLASS_API __declspec(dllimport)
#endif

// interface
class CLASS_API ICLASS
{
    public:
    virtual int add(int a, int b) = 0;
    virtual int getSum()=0;
};

// implement
class DerivedA: public ICLASS
{
    public:
     int add(int a, int b) override;
     int getSum() override;
     private:
     int sum=0;
};
// implement
class DerivedB: public ICLASS
{
    public:
     int add(int a, int b) override;
     int getSum() override;
     private:
     int sum=0;
};
// C Style way of exporting classes
// Factory function that creates instances of the class object.
extern "C" CLASS_API ICLASS* GetDerivedAClass();
extern "C" CLASS_API ICLASS* GetDerivedBClass();
extern "C" CLASS_API ICLASS* GetInterfacePtr();
// C++ style of passing classes
CLASS_API std::shared_ptr<ICLASS> GetInterfaceSharedPtr();
CLASS_API std::unique_ptr<ICLASS> GetInterfaceUniquePtr();