#pragma once

namespace config {
    const bool DEBUG = false;
    const bool USE_DUMMY_DATA = false;
    const int WINDOW_ID = 0; // [ 0 ~ 3 ]
    const int OSC_RECV_PORT_OFFSET = 60020;
    const int OSC_RECV_PORT = OSC_RECV_PORT_OFFSET + WINDOW_ID;
    const int FPS = 30;
    const int DIVIDED_WIDTH = 360;
    const int WIDTH = 4 * DIVIDED_WIDTH;
    const int HEIGHT = 640;
    const double ASPECT_RATIO = (double) WIDTH /  (double) HEIGHT;
};