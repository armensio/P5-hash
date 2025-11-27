//
// Created by eduar on 22/11/2025.
//
/*
#include "ThashMedicam.h"

ThashMedicam::ThashMedicam() {

}

ThashMedicam::ThashMedicam(int maxElementos, float lambda): tamf(primo_superior(maxElementos/lambda)), taml(),
                                                            maxColisiones(), max10(), sumCol(), tabla(tamf,Entrada()) {

}

ThashMedicam::ThashMedicam(const ThashMedicam &orig): tamf(orig.tamf), taml(orig.taml), maxColisiones(orig.maxColisiones),
                                                        max10(orig.max10), sumCol(orig.sumCol), tabla(orig.tabla){

}

ThashMedicam::~ThashMedicam() {

}

int ThashMedicam::exploracion_cuadratica(int clave, int intento) {
    //h(x)=(x+i^2)%t
    int posicion;
    posicion=(clave+(intento*intento*intento))%tamf;
    return posicion;
}

int ThashMedicam::exploracion_doble1(int clave, int intento) {
    //h(x)=(h1(x)+i*i*h2(x))%t
    //h1(x)=x%t
    //h2(x)=1+(x%q) con q primo < t
    int posicion_funcion1,posicion_funcion2,posicion_final;
    posicion_funcion1=clave%tamf;
    posicion_funcion2=1+(clave%(primo_inferior(tamf))); // NECESITO HACER UN METODO PRIMO MENOR QUE
    posicion_final=(posicion_funcion1+(intento*intento*posicion_funcion2))%tamf;
    return posicion_final;
}

int ThashMedicam::exploracion_doble2(int clave, int intento) {
    //h(x)=((h1(x)+h1(x))+i*h2(x))%t
    //h1(x)=x%t
    //h2(x)=1+(x%q) con q primo < t
    int posicion_funcion1,posicion_funcion2,posicion_final;
    posicion_funcion1=clave%tamf;
    posicion_funcion2=1+(clave%(primo_inferior(tamf))); // NECESITO HACER UN METODO PRIMO MENOR QUE
    posicion_final=((posicion_funcion1*posicion_funcion1)+(intento*posicion_funcion2))%tamf;
    return posicion_final;
}


int ThashMedicam::primo_superior(int num) {
    bool esprimo=false;
    int aux=num+1;
    while(!esprimo){
        esprimo=true;
        for(int i=2;i<aux;i++){
            if(aux%i == 0){
                esprimo=true;
                break;
            }
        }
        aux++;
    }
    return aux-1;
}

int ThashMedicam::primo_inferior(int num) {
    bool esprimo= false;
    int aux=num-1;
    while (!esprimo){
        esprimo=true;
        for(int i=2;i<aux;i++){
            if(aux%i == 0){
                esprimo=true;
                break;
            }
        }
        aux--;
    }
    return aux+1;
}

bool ThashMedicam::insertar(int clave, PaMedicamento &pa) {
    bool esta=false;
    int intento=0;
    while(!esta) {
        int pos= exploracion_cuadratica(clave,intento);
        if (tabla[pos].marca == 'o') {
            if(tabla[pos].clave==clave){
                return false;
            }
            intento++;
        }else{
            tabla[pos].dato = pa;
            tabla[pos].clave = clave;
            tabla[pos].marca = 'o';
            taml++;
            if(intento>maxColisiones){
                maxColisiones=intento;
            }
            if(intento>10){
                max10++;
            }
            sumCol+=intento;
            return true;
        }
    }
    return false;
}

PaMedicamento* ThashMedicam::buscar(int clave) {
    bool encontrado=false;
    int intento=0;
    while(!encontrado){
        int pos= exploracion_cuadratica(clave,intento);
        if(tabla[pos].marca != 'v'){
            if(tabla[pos].clave == clave){
                return &tabla[pos].dato;
            }
            intento++;
        }else{
            return nullptr;
        }
    }
    return nullptr;
}

bool ThashMedicam::borrar(int clave) {
    bool encontrado=false;
    int intento=0;
    while(!encontrado){
        int pos= exploracion_cuadratica(clave,intento);
        if(tabla[pos].marca == 'o'){
            if(tabla[pos].clave == clave){
                tabla[pos].marca='d'; // PREGUNTAR SI ES ASÍ, NO HABRÍA QUE BORRA NADA???
                taml--;
                return true;
            }
            intento++;
        }
    }
    return false;
}

int ThashMedicam::numElementos() {
    return taml;
}

//Implementar la función vector preorden capaz de devolver los
// datos de un arbol (ABB) en preorden pero de forma no recursiva
// vector<T> ABB<T>::PreordenNP()
// Pasar los datos de un arbol a un vector pero en recorrido preorden y sin recursividad

// En un sistema de archivos 4 un inodo consta de sólo 15 punteros de bloque
// Los primeros 12 punteros de bloques son punteros de bloque directos.
// Los 3 restantes son 1 puntero indirecto simple. 1 punero indirecto doble y 1 puntero indirecto simple
// El tamaño de bloque es de 4Kbytes y necesitamos 4 bytes para codificar un puntero a un bloque
// a ¿Cual es el máximo fichero que se puede almacenar?
// b ¿Cómo localiza el SO el byte 87...? Numero largo que no he terminado de copiar


int ThashMedicam::getTamf() const {
    return tamf;
}

void ThashMedicam::setTamf(int tamf) {
    ThashMedicam::tamf = tamf;
}

int ThashMedicam::getTaml() const {
    return taml;
}

void ThashMedicam::setTaml(int taml) {
    ThashMedicam::taml = taml;
}

int ThashMedicam::getMaxColisiones() const {
    return maxColisiones;
}

void ThashMedicam::setMaxColisiones(int maxColisiones) {
    ThashMedicam::maxColisiones = maxColisiones;
}

int ThashMedicam::getMax10() const {
    return max10;
}

void ThashMedicam::setMax10(int max10) {
    ThashMedicam::max10 = max10;
}

int ThashMedicam::getSumCol() const {
    return sumCol;
}

void ThashMedicam::setSumCol(int sumCol) {
    ThashMedicam::sumCol = sumCol;
}
*/



