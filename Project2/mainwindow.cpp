#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    window()->setStyleSheet("background: url(:/resource/background.jpg) repeat cover");
    window()->setFixedSize(900, 600);
    bgplayer.setMedia(QMediaContent(QUrl("qrc:/resource/music/bgm.mp3")));
    bgplayer.play();

    player[0].setMedia(QMediaContent(QUrl("qrc:/resource/music/1.mp3")));
    player[1].setMedia(QMediaContent(QUrl("qrc:/resource/music/2.mp3")));
    player[2].setMedia(QMediaContent(QUrl("qrc:/resource/music/3.mp3")));
    player[3].setMedia(QMediaContent(QUrl("qrc:/resource/music/4.mp3")));
    player[4].setMedia(QMediaContent(QUrl("qrc:/resource/music/5.mp3")));
    player[5].setMedia(QMediaContent(QUrl("qrc:/resource/music/6.mp3")));
    player[6].setMedia(QMediaContent(QUrl("qrc:/resource/music/7.mp3")));
    player[7].setMedia(QMediaContent(QUrl("qrc:/resource/music/8.mp3")));
    player[8].setMedia(QMediaContent(QUrl("qrc:/resource/music/9.mp3")));


    CreateMap();
    CreateObject();
    Restart();

    connect(Button_Ge_H, SIGNAL(clicked()), this, SLOT(Button_Ge_H_pressed()));
    connect(Button_Ge_N, SIGNAL(clicked()), this, SLOT(Button_Ge_N_pressed()));
    connect(Button_Ge_E, SIGNAL(clicked()), this, SLOT(Button_Ge_E_pressed()));
    connect(Button_Cus, SIGNAL(clicked()), this, SLOT(Button_Cus_pressed()));
    connect(Button_Start, SIGNAL(clicked()), this, SLOT(Button_Start_pressed()));

    connect(Button_ReStart, SIGNAL(clicked()), this, SLOT(Button_ReStart_pressed()));

    connect(Button_Ans, SIGNAL(clicked()), this, SLOT(Button_Ans_pressed()));
    connect(Button_Che, SIGNAL(clicked()), this, SLOT(Button_Che_pressed()));

}

