#include <iostream>
#include <set>
#include <vector>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <climits>

using namespace std;
const int GANADOR=7; //Número que representa que el usuario ganó
const int PERDEDOR=0; //Número que representa que el usuario perdió
const string ARCHIVO_PALABRAS="palabras.txt";  //archivo con la lista de palabras a usar, en el directorio del programa

struct Palabras{
    vector<string> nivel1;
    vector<string> nivel2;
    vector<string> nivel3;
};

struct Jugada{
    unsigned int nivel;
    unsigned int intentos=6;
    string palabra;
    set<char> letrasAdivinadas;
    bool ganador=false;
    string palabraArriesgada;
    char ultimaLetraArriesgada;
};


/*
PROPÓSITO: Determina si el archivo cuyo nombre se pasa por parámetro está vacío.
PARÁMETROS:
    string: nombre del archivo a evaluar.
RETORNO: true si el archivo existe, false en caso contrario.
*/
bool existeArchivo(string archivo){
    ifstream infile(archivo);
    return infile.good();
}


/*
PROPÓSITO: Lee del archivo cada palabra almacenada y la guarda en un contenedor en memoria de acuerdo a su cantidad de letras.
Para el nivel 1 las palabras tienen hasta 7 letras inclusive.
Para el nivel 2 las palabras tienen entre 7 y 11 letras inclusive.
Para el nivel 3 las palabras tienen más de 11 letras.
RETORNO: objeto Palabras con vectores de palabras de acuerdo al nivel si el archivo de palabras existe
(si algún archivo no existe, el vector queda vacío).
*/
Palabras cargarPalabras(){
    vector<string> palabrasNivel1, palabrasNivel2, palabrasNivel3;
    string palabra;
    if (existeArchivo(ARCHIVO_PALABRAS)) {
        ifstream archivo(ARCHIVO_PALABRAS);
        if (archivo.is_open()) {
            while (getline(archivo, palabra)) {
                if (palabra.length()<=7)
                    palabrasNivel1.push_back(palabra);
                else
                    if ((palabra.length()>7) && (palabra.length()<=11))
                        palabrasNivel2.push_back(palabra);
                    else
                        palabrasNivel3.push_back(palabra);
            }
            archivo.close();
        }
    }
    Palabras palabras;
    palabras.nivel1=palabrasNivel1;
    palabras.nivel2=palabrasNivel2;
    palabras.nivel3=palabrasNivel3;
    return palabras;
}


/*
PROPÓSITO: Selecciona de manera aleatoria un elemento de un vector de strings y lo retorna.
PARÁMETROS:
    vector<string> : vector con palabras.
RETORNO: Palabra seleccionada al azar.
*/
string seleccionarPalabra(vector<string> palabras){
    srand(time(NULL));
    int indice = rand() % palabras.size();
    return palabras[indice];
}


/*
PROPÓSITO: Mostrar el dibujo en el estado actual.
PARÁMETROS:
    int : cantidad de intentos restantes
*/
void mostrarDibujo(int vidas){
    switch (vidas){
    case 6:
        cout << "__________\n|         |\n|\n|\n|\n|\n|";
        break;
    case 5:
        cout << "__________\n|         |\n|         0\n|\n|\n|\n|";
        break;
    case 4:
        cout << "__________\n|         |\n|         0\n|         |\n|\n|\n|";
        break;
    case 3:
        cout << "__________\n|         |\n|         0\n|        /|\n|\n|\n|";
        break;
    case 2:
        cout << "__________\n|         |\n|         0\n|        /|\\\n|\n|\n|";
        break;
    case 1:
        cout << "__________\n|         |\n|         0\n|        /|\\\n|        /\n|\n|";
        break;
    case PERDEDOR:
        cout << " _________\n|         |\n|         0\n|        /|\\\n|        / \\\n|\n|\n";
        break;
    case GANADOR:
        cout << "__________\n|         |\n|         \n|        \n|      0\n|     \\|/\n|     / \\\n";
        break;
    }
    cout << endl;
}


