#pragma once

#include <Core/Support/Singleton.h>
#include <Core/Support/gap_sdk.h>

namespace Core::Device {

class Cluster {
    SINGLETON_CLASS(Cluster)
public:
    [[nodiscard]] bool open_cluster();
    [[nodiscard]] bool submit_task_asynchronously(void* task, void* args);
    [[nodiscard]] bool submit_task_synchronously(void* task, void* args) const;
    bool close_cluster();

    [[nodiscard]] bool is_cluster_open();

    ~Cluster();

private:
    struct pi_device m_cluster_dev;
    struct pi_cluster_conf m_config;
    bool m_cluster_opened;
};

}