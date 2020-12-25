#include <QSqlError>
#include <QSqlDatabase>

#include <core/logging.h>
#include <data/sql/sqldatasource.h>

using namespace Data::Sql;

static const QString FILENAME = "WorkTracker2.db";
static const QString SQLITE_DRIVER = "QSQLITE";

SqlDataSource::SqlDataSource(QString location)
    : Data::DataSource{location, FILENAME}
{
}

bool
SqlDataSource::load()
{
    auto dbFilePath = absoluteFilePath();
    auto db = QSqlDatabase::addDatabase(SQLITE_DRIVER);
    db.setDatabaseName(dbFilePath);
    if (!db.open()) {
        qCCritical(LOG_WT2) << "Cannot open database file: " << db.lastError().text();
        return false;
    }
    return true;
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
