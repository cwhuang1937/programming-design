#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    window()->setFixedSize(1200, 900);
    window()->setStyleSheet("background: gray");
    setting();
    srand(time(NULL));

    connect(Button_auto, SIGNAL(clicked()), this, SLOT(Button_auto_push()));
    for(int i=0; i<3; ++i){
        connect(timer_enemy_gen[i], SIGNAL(timeout()), signalMapper_enemy_gen[i], SLOT(map()));
        signalMapper_enemy_gen[i]->setMapping(timer_enemy_gen[i], i);
        connect(signalMapper_enemy_gen[i], SIGNAL(mapped(int)), this, SLOT(generate_enemy(int)));
    }

    connect(timer_detect, SIGNAL(timeout()), this, SLOT(detect_player())); //player dectect attack
    connect(timer_detect_enemy, SIGNAL(timeout()), this, SLOT(enemy_detect_attack())); //enemy dectect attack
    connect(timer_life_gen, SIGNAL(timeout()), this, SLOT(life_gen()));
    connect(timer_player_move, SIGNAL(timeout()), this, SLOT(move_player()));
    connect(timer_unique_skill_add, SIGNAL(timeout()), this, SLOT(unique_skill_add()));


}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::use_unique_skill_end(){
    qDebug() << "End of Use Unique Skill";
    timer_unique_skill->stop();
    shoot_num = 1;
}
void MainWindow::use_unique_skill(){
    qDebug() << "Use Unique Skill";
    unique_skill_num = 0;
    unique_skill_pro->setValue(unique_skill_num);
    shoot_num = 5;
    timer_unique_skill->start(5000);
    connect(timer_unique_skill, SIGNAL(timeout()), this, SLOT(use_unique_skill_end()));
}
void MainWindow::unique_skill_add(){
    if(unique_skill_num >= 100)
        return;
    unique_skill_num += 5;
    unique_skill_pro->setValue(unique_skill_num);
}

