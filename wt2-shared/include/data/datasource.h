#pragma once

#include <QString>

namespace Data
{

/**
 * Base class for data sources to help with database filename creation.
 */
class DataSource {
protected:
    /**
     * Create a new data source with a path and a designated database filename. The
     * directory at `location` will be created if it does not exist.
     *
     * @param location
     *      The path where the database file is stored. This parameter can be empty
     *      which will result in the user's default application data directory being
     *      used.
     *
     * @param filename
     *      The name of the database file. This must not be empty.
     */
    DataSource(QString location, QString filename);

    /**
     * Move-constructor.
     */
    DataSource(DataSource&& other);

    /**
     * Returns the computed database file's file-path that includes absolute path to the
     * file and the file's name, based on the values passed to the constructor.
     */
    QString absoluteFilePath() const;

private:
    QString absoluteFilePath_;
};

}
