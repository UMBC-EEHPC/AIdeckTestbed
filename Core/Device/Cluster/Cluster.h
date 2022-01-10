#pragma once

#include <Core/Support/gap_sdk.h>
#include <Core/Support/Singleton.h>
#include <Core/Support/Kernel.h>

namespace Core::Device {

class Cluster {
    SINGLETON_CLASS(Cluster)
    public:
        [[nodiscard]] bool open_cluster();
        [[nodiscard]] bool submit_kernel_asynchronously(Core::Support::Kernel const& kernel);
        [[nodiscard]] bool submit_kernel_synchronously(Core::Support::Kernel const& kernel);
        bool close_cluster();

        [[nodiscard]] bool is_cluster_open();

        ~Cluster();
    private:
        struct pi_device m_cluster_dev;
        struct pi_cluster_conf m_config;
        bool m_cluster_opened;
};

}