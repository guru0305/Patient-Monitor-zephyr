#pragma once

#include "model/PatientData.hpp"
#include "observer/Subject.hpp"
#include <zephyr/kernel.h>
#include <zephyr/sys/ring_buffer.h>

class DataModel : public Subject
{
    private:
        PatientData patient_data_;
        k_mutex patient_mutex_;
        static constexpr size_t ECG_BUFFER_SIZE = 300;

        uint8_t ecg_storage_[ECG_BUFFER_SIZE];
        struct ring_buf ecg_ring_buffer_;

    public:
        void set_patient_data(const PatientData& data);
        PatientData get_patient_data();
        DataModel();

        void PushECGSample(uint16_t sample);

        uint32_t PopECGSamples(
            uint8_t* buffer,
            uint32_t buffer_size);

};