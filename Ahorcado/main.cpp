#include <iostream>
#include<string>
#include<vector>
#include<cstdlib>
#include<ctime>
#include<fstream>
#include<filesystem>

using namespace std;

struct Jugador{
    string nombre;
    int vida{100};
};

vector<string> cargarPalabras() {

    vector<string> palabras;
    ifstream archivo("palabras.txt");

    if (archivo.is_open()) {
        string palabra;
        while (getline(archivo, palabra)) {
            std::cout << palabra<<endl;
        }

        archivo.close();

    } else {
        cout << "Error al abrir el archivo." << endl;
    }

    return palabras;
}

int generar_num_aleatorio(int menor, int mayor){
    int num = rand() % mayor + menor;
    return num;
}

string conseguir_palabra(const vector<string> & p, int numero_aleatorio) {
    //Escoger una palabra del .txt
    return p.at(numero_aleatorio);
}

bool comprobar_palabra(const string & n){
    //Si la palabra no ha sido modificada.
    for(int i{0};i<n.size();i++){
        if(n.at(i) != '-'){
            return true;
        }
    }
    return false;
}

char PedirCaracter() {
    char aux;

    cout<<"\n\tDame una letra : "<<endl;
    cin>>aux;
    while (cin.fail() or (aux<97 and aux>122)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout<<"\n\tCaracter invalido, introduce otra letra";
        cin>>aux;
    }
    return aux;
}
string Crear_Extra(const string & palabra) {
    string aux;
    for (int i{0};i<palabra.size();i++) {
        aux.at(i) = '-';
    }
    return aux;

}

bool Palabra_correcta(char n,const string & palabra){
    for(int i{0};i<palabra.size();i++){
        if (palabra.at(i) == n) {
            return true;
        }
    }
    return false;
}

void Partida() {

}




int main()
{
    bool repetir = 1;
    Jugador J1;
    do{
        cout<<"\n\tIntroduce tu nombre jugador : ";
        cin>>J1.nombre;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
    }while(cin.fail());
    do {
        J1.vida = 100;

        //Se consiguen las palabras del .txt:
        vector<string>contenedor = cargarPalabras();
        //Numero maximo que sera el tamaño-1 (para no cometer un out_of_range) del contenedor que tiene todas las palabras del txt
        int maximo = contenedor.size()-1;
        //Numero aleatorio : 0- Tamaño del vector
        int num_aleatorio = generar_num_aleatorio(0,maximo);

        //Elegir entre una de las palabras guardadas en el .txt
        string palabra_secreta = conseguir_palabra(contenedor,num_aleatorio);



        //Pruebas de que funciona bien hasta ahora el codigo.
        cout<<num_aleatorio<<endl;
        for (string palabra : contenedor) {
            cout << palabra << endl;
        }

        int contador = palabra_secreta.size();
        do {











            contador--;
        }while (contador>0 or J1.vida > 0);
        string palabra_extra;
        cout << "\n\tAntes de terminar, introduce una nueva palabra para asi expandir el diccionario ";
        cin >> palabra_extra;
        ofstream archivo("palabras.txt", ios::app);
        if (archivo.is_open()) {
            archivo << palabra_extra << endl;
            archivo.close();
            cout << "Palabra guardada correctamente." << endl;
        } else {
            cout << "Error al abrir el archivo." << endl;
        }
        cout<<"\n\tQuieres volver a jugar otra partida (0-no,1-si)?"<<endl;
        cin>>repetir;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<<"\n\tEntrada invalida, introduzca otra"<<endl;
            cin>>repetir;
        }
    }while (repetir);

    
    return 0;
}
