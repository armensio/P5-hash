//
// Created by eduar on 14/10/2025.
//

#ifndef P1_MEDIEXPRESS_H
#define P1_MEDIEXPRESS_H
#include "Laboratorio.h"
#include "PaMedicamento.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include "Farmacia.h"
#include "ThashMedicam.h"

#include <list>
#include <vector>
#include <map>
#include <string>
using namespace std;

class MediExpress {
private:
    list<Laboratorio> labs;
    //map<int,PaMedicamento> medication;
    multimap<string,Farmacia> pharmacy;
    ThashMedicam idMedication;
    vector<int> id_medicamentosss;

public:
    MediExpress();
    MediExpress(const string &fichero_pamedicamentos,const string &fichero_laboratorios,const string &fichero_farmacias);
    ~MediExpress();

    void suministrarMed(PaMedicamento *pa,Laboratorio *l); // NO CAMBIA
    Laboratorio* buscarLab(string nombreLab); // NO CAMBIA
    vector<Laboratorio*> buscarLabCiudad(string nombreCiudad); // NO CAMBIA
    vector<PaMedicamento*> buscarCompuesto(string nombrePA);
    vector<PaMedicamento*> getMedicamentoSinLab();

    PaMedicamento* buscarCompuesto(int id_num);
    void suministrarFarmacia(Farmacia *f, int id_num, int n);
    Farmacia* buscarFarmacia(string cif);
    vector<Laboratorio*> buscarLabs(string nombrePA);

    vector<Farmacia*> buscarFarmacias(string provincia);
    bool eliminarMedicamento(int id_num);
};


#endif //P1_MEDIEXPRESS_H
