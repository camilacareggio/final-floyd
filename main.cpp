#include <iostream>
#include <cstdlib>
#include <fstream>
#include "Estructuras.h"
#include "Pagina.h"
#include "Paquete.h"
#include "Router.h"
#define MIEMBRO   1
#define NO_MIEMBRO 0

using namespace std;

void warshall(int peso[][MAXNODOS], int caminos[][MAXNODOS]);
void Floyd(int peso[][MAXNODOS], int A[][MAXNODOS],int cf[][MAXNODOS]);
void caminoFloyd(int cf[][MAXNODOS], int s, int t, Cola<int>* paradas);
void printMatrix(int C[][MAXNODOS]);
void updateMatrix(int ri, int rd, int m_editar[][MAXNODOS], int paq, int a_banda);

int main(int argc, char *argv[])
{   
    //read matrix
    ifstream myfile;
    myfile.open ("matrix2.txt");
    int mat_adyacencia[MAXNODOS][MAXNODOS];
    for (int i = 0; i < MAXNODOS; i++) {
        for (int j = 0; j < MAXNODOS; j++) {
        myfile >> mat_adyacencia[i][j];
        }
    }

    //imprimir matriz
    cout<<"Matriz de conexiones:"<<endl;
    printMatrix(mat_adyacencia);

    int caminos[MAXNODOS][MAXNODOS];
    int cf[MAXNODOS][MAXNODOS];
    int MatrizFloyd[MAXNODOS][MAXNODOS];
    int *pdist, i, j, precede[MAXNODOS];
    int id_pag=0;

    Router *rt_arr[MAXNODOS]; // Inicializar routers
    for(int i=0; i<MAXNODOS; i++) {
        rt_arr[i] = new Router(i);
    }

    //construir canales de envios
    for(int j=0; j<MAXNODOS; j++){
        for(int i=0; i<MAXNODOS; i++){
            if(mat_adyacencia[j][i]==1){
                rt_arr[j]->construir_canales(i);
            }
        }
        cout<<"CANALES DE ENVIO DEL ROUTER "<<rt_arr[j]->get_ip()<<endl;
        rt_arr[j]->mostrar_canales();
    }

    //canales de recibos
    for(int j=0; j<MAXNODOS; j++){
        rt_arr[j]->set_recibos(new Canal(j, j));
        for(int i=0; i<MAXNODOS; i++){
            if(mat_adyacencia[j][i]==1){
                rt_arr[j]->set_recibos(rt_arr[i]->buscar_canal(j));
            }
        }
        //cout<<"CANALES DE RECIBO DEL ROUTER "<<rt_arr[j]->get_ip()<<endl;
        //rt_arr[j]->mostrar_canales_recibo();
    }

    //Set cantidad de ciclos a simular
    int CICLOS_MAX;
    cout<<endl;
    cout<<"CANTIDAD DE CICLOS A SIMULAR: ";
    cin>>CICLOS_MAX;
    
    warshall(mat_adyacencia,caminos);
    
    //Simulación de ciclos
    for(int ciclo=0; ciclo<CICLOS_MAX; ciclo++){
        // En el primer ciclo y cada 2 ciclos se actualiza la matriz de adyacencia y se recalcula Floyd
        if(ciclo==0 || ciclo%2==0){
            for(int in=0; in<MAXNODOS; in++){
                for(int out=0; out<MAXNODOS; out++){
                    if(mat_adyacencia[in][out]>0 && mat_adyacencia[in][out]<INFI){               
                        updateMatrix(in, out, mat_adyacencia, rt_arr[in]->total_paquetes(out), ANCHO_BANDA);
                    }
                }
            }
            cout<<"Matriz de adyacencia para el ciclo "<<ciclo<<endl;
            printMatrix(mat_adyacencia);
            // calcular Floyd para todos los caminos posibles y armar tablas de enrutamiento
            for(int s=0; s<MAXNODOS; s++){
                for(int t=0; t<MAXNODOS; t++){
                    // router de inicio s; router final t

                    
                    Cola<int>* paradas=new Cola<int>(); 

                    if(caminos[s][t]==1){
                        Floyd(mat_adyacencia,MatrizFloyd,cf);                        
                        caminoFloyd(cf,s,t, paradas);
                    }
                    else{
                        cout<<"\n NO HAY CAMINO POSIBLE ENTRE s= "
                            <<s<<" y t= "<<t<<endl;
                        
                    }
                    //cout<<"PROX NODO:"<<paradas->tope() <<" DESTINO "<<t<<endl;
                    if(paradas->esvacia()){
                        rt_arr[s]->set_tabla_enrutamiento(t, t);
                    }
                    else{
                        rt_arr[s]->set_tabla_enrutamiento(t, paradas->tope());
                    }
                    delete paradas;
                }
                rt_arr[s]->print_tabla_enrutamiento();
            }
        }
        // En cada ciclo, por turnos, todos los routers reciben y envian paquetes
        for(int rout=0; rout<MAXNODOS; rout++){
            // En el primer ciclo y cada 5 ciclos, se crean paginas en cada router
            if(ciclo==0 || ciclo%5==0){ //VER
                rt_arr[rout]->recibir_pagina(new Pagina(id_pag, rout));
                id_pag++;
            }
            rt_arr[rout]->recibir();
            //rt_arr[rout]->mostrar_canales();
            //rt_arr[rout]->mostrar_canales_recibo();
        }
        system("PAUSE");
    }
    
    
    cout<<endl<<endl<<endl;
    system("PAUSE");
    return EXIT_SUCCESS;
}

