//
// Created by eduar on 14/10/2025.
//

#include "MediExpress.h"
using namespace std;

MediExpress::MediExpress() {

}

MediExpress::MediExpress(const std::string &fichero_pamedicamentos, const std::string &fichero_laboratorios, const std::string &fichero_farmacias) {

    std::ifstream is;
    std::stringstream columnas;
    std::string fila;
    int contador = 0;

    std::string id_number = "";
    std::string id_alpha = "";
    std::string nombre = "";

    vector<int> id_medicamentos;
    is.open(fichero_pamedicamentos); //carpeta de proyecto
    if (is.good()) {
        std::cout << endl << "Los 50 primeros medicamentos son: " << std::endl;
        while (getline(is, fila)) {

            //¿Se ha leído una nueva fila?
            if (fila != "") {

                columnas.str(fila);

                getline(columnas, id_number, ';'); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas, id_alpha, ';');
                getline(columnas, nombre, ';');

                PaMedicamento dato(stoi(id_number), id_alpha, nombre);

                idMedication.insertar(stoi(id_number),dato);

                id_medicamentos.push_back(stoi(id_number));

                fila = "";
                columnas.clear();

                if (idMedication.numElementos() < 51) {
                    std::cout << ++contador
                              << " Medicamento: ( Id_number=" << id_number
                              << ")" << std::endl;
                }

            }
        }

        is.close();

    } else {
        std::cout << "Error de apertura en archivo" << std::endl;
    }


    //Lectura de los laboratorios
    contador = 0;

    string id="";
    string nombreLab="";
    string direccion="";
    string codPostal="";
    string localidad="";


    is.open(fichero_laboratorios); //carpeta de proyecto
    if (is.good()) {
        std::cout << endl << endl << "Los 50 primeros laboratorios son: " << std::endl;
        while (getline(is, fila)) {

            //¿Se ha leído una nueva fila?
            if (fila != "") {

                columnas.str(fila);

                getline(columnas, id, ';'); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas, nombreLab, ';');
                getline(columnas, direccion, ';');
                getline(columnas, codPostal, ';');
                getline(columnas, localidad, ';');

                Laboratorio l(stoi(id), nombreLab, direccion,codPostal,localidad);
                labs.push_back(l);
                fila = "";
                columnas.clear();

                if (labs.size() < 51) {
                    std::cout << ++contador
                              << " Laboratorio: ( Id=" << id
                              << " Nombre=" << nombreLab
                              << " Direccion" << direccion
                              << " CodPostal" << codPostal
                              << " Localidad" << localidad
                              << ")" << std::endl;
                }

            }
        }

        is.close();
    } else {
        std::cout << "Error de apertura en archivo" << std::endl;
    }


    // Asigno los sobrantes a laboratorios de Madrid
    vector<Laboratorio *> madrid;
    madrid = buscarLabCiudad("Madrid");
    vector<PaMedicamento*> sin_labs=getMedicamentoSinLab();
    for(int i=0;i<sin_labs.size() && i<madrid.size();i++){
        sin_labs[i]->servidoPor(madrid[i]);
    }

    /*
    list<Laboratorio>::iterator j=labs.begin();
    //Enlace de medicamentos con laboratorios
    for(int i=0;i<medication.size() && j!=labs.end();i=i+2){
        medication[i].servidoPor(&(*j));
        medication[i+1].servidoPor(&(*j));
        j++;
    }*/

    // ME DA PROBLEMA EN EL MEDICAMENTO2 CORREGIRRRRRRR
    list<Laboratorio>::iterator j=labs.begin();
    //Enlace de medicamentos con laboratorios
    for(int i=0;i<id_medicamentos.size() && j!=labs.end();i=i+2){
        PaMedicamento *medicamento=idMedication.buscar(id_medicamentos[i]);
        if(medicamento){
            medicamento->servidoPor(&(*j));
        }
        /*PaMedicamento *medicamento2=idMedication.buscar(id_medicamentos[i+1]);
        if(medicamento2){
            medicamento->servidoPor(&(*j));
        }*/
        j++;
    }


    //Cargo las farmacias
    contador = 0;

    std::string cif = "";
    std::string provincia = "";


    is.open(fichero_farmacias); //carpeta de proyecto
    if (is.good()) {
        std::cout << endl << endl << "Las primeras 50 farmacias son: " << std::endl;
        while (getline(is, fila)) {

            //¿Se ha leído una nueva fila?
            if (fila != "") {

                columnas.str(fila);

                getline(columnas, cif, ';'); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas, provincia, ';');
                getline(columnas, localidad, ';');
                getline(columnas, nombre, ';');
                getline(columnas, direccion, ';');
                getline(columnas, codPostal, '\r');

                Farmacia f(cif,provincia,localidad,nombre,direccion,codPostal,this);
                pharmacy.insert(std::pair<string,Farmacia>(provincia,f));

                fila = "";
                columnas.clear();

                if (pharmacy.size() < 51) {
                    std::cout << ++contador
                              << " Farmacia: ( CIF=" << cif
                              << " Provincia= " << provincia
                              << " Localidad=" << localidad
                              << " Nombre=" << nombre
                              << " Direccion=" << direccion
                              << " CodPostal=" << codPostal
                              << ")" << std::endl;
                }

            }
        }

        is.close();
    } else {
        std::cout << "Error de apertura en archivo" << std::endl;
    }



    //LEO DE NUEVO LAS FARMACIAS

    vector<string> cifs;
    is.open(fichero_farmacias); //carpeta de proyecto
    if (is.good()) {
        while (getline(is, fila)) {

            //¿Se ha leído una nueva fila?
            if (fila != "") {

                columnas.str(fila);

                getline(columnas, cif, ';'); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas, provincia, ';');
                getline(columnas, localidad, ';');
                getline(columnas, nombre, ';');
                getline(columnas, direccion, ';');
                getline(columnas, codPostal, '\r');

                cifs.push_back(cif);

                fila = "";
                columnas.clear();
            }
        }
        is.close();
    } else {
        std::cout << "Error de apertura en archivo" << std::endl;
    }

