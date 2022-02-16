#include "Pagina.h"

Pagina::Pagina(int id, int ip_origen){
	this->id=id;
	this->tamanio=rand() % (ANCHO_BANDA*2);
	this->ip_origen=ip_origen;
	this->ip_destino=rand() % MAXNODOS;
	this->ip_origen_pc=rand() % NRO_PC;
	this->ip_destino_pc=rand() % NRO_PC;
	this->paq_recibidos=0;
	cout<<"Pagina CREADA ID: "<<this->id<<" size: "<<this->tamanio<<endl;
	cout<<"ORIGEN: PC nro "<< this->ip_origen_pc<<" Router nro "<<this->ip_origen<<endl;
	cout<<"DESTINO: PC nro "<<this->ip_destino_pc<<" Router nro "<<this->ip_destino<<endl<<endl;
};

Pagina::Pagina(int id, int ip_origen, int ip_destino, int tamanio, int ip_origen_pc, int ip_destino_pc){
	this->id=id;
	this->tamanio=tamanio;
	this->ip_origen=ip_origen;
	this->ip_destino=ip_destino;
	this->paq_recibidos=0;
	this->ip_origen_pc=ip_origen_pc;
	this->ip_destino_pc=ip_destino_pc;
};

Pagina::~Pagina(){
};

int Pagina::obtener_id(){
	return this->id;
};

int Pagina::obtener_tamanio(){
	return this->tamanio;
};

int Pagina::obtener_ip_origen(){
	return this->ip_origen;
};

int Pagina::obtener_ip_destino(){
	return this->ip_destino;
};

int Pagina::obtener_ip_origen_pc(){
	return this->ip_origen_pc;
}

int Pagina::obtener_ip_destino_pc(){
	return this->ip_destino_pc;
};

int Pagina::obtener_paq_recibidos(){
    return this->paq_recibidos;
};

void Pagina::recibir_paquete(){
	paq_recibidos++;
};