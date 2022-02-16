#include "Router.h"

Router:: Router(int nro_router){
	this->nro_router=nro_router;
    ip = bitset<4>(this->nro_router).to_string();
    cout<< "Router nro: "<<this->nro_router<<" IP: "<<this->ip<<endl;
    // inicializo las pc conectadas al router
    for(int pc=0; pc<NRO_PC; pc++){
        pcs[pc]=new Computadora(pc, this->nro_router);
    }
    cout<<endl;
};

Router::~Router(){
};

int Router::obtener_nro_router(){
	return this->nro_router;
};

string Router::get_ip(){
    return this->ip;
}

int Router::total_paquetes(int destino){
    return buscar_canal(destino)->get_size();
};

int Router::total_total_paquetes(){
    int tot_paq = this->recibos.cabeza()->get_size();
    return (tot_paq + total_total_paquetes(this->recibos.resto()));
};

int Router::total_total_paquetes(Lista<Canal*>* can){
    int tot_p=0;
    if(!can->esvacia()){
        tot_p =+ can->cabeza()->get_size();
        return (tot_p + total_total_paquetes(can->resto()));
    }
    return tot_p;
};

void Router::construir_canales(int destino){
    this->envios.add(new Canal(this->nro_router, destino));
};

void Router::set_recibos(Canal* canal){
    this->recibos.add(canal);
};

void Router::set_tabla_enrutamiento(int destino, int enviar_a){
    if(this->nro_router!=destino){
        tabla_enrutamiento[destino]=enviar_a;
    }
    else{
        tabla_enrutamiento[destino]=this->nro_router;
    }
};

void Router::print_tabla_enrutamiento(){
    cout<<endl;
    cout<<"Tabla de enrutamiento del Router nro "<<this->nro_router<<" IP: "<<this->get_ip()<<endl;
    cout<<"Destino--->Enviar a"<<endl;
    for(int i=0; i<MAXNODOS; i++){
        cout<<"  "<<i<<" ----------> "<<tabla_enrutamiento[i]<<endl;
    }
};



void Router::recibir_pagina(Pagina* pag_recibida){
    //cout<<"Pagina origen: "<<pag_recibida->obtener_ip_origen()<<" destino: "<<pag_recibida->obtener_ip_destino()<<" tamanio: "<<pag_recibida->obtener_tamanio()<<endl;
    int total = pag_recibida->obtener_tamanio();
    if(pag_recibida->obtener_ip_destino()==this->nro_router){
        //cout<<"Mandar directo a pc"<<endl;
        this->pcs[pag_recibida->obtener_ip_destino_pc()]->recibir_pag(pag_recibida);
    }
    else{
        for(int k=0; k<total; k++){
            //enviar_paquete(new Paquete(pag_recibida->obtener_ip_origen(), pag_recibida->obtener_ip_destino(), pag_recibida->obtener_id(), k, pag_recibida->obtener_tamanio(),pag_recibida->obtener_ip_origen_pc(),pag_recibida->obtener_ip_destino_pc()));
            buscar_canal(this->nro_router, this->recibos.resto())->add_paquete(new Paquete(pag_recibida->obtener_ip_origen(), pag_recibida->obtener_ip_destino(), pag_recibida->obtener_id(), k, pag_recibida->obtener_tamanio(),pag_recibida->obtener_ip_origen_pc(),pag_recibida->obtener_ip_destino_pc()));
        } //VER
    }
};

void Router::recibir(){
    //cout<<"Total de paquetes a recibir: "<<total_total_paquetes()<<" en el router "<<this->ip<<endl;
    //mostrar_canales_recibo();
    int tot_inicial = total_total_paquetes();
    int tot= recibir_paquetes(this->recibos.cabeza());
    //cout<<"Recibidos hasta ahora: "<<tot<<endl;
    recibir(tot_inicial, tot, this->recibos.resto());
};

void Router::recibir(int tot_inicial, int tot, Lista<Canal*>* m){
    if(tot<tot_inicial){
        if(m->esvacia()==false){
            tot= tot+ recibir_paquetes(m->cabeza());
            //cout<<"Recibidos hasta ahora: "<<tot<<" quedan: "<<total_total_paquetes() <<endl;
            recibir(tot_inicial, tot, m->resto());
        }
        else{
            tot= tot + recibir_paquetes(this->recibos.cabeza());
            //cout<<"Recibidos hasta ahora: "<<tot<<" quedan: "<<total_total_paquetes() <<endl;
            recibir(tot_inicial, tot, this->recibos.resto());
        }
    }
};

int Router::recibir_paquetes(Canal* canal){
    if(canal->get_size()!=0){
        //if es de este router
        if(canal->get_paquete()->obtener_ip_destino()==this->nro_router){
            construir_pagina(canal->get_paquete());
            canal->sacar_paquete(); //poner dentro
        }
        else if(buscar_canal(tabla_enrutamiento[canal->get_paquete()->obtener_ip_destino()])->canal_saturado()){ // si alcanza el ancho de banda, dejo de pasar paquetes
            //cout<<"Canal saturado"<<endl;
            canal->reencolar_paquete();
        }
        else{
            //cout<<"Canal saturado? "<<(buscar_canal(tabla_enrutamiento[canal->get_paquete()->obtener_ip_destino()])->canal_saturado())<<endl;
            enviar_paquete(canal->get_paquete());
            canal->sacar_paquete(); //poner dentro
        }
        return 1;
    }
    return 0;
};

void Router::enviar_paquete(Paquete* p){
    //cout<<"Paquete nro "<<p->obtener_nro_orden()<<" de pagina "<<p->obtener_id_pagina()<<" con destino a "<<p->obtener_ip_destino()<<endl;
    int r_destino=tabla_enrutamiento[p->obtener_ip_destino()];
    buscar_canal(r_destino)->add_paquete(p);
};



