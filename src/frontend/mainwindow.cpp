#include "mainwindow.h"
#include "../backend/backend.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {

  ui->setupUi(this);
  ui->widget->xAxis->setRange(-10, 10);
  ui->widget->yAxis->setRange(-10, 10);

  x_begin = -10;
  x_end = 10;
  h = (x_end - x_begin)/10000;

  // Цифровые кнопки
  connect(ui->pushButton_0, &QPushButton::clicked, this,
          &MainWindow::digit_buttons);
  connect(ui->pushButton_1, &QPushButton::clicked, this,
          &MainWindow::digit_buttons);
  connect(ui->pushButton_2, &QPushButton::clicked, this,
          &MainWindow::digit_buttons);
  connect(ui->pushButton_3, &QPushButton::clicked, this,
          &MainWindow::digit_buttons);
  connect(ui->pushButton_4, &QPushButton::clicked, this,
          &MainWindow::digit_buttons);
  connect(ui->pushButton_5, &QPushButton::clicked, this,
          &MainWindow::digit_buttons);
  connect(ui->pushButton_6, &QPushButton::clicked, this,
          &MainWindow::digit_buttons);
  connect(ui->pushButton_7, &QPushButton::clicked, this,
          &MainWindow::digit_buttons);
  connect(ui->pushButton_8, &QPushButton::clicked, this,
          &MainWindow::digit_buttons);
  connect(ui->pushButton_9, &QPushButton::clicked, this,
          &MainWindow::digit_buttons);

  // Функциональные кнопки
  connect(ui->pushButton_acos, &QPushButton::clicked, this,
          &MainWindow::on_pushButton_func_clicked);
  connect(ui->pushButton_asin, &QPushButton::clicked, this,
          &MainWindow::on_pushButton_func_clicked);
  connect(ui->pushButton_atan, &QPushButton::clicked, this,
          &MainWindow::on_pushButton_func_clicked);
  connect(ui->pushButton_cos, &QPushButton::clicked, this,
          &MainWindow::on_pushButton_func_clicked);
  connect(ui->pushButton_ln, &QPushButton::clicked, this,
          &MainWindow::on_pushButton_func_clicked);
  connect(ui->pushButton_log, &QPushButton::clicked, this,
          &MainWindow::on_pushButton_func_clicked);
  connect(ui->pushButton_sin, &QPushButton::clicked, this,
          &MainWindow::on_pushButton_func_clicked);
  connect(ui->pushButton_sqrt, &QPushButton::clicked, this,
          &MainWindow::on_pushButton_func_clicked);
  connect(ui->pushButton_tan, &QPushButton::clicked, this,
          &MainWindow::on_pushButton_func_clicked);

  // Операторы
  connect(ui->pushButton_plus, &QPushButton::clicked, this,
          &MainWindow::on_pushButton_plus_minus_clicked);
  connect(ui->pushButton_minus, &QPushButton::clicked, this,
          &MainWindow::on_pushButton_plus_minus_clicked);
  connect(ui->pushButton_mul, &QPushButton::clicked, this,
          &MainWindow::on_pushButton_mul_div_pow_mod_rb_clicked);
  connect(ui->pushButton_div, &QPushButton::clicked, this,
          &MainWindow::on_pushButton_mul_div_pow_mod_rb_clicked);
  connect(ui->pushButton_mod, &QPushButton::clicked, this,
          &MainWindow::on_pushButton_mul_div_pow_mod_rb_clicked);
  connect(ui->pushButton_rb, &QPushButton::clicked, this,
          &MainWindow::on_pushButton_mul_div_pow_mod_rb_clicked);
  connect(ui->pushButton_pow, &QPushButton::clicked, this,
          &MainWindow::on_pushButton_mul_div_pow_mod_rb_clicked);

  // Другие связи
  connect(ui->x_max, &QLineEdit::editingFinished, this,
          &MainWindow::edit_graph_params);
  connect(ui->x_min, &QLineEdit::editingFinished, this,
          &MainWindow::edit_graph_params);
  connect(ui->y_min, &QLineEdit::editingFinished, this,
          &MainWindow::edit_graph_params);
  connect(ui->y_max, &QLineEdit::editingFinished, this,
          &MainWindow::edit_graph_params);
  connect(ui->credit_calc, &QPushButton::clicked, this,
          &MainWindow::calc_credit);
  connect(ui->calc_deposit, &QPushButton::clicked, this,
          &MainWindow::calc_deposit);
  connect(ui->add_money, &QPushButton::clicked, this, &MainWindow::add_money);
  connect(ui->take_money, &QPushButton::clicked, this,
          &MainWindow::add_withdrawal);
  connect(qApp, &QApplication::aboutToQuit, this,
          &MainWindow::on_application_about_to_quit);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_application_about_to_quit() {
  QVBoxLayout *Vbox = ui->verticalLayout;
  QVBoxLayout *Vbox_2 = ui->verticalLayout_2;
  while (Vbox->count() > 0) {
    QLayoutItem *layoutItem = Vbox->takeAt(0);
    QWidget *widget = layoutItem->widget();
    if (widget) {
      QHBoxLayout *HBox = qobject_cast<QHBoxLayout *>(widget->layout());
      if (HBox) {
        remove_HBoxLayout(HBox);
      }
    }
    delete layoutItem;
  }
  while (Vbox_2->count() > 0) {
    QLayoutItem *layoutItem = Vbox_2->takeAt(0);
    QWidget *widget = layoutItem->widget();
    if (widget) {
      QHBoxLayout *HBox = qobject_cast<QHBoxLayout *>(widget->layout());
      if (HBox) {
        remove_HBoxLayout(HBox);
      }
    }
    delete layoutItem;
  }
}

