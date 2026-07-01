#include "model/DataModel.hpp"

DataModel::DataModel()
{
    k_mutex_init(&patient_mutex_);

    ring_buf_init(
        &ecg_ring_buffer_,
        ECG_BUFFER_SIZE,
        ecg_storage_);
}

void DataModel::set_patient_data(const PatientData& data)
{
    k_mutex_lock(&patient_mutex_, K_FOREVER);

    patient_data_ = data;

    k_mutex_unlock(&patient_mutex_);

    notify_observers();
}

PatientData DataModel::get_patient_data()
{
    PatientData copy;

    k_mutex_lock(&patient_mutex_, K_FOREVER);

    copy = patient_data_;

    k_mutex_unlock(&patient_mutex_);

    return copy;
}

void DataModel::PushECGSample(uint16_t sample)
{
    ring_buf_put(
        &ecg_ring_buffer_,
        reinterpret_cast<uint8_t*>(&sample),
        sizeof(sample));
}

uint32_t DataModel::PopECGSamples(
    uint8_t* buffer,
    uint32_t buffer_size)
{
    return ring_buf_get(
        &ecg_ring_buffer_,
        buffer,
        buffer_size);
}