#pragma once

#include<cstdint>

struct VitalSigns
{
    uint8_t hr;
    uint8_t spo2;
    uint8_t rr;

    uint8_t sys;
    uint8_t dias;
    uint8_t mean;
};

class FakeVitalSource
{
    private:
        uint8_t hr[18] = {75,71,70,69,68,56,56,56,56,68,71,72,69,72,72,72,72,72};
        uint8_t spo2[18] = {98,95,96,99,90,89,85,74,65,75,89,81,95,95,95,95,95,95};
        uint8_t rr[18] = {16,16,14,15,15,13,12,15,16,16,14,11,13,16,16,16,16,16};
        uint8_t sys[18] = {120,119,118,119,115,111,110,115,112,105,100,115,113,120,120,120,120,120};
        uint8_t dias[18] = {80,80,79,78,75,78,82,83,80,80,78,85,76,80,80,80,80,80};
        int count = 0;

    public:
        VitalSigns GetVitals();
};