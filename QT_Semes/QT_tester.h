#pragma once
#include <QDialog>
#include <QtWidgets/qlineedit.h>
#include <QStandardItemModel>
#include "StructureTester.h"
#include "ui_QT_tester.h"

class QTester : public QDialog
{
public:
	explicit QTester(QWidget *parent = nullptr);
	~QTester();
private Q_SLOTS:
	void on_start_test();
private:
	Ui::Dialog_tester ui_;
	AUS2::Tester *tester_;
	QLineEdit *lineEdit_2_;
};