//------------------------------- Funciones --------------------------------------------------------------------------------------------------------------------------------------

// Warshall detecta si hay camino posible
void warshall(int peso[][MAXNODOS], int caminos[][MAXNODOS]) // matriz de adyacencia y de caminos
{ int i,j,k;
//inicializo caminos haciendola igual a la adjunta impl�cita en peso  
  for(i=0;i<MAXNODOS;i++){
         for(j=0;j<MAXNODOS;j++){
                if(peso[i][j]==INFI)caminos[i][j]=0; //si es inf, pongo el camino en 0 xq no hay
                else                caminos[i][j]=1; // hay camino
         }
  }
  
  for(k=0;k<MAXNODOS;k++){
         for(i=0;i<MAXNODOS;i++){
                for(j=0;j<MAXNODOS;j++){                 
                                if(caminos[i][j]==0) // si no hay camino entre i y j
                                   caminos[i][j]=caminos[i][k]&&caminos[k][j]; // veo si hay camino pasando por k
                }
         }
  }
}//fin warshall     

// si hay camino, Floyd calcula las distancias menores de todos los nodos a todos
void Floyd(int peso[][MAXNODOS], int A[][MAXNODOS], int cf[][MAXNODOS])
{ int i,j,k;
  for(i=0;i<MAXNODOS;i++){
         for(j=0;j<MAXNODOS;j++){
                                 A[i][j]=peso[i][j]; cf[i][j]=-1;
         }
  }
  for(i=0;i<MAXNODOS;i++) A[i][i]=0;
  
  for(k=0;k<MAXNODOS;k++){
      for(i=0;i<MAXNODOS;i++){
         for(j=0;j<MAXNODOS;j++){
                                 if((A[i][k]+ A[k][j])< A[i][j]){ // veo cual es el menor camino: pasando por k o no
                                              A[i][j]= A[i][k]+ A[k][j]; // reemplazo si es menor
                                              cf[i][j]=k; // guardo nodo intermedio
                                 }
         }
      }
  }

  // imprimo floyd
    /*cout<<"\n FLOYD ------------------------\n";    
    for(i=0;i<MAXNODOS;i++){
           cout<<"\n";                 
           for(j=0;j<MAXNODOS;j++){
                  printf(" %5i",A[i][j]);                 
           }                 
    }
    cout<<endl;
    system("PAUSE");*/
     
}

void caminoFloyd(int cf[][MAXNODOS], int s, int t, Cola<int>* paradas){
    int k;
    k=cf[s][t];
    if (k!=-1){
        caminoFloyd(cf,s,k, paradas);
        paradas->encolar(k);
        caminoFloyd(cf,k,t, paradas);
    }
}

void printMatrix(int C[][MAXNODOS]){
    for(int i=0;i<MAXNODOS;i++){
           cout<<"\n";                 
           for(int j=0;j<MAXNODOS;j++){
                  printf(" %5i",C[i][j]);                 
           }                 
    }
    cout<<endl<<endl;
}

void updateMatrix(int ri, int rd, int m_editar[][MAXNODOS], int paq, int a_banda){
       m_editar[ri][rd]=paq+1;
}