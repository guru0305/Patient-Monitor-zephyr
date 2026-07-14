#include<datasource/SineWaveSource.hpp>
#include<cmath>

 uint16_t SineWaveSource :: GetSample() 
 {
    constexpr float amplitude = 100.0f;
    constexpr float offset = 120.0f;

    float value = offset + amplitude * std::sin(sample_index_ * 0.1f);
    sample_index_++;

    return static_cast<uint16_t>(value);
 }
