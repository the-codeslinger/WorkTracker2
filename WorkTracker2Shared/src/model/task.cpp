#include "task.h"
#include "../core/constants.h"

using namespace Model;

Task::Task()
    : Task(Core::invalidId, "", QDateTime())
{
}

Task::Task(int id, const QString& name, const QDateTime& lastUsed)
{
    id_ = id;
    name_ = name;
    lastUsed_ = lastUsed;
}
