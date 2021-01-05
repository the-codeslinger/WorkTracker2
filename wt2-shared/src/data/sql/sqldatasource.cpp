#include <QFile>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>

#include <core/logging.h>
#include <data/sql/sqldatasource.h>

using namespace Data::Sql;

SqlDataSource::SqlDataSource(QString location)
    : Data::DataSource{location, FILENAME}
{
}

bool
SqlDataSource::load()
{
    auto dbFilePath = absoluteFilePath();
    auto dbExists = QFile::exists(dbFilePath);

    auto db = QSqlDatabase::addDatabase(SQLITE_DRIVER);
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
    return QSqlDatabase::database();
}

bool
SqlDataSource::createTables()
{
    auto conn = database();
    if (!conn.transaction()) {
        return false;
    }

    QSqlQuery query;

    if (query.exec("PRAGMA foreign_keys = ON;")) {
        return false;
    }

    if (query.exec("CREATE TABLE task"
                   "("
                     "id        INTEGER PRIMARY KEY ASC,"
                     "name      TEXT    NOT NULL,"
                     "last_used TEXT    NOT NULL"
                   ");")) {
        return false;
    }

    if (query.exec("CREATE INDEX ix_task_last_used ON task (last_used);")) {
        return false;
    }

    if (query.exec("CREATE TABLE workday"
                   "("
                     "id        INTEGER PRIMARY KEY ASC,"
                     "start     TEXT    NOT NULL,"
                     "stop      TEXT    NULL"
                   ");")) {
        return false;
    }

    if (query.exec("CREATE TABLE worktask"
                   "("
                     "id         INTEGER PRIMARY KEY ASC,"
                     "workday_id BIGINT  NOT NULL,"
                     "task_id    BIGINT  NOT NULL,"
                     "FOREIGN KEY (workday_id) REFERENCES workday (id) ON DELETE CASCADE,"
                     "FOREIGN KEY (task_id)    REFERENCES task (id)    ON DELETE CASCADE"
                   ");")) {
        return false;
    }

    if (query.exec("CREATE TABLE timeslot"
                   "("
                     "id          INTEGER PRIMARY KEY ASC,"
                     "worktask_id BIGINT  NOT NULL,"
                     "start       TEXT    NOT NULL,"
                     "stop        TEXT    NULL,"
                     "FOREIGN KEY (worktask_id) REFERENCES worktask (id) ON DELETE CASCADE"
                   ");")) {
        return false;
    }

    if (!conn.commit()) {
        conn.rollback();
        return false;
    }
    return false;
}

bool
SqlDataSource::verifyTables() const
{
    return false;
}