void MainWindow::remove_HBoxLayout(QHBoxLayout *HBox) {
  while (HBox->count() > 0) {
    QLayoutItem *item = HBox->takeAt(0);
    delete item->widget();
    delete item;
  }
  delete HBox;
}

void MainWindow::add_withdrawal() {
  if (ui->withdrawal_sum->text() != "") {

    QRegularExpression regex("^\\d+$");
    bool test_1 = regex.match(ui->withdrawal_sum->text()).hasMatch();
    if (test_1) {
      QVBoxLayout *Vbox = ui->verticalLayout_2;
      QHBoxLayout *HBox = new QHBoxLayout();
      QLineEdit *type = new QLineEdit(ui->withdrawal_type->currentText());
      QDateEdit *dateEdit = new QDateEdit(ui->withdrawal_date->date());
      QLineEdit *sum = new QLineEdit(ui->withdrawal_sum->text());
      QPushButton *button = new QPushButton("удалить");
      type->setEnabled(false);
      dateEdit->setEnabled(false);
      sum->setEnabled(false);
      type->setStyleSheet("color: black;");
      dateEdit->setStyleSheet("color: black;");
      sum->setStyleSheet("color: black;");
      HBox->addWidget(type);
      HBox->addWidget(dateEdit);
      HBox->addWidget(sum);
      HBox->addWidget(button);
      connect(button, &QPushButton::clicked,
              [this, HBox]() { remove_HBoxLayout(HBox); });
      Vbox->addLayout(HBox);
      Vbox->setAlignment(Qt::AlignTop);
    } else {
      ui->label_43->setText("Введены не корректные данные");
      ui->withdrawal_sum->setText("");
    }
  }
}

void MainWindow::add_money() {
  if (ui->sum_to_add->text() != "") {

    QRegularExpression regex("^\\d+$");
    bool test_1 = regex.match(ui->sum_to_add->text()).hasMatch();
    if (test_1) {
      QVBoxLayout *Vbox = ui->verticalLayout;
      QHBoxLayout *HBox = new QHBoxLayout();
      QLineEdit *type = new QLineEdit(ui->type_of_add->currentText());
      QDateEdit *dateEdit = new QDateEdit(ui->date_of_add->date());
      QLineEdit *sum = new QLineEdit(ui->sum_to_add->text());
      QPushButton *button = new QPushButton("удалить");
      type->setEnabled(false);
      dateEdit->setEnabled(false);
      sum->setEnabled(false);
      type->setStyleSheet("color: black;");
      dateEdit->setStyleSheet("color: black;");
      sum->setStyleSheet("color: black;");
      HBox->addWidget(type);
      HBox->addWidget(dateEdit);
      HBox->addWidget(sum);
      HBox->addWidget(button);
      connect(button, &QPushButton::clicked,
              [this, HBox]() { remove_HBoxLayout(HBox); });
      Vbox->addLayout(HBox);
      Vbox->setAlignment(Qt::AlignTop);
    } else {
      ui->label_43->setText("Введены не корректные данные");
      ui->sum_to_add->setText("");
    }
  }
}

