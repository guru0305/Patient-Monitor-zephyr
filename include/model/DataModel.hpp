#pragma once

#include "model/PatientData.hpp"
#include "observer/Subject.hpp"

class DataModel : public Subject
{
    private:
    PatientData patient_data_;
    void notify_observer();

    public:
    void set_patient_data(const PatientData& data);
    const PatientData& get_patient_data() const;

};