#pragma once

#include <QtWidgets/QMainWindow>
#include <process.h>
#include <QStandardItemModel>
#include "ui_QT_Semes.h"
#include "Controller.h"

class QT_Semes : public QMainWindow
{
    Q_OBJECT

public:
    QT_Semes(QWidget *parent = Q_NULLPTR);

private slots:
    void onButtonClickedGeneratePeople();
    void onActionZobrazit();
    void onActionPridatMan();
    void onActionPridatGen();
    void onSelectedPerson();
    void onSelectedTest();
    void onDoubleClickedTest();
    void onClickedOsobaView();
    void onClickedTestView();
    void onClickedOkresView();
    void onClickedKrajView();
    void onClickedSlovenskoView();
    void onFilterPerson();
    void onResetPerson();
    void onFilterTest();
    void onResetTest();
    void onFilterDistrict();
    void onResetDistrict();
private:
    void test_view();
    void person_view();
    void district_view();
    void render_person_view(std::list<AUS2::Person *> *l);
    void render_test_view(std::list<AUS2::Test *> *l);
    void render_person(const std::string &id);
    void render_test(const std::string &uuid);
    
private:
    Ui::QT_SemesClass ui_;
    AUS2::Controller *controller_;
};