QDate MainWindow::get_happy_day(QDate current) {
  QString periodicy = ui->periodicity->currentText();
  if (periodicy == "Каждый день") {
    current = current.addDays(1);
  } else if (periodicy == "Каждую неделю") {
    current = current.addDays(7);
  } else if (periodicy == "Раз в месяц") {
    current = current.addMonths(1);
  } else if (periodicy == "Раз в квартал") {
    current = current.addMonths(3);
  } else if (periodicy == "Раз в полгода") {
    current = current.addMonths(6);
  } else if (periodicy == "Раз в год") {
    current = current.addYears(1);
  }
  return current;
}

double MainWindow::get_additions(QDate current, QString periodicy, QDate date,
                                 char *sum) {
  double result = 0;
  if (date.daysTo(current) >= 0) {
    if (periodicy == "Разовое") {
      if (date.daysTo(current) == 0) {
        result += strtod(sum, NULL);
      }
    } else if (periodicy == "Раз в месяц") {
      while (date.daysTo(current) > 0) {
        date = date.addMonths(1);
      }
      if (date.daysTo(current) == 0) {
        result += strtod(sum, NULL);
      }
    } else if (periodicy == "Раз в 2 месяца") {
      while (date.daysTo(current) > 0) {
        date = date.addMonths(2);
      }
      if (date.daysTo(current) == 0) {
        result += strtod(sum, NULL);
      }
    } else if (periodicy == "Раз в квартал") {
      while (date.daysTo(current) > 0) {
        date = date.addMonths(3);
      }
      if (date.daysTo(current) == 0) {
        result += strtod(sum, NULL);
      }
    } else if (periodicy == "Раз в полгода") {
      while (date.daysTo(current) > 0) {
        date = date.addMonths(6);
      }
      if (date.daysTo(current) == 0) {
        result += strtod(sum, NULL);
      }
    } else if (periodicy == "Раз в год") {
      while (date.daysTo(current) > 0) {
        date = date.addYears(1);
      }
      if (date.daysTo(current) == 0) {
        result += strtod(sum, NULL);
      }
    }
  }
  return result;
}

double MainWindow::get_current_day_withdrowal(QDate current) {
  double result = 0;
  QVBoxLayout *Vbox = ui->verticalLayout_2;
  for (int i = 0; i < Vbox->count(); i++) {
    QHBoxLayout *Hbox = qobject_cast<QHBoxLayout *>(Vbox->itemAt(i)->layout());
    if (Hbox) {
      QLineEdit *type = qobject_cast<QLineEdit *>(Hbox->itemAt(0)->widget());
      QDateEdit *dateEdit =
          qobject_cast<QDateEdit *>(Hbox->itemAt(1)->widget());
      QLineEdit *sum_line =
          qobject_cast<QLineEdit *>(Hbox->itemAt(2)->widget());
      char *sum = sum_line->text().toUtf8().data();
      QString periodicy = type->text();
      QDate date = dateEdit->date();
      result += get_additions(current, periodicy, date, sum);
    }
  }
  return result;
}

double MainWindow::get_current_day_addition(QDate current) {
  double result = 0;
  QVBoxLayout *Vbox = ui->verticalLayout;
  for (int i = 0; i < Vbox->count(); i++) {
    QHBoxLayout *Hbox = qobject_cast<QHBoxLayout *>(Vbox->itemAt(i)->layout());
    if (Hbox) {
      QLineEdit *type = qobject_cast<QLineEdit *>(Hbox->itemAt(0)->widget());
      QDateEdit *dateEdit =
          qobject_cast<QDateEdit *>(Hbox->itemAt(1)->widget());
      QLineEdit *sum_line =
          qobject_cast<QLineEdit *>(Hbox->itemAt(2)->widget());
      char *sum = sum_line->text().toUtf8().data();
      QString periodicy = type->text();
      QDate date = dateEdit->date();
      result += get_additions(current, periodicy, date, sum);
    }
  }
  return result;
}

