#include "WIFI.h"

using namespace etl;

namespace Core::Device {

static WIFI* g_wifi = nullptr;

[[nodiscard]] WIFI* WIFI::initialize()
{
    if (g_wifi)
        return nullptr;

    if (!(g_wifi = create_singleton_l2<WIFI>()))
        return nullptr;

    pi_nina_w10_conf_init(&(g_wifi->m_config));

    g_wifi->m_config.ssid = WIFI_SSID;
    g_wifi->m_config.passwd = WIFI_PASSWD;
    g_wifi->m_config.ip_addr = WIFI_ADDR;
    g_wifi->m_config.port = WIFI_PORT;

    pi_open_from_conf(&(g_wifi->m_wifi_device), &(g_wifi->m_config));
    if (pi_transport_open(&(g_wifi->m_wifi_device)))
        return nullptr;

    return g_wifi;
}

WIFI& WIFI::self()
{
    return *g_wifi;
}

}