#include <iostream>
#include <string>
#include "PaMedicamento.h"
#include "MediExpress.h"

#include <list>
#include <vector>
using namespace std;

void mostrar_vector_labs(vector<Laboratorio*> vector, int cantidad_a_mostrar = UINT_MAX){
    int contador=0;
    if(cantidad_a_mostrar==UINT_MAX) {
        for (int i = 0; i < vector.size(); i++) {
            std::cout << ++contador
                      << " Laboratorio: ( Id=" << vector[i]->getId()
                      << " Nombre=" << vector[i]->getNombreLab()
                      << " Direccion" << vector[i]->getDireccion()
                      << " CodPostal" << vector[i]->getCodPostal()
                      << " Localidad" << vector[i]->getLocalidad()
                      << ")" << std::endl;
        }
    }else{
        for (int i = 0; i < cantidad_a_mostrar; i++) {
            std::cout << ++contador
                      << " Laboratorio: ( Id=" << vector[i]->getId()
                      << " Nombre=" << vector[i]->getNombreLab()
                      << " Direccion" << vector[i]->getDireccion()
                      << " CodPostal" << vector[i]->getCodPostal()
                      << " Localidad" << vector[i]->getLocalidad()
                      << ")" << std::endl;
        }
    }
}

void mostrar_farmacia(vector<Farmacia*> &vector){
    for(int i=0;i<100 && i<vector.size();i++){
            std::cout << i+1
                      << " Farmacia: ( CIF=" << vector[i]->getCif()
                      << " Provincia= " << vector[i]->getProvincia()
                      << " Localidad=" << vector[i]->getLocalidad()
                      << " Nombre=" << vector[i]->getNombre()
                      << " Direccion=" << vector[i]->getDireccion()
                      << " CodPostal=" << vector[i]->getCodPostal()
                      << ")" << std::endl;
    }
}


/**
 * @author Eduardo Calvo Almeida eca00028@red.ujaen.es
 */
int main() {
    try {
        MediExpress m("../pa_medicamentos.csv","../lab2.csv","../farmacias.csv");

        // SEVILLA
        vector<Farmacia*> sevilla=m.buscarFarmacias("SEVILLA");
        PaMedicamento *pa;

        cout << endl << endl << endl;
        cout << "Farmacias en Sevilla: " << sevilla.size() << endl;
        int unidades;
        for(int i=0;i<sevilla.size();i++){
            for(int j=0;j<12;j++) {
                unidades = sevilla[i]->comprarMedicam(3640, 1, pa);
                cout << "En la farmacia " << sevilla[i]->getCif() << " hay " << unidades
                     << " unidades de Oxido de magnesio" << endl;
                if (unidades == 0) {
                    unidades = sevilla[i]->comprarMedicam(3632, 1, pa);
                    cout << "En la farmacia " << sevilla[i]->getCif() << " hay " << unidades
                         << " unidades de Carbonato de magnesio" << endl;
                    if (unidades == 0) {
                        unidades = sevilla[i]->comprarMedicam(3633, 1, pa);
                        cout << "En la farmacia " << sevilla[i]->getCif() << " hay " << unidades
                             << " unidades de Cloruro de magnesio" << endl;
                        if (unidades == 0) {
                            cout << "No hay ninguno de los medicamentos" << endl;
                        }
                    }
                }
            }
        }


        // VIRUSES
        cout << endl << endl;
        vector<Farmacia*> madrid=m.buscarFarmacias("MADRID");
        int contador=0;
        vector<PaMedicamento*> virus;
        for(int i=0;i<madrid.size();i++){
            virus=madrid[i]->buscaMedicamNombre("VIRUS");
            contador+=virus.size();
            cout << "Farmacia con cif: " << madrid[i]->getCif() << " tiene VIRUS" << endl;
        }
        cout << "En Madrid hay " << contador << " farmacias con VIRUS" << endl;



        cout << endl << endl;
        // ELIMINO MEDICAMENTO 9355
        if(m.eliminarMedicamento(9355)){
            cout << "El medicamento con id 9355 se ha eliminado con exito" << endl;
        }else{
            cout << "Error en el borrado del medicamento con id 9355" << endl;
        }

        // Verifico si el medicamento se ha eliminado
        if(!m.buscarCompuesto(9355)){
            cout << "Ya no existe el medicamento con id_num=9355" << endl;
        }else{
            cout << "El medicamento con id_num=9355 sigue existiendo" << endl;
        }


        if(m.buscarCompuesto(3244)){
            cout << "El medicamento con id_num=3244 esta" << endl;
        }else{
            cout << "El medicamento con id_num=3244 no esta" << endl;
        }

        // ELIMINO MEDICAMENTO 3244
        if(m.eliminarMedicamento(3244)){
            cout << "El medicamento con id 3244 se ha eliminado con exito" << endl;
        }else{
            cout << "Error en el borrado del medicamento con id 3244" << endl;
        }

    }catch (exception &e) {
        cerr << e.what() << endl;
    }

    return 0;
}