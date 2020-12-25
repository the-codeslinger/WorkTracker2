#pragma once

#include <QDateTime>

#include "../worktracker2_global.h"
#include "../core/duration.h"

namespace Model {

/**
 * A timeslot is an arbitrary large span of time a user has spent working on a task.
 * It consists of a start and a stop timestamp.
 */
class WT2_EXPORT Timeslot {
public:
    /**
     * Create an invalid timeslot.
     */
    Timeslot() = default;

    /**
     * Create a timeslot with a start date. If the date is valid then the resulting
     * timeslot is valid.
     */
    Timeslot(const QDateTime& start);

    /**
     * Create a timeslot with a start and a stop date. If at least the start date is valid
     * then the resulting timeslot is considered valid.
     */
    Timeslot(const QDateTime& start, const QDateTime& stop);

    /**
     * @return
     *      Return \c true or \c false, depending on whether at least the start timestamp
     *      has been set or not. If the default constuctor was used a Timeslot and no
     *      property has been set, the instance is considered invalid.
     */
    bool isValid() const;

    /**
     * @return
     *      Returns the start timestamp. Note that this may be an invalid timestamp.
     */
    QDateTime start() const;

    /**
     * Set a new start timestamp.
     */
    void setStart(const QDateTime start);

    /**
     * @return
     *      Returns the stop timestamp. Note that this may be an invalid timestamp.
     */
    QDateTime stop() const;

    /**
     * Set a new stop timestamp.
     */
    void setStop(const QDateTime stop);

    /**
     * @return
     *      Calculates and returns the duration. If no start timestamp has been set then
     *      an invalid duration instance is returned. If start has been set, but no stop
     *      is available, then a current timestamp is used as stop. This is useful to get
     *      an intermediate result.
     */
    Core::Duration duration() const;

private:
    QDateTime start_;
    QDateTime stop_;
};

}
