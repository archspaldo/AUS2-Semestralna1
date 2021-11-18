#pragma once
#include <QDialog>
#include "Controller.h"
#include "ui_QT_add_test.h"

class QAddTestDialog : public QDialog
{
public:
	explicit QAddTestDialog(QWidget *parent = nullptr, AUS2::Controller *controller = nullptr);
	~QAddTestDialog();
private Q_SLOTS:
	virtual void accept() override;
private:
	Ui::Dialog_add_test ui_;
	AUS2::Controller *controller_;
	QLineEdit *lineEdit_4_;
};

