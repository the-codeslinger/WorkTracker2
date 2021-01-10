#include <QFile>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>

#include <core/logging.h>
#include <data/sql/sqldatasource.h>

using namespace Data::Sql;

void
SqlDataSource::init()
{
    QSqlDatabase::addDatabase(SQLITE_DRIVER, FILENAME);
}

void
SqlDataSource::cleanup()
{
    QSqlDatabase::removeDatabase(FILENAME);
}

SqlDataSource::SqlDataSource(QString location)
    : Data::DataSource{location, FILENAME}
{
}

SqlDataSource::SqlDataSource(SqlDataSource&& other)
    : DataSource(std::move(other))
{
}

bool
SqlDataSource::load()
{
    auto dbFilePath = absoluteFilePath();
    auto dbExists = QFile::exists(dbFilePath);

    auto db = database();
    db.setDatabaseName(dbFilePath);

    if (!db.open()) {
        qCCritical(LOG_WT2) << "Cannot open database file: " << db.lastError().text();
        return false;
    }

    if (!dbExists && !createTables()) {
        qCCritical(LOG_WT2) << "Cannot create database tables: " << db.lastError().text();
        return false;
    }

    return verifyTables();
}

bool
SqlDataSource::save()
{
    // Nothing to do here. Database does not need to be saved explicitly.
    return true;
}

QSqlDatabase
SqlDataSource::database() const
{
    // Since only one connection is required for this application the default connection
    // is used.
    return QSqlDatabase::database(FILENAME);
}

bool
SqlDataSource::createTables()
{
    constexpr const char* foreignKeys =
            "PRAGMA foreign_keys = ON;";
    constexpr const char* tableTask =
            "CREATE TABLE task"
            "("
              "id        INTEGER PRIMARY KEY ASC,"
              "name      TEXT    NOT NULL,"
              "last_used TEXT    NOT NULL"
            ");";
    constexpr const char* tableWorkday =
            "CREATE TABLE workday"
            "("
              "id        INTEGER PRIMARY KEY ASC,"
              "start     TEXT    NOT NULL,"
              "stop      TEXT    NULL"
            ");";
    constexpr const char* tableWorktask =
            "CREATE TABLE worktask"
            "("
              "id         INTEGER PRIMARY KEY ASC,"
              "workday_id BIGINT  NOT NULL,"
              "task_id    BIGINT  NOT NULL,"
              "FOREIGN KEY (workday_id) REFERENCES workday (id) ON DELETE CASCADE,"
              "FOREIGN KEY (task_id)    REFERENCES task (id)    ON DELETE CASCADE"
            ");";
    constexpr const char* tableTimeslot =
            "CREATE TABLE timeslot"
            "("
              "id          INTEGER PRIMARY KEY ASC,"
              "worktask_id BIGINT  NOT NULL,"
              "start       TEXT    NOT NULL,"
              "stop        TEXT    NULL,"
              "FOREIGN KEY (worktask_id) REFERENCES worktask (id) ON DELETE CASCADE"
            ");";
    constexpr const char* indexTask =
            "CREATE INDEX ix_task_last_used ON task (last_used);";

    auto query = QSqlQuery{database()};
    return query.exec(foreignKeys)
            && query.exec(tableTask)
            && query.exec(tableWorkday)
            && query.exec(tableWorktask)
            && query.exec(tableTimeslot)
            && query.exec(indexTask);
}

bool
SqlDataSource::verifyTables() const
{
    auto conn = database();
    auto tables = conn.tables();

    return tables.contains("task")
            && tables.contains("workday")
            && tables.contains("worktask")
            && tables.contains("timeslot");
}
