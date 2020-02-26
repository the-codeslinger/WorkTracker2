#pragma once

#include <optional>

#include "../worktracker2_global.h"

#include "../model/workday.h"

namespace Data {

/**
 * The main data access class for `Workday` objects. This defines all the find and save
 * methods that are required by the application.
 *
 * It is comparable to Spring Data repository classes, only with less magic happening
 * in the background.
 */
class WT2_EXPORT WorkdayRepository {
public:
    virtual ~WorkdayRepository() {}

    /**
     * Count the number of workdays in the database. The number returned does not
     * differentiate between active and not active. All workdays are returned.
     */
    virtual int countWorkdays() const = 0;

    /**
     * Find the workday that is still active. By design it is expected that there is no or
     * at maximum one workday active.
     *
     * @return
     *      Returns the one and only active workday or `nullopt` if none exists.
     */
    virtual std::optional<Model::Workday> findLastActiveWorkday() const = 0;

    /**
     * TBD if still required
     *
     * @param index
     * @return

    virtual std::optional<Model::Workday> findWorkdayAt(int index) const = 0;*/

    /**
     * Save a new workday to the database.
     *
     * @param workday
     *      The workday to save. If the task has an id then its values are updated.
     *
     * @return
     *      Returns the saved task. If the task is new then the returned value contains
     *      the database id in addition to the name.
     */
    virtual void saveWorkday(const Model::Workday& workday) = 0;
};

}
