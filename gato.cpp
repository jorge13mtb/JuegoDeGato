
/* Juego de Gato
   Jorge Chavarría Rodríguez
   2013
*/

#include <windows.h>
#include <iostream>
#include <conio.h>
using namespace std;

// Clase Gato
class Gato
{
      public:
             int _tablero[3][3];  // matriz de 3x3 para el tablero del gato
             int pfila;           // posición x del cursor en en tablero
             int pcolumna;        // posición y del cursos en la tablero
             int turno;           // turno (quien esta jugando) de jugador 1 para x, 2 para 0
             int estado;          // auxiliar utilizada en la validación del juego, indica si hay 3 "fichas" iguales seguidas.
             int primera_pos;     // auxiliar utilizada en la validación del juego, primera pos para compararla con los demás.
             
      public:
             Gato();                  // Constructor de la clase gato, inicializa el tablero con 0 (vacía)
             void Jugar();            //  Método que permite el moverse dentro del tablero
             void Marcar();           // Permite marcar el tablero, ya sea con una "X" si es el turno 1, o con un "O" en caso contrario
             void Mover_Arriba();     // Permite moverse una posción hacia arriba en el tablero
             void Mover_Abajo();      // Permite moverse una posción hacia abajo en el tablero
             void Mover_Derecha();    // Permite moverse una posción hacia la derecha en el tablero
             void Mover_Izquierda();  // Permite moverse una posción hacia la izquierda en el tablero
             void Imprimir();         // Imprime el tablero
             void Pintar_Celda(int i, int j, string letra);  // Dibuja una celda del tablero
             
             bool Validar();             // Método para validar si un jugador ha ganado
             bool Valida_Filas();        // Verifica si hay 3 fichas iguales en la misma fila
             bool Valida_Columnas();     // Verifica si hay 3 fichas iguales en la misma columna
             bool Valida_Diagonal_1();   // Verifica si hay 3 fichas iguales en la diagonal
             bool Valida_Diagonal_2();   // Verifica si hay 3 fichas iguales en la diagonal inversa
             bool Gato::Valida_Empate(); // Verifica si hay un empate  
             void Gato::Limpiar();       // Pone el tablero como al inicio del juego
};

Gato::Gato()  // Constructor de la clase gato, inicializa el tablero con 0 (vacía)
{
    pfila = 0;
    pcolumna = 0;
    turno = 1;
    estado = 0;
    primera_pos = 0;
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {   
            _tablero[i][j] = 0;
        }
    }  
}

//  Método que permite el moverse dentro del tablero
void Gato::Jugar()
{
    Imprimir();
    bool terminado = true;
    int tecla;
    while(terminado)
    {
        if(kbhit())
        {
            tecla = getch();
            if(tecla == 32)  // espacio
               Marcar();

            else if(tecla == 72) // arriba
                 Mover_Arriba();
            
            else if(tecla == 80) // abajo
                 Mover_Abajo();
                               
            else if(tecla == 75) // izquierda
                 Mover_Izquierda();

            else if(tecla == 77) // derecha  
                 Mover_Derecha();
            

            if(Validar() == true)
            {
                terminado=false;
                
                if(turno==2)
                {
                      cout<<endl<<"Felicidades ha ganado el jugador X "<<endl<<endl;
                      turno=1;      
                }
                else 
                {
                      cout<<endl<<"Felicidades ha ganado el jugador O "<<endl<<endl; 
                      turno=2;
                }
            }   
            else if(Valida_Empate())
            {
                terminado=false;
                cout<<endl<<"Hubo un empate "<<endl; 
            }
        }
    }
    
    pfila = 0;
    pcolumna = 0;
}

// Permite marcar el tablero, ya sea con una "X" si es el turno 1, o con un "O" en caso contrario
void Gato::Marcar()
{
    if (_tablero[pfila][pcolumna] == 0 & turno==1)
    {
        _tablero[pfila][pcolumna] = 1;
        turno = 2;
    }
    else if(_tablero[pfila][pcolumna] == 0 & turno==2)
    {
        _tablero[pfila][pcolumna] = 2;
        turno = 1;
    }               
    Imprimir();  
}


// Permite moverse una posción hacia arriba en el tablero
void Gato::Mover_Arriba()
{
    if (pfila != 0)
        pfila--;     

    Imprimir();
}

// Permite moverse una posción hacia abajo en el tablero
void Gato::Mover_Abajo()
{
    if (pfila == 2)
        pfila = 0;      
    else
        pfila++;
        
    Imprimir(); 
}

// Permite moverse una posción hacia la derecha en el tablero
void Gato::Mover_Derecha()
{
    if(pfila==2 & pcolumna==2)
        Imprimir(); 
     else if (pcolumna == 2)
     {
         pcolumna = 0;
         pfila++;        
     }
     else
         pcolumna++;
       
     Imprimir();
}

// Permite moverse una posción hacia la izquierda en el tablero
void Gato::Mover_Izquierda()
{
    if(pcolumna < 0)
        pcolumna = 0;
    else if(pfila==0 & pcolumna==0)
        Imprimir(); 
    else if(pcolumna == 0)
    {
        pfila--;
        pcolumna = 2;
    }
    else
        pcolumna--;
                    
    Imprimir();  
}


