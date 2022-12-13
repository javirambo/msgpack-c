/**
 * @author javier
 * @brief Prueba del MsgPack. Esto compila OK.
 * @date 2022-12-13
 */
#include "esp_system.h"
#include "esp_event.h"
#include "esp_log.h"
#include "components/msgpack/include/msgpack.h"

static const char *TAG = "main";

void app_main(void)
{
    /// TEST DEL MSG PACK

    msgpack_sbuffer *buffer = msgpack_sbuffer_new();
    msgpack_packer *pk = msgpack_packer_new(buffer, msgpack_sbuffer_write);

    msgpack_pack_array(pk, 3);
    msgpack_pack_bin(pk, 5);
    msgpack_pack_bin_body(pk, "Hello", 5);
    msgpack_pack_bin(pk, 11);
    msgpack_pack_bin_body(pk, "MessagePack", 11); /*=> ["Hello", "MessagePack", 12345] */
    msgpack_pack_int(pk, 99912345L);

    ESP_LOGE(TAG, "buffer->size=%d", buffer->size);

    msgpack_unpacked msg;
    msgpack_unpacked_init(&msg);
    msgpack_unpack_return ret = msgpack_unpack_next(&msg, buffer->data, buffer->size, NULL);

    msgpack_object obj = msg.data;
    msgpack_object_print(stdout, obj); /*=> ["Hello", "MessagePack", 12345] */

    msgpack_sbuffer_free(buffer);
    msgpack_packer_free(pk);
}
