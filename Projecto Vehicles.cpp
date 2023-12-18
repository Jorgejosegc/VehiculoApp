#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <string.h>
#include <windows.h>
#define max 20       
#define dolar 270000
#define Actualidad 2020
using namespace std; 


void gotoxy(int x, int y) {
COORD coord;
coord.X = x;
coord.Y = y;
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

struct vehi{
	char marca[25], modelo[25], color[25], serial[25];
  	long int ano; 
	double precio;
}vehiculo;

void Menu();  
int busqueda(char serial[25]);
long int FechaValida(char seri2[25],char marca[25], char modelo[25]);
void incluir();     // (1)
void consultar ();  // (2)
void modificar();   // (3)
void eliminar();    // (4)
void modelo();      // (5)
void barato();      // (6)
void antiguo();     // (7)

int main()
{
	system("COLOR f0");
	Menu();
}

void Menu()
{  
	char sel;
	do
	{	
		system("cls");
		            printf("=====================");
		gotoxy(1,1);printf("ORIENTE CARS C.A.");
		gotoxy(0,2);printf("==================");
	 	gotoxy(25,4);printf(".....REGISTRO DE AUTOMOVILES.....");
	 	gotoxy(25,5);printf("=================================");
	 	gotoxy(20,8);printf("1.- Incluir Vehiculo");
	 	gotoxy(20,10);printf("2.- Consultar Datos del Vehiculo");
	 	gotoxy(20,12);printf("3.- Modificar Vehiculo en el Registro");
	 	gotoxy(20,14);printf("4.- Eliminar Vehiculo del Registros");
	 	gotoxy(20,16);printf("5.- Reporte por Modelo ");
	 	gotoxy(20,18);printf("6.- Reporte Barato x Marca");
	 	gotoxy(20,20);printf("7.- Mas Antiguo"); 		
 		gotoxy(20,22);printf("0.- Salida");
	 	gotoxy(57,24);printf("Seleccion = ");
		sel=getchar();	
		system("cls");
	
		switch (sel)
		{
			case '1':{incluir(); break;}
			case '2':{consultar (); break;}
			case '3':{modificar(); break;}
			case '4':{eliminar(); break;}
			case '5':{modelo();	break;}
			case '6':{barato();break;}
			case '7':{antiguo(); break;}
		}
			
	}while(sel!='0');
}

void incluir()      // (1)
{
    int valor, aux=1;
    char seri2[25], op;
     
	do{system("cls"); 
	
        gotoxy(28,2);puts(".....INCLUIR VEHICULO.....");
        gotoxy(28,3);puts("==========================");
        gotoxy(20,7);printf("Ingrese serial del motor         = ");cin>>seri2;
        
        valor=busqueda(seri2);
        
		if(valor==0){
					strcpy(vehiculo.serial,seri2);
            
					gotoxy(20,9);printf("Ingrese la marca del vehiculo    = ");cin>>vehiculo.marca;
            		gotoxy(20,11);printf("Ingrese el modelo del vehiculo   = ");cin>>vehiculo.modelo;
            		fflush(stdin);            		
        			gotoxy(20,13);printf("Ingrese el ano del vehiculo      = ");vehiculo.ano=FechaValida(seri2,vehiculo.marca,vehiculo.modelo);
					gotoxy(20,15);printf("Ingrese color del vehiculo       = ");cin>>vehiculo.color;
            		gotoxy(20,17);printf("Ingrese el precio del vehiculo $ = ");cin>>vehiculo.precio; 
                         
            		FILE *arch1; 
            		arch1=fopen("vehiculo.dat", "at+");
     				fwrite(&vehiculo, sizeof(vehiculo),1,arch1);
     				fclose(arch1);
                  
           			gotoxy(26,21);printf(">>>> VEHICULO REGISTRADO <<<<");
					aux=1;
					gotoxy(58,24);printf("ENTER PARA SALIR >>>>");	 
					getch();
					}
        else{
					gotoxy(26,12);puts(">>>>VEHICULO YA REGISTRADO<<<<");
        			gotoxy(1,20);printf("Presione (i) para intentar nuevamente >>>");
        			gotoxy(1,21);printf("Presione (s) para volver al Menu      >>>");
        			gotoxy(57,23);printf("Seleccion = ");
					cin>>op;
        			if(op=='i'||op=='I')aux=0;
					if(op=='s'||op=='S')aux=1;
			}
        
	}while(aux!=1);
	
     
}    

void consultar ()   // (2)
{
	int valor, aux;
    char seri2[25], op;
    
	do{system("cls");
		
    	gotoxy(22,2);puts(".....CONSULTA DATOS DEL VEHICULOS.....");
    	gotoxy(22,3);puts("======================================");
    	gotoxy(25,6);printf("Ingrese Serial del Motor = ");
    	cin>>seri2;
    	valor=busqueda(seri2);
    	if(valor==1) { 
                     gotoxy(32,9);printf("MARCA ----> %s", vehiculo.marca);
                     gotoxy(32,11);printf("MODELO ---> %s", vehiculo.modelo);
                     gotoxy(32,13);printf("ANO ------> %ld", vehiculo.ano);
                     gotoxy(32,15);printf("COLOR ----> %s", vehiculo.color);
                     gotoxy(32,17);printf("PRECIO ---> %.2lf\n", vehiculo.precio);
                     aux=1;
                     gotoxy(58,24);printf("ENTER PARA SALIR >>>>");
					 getch();

    	} 
    	else{
					gotoxy(24,12);puts(">>>> VEHICULO NO REGISTRADO <<<<");
					gotoxy(1,20);printf("Presione (i) para intentar nuevamente >>>");
        			gotoxy(1,21);printf("Presione (s) para volver al Menu      >>>");
        			gotoxy(57,23);printf("Seleccion = ");
					cin>>op;
        			if(op=='i'||op=='I')aux=0;
					if(op=='s'||op=='S')aux=1;
			}
  
    }while(aux!=1);
}

void modificar()    // (3)              
{
	char serial[25], op,serialN[25];
  	int valor,i, aux, band; 	
	
	do{system("cls");
		gotoxy(22,2);puts(".....MODIFICAR DATOS DEL VEHICULOS.....");
    	gotoxy(22,3);puts("=======================================");  
  	
		gotoxy(12,6);printf("Ingrese el serial del Vehiculo que se va a editar = ");
		scanf("%s",serial);
		valor=busqueda(serial);
		if (valor==1)
		{
			FILE *arch1;
			arch1 =fopen("vehiculo.dat","r");
			FILE *arch2;
			arch2 =fopen("temp.dat","at+");
   			while ( (fread(&vehiculo,sizeof(vehiculo),1,arch1)==1) )
			{
				if (strcmp(vehiculo.serial,serial)==0)
				{  
					gotoxy(20,9);printf("Ingrese nuevo serial del motor      = ");
											do{
												gotoxy(58,9);cin>>serialN;
												band=busqueda(serialN);
												if(strcmp(serialN,serial)==0)band=0;
												if(band==1)
												{
													gotoxy(27,15);printf(">>>> SERIAL YA REGISTRADO <<<<");
													getch();
													system("cls");
													gotoxy(22,2);puts(".....MODIFICAR DATOS DEL VEHICULOS.....");
						   							gotoxy(22,3);puts("=======================================");  
													gotoxy(12,6);printf("Ingrese el serial del Vehiculo que se va a editar = %s",serial);
													gotoxy(20,9);printf("Ingrese nuevo serial del motor      = ");  	
												}	
											}while(band==1);
											strcpy(vehiculo.serial,serialN);		
					
					gotoxy(20,11);printf("Ingrese nueva marca del vehiculo    = ");cin>>vehiculo.marca;
      				gotoxy(20,13);printf("Ingrese nuevo modelo del vehiculo   = ");cin>>vehiculo.modelo;
      				gotoxy(20,15);printf("Ingrese nuevo ano del vehiculo      = ");cin>>vehiculo.ano;
      				gotoxy(20,17);printf("Ingrese nuevo color del vehiculo    = ");cin>>vehiculo.color;
      				gotoxy(20,19);printf("Ingrese nuevo precio del vehiculo $ = ");cin>>vehiculo.precio;
    			}
				fwrite(&vehiculo,sizeof(vehiculo),1,arch2);
  			}
  			fclose(arch1);
 	 		fclose(arch2);
  			remove("vehiculo.dat");
			rename("temp.dat","vehiculo.dat");
  			gotoxy(27,22);printf(">>>> REGISTRO MODIFICADO <<<<");
  			aux=1;
  			gotoxy(58,25);printf("ENTER PARA SALIR >>>>");
  			getch();
  		}
		else{
					gotoxy(26,12);printf(">>>> SERIAL NO ENCONTRADO <<<<");
					gotoxy(1,20);printf("Presione (i) para intentar nuevamente >>>");
        			gotoxy(1,21);printf("Presione (s) para volver al Menu      >>>");
        			gotoxy(57,23);printf("Seleccion = ");
					cin>>op;
        			if(op=='i'||op=='I')aux=0;
					if(op=='s'||op=='S')aux=1;			
		}
		
	}while(aux!=1);
  
}

void eliminar()     // (4)
{
		
	char serial[25], op,sel;
  	int valor, aux;   
  	
  	do{system("cls");
  		gotoxy(21,2);puts(".....ELIMINAR VEHICULOS DEL REGISTRO.....");
    	gotoxy(21,3);puts("========================================="); 
		
		gotoxy(12,6);printf("Ingrese el serial del Vehiculo que se va a eliminar = ");cin>>serial;
  		valor=busqueda(serial);
  		if (valor==1)
		{
			gotoxy(32,9);printf("MARCA ----> %s", vehiculo.marca);
            gotoxy(32,11);printf("MODELO ---> %s", vehiculo.modelo);
            gotoxy(32,13);printf("ANO ------> %ld", vehiculo.ano);
            gotoxy(32,15);printf("COLOR ----> %s", vehiculo.color);
            gotoxy(32,17);printf("PRECIO ---> %.2lf\n", vehiculo.precio);
            
            gotoxy(28,20);printf("SEGURO QUE DESEA ELIMINAR ?");
            gotoxy(33,22);printf("SI (s)    NO(n)");
            gotoxy(57,23);printf("Seleccion = ");cin>>sel;            
            
            if(sel=='s'||sel=='S')
            {
            	system("cls");
				FILE *arch1;
				arch1 = fopen("vehiculo.dat","r");
    			FILE *arch2;
   		 		arch2 = fopen("temp.dat","at+");
  		
				while ( fread(&vehiculo,sizeof(vehiculo),1,arch1))
				{
   					if (strcmp(vehiculo.serial,serial)!=0)
   		  			fwrite(&vehiculo,sizeof(vehiculo),1,arch2);   
				}
    	  		fclose(arch1);
  				fclose(arch2);
  				remove("vehiculo.dat");
  				rename("temp.dat","vehiculo.dat");
  				gotoxy(21,2);puts(".....ELIMINAR VEHICULOS DEL REGISTRO.....");
    			gotoxy(21,3);puts("========================================="); 
				gotoxy(12,6);printf("Ingrese el serial del Vehiculo que se va a eliminar = %s",serial);
				gotoxy(27,12);printf(">>>> VEHICULO ELIMINADO <<<<");
  				aux=1;
  				gotoxy(58,24);printf("ENTER PARA SALIR >>>>");
  				getch();
  			}
  			
  			if(sel=='n'||sel=='N')
  			{
  				gotoxy(1,24);printf("Presione (i) para intentar nuevamente >>>");
  				gotoxy(1,25);printf("Presione (s) para volver al Menu      >>>");
  				gotoxy(57,23);printf("Seleccion = ");
  				cin>>op;
  				if(op=='i'||op=='I')aux=0;
  				if(op=='s'||op=='S')aux=1;
  			}
  		}
		else{
					gotoxy(26,12);printf(">>>> SERIAL NO ENCONTRADO <<<<");
					gotoxy(1,20);printf("Presione (i) para intentar nuevamente >>>");
        			gotoxy(1,21);printf("Presione (s) para volver al Menu      >>>");
        			gotoxy(57,23);printf("Seleccion = ");
					cin>>op;
        			if(op=='i'||op=='I')aux=0;
					if(op=='s'||op=='S')aux=1;			
		}
	}while(aux!=1);
}

void modelo()       // (5)
{
	int aux=0,cont; double bs, total;
    char mode[25],op;  
	
	do{system("cls");
		gotoxy(27,2);puts("....REPORTE POR MODELO....");
		gotoxy(27,3);puts("==========================");
	    
   	 	gotoxy(20,6);printf("Ingrese Modelo de Vehiculo a buscar = ");
    	cin>>mode;
		cont=0;
		total=0;
    	FILE *arch1;
    	arch1=fopen("vehiculo.dat","r");
    	while(fread(&vehiculo, sizeof(vehi),1, arch1)==1)
		{
			if(strcmp(mode,vehiculo.modelo)==0) 
			{
				bs=vehiculo.precio*dolar;
           	 	printf("\n\n\t\t     SERIAL DEL MOTOR ---> %s", vehiculo.serial); 
           	 	printf("\n\t\t     MARCA --------------> %s", vehiculo.marca);
            	printf("\n\t\t     ANO ----------------> %ld", vehiculo.ano);
            	printf("\n\t\t     PRECIO -------------> %.2lf$ (%.2lf Bolivares)", vehiculo.precio, bs);
            	total=total+bs;
            	cont++;
				aux=1;
			}
		}
		if(aux==1){printf("\n\n\n\t\t\tPRECIO TOTAL >>>> %.2lf Bolivares",total);}
		if(cont==1){gotoxy(58,24);printf("ENTER PARA SALIR >>>>");getch();}
		if(cont>1){printf("\n\n\n\n\t\t\t\t\t\t\t  ENTER PARA SALIR >>>>");getch();}
        fclose(arch1);
        
    	if(aux!=1) {
    				gotoxy(16,12);printf(">>>> NO HAY VEHICULOS DE ESE MODELO <<<<");
					gotoxy(1,20);printf("Presione (i) para intentar nuevamente >>>");
        			gotoxy(1,21);printf("Presione (s) para volver al Menu      >>>");
        			gotoxy(57,23);printf("Seleccion = ");
					cin>>op;
        			if(op=='i'||op=='I')aux=0;
					if(op=='s'||op=='S')aux=1;    		
		}	
	}while(aux!=1);
}

void barato()       // (6)
{
	int aux;
	do{system("cls");
	
		int i=0, band=0, n, cambio;
    	double auxp; long int auxa;
    	char auxs[25], auxm[25], auxc[25], marc[25],op;
     
		FILE *arch1;
    	arch1=fopen("vehiculo.dat", "r");
     
    	struct vehi2 
		{	char serial[25], modelo[25], color[25];
    		double  precio;
        	long int ano;
		}veh[max];
                    
		gotoxy(25,2);puts("....REPORTE BARATO X MARCA....");
		gotoxy(25,3);puts("==============================");     	
		 
		gotoxy(20,6);printf("Ingrese la marca del vehiculo a buscar = ");cin>>marc;
		
    	while(fread(&vehiculo, sizeof(vehiculo),1, arch1)==1)
     	{
        	if(strcmp(marc,vehiculo.marca)==0) {strcpy(veh[i].serial,vehiculo.serial);
                                              	strcpy(veh[i].modelo,vehiculo.modelo);
                                              	strcpy(veh[i].color,vehiculo.color);
                                              	veh[i].ano=vehiculo.ano;
                                              	veh[i].precio=vehiculo.precio;
                                              	i++;
                                              	band=1;}
     	}  
     	n=i;
     	if(band==1) 
		{			 
			do{ 
				cambio=0; for(i=0;i<n;i++)  if(veh[i].precio<veh[i+1].precio) { strcpy(auxs,veh[i].serial);
                                                                             	strcpy(auxm,veh[i].modelo);
                                                                             	strcpy(auxc,veh[i].color);
                                                                             	auxa=veh[i].ano;
                                                                             	auxp=veh[i].precio;
                                                                             	strcpy(veh[i].serial,veh[i+1].serial);
                                                                             	strcpy(veh[i].modelo,veh[i+1].modelo);
                                                                             	strcpy(veh[i].color,veh[i+1].color);
                                                                             	veh[i].ano=veh[i+1].ano;
                                                                             	veh[i].precio=veh[i+1].precio;
                                                                             	strcpy(veh[i+1].serial,auxs);
                                                                             	strcpy(veh[i+1].modelo,auxm);
                                                                             	strcpy(veh[i+1].color,auxc);
                                                                             	veh[i+1].ano=auxa;
                                                                             	veh[i+1].precio=auxp;
                                                                             	cambio=1;} 
            }while(cambio==1);
			
			aux=1;
			for(i=0;i<n;i++) {printf("\n\n\t\t\t     SERIAL ----> %s", veh[i].serial);
							  printf("\n\t\t\t     MODELO ----> %s", veh[i].modelo);
							  printf("\n\t\t\t     ANO -------> %ld", veh[i].ano);
							  printf("\n\t\t\t     COLOR -----> %s", veh[i].color);
							  printf("\n\t\t\t     PRECIO ----> %.2lf\n", veh[i].precio);}
			if(i==1){gotoxy(58,24);printf("ENTER PARA SALIR >>>>");getch();}
			if(i>1){printf("\n\n\n\t\t\t\t\t\t\t  ENTER PARA SALIR >>>>");getch();}
        }	
		if(band!=1){gotoxy(21,12);printf(">>>> NO HAY VEHICULOS DE ESA MARCA <<<<");
					gotoxy(1,20);printf("Presione (i) para intentar nuevamente >>>");
        			gotoxy(1,21);printf("Presione (s) para volver al Menu      >>>");
        			gotoxy(57,23);printf("Seleccion = ");
					cin>>op;
        			if(op=='i'||op=='I')aux=0;
					if(op=='s'||op=='S')aux=1;}
        fclose(arch1);
	}while(aux!=1);
}

void antiguo()      // (7)
{
	int viejo,cont=0;
    double BS;
     
    gotoxy(17,2);puts("......VEHICULO MAS ANTIGUO DEL CONCESIONARIO......"); 
	gotoxy(17,3);puts("==================================================");
    FILE *arch1;
    arch1=fopen("vehiculo.dat","r");
    
    if(fread(&vehiculo, sizeof(vehiculo),1, arch1)==1)
    viejo=vehiculo.ano;

	while(fread(&vehiculo, sizeof(vehiculo),1, arch1)==1)
    {
	    if(vehiculo.ano<viejo) {viejo=vehiculo.ano;}
	}
	fclose(arch1);
	
	arch1=fopen("vehiculo.dat","r");
	while(fread(&vehiculo, sizeof(vehiculo),1, arch1)==1)
	{
		if(vehiculo.ano==viejo)
		{
			BS=vehiculo.precio*dolar;
	 	
			
	 		printf("\n\n\t\t   Serial del motor------> %s ",vehiculo.serial);
	  		printf("\n\t\t   Marca del vehiculo----> %s ",vehiculo.marca);
	 		printf("\n\t\t   Modelo del vehiculo---> %s ",vehiculo.modelo);
			printf("\n\t\t   Ano del vehiculo------> %ld",vehiculo.ano);  
	 		printf("\n\t\t   Color del vehiculo----> %s ",vehiculo.color);
	 		printf("\n\t\t   Precio del vehiculo---> %.2lf$ (%.2lf Bolivares)\n\n",vehiculo.precio,BS); 
	 		cont++;
		}
		
	}
	fclose(arch1);	 
	if(cont==1){gotoxy(58,24);printf("ENTER PARA SALIR >>>>");getch();}
	if(cont>1){printf("\n\n\n\t\t\t\t\t\t\t  ENTER PARA SALIR >>>>");getch();}
}

//>>>>>> FUNCIONES ADICIONALES <<<<<<
//====================================

int busqueda(char serial[25])
{
    int band, re;
    FILE *arch1;
    arch1=fopen("vehiculo.dat", "r");
     
    while((band==0)&&(fread(&vehiculo,sizeof(vehiculo),1, arch1)==1))
    {
    	if(strcmp(vehiculo.serial,serial)==0) { band=1; }
    }
    if(band==0) re=0;
    else re=1;
    fclose(arch1);
    return(re);                         
}

long int FechaValida(char seri2[25],char marca[25], char modelo[25])
{
	double ano;
	do{
		gotoxy(55,13);cin>>ano;
		if(ano>Actualidad)
		{
			gotoxy(29,18);printf(">>>> FECHA INVALIDA <<<<");
			getch();
			system("cls");
    		gotoxy(28,2);puts(".....INCLUIR VEHICULO.....");
    		gotoxy(28,3);puts("==========================");
    		gotoxy(20,7);printf("Ingrese serial del motor         = %s",seri2);	
			gotoxy(20,9);printf("Ingrese la marca del vehiculo    = %s",marca);
			gotoxy(20,11);printf("Ingrese el modelo del vehiculo   = %s",modelo);
			gotoxy(20,13);printf("Ingrese el ano del vehiculo      = "); 
		}
	}while(ano>Actualidad);
	return(ano);
}