MainWindow::~MainWindow()
{
    delete ui;
}
bool MainWindow::check_Unity(int *number){
    int counter[9] = {0};
    for(int i=0; i<9; ++i)
        ++counter[number[i]-1];
    for(int i=0; i<9; ++i)
        if(counter[i] > 1)
            return false;
    return true;
}
bool MainWindow::check_Que(){
    int numbers[9], cell;
    bool result;
    for(int i=0; i<81; i+=9){ // check rows
        for(int j=0; j<9; ++j)
            numbers[j] = Map[i+j]->text().toInt();
        result = check_Unity(numbers);
        if(result == false)
            return false;
    }
    for(int i=0; i<9; ++i){ // check columns
        for(int j=0; j<9; ++j)
            numbers[j] = Map[i+9*j]->text().toInt();
        result = check_Unity(numbers);
        if(result == false)
            return false;
    }
    for(int i=0; i<9; ++i){ // check cells
        for(int j=0; j<9; ++j){
            cell = 27*(i/3) + 3*(i%3) + 9*(j/3) + (j%3);
            numbers[j] = Map[cell]->text().toInt();
        }
        result = check_Unity(numbers);
        if(result == false)
            return false;
    }
    return true;
}
void MainWindow::Button_ReStart_pressed(){
    Restart();
    qDebug() << "Restart";
    Button_Ge_H->show();
    Button_Ge_N->show();
    Button_Ge_E->show();
    Button_Cus->show();
    Button_Start->show();
    Button_Ans->hide();
    Button_Che->hide();
    disconnect(this, SIGNAL(change_Num(int, int)), this, SLOT(change_Num_Slot(int, int)));
    Label->setText("Welcome To Play My Game ^^");

}
void MainWindow::Button_Start_pressed(){
    if(check_Que() == true){
        saveMap();
        Button_Ge_H->hide();
        Button_Ge_N->hide();
        Button_Ge_E->hide();
        Button_Cus->hide();
        Button_Start->hide();
        Button_Ans->show();
        Button_Che->show();
        TimerStart();

        for(int i=0; i<Sudoku::sudokuSize; ++i){
            if(Map[i]->text() == "")
                continue;
            Que_Map[i] = true;
            Map[i]->setStyleSheet("background: white; color: darkCyan; font-size: 24px; font-weight: bold");
        }
        for(int i=0; i<Sudoku::sudokuSize; ++i){
            connect(Map[i], SIGNAL(clicked()), signalMapper, SLOT(map()));
            signalMapper->setMapping(Map[i], i);
        }
        connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(Button_Map_pressed(int)));

        connect(this, SIGNAL(change_Num(int, int)), this, SLOT(change_Num_Slot(int, int)));

        Label->setText("Be Patient  !!  Be Careful  !! ");
        for(int i=0; i<27; i+=9)    // set cell background
            for(int j=0; j<3; ++j){
                if(Map[i+j]->text() == "")
                    Map[i+j]->setStyleSheet("background: lightgray; color: black; font-size: 24px; font-weight: bold");
                else
                    Map[i+j]->setStyleSheet("background: lightgray; color: darkCyan; font-size: 24px; font-weight: bold");
            }
        for(int i=0; i<27; i+=9)
            for(int j=6; j<9; ++j)
                if(Map[i+j]->text() == "")
                    Map[i+j]->setStyleSheet("background: lightgray; color: black; font-size: 24px; font-weight: bold");
                else
                    Map[i+j]->setStyleSheet("background: lightgray; color: darkCyan; font-size: 24px; font-weight: bold");
        for(int i=0; i<27; i+=9)
            for(int j=30; j<33; ++j)
                if(Map[i+j]->text() == "")
                    Map[i+j]->setStyleSheet("background: lightgray; color: black; font-size: 24px; font-weight: bold");
                else
                    Map[i+j]->setStyleSheet("background: lightgray; color: darkCyan; font-size: 24px; font-weight: bold");
        for(int i=0; i<27; i+=9)
            for(int j=54; j<57; ++j)
                if(Map[i+j]->text() == "")
                    Map[i+j]->setStyleSheet("background: lightgray; color: black; font-size: 24px; font-weight: bold");
                else
                    Map[i+j]->setStyleSheet("background: lightgray; color: darkCyan; font-size: 24px; font-weight: bold");
        for(int i=0; i<27; i+=9)
            for(int j=60; j<63; ++j)
                if(Map[i+j]->text() == "")
                    Map[i+j]->setStyleSheet("background: lightgray; color: black; font-size: 24px; font-weight: bold");
                else
                    Map[i+j]->setStyleSheet("background: lightgray; color: darkCyan; font-size: 24px; font-weight: bold");



    }
    else{
        Label->setText("Your puzzle is wrong !!!");
    }
}

void MainWindow::Button_Che_pressed(){
    Sudoku check;
    for(int i=0; i<Sudoku::sudokuSize; ++i){
        QString qstr =  Map[i]->text();
        int value;

        value = qstr.toInt();
        check.setNumber(i, value);
    }
    if(check.check_answer()){
        Label->setText("Correct !!!");
        disconnect(Timer, SIGNAL(timeout()), this, SLOT(showTime()));
    }
    else
        Label->setText("Wrong !!!");
}

void MainWindow::change_Num_Slot(int index, int num){
    QString qstr;
    if(num != 0)
        qstr = QString::number(num);
    else
        qstr = "";
    Map[index]->setText(qstr);
    player[num-1].play();
}
void MainWindow::keyPressEvent(QKeyEvent *input){
    if(input->key() == Qt::Key_1 && Que_Map[Position] == false)
        emit change_Num(Position, 1);
    else if(input->key() == Qt::Key_2 && Que_Map[Position] == false)
        emit change_Num(Position, 2);
    else if(input->key() == Qt::Key_3 && Que_Map[Position] == false)
        emit change_Num(Position, 3);
    else if(input->key() == Qt::Key_4 && Que_Map[Position] == false)
        emit change_Num(Position, 4);
    else if(input->key() == Qt::Key_5 && Que_Map[Position] == false)
        emit change_Num(Position, 5);
    else if(input->key() == Qt::Key_6 && Que_Map[Position] == false)
        emit change_Num(Position, 6);
    else if(input->key() == Qt::Key_7 && Que_Map[Position] == false)
        emit change_Num(Position, 7);
    else if(input->key() == Qt::Key_8 && Que_Map[Position] == false)
        emit change_Num(Position, 8);
    else if(input->key() == Qt::Key_9 && Que_Map[Position] == false)
        emit change_Num(Position, 9);
    else if(Que_Map[Position] == false)
        emit change_Num(Position, 0);
}