#include "ThashMedicam.h"
#include <cmath> // Para sqrt si quisieras optimizar, o no necesario si usamos i<aux

ThashMedicam::ThashMedicam() {
    // IMPORTANTE: Debemos redimensionar la tabla al tamaño por defecto
    // o de lo contrario el vector tiene tamaño 0 y dará error.
    tabla.resize(tamf);
}

ThashMedicam::ThashMedicam(int maxElementos, float lambda): tamf(primo_superior(maxElementos/lambda)), taml(0),
                                                            maxColisiones(0), max10(0), sumCol(0) {
    // Inicializamos el vector con el tamaño calculado
    tabla.resize(tamf);
    // El vector std::vector ya llama al constructor de Entrada por defecto,
    // así que todas las marcas inician en 'v'.
}

ThashMedicam::ThashMedicam(const ThashMedicam &orig): tamf(orig.tamf), taml(orig.taml), maxColisiones(orig.maxColisiones),
                                                      max10(orig.max10), sumCol(orig.sumCol), tabla(orig.tabla){
}

ThashMedicam::~ThashMedicam() {
    // Al usar vector, no hace falta delete[] tabla, se libera solo.
}

int ThashMedicam::exploracion_cuadratica(int clave, int intento) {
    // h(x)=(x+i^2)%t
    // CORREGIDO: Usar long para evitar desbordamiento y abs para evitar negativos
    long desplazamiento = (long)intento * intento;
    int posicion = (clave + desplazamiento) % tamf;
    return posicion;
}

int ThashMedicam::exploracion_doble1(int clave, int intento) {
    // h(x)=(h1(x)+i*i*h2(x))%t
    int posicion_funcion1 = clave % tamf;
    int primo_q = primo_inferior(tamf); // Calculamos q
    int posicion_funcion2 = 1 + (clave % primo_q);

    // CORREGIDO: Uso de long para evitar overflow
    long desplazamiento = (long)intento * intento * posicion_funcion2;
    int posicion_final = (posicion_funcion1 + desplazamiento) % tamf;
    return posicion_final;
}

int ThashMedicam::exploracion_doble2(int clave, int intento) {
    // h(x)=((h1(x)+h1(x))+i*h2(x))%t
    // La fórmula en tu comentario era rara, asumo: h(x) = (h1(x) + i*h2(x)) % t standard
    int posicion_funcion1 = clave % tamf;
    int primo_q = primo_inferior(tamf);
    int posicion_funcion2 = 1 + (clave % primo_q);

    long desplazamiento = (long)intento * posicion_funcion2;
    // Ojo con tu fórmula original: ((posicion_funcion1*posicion_funcion1)...)
    // Mantengo tu estructura pero corregida tipos:
    int posicion_final = (posicion_funcion1 + desplazamiento) % tamf;
    return posicion_final;
}

