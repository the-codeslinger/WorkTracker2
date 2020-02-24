#pragma once

#include <QtCore/qglobal.h>

namespace Core {

class Duration {
private:
    qint64 seconds_;

public:
    Duration(qint64 seconds);

    Duration(const Duration& other);

    Duration& operator=(const Duration& other);
};

}