// Asigno 100 medicamentos a cada farmacia que está en el vector de cofs
    int m=0;
    for(int i=0;i<cifs.size();i++){
        Farmacia *f= buscarFarmacia(cifs[i]);
        if(f){
            int c=0;
            while(c<100){
                PaMedicamento *medicamento= buscarCompuesto(id_medicamentos[m]);
                f->nuevoStock(medicamento,10);

                c++;
                m++;
                if(m==id_medicamentos.size()){
                    m=0;
                }
            }
        }
    }


}

MediExpress::~MediExpress() {

}

void MediExpress::suministrarMed(PaMedicamento *pa, Laboratorio *l) {
    pa->servidoPor(l);
}

Laboratorio* MediExpress::buscarLab(std::string nombreLab) {
    list<Laboratorio>::iterator i = labs.begin();
    while (i != labs.end()) {
        if (i->getNombreLab().find(nombreLab) != string::npos) {
            return &(*i);
        } else {
            i++;
        }
    }
    return nullptr;
}

vector<Laboratorio*> MediExpress::buscarLabCiudad(std::string nombreCiudad) {
    vector<Laboratorio*> laboratorios;
    list<Laboratorio>::iterator i=labs.begin();
    while(i!=labs.end()){
        if (i->getLocalidad().find(nombreCiudad) != string::npos) {
            laboratorios.push_back(&(*i));
        }
        i++;
    }
    return laboratorios;
}

vector<PaMedicamento*> MediExpress::buscarCompuesto(std::string nombrePA) {
    vector<PaMedicamento*> medicamentos;
    for(int i=0;i<id_medicamentosss.size();i++){
        PaMedicamento *medicamento= buscarCompuesto(id_medicamentosss[i]);
        if(medicamento->getNombre().find(nombrePA)!= string::npos){
            medicamentos.push_back(medicamento);
        }
    }
    return medicamentos;
}

vector<PaMedicamento*> MediExpress::getMedicamentoSinLab() {
    vector<PaMedicamento*> medicamentos;
    for(int i=0;i<id_medicamentosss.size();i++){
        PaMedicamento *medicamento= buscarCompuesto(id_medicamentosss[i]);
        if(medicamento->getServe()== nullptr){
            medicamentos.push_back(medicamento);
        }
    }
    return medicamentos;
}

PaMedicamento* MediExpress::buscarCompuesto(int id_num) {
    return idMedication.buscar(id_num);
}

void MediExpress::suministrarFarmacia(Farmacia *f, int id_num, int n) {
    PaMedicamento *medicamento= buscarCompuesto(id_num);
    if(medicamento){
        f->nuevoStock(medicamento,n);
    }
}


Farmacia* MediExpress::buscarFarmacia(std::string cif) {
    multimap<string,Farmacia>::iterator i=pharmacy.begin();
    while(i!=pharmacy.end()){
        if(cif==i->second.getCif()){
            return &i->second;
        }
        i++;
    }
    return nullptr;
}

vector<Laboratorio*> MediExpress::buscarLabs(std::string nombrePA) {
    vector<Laboratorio*> v;
    for(int i=0;i<id_medicamentosss.size();i++){
        PaMedicamento *medicamento= buscarCompuesto(id_medicamentosss[i]);
        if(medicamento->getNombre().find(nombrePA)!= string::npos){
            if(medicamento->getServe()){
                v.push_back(medicamento->getServe());
            }
        }
    }
    return v;
}

vector<Farmacia*> MediExpress::buscarFarmacias(std::string provincia) {
    vector<Farmacia*> v;
    multimap<string,Farmacia>::iterator i=pharmacy.find(provincia);
    if(i!=pharmacy.end()){
        while(i->second.getProvincia()==provincia) {
            v.push_back(&(*i).second);
            i++;
        }
    }
    return v;
}

bool MediExpress::eliminarMedicamento(int id_num) {
    bool eliminado=idMedication.borrar(id_num);
    multimap<string,Farmacia>::iterator i=pharmacy.begin();
    while(i!=pharmacy.end()){
        if(i->second.buscaMedicamId(id_num)>0){
            if (!i->second.eliminarStock(id_num)) {
                cerr << "[MediExpress::eliminarMedicameto] Error al intentar eliminar un medicamento del stock de una farmacia" << endl;
            }
        }
        i++;
    }
    if(eliminado){
        return true;
    }
    return false;
}
