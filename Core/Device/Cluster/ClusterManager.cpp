#include "ClusterManager.h"

namespace Core::Device {

ClusterManager::ClusterManager()
{
    while (!Cluster::self().open_cluster())
        ;
}

ClusterManager::~ClusterManager()
{
    Cluster::self().close_cluster();
}

}