#pragma once
#include <QtWidgets/QMainWindow>
#include <process.h>
#include <QStandardItemModel>
#include "ui_QT_Semes.h"
#include "Controller.h"
#include "StructureTester.h"
#include "QT_test_view.h"
#include "QT_person_view.h"

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

private:
    void person_view(QAbstractItemModel *item_model = nullptr);
    void test_view(QAbstractItemModel *item_model = nullptr);
    void tester(int operations, int insert, int remove, int get, int interval);
    
private:
    Ui::QT_SemesClass ui_;
    AUS2::Controller *controller_;
    QTestView *test_view_;
    QPersonView *person_view_;
};
