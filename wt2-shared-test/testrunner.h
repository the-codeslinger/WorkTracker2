#pragma once

#include <QTest>
#include <QList>
#include <QString>
#include <QSharedPointer>

namespace Test
{
    class TestRunner
    {
        typedef QList<QSharedPointer<QObject>> TestList;

    public:
        static bool findObject(QSharedPointer<QObject> object)
        {
            TestList& list = testList();
            if (list.contains(object)) {
                return true;
            }

            foreach (QSharedPointer<QObject> test, list) {
                if (test->objectName() == object->objectName()) {
                    return true;
                }
            }
            return false;
        }

        static void addTest(QSharedPointer<QObject> object)
        {
            TestList &list = testList();
            if (!findObject(object)) {
                list.append(object);
            }
        }

        static int run(int argc, char* argv[])
        {
            int ret = 0;

            foreach (QSharedPointer<QObject> test, testList()) {
                ret += QTest::qExec(test.data(), argc, argv);
            }

            return ret;
        }

    private:
        TestRunner() = delete;

        static TestList& testList()
        {
            static TestList list;
            return list;
        }
    };

    template <class T>
    class UnitTest
    {
    public:
        QSharedPointer<T> child;

        UnitTest(const QString& name)
            : child{new T}
        {
            child->setObjectName(name);
            TestRunner::addTest(child);
        }
    };
}

#define DECLARE_TEST(className) static Test::UnitTest<className> t(#className);
