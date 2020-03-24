#pragma once

#include "../../worktracker2_global.h"
#include "../workdayrepository.h"
#include "xmlrepository.h"
#include "xmltaskrepository.h"

namespace Data::Xml {

/**
 * Implements the `Data::WorkdayRepository` for use with an XML database file.
 */
class WT2_EXPORT XmlWorkdayRepository : XmlRepository, WorkdayRepository {
public:
    XmlWorkdayRepository(
            const XmlDataSource& dataSource,
            const XmlTaskRepository& taskRepository);

    virtual int countWorkdays() const override;

    virtual std::optional<Model::Workday> findLastActiveWorkday() const override;

    virtual Model::Workday saveWorkday(Model::Workday& workday) override;

private:
    Model::Workday workdayFromElement(const QDomElement& workdayElement) const;
    Model::WorkTask workTaskFromElement(const QDomElement& workTaskElement) const;
    Model::Timeslot timeslotFromElement(const QDomElement& timeslotElement) const;

    void addTimeslots(const QDomNodeList& nodes, Model::WorkTask& worktask) const;

    QDomElement elementFromWorkday(const Model::Workday& workday) const;
    QDomElement updateElement(const Model::Workday& workday, QDomElement& element) const;

    XmlTaskRepository taskRepository_;
};

}
