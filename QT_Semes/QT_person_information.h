#pragma once
#include <QtWidgets/qwidget.h>
#include <QStandardItemModel>
#include "ui_QT_person_information.h"
#include "Controller.h"

class QPersonInformation : public QWidget
{
	Q_OBJECT;
public:
	explicit QPersonInformation(QWidget *parent = nullptr, AUS2::Controller *controller = nullptr);
	~QPersonInformation();
	void reset();
	void render_person(QString id);
private Q_SLOTS:
	void on_remove_person_button_clicked();
	void on_person_doubleclicked();
private:
	Ui::Form_person_information ui_;
	AUS2::Controller *controller_;
	AUS2::Person *rendered_person_;
Q_SIGNALS:
	void test_doubleclicked(QAbstractItemModel * = nullptr);
	void person_removed();
};

