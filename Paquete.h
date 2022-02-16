#ifndef PAQUETE_H
#define PAQUETE_H
#include <iostream>
#include <vector>

using namespace std;

class Paquete
{
    private:
        int ip_origen; // ip router origen
        int ip_destino; // ip router destino
        int ip_origen_pc;
        int ip_destino_pc;
        int id_pagina;
        int nro_orden; // orden del paquete
        int tamanio_pag;
    public:
        Paquete(int ip_origen, int ip_destino, int id_pagina, int nro_orden, int tamanio_pag, int ip_origen_pc,int ip_destino_pc);
        ~Paquete();
        int obtener_ip_origen();
        int obtener_ip_destino();
        int obtener_ip_origen_pc();
        int obtener_ip_destino_pc();
        int obtener_id_pagina();
        int obtener_nro_orden();
        int obtener_tamanio_pag();
};

#endif