#ifndef ROUTER_H
#define ROUTER_H
#include <iostream>
#include <cstdlib>
#include <bitset>
#include <string>
#include "Estructuras.h"
#include "Pagina.h"
#include "Paquete.h"
#include "Canal.h"
#include "Computadora.h"

using namespace std;

/* Cada router cumple las siguientes funciones:
1- recibir pagina y dividirla en paquetes
2- recibir paquetes de routers vecinos
3- enviar paquetes al canal que corresponda segun la tabla de enrutamiento y segun el ancho de banda permita
4- construir pagina cuando el destino de los paquetes sea el propio router
5- enviar la pagina contruida a la computadora destino*/
class Router
{
	private:
		int nro_router;
		string ip;
		int tabla_enrutamiento[MAXNODOS]; // segun el destino final del paquete, me indica a donde enviarlo
		Lista<Canal*> envios; // canales cuyo origen es este router
		Lista<Canal*> recibos; // canales cuyo destino es este router
		Lista<Pagina*> paginas; // paginas por armarse en este router
		Computadora* pcs[NRO_PC]; // terminales conectados
		int total_total_paquetes(); // cantidad total de paquetes por recibir
		int total_total_paquetes(Lista<Canal*>* can);
		
	public:
		Router(int ip);
		~Router();
		int obtener_nro_router();
		string get_ip();
		int total_paquetes(int destino); // cantidad de paquetes de un canal
		void construir_canales(int destino); // construye canales de envio
		void set_recibos(Canal* canal);	// avisa los canales de recibo
		void set_tabla_enrutamiento(int destino, int enviar_a);
		void print_tabla_enrutamiento();

		void recibir_pagina(Pagina* pag_recibida);
		void recibir();
		void recibir(int tot_inicial, int tot, Lista<Canal*>* m);
		int recibir_paquetes(Canal* canal);
		void enviar_paquete(Paquete* p);

		void mostrar_canales(); // de envio
		void mostrar_canales(Lista<Canal*>* m);
		void mostrar_canales_recibo();
		void mostrar_canales_recibo(Lista<Canal*>* m);
		Canal* buscar_canal(int destino);
		Canal* buscar_canal(int destino, Lista<Canal*>* m);
		void construir_pagina(Paquete* p);
		void construir_pagina(Paquete* p, Lista<Pagina*>* pags);
};

#endif