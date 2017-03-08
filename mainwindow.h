#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <exception>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    int grade() const{
        int totalPercent = 0;

        //section for adding HW together and adding to raw percent
        std::vector<int> HWScores = { HW1TextEdit.getText(), HW2TextEdit.getText(),
                                      HW3TextEdit.getText(), HW4TextEdit.getText(),
                                      HW5TextEdit.getText(), HW6TextEdit.getText(),
                                      HW7TextEdit.getText(), HW8TextEdit.getText() };

       double totalHWPer = HWScores[0];
       int lowestScore = HWScores[0];
       //equals 1 if the grading scheme is using 8 HW
       int sevenOrEight = 0;

       if(HWradioButton.checked())
           ++sevenOrEight;

       for(int j = 1; j < HWScores.size(); ++j){
           totalHWPer += HWScores[j];

           if(HWScores[j] < HWScore[j - 1])
               lowestScore = HWScores[j];
       }

       totalHWPer -= lowestScore;
       totalHWPer /= (sevenOrEight ? 7 : 6);
       totalPercent += 25 *(totalHWPer / 100);

       //now for midterms
       std::vector<int> MTScores = { MT1TextEdit.getText(), MT2TextEdit.getText() };
       //collect lowest midterm, and the sum of them
       int lowestMT = ((MTScores[0] < MTScores[1]) ? MTScores[0] : MTScores[1]);
       double totalMTScores = MTScores[0] + MTScores[1];

       //add MT scores to the grade
       //might as well add final grade in
       if(SchemeChoiceradioButton_1.checked() && !SchemeChoiceradioButton_2.checked()){
           totalPercent += 40 * ((totalMTScores / 2) / 100);
           totalPercent += 35 * (FinalTextEdit.getText() / 100);
       }

       else if(!SchemeChoiceradioButton_1.checked() && SchemeChoiceradioButton_2.checked()){
           totalMTScores -= lowestMT;
           totalPercent += 30 * (totalMTScores / 100);
           totalPercent += 45 * (FinalTextEdit.getText() / 100);
       }

       //if this else gets triggered, incorrect inputs were made
       else{
           throw std::exception("Incorrect grade inputs.");
       }

       return totalPercent;
    }
    //end of Grade() function

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
