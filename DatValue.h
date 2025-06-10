#pragma once
#include<iostream>

class DatValue{
protected:
    const virtual void Print(std::ostream& os) const = 0;
public:
    DatValue() {}

    virtual DatValue* GetCopy() = 0;
    
    friend std::ostream& operator<<(std::ostream& os, const DatValue& dv){
        if (&dv != nullptr){
            dv.Print(os);
        }
        return os;
    }
};