void Router::mostrar_canales(){
    cout<<"Desde router nro: "<<this->envios.cabeza()->get_origen();
    cout<<" hasta router nro "<<this->envios.cabeza()->get_destino();
    cout<<" cantidad de paquetes: "<<this->envios.cabeza()->get_size()<<endl;
    mostrar_canales(this->envios.resto());
};

void Router::mostrar_canales(Lista<Canal*>* m){
    if(m->esvacia()==false){
        cout<<"Desde router nro: "<<m->cabeza()->get_origen();
        cout<<" hasta router nro "<<m->cabeza()->get_destino();
        cout<<" cantidad de paquetes: "<<m->cabeza()->get_size()<<endl;
        mostrar_canales(m->resto());
    }
};

void Router::mostrar_canales_recibo(){
    cout<<"Desde router nro: "<<this->recibos.cabeza()->get_origen();
    cout<<" hasta router nro "<<this->recibos.cabeza()->get_destino();
    cout<<" cantidad de paquetes: "<<this->recibos.cabeza()->get_size()<<endl;
    mostrar_canales(this->recibos.resto());
};

void Router::mostrar_canales_recibo(Lista<Canal*>* m){
    if(m->esvacia()==false){
        cout<<"Desde router nro: "<<m->cabeza()->get_origen();
        cout<<" hasta router nro "<<m->cabeza()->get_destino();
        cout<<" cantidad de paquetes: "<<m->cabeza()->get_size()<<endl;
        mostrar_canales(m->resto());
    }
};

Canal* Router::buscar_canal(int destino){
    if(this->envios.cabeza()->get_destino()==destino){
        return this->envios.cabeza();
    }
    else{
        return buscar_canal(destino, this->envios.resto());
    }
};

Canal* Router::buscar_canal(int destino, Lista<Canal*>* m){
    if(m->esvacia()==false){
        if(m->cabeza()->get_destino()==destino){
            return m->cabeza();
        }
        else{
            return buscar_canal(destino, m->resto());
        }
    }
    else{
        return nullptr;
    }
};

void Router::construir_pagina(Paquete* p){
    if(this->paginas.esvacia()){
        this->paginas.add(new Pagina(p->obtener_id_pagina(), p->obtener_ip_origen(), p->obtener_ip_destino(), p->obtener_tamanio_pag(),p->obtener_ip_origen_pc(),p->obtener_ip_destino_pc()));
        this->paginas.cabeza()->recibir_paquete();
        if(this->paginas.cabeza()->obtener_tamanio()==this->paginas.cabeza()->obtener_paq_recibidos()){
            this->pcs[paginas.cabeza()->obtener_ip_destino_pc()]->recibir_pag(paginas.cabeza());
            //cout<<"PAGINA CONSTURIDA origen: "<<this->paginas.cabeza()->obtener_ip_origen()<<" destino: "<<this->paginas.cabeza()->obtener_ip_destino()<<" tamanio: "<<this->paginas.cabeza()->obtener_tamanio()<<endl; //enviar a pc
            this->paginas.borrar();
        }
    }
    else if(this->paginas.cabeza()->obtener_id()!=p->obtener_id_pagina()){
        construir_pagina(p, this->paginas.resto());
    }
    else{
        this->paginas.cabeza()->recibir_paquete();
        if(this->paginas.cabeza()->obtener_tamanio()==this->paginas.cabeza()->obtener_paq_recibidos()){
            this->pcs[paginas.cabeza()->obtener_ip_destino_pc()]->recibir_pag(paginas.cabeza());
            //cout<<"PAGINA CONSTURIDA origen: "<<this->paginas.cabeza()->obtener_ip_origen()<<" destino: "<<this->paginas.cabeza()->obtener_ip_destino()<<" tamanio: "<<this->paginas.cabeza()->obtener_tamanio()<<endl; //enviar a pc
            this->paginas.borrar();
        }
    }
};

void Router::construir_pagina(Paquete* p, Lista<Pagina*>* pags){
    if(pags->esvacia()){
        this->paginas.add(new Pagina(p->obtener_id_pagina(), p->obtener_ip_origen(), p->obtener_ip_destino(), p->obtener_tamanio_pag(),p->obtener_ip_origen_pc(),p->obtener_ip_destino_pc()));
        pags->cabeza()->recibir_paquete();
        if(pags->cabeza()->obtener_tamanio()==pags->cabeza()->obtener_paq_recibidos()){
            this->pcs[pags->cabeza()->obtener_ip_destino_pc()]->recibir_pag(pags->cabeza());
            //cout<<"PAGINA CONSTURIDA origen: "<<pags->cabeza()->obtener_ip_origen()<<" destino: "<<pags->cabeza()->obtener_ip_destino()<<" tamanio: "<<pags->cabeza()->obtener_tamanio()<<endl; //enviar a pc
            this->paginas.borrarDato(pags->cabeza());
        }
    }
    else if(pags->cabeza()->obtener_id()!=p->obtener_id_pagina()){
        construir_pagina(p, pags->resto());
    }
    else{
        pags->cabeza()->recibir_paquete();
        if(pags->cabeza()->obtener_tamanio()==pags->cabeza()->obtener_paq_recibidos()){
            this->pcs[pags->cabeza()->obtener_ip_destino_pc()]->recibir_pag(pags->cabeza());
            //cout<<"PAGINA CONSTURIDA origen: "<<pags->cabeza()->obtener_ip_origen()<<" destino: "<<pags->cabeza()->obtener_ip_destino()<<" tamanio: "<<pags->cabeza()->obtener_tamanio()<<endl; //enviar a pc
            this->paginas.borrarDato(pags->cabeza());
        }
    }
};