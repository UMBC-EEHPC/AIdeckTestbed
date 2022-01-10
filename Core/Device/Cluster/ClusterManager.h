#pragma once

#include <Core/Support/Kernel.h>
#include "Cluster.h"

namespace Core::Device {

class ClusterManager {
    public:
        ClusterManager();

        ClusterManager(ClusterManager const&) = delete;
        ClusterManager& operator=(ClusterManager const&) = delete;

        [[nodiscard]] bool submit_kernel_asynchronously(Core::Support::Kernel const& kernel);
        [[nodiscard]] bool submit_kernel_synchronously(Core::Support::Kernel const& kernel);

        ~ClusterManager();
    private:
};

}