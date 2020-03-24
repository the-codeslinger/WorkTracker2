#pragma once

#include <QString>
#include <QDomDocument>

#include "../../worktracker2_global.h"

namespace Data::Xml {

/**
 * Represents the XML database file loaded into memory. If the file doesn't exist it
 * will be created.
 */
class WT2_EXPORT XmlDataSource {
public:
    /**
     * Creates a new data source with an optional path to the database file.
     *
     * @param[in] location
     *      If specified the XML file at that location will be used as database file.
     *      Other the standard location in the user's data directory is used.
     */
    XmlDataSource(QString location = "");

    /**
     * Copy-constructor.
     */
    XmlDataSource(const XmlDataSource& other);

    /**
     * Move-constructor.
     */
    XmlDataSource(XmlDataSource&& temp);

    /**
     * Assignment operator.
     */
    XmlDataSource& operator=(const XmlDataSource& other);

    /**
     * AMove-asignment operator.
     */
    XmlDataSource& operator=(XmlDataSource&& temp);

    /**
     * @return
     *      Returns the state of the data source. If it is correctly loaded then `false`
     *      is returned. If there's a problem loading or creating the database then `true`
     *      is returned.
     */
    bool isNull() const;

    /**
     * @return
     *      Returns the internal DOM document for use when DOM objects need to be created.
     */
    QDomDocument document() const;

    /**
     * Reads the XML database from the given location, the default location in the user's
     * data directory or creates a new one in memory which will be written to the default
     * location.
     *
     * @return
     *      `true` on success or `false` if any error occurred.
     */
    bool load();

    /**
     * Saves the database to the location determined in `DataSource::load()`.
     *
     * @return
     *      `true` on success or `false` if any error occurred.
     */
    bool save() const;

    /**
     * @return
     *      Returns the database file location.
     */
    QString location() const;

private:
    QDomDocument document_;
    QString      location_;
};

}