void MainWindow::calc_deposit() {
  QDate start = ui->dateEdit->date();
  QDate current = start;
  QDate happy_day = get_happy_day(start);
  double duration = strtod(ui->duration_depos->text().toUtf8().data(), NULL);
  QDate end = start.addMonths(duration);
  double sum_depos = strtod(ui->sum_depos->text().toUtf8().data(), NULL);
  double procent = strtod(ui->procent_depos->text().toUtf8().data(), NULL);
  double profit = 0;
  double profit_buffer = 0;
  double tax_procent = 0;
  if (ui->tax->text() != "") {
    tax_procent = strtod(ui->tax->text().toUtf8().data(), NULL);
  }
  double yearly_profit = 0;
  double total_tax = 0;
  while (current.daysTo(end) > 0) {
    sum_depos += get_current_day_addition(current);
    sum_depos -= get_current_day_withdrowal(current);
    current = current.addDays(1);
    int days_in_year = current.daysInYear();
    double day_share = procent / days_in_year;
    profit += sum_depos * day_share / 100;
    yearly_profit += sum_depos * day_share / 100;
    if (current.daysTo(happy_day) == 0) {
      happy_day = get_happy_day(happy_day);
      profit = round(profit * 100) / 100;
      if (ui->checkBox->isChecked()) {
        sum_depos += profit;
        profit_buffer += profit;
        profit = 0;
      }
    }
    if ((current.month() == 12 && current.day() == 31) ||
        current.daysTo(end) == 0) {
      double yearly_taxable_income = yearly_profit - 85000;
      if (yearly_taxable_income > 0) {
        double tax_amount = yearly_taxable_income * tax_procent / 100;
        total_tax += tax_amount;
      }
      yearly_profit = 0;
    }
  }
  if (ui->checkBox->isChecked()) {
    profit = round(profit * 100) / 100;
    sum_depos += profit;
  }
  profit_buffer += profit;
  QRegularExpression regex("^\\d+$");
  bool test_1 = regex.match(ui->duration_depos->text()).hasMatch();
  bool test_2 = regex.match(ui->sum_depos->text()).hasMatch();
  bool test_3 = regex.match(ui->procent_depos->text()).hasMatch();
  if (test_1 && test_2 && test_3) {
    output_data(true, profit_buffer, total_tax, sum_depos);
  } else {
    output_data(false, 0, 0, 0);
  }
}

void MainWindow::output_data(bool is_ok, double profit_buffer, double total_tax,
                             double sum_depos) {
  ui->label_35->setEnabled(is_ok);
  ui->label_37->setEnabled(is_ok);
  ui->label_39->setEnabled(is_ok);
  ui->label_34->setEnabled(is_ok);
  ui->label_36->setEnabled(is_ok);
  ui->label_38->setEnabled(is_ok);
  ui->label_40->setEnabled(is_ok);
  ui->label_41->setEnabled(is_ok);
  ui->label_42->setEnabled(is_ok);
  if (is_ok) {
    ui->label_35->setText(QString::number(profit_buffer, 'f', 2));
    ui->label_37->setText(QString::number(total_tax, 'f', 2));
    ui->label_39->setText(QString::number(sum_depos, 'f', 2));
    ui->label_43->setText("");
  } else {
    ui->label_35->setText("");
    ui->label_37->setText("");
    ui->label_39->setText("");
    ui->label_43->setText("Введены не корректные данные");
  }
}

void MainWindow::setLabelsState(bool enabled) {
  ui->label_13->setEnabled(enabled);
  ui->label_14->setEnabled(enabled);
  ui->label_15->setEnabled(enabled);
  ui->label_16->setEnabled(enabled);
  ui->label_17->setEnabled(enabled);
  ui->label_18->setEnabled(enabled);
  ui->label_19->setEnabled(enabled);
  ui->label_20->setEnabled(enabled);
  ui->label_21->setEnabled(enabled);
  if (enabled == false) {
    ui->label_14->setText("");
    ui->label_17->setText("");
    ui->label_20->setText("");
  }
}

