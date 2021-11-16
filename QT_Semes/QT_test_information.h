#pragma once
#include <QtWidgets/qwidget.h>
#include "ui_QT_test_information.h"
#include "Controller.h"

class QTestInformation : public QWidget
{
	Q_OBJECT;
public:
	explicit QTestInformation(QWidget *parent = nullptr, AUS2::Controller *controller = nullptr);
	~QTestInformation();
	void reset();
	void render_test(QString uuid);
private Q_SLOTS:
	void on_remove_test_button_clicked();
private:
	Ui::Form_test_information ui_;
	AUS2::Controller *controller_;
	AUS2::Test *rendered_test_;
};

