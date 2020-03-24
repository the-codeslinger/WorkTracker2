#include <QDebug>

#include "../../core/constants.h"
#include "xmlworkdayrepository.h"

using namespace Data::Xml;

static const QString WORKDAY_LIST_ELEMENT_NAME = "workdays";
static const QString WORKDAY_ELEMENT_NAME = "day";
static const QString WORKTASK_ELEMENT_NAME = "task";
static const QString TIMESLOT_ELEMENT_NAME = "time";

static const QString START_ATTRIBUTE_NAME = "start";
static const QString STOP_ATTRIBUTE_NAME = "stop";

XmlWorkdayRepository::XmlWorkdayRepository(
        const XmlDataSource& dataSource,
        const XmlTaskRepository& taskRepository)
    : XmlRepository (dataSource, WORKDAY_LIST_ELEMENT_NAME)
    , taskRepository_(taskRepository)
{
}

int
XmlWorkdayRepository::countWorkdays() const
{
    return count();
}

std::optional<Model::Workday>
XmlWorkdayRepository::findLastActiveWorkday() const
{
    return std::nullopt;
}

Model::Workday
XmlWorkdayRepository::saveWorkday(Model::Workday& workday)
{

    if (Core::Constants::invalidId == workday.id()) {
        workday.setId(count());
        appendChild(elementFromWorkday(workday));
    } else {
        auto found = findElementById(workday.id());
        // It's easier to start from scratch rather than performing a diff and removing
        // obsolete data and update what remains.
        found.clear();
        found.setTagName(WORKDAY_ELEMENT_NAME);
        updateElement(workday, found);
    }
    return workday;
}

Model::Workday
XmlWorkdayRepository::workdayFromElement(const QDomElement& workdayElement) const
{
    auto workTasks = QList<Model::WorkTask>{};
    auto workTaskElements = workdayElement.childNodes();

    for (int c = 0; c < workTaskElements.size(); c++) {
        auto workTaskElement = workTaskElements.at(c);
        if (!workTaskElement.isElement() || !workTaskElement.isNull()) {
            qDebug() << "Found work task element that is no element or is null; ignoring";
            continue;
        }

        workTasks << workTaskFromElement(workTaskElement.toElement());
    }

    return Model::Workday{
        attributeInt(ID_ATTRIBUTE_NAME, workdayElement),
        attributeDateTime(START_ATTRIBUTE_NAME, workdayElement),
        attributeDateTime(STOP_ATTRIBUTE_NAME, workdayElement),
        workTasks
    };
}

QDomElement
XmlWorkdayRepository::elementFromWorkday(const Model::Workday& workday) const
{
    auto element = createElement(WORKDAY_ELEMENT_NAME);
    return updateElement(workday, element);
}

QDomElement
XmlWorkdayRepository::updateElement(const Model::Workday& workday, QDomElement& element) const
{
    // The day element.
    setAttribute(ID_ATTRIBUTE_NAME, workday.id(), element);
    setAttribute(START_ATTRIBUTE_NAME, workday.start(), element);
    setAttribute(STOP_ATTRIBUTE_NAME, workday.stop(), element);

    // All the worktask elements.
    for (const auto& worktask : workday.workTasks()) {
        auto wte = createElement(WORKTASK_ELEMENT_NAME);
        setAttribute(ID_ATTRIBUTE_NAME, worktask.task().id(), wte);
        element.appendChild(wte);

        // All the timeslot elements
        for (const auto& timeslot : worktask.timeSlots()) {
            auto tse = createElement(TIMESLOT_ELEMENT_NAME);
            setAttribute(START_ATTRIBUTE_NAME, timeslot.start(), tse);
            setAttribute(STOP_ATTRIBUTE_NAME, timeslot.stop(), tse);
            wte.appendChild(tse);
        }
    }

    return element;
}

Model::WorkTask
XmlWorkdayRepository::workTaskFromElement(const QDomElement& workTaskElement) const
{
    auto taskId = attributeInt(ID_ATTRIBUTE_NAME, workTaskElement);
    auto task = taskRepository_.findTaskById(taskId);

    auto workTask = Model::WorkTask{};
    if (!task.has_value()) {
        qDebug() << "Found taskId " << taskId << " but there is no task with this id";
    }

    workTask.setTask(task.value());
    addTimeslots(workTaskElement.childNodes(), workTask);

    return workTask;
}

void
XmlWorkdayRepository::addTimeslots(
        const QDomNodeList& nodes,
        Model::WorkTask& workTask) const
{
    for (int t = 0; t < nodes.size(); t++) {
        auto tnode = nodes.at(t);
        if (!tnode.isElement() || !tnode.isNull()) {
            qDebug() << "Found timeslot element that is no element or is null; ignoring";
            continue;
        }

        auto timeslot = timeslotFromElement(tnode.toElement());
        workTask.addTimeslot(timeslot);
    }
}

Model::Timeslot
XmlWorkdayRepository::timeslotFromElement(const QDomElement& timeslotElement) const
{
    return Model::Timeslot{
        attributeDateTime(START_ATTRIBUTE_NAME, timeslotElement),
        attributeDateTime(STOP_ATTRIBUTE_NAME, timeslotElement)
    };
}