/*
PROPÓSITO: Mostrar el juego en el estado actual. Mostrar el juego en el estado actual. Por cada letra adivinada, si la letra existe en la palabra se muestra en el lugar correspondiente, en caso contrario, se muestra un guión bajo " _ ".
PARÁMETROS:
    string : palabra en juego.
    set<char> : letras ya adivinadas por el usuario.
*/
void mostrarJuego(string palabra, set<char> letrasAdivinadas){
    for (unsigned int i=0; i<palabra.length(); i++){
        if (letrasAdivinadas.find(palabra[i]) != letrasAdivinadas.end())
            cout << palabra[i];
        else
            cout << " _ ";
    }
    cout << endl;
}


/*
PROPÓSITO: Eliminar espacios delante y detrás de una cadena de caracteres.
PARÁMETROS:
    string : cadena a modificar
RETORNO: cadena modificada (sin los espacios sobrantes).
*/
string trim(string str){
    int i=0;

    //Corta desde la izquierda
    while (isspace(str[i])!=0)
        i++;
    str = str.substr(i,str.length()-i);

    //Corta desde la derecha
    i=str.length()-1;
    while (isspace(str[i])!=0)
        i--;
    str = str.substr(0,i+1);
    return str;
}


/*
PROPÓSITO: Retornar un string con todas sus letras en mayúscula.
PARÁMETROS:
    string : cadena de caracteres a convertir a mayúscula.
RETORNO: string con la cadena convertida.
*/
string mayusculas(string str)
{
    for (unsigned int i = 0; i<str.length() ; i++){
        str[i] = toupper(str[i]);
    }
    return str;
}


/*
PROPÓSITO: Verificar si el usuario ya adivinó todas las letras de la palabra.
PARÁMETROS:
    set<char> : letras ya arriesgadas.
    set<char> : letras en la palabra.
RETORNO: true si todas las letras de la palabra fueron adivinadas, false en caso contrario.
*/
bool todasLasLetrasAdivinadas(set<char> letrasAdivinadas, set<char> letrasDeLaPalabra){
    for (auto letra : letrasDeLaPalabra){
        if (letrasAdivinadas.find(letra)==end(letrasAdivinadas)){
            return false;
        }
    }
    return true;
}


/*
PROPÓSITO: Verificar si la letra arriesgada por el usuario está en la palabra o no
PARÁMETROS:
    string : palabra a adivinar en la jugada actual.
    char : letra arriesgada por el usuario.
RETORNO: true si la letra estaba en la palabra, false en caso contrario.
*/
bool letraEnPalabra(string palabra, char letra){
    return (palabra.find(letra) != string::npos);
}


/*
PROPÓSITO: Verifica el estado del juego (si el jugador ganó o no).
Si aún quedan intentos (intentos!=PERDEDOR), se verifica si el jugador arriesgó una palabra y, de ser así, se verifica si coincide con la palabra en juego. En ese caso, el campo ganador se pone en true. Si no acertó la palabra, el campo intentos se pone en 0 (utilizando la constante PERDEDOR).
Si no arriesgó una palabra, se verifica si la letra arriesgada está en la palabra y, de no ser así, se decrementa el campo intentos.
Si la letra arriesgada está en la palabra, se verifica si ya acertó todas las letras de la palabra en juego. En caso de ser así, el campo ganador se pone en true.
PARÁMETROS:
    Jugada : datos de la jugada actual.
RETORNO: Jugada actual.
*/
Jugada verificarEstado(Jugada jugada){
    //Si aún tiene intentos, se verifica si acertó
    if (!jugada.intentos==PERDEDOR){

        //Sólo puede arriesgarse una palabra una sola vez por juego.
        if (jugada.palabraArriesgada!=""){
            if (jugada.palabra==jugada.palabraArriesgada)
                jugada.ganador=true;
            else{
                jugada.ganador=false;
                jugada.intentos=PERDEDOR;
            }
        }

        //Si palabraArriesgada está vacío, no se arriesgó una palabra sino una letra.
        else{
            //Si la letra arriesgada no está en la palabra, se decrementa la cantidad de intentos restantes
            if (!letraEnPalabra(jugada.palabra, jugada.ultimaLetraArriesgada)){
                jugada.intentos--;
            }

            //Si ya acertó todas las letras, ganador se pone en true
            set<char> letrasDeLaPalabra;
            for (unsigned int i=0; i!=jugada.palabra.length(); i++){
                letrasDeLaPalabra.insert(jugada.palabra[i]);
            }
            if (todasLasLetrasAdivinadas(jugada.letrasAdivinadas, letrasDeLaPalabra)){
                jugada.ganador=true;
            }
        }
    }
    return jugada;
}


