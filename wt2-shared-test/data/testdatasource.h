#include "../testrunner.h"

class TestDataSource : public QObject
{
    Q_OBJECT

private slots:
//    void initTestCase();
//    void cleanupTestCase();

    void init();
    void cleanup();

    // Custom tests.
    void loadDefaultLocationCreateNewSuccess();
    void loadSpecificLocationCreateNewSuccess();
    void loadExistingInvalidDbError();
    void loadExistingValidDbSuccess();

private:
    QString expectedDefaultDbFilePath_;
    QString expectedSpecificDbFilePath_;
};