void MainWindow::Button_bomb_push(){
    timer_detect->stop();  //invincible
    timer_detect_wait->start(3000);
    player->setPixmap(QPixmap(":/resource/picture/player_inv.png").scaled(80, 100));
    skill_num--;
    skill_num_str = QString::number(skill_num);
    skill->setText("X " + skill_num_str);
    Bullet *b[15];
    for(int i=0; i<15; ++i){
        b[i] = new Bomb;
        b[i]->setPixmap(QPixmap(":/resource/picture/bomb.png").scaled(60, 100));
        b[i]->setPos(60*i, 810);
        b[i]->connect(timer_fly, SIGNAL(timeout()), b[i], SLOT(fly()));
        scene->addItem(b[i]);
    }

}
void MainWindow::life_gen(){
    int x = rand()%840;
    Tool1 *life;
    life = new Tool1;
    life->setPixmap(QPixmap(":/resource/picture/tool1.png").scaled(50, 70));
    life->setPos(x, 0);
    life->connect(timer_tool_fly, SIGNAL(timeout()), life, SLOT(fly()));
    scene->addItem(life);
}
void MainWindow::boss_detect_attack(){
    if(boss_hp_bar <= 0){ // boss killed
        Tool2 *skill;
        skill = new Tool2;
        skill->setPixmap(QPixmap(":/resource/picture/bomb_tool.png").scaled(30, 70));
        skill->setPos(boss->x(), boss->y());
        skill->connect(timer_tool_fly, SIGNAL(timeout()), skill, SLOT(fly()));
        scene->addItem(skill);
        e3_num++; // record kills
        e3_num_str = QString::number(e3_num);
        e3_rec->setText("X " + e3_num_str);
        score_num += 5000; // record scores
        score_record->display(score_num);
        boss_pro->hide();
        timer_enemy_gen[2]->start(20000);
        delete boss;
        boss_hp += 100;
        disconnect(timer_detect_boss, SIGNAL(timeout()), this, SLOT(boss_detect_attack()));
        return;
    }

    QList<QGraphicsItem *> boss_list = scene->collidingItems(boss);
    foreach (QGraphicsItem *i, boss_list) {
        Bullet_p1 *item1 = dynamic_cast<Bullet_p1*>(i);
        Bomb *item2 = dynamic_cast<Bomb*>(i);
        if(item1){
            delete item1;
            boss_hp_bar--;;
            boss_pro->setValue(boss_hp_bar);
        }
        if(item2){
            delete item2;
            boss_hp_bar -= 20;;
            boss_pro->setValue(boss_hp_bar);
        }
    }

}
void MainWindow::enemy_detect_attack(){
    if(life_num <= 0){  //game over
        Timer->disconnect();
        timer_detect->disconnect();
        timer_auto->disconnect();
        timer_detect_boss->disconnect();
        timer_detect_enemy->disconnect();
        timer_detect_wait->disconnect();
        timer_fly->disconnect();
        timer_player_move->disconnect();

        QGraphicsScene *scene_end = new QGraphicsScene(0, 0, 898, 898);
        QPixmap bg(":/resource/picture/background_end.jpg");
        QString score_str = QString::number(score_num);
        scene_end->setBackgroundBrush(bg.scaled(900,900));
        ui->graphicsView->setScene(scene_end);
        Game_over->setWindowTitle("Game Over\n");
        Game_over->setText("Your Scores: " + score_str);
        Game_over->show();

        return;
    }
    score_num += 1;
    score_record->display(score_num);
    QList<QGraphicsItem *> scene_list = scene->items();
    QList<QGraphicsItem *> enemy1_list, enemy2_list;
    foreach (QGraphicsItem *i, scene_list){
        Enemy_1 *enemy1 = dynamic_cast<Enemy_1*>(i);
        Enemy_2 *enemy2 = dynamic_cast<Enemy_2*>(i);
        if(enemy1)
            enemy1_list.append(enemy1);
        if(enemy2)
            enemy2_list.append(enemy2);

    }
//    qDebug() << enemy_list.size();
    foreach (QGraphicsItem *i, enemy1_list) {
        QList<QGraphicsItem *> attack_list = scene->collidingItems(i);
        foreach (QGraphicsItem *j, attack_list) {
            Bullet_p1 *item1= dynamic_cast<Bullet_p1*>(j);
            Bomb *item2 = dynamic_cast<Bomb*>(j);
            if(item1 || item2){
                e1_num++;
                e1_num_str = QString::number(e1_num);
                e1_rec->setText("X " + e1_num_str);
                score_num += 200;
                score_record->display(score_num);
                delete i;
                delete item1;
                break;
            }
        }
     }
    foreach (QGraphicsItem *i, enemy2_list) {
        QList<QGraphicsItem *> attack_list = scene->collidingItems(i);
        foreach (QGraphicsItem *j, attack_list) {
            Bullet_p1 *item1 = dynamic_cast<Bullet_p1*>(j);
            Bomb *item2 = dynamic_cast<Bomb*>(j);
            if(item1 || item2){
                e2_num++;
                e2_num_str = QString::number(e2_num);
                e2_rec->setText("X " + e2_num_str);
                score_num += 100;
                score_record->display(score_num);
                delete i;
                delete item1;
                break;
            }
        }
     }
}

void MainWindow::detect_player(){
    QList<QGraphicsItem *> list = scene->collidingItems(player);
    foreach (QGraphicsItem *i, list) {
        Enemy *enemy = dynamic_cast<Enemy*>(i);
        Bullet_e1 *bullet1 = dynamic_cast<Bullet_e1*>(i);
        Bullet_e2 *bullet2 = dynamic_cast<Bullet_e2*>(i);
        Bullet_boss1 *bullet3 = dynamic_cast<Bullet_boss1*>(i);
        Tool1 *tool1 = dynamic_cast<Tool1*>(i);
        Tool2 *tool2 = dynamic_cast<Tool2*>(i);
        if(enemy || bullet1 || bullet2 || bullet3){
            delete player;
            life_num--;
            life_num_str = QString::number(life_num);
            life->setText("X " + life_num_str);
            revive();
            break;
        }
        if(tool1){
            life_num++;
            delete tool1;
            life_num_str = QString::number(life_num);
            life->setText("X " + life_num_str);
            break;
        }
        if(tool2){
            skill_num++;
            qDebug() << skill_num;
            delete tool2;
            skill_num_str = QString::number(skill_num);
            skill->setText("X " + skill_num_str);
            break;
        }
    }

}

