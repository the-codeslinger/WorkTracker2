#include "task.h"
#include "../core/constants.h"

using namespace Model;

Task::Task()
    : Task{Core::Constants::invalidId, "", QDateTime()}
{
}

Task::Task(int id, const QString& name, const QDateTime& lastUsed)
    : id_{id}
    , name_{name}
    , lastUsed_{lastUsed}
{
}

bool
Task::operator==(const Task& other) const
{
    return id_ == other.id_ && name_.toLower() == other.name_.toLower();
}

bool
Task::operator!=(const Task& other) const
{
    return !operator==(other);
}

bool
Task::operator<(const Task& other) const
{
    return id_ < other.id_ && name_ < other.name_;
}

int
Task::id() const
{
    return id_;
}

void
Task::setId(int id)
{
    id_ = id;
}

QString
Task::name() const
{
    return name_;
}

void
Task::setName(const QString& name)
{
    name_ = name;
}

QDateTime
Task::lastUsed() const
{
    return lastUsed_;
}

void
Task::setLastUsed(const QDateTime& lastUsed)
{
    lastUsed_ = lastUsed;
}
