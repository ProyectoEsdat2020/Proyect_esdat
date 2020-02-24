//EL PROGRAMA NECESITA ARCHIVOS PARA QUE 
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <stdio.h>
#include <windows.h>
#include <ctime>
#include <conio.h>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <ctime>
#include <algorithm>
#include <vector>
#include <stdlib.h>

using namespace std;
//reproductor

struct Cancion{
	string nombre;
	string autor;
	string album;
	string genero;
};
struct NodoRepro{
	Cancion dato;
	NodoRepro *sgte;
	NodoRepro *ant;
}*ultimo,*primero;

struct NodoLRepro{
	string dato;
	NodoLRepro *p;
};
struct Nodo{
	int info;
	Nodo *sgte;
};


typedef NodoRepro *PNodoR;
typedef NodoLRepro *PNodoLR;
//FIN-REPDRODUCTOR

typedef Nodo *PNodo;

void menu();
void insertarfinal(PNodo &L, int valor);
void listar(PNodo L);

//REPRODUCTOR
void Spotify();
void insertarF(PNodoLR &, string);
void imprimir(PNodoLR actual);
void insertarcancion(PNodoR &,string,string,string,string) ;
void cancionactual(PNodoR );
void reproductor(PNodoR *&,char );
void muestra_contenido_de(const std::string &a_carpeta);
char opciones();
void menuRepro();	
void cuadro();
void cuadro2();
void cuadro3();
void spot();
//FIN-REPRODUCTOR
//JUEGO_PILAS
void push(PNodo &p, int alt1);
int pop(PNodo &p);
void juego_pilas();
//FIN-JUEGO_PILAS
void pixelinicio();
void pixeliphone();

void gotoxy(int x,int y){  
	HANDLE hcon;  
	hcon = GetStdHandle(STD_OUTPUT_HANDLE);  
	COORD dwPos;  
	dwPos.X = x;  
	dwPos.Y= y;  
	SetConsoleCursorPosition(hcon,dwPos);  
}
//
char x_op;
PNodoR cancion=NULL;
PNodoLR lista=NULL;
int contadorRepro=0;	
//
int main(int argc, char *argv[]) {
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
	PNodo L=NULL;
/*	cout<<"BIENVENIDOS AL SIMULADOR DE CELULAR.."<<endl;*/
	pixelinicio();
    pixeliphone();
	gotoxy(2,60);
	system("pause");
	menu();
	return 0;
}	

void menu(){
	int op;
	do{
		while(op!=1 && op!=2 && op!=3&& op!=4&& op!=5&& op!=6&&op!=7){cout<<"Ingrese una opcion valida (1-2-3-4-5-6-7):"<<endl;cin>>op;}
		fflush(stdin);
		switch(op) 
		{
		case 1:{
			system("cls");
			Spotify();
		}break;
		case 2:{
			system("cls");
			juego_pilas();
		}break;
		case 3:{
			
		}break;
		case 4:{
		}break;
		case 5:{
		}break;
		case 6:{
		}break;
		case 7:{
		}break;
		}
		system("cls");
	}while(op!=7);
}



void insertarfinal(PNodo &L, int valor){
	PNodo nuevo = new Nodo;
	nuevo->info = valor;
	nuevo->sgte = NULL;
	if(L==NULL){
		L=nuevo;
	}
	else{
		PNodo p=L;
		while(p->sgte!=NULL){
			p=p->sgte;
		}
		p->sgte = nuevo;
	}
}
	
void listar(PNodo L){
	PNodo p=L;
	while(p!=NULL){
		cout<<p->info<<endl;
		p=p->sgte;
	}
}
// REPRODUCTOR
	
