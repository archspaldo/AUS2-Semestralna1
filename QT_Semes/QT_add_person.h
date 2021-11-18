#pragma once
#include <QDialog>
#include "Controller.h"
#include "ui_QT_add_person.h"

class QAddPerson : public QDialog
{
public:
	explicit QAddPerson(QWidget *parent = nullptr ,AUS2::Controller *controller = nullptr);
	~QAddPerson();
private Q_SLOTS:
	virtual void accept() override;
private:
	Ui::Dialog_add_person ui_;
	AUS2::Controller *controller_;
	QLineEdit *lineEdit_4_;
};