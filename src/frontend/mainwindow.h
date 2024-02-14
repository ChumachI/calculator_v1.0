#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRegularExpression>
#include <QVector>
#include <QKeyEvent>
#include <QDate>
#include <QHBoxLayout>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT



public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
        void digit_buttons();

        void on_pushButton_AC_clicked();

        void on_pushButton_dot_clicked();

        void on_pushButton_plus_minus_clicked();

        void on_pushButton_mul_div_pow_mod_rb_clicked();

        void on_pushButton_lb_clicked();

        void on_pushButton_x_clicked();

        void on_pushButton_result_clicked();

        void on_pushButton_func_clicked();

        void edit_graph_params();

        void clearGraphData();

        void calculateAndAddGraphData();

        void showGraph();

        void resetLineEdit();

        void calculateAndShowResult();

        void resetFlagsAndPlaceholderText();

        void calc_credit();

        void setLabelsState(bool enabled);

        void calculate_annuity();

        void calculate_differentiated();

        void calc_deposit();

        QDate get_happy_day(QDate current);

        void add_money();

        double get_current_day_addition(QDate current);

        double get_current_day_withdrowal(QDate current);

        void remove_HBoxLayout(QHBoxLayout *HBox);

        double get_additions(QDate current, QString periodicy, QDate date, char * sum);

        void output_data(bool is_ok, double profit_buffer, double total_tax,
                             double sum_depos);

        void add_withdrawal();

        void on_application_about_to_quit();


private:
    Ui::MainWindow *ui;
    bool is_dot_set = false;
    bool is_x_set = false;
    bool result_shown = false;
    bool is_error = false;
    QString prev_operator = "";
    double x_begin, x_end, h, X;
    int N;
    QVector<double> x,y;


protected:
    void keyPressEvent(QKeyEvent *event);
};
#endif // MAINWINDOW_H
