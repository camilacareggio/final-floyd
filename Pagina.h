#ifndef PAGINA_H
#define PAGINA_H
#include <cstdlib>
#include <iostream>
#include "Estructuras.h"

using namespace std;

class Pagina
{
	private:
		int id;// id de la página.
		int tamanio;//tamaño de la página = cantidad de paquetes
		int ip_origen;//ip router origen
		int ip_destino;//ip router destino
		int ip_origen_pc; 
		int ip_destino_pc;
		int paq_recibidos; // paquetes recibidos al reconstruir la pag
		
	public:		
		Pagina(int id, int ip_origen);
		Pagina(int id, int ip_origen, int ip_destino, int tamanio, int ip_origen_pc, int ip_destino_pc);
		~Pagina();
		int obtener_id();
		int obtener_tamanio();
        int obtener_ip_origen();
        int obtener_ip_destino();
		int obtener_ip_origen_pc();
		int obtener_ip_destino_pc();
		int obtener_paq_recibidos();
		void recibir_paquete();
};

#endif