void Spotify(){
	int suma ; 
	string nombrec,autorc,albumc,generoc;
	//INGRESO DE DATOS
	char carpeta[] ="C:\\prueba" ;
	gotoxy(55,3);cout<<"LISTA DE CANCIONES\n"<<endl;
	muestra_contenido_de(carpeta);
	cuadro();
	for(int i=1;i<=(contadorRepro-2);i++){
		cuadro2();
		gotoxy(5,4);cout<<"\tINGRESO DE DATOS:"<<endl;
		fflush(stdin);
		gotoxy(5,8);cout<<"Nombre : ";
		nombrec=lista->dato;
		cout<<nombrec<<endl;
		//getline(cin,nombrec);
		lista=lista->p;
		gotoxy(5,10);cout<<"Ingrese autor de cancion "<<i<<":"<<endl;
		gotoxy(5,11);getline(cin,autorc);
		gotoxy(5,13);cout<<"Ingrese album de cancion "<<i<<":"<<endl;
		gotoxy(5,14);getline(cin,albumc);
		gotoxy(5,16);cout<<"Ingrese genero de cancion "<<i<<":"<<endl;
		gotoxy(5,17);getline(cin,generoc);
		insertarcancion(cancion,nombrec,autorc,albumc,generoc);
		system("cls");
	}
	cuadro3();
	// PANTALLA DE CARGA.
	for(int i=1;i<=50;i++)
	{
		Sleep(50);gotoxy(22+i,20);cout<<char(176);
		Sleep(50);gotoxy(22+i,20);cout<<char(177);
		Sleep(50);gotoxy(22+i,20);cout<<char(178);
		Sleep(50);gotoxy(22+i,20);cout<<char(219);
		gotoxy(44,22);cout<<"CARGANDO";
		suma=2*i;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 249);
		gotoxy(46,20);cout<<suma<<"%";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	}
	system("cls");
	if(suma == 100)
	{
		cancionactual(cancion);
		menu();
	}
	else
	{
		exit(0);
	}
	gotoxy(2,28);
}
	
//
void cuadro(){
	for(int i=0;i<74;i++){
		gotoxy(50,2+i/4);cout<<"=";
	}
}
	
void cuadro2(){
	for(int i=0;i<74;i++){
		gotoxy(2+i,2);cout<<"=";
		gotoxy(2,2+i/4);cout<<"=";
		gotoxy(76,2+i/4);cout<<"=";
		gotoxy(3+i,20);cout<<"=";
	}
}
	
void insertarcancion(PNodoR &cancion ,string nombrec,string autorc,string albumc,string generoc){
	
	PNodoR nuevoNodo;
	nuevoNodo = new NodoRepro; 
	nuevoNodo->dato.nombre=nombrec;
	nuevoNodo->dato.autor=autorc;
	nuevoNodo->dato.album=albumc;
	nuevoNodo->dato.genero=generoc;
	
	if(primero == NULL){ 
		primero = nuevoNodo;
		ultimo = nuevoNodo;
		nuevoNodo-> sgte = primero;
		nuevoNodo->ant = ultimo; 
		cancion = nuevoNodo; 
	}  
	else{ 
		ultimo->sgte = nuevoNodo; 
		nuevoNodo->ant=ultimo;
		nuevoNodo->sgte=primero;
		ultimo=nuevoNodo;
		primero->ant=ultimo;
		cancion=primero;
	}	
}
	
void cancionactual(PNodoR cancion){
	
	const string ubicacion="C:\\prueba\\";
	
	std::string ubic = ubicacion + (cancion->dato.nombre);
	
	system(ubic.c_str());
	
	system("cls");
	gotoxy(25,17);cout<<"CANCION ACTUAL: "<<endl;
	gotoxy(25,19);cout<<"NOMBRE: "<<cancion->dato.nombre<<endl;
	gotoxy(25,20);cout<<"AUTOR: "<<cancion->dato.autor<<endl;
	gotoxy(25,21);cout<<"ALBUM: "<<cancion->dato.album<<endl;
	gotoxy(25,22);cout<<"GENERO: "<<cancion->dato.genero<<endl;
}
void reproductor(PNodoR &cancion,char sas){
	fflush(stdin);
	switch(sas) {
	case 's' :{//siguiente
		cancion = cancion->sgte; 
		cancionactual(cancion);
		menuRepro();
	}
		break;
	case 'S' :{//siguiente
		cancion = cancion->sgte; 
		cancionactual(cancion);
		menuRepro();
	}
		break;
	case 'a' :{ //atras*/
		cancion = cancion->ant; 
		cancionactual(cancion); 
		menuRepro();
	}
		break;
	case 'A' :{ //atras*/
		cancion = cancion->ant; 
		cancionactual(cancion); 
		menuRepro();
	}
		break;
	case 'r' :{ //salir
		system("C:\\Users\\Kevin\\Desktop\\T3\\cerrarwm.bat");
	}
	}
}
	
