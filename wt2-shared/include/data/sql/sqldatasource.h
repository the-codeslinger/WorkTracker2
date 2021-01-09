#pragma once

#include <QString>

#include <worktracker2_global.h>
#include <data/datasource.h>

class QSqlDatabase;

namespace Data::Sql {

/**
 * Implements a connection to a SQLite database. One or more `SqlDataSource` classes
 * can exist at the same time for the same database.
 *
 * On start of the application `SqlDataSource::init()` must be called and
 * `SqlDataSource::cleanup()` when the application terminates.
 */
class WT2_EXPORT SqlDataSource : Data::DataSource {
public:
    /**
     * Registers a database with `QSqlDatabase` using the connection name
     * "WorkTracker2.db".
     * Must be called once on application startup.
     */
    static void init();
    /**
     * Removes the database connection "WorkTracker2.db" from `QSqlDatabase`.
     * Must be called once on application termination.
     */
    static void cleanup();

    /**
     * Creates a new data source with an optional path to the database file. The database
     * filename is "WorkTracker2.db".
     *
     * @param[in] location
     *      If specified, the given directory will be used to create a new database file
     *      or use the existing database file found at that location.
     *
     */
    SqlDataSource(QString location = "");

    /**
     * Load an existing database or create a new one. Uses the location specified in the
     * constructor or the user's profile default data directory.
     *
     * @return
     *      `true` on success or `false` on error.
     */
    bool load();

    /**
     * Save the current state of the database to file.
     *
     * @return
     *      `true` on success or `false` on error.
     */
    bool save();

    /**
     * Returns a connection to the database. Make sure to test if the connection is open
     * before using it. If `load()` fails and its return value is ignored then the
     * connection object returned may not be a valid connection.
     */
    QSqlDatabase database() const;

private:
    static constexpr const char* FILENAME = "WorkTracker2.db";
    static constexpr const char* SQLITE_DRIVER = "QSQLITE";

    /**
     * Execute DDL commands to create tables and indices.
     */
    bool createTables();

    /**
     * Verify that the database contains a valid table structure.
     */
    bool verifyTables() const;
};

}
