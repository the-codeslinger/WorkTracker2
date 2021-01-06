#include "../testrunner.h"

class TestDataSource : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();

    // Custom tests.
    void loadDefaultLocationCreateNewSuccess();
    void loadSpecificLocationCreateNewSuccess();
    void loadExistingInvalidDbError();

private:
    QString expectedDefaultDbFilePath_;
    QString expectedSpecificDbFilePath_;
};
