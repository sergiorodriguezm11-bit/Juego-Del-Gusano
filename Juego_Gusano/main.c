/****************************************************************/
/*NOMBRE DEL PROGRAMA: Proyecto_11				    			*/
/*AUTORES:Javier Ruiz y Sergio Rodríguez		     			*/			
/*OBJETIVO:	Rellenar la matriz con un numero determinado de $.  */
/*FECHA DE CREACION: 10/12/2024									*/
/*ULTIMA MODIFICACION:  20/01/2025      						*/
/****************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h> 
#include <conio.h>
#include <locale.h>
#include <string.h>
#include <stdbool.h>

int i,j,numero=0,numerob=0; //variables i y j para los bucles for y numero para el numero del usuario
int matriz[79][19], matrizb[79][19];//matriz con la que se sabra en que posiciones estan los simbolos
int fila=0,columna=0;//fila y columnas para posteriormente asignar un numero aleatorio
int limite_inferior=2,limite_superior_A=79,limite_superior_B=19;//variables necesarias para calcular un numero aleatorio, (delimitaciones del numero)
int lado=40,altura=12,direccion=0,puntaje=0;
char pulsado;
int tiempo;
int cola[100][2];
int longitud=2;
bool abierto=true,salir=false;
char continua='S';//char para saber si continuara el usuario dentro del programa o no
	
enum Colores // Listado de colores (La letra "L" al inicio, indica que es un color más claro que su antecesor).
{
 BLACK = 0,
 BLUE = 1,
 GREEN = 2,
 CYAN = 3,
 RED = 4,
 MAGENTA = 5,
 BROWN = 6,
 LGREY = 7,
 DGREY = 8,
 LBLUE = 9,
 LGREEN = 10,
 LCYAN = 11,
 LRED = 12,
 LMAGENTA = 13,
 YELLOW = 14,
 WHITE = 15
};

void Color(int fondo, int texto) // Función para cambiar el color del fondo y/o pantalla
{
    int Nuevo_Color;
     HANDLE Consola = GetStdHandle(STD_OUTPUT_HANDLE); // Tomamos la consola.

     // Para cambiar el color, se utilizan números desde el 0 hasta el 255.
     // Pero, para convertir los colores a un valor adecuado, se realiza el siguiente cálculo.
     Nuevo_Color = texto + (fondo * 16);

     SetConsoleTextAttribute(Consola, Nuevo_Color); // Guardamos los cambios en la Consola.
     
     //Cambiar el color a partir de ese momento sería por ejemplo: Color(YELLOW,WHITE); //Color de fondo amarillo y del texto blanco
}

/////////////////////////////////////////////////
//FUNCIONES DE PLANTILLA PARA GOTOXY Y PANTALLA//
/////////////////////////////////////////////////

//Función para posicionar el cursor en la pantalla en unas coordenadas
 void gotoxy(int x,int y){  
      HANDLE hcon;  
      hcon = GetStdHandle(STD_OUTPUT_HANDLE);  
      COORD dwPos;  
      dwPos.X= x;  
      dwPos.Y= y;  
      SetConsoleCursorPosition(hcon,dwPos);  
 }
 
//Función para ocultar el cursor parpadeante
void OcultarCursor()
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}
 
//Función para mostrar el cursor parpadeante
void MostrarCursor()
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = TRUE;
   SetConsoleCursorInfo(consoleHandle, &info);
}
 
//Función para ajustar la ventana de la consola (CMD) a un ancho y alto específico en caracteres
int AjustarVentana(int Ancho, int Alto) {
    COORD Coordenada;
    Coordenada.X = Ancho;
    Coordenada.Y = Alto;

    SMALL_RECT Rect;
    Rect.Top = 0;
    Rect.Left = 0;
    Rect.Right = Ancho - 1;
    Rect.Bottom = Alto - 1;

    // Obtener el controlador de la consola
    HANDLE hConsola = GetStdHandle(STD_OUTPUT_HANDLE);

    // Ajustar el buffer al nuevo tamaño
    SetConsoleScreenBufferSize(hConsola, Coordenada);

    // Cambiar tamaño de consola a lo especificado en el buffer
    SetConsoleWindowInfo(hConsola, TRUE, &Rect);
    return 1;
}
 
////////////////////////
//FUNCIONES PERSONALES//
////////////////////////

void tiempo_inicio()
{
	tiempo=time(NULL);
}
void tiempo_final()
{
	tiempo=time(NULL)-tiempo;
}
void intro_sonido()
{
	//char cancion[]="menu_principal_.wav";
	char cancion[]="pacman_beginning.wav";
	
	//PlaySound((LPCSTR)cancion,NULL, SND_LOOP | SND_FILENAME | SND_ASYNC );
	PlaySound((LPCSTR)cancion,NULL, SND_FILENAME | SND_ASYNC );
}

void sonido_final()
{
	//char cancion[]="final.wav";
	
	//PlaySound((LPCSTR)cancion,NULL, SND_FILENAME | SND_ASYNC );	
}

void inicio_sonido()
{
	//char cancion[]="inicio.wav";
	
	//PlaySound((LPCSTR)cancion,NULL,  SND_FILENAME | SND_ASYNC );
}

void comer_sonido()
{
	//char cancion[]="comer.wav";
	char cancion[]="pacman_eatfruit.wav";
	
	PlaySound((LPCSTR)cancion,NULL,  SND_FILENAME | SND_ASYNC );
}

void muerte_sonido()
{
	//char cancion[]="muerte.wav";
	char cancion[]="pacman_death.wav";
	
	PlaySound((LPCSTR)cancion,NULL,  SND_FILENAME | SND_ASYNC );
}

void movimiento_sonido()
{
	//char cancion[]="muerte.wav";
	char cancion[]="pacman_chomp.wav";
	
	PlaySound((LPCSTR)cancion,NULL,  SND_FILENAME | SND_ASYNC );
}

void PintarMarco()
{
	gotoxy(14,21);
	printf("                                                        ");
    int j;
    setlocale(LC_ALL,"C");
    gotoxy(1,1);printf("%c",201);
    gotoxy(80,1);printf("%c",187);
    gotoxy(1,24);printf("%c",200);
    gotoxy(80,24);printf("%c",188);
   
    for(j=2;j<80;j++){
        gotoxy(j,1);printf("%c",205);
        gotoxy(j,20);printf("%c",205);
        gotoxy(j,24);printf("%c",205);        
    }
   
    for(j=2;j<24;j++){
        gotoxy(1,j);printf("%c",186);
        gotoxy(80,j);printf("%c",186);
    }
   
    gotoxy(1,20);printf("%c",204);
    gotoxy(80,20);printf("%c",185);
   
    setlocale (LC_ALL,"Spanish");
}
void limpiarA()
{
	longitud=2;
	int k=0;
	for(i=2;i<80;i++)
	{
		for(j=2;j<=19;j++)
		{
			gotoxy(i,j);printf(" ");
		}
	}
	
	for(i=0;i<19;i++)
	{
		for(j=0;j<79;j++)
		{
			matriz[j][i]=0;
		}
	}

	for(i=0;i<2;i++)
	{
		for(j=0;j<100;j++)
		{
			cola[i][j]=k;
			k++;	
		}
	}
}
void limpiarB()
{
	for(i=2;i<80;i++)
	{
		for(j=22;j<24;j++)
		{
			gotoxy(i,j);printf(" ");
		}
	}
}
void instrucciones()
{
	limpiarB();
	gotoxy(14,20);
	printf(" ESCRIBE UN NUMERO DEL 0 AL 1303 PARA CREAR MANZANAS ");
	gotoxy(14,21);
	printf("-----------------------------------------------------");
}

void instruccionesB()
{
	limpiarB();
	gotoxy(14,20);
	printf(" ESCRIBE UN NUMERO DEL 0 AL 100 PARA CREAR BLOQUES ");
	gotoxy(14,21);
	printf("---------------------------------------------------");
}
void comida()
{	
	//bucle for paraa inicializar a 0 la matriz (siendo 0=vacio)
	for(i=0;i<19;i++)
	{
		for(j=0;j<79;j++)
		{
			matriz[j][i]=0;
		}
	}
	//se obtiene el numeor que quiere el jugador, no saldra del bucle hasta que cumpla la condicion de ser positivo y menor o igual que 78*18(1404)
	do
	{
		instrucciones();//funcion para obtener el diseño del marco y tambien sus instrucciones (lineas 108-115)
		gotoxy(36,23);//posicion en pantalla donde comenzara el siguiente apartado
		Color(BLACK,LRED);
		scanf("%i",&numero);//se obtiene el numero del usuario
		Color(BLACK,WHITE);
	}while(numero>78*18-101||numero<0);
	//bucle for donde permanecera hasta que complete todos los numeros pedidos por el usuario
	for(i=0;i<numero;i++)
	{
		columna = limite_inferior + rand()%(limite_superior_A + 1 - limite_inferior); //obtencion de un numero aleatorio
		fila = limite_inferior + rand()%(limite_superior_B + 1 - limite_inferior);//obtencion de un numero aleatorio
		
		if(matriz[columna-2][fila-2]!=1)//si la posicion -2 (ya que el limite inferior de los numeros aleatorios es 2) es distinta a 1, significa que esta vacia esa zona por lo tanto
		{
			gotoxy(columna,fila);//por lo tanto se posiciona el cursor en ese lugar 
			matriz[columna-2][fila-2]=1;//para despues guardar que en esa posicion de la matriz hay un numero existente (por lo tanto si se vuelve a esta misma posicion, no podra entrar en el if)
			Color(BLACK,RED);
			printf("%c",210);//y por ultimo imprimer en pantalla el simbolo
			Color(BLACK,WHITE);
			continue;
		}
		i--;//si llega hasta aqui, significa que no entro en el if y por lo tanto, la casilla no esta vacia, por ello se resta 1 a la variable i para q no cuente este bucle dentro del for
	}
}

void bloques()
{	
	
	for(i=0;i<19;i++)
	{
		for(j=0;j<79;j++)
		{
			matrizb[j][i]=0;
		}
	}
	
	do
	{
		instruccionesB();
		gotoxy(36,23);
		Color(BLACK,LRED);
		scanf("%i",&numerob);
		Color(BLACK,WHITE);
		
	}while(numerob>100||numerob<0);
	
	for(i=0;i<numerob;i++)
	{
		columna = limite_inferior + rand()%(limite_superior_A + 1 - limite_inferior); 
		fila = limite_inferior + rand()%(limite_superior_B + 1 - limite_inferior);
		
		if(matrizb[columna-2][fila-2]!=1&&matriz[columna-2][fila-2]!=1)
		{
			gotoxy(columna,fila);
			matrizb[columna-2][fila-2]=1;
			setlocale(LC_ALL,"C");
			printf("%c",219);
			setlocale(LC_ALL,"SPANISH");
			continue;
		}
		i--;
	}	
	
	puntaje=0;
}

void control()
{
	if (kbhit()) 
	{
		pulsado=getch();
        if(pulsado=='w'||pulsado=='W'||pulsado==72)direccion=2; 
        if(pulsado=='s'||pulsado=='S'||pulsado==80)direccion=3;
        if(pulsado=='a'||pulsado=='A'||pulsado==75)direccion=1;
        if(pulsado=='d'||pulsado=='D'||pulsado==77)direccion=0;
        if(pulsado==27)
			{
				salir=true;
			}
    }
}
void muerte()
{
	gotoxy(lado,altura);
	setlocale(LC_ALL,"C");
	Color(BLACK,YELLOW);
	printf("%c",178);
	Sleep(300);
	gotoxy(lado,altura);
	printf("%c",177);
	Sleep(300);
	gotoxy(lado,altura);
	printf("%c",176);
	Sleep(300);
	setlocale(LC_ALL,"SPANISH");
	gotoxy(lado,altura);
	printf(" ");
	Color(BLACK,WHITE);
	Sleep(500);
}
void comer()
{
	if(matriz[lado-2][altura-2]==1)
	{
		matriz[lado-2][altura-2]=0;
		puntaje+=1;
		comer_sonido();
		longitud+=1;
	}
	if(matrizb[lado-2][altura-2]==1)
	{
		salir=true;
		muerte_sonido();
		muerte();
	}
		Color(BLACK,LBLUE);
		gotoxy(4,23);printf("\t\t-Puntos: %i\t\t\t-Comida total: %i",puntaje,numero);
		Color(BLACK,WHITE);
	
}
void serpiente()
{

		switch(direccion)
		{
			case 0://derecha (+j)
				if(lado+1>=80)
				{
					gotoxy(lado,altura);printf(" ");
					lado=2;
				}else
					{
						gotoxy(lado,altura);printf(" ");
						lado+=1;
					}
				break;
			case 1://izquierda(-j)
				if(lado-1<=2)
				{
					gotoxy(lado,altura);printf(" ");
					lado=79;
				}else
					{
						gotoxy(lado,altura);printf(" ");
						lado-=1;
					}break;
			case 2://arriba(-i)
				if(altura-1<=1)
				{
					gotoxy(lado,altura);printf(" ");
					altura=19;
				}else
					{
						gotoxy(lado,altura);printf(" ");
						altura-=1;
					}break;
			default://abajo(+i)
				if(altura+1>=20)
				{
					gotoxy(lado,altura);printf(" ");
					altura=2;
				}else
					{
						gotoxy(lado,altura);printf(" ");
						altura+=1;
					}break;
		}
		
		Color(BLACK,GREEN);
		for(i=longitud-1;i>0;i--)
	    {
	        cola[i][0]=cola[i-1][0];
	        cola[i][1]=cola[i-1][1];
	    }
		cola[0][0]=lado;
   		cola[0][1]=altura;
		for(i=0;i<longitud;i++)
	    {
	        if(i==0)
	        {
	            gotoxy(cola[i][0],cola[i][1]);
	            if(abierto==true)
				{
					abierto=false;
					gotoxy(lado,altura);printf("C");
				}else
					{
						abierto=true;
						gotoxy(lado,altura);printf("O");
					}
	        }
	        else
		        {
		            gotoxy(cola[i][0],cola[i][1]);
		            printf("o");
		        }
		}
		gotoxy(cola[longitud-1][0],cola[longitud-1][1]);
		printf(" ");
		
		movimiento_sonido();
		Color(BLACK,WHITE);
		Sleep(150);
	
}
void continuar()
{
	
	do//bucle do while donde siempre entra la primera vez
		{
			Color(BLACK,GREEN);
			gotoxy(4,23);printf("\tQuieres continuar(S/N):  ");//se pregunta al usuario si quiere continuar
			Color(BLACK,WHITE);
			scanf("%s",&continua);//se obtiene una respuesta
			system("CLS");
			
		}while(toupper(continua)!='S'&& toupper(continua)!='N');//se quedara en el bucle siempre que no responda correctamente a la pregunta con una s o una n como se pide
		
		if(toupper(continua)=='S')
		{
			lado=40;
			altura=12;
			direccion=0;
			puntaje=0;
		}
}
//PERDIDO
/////////
void lluvia()
{
	int j;
	int q=0;
	setlocale(LC_ALL,"C");
	for(j=2;j<80;j++)
	{
		Color(BLACK,GREEN);
		gotoxy(j,20);printf("%c",205);
		Color(BLACK,WHITE);
	}
	for(j=2;j<80;j++)
	{
		gotoxy(j,2);printf("%c",178);
	}
	for(j=2;j<80;j++)
	{
		gotoxy(j,3);printf("%c",176);
	}
	setlocale (LC_ALL,"Spanish");
	gotoxy(40,18);printf("RIP");
	gotoxy(43,18);printf("|");
	gotoxy(39,18);printf("|");
	gotoxy(43,19);printf("|");
	gotoxy(39,19);printf("|");
	gotoxy(43,20);printf("|");
	gotoxy(39,20);printf("|");
	gotoxy(40,17);printf("-");
	gotoxy(41,17);printf("-");
	gotoxy(42,17);printf("-");
	for(q=4;q<25;q++)
	{
		if(q%2==1)
		{
			for(j=1;j<80;)
			{  Color(BLACK,BLUE);
				gotoxy(j,q);printf("/");
				Color(BLACK,WHITE);
				j+=4;  
			}	
		}

	}
}
void lluviaB()
{
	int j;
	int q;
	setlocale(LC_ALL,"C");
	for(j=2;j<80;j++)
	{
		Color(BLACK,GREEN);
		gotoxy(j,20);printf("%c",205);
		Color(BLACK,WHITE);
	}
	for(j=2;j<80;j++)
	{
		gotoxy(j,2);printf("%c",178);
	}
	for(j=2;j<80;j++)
	{
		gotoxy(j,3);printf("%c",176);
	}
	setlocale (LC_ALL,"Spanish");
	gotoxy(40,18);printf("RIP");
	gotoxy(43,18);printf("|");
	gotoxy(39,18);printf("|");
	gotoxy(43,19);printf("|");
	gotoxy(39,19);printf("|");
	gotoxy(43,20);printf("|");
	gotoxy(39,20);printf("|");
	gotoxy(40,17);printf("-");
	gotoxy(41,17);printf("-");
	gotoxy(42,17);printf("-");
	for(q=4;q<25;q++)
	{
		if(q%2!=1)
		{
			for(j=2;j<80;)
			{  Color(BLACK,BLUE);
				gotoxy(j,q);printf("/");
				Color(BLACK,WHITE);
				j+=4;  
			}	
		}
	}
}
void perdido()
{
	int i,e=0;
	while(!_kbhit())
	{
		
		lluvia();
		Color(BLACK,LBLUE);
		gotoxy(4,23);printf("\t\t-Puntos: %i\t\t\t-Comida total: %i",puntaje,numero);
		Color(BLACK,WHITE);
		gotoxy(20,20);
		printf(" HAS TARDADO UN TIEMPO DE %i SEGUNDOS ",tiempo);
		Sleep(100);
		system("CLS");
		lluviaB();
		Color(BLACK,LBLUE);
		gotoxy(4,23);printf("\t\t-Puntos: %i\t\t\t-Comida total: %i",puntaje,numero);
		Color(BLACK,WHITE);
		gotoxy(20,20);
		printf(" HAS TARDADO UN TIEMPO DE %i SEGUNDOS ",tiempo);
		Sleep(100);
		system("CLS");
		
	}
	getch();
}
void pantalla_inicio()
{
	intro_sonido();
	while(!_kbhit())
	{
		Color(BLACK,GREEN);
		gotoxy(14,22);printf("PULSA CUALQUIER TECLA PARA COMENZAR LA PARTIDA");
		gotoxy(14,7);printf ("****    ***    ***   *   *   ***   ****    *   *");
		Sleep(100);
		gotoxy(14,8);printf ("*   *  *   *  *   *  *   *  *   *  *   *   ** **");
		Sleep(100);
		gotoxy(14,9);printf ("****   *****  *      *   *  *   *  ****    * * *");
		Sleep(100);
		gotoxy(14,10);printf("*      *   *  *   *  * * *  *   *  *   *   *   *");
		Sleep(100);
		gotoxy(14,11);printf("*      *   *   ***   ** **   ***   *    *  *   *");
		Sleep(500);
		Color(BLACK,RED);
		gotoxy(14,22);printf("PULSA CUALQUIER TECLA PARA COMENZAR LA PARTIDA");
		gotoxy(14,7);printf ("                                                ");
		Sleep(100);
		gotoxy(14,8);printf ("                                                ");
		Sleep(100);
		gotoxy(14,9);printf ("                                                ");
		Sleep(100);
		gotoxy(14,10);printf("                                                ");
		Sleep(100);
		gotoxy(14,11);printf("                                                ");
		Sleep(100);
	}
	Color(BLACK,WHITE);
	getch();
	
	
}

void pantalla_final()
{
	gotoxy(20,20);
	printf(" HAS TARDADO UN TIEMPO DE %i SEGUNDOS ",tiempo);
	while(!_kbhit())
	{
		Color(BLACK,RED);
		gotoxy(14,7);printf(" ****   ***   *   *  *****     ***  *   *  *****  **** ");
		gotoxy(14,8);printf("*      *   *  ** **  *        *   * *   *  *      *   *");
		gotoxy(14,9);printf("*  **  *****  * * *  ***      *   * *   *  ***    ****");
		gotoxy(14,10);printf("*   *  *   *  *   *  *        *   *  * *   *      *   *");
		gotoxy(14,11);printf(" ***   *   *  *   *  *****     ***    *    *****  *    *");
		Sleep(500);
		Color(BLACK,WHITE);
		gotoxy(14,7);printf(" ****   ***   *   *  *****     ***  *   *  *****  **** ");
		gotoxy(14,8);printf("*      *   *  ** **  *        *   * *   *  *      *   *");
		gotoxy(14,9);printf("*  **  *****  * * *  ***      *   * *   *  ***    ****");
		gotoxy(14,10);printf("*   *  *   *  *   *  *        *   *  * *   *      *   *");
		gotoxy(14,11);printf(" ***   *   *  *   *  *****     ***    *    *****  *    *");
		Sleep(500);
	}
	getch();
}


/////////////////////
//PROGRAMA PRINCIPAL/
/////////////////////
int main()
{
    setlocale(LC_ALL,"C");        //Establecemos por defecto la tabla de caracteres en ingles para usar los caracteres de dibujo    
   
    AjustarVentana(85,25);    //Ajustamos el tamaño de la ventana de la consola (modificar según necesidad)
    OcultarCursor();        //Ocultamos el cursor parpadeante, queda muy feo que se vea    
   
   
    setlocale (LC_ALL,"Spanish");
   
    //variables//
    ////////////
	

	srand(time(NULL));//funcion para obtener un numero aleatorio (cambio de semilla entre ejecuciones)
	
	//incio de codigo//
	//////////////////
	PintarMarco();
	pantalla_inicio();
	while(toupper(continua)!='N')
	{
		limpiarA();
		bloques();
		comida();
		tiempo_inicio();
		PintarMarco();
		inicio_sonido();
		limpiarB();
		while(puntaje<numero&&salir==false)
		{
			serpiente();
			comer();
			control();
		}
		salir=false;
		sonido_final();
		tiempo_final();
		limpiarA();
		if(puntaje>=numero)
		{
			pantalla_final();
		}else
			{
				perdido();
			}
		PintarMarco();
		limpiarB();
		limpiarA();
		continuar();
		if(toupper(continua)=='S')
		{
			intro_sonido();
			PintarMarco();
		}
			
	}
    /* FIN CODIGO */
   
    MostrarCursor();//Reactivamos la visibilidad del cursor parpadeante
    return 0;
}