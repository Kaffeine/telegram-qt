/*
   Copyright (C) 2018 Alexandr Akulich <akulichalexander@gmail.com>

   This file is a part of TelegramQt library.

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

 */

#include <QObject>
#include <QScopedValueRollback>

#include "UniqueLazyPointer.hpp"

#include <QTest>
#include <QDebug>

class tst_UniqueLazyPointer : public QObject
{
    Q_OBJECT
private slots:
    void basic();
    void lvalues();
    void rvalues();
};

struct TestClass
{
    TestClass(int value = 0)
        : member(value)
    {
        ++constructionCounter;
    }

    TestClass(const TestClass &copy) :
        TestClass(copy.member)
    {
    }

    ~TestClass()
    {
        ++destructionCounter;
    }

    int member = 0;

    static int constructionCounter;
    static int destructionCounter;
};

int TestClass::constructionCounter = 0;
int TestClass::destructionCounter = 0;

using TestClassPtr = Telegram::UniqueLazyPointer<TestClass>;

void tst_UniqueLazyPointer::basic()
{
    QScopedValueRollback<int> counter1(TestClass::constructionCounter);
    QScopedValueRollback<int> counter2(TestClass::destructionCounter);
    {
        // Default constructor
        TestClassPtr nullPtr;
        QVERIFY(nullPtr.isNull());
        QCOMPARE(TestClass::constructionCounter, 0);

        TestClassPtr data1Ptr;
        TestClassPtr data2Ptr;
        // Access the object to trigger its construction
        data1Ptr->member = 1;
        data2Ptr->member = 2;
        QCOMPARE(data1Ptr->member, 1);
        QCOMPARE(data2Ptr->member, 2);

        QVERIFY(data1Ptr);
        QCOMPARE(TestClass::constructionCounter, 2);
        QCOMPARE(TestClass::destructionCounter, 0);
    }
    QCOMPARE(TestClass::destructionCounter, 2);
}

void tst_UniqueLazyPointer::lvalues()
{
    QScopedValueRollback<int> counter1(TestClass::constructionCounter);
    QScopedValueRollback<int> counter2(TestClass::destructionCounter);

    // Default constructor
    TestClassPtr nullPtr;
    TestClassPtr data1Ptr;
    TestClassPtr data2Ptr;
    data1Ptr->member = 1;
    data2Ptr->member = 2;
    QCOMPARE(TestClass::constructionCounter, 2);
    TestClass::constructionCounter = 0;

    // Test matrix:
    // LValue argument; copy constructor from null ptr
    // LValue argument; copy constructor from ptr with object
    // LValue argument; assignment operator from null ptr to null ptr
    // LValue argument; assignment operator from null ptr to ptr with object
    // LValue argument; assignment operator from ptr with object to null ptr
    // LValue argument; assignment operator from ptr with object to ptr with object

    // Copy constructor from null ptr
    TestClassPtr ptr1 = nullPtr;
    QCOMPARE(TestClass::constructionCounter, 0);
    QVERIFY(!ptr1);

    // Copy constructor from ptr with object
    TestClassPtr ptr2 = data1Ptr;
    QVERIFY(data1Ptr);
    QVERIFY(ptr2);
    QCOMPARE(TestClass::constructionCounter, 1);
    TestClass::constructionCounter = 0;

    TestClassPtr ptr4;

    // assignment operator from null ptr to null ptr
    ptr4 = nullPtr;
    QCOMPARE(TestClass::constructionCounter, 0);
    QVERIFY(!ptr4);

    // assignment operator from null ptr to ptr with object
    ptr4 = data1Ptr;
    QCOMPARE(TestClass::constructionCounter, 1);
    QVERIFY(ptr4);
    TestClass::constructionCounter = 0;

    // assignment operator from ptr with object to null ptr
    QCOMPARE(TestClass::destructionCounter, 0);
    ptr4 = nullPtr;
    QCOMPARE(TestClass::destructionCounter, 1);
    QVERIFY(!ptr4);
    TestClass::destructionCounter = 0;

    // assignment operator from ptr with object to ptr with object
    QCOMPARE(data1Ptr->member, 1);
    QCOMPARE(data2Ptr->member, 2);
    data1Ptr = data2Ptr;
    QCOMPARE(data1Ptr->member, 2);
    QCOMPARE(TestClass::constructionCounter, 0);
    QCOMPARE(TestClass::destructionCounter, 0);
}

void tst_UniqueLazyPointer::rvalues()
{
    QScopedValueRollback<int> counter1(TestClass::constructionCounter);
    QScopedValueRollback<int> counter2(TestClass::destructionCounter);

    // Default constructor
    TestClassPtr nullPtr;
    TestClassPtr data1Ptr;
    TestClassPtr data2Ptr;
    data1Ptr->member = 1;
    data2Ptr->member = 2;
    QCOMPARE(TestClass::constructionCounter, 2);
    TestClass::constructionCounter = 0;

    // Test matrix:
    // Default constructor
    // RValue argument; move constructor from null ptr
    // RValue argument; move constructor from ptr with object
    // RValue argument; move (assignment) operator from null ptr to null ptr
    // RValue argument; move (assignment) operator from null ptr to ptr with object
    // RValue argument; move (assignment) operator from ptr with object to null ptr
    // RValue argument; move (assignment) operator from ptr with object to ptr with object

    // Move constructor from null
    QCOMPARE(TestClass::constructionCounter, 0);
    TestClassPtr ptr4 = TestClassPtr();
    QVERIFY(!ptr4);
    QCOMPARE(TestClass::constructionCounter, 0);

    // Move constructor from obj
    TestClassPtr ptr5 = TestClassPtr(new TestClass);
    QCOMPARE(TestClass::constructionCounter, 1);
    // cleanup
    TestClass::constructionCounter = 0;

    // move (assignment) operator from null ptr to null ptr
    TestClassPtr ptr6;
    ptr6 = TestClassPtr();
    QVERIFY(ptr6.isNull());
    QCOMPARE(TestClass::constructionCounter, 0);
    QCOMPARE(TestClass::destructionCounter, 0);

    // move (assignment) operator from null ptr to ptr with object
    ptr6 = TestClassPtr(new TestClass);
    QCOMPARE(TestClass::constructionCounter, 1);
    QCOMPARE(TestClass::destructionCounter, 0);
    // cleanup
    TestClass::constructionCounter = 0;

    // move (assignment) operator from ptr with object to null ptr
    ptr6 = TestClassPtr();
    QVERIFY(ptr6.isNull());
    QCOMPARE(TestClass::constructionCounter, 0);
    QCOMPARE(TestClass::destructionCounter, 1);
    // cleanup
    TestClass::destructionCounter = 0;

    // move (assignment) operator from ptr with object to ptr with object
    TestClassPtr ptr7;
    ptr7->member = 1;
    QCOMPARE(TestClass::constructionCounter, 1);
    QCOMPARE(TestClass::destructionCounter, 0);
    TestClass::constructionCounter = 0;
    QCOMPARE(ptr7->member, 1);
    ptr7 = TestClassPtr(new TestClass(12));
    QCOMPARE(ptr7->member, 12);
    QCOMPARE(TestClass::constructionCounter, 1);
    QCOMPARE(TestClass::destructionCounter, 1);
}

QTEST_APPLESS_MAIN(tst_UniqueLazyPointer)

#include "tst_UniqueLazyPointer.moc"
