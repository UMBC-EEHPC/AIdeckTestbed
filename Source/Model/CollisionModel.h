#pragma once

#include <Benchmarks.h>
#include <Core/Device/Cluster/Cluster.h>
#include <Core/Support/Assertions.h>
#include <etl/vector.h>

namespace Model {

class CollisionModel {
public:
    CollisionModel(etl::vector_ext<uint8_t>& frame_data, etl::vector_ext<uint8_t>& frame_resized, Core::Device::Cluster const& cluster);

    CollisionModel(CollisionModel const&) = delete;
    CollisionModel& operator=(CollisionModel const&) = delete;

    [[nodiscard]] bool run_model();

    [[nodiscard]] bool open_model();
    void close_model();

    ~CollisionModel();

private:
    bool m_is_model_open;
    Core::Device::Cluster const& m_cluster;
};

}