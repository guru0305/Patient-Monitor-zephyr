#pragma once

extern int mock_usb_enable_return;

inline int usb_enable(void*)
{
    return mock_usb_enable_return;
}