#pragma once 
#include <iostream>
#include <cstdint>
#include <iomanip>
#include "DatValue.h"

using Key = std::string;
using PDataValue = DatValue*;

class Marks: public DatValue{
    private:
        uint8_t _math;
        uint8_t _chem;
        uint8_t _zvo;
        uint8_t _difeq;
        uint8_t _ads;
    public:
        Marks(uint8_t math,
            uint8_t chem,
            uint8_t zvo,
            uint8_t difeq,
            uint8_t ads){
            _math = math;
            _chem = chem;
            _zvo = zvo;
            _difeq = difeq;
            _ads = ads;
            }
        PDataValue GetCopy(){
            PDataValue tmp = new Marks(_math,_chem,_zvo,_difeq,_ads);
            return tmp;
        }
        const void Print(std::ostream& os)const{
            size_t flag = 10;
            os << "|" << std::setw(flag) << std::left <<static_cast<int>(_math)
                << "|" << std::setw(flag) << std::left <<static_cast<int>(_chem)
                << "|" << std::setw(flag) << std::left <<static_cast<int>(_zvo)
                << "|" << std::setw(flag) << std::left <<static_cast<int>(_difeq)
                << "|" << std::setw(flag) << std::left << static_cast<int>(_ads)
                << "|"<< std::endl;
        }
        uint8_t GetMath() const { return _math; }
        uint8_t GetChem() const { return _chem; }
        uint8_t GetZvo() const { return _zvo; }
        uint8_t GetDifeq() const { return _difeq; }
        uint8_t GetAds() const { return _ads; }
};