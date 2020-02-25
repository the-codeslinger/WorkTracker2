#pragma once

#include "../worktracker2_global.h"

namespace Core {

/**
 * Wraps a duration between two timestamps into a class and provides conversion methods
 * to retrieve the value in different units.
 */
class WT2_EXPORT Duration {
private:
    qint64 milliseconds_;

public:
    /**
     * Create a new instance
     */
    Duration();

    /**
     * Create a new duration of the specified amound of \a milliseconds.
     */
    Duration(qint64 milliseconds);

    /**
     * Add the `other` duration to `this` and return a new duration.
     *
     * @return
     *      If `this` and `other` are invalid then the resulting duration will be invalid.
     *      If either instance is valid then the resulting duration will also be valid.
     */
    Duration operator+(const Duration& other) const;

    /**
     * Compound assignment. Adds `other` to `this` and returns `this`. This method works
     * in the same way as the assignment operator with regards to determining validity.
     */
    Duration& operator+=(const Duration& other);

    /**
     * @return
     *      Returns the value in milliseconds.
     */
    qint64 toMilliseconds() const;

    /**
     * @return
     *      Returns the value in seconds. Note that the result is truncated to integer
     *      scaling and can lose some accuracy in the process.
     */
    qint64 toSeconds() const;

    /**
     * @return
     *      Returns the value in minutes. Note that the result is truncated to integer
     *      scaling and can lose some accuracy in the process. The value may not even
     *      be large enough for a fully minute.
     */
    qint64 toMinutes() const;

    /**
     * @return
     *      Return whether this instance constains a valid duration value.
     */
    bool isValid() const;


};

}
