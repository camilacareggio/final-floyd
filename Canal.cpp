#include "Canal.h"

Canal::Canal(int o, int d){
    this->origen=o;
    this->destino=d;
};

int Canal::get_origen(){
    return this->origen;
};

int Canal::get_destino(){
    return this->destino;
};

int Canal::get_size(){
    return this->conexion.size();
};

Paquete* Canal::get_paquete(){
    return this->conexion.tope();
};

void Canal::sacar_paquete(){
    this->conexion.desencolar();
};

void Canal::reencolar_paquete(){
    this->conexion.reencolar();
};

void Canal::add_paquete(Paquete* p){
    this->conexion.encolar(p);
};

bool Canal::canal_saturado(){
    return (get_size()>=ANCHO_BANDA);
};