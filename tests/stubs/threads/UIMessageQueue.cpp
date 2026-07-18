#include "threads/UIMessageQueue.hpp"

#include <cstring>

k_msgq ui_message_queue;

int mock_msgq_return = 0;

UIMessage mock_last_message{};

int k_msgq_put(
    k_msgq*,
    const void* data,
    int32_t)
{
    std::memcpy(
        &mock_last_message,
        data,
        sizeof(UIMessage));

    return mock_msgq_return;
}