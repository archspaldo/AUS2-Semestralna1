#pragma once
#include <QtWidgets/qwidget.h>
#include <QStandardItemModel>
#include <list>
#include "ui_QT_person_view.h"
#include "QT_person_information.h"

class QPersonView : public QWidget
{
	Q_OBJECT;
public:
	explicit QPersonView(QWidget *parent = nullptr, AUS2::Controller *controller = nullptr);
	~QPersonView();
	void set_model(QAbstractItemModel *item_model = nullptr);
	void set_active();
	void reset_model();
private Q_SLOTS:
	void on_filter_button_clicked();
	void on_reset_button_clicked();
	void on_test_clicked();
	void on_person_removed();
private:
	void render_people(std::list<AUS2::Person *> *person_list);
	QPersonInformation *person_information_;
	Ui::Form_person_view ui_;
	AUS2::Controller *controller_;
Q_SIGNALS:
	void test_doubleclicked(QAbstractItemModel * = nullptr);
};

