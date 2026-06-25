#include "model/DataModel.hpp"

void DataModel::set_patient_data(const PatientData& data)
{
    patient_data_ = data;

    notify_observers();
}

const PatientData& DataModel::get_patient_data() const
{
    return patient_data_ ;
}