void MainWindow::generate_enemy(int index){
    Enemy *enemy;
    int x, y;
    switch (index) {
    case 0:
        x = rand()%840;
        y = rand()%270 + 30;
        enemy = new Enemy_1;
        enemy ->setPixmap(QPixmap(":/resource/picture/enemy1.png").scaled(120, 120));
        enemy ->setPos(x, y);
        enemy ->connect(timer_enemy_move[index], SIGNAL(timeout()), enemy, SLOT(move()));
        scene->addItem(enemy);
        enemy->shoot();
        break;
    case 1:
        x = rand()%2;
        y = rand()%420 + 30;
        enemy = new Enemy_2;
        enemy ->setPixmap(QPixmap(":/resource/picture/enemy2.png").scaled(60, 60));
        enemy ->setPos(x*800, y);
        enemy ->connect(timer_enemy_move[index], SIGNAL(timeout()), enemy, SLOT(move()));
        scene->addItem(enemy);
        enemy->shoot();
        break;
    case 2:
        boss = new Boss;
        boss ->setPixmap(QPixmap(":/resource/picture/boss.png").scaled(300, 300));
        boss ->setPos(400, 50);
        boss ->connect(timer_enemy_move[index], SIGNAL(timeout()), boss, SLOT(move()));
        scene->addItem(boss);
        boss->shoot();
        connect(timer_detect_boss, SIGNAL(timeout()), this, SLOT(boss_detect_attack())); //boss dectect attack
        timer_enemy_gen[2]->stop();
        boss_pro->setMaximum(boss_hp);
        boss_pro->setValue(boss_hp);
        boss_hp_bar = boss_hp;
        boss_pro->show();
        break;
    default:
        break;
    }
}

void MainWindow::keyPressEvent(QKeyEvent *e){
    switch (e->key()) {
    case Qt::Key_Up:
    case Qt::Key_W:
        up = 1;
        break;
    case Qt::Key_Down:
    case Qt::Key_S:
        down = 1;
        break;
    case Qt::Key_Left:
    case Qt::Key_A:
        left = 1;
        break;
    case Qt::Key_Right:
    case Qt::Key_D:
        right = 1;
        break;
    case Qt::Key_Space:
        player_shoot();
        break;
    case Qt::Key_Shift:
        Button_auto_push();
        break;
    case Qt::Key_Control:
        if(skill_num<=0)
            break;
        Button_bomb_push();
        break;
    case Qt::Key_Z:
        if(unique_skill_num<100)
            break;
        use_unique_skill();
        break;
    default:
        break;
    }
}
void MainWindow::keyReleaseEvent(QKeyEvent *e){
    switch (e->key()) {
    case Qt::Key_Up:
    case Qt::Key_W:
        up = 0;
        break;
    case Qt::Key_Down:
    case Qt::Key_S:
        down = 0;
        break;
    case Qt::Key_Left:
    case Qt::Key_A:
        left = 0;
        break;
    case Qt::Key_Right:
    case Qt::Key_D:
        right = 0;
        break;
    default:
        break;
    }
}

void MainWindow::mousePressEvent(QMouseEvent *e){
    player_shoot();
}
void MainWindow::Button_auto_push(){
    if(auto_index == 0){
        connect(timer_auto, SIGNAL(timeout()), this, SLOT(player_shoot()));
        ++auto_index;
    }
    else{
        disconnect(timer_auto, SIGNAL(timeout()), this, SLOT(player_shoot()));
        auto_index = 0;
    }
}

