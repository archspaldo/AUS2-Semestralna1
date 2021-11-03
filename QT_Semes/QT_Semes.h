#pragma once

#include <QtWidgets/QMainWindow>
#include <process.h>
#include <QStandardItemModel>
#include "ui_QT_Semes.h"
#include "Controller.h"
#include "StructureTester.h"

class QT_Semes : public QMainWindow
{
    Q_OBJECT

public:
    QT_Semes(QWidget *parent = Q_NULLPTR);
    ~QT_Semes();
private slots:
    void onButtonClickedTester();
    void onButtonClickedGeneratePeople();
    void onButtonClickedAddPerson();
    void onButtonClickedAddTest();
    void onActionZobrazit();
    void onActionPridatOsMan();
    void onActionPridatTsMan();
    void onActionPridatGen();
    void onActionTest_2();
    void onSelectedPerson();
    void onSelectedTest();
    void onDoubleClickedTest();
    void onClickedOsobaView();
    void onClickedTestView();
    void onClickedOkresView();
    void onClickedKrajView();
    void onClickedSlovenskoView();
    void onClickedStanicaView();
    void onFilterPerson();
    void onResetPerson();
    void onFilterTest();
    void onResetTest();
    void onFilterDistrict();
    void onResetDistrict();
    void onFilterStation();
    void onResetStation();
private:
    void generator_view();
    void add_person_view();
    void add_test_view();
    void tester_view();
    void test_view();
    void person_view();
    void district_view();
    void station_view();
    void tester(int operations, int insert, int remove, int get, int interval);
    void render_person_view(std::list<AUS2::Person *> *l);
    void render_test_view(std::list<AUS2::Test *> *l);
    void render_person(const std::string &id);
    void render_test(const std::string &uuid);
    
private:
    Ui::QT_SemesClass ui_;
    AUS2::Controller *controller_;
};
