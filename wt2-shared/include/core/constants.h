#pragma once

#include "../worktracker2_global.h"

namespace Core
{

/**
 * Defines application-wide constants.
 */
class WT2_EXPORT Constants {
public:
    /**
     * The default invalid value of an id.
     */
    static const int invalidId = -1;

private:
    Constants() = delete;
};

}
