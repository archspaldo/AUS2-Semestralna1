#pragma once
#include <QDialog>
#include "Controller.h"
#include "ui_QT_generator.h"

class QGeneratorDialog : public QDialog
{
public:
	explicit QGeneratorDialog(QWidget *parent = nullptr, AUS2::Controller *controller = nullptr);
	~QGeneratorDialog();
private Q_SLOTS:
	virtual void accept() override;
private:
	Ui::Dialog_generator ui_;
	AUS2::Controller *controller_;
};

