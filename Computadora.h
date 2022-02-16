#ifndef COMPUTADORA_H
#define COMPUTADORA_H
#include <iostream>
#include <string>
#include <bitset>
#include <cstdlib>
#include "Pagina.h"

using namespace std;

/*Terminal conectado a un unico router*/
class Computadora{
    private:
        int nro_pc;
        string ip;
        int nro_router;
    public:
        Computadora(int id, int router_id);
        int get_nro_pc();
        void recibir_pag(Pagina* pagina);
};
#endif