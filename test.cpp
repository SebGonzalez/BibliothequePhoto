#include "test.h"

class testData : public QSharedData
{
public:

};

test::test(QWidget *parent) : QMainWindow(parent), data(new testData)
{

}

test::test(const test &rhs) : data(rhs.data)
{

}

test &test::operator=(const test &rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

test::~test()
{

}
