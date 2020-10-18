#include"Generator.h"

void Generator::setModel(int holes){
    QFile file(":/resource/input");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        cerr << "Opening Fail !!!" << endl;
        exit(1);
    }

    QTextStream in(&file);

    srand(time(NULL));
	num = rand()%9;                                       
                                                               
	for(int i=0; i<81; ++i){ // change final answer                              
		new_map[i] = 0;                                     
        in >> data;
        new_map[i] = (data+num)%9+1;
	} 

    for(int i=0; i<holes; ++i){
		zeros = rand()%81;
		new_map[zeros] = 0;
	}
}
int Generator::getMap(int index){
	return new_map[index];
}
                     