char opciones(){
	char x;
	cuadro3();
	spot();
	gotoxy(25,9);cout<<"SIGUIENTE CANCION   === S"<<endl;
	gotoxy(25,11);cout<<"ANTERIOR CANCION    === A"<<endl;
	gotoxy(25,13);cout<<"SALIR == R"<<endl;
	gotoxy(4,26);cout<<"OPCION :  ";cin>>x;
	while(x!='s' && x!='a' && x!='r' && x!='S' && x!='A' && x!='R'){
		gotoxy(25,22);cout<<"Ingrese una opcion valida (s-a-r):"<<endl;cin>>x;
	}
	return x;
}
	
void menuRepro(){
	x_op = opciones();
	reproductor(cancion,x_op);
}

void cuadro3(){
	for(int k=0;k<74;k++){
		gotoxy(2+k,2);cout<<"=";
		gotoxy(2+k,28);cout<<"=";
	}
	for(int i=0;i<27;i++){
		gotoxy(2,2+i);cout<<"=";
		gotoxy(75,2+i);cout<<"=";
	}
	for(int j=0;j<74;j++){
		gotoxy(2+j,24);cout<<"=";
	}
	for(int m=0;m<22;m++){
		gotoxy(20,2+m);cout<<"=";
	}
}
void spot(){
	gotoxy(10,4);cout<<"###"<<endl;
	gotoxy(10,5);cout<<"#"<<endl;
	gotoxy(10,6);cout<<"###"<<endl;
	gotoxy(10,7);cout<<"  #"<<endl;
	gotoxy(10,8);cout<<"###"<<endl;
	
	gotoxy(10,10);cout<<"###"<<endl;
	gotoxy(10,11);cout<<"# #"<<endl;
	gotoxy(10,12);cout<<"###"<<endl;
	gotoxy(10,13);cout<<"#"<<endl;
	
	gotoxy(10,15);cout<<"###"<<endl;
	gotoxy(10,16);cout<<"# #"<<endl;
	gotoxy(10,17);cout<<"# #"<<endl;
	gotoxy(10,18);cout<<"###"<<endl;
	
	gotoxy(10,20);cout<<"###"<<endl;
	gotoxy(10,21);cout<<" # "<<endl;
	gotoxy(10,22);cout<<" # "<<endl;
	gotoxy(10,23);cout<<" # "<<endl;
}
void muestra_contenido_de(const std::string &a_carpeta){
	
	WIN32_FIND_DATA ffd{};
	
	//inicio
	if (auto handle = FindFirstFile((a_carpeta + "/*.*").c_str(), &ffd)){
		do {
			if(contadorRepro>1){
				gotoxy(55,contadorRepro+4);
				std::cout << ffd.cFileName << '\n';
				insertarF(lista,ffd.cFileName);
			}
			contadorRepro++;
		}while (FindNextFile(handle, &ffd) != 0);
	}				//fin
}
	
void insertarF(PNodoLR &lista, string valor){
	PNodoLR ultimo = new NodoLRepro;
	PNodoLR nuevoNodo = new NodoLRepro;
	nuevoNodo->dato=valor;
	nuevoNodo->p=NULL;
	if (lista == NULL){
		lista=nuevoNodo;
	}else{
		ultimo=lista;
		
		while(ultimo->p!=NULL){
			ultimo = ultimo->p;
		}
		
		ultimo->p=nuevoNodo;
	}
}
//FIN-reproductor
	
