#include <QDir>
#include <QStandardPaths>

#include <core/logging.h>
#include <data/datasource.h>

using namespace Data;

DataSource::DataSource(QString location, QString filename)
{
    if (location.isEmpty())  {
        qCDebug(LOG_WT2) << "No database location specified; use user's default data directory";
        location = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    }

    QDir dir(location);
    if (!dir.exists()) {
        qCDebug(LOG_WT2) << "Database location does not exist; create now";

        if (!dir.mkpath(location)) {
            qCCritical(LOG_WT2) << "Cannot create database directory: " << location;
        }
    }

    absoluteFilePath_ = location;
    if (!location.endsWith(QDir::separator())) {
        absoluteFilePath_ += QDir::separator();
    }
    absoluteFilePath_ +=  filename;

    qCDebug(LOG_WT2) << "Database file-path: " << absoluteFilePath_;
}

QString
DataSource::absoluteFilePath() const
{
    return absoluteFilePath_;
}
