#include <iostream>
#include <windows.h>
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

using namespace std;

int printers[3]; //Si es 1 esta libre, si es 0 esta ocupado

struct proceso{
    int time_execut;
    int print_used;
    bool active = false;
    bool executed = false;
}procesos[10 ];

int n_proc = 0;
int n_print = 0;

void initializePrinters();//Inicia todas las impresoras con 1 = libres
void getPrinter(int n_proc, int n_print);
void leavePrinter(int p);
int timeR(); //me devuelve un numero del 1 al 9, representa la cantidad de "tiempo" que el proceso necesita
void restTime();
bool available();
bool remainProcess();//mientras queden procesos por ser ejecutados
bool remainTime();//Mientras algun proceso le quede tiempo de ejecución.
void printAll();

int main()
{
    cout << "Solucion programada por Leonardo Aranda Gutierrez 217761528" << endl << endl;
    cout << "CENTRO UNIVERSITARIO DE CIENCIAS EXACTAS E INGENIERIAS" << endl;
    cout << "INGENIERIA INFORMATICA" << endl;
    cout << "SEMINARIO DE SISTEMAS OPERATIVOS." << endl <<endl;
    cout << "ESTE PROGRAMA REPRESENTA EL PROBLEMA DE APLICACIONES IMPRESORAS" << endl;
    cout << "*para efectos practicos se manejaran solo 10 procesos'" << endl;
    cout << "Presione cualquier tecla para continuar..." << endl << endl;

    system("pause");

    initializePrinters();
    printAll();//Imprimimos una vista de impresoras y procesos

    while (remainProcess() or remainTime()) {//mientras queden procesos

        if (procesos[n_proc].executed == false) {
            for (int i=0;i<10;++i) {
                if (procesos[i].time_execut == 0 and procesos[i].active == true) {//si el tiempo de ejecución ya llegó a 0 y era un proceso activo
                    leavePrinter(i); //se libera la impresora
                }
            }
            cout << endl << endl;
            SetConsoleTextAttribute(hConsole, 6);
            cout << "El proceso " << n_proc+1 << " requiere una impresora." << endl;//El proceso entrante en FIFO solicita una impresora
            SetConsoleTextAttribute(hConsole, 7);
            if (available()==true) {//si hay impresoras disponibles
                SetConsoleTextAttribute(hConsole, 2);
                cout << "La impresora " << n_print+1 << " esta disponible." << endl;
                SetConsoleTextAttribute(hConsole, 7);
                getPrinter(n_proc,n_print); //se le concede una impresora para trabajar.
            }else if (available()==false) {//si no hay impresoras disponibles
                SetConsoleTextAttribute(hConsole, 4);
                cout << "No hay impresoras disponibles, el proceso " << n_proc+1 << " debe esperar." << endl; //El proceso debe de esperar
                SetConsoleTextAttribute(hConsole, 7);
            }


        }
        restTime();//restamos un tiempo a cada proceso activo

        for (int i=0;i<10;++i) {
            if (procesos[i].time_execut == 0 and procesos[i].active == true) {//si el tiempo de ejecución ya llegó a 0 y era un proceso activo
                leavePrinter(i); //se libera la impresora
            }
        }
        printAll();
        Sleep(1000);
    }

    printAll();
    cout << endl << endl;
    system("pause");
    return 0;
}

void getPrinter(int n_proc, int n_print){
    procesos[n_proc].print_used = n_print;
    printers[n_print] = 0;
    int time = timeR();
    procesos[n_proc].time_execut = time;
    procesos[n_proc].active = true;
    SetConsoleTextAttribute(hConsole, 9);
    cout << "Impresora[" << n_print+1 << "] - Proceso[" << n_proc+1 << "]" << endl;
    SetConsoleTextAttribute(hConsole, 7);
}

void leavePrinter(int p){

    int printer = procesos[p].print_used;
    printers[printer] = 1;
    procesos[p].executed = true;
    procesos[p].active = false;

    SetConsoleTextAttribute(hConsole, 10);
    cout << "El proceso " << n_proc+1 << " ha terminado su ejecucion, se libera la impresora " << n_print+1   << endl;
    SetConsoleTextAttribute(hConsole, 7);
}

//Listo
void initializePrinters(){
    for (int i=0;i<3;++i) {
        printers[i] = 1;
    }
}

bool available(){//Disponibilidad de impresoras
    bool flag = false;

    for (int i=0;i<3;++i) {
        if (printers[i] == 1) {
            flag = true;
            n_print = i;
            break;
        }
    }

    return flag;
}

bool remainProcess(){//Procesos faltantes
    bool flag = false;

    for (int i=0;i<10;++i) {
        if (procesos[i].executed == false and procesos[i].active == false) {
            flag = true;
            n_proc = i;
            break;
        }
    }

    return flag;
}

bool remainTime(){
    bool flag = false;

    for (int i=0;i<10;++i) {
        if (procesos[i].time_execut > 0 and procesos[i].active == true) {
            flag = true;
            break;
        }
    }

    return flag;
}

//Listo
int timeR(){
    int time = (rand()%9)+1;
    return time;
}

//Listo
void restTime(){
    for (int i=0;i<10;++i) {
        if (procesos[i].active == true) {
            procesos[i].time_execut = procesos[i].time_execut -1;
        }
    }
}

//Listo
void printAll(){
    cout<< endl<<endl;
    cout << "IMPRESORAS\t\t\tPROCESOS" << endl;
    SetConsoleTextAttribute(hConsole, 6);
    for(int i=0;i<3;++i){
        cout << "I" << i+1 << " ";
    }
    cout << "\t\t\t";
    for(int i=0;i<10;++i){
        cout << "P" << i+1 << " ";
    }
    cout << endl;
    SetConsoleTextAttribute(hConsole, 7);

    for(int i=0;i<3;++i){
        if (printers[i] == 1) {
            SetConsoleTextAttribute(hConsole, 10);
            cout << " - ";
            SetConsoleTextAttribute(hConsole, 7);
        }else if (printers[i]==0) {
            SetConsoleTextAttribute(hConsole, 4);
            cout << " * ";
            SetConsoleTextAttribute(hConsole, 7);
        }
    }
    cout << "\t\t\t";
    for(int i=0;i<10;++i){
        if (procesos[i].active == 1) {
            SetConsoleTextAttribute(hConsole, 10);
            cout << " * ";
            SetConsoleTextAttribute(hConsole, 7);
        }else if (procesos[i].active==0) {
            if (procesos[i].executed == true) {
                SetConsoleTextAttribute(hConsole, 13);
                cout << " F ";
                SetConsoleTextAttribute(hConsole, 7);
            }else {
                SetConsoleTextAttribute(hConsole, 4);
                cout << " - ";
                SetConsoleTextAttribute(hConsole, 7);
            }
        }
    }
    cout << endl;
    cout << "          \t\t\t";
    for(int i=0;i<10;++i){
        if (procesos[i].active == 1) {
            cout << "I" << procesos[i].print_used+1 << " ";
        }else{
            cout << "   ";
        }
    }
    cout << endl;
    cout << "          \t\t\t";
    for(int i=0;i<10;++i){
        if (procesos[i].active == 1) {
            cout << procesos[i].time_execut << "s ";
        }else if (procesos[i].active==0) {
            cout << "   ";
        }
    }
}