void MainWindow::player_shoot(){
    Bullet_p1 *b[shoot_num];
    if(shoot_num == 1){
        b[0] = new Bullet_p1;
        b[0]->setPixmap(QPixmap(":/resource/picture/bullet1.png").scaled(30, 50));
        b[0]->setPos(player->x()+28, player->y() - b[0]->pixmap().height()/2-10);
        b[0]->connect(timer_fly, SIGNAL(timeout()), b[0], SLOT(fly()));
        scene->addItem(b[0]);
        return;
    }
    for(int i=0; i<shoot_num; ++i){
        b[i] = new Bullet_p1;
        b[i]->setPixmap(QPixmap(":/resource/picture/bullet1.png").scaled(30, 50));
        b[i]->setPos(player->x()+28-50+25*i, player->y() - b[i]->pixmap().height()/2-10);
        b[i]->connect(timer_fly, SIGNAL(timeout()), b[i], SLOT(fly()));
        scene->addItem(b[i]);
    }
}
void MainWindow::setting(){
    ui->setupUi(this);
    scene = new QGraphicsScene(0, 0, 898, 898); //create object
    for(int i=0; i<3; ++i){
        signalMapper_enemy_gen[i] = new QSignalMapper;
        timer_enemy_gen[i] = new QTimer;
        timer_enemy_move[i] = new QTimer;
    }
    timer_fly = new QTimer;
    timer_auto = new QTimer;
    timer_detect = new QTimer;
    timer_detect_wait = new QTimer;
    timer_detect_enemy = new QTimer;
    timer_detect_boss = new QTimer;
    Timer = new QTimer;
    timer_life_gen = new QTimer;
    timer_tool_fly = new QTimer;
    timer_player_move = new QTimer;
    timer_unique_skill_add = new QTimer;
    timer_unique_skill = new QTimer;

    Game_over = new QMessageBox;
    LCD = new QLCDNumber(this);
    score_record = new QLCDNumber(this);
    boss_pro = new QProgressBar(this);
    unique_skill_pro = new QProgressBar(this);
    Button_auto = new QPushButton(this);
    Button_bomb = new QPushButton(this);
    life_icon = new QLabel(this);
    life = new QLabel(this);
    score = new QLabel(this);
    kills = new QLabel(this);
    e1 = new QLabel(this);
    e2 = new QLabel(this);
    e3 = new QLabel(this);
    e1_rec = new QLabel(this);
    e2_rec = new QLabel(this);
    e3_rec = new QLabel(this);
    skill = new QLabel(this);
    skill_icon = new QLabel(this);

    Game_over->setGeometry(300, 300, 600, 150);
    Game_over->setStyleSheet("color: purple; font-size: 40px; font-weight: bold; background: black");
    Game_over->hide();

    boss_pro->hide();
    boss_pro->setGeometry(0, 0, 900, 30);
    boss_pro->setStyleSheet("color: purple; font-size: 40px; font-weight: bold");
    boss_pro->setFormat("BOSS: %p %");
    ui->graphicsView->setScene(scene); // set background

    QPixmap bg(":/resource/picture/background.jpg");
    scene->setBackgroundBrush(bg.scaled(900,900));

    life_icon->setPixmap(QPixmap(":/resource/picture/player.png").scaled(60, 80));
    life_icon->setGeometry(900, 240, 150, 80);
    skill_icon->setPixmap(QPixmap(":/resource/picture/bomb.png").scaled(30, 70));
    skill_icon->setGeometry(920, 320, 130, 80);
    e1->setPixmap(QPixmap(":/resource/picture/enemy1.png").scaled(70, 70));
    e1->setGeometry(900, 560, 150, 80);
    e2->setPixmap(QPixmap(":/resource/picture/enemy2.png").scaled(70, 70));
    e2->setGeometry(900, 640, 150, 80);
    e3->setPixmap(QPixmap(":/resource/picture/boss.png").scaled(70, 70));
    e3->setGeometry(900, 480, 150, 80);

    life->setText("X 5");
    life->setStyleSheet("color: red; font-size: 40px; font-weight: bold");
    life->setGeometry(1050, 240, 150, 80);
    skill->setText("X 3");
    skill->setStyleSheet("color: blue; font-size: 40px; font-weight: bold");
    skill->setGeometry(1050, 320, 150, 80);
    e1_rec->setText("X 0");
    e1_rec->setStyleSheet("color: green; font-size: 40px; font-weight: bold");
    e1_rec->setGeometry(1050, 560, 150, 80);
    e2_rec->setText("X 0");
    e2_rec->setStyleSheet("color: green; font-size: 40px; font-weight: bold");
    e2_rec->setGeometry(1050, 640, 150, 80);
    e3_rec->setText("X 0");
    e3_rec->setStyleSheet("color: green; font-size: 40px; font-weight: bold");
    e3_rec->setGeometry(1050, 480, 150, 80);

    score->setText("   Your Scores");
    score->setStyleSheet("color: black; font-size: 40px; font-weight: bold");
    score->setGeometry(900, 80, 300, 80);
    score_record->setGeometry(900, 160, 300, 80);
    score_record->setDigitCount(10);
    score_record->display("0");
    score_record->setStyleSheet("color: blue");
    kills->setText("     Your Kills");
    kills->setStyleSheet("color: black; font-size: 40px; font-weight: bold");
    kills->setGeometry(900, 400, 300, 80);

    auto_index = 0;
    sec = 0;
    min = 0;
    life_num = 5;
    skill_num = 3;
    boss_hp = 100;
    boss_hp_bar = 0;
    score_num = 0;
    e1_num = 0;
    e2_num = 0;
    e3_num = 0;
    unique_skill_num = 100;
    shoot_num = 1;



    LCD->setGeometry(900, 0, 300, 80);
    LCD->setDigitCount(5);
    LCD->display("00:00");
    LCD->setStyleSheet("color: purple");

    Timer->start(1000);
    connect(Timer, SIGNAL(timeout()), this, SLOT(showTime()));

    timer_fly->start(10);   //control environment
    timer_auto->start(100);
    timer_enemy_gen[0]->start(2000);
    timer_enemy_move[0]->start(50);
    timer_enemy_gen[1]->start(2500);
    timer_enemy_move[1]->start(1000);
    timer_enemy_gen[2]->start(20000);
    timer_enemy_move[2]->start(500);
    timer_detect_enemy->start(5);
    timer_detect_boss->start(5);
    timer_life_gen->start(15000);
    timer_tool_fly->start(500);
    timer_player_move->start(10);
    timer_unique_skill_add->start(2000);

    unique_skill_pro->setGeometry(900, 700, 300, 100);
    unique_skill_pro->setFormat("Skill(Press Z)\n  %p %");
    unique_skill_pro->setStyleSheet("color: purple; font-size: 30px; font-weight: bold; background: white");
    unique_skill_pro->setValue(unique_skill_num);
    Button_auto->setGeometry(900, 800, 150, 100);
    Button_auto->setText("AUTO\n(Shift)");
    Button_auto->setStyleSheet("color: purple; font-size: 40px; font-weight: bold; background: blue");
    Button_bomb->setGeometry(1050, 800, 150, 100);
    Button_bomb->setText("BOMB\n(Ctrl)");
    Button_bomb->setStyleSheet("color: purple; font-size: 40px; font-weight: bold; background: blue");
    revive();
}
void MainWindow::revive(){
    timer_detect->stop();
    timer_detect_wait->start(3000);

    player = new Player;
    player->setPixmap(QPixmap(":/resource/picture/player_inv.png").scaled(80, 100));
    scene->addItem(player);
    player->setPos(450, 750);


    timer_detect_wait->connect(timer_detect_wait, SIGNAL(timeout()), this, SLOT(invincible()));
}
void MainWindow::invincible(){
    player->setPixmap(QPixmap(":/resource/picture/player.png").scaled(80, 100));
    timer_detect->start(5);
    timer_detect_wait->stop();
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
void MainWindow::move_player(){
    if(player->y()>0 && up == 1)
        player->setPos(player->x(), player->y() - 5);
    if(player->y()<810 && down == 1)
        player->setPos(player->x(), player->y() + 5);
    if(player->x()>0 && left == 1)
        player->setPos(player->x() - 5 , player->y());
    if(player->x()<840 && right == 1)
        player->setPos(player->x() + 5, player->y());
}

