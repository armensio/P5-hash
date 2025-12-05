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
        MediExpress m("../pa_medicamentos.csv","../lab2.csv","../farmacias.csv",3310,0.65);
        cout << endl << endl;
        //m.mostrarEstadoTabla();

        vector<PaMedicamento*> medicamentos;
        medicamentos=m.buscarCompuesto("MAGNESIO CLORURO HEXAHIDRATO");
        cout << medicamentos.size() <<" medicamentos tienen MAGNESIO CLORURO HEXAHIDRATO" << endl;
        for(int i=0;i<medicamentos.size();i++){
            cout << medicamentos[i]->getNombre() << endl;
        }
        medicamentos=m.buscarCompuesto("CLORURO");
        cout << endl << medicamentos.size() <<" medicamentos tienen CLORURO" << endl;
        for(int i=0;i<medicamentos.size();i++){
            cout << medicamentos[i]->getNombre() << endl;
        }
        medicamentos=m.buscarCompuesto("ANHIDRO CALCIO CLORURO");
        cout << endl << medicamentos.size() <<" medicamentos tienen ANHIDRO CALCIO CLORURO" << endl;
        for(int i=0;i<medicamentos.size();i++){
            cout << medicamentos[i]->getNombre() << endl;
        }
        medicamentos=m.buscarCompuesto("LIDOCAINA HIDROCLORURO");
        cout << endl << medicamentos.size() <<" medicamentos tienen LIDOCAINA HIDROCLORURO" << endl;
        for(int i=0;i<medicamentos.size();i++){
            cout << medicamentos[i]->getNombre() << endl;
        }
        medicamentos=m.buscarCompuesto("MENTA PIPERITA");
        cout << endl << medicamentos.size() <<" medicamentos tienen MENTA PIPERITA" << endl;
        for(int i=0;i<medicamentos.size();i++){
            cout << medicamentos[i]->getNombre() << endl;
        }
        medicamentos=m.buscarCompuesto("VIRUS GRIPE");
        cout << endl << medicamentos.size() <<" medicamentos tienen VIRUS GRIPE" << endl;
        for(int i=0;i<medicamentos.size();i++){
            cout << medicamentos[i]->getNombre() << endl;
        }


        // SEVILLA
        vector<Farmacia*> sevilla=m.buscarFarmacias("SEVILLA");
        PaMedicamento *pa;
        cout << endl << endl << endl;
        cout << "Farmacias en Sevilla: " << sevilla.size() << endl;
        int unidades;
        for(int i=0;i<sevilla.size();i++){
            for(int j=0;j<12;j++) {
                vector<PaMedicamento*> medicamentos2=sevilla[i]->buscaMedicamNombre("MAGNESIO");
                for(int k=0;k<medicamentos2.size();k++) {
                    unidades = sevilla[i]->comprarMedicam(medicamentos2[k]->getIdNum(), 1, pa);
                    cout << "En la farmacia " << sevilla[i]->getCif() << " hay " << unidades
                         << " unidades de " << medicamentos2[k]->getNombre() << endl;
                    if (unidades == 0) {
                        unidades = sevilla[i]->comprarMedicam(3640, 1, pa);
                        cout << "En la farmacia " << sevilla[i]->getCif() << " hay " << unidades
                             << " unidades de Oxido de magnesio" << endl;
                        if (unidades == 0) {
                            cout << "No hay ninguno de los medicamentos" << endl;
                        }
                    }
                }
            }
        }


        //vector<Farmacia*> jaen=m.buscarFarmacias("JAEN");
        //cout << "Farmacias en Jaen: " << jaen.size() << endl;
        //Esto es lo que debería poner pero no me coge ninguna farmacia, entonces he buscado a mano la única farmacia

        Farmacia *jaen=m.buscarFarmacia("E23319585");
        vector<PaMedicamento*> medicamentos3=jaen->buscaMedicamNombre("ANTIGENO OLIGOSACARIDO");
        cout << medicamentos3.size() << " medicamentos con ese nombre en la farmacia de jaen" << endl;
        for(int i=0;i<medicamentos3.size();i++){
            cout << "Antes de pedir " << medicamentos3[i]->getNombre() << ": " << jaen->buscaMedicamId(medicamentos3[i]->getIdNum()) << " unidades" <<  endl;
            jaen->nuevoStock(medicamentos3[i],10);
            cout << "Después de pedir " << medicamentos3[i]->getNombre() << ": " << jaen->buscaMedicamId(medicamentos3[i]->getIdNum()) << " unidades" <<  endl;
        }

        vector<PaMedicamento*> bismutos=m.buscarCompuesto("BISMUTO");
        cout << bismutos.size() << endl;
        vector<PaMedicamento*> cianuros=m.buscarCompuesto("CIANURO");
        cout << cianuros.size() << endl;
        for(int i=0;i<bismutos.size();i++){
            m.eliminarMedicamento(bismutos[i]->getIdNum());
        }
        for(int i=0;i<cianuros.size();i++){
            m.eliminarMedicamento(cianuros[i]->getIdNum());
        }

    }catch (exception &e) {
        cerr << e.what() << endl;
    }

    return 0;
}