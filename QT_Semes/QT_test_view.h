#pragma once
#include <QtWidgets/qwidget.h>
#include <QStandardItemModel>
#include <list>
#include "ui_QT_test_view.h"
#include "QT_test_information.h"

class QTestView : public QWidget
{
	Q_OBJECT;
public:
	explicit QTestView(QWidget *parent = nullptr, AUS2::Controller *controller = nullptr);
	~QTestView();
	void set_model(QAbstractItemModel *item_model);

	QTestInformation *test_information_;
private Q_SLOTS:
	void on_filter_button_clicked();
	void on_reset_button_clicked();
	void on_test_clicked();
private:
	void render_tests(std::list<AUS2::Test *> *test_list);
	Ui::Form_test_view ui_;
	AUS2::Controller *controller_;
};

