#ifndef CANAL_H
#define CANAL_H
#include <cstdlib>
#include <iostream>
#include <sstream>
#include "Estructuras.h"
#include "Paquete.h"

using namespace std;

/*Es la conexion entre los routers vecinos, contiene una cola con
los paquetes que se mandan por ese camino*/
class Canal{
    private:
        int origen;
        int destino;
        Cola<Paquete*> conexion;
    public:
        Canal(int o, int d);
        ~Canal();
        int get_origen();
        int get_destino();
        int get_size();
        Paquete* get_paquete();
        void sacar_paquete();
        void reencolar_paquete();
        void add_paquete(Paquete* p);
        bool canal_saturado();
};

#endif