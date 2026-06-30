#include<datasource/SineWaveSource.hpp>
#include<cmath>

// uint16_t beat[24] = 
// {
//     125,125,125,125, 90,108,118,125,
//     125, 90, 40,230, 70,125,
//     125,140,165,180,165,140,
//     125,125,125,125
// };

// int count = -1;

 uint16_t SineWaveSource :: GetSample() 
 {
    constexpr float amplitude = 100.0f;
    constexpr float offset = 120.0f;

    float value = offset + amplitude * std::sin(sample_index_ * 0.1f);
    sample_index_++;

    return static_cast<uint16_t>(value);
 }

// uint16_t SineWaveSource :: GetSample()
// {
//    if(count>=23)
//    {
//       count=0;
//    }
//    count++;
//    return static_cast<uint16_t>(beat[count]);
// }