#pragma once

#include <Core/Support/gap_sdk.h>

namespace Core::Device::CPU {

inline void set_fabric_frequency(int mhz) {
    pi_freq_set(PI_FREQ_DOMAIN_FC, mhz * 1000 * 1000);
}

inline void set_cluster_frequency(int mhz) {
    pi_freq_set(PI_FREQ_DOMAIN_CL, mhz * 1000 * 1000);
}

inline void set_fabric_voltage(float voltage) {
    pi_pmu_voltage_set(PI_PMU_DOMAIN_FC, static_cast<uint32_t>(voltage * 1000));
}

inline void set_cluster_voltage(float voltage) {
    pi_pmu_voltage_set(PI_PMU_DOMAIN_CL, static_cast<uint32_t>(voltage * 1000));
}

inline unsigned int get_fabric_frequency() {
    return pi_freq_get(PI_FREQ_DOMAIN_FC);
}

inline unsigned int get_cluster_frequency() {
    return pi_freq_get(PI_FREQ_DOMAIN_CL);
}

inline unsigned int get_peripheral_frequency() {
    return pi_freq_get(PI_FREQ_DOMAIN_PERIPH);
}

}