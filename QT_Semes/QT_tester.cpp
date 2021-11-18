#include "QT_tester.h"

QTester::QTester(QWidget *parent) :
	QDialog(parent), tester_(new AUS2::Tester()) {
	this->ui_.setupUi(this);
	
	this->lineEdit_2_ = new QLineEdit(this);
	this->lineEdit_2_->setObjectName("lineEdit");
	this->lineEdit_2_->setVisible(false);
	this->ui_.gridLayout->addWidget(this->lineEdit_2_, 5, 0, 1, 2);

	connect(this->ui_.pushButton, &QPushButton::clicked, this, &QTester::on_start_test);
}

QTester::~QTester() {
	delete this->tester_;
	delete this->ui_.tableView->model();
	this->lineEdit_2_;
}

void QTester::on_start_test() {
	QStandardItemModel *model = new QStandardItemModel();
	model->setColumnCount(2);
	model->setHorizontalHeaderLabels(QStringList({ QString::fromWCharArray(L"Vykonaná operácia"), QString::fromWCharArray(L"Výsledok") }));
	this->ui_.tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	this->ui_.tableView->horizontalHeader()->setStretchLastSection(true);

	this->tester_->reset();
	this->tester_->set(this->ui_.spinBox->value(), this->ui_.spinBox_2->value(), this->ui_.spinBox_4->value(), this->ui_.spinBox_3->value(), this->ui_.spinBox_4->value());
	std::string str;
	QStandardItem *item;
	bool res;
	while (this->tester_->has_next()) {
		res = this->tester_->next(str);	
		model->appendRow({ new QStandardItem(QString::fromStdString(str)),  new QStandardItem(QString::number(res)) });
	}
	delete this->ui_.tableView->model();
	this->ui_.tableView->setModel(model);
}