/*
PROPÓSITO: Ofrecer al usuario la posibilidad de "adivinar" la palabra, impidiendo incluir números en la palabra arriesgada.
RETORNO: palabra arriesgada por el usuario.
*/
string arriesgarPalabra(){
    string palabra;
    do{
        cout << "\n\t\tARRIESGAR PALABRA: ";
        getline(cin,palabra);
        palabra=trim(mayusculas(palabra));
        if (palabra.find_first_of("0123456789") != string::npos){
            cout << "\t\tLA PALABRA SOLO PUEDE CONTENER LETRAS.\n\n";
        }
    }while (palabra.find_first_of("0123456789") != string::npos);
    return palabra;
}


/*
PROPÓSITO: Ofrecer al usuario la posibilidad de "adivinar" una letra.
Si la letra ya había sido usada previamente (esté o no en la palabra) se imprime un mensaje y se pide otra.
Se valida que el dato ingresado sea una letra y no otro tipo de carácter.
PARÁMETROS:
    set<char>* : puntero al conjunto de letras ya arriesgadas.
RETORNO: letra elegida por el usuario.
*/
char arriesgarLetra(const set<char> &letras){
    char letra;  
    do{
        cout << "\n\t\tADIVINAR LETRA: ";
        cin >> letra;
        letra=toupper(letra);
        if (letras.find(letra) != letras.end()){
            cout << "\n\t\tLETRA YA ARRIESGADA.\n\n" << endl;
        }
    } while ((!isalpha(letra)) || (letras.find(letra) != letras.end()));
    return letra;
}


/*
PROPÓSITO: Ofrecer al usuario la posibilidad de "adivinar" una letra o la palabra entera, mostrándole un menú que le permita elegir (se valida el ingreso de un dato válido).
Si elige arriesgar una letra, se llama a la función correspondiente y la letra se guarda en el campo ultimaLetraArriesgada, además de agregarse al campo letrasAdivinadas.
Si elige arriesgar una palabra, se llama a la función correspondiente y la palabra se guarda en el campo palabraArriesgada.
PARÁMETROS:
    Jugada : datos de la jugada actual.
RETORNO: Jugada actual.
*/
Jugada arriesgar(Jugada jugada){
    int opcion;
    bool errorDeTipoIngresado;

    //Las opciones se muestran hasta que el usuario ingrese una opción válida
    do{
        cout << "\n\tSeleccionar siguiente paso:\n";
        cout << "\t\t1: Adivinar letra\n";
        cout << "\t\t2: Arriesgar palabra (a todo o nada!)\n";

        //Validación de ingreso de tipo de dato entero
        cout << "\n\n--Seleccionar: ";
        cin >> opcion;
        errorDeTipoIngresado = cin.fail();
        cin.clear();
        cin.ignore(INT_MAX, '\n');

    } while (errorDeTipoIngresado || (opcion!=1 && opcion!=2));

    cout << "\n\n\n\n";

    //Se arriesga una sola letra y el juego continúa si quedan más intentos
    if (opcion==1){
        jugada.ultimaLetraArriesgada=arriesgarLetra(jugada.letrasAdivinadas);
        jugada.letrasAdivinadas.insert(jugada.ultimaLetraArriesgada);
    }

    //Se arriesga la palabra completa y el juego debe terminar
    else{
        jugada.palabraArriesgada=arriesgarPalabra();
    }
    return jugada;
}


