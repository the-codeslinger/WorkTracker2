#pragma once

#include <QString>
#include <QDateTime>

#include "../worktracker2_global.h"

namespace Model {

/**
 * A task is something a user is working on, e.g. writing class documentation.
 * It is used to group one or more timeframes that all sum up to the total time
 * the user has spent working on that task.
 *
 * A task merely consists of a plain-text name, defined by the user, when it was
 * last used and an internal id.
 */
class WT2_EXPORT Task
{
public:
    /**
     * Creates a new `Task` without any values.
     */
    Task();

    /**
     * Creates a new instance with a data source, an id, a name and the last-used date.
     */
    Task(int id, const QString& name, const QDateTime& lastUsed);

    /**
     * Compares `id()` and `name()` and returns `true` if both are the same. The task's
     * name is compared case-insensitive.
     */
    bool operator==(const Task& other) const;

    /**
     * Compares `id()` and `name()` and returns `true` if either one of them are
     * different.The task's name is compared case-insensitive.
     */
    bool operator!=(const Task& other) const;

    /**
     * Required by `QMap` for `Task` to be used as a key. Simply compares `id` and `name`
     * with `other` using the less-than operator.
     */
    bool operator<(const Task& other) const;

    /**
     * @return
     *      Returns the database id of the task or `Core::invalidId` if the task is yet
     *      to be saved to database.
     */
    int id() const;

    /**
     * Set a new database `id`.
     */
    void setId(int id);

    /**
     * @return
     *      Returns the name of the task.
     */
    QString name() const;

    /**
     * Set a new `name` for the task.
     */
    void setName(const QString& name);

    /**
     * @return
     *      Returns the last-used date.
     */
    QDateTime lastUsed() const;

    /**
     * Set a new `lastUsed` date.
     */
    void setLastUsed(const QDateTime& lastUsed);

private:
    int id_;
    QString name_;
    QDateTime lastUsed_;
};

}
