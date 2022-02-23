#include "Camera.h"

using namespace etl;

namespace Core::Device {

pi_device m_camera_device;
static pi_task_t camera_callback_task;
static Camera* g_camera = nullptr;

/*
 * Unfortunately there's no way to pass a lambda directly
 * as a callback, so we have to provide a C wrapper
 */
void camera_c_callback(void* arg)
{
    pi_camera_control(&m_camera_device, PI_CAMERA_CMD_STOP, 0);
    delegate<void(void)>* callback = reinterpret_cast<delegate<void(void)>*>(arg);
    (*callback)();
}

[[nodiscard]] Camera* Camera::initialize()
{
    if (g_camera)
        return nullptr;

    if (!(g_camera = create_singleton_l2<Camera>()))
        return nullptr;

    pi_himax_conf_init(&(g_camera->m_config));

    g_camera->m_config.format = PI_CAMERA_QVGA;

    pi_open_from_conf(&(m_camera_device), &(g_camera->m_config));
    if (pi_camera_open(&(m_camera_device)))
        return nullptr;

    pi_camera_control(&(m_camera_device), PI_CAMERA_CMD_START, 0);

    uint8_t set_value = 3;
    uint8_t reg_value;

    pi_camera_reg_set(&(m_camera_device), IMG_ORIENTATION, &set_value);
    pi_time_wait_us(1000000);
    pi_camera_reg_get(&(m_camera_device), IMG_ORIENTATION, &reg_value);
    assert_gap8(set_value == reg_value);

    pi_camera_control(&(m_camera_device), PI_CAMERA_CMD_STOP, 0);
    pi_camera_control(&(m_camera_device), PI_CAMERA_CMD_AEG_INIT, 0);

    return g_camera;
}

Camera& Camera::self()
{
    return *g_camera;
}

void Camera::capture_image(vector_ext<uint8_t>& buffer)
{
    pi_camera_control(&m_camera_device, PI_CAMERA_CMD_START, 0);
    pi_camera_capture(&m_camera_device, buffer.data(), get_image_width() * get_image_height());
    pi_camera_control(&m_camera_device, PI_CAMERA_CMD_STOP, 0);
}

void Camera::stream(vector_ext<uint8_t>& buffer, delegate<void(void)> callback)
{
    pi_task_callback(&camera_callback_task, camera_c_callback, reinterpret_cast<void*>(&callback));

    assert_gap8(!pi_camera_control(&m_camera_device, PI_CAMERA_CMD_STOP, NULL));
    pi_camera_capture_async(&m_camera_device, buffer.data(), get_image_width() * get_image_height(), &camera_callback_task);
    assert_gap8(!pi_camera_control(&m_camera_device, PI_CAMERA_CMD_START, NULL));

    pi_task_wait_on(&camera_callback_task);
}

}
