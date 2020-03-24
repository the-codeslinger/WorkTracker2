#include "../../core/constants.h"
#include "xmltaskrepository.h"

using namespace Data::Xml;

static const QString TASKS_LIST_ELEMENT_NAME = "tasks";
static const QString NAME_ATTRIBUTE_NAME = "name";
static const QString LAST_USED_ATTRIBUTE_NAME = "last_used";

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
    return count();
}

std::optional<Model::Task>
XmlTaskRepository::findTaskById(int id) const
{
    auto found = findElementById(id);
    if (found.isNull()) {
        return std::nullopt;
    }
    return taskFromElement(found);
}

std::optional<Model::Task>
XmlTaskRepository::findTaskByName(const QString& name) const
{
    auto found = findFirstElement([name](const QDomElement& element) {
        return name.toLower() == element.attribute(NAME_ATTRIBUTE_NAME).toLower();
    });
    if (found.isNull()) {
        return std::nullopt;
    }
    return taskFromElement(found);
}

QList<Model::Task>
XmlTaskRepository::listTasksSortedByLastUsed() const
{
    auto converter = std::bind(
                &XmlTaskRepository::taskFromElement,
                this, std::placeholders::_1);
    auto taskResults = allElementsAs<Model::Task>(converter);

    auto sorter = [](const Model::Task& left, const Model::Task& right) {
        return left.lastUsed() > right.lastUsed();
    };
    std::sort(std::begin(taskResults), std::end(taskResults), sorter);
    return taskResults;
}

Model::Task
XmlTaskRepository::saveTask(Model::Task& task)
{
    if (Core::Constants::invalidId == task.id()) {
        task.setId(countTasks());
        appendChild(elementFromTask(task));
    } else {
        auto found = findElementById(task.id());
        updateElement(task, found);
    }
    return task;
}

Model::Task
XmlTaskRepository::taskFromElement(const QDomElement& taskElement) const
{
    return Model::Task{
        attributeInt(ID_ATTRIBUTE_NAME, taskElement),
        attributeString(NAME_ATTRIBUTE_NAME, taskElement),
        attributeDateTime(LAST_USED_ATTRIBUTE_NAME, taskElement)
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
    setAttribute(ID_ATTRIBUTE_NAME, task.id(), element);
    setAttribute(NAME_ATTRIBUTE_NAME, task.name(), element);
    setAttribute(LAST_USED_ATTRIBUTE_NAME, task.lastUsed(), element);
    return element;
}
