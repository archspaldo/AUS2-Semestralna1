#pragma once
#include <QtWidgets/QMainWindow>
#include <process.h>
#include <QStandardItemModel>
#include "ui_QT_Semes.h"
#include "Controller.h"
#include "StructureTester.h"
#include "QT_test_view.h"
#include "QT_person_view.h"
#include "QT_locations_view.h"
#include "QT_add_person.h"
#include "QT_add_test.h"
#include "QT_generator.h"
#include "QT_tester.h"

class QT_Semes : public QMainWindow
{
    Q_OBJECT;
public:
    explicit QT_Semes(QWidget *parent = Q_NULLPTR);
    ~QT_Semes();
private Q_SLOTS:
    void on_test_doubleclicked(QAbstractItemModel *item_model = nullptr);
    void on_person_view_triggered();
    void on_test_view_triggered();
    void on_location_view_triggered();
    void on_add_person_triggered();
    void on_add_test_triggered();
    void on_generate_triggered();
    void on_tester_triggered();
private:
    void person_view();
    void test_view(QAbstractItemModel *item_model = nullptr);
    void location_view();
private:
    Ui::QT_SemesClass ui_;
    AUS2::Controller *controller_;
    QTestView *test_view_;
    QPersonView *person_view_;
    QLocationView *location_view_;
};
