#include "Cluster.h"

namespace Core::Device {

static Cluster* g_cluster = nullptr;

[[nodiscard]] Cluster* Cluster::initialize()
{
    if (g_cluster)
        return nullptr;

    if (!(g_cluster = create_singleton_l2<Cluster>()))
        return nullptr;

    g_cluster->m_cluster_opened = false;

    return g_cluster;
}

[[nodiscard]] Cluster& Cluster::self()
{
    return *g_cluster;
}

[[nodiscard]] bool Cluster::open_cluster()
{
    pi_cluster_conf_init(&m_config);
    m_config.id = 0;
    pi_open_from_conf(&m_cluster_dev, &m_config);
    return (m_cluster_opened = !pi_cluster_open(&m_cluster_dev));
}

[[nodiscard]] bool Cluster::submit_task_synchronously(void* task, void* args) const
{
    struct pi_cluster_task submitted_task = { 0 };
    submitted_task.entry = task;
    submitted_task.arg = args;
    submitted_task.stack_size = (unsigned int)STACK_SIZE;
    submitted_task.slave_stack_size = (unsigned int)SLAVE_STACK_SIZE;

    auto status = pi_cluster_send_task_to_cl(&m_cluster_dev, &submitted_task);

    return !status;
}

bool Cluster::close_cluster()
{
    return (m_cluster_opened != pi_cluster_close(&m_cluster_dev));
}

[[nodiscard]] bool Cluster::is_cluster_open()
{
    return m_cluster_opened;
}

Cluster::~Cluster()
{
    close_cluster();
}

}