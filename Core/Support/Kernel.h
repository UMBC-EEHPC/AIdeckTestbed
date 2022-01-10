#pragma once

#include "gap_sdk.h"

namespace Core::Support {

/*
 * I *REALLY* wanted to use lambdas for this, but unfortunately,
 * due to the way C++ lambdas and class member functions work, you can't
 * just simply pass a std::function or whatever into the method for sending
 * tasks to the GAP8 cluster API. Yes I know, very tragic.
 * TODO: write a new GAP8 SDK in C++
 */

class Kernel {
    public:
        constexpr Kernel(uint8_t num_cores, 
                uint16_t fc_stack_size, 
                uint16_t cc_stack_size, 
                void (*cluster_task)(void*),
                void* args) :
            m_num_cores(num_cores),
            m_fc_stack_size(fc_stack_size),
            m_cc_stack_size(cc_stack_size),
            m_cluster_task(cluster_task),
            m_args(args) {}

        [[nodiscard]] constexpr uint8_t get_num_cores_assigned() const {
            return m_num_cores;
        }
        [[nodiscard]] constexpr uint16_t get_fc_stack_size() const {
            return m_fc_stack_size;
        }
        [[nodiscard]] constexpr uint16_t get_cc_stack_size() const {
            return m_cc_stack_size;
        }
        [[nodiscard]] constexpr void(*get_cluster_task(void) const)(void*) {
            return m_cluster_task;
        }
        [[nodiscard]] constexpr void* get_args() const {
            return m_args;
        }
    private:
        uint8_t m_num_cores;
        uint16_t m_fc_stack_size;
        uint16_t m_cc_stack_size;
        void (*m_cluster_task)(void*);
        void* m_args;
};

}