
#include "touchscreen.h"

touchscreen::touchscreen()
{
    setAcceptTouchEvents(true);
}

bool touchscreen::sceneEvent(QEvent *event) {
    emit touchEvent();
    return true;
}