void MainWindow::calculate_differentiated() {
  QString sum = ui->lineEdit_3->text();
  QString duration = ui->lineEdit_4->text();
  QString procent = ui->lineEdit_5->text();
  double duration_d = strtod(duration.toUtf8().data(), NULL);
  double sum_d = strtod(sum.toUtf8().data(), NULL);
  QString expression1 = sum + "/" + duration + "+(" + sum + "-(1-1)*(" + sum +
                        "/" + duration + "))*" + procent + "/100/12";
  QString expression2 = sum + "/" + duration + "+(" + sum + "-(" + duration +
                        "-1)*(" + sum + "/" + duration + "))*" + procent +
                        "/100/12";
  char *result1;
  char *result2;
  int status1 = calculate(expression1.toUtf8().data(), &result1);
  int status2 = calculate(expression2.toUtf8().data(), &result2);
  if (status1 == 0 && status2 == 0) {
    setLabelsState(true);
    double monthly_1 = strtod(result1, NULL);
    double monthly_2 = strtod(result2, NULL);
    QString monthly_range = QString::number(monthly_1, 'f', 2) + "..." +
                            QString::number(monthly_2, 'f', 2);
    ui->label_14->setText(monthly_range);
    double total_pay = 0;
    int status = 0;
    for (int i = 1; i <= duration_d && status == 0; i++) {
      QString expressionI = sum + "/" + duration + "+(" + sum + "-(" +
                            QString::number(i) + "-1)*(" + sum + "/" +
                            duration + "))*" + procent + "/100/12";
      char *result;
      status = calculate(expressionI.toUtf8().data(), &result);
      total_pay += strtod(result, NULL);
    }
    ui->label_20->setText(QString::number(total_pay, 'f', 2));
    ui->label_17->setText(QString::number(total_pay - sum_d, 'f', 2));
    ui->label_22->setText("");
  } else {
    ui->label_22->setText("Введены не корректные данные");
    setLabelsState(false);
  }
}

void MainWindow::calculate_annuity() {
  QString sum = ui->lineEdit_3->text();
  QString duration = ui->lineEdit_4->text();
  QString procent = ui->lineEdit_5->text();
  double duration_d = strtod(duration.toUtf8().data(), NULL);
  double sum_d = strtod(sum.toUtf8().data(), NULL);
  QString expression = "(" + sum + "*" + procent + "/100/12)/(1-(1+" + procent +
                       "/100/12)^-" + duration + ")";
  char *charArray = expression.toUtf8().data();
  char *result;
  int status = calculate(charArray, &result);
  if (status == 0) {
    setLabelsState(true);
    double monthly_d = strtod(result, NULL);
    double over_pay_d =
        round(monthly_d * 100) / 100 * (round(duration_d * 100) / 100) -
        round(sum_d * 100) / 100;
    ui->label_14->setText(QString::number(monthly_d, 'f', 2));
    ui->label_17->setText(QString::number(over_pay_d, 'f', 2));
    ui->label_20->setText(QString::number(over_pay_d + sum_d, 'f', 2));
    ui->label_22->setText("");
  } else {
    ui->label_22->setText("Введены не корректные данные");
    setLabelsState(false);
  }
}

void MainWindow::calc_credit() {
  QString type = ui->comboBox->currentText();
  if (type == "Аннуитетный") {
    calculate_annuity();
  } else if (type == "Дифференцированный") {
    calculate_differentiated();
  } else {
    setLabelsState(false);
  }
}

void MainWindow::edit_graph_params() {
  double x_min = strtod(ui->x_min->text().toUtf8().data(), NULL);
  double x_max = strtod(ui->x_max->text().toUtf8().data(), NULL);
  double y_min = strtod(ui->y_min->text().toUtf8().data(), NULL);
  double y_max = strtod(ui->y_max->text().toUtf8().data(), NULL);
  ui->widget->xAxis->setRange(x_min, x_max);
  ui->widget->yAxis->setRange(y_min, y_max);
  x_begin = x_min;
  x_end = x_max;
  h = (x_end - x_begin)/10000;
}