// Método para validar si un jugador ha ganado
bool Gato::Validar()
{    
     if(Valida_Filas() || Valida_Columnas() || Valida_Diagonal_1() || Valida_Diagonal_2())
         return true;
     else
         return false;
}   

// Verifica si hay 3 fichas iguales en la misma fila 
bool Gato::Valida_Filas()
{
    for(int i = 0; i < 3; i++)    
    {           
        primera_pos = _tablero[i][0];
        if(primera_pos != 0)
        {
            for(int j = 0; j < 3; j++)
            {
                if(primera_pos == _tablero[i][j])
                    estado++;
            } 
            if (estado==3) 
                return true;
            estado=0;
        }  
    }
    estado=0;
    return false;
}

// Verifica si hay 3 fichas iguales en la misma columna 
bool Gato::Valida_Columnas()
{
    for(int i = 0; i < 3; i++) 
    {           
        primera_pos = _tablero[0][i];
        if(primera_pos !=0)
        {
            for(int j = 0; j < 3; j++)
            {
                if(primera_pos == _tablero[j][i])
                    estado++;
            } 
            if (estado==3)
               return true;
            estado=0;
        }  
    }
    estado=0;
    return false;
}

// Verifica si hay 3 fichas iguales en la dianonal
bool Gato::Valida_Diagonal_1()
{
    primera_pos = _tablero[0][0];
    if(primera_pos != 0)
    {
        for(int i = 0; i < 3; i++) 
        {           
            if(primera_pos == _tablero[i][i])
                estado++;
        } 
        if (estado==3)
               return true;
            estado=0;
    }  
    estado=0;
    return false;
}

// Verifica si hay 3 fichas iguales en la diagonal inversa
bool Gato::Valida_Diagonal_2()
{
    int n=2;
    for(int i = 0; i < 3; i++)    
    {           
        primera_pos = _tablero[0][2];
        if(primera_pos !=0)
        {
            if(primera_pos == _tablero[i][n])
                estado++;
     
            if (estado==3)
               return true;
        }  
        n--;
    }
    estado=0;
    return false;
}

// Verifica si hay un empate
bool Gato::Valida_Empate()
{ 
    int cuantos = 0;
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {   
           if(_tablero[i][j] != 0)
              cuantos++;
        }
    } 
    if(cuantos == 9)
        return true;
    return false; 
}

// Pone el tablero como al inicio del juego
void Gato::Limpiar()
{
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {   
            _tablero[i][j] = 0;
        }
    }  
}

// Método de impresión, dibuja el tablero y usa el método "Pintar_Celda" como auxiliar
void Gato::Imprimir()
{
    system("cls");
    cout<<endl<<"************************Gato************************"<<endl<<endl;
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {       
            if(_tablero[i][j] == 0)
                 Pintar_Celda(i, j , "   ");
            
            else if(_tablero[i][j] == 1)
                 Pintar_Celda(i, j , " X ");
                 
            else 
                 Pintar_Celda(i, j , " O ");
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
        cout<<endl<<endl;
    }
}

// Permite puntar una celca, ya sea vacia, con una "X" o con un "O"
void Gato::Pintar_Celda(int i, int j, string letra)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
    if(pfila == i && pcolumna == j)
    {   
        cout<<"  > ";
        if(letra=="   ")
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xff);
        else if(letra==" X ")
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xce);
        else
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x91);
        cout<<letra;  
    }
    else
    {
        cout<<"    ";
        if(letra=="   ")
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xff);
        else if(letra==" X ")
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xce);
        else
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x91);
        cout<<letra;
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
    cout<<" ";   
}



int main()
{
    Gato *Juego_Gato = new Gato();
    string opcion;
    
    while(true)
    {
        system("cls");
        cout<<"************************        Gato      ************************"<<endl<<endl;
        cout<<"--------------------------------MENU-------------------------------"<<endl;
        cout<<"       1. Instrucciones"<<endl;
        cout<<"       2. Jugar"<<endl;
        cout<<"       3. Salir"<<endl;
        cout<<endl<<">>>>>>>Digite una Opcion y Presione ENTER: ";
        cin>>opcion;
        if (opcion == "1")
        {
            system("cls");       
            cout<<endl<<"************************    Instrucciones del Gato    ************************"<<endl<<endl;
            cout<<"El jugador se desplaza sobre el tablero usando los cuatro direccionales"<<endl<<endl;
            cout<<"Se marca la ficha, usando la barra de espacio"<<endl<<endl;
            cout<<"La misma tecla se utiliza para los 2, pero marca diferente dependiendo del turno"<<endl<<endl;
            cout<<"Empieza el jugador X, y luego el O, el que gana, empieza la siguiente partida"<<endl<<endl;
            cout<<""<<endl<<endl;
        }             
        else if(opcion == "2")
        {
            Juego_Gato->Jugar();  
            Juego_Gato->Limpiar();    
        }
        else if(opcion == "3")
            break;
    
        else
            cout<<endl<<"**************************OPCION NO VALIDA*************************"<<endl<<endl;
        system("pause");           
    }
    Juego_Gato = NULL;
    delete Juego_Gato;
    return 0;
}