/*
PROPÓSITO: Inicializa el juego de acuerdo al nivel seleccionado por el usuario, almacenando en el campo palabra una palabra al azar, en mayúsculas.
Luego controla el orden del desarrollo del juego (una jugada continúa mientras el jugador tenga intentos restantes y el campo "ganador" esté en falso).
Mientras la jugada continúa, se muestra la cantidad de intentos restantes, el dibujo de la horca en el estado actual, la palabra a adivinar (con guiones en las letras no adivinadas). Luego se da la opción de arriesgar una letra o la palabra entera. Si la cantidad de intentos se redujo (porque no acertó la letra), se muestra un mensaje que lo indique. Si la letra arriesgada era correcta, se muestra un mensaje que lo indique. Una vez finalizada la jugada, si el campo ganador está en true significa que acertó todas las letras o que arriesgó una palabra y acertó, y se muestra el dibujo correspondiente al estado GANADOR y un mensaje, y el juego termina. Si la jugada finalizó con el campo ganador en falso, se muestra el dibujo correspondiente al estado PERDEDOR y un mensaje, y el juego termina.
PARÁMETROS:
    int : nivel del juego.
    vector<string> : palabras del nivel seleccionado
*/
void controlarJuego(int nivel, vector<string> palabras){
    Jugada jugada;
    jugada.nivel=nivel;

    //Elige una palabra al azar para la jugada actual y la estandariza a mayúsculas
    jugada.palabra=mayusculas(seleccionarPalabra(palabras));

    //Desarrollo del juego
    while ((jugada.intentos > 0) && (!jugada.ganador)){
        cout << "\n\n\tINTENTOS RESTANTES: " << jugada.intentos << "\n\n\n";
        mostrarDibujo(jugada.intentos);
        cout << endl;
        mostrarJuego(jugada.palabra, jugada.letrasAdivinadas);
        cout << "\n\n";

        //Permite al usuario elegir si arriesgará una letra o la palabra
        jugada=arriesgar(jugada);

        //Verifica si el usuario acertó o no, y si ganó o perdió
        unsigned int intentosAnterior=jugada.intentos;
        jugada=verificarEstado(jugada);
        if (jugada.intentos < intentosAnterior){
            cout << "\n\t\tNOP!\n";
        }
        else{
            cout << "\n\t\tACERTASTE\n";
        }
    }
    if (jugada.ganador){
        mostrarDibujo(GANADOR);
        cout << "\n\t\tGANASTE!\n\n\n";
    }
    else{
        mostrarDibujo(PERDEDOR);
        cout << "La palabra era: " << jugada.palabra;
        cout << "\n\n\t\tFIN DEL JUEGO!\n\n\n\n";
    }
}


/* Inicio del programa */
int main(){

    //Inicializa cargando las palabras del archivo txt correspondiente
    Palabras palabras=cargarPalabras();

    int nivel;
    bool errorDeTipoIngresado;
    set<int> opcionesValidas{0,1,2,3};

    std::cout << "( EL ahorcado)" << '\n';


    //El menú se muestra hasta que el usuario ingrese una opción de menú válida y se vuelve a mostrar cuando termina el juego
    do{
        cout << "\n\tSeleccionar Nivel:" << endl;
        cout << "\t\t1: Facil" << endl;
        cout << "\t\t2: Medio" << endl;
        cout << "\t\t3: Dificil" << endl;
        cout << "\t0: Salir\n" << endl;

        //Validación de ingreso de tipo de dato entero
        cout << "--Opcion seleccionada: ";
        cin >> nivel;
        errorDeTipoIngresado = cin.fail();
        cin.clear();
        cin.ignore(INT_MAX, '\n');

        //Iniciar el juego o salir
        if (opcionesValidas.find(nivel) != opcionesValidas.end()){
            switch (nivel){
            case 0:
                break;
            case 1:
                if (palabras.nivel1.empty()){
                    cout << "\tERROR: No hay palabras para ese nivel." << endl;
                }
                else{
                    controlarJuego(nivel, palabras.nivel1);
                }
                break;
            case 2:
                if (palabras.nivel2.empty()){
                    cout << "\tERROR: No hay palabras para ese nivel." << endl;
                }
                else{
                    controlarJuego(nivel, palabras.nivel2);
                }
                break;
            case 3:
                if (palabras.nivel3.empty()){
                    cout << "\tERROR: No hay palabras para ese nivel." << endl;
                }
                else{
                    controlarJuego(nivel, palabras.nivel3);
                }
                break;
            }
        }
    } while (errorDeTipoIngresado || (opcionesValidas.find(nivel) == opcionesValidas.end()) || nivel!=0);

    return 0;
}