void MainWindow::digit_buttons() {
  QPushButton *button = (QPushButton *)sender();
  if (ui->lineEdit->text() == "0" || result_shown) {
    ui->lineEdit->setText("");
    result_shown = false;
  }
  if (ui->lineEdit->text().endsWith("X")) {
    ui->lineEdit->setText(ui->lineEdit->text() + "*" + button->text());
  } else {
    ui->lineEdit->setText(ui->lineEdit->text() + button->text());
  }

  MainWindow::prev_operator = "";
  MainWindow::is_error = false;
}

void MainWindow::on_pushButton_AC_clicked() {
  ui->lineEdit->setText("0");
  MainWindow::is_dot_set = false;
  MainWindow::is_x_set = false;
  ui->lineEdit_2->setPlaceholderText("");
  MainWindow::is_error = false;
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_0) {
    ui->pushButton_0->click();
  } else if (event->key() == Qt::Key_1) {
    ui->pushButton_1->click();
  } else if (event->key() == Qt::Key_2) {
    ui->pushButton_2->click();
  } else if (event->key() == Qt::Key_3) {
    ui->pushButton_3->click();
  } else if (event->key() == Qt::Key_4) {
    ui->pushButton_4->click();
  } else if (event->key() == Qt::Key_5) {
    ui->pushButton_5->click();
  } else if (event->key() == Qt::Key_6) {
    ui->pushButton_6->click();
  } else if (event->key() == Qt::Key_7) {
    ui->pushButton_7->click();
  } else if (event->key() == Qt::Key_8) {
    ui->pushButton_8->click();
  } else if (event->key() == Qt::Key_9) {
    ui->pushButton_9->click();
  } else if (event->key() == Qt::Key_Period || event->key() == Qt::Key_Comma) {
    ui->pushButton_dot->click();
  } else if (event->key() == Qt::Key_Plus) {
    ui->pushButton_plus->click();
  } else if (event->key() == Qt::Key_Minus) {
    ui->pushButton_minus->click();
  } else if (event->key() == Qt::Key_Slash) {
    ui->pushButton_div->click();
  } else if (event->key() == Qt::Key_Asterisk) {
    ui->pushButton_mul->click();
  } else if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
    ui->pushButton_result->click();
  } else {
    QMainWindow::keyPressEvent(event);
  }
}

void MainWindow::on_pushButton_dot_clicked() {
  if (MainWindow::is_dot_set == false) {
    QPushButton *button = (QPushButton *)sender();
    ui->lineEdit->setText(ui->lineEdit->text() + button->text());
    MainWindow::is_dot_set = true;
  }
  MainWindow::is_error = false;
}

void MainWindow::on_pushButton_plus_minus_clicked() {
  if (ui->lineEdit->text() == "0") {
    ui->lineEdit->setText("");
  }
    QPushButton *button = (QPushButton *)sender();
    ui->lineEdit->setText(ui->lineEdit->text() + button->text());
    MainWindow::prev_operator = button->text();
    MainWindow::is_dot_set = false;
    MainWindow::result_shown = false;
  
  MainWindow::is_error = false;
}

void MainWindow::on_pushButton_mul_div_pow_mod_rb_clicked() {
  if (MainWindow::is_error == false) {
    QPushButton *button = (QPushButton *)sender();
    ui->lineEdit->setText(ui->lineEdit->text() + button->text());
    MainWindow::prev_operator = button->text();
    MainWindow::is_dot_set = false;
    MainWindow::result_shown = false;
    MainWindow::is_error = false;
  }
}

void MainWindow::on_pushButton_func_clicked() {
  QPushButton *button = (QPushButton *)sender();
  if (is_error) {
    ui->lineEdit->setText("");
  }
  if (ui->lineEdit->text() == "0") {
    ui->lineEdit->setText(button->text() + "(");
  } else if (MainWindow::result_shown) {
    ui->lineEdit->setText(button->text() + "(" + ui->lineEdit->text());
  } else if (MainWindow::prev_operator == "" ||
             MainWindow::prev_operator == "x" ||
             MainWindow::prev_operator == ")") {
    ui->lineEdit->setText(ui->lineEdit->text() + "*" + button->text() + "(");
  } else {
    ui->lineEdit->setText(ui->lineEdit->text() + button->text() + "(");
  }
  MainWindow::prev_operator = "(";
  MainWindow::is_dot_set = false;
  MainWindow::result_shown = false;
  MainWindow::is_error = false;
}