void MainWindow::Button_Map_pressed(int pos){
    Position = pos;
    qDebug() << Position;
}
void MainWindow::saveMap(){
    for(int i=0; i<Sudoku::sudokuSize; ++i){
        QString qstr =  Map[i]->text();
        int value;

        value = qstr.toInt();
        que.setNumber(i, value);
    }
}
void MainWindow::Button_Ans_pressed(){
    disconnect(Timer, SIGNAL(timeout()), this, SLOT(showTime()));
    if(solve_Puzzle(que, ans) == true) // solve puzzle
        Label->setText("Solvable !!!");
    else
        Label->setText("Unsolvable !!!");
    for(int i=0; i<Sudoku::sudokuSize; ++i){
        QString qstr = QString::number(ans.getNumber(i));
        Map[i]->setText(qstr);
    }
}
bool MainWindow::solve_Puzzle(Sudoku que, Sudoku & ans){
    int firstZero;
    int final_ans[Sudoku::sudokuSize];
    firstZero = que.getZeros_index();
    que.setPossibles(firstZero);

    if(firstZero == -1){
        if(que.check_answer()){
            for(int i=0; i<Sudoku::sudokuSize; ++i){
                final_ans[i] =  que.getNumber(i);
                ans.setMap(final_ans);
            }
            return true;
        }
        else
            return false;
    }
    else{
        for(int i=0; i<que.poss_num; ++i){
            que.setNumber(firstZero, que.chooses[i]);
            if(solve_Puzzle(que, ans))
                return true;
        }

        return false;
    }

}
void MainWindow::Button_Cus_pressed(){
    Restart();

    for(int i=0; i<Sudoku::sudokuSize; ++i){
        connect(Map[i], SIGNAL(clicked()), signalMapper, SLOT(map()));
        signalMapper->setMapping(Map[i], i);
    }
    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(Button_Map_pressed(int)));
    connect(this, SIGNAL(change_Num(int, int)), this, SLOT(change_Num_Slot(int, int)));
    qDebug() << "Custom";
    Label->setText("Please input a reasonable puzzle !!!");
}
void MainWindow::Button_Ge_H_pressed(){
    Restart();
    disconnect(this, SIGNAL(change_Num(int, int)), this, SLOT(change_Num_Slot(int, int)));
    qDebug() << "Hard";
    ge.setModel(70);
    for(int i=0; i<Sudoku::sudokuSize; ++i){
        QString qstr = QString::number(ge.getMap(i));
        if(qstr == '0')
            continue;
        Que_Map[i] = true;
        Map[i]->setText(qstr);
        Map[i]->setStyleSheet("background: white; font-size: 24px; font-weight: bold");
    }
    Label->setText("This is suitable for a Master !!");
    setBackground();
}
void MainWindow::Button_Ge_N_pressed(){
    Restart();
    disconnect(this, SIGNAL(change_Num(int, int)), this, SLOT(change_Num_Slot(int, int)));
    qDebug() << "Normal";
    ge.setModel(50);
    for(int i=0; i<Sudoku::sudokuSize; ++i){
        QString qstr = QString::number(ge.getMap(i));
        if(qstr == '0')
            continue;
        Que_Map[i] = true;
        Map[i]->setText(qstr);
        Map[i]->setStyleSheet("background: white; font-size: 24px; font-weight: bold");
    }
    Label->setText("This is suitable for a Challenger !!");
    setBackground();
}
void MainWindow::Button_Ge_E_pressed(){
    Restart();
    disconnect(this, SIGNAL(change_Num(int, int)), this, SLOT(change_Num_Slot(int, int)));
    qDebug() << "Easy";
    ge.setModel(25);
    for(int i=0; i<Sudoku::sudokuSize; ++i){
        QString qstr = QString::number(ge.getMap(i));
        if(qstr == '0')
            continue;
        Que_Map[i] = true;
        Map[i]->setText(qstr);
        Map[i]->setStyleSheet("background: white; font-size: 24px; font-weight: bold");
    }
    Label->setText("This is suitable for a Rookie !!");
    setBackground();
}
void MainWindow::CreateMap(){
    int x=50;
    int y=50;
    for(int i=0; i<Sudoku::sudokuSize; ++i){
        Map[i] = new QPushButton(this);
        Map[i]->setGeometry(x+50*(i%9), y, 50, 50);
        if(i%9 == 8)
            y+=50;
    }
}