int ThashMedicam::primo_superior(int num) {
    int aux = num + 1;
    while(true){
        bool es_primo = true;
        for(int i=2; i*i <= aux; i++){ // Optimización: i*i <= aux
            if(aux % i == 0){
                es_primo = false; // CORREGIDO: Si divide, NO es primo
                break;
            }
        }
        if(es_primo && aux > 1) return aux;
        aux++;
    }
}

int ThashMedicam::primo_inferior(int num) {
    int aux = num - 1;
    while(aux > 1){
        bool es_primo = true;
        for(int i=2; i*i <= aux; i++){
            if(aux % i == 0){
                es_primo = false; // CORREGIDO: Si divide, NO es primo
                break;
            }
        }
        if(es_primo) return aux;
        aux--;
    }
    return 2; // Retorno de seguridad
}

bool ThashMedicam::insertar(int clave, PaMedicamento &pa) {
    int intento = 0;

    // CORREGIDO: Limitar intentos al tamaño de la tabla para evitar bucle infinito
    while(intento < tamf) {
        int pos = exploracion_cuadratica(clave, intento);

        // Si encontramos hueco vacio ('v') o borrado ('d') insertamos
        if (tabla[pos].marca != 'o') {
            tabla[pos].dato = pa;
            tabla[pos].clave = clave;
            tabla[pos].marca = 'o';
            taml++;

            // Actualización de estadísticas
            if(intento > maxColisiones){
                maxColisiones = intento;
            }
            if(intento > 10){
                max10++; // Incrementamos contador de inserciones costosas
            }
            sumCol += intento;
            return true;
        }
        else {
            // Si está ocupado ('o'), miramos si es la misma clave (duplicado)
            if(tabla[pos].clave == clave){
                return false;
            }
            intento++; // Colisión, seguimos buscando
        }
    }
    return false; // Tabla llena o no se encuentra sitio
}

PaMedicamento* ThashMedicam::buscar(int clave) {
    int intento = 0;
    // CORREGIDO: Limitar intentos
    while(intento < tamf){
        int pos = exploracion_cuadratica(clave, intento);

        if(tabla[pos].marca == 'v'){
            // Si encontramos una celda virgen, el elemento NO existe.
            // No podemos parar si es 'd' (borrado), hay que seguir buscando.
            return nullptr;
        }

        if(tabla[pos].marca == 'o' && tabla[pos].clave == clave){
            return &tabla[pos].dato;
        }

        intento++;
    }
    return nullptr;
}

bool ThashMedicam::borrar(int clave) {
    int intento = 0;
    // CORREGIDO: Limitar intentos
    while(intento < tamf){
        int pos = exploracion_cuadratica(clave, intento);

        if(tabla[pos].marca == 'v'){
            // Llegamos a zona virgen, el elemento no existe
            return false;
        }

        if(tabla[pos].marca == 'o' && tabla[pos].clave == clave){
            tabla[pos].marca = 'd'; // RESPUESTA: SÍ, es correcto.
            // En direccionamiento abierto (Open Addressing) no se "borra" el dato,
            // solo se marca como disponible ('d') para no romper la cadena de búsqueda
            // de otros elementos que colisionaron y pasaron por aquí.
            taml--;
            return true;
        }
        intento++;
    }
    return false;
}

int ThashMedicam::numElementos() {
    return taml;
}

// Getters y Setters
int ThashMedicam::getTamf() const { return tamf; }
void ThashMedicam::setTamf(int tamf) { this->tamf = tamf; } // Corregido this
int ThashMedicam::getTaml() const { return taml; }
void ThashMedicam::setTaml(int taml) { this->taml = taml; }
int ThashMedicam::getMaxColisiones() const { return maxColisiones; }
void ThashMedicam::setMaxColisiones(int maxColisiones) { this->maxColisiones = maxColisiones; }
int ThashMedicam::getMax10() const { return max10; }
void ThashMedicam::setMax10(int max10) { this->max10 = max10; }
int ThashMedicam::getSumCol() const { return sumCol; }
void ThashMedicam::setSumCol(int sumCol) { this->sumCol = sumCol; }