void MainWindow::on_pushButton_lb_clicked() {
  if (ui->lineEdit->text() == "0" || is_error) {
    ui->lineEdit->setText("");
  } else if (MainWindow::prev_operator == "" ||
             MainWindow::prev_operator == "x") {
    ui->lineEdit->setText(ui->lineEdit->text() + "*");
  }
  QPushButton *button = (QPushButton *)sender();
  ui->lineEdit->setText(ui->lineEdit->text() + button->text());
  MainWindow::prev_operator = "(";
  MainWindow::is_dot_set = false;
  MainWindow::result_shown = false;
  MainWindow::is_error = false;
}

void MainWindow::on_pushButton_x_clicked() {
  if (ui->lineEdit->text() == "0" || result_shown || is_error) {
    ui->lineEdit->setText("");
    result_shown = false;
  } else if (MainWindow::prev_operator == "") {
    ui->lineEdit->setText(ui->lineEdit->text() + "*");
  }
  QPushButton *button = (QPushButton *)sender();
  ui->lineEdit->setText(ui->lineEdit->text() + button->text());
  ui->lineEdit_2->setPlaceholderText("Введите X");
  MainWindow::prev_operator = "";
  MainWindow::is_dot_set = false;
  MainWindow::is_x_set = true;
  MainWindow::is_error = false;
}

void MainWindow::on_pushButton_result_clicked() {
  if (MainWindow::is_x_set == true && ui->lineEdit_2->text().isEmpty()) {
    // Очистка данных графика
    clearGraphData();
    // Настройка параметров графика
    edit_graph_params();
    // Расчет и добавление данных графика
    calculateAndAddGraphData();
    // Отображение графика
    showGraph();
  } else {
    // Расчет и отображение результата
    calculateAndShowResult();
    // Сброс стилей и текста ввода
    resetLineEdit();
    // Сброс флагов и текста ввода
    resetFlagsAndPlaceholderText();
  }
}

void MainWindow::clearGraphData() {
  x.clear();
  y.clear();
  ui->widget->clearGraphs();
}

void MainWindow::calculateAndAddGraphData() {
  for (X = x_begin; X < x_end; X += h) {
    QString str = ui->lineEdit->text();
    str.replace(QRegularExpression("X"), QString::number(X));
    QByteArray byteArray = str.toUtf8();
    char *charArray = byteArray.data();
    char *result;
    int status = calculate(charArray, &result);
    if (status == 0) {
      double y_min = strtod(ui->y_min->text().toUtf8().data(), NULL);
      double y_max = strtod(ui->y_max->text().toUtf8().data(), NULL);
      double resultValue = strtod(result, nullptr);
      if (resultValue <= y_max && resultValue >= y_min)
        y.push_back(resultValue);
      else
        y.push_back(qQNaN());
      x.push_back(X);
    } else {
      y.push_back(qQNaN());
      x.push_back(X);
    }
  }
  ui->widget->addGraph();
  ui->widget->graph(0)->addData(x, y);
}

void MainWindow::showGraph() { ui->widget->replot(); }

void MainWindow::resetLineEdit() {
  ui->lineEdit_2->setStyleSheet("");
  QString str = ui->lineEdit->text();
  if (MainWindow::is_x_set == true) {
    str.replace(QRegularExpression("X"), ui->lineEdit_2->text());
  }
  ui->lineEdit_2->setText("");
}

void MainWindow::calculateAndShowResult() {
  QString str = ui->lineEdit->text();
  if (MainWindow::is_x_set == true) {
    str.replace(QRegularExpression("X"), ui->lineEdit_2->text());
  }
  ui->lineEdit_2->setText("");
  QByteArray byteArray = str.toUtf8();
  char *charArray = byteArray.data();
  char *result;
  int status = calculate(charArray, &result);
  if (status != 0) {
    MainWindow::is_error = true;
  }
  ui->lineEdit->setText(result);
}

void MainWindow::resetFlagsAndPlaceholderText() {
  MainWindow::result_shown = true;
  MainWindow::is_x_set = false;
  MainWindow::prev_operator = "";
  ui->lineEdit_2->setPlaceholderText("");
}