void MainWindow::CreateObject(){
    Button_Ge_H = new QPushButton("Hard Puzzle", this);
    Button_Ge_N = new QPushButton("Normal Puzzle", this);
    Button_Ge_E = new QPushButton("Easy Puzzle", this);
    Button_Cus = new QPushButton("Custom Puzzle", this);
    Button_Ans = new QPushButton("Solve Puzzle", this);
    Button_Che = new QPushButton("Check Answer", this);
    Button_Start = new QPushButton("Start Game", this);
    Button_ReStart = new QPushButton("Restart Game", this);
    Label = new QLabel("Welcome To Play My Game ^^", this);
    LCD = new QLCDNumber(this);
    Timer = new QTimer(this);

    Button_Ge_H ->setGeometry(575, 100, 300, 50);
    Button_Ge_N ->setGeometry(575, 175, 300, 50);
    Button_Ge_E ->setGeometry(575, 250, 300, 50);
    Button_Cus ->setGeometry(575, 325, 300, 50);
    Button_Start ->setGeometry(575, 400, 300, 50);
    Button_Ans ->setGeometry(575, 175, 300, 50);
    Button_Che ->setGeometry(575, 325, 300, 50);
    Button_ReStart ->setGeometry(575, 525, 300, 50);
    Label ->setGeometry(50, 525, 500, 50);
    Label ->setStyleSheet("color: cyan; font-size: 30px; font-weight: bold");
    LCD->setGeometry(575, 25, 300, 50);
    LCD->setDigitCount(5);
    LCD->display("00:00");
    LCD->setStyleSheet("color: purple");
    Button_Ans ->hide();
    Button_Che ->hide();
    Button_Ge_H ->setStyleSheet("background: blue; color: yellow; font-size: 30px; font-weight: bold");
    Button_Ge_N ->setStyleSheet("background: blue; color: yellow; font-size: 30px; font-weight: bold");
    Button_Ge_E ->setStyleSheet("background: blue; color: yellow; font-size: 30px; font-weight: bold");
    Button_Cus ->setStyleSheet("background: blue; color: yellow; font-size: 30px; font-weight: bold");
    Button_Start ->setStyleSheet("background: magenta; color: red; font-size: 30px; font-weight: bold");
    Button_ReStart ->setStyleSheet("background: magenta; color: red; font-size: 30px; font-weight: bold");
    Button_Ans ->setStyleSheet("background: red; color: blue; font-size: 30px; font-weight: bold");
    Button_Che ->setStyleSheet("background: red; color: blue; font-size: 30px; font-weight: bold");

}
void MainWindow::Restart(){
    QString empty = "";
    for(int i=0; i<Sudoku::sudokuSize; ++i){
        Map[i]->setStyleSheet("color: black; font-size: 24px; font-weight: bold");
        Map[i]->setText(empty);
        Map[i]->setStyleSheet("background: white; color: black; font-size: 24px; font-weight: bold");
        Que_Map[i] = false;
    }
    setBackground();
    disconnect(Timer, SIGNAL(timeout()), this, SLOT(showTime()));
    sec = 0;
    min = 0;
    LCD->display("00:00");
}
void MainWindow::setBackground(){
    for(int i=0; i<27; i+=9) // set cell background
        for(int j=0; j<3; ++j)
            Map[i+j]->setStyleSheet("background: lightgray; color: black; font-size: 24px; font-weight: bold");
    for(int i=0; i<27; i+=9)
        for(int j=6; j<9; ++j)
            Map[i+j]->setStyleSheet("background: lightgray; color: black; font-size: 24px; font-weight: bold");
    for(int i=0; i<27; i+=9)
        for(int j=30; j<33; ++j)
            Map[i+j]->setStyleSheet("background: lightgray; color: black; font-size: 24px; font-weight: bold");
    for(int i=0; i<27; i+=9)
        for(int j=54; j<57; ++j)
            Map[i+j]->setStyleSheet("background: lightgray; color: black; font-size: 24px; font-weight: bold");
    for(int i=0; i<27; i+=9)
        for(int j=60; j<63; ++j)
            Map[i+j]->setStyleSheet("background: lightgray; color: black; font-size: 24px; font-weight: bold");
}
void MainWindow::TimerStart(){
    Timer->start(1000);
    connect(Timer, SIGNAL(timeout()), this, SLOT(showTime()));
}
void MainWindow::showTime(){
    ++sec; // + 1 second
    if(sec > 59){
        sec = 0;
        ++min;
    }
    secstr = QString::number(sec);
    minstr = QString::number(min);
    if(sec < 10)
        secstr = "0"+secstr;
    if(min < 10)
        minstr = "0"+minstr;

    LCD->display(minstr+":"+secstr);
}
