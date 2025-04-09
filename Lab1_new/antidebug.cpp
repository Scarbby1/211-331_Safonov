#include "antidebug.h"

void AntiDebug::checkDebugger() {
    if (IsDebuggerPresent()) {
        QMessageBox::critical(nullptr, "Обнаружена отладка", "Приложение запущено под отладчиком!");
        exit(1);
    }
}
