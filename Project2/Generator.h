#include <iostream>
#include <cstdlib>
#include <QTextStream>
#include <QFile>
#include <QDebug>
using namespace std;

class Generator{
public:
    void setModel(int holes);
    int getMap(int index);

private:
	int num, data, zeros;
	int new_map[81];
};