//juego_pilas
void juego_pilas(){
	PNodo p=NULL;
	int n,op1,i,j,alt1,intento,carta,correcto=0,incorrecto=0;
	srand((unsigned)time(NULL));
	cout<<"ADIVINA - LA - CARTA"<<endl;
	cout<<"_-_-_-_-_-_-_-_-_-_-_"<<endl<<endl;
	cout<<"~Este juego consiste en adivinar el simbolo de la carta que esta primera en el mazo~"<<endl;
	cout<<"~si aciertas la mayoria de las 10 primeras cartas que salgan ganste~"<<endl<<endl;
	do{
		cout<<"elija dificultad :"<<endl;
		cout<<"(1)--------------->EASY"<<endl;
		cout<<"(2)--------------->NORMAL"<<endl;
		cout<<"(3)--------------->HARD"<<endl;
		cin>>op1;
		if(op1==1)
			n=10;
		if(op1==2)
			n=20;
		if(op1==3)
			n=30;
		else
			cout<<"ingrese una dificultad valida"<<endl;
	}while(op1>=4);
	for(i=0;i<n;i++){
		alt1=rand()%5;
		push(p,alt1);
	}
	system("cls");
	for(j=0;j<10;j++){
		do{
			cout<<"ingrese el intento "<<j+1<<" :"<<endl;
			cout<<"1->(trebol)"<<endl;
			cout<<"2->(corazon)"<<endl;
			cout<<"3->(diamante)"<<endl;
			cout<<"4->(espada)"<<endl;
			cin>>intento;
		}while(intento>=5);
		carta=pop(p);
		if(intento==carta){
			cout<<"CORRECTO"<<endl;
			correcto++;
		}
		else{
			cout<<"INCORRECTO"<<endl;
			incorrecto++;
		}
	}
	system("cls");
	cout<<"RESULTADOS"<<endl;
	cout<<"-_-_-_-_-_"<<endl<<endl;
	cout<<"aciertos :"<<correcto<<endl;
	cout<<"desaciertos:"<<incorrecto<<endl;
	for(int s=0;s<8;s++){
		Sleep(700);
		cout<<"."<<endl;
	}
	if(correcto>incorrecto){
		cout<<"USTED A GANADO";
	}
	else{
		cout<<"USTED A PERDIDO";
	}
}
	
void push(PNodo &p, int alt1){
	PNodo nuevo = new Nodo;
	nuevo->info=alt1;
	nuevo->sgte=p;
	p=nuevo;
}
int pop(PNodo &p){
	int x=p->info;
	PNodo temp=p;
	p=p->sgte;
	delete temp;
	return x;
}
//FIN-juego_pilas
	
void pixeliphone(){
	gotoxy(15,10);cout<<"  ___ ____  _   _  ___  _   _ _____  "<<endl;
	gotoxy(15,11);cout<<"	|_ _|  _ "<<char(92)<<"| | | |/ _ "<<char(92)<<"| "<<char(92)<<" | | ____| "<<endl;
	gotoxy(15,12);cout<<"	 | || |_) | |_| | | | |  "<<char(92)<<"| |  _|   "<<endl;
	gotoxy(15,13);cout<<"	 | ||  __/|  _  | |_| | |"<<char(92)<<"  | |___  "<<endl;
	gotoxy(15,14);cout<<"	|___|_|   |_| |_|"<<char(92)<<"___/|_| "<<char(92)<<"_|_____| "<<endl;
}

void pixelinicio(){
	for(int i=0;i<45;i++){
		gotoxy(10+i,5);cout<<"="<<endl;
	}
	for(int i=0;i<45;i++){
		gotoxy(10+i,54);cout<<"="<<endl;
	}
	for(int i=0;i<50;i++){
		gotoxy(10,5+i);cout<<"="<<endl;
	}
	for(int i=0;i<50;i++){
		gotoxy(55,5+i);cout<<"="<<endl;
	}
	}
