#include <QString>
#include <QDate>
#include <QMessageBox>
#include <array>
#include "MainWindow.h"

MainWindow::MainWindow(QMainWindow* parent)
    : QMainWindow(parent), ui{std::make_unique<Ui::MainWindow>()}
{
    ui->setupUi(this);
}

void MainWindow::callback_calculate()
{
    // Data structures to calculate score. array[index] = points.
    static const std::array<int,8> temp_score {4, 3, 2, 1, 0, 1, 3, 4};
    static const std::array<int,6> pa_score   {4, 2, 0, 2, 3, 4};
    static const std::array<int,7> fc_score   {4, 3, 2, 0, 2, 3, 4};
    static const std::array<int,7> fr_score   {4, 2, 1, 0, 1, 3, 4};
    static const std::array<int,7> pao2_score {4, 3, 1, 0, 2, 3, 4};
    static const std::array<int,7> ph_score   {4, 3, 2, 0, 1, 3, 4};
    static const std::array<int,8> na_score   {4, 3, 2, 0, 1, 2, 3, 4};
    static const std::array<int,7> k_score    {4, 2, 1, 0, 1, 3, 4};
    static const std::array<int,8> cr_score   {2, 0, 2, 4, 3, 6, 4, 8};
    static const std::array<int,6> ht_score   {4, 2, 0, 1, 2, 4};
    static const std::array<int,6> leuc_score {4, 2, 0, 1, 2, 4};
    
    // Data structures for mortality
    static const std::array<int,8> mort_non_op {4, 8, 15, 24, 40, 55, 73, 85};
    static const std::array<int,8> mort_op     {1, 3, 7,  12, 30, 35, 73, 88};
    
    
    // Calculate result
    int result = 0;
    result += temp_score[ui->temp_field->currentIndex()];
    result += pa_score[ui->pa_field->currentIndex()];
    result += fc_score[ui->fc_field->currentIndex()];
    result += fr_score[ui->fr_field->currentIndex()];
    result += pao2_score[ui->po2_field->currentIndex()];
    result += ph_score[ui->ph_field->currentIndex()];
    result += na_score[ui->na_field->currentIndex()];
    result += k_score[ui->k_field->currentIndex()];
    result += cr_score[ui->cr_field->currentIndex()];
    result += ht_score[ui->ht_field->currentIndex()];
    result += leuc_score[ui->leuc_field->currentIndex()];
    result += (15 - ui->glasgow_field->currentText().toInt());
    
    bool op_flag = false;
    if (ui->none_button->isChecked()) {
        result += 0;
    }
    else {
        if (ui->non_cir_button->isChecked()) {
            result += 5;
        }
        else {
            op_flag = true;
            if (ui->cir_emerg_button->isChecked()) {
                result += 5;
            }
            else {
                if (ui->cir_elec_button->isChecked()) {
                    result += 2;
                }
            }
        }
    }
    
    // Check date
    auto today = QDate::currentDate();
    auto birth = ui->dateEdit->date();
    auto days = birth.daysTo(today);
    auto years = static_cast<int>(days / 365.25);
    ui->age_label->setText("Age: " + QString::number(years));
    
    if (years >= 75) {
        result += 6;
    }
    else if (years >= 65 && years <= 74) {
        result += 5;
    }
    else if (years >= 55 && years <= 64) {
        result += 3;
    }
    else if (years >= 45 && years <= 54) {
        result += 2;
    }
    
    QString msg = "Result: " + QString::number(result);
    msg += "       Mortality: ";
    
    if (result >= 35) {
        msg += op_flag ? QString::number(mort_op[7]) : QString::number(mort_non_op[7]);
    }
    else if (result >= 30 && result <= 34) {
        msg += op_flag ? QString::number(mort_op[6]) : QString::number(mort_non_op[6]);
    }
    else if (result >= 25 && result <= 29) {
        msg += op_flag ? QString::number(mort_op[5]) : QString::number(mort_non_op[5]);
    }
    else if (result >= 20 && result <= 24) {
        msg += op_flag ? QString::number(mort_op[4]) : QString::number(mort_non_op[4]);
    }
    else if (result >= 15 && result <= 19) {
        msg += op_flag ? QString::number(mort_op[3]) : QString::number(mort_non_op[3]);
    }
    else if (result >= 10 && result <= 14) {
        msg += op_flag ? QString::number(mort_op[2]) : QString::number(mort_non_op[2]);
    }
    else if (result >= 5 && result <= 9) {
        msg += op_flag ? QString::number(mort_op[1]) : QString::number(mort_non_op[1]);
    }
    else {
        msg += op_flag ? QString::number(mort_op[0]) : QString::number(mort_non_op[0]);
    }
    msg += "%";
    ui->result_label->setText(msg);
}

void MainWindow::about()
{
    QMessageBox::information(this, "About",
"Apache II (Acute Physiology and Chronic Health disease Classification System II)\n\n version 0.1\n\nAuthor: Fernando B. Giannasi\nJan/2018\n\nAPACHE II (\"Acute Physiology And Chronic Health Evaluation II\") is a severity-of-disease classification system (Knaus et al., 1985), one of several ICU scoring systems. It is applied within 24 hours of admission of a patient to an intensive care unit (ICU): an integer score from 0 to 71 is computed based on several measurements; higher scores correspond to more severe disease and a higher risk of death. The first APACHE model was presented by Knaus et al. in 1981. source: Wikipedia");
}

void MainWindow::mortality()
{
    static QString msg = "0-4 points: 4% non op/ 1% post-op\n5-9 points: 8% non op/ 3% post-op\n10-14 points: 15% non op/ 7% post-op\n15-19 points: 24% non op/ 12% post-op\n20-24 points: 40% non op/ 30% post-op\n25-29 points: 55% non op/ 35% post-op\n30-34 points: 73% gen. mortality\n35-100 points: 85% non op/ 88% post-op";   
    QMessageBox::information(this, "Mortality", msg);
                             
}

void MainWindow::blank()
{
    QDate base (1980, 1, 1);
    ui->dateEdit->setDate(base);
    ui->temp_field->setCurrentIndex(4);
    ui->pa_field->setCurrentIndex(2);
    ui->fc_field->setCurrentIndex(3);
    ui->fr_field->setCurrentIndex(3);
    ui->po2_field->setCurrentIndex(3);
    ui->ph_field->setCurrentIndex(3);
    ui->na_field->setCurrentIndex(3);
    ui->k_field->setCurrentIndex(3);
    ui->cr_field->setCurrentIndex(1);
    ui->ht_field->setCurrentIndex(2);
    ui->leuc_field->setCurrentIndex(2);
    ui->glasgow_field->setCurrentIndex(12);
    ui->none_button->click();
}