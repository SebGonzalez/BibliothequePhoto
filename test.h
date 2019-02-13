#ifndef TEST_H
#define TEST_H

#include <QDeclarativeItem>
#include <QMainWindow>
#include <QObject>
#include <QQuickItem>
#include <QSharedDataPointer>
#include <QWidget>

class testData;

class test : public QMainWindow
{
    Q_OBJECT
public:
    explicit test(QWidget *parent = nullptr);
    test(const test &);
    test &operator=(const test &);
    ~test();

signals:

public slots:

private:
    QSharedDataPointer<testData> data;
};

#endif // TEST_H
