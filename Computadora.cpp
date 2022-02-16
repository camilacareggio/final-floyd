#include "Computadora.h"

Computadora::Computadora(int nro_pc, int nro_router){
    this->nro_pc=nro_pc;
    this->nro_router=nro_router;
    ip = bitset<4>(this->nro_pc).to_string();
    cout<<"PC nro: "<<this->nro_pc<<" con ip: "<<this->ip<<endl;
};

int Computadora::get_nro_pc(){
    return this->nro_pc;
};

void Computadora::recibir_pag(Pagina* pagina){
    cout<<"PAGINA RECIBIDA ID: "<<pagina->obtener_id()<<" en PC nro "<<this->nro_pc<<" Router nro "<<this->nro_router<<endl;
    cout<<"Viene desde PC nro "<<pagina->obtener_ip_origen_pc()<<" Router nro "<<pagina->obtener_ip_origen()<<" de tamanio "<<pagina->obtener_tamanio()<<endl<<endl;
};