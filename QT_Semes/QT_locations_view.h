#pragma once
#include <QtWidgets/qwidget.h>
#include <QStandardItemModel>
#include <list>
#include "ui_QT_locations_view.h"
#include "QT_person_information.h"
#include "QT_test_information.h"

class QTLocationsView : public QWidget
{
	Q_OBJECT;
public:
	explicit QTLocationsView(QWidget *parent = nullptr, AUS2::Controller *controller = nullptr);
	~QTLocationsView();
private Q_SLOTS:
	void on_filter_button_clicked();
	void on_reset_button_clicked();
	void on_select_location();
private:
	void render_people(std::list<AUS2::Person *> *person_list);
	void render_tests(std::list<AUS2::Test *> *test_list);
	void render_locations(std::list<std::pair<AUS2::TestLocation *, int> *> *location_list);
	void set_active_model();
	QPersonInformation *person_information_;
	QTestInformation *test_information_;
	QAbstractItemModel *person_model_, *test_model_;
	Ui::Form_location_view ui_;
	AUS2::Controller *controller_;
};

