#include "threads/UIMessageQueue.hpp"

K_MSGQ_DEFINE(
    ui_message_queue,
    sizeof(UIMessage),
    10,
    4);