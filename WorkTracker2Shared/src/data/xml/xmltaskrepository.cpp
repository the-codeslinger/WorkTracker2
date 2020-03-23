#include "../../core/constants.h"
#include "xmltaskrepository.h"

using namespace Data::Xml;

static const QString TASKS_LIST_ELEMENT_NAME = "tasks";
static const QString TASK_ID_ELEMENT_NAME = "id";
static const QString TASK_NAME_ELEMENT_NAME = "name";
static const QString TASK_LAST_USED_ELEMENT_NAME = "last_used";

XmlTaskRepository::XmlTaskRepository(const XmlDataSource& dataSource)
    : XmlRepository(dataSource, TASKS_LIST_ELEMENT_NAME)
{
}

XmlTaskRepository::~XmlTaskRepository()
{
}

int
XmlTaskRepository::countTasks() const
{
    return dom_.childNodes().size();
}

std::optional<Model::Task>
XmlTaskRepository::findTaskById(int id) const
{
    auto found = findFirstNode([id](const QDomElement& element) {
        auto value = element.attribute(TASK_ID_ELEMENT_NAME);
        if (!value.isNull()) {
            auto ok = false;
            auto foundId = value.toInt(&ok);
            if (ok) {
                return id == foundId;
            }
        }
        return false;
    });
    return taskFromElement(found);
}

std::optional<Model::Task>
XmlTaskRepository::findTaskByName(const QString& name) const
{
    auto found = findFirstNode([name](const QDomElement& element) {
        return name.toLower() == element.attribute(TASK_NAME_ELEMENT_NAME).toLower();
    });
    return taskFromElement(found);
}

QList<Model::Task>
XmlTaskRepository::listTasksSortedByLastUsed() const
{
    auto list = QList<Model::Task>{};

    auto children = dom_.childNodes();

    int size = children.size();
    for (int i = 0; i < size; i++) {
        auto taskNode = children.at(i);
        if (taskNode.isElement() && !taskNode.isNull()) {
            list << taskFromElement(taskNode.toElement()).value();
        }
    }

    auto sorter = [](const Model::Task& left, const Model::Task& right) {
        return left.lastUsed() > right.lastUsed();
    };
    std::sort(std::begin(list), std::end(list), sorter);
    return list;
}

Model::Task
XmlTaskRepository::saveTask(Model::Task& task)
{
    if (Core::Constants::invalidId == task.id()) {
        task.setId(countTasks());
        dom_.appendChild(elementFromTask(task));
    } else {

        // Update
    }
    return task;
}

std::optional<Model::Task>
XmlTaskRepository::taskFromElement(const QDomElement& taskElement) const
{
    if (taskElement.isNull()) {
        return std::nullopt;
    }

    return Model::Task{
        attributeInt(TASK_ID_ELEMENT_NAME, taskElement),
        attributeString(TASK_NAME_ELEMENT_NAME, taskElement),
        attributeDateTime(TASK_LAST_USED_ELEMENT_NAME, taskElement)
    };
}

QDomElement
XmlTaskRepository::elementFromTask(const Model::Task& task) const
{
    auto element = QDomElement{};
    return updateElement(task, element);
}

QDomElement
XmlTaskRepository::updateElement(const Model::Task& task, QDomElement& element) const
{
    setAttribute(TASK_ID_ELEMENT_NAME, task.id(), element);
    setAttribute(TASK_NAME_ELEMENT_NAME, task.name(), element);
    setAttribute(TASK_LAST_USED_ELEMENT_NAME, task.lastUsed(), element);
    return element;
}
