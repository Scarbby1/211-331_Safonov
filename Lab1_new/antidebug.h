#ifndef ANTIDEBUG_H
#define ANTIDEBUG_H

#include <windows.h>
#include <QMessageBox>

class AntiDebug {
public:
    static void checkDebugger();
};

#endif // ANTIDEBUG_H
