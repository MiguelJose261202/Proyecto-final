#include <iostream>
#include <fstream>//------------------------------> Sirve para la entrada y salida de un archivo
using namespace std;
// VARIABLES ESTATICAS
int NUM_LETRAS;
int NUM_INTENTOS;
int main()
{
     // Declarando variables
     int opcion, MenuCaso1, MenuJuego;
     int NUMjugadores;
     // ios :: out -------> Cada vez que corra el programa  va a borrar la informacion previamente
     // ios :: app -------> Cada vez que corra el programa va a generar el mismo mensaje en la parte de abajo como una pleca n
     ofstream Escritura ("Prueba.txt", ios ::out | ios ::app);
     Escritura<<"quepedo esta cosa jala\n";//ES LO QUE SE VA VER EN EL TXT





     // Menu principal del juego
     cout << "Bienvenido al jnuego del ahorcado, que le gustaria hacer a continuaicon usuario" << endl;
     cout << "|---------Menu--------------|" << endl;
     cout << "|1.Jugar al ahorcado        |" << endl;
     cout << "|2.Ver tabla de posiciones  |" << endl;
     cout << "|3.Agregar palabras al juego|" << endl;
     cout << "|4.Salir                    |" << endl;
     cout << "|---------------------------|" << endl;
     cout << "Eleccion:";
     cin >> opcion;//variable para guardar la opcion del codigo principal

     switch (opcion)
     {
     // Menu del modulo jugar
     case 1: // El menu que se le mostrara al usuario al iniciar a jugar
          cout << "|-----------Menu------------|" << endl;
          cout << "|1.Comenzar a jugar         |" << endl;
          cout << "|2.Reglas del juego         |" << endl;
          cout << "|3.salir                    |" << endl;
          cout << "|---------------------------|" << endl;
          cout << "Eleccion:";
          cin >> MenuCaso1;//variable para guardar la opcion del menu caso 1
          switch (MenuCaso1)
          {
          case 1: //---------------------------------------------------JUEGO-------------------------------------------//
               cout << "|En cual dificultad te gustaria jugar usuario?|" << endl;
               cout << "|1.Facil                                      |" << endl;
               cout << "|2.Normal                                     |" << endl;
               cout << "|3.Dificil                                    |" << endl;
               cout << "Eleccion:";
               cin >> MenuJuego;
               switch (MenuJuego)
               {
               case 1: //-------------------------------------MODO FACIL--------------------------------------------------//

                    cout << "Introduzca el numero de jugadores:" << endl;
                    //NO se si hacer un menu del numero de jugadores
                    cin >> NUMjugadores;//variable para guardar el numero de jugadores

                    break;
               case 2: //-----------------------------------MODO NORMAL-------------------------------------------------//
                    cout << "aqui el modo normal" << endl;
                    break;
               case 3: //-----------------------------------MODO DIFICIL--------------------------------------------------//
                    cout << "aqui el modo dificil" << endl;
                    break;
               default: // salida
                    cout << "introduci un numero valido porfa" << endl;
                    break;
               }
               break;
          case 2:
               cout << "|---------Reglas----------------------------------------------------------------|" << endl;
               cout << "|Tu tendras que adivinar una palabra escondida la cual no podras ver obviamente |" << endl;
               cout << "|contando con una cantidad de intentos con respecto a la dificultad seleccionada|" << endl;
               cout << "|debido a esto palabra seria de una longitud mayor o menor segun la dificultad  |" << endl;
               cout << "|si tus intentos acaban tu juego termina a su vez pasa el siguiente jugador     |" << endl;
               cout << "|-------------------------------------------------------------------------------|" << endl;
               
               break;
          case 3: // salir del programa
               cout << "demole pa fuera";
               break;
          default: //----------default para le numero correcto---//
               cout << "ingresa un numero valido porfavor";
               break;
          }
          break;
     // Menu tabla de juego
     case 2: //---------------------------------------------------TABLA DE JUGADORES--------------------------------//
          cout << "aqui se mostraria la tabla de jugadores";
          break;
     // Menu agregar palabras
     case 3: //------------------------------------------------AGREGAR PALABRAS--------------------------------------//
          cout << "aqui seria el modulo donde se agregarian palabras";
          break;
     // Salida
     case 4:
          cout << "gracias por tu tiempo master";
          break;
     // error por no ingresar un numero correcto
     default:
          cout << "introduci un numero valido porfavor";
          break;
     }

     return 0;
}
