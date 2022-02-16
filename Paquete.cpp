#include "Paquete.h"

Paquete::Paquete(int ip_origen, int ip_destino, int id_pagina, int nro_orden, int tamanio_pag, int ip_origen_pc,int ip_destino_pc){
    this->ip_origen=ip_origen;
    this->ip_destino=ip_destino;
    this->id_pagina=id_pagina;
    this->nro_orden=nro_orden;
    this->tamanio_pag=tamanio_pag;
    this->ip_origen_pc=ip_origen_pc;
    this->ip_destino_pc=ip_destino_pc;
};

Paquete::~Paquete(){
};

int Paquete::obtener_ip_origen(){
    return this->ip_origen;
};

int Paquete::obtener_ip_destino(){
    return this->ip_destino;
};

int Paquete::obtener_ip_origen_pc(){
    return this->ip_origen_pc;
}

int Paquete::obtener_ip_destino_pc(){
    return this->ip_destino_pc;
};

int Paquete::obtener_id_pagina(){
    return this->id_pagina;
};

int Paquete::obtener_nro_orden(){
    return this->nro_orden;
};

int Paquete::obtener_tamanio_pag(){
    return this->tamanio_pag;
};