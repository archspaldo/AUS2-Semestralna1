#pragma once
#include <QtWidgets/qwidget.h>
#include <QStandardItemModel>
#include <list>
#include <QHeaderView>
#include "ui_QT_locations_view.h"
#include "QT_person_information.h"
#include "QT_test_information.h"

class QLocationView : public QWidget
{
	Q_OBJECT;
public:
	explicit QLocationView(QWidget *parent = nullptr, AUS2::Controller *controller = nullptr);
	~QLocationView();
	void set_active();
private Q_SLOTS:
	void on_filter_button_clicked();
	void on_reset_button_clicked();
	void on_location_selected();
	void on_model_selected();
	void on_item_clicked();
	void on_person_removed();
	void on_test_removed();
	void on_test_double_clicked(QAbstractItemModel *model = nullptr);
private:
	void render_people(std::list<AUS2::Person *> *person_list);
	void render_tests(std::list<AUS2::Test *> *test_list);
	void render_locations(std::list<std::pair<AUS2::TestLocation *, int> *> *location_list);
	void update_model();
	QPersonInformation *person_information_;
	QTestInformation *test_information_;
	QAbstractItemModel *person_model_, *test_model_, *location_model_;
	Ui::Form_location_view ui_;
	AUS2::Controller *controller_;
Q_SIGNALS:
	void test_doubleclicked(QAbstractItemModel * = nullptr);
};

