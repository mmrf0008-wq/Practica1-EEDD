#include <fstream>
#include <iostream>

#include "VDinamico.h"
#include "Especie.h"
#include "LectorCSV.h"
#include <string>
#include <iostream>
#include <string>
using namespace std;

#if defined(_WIN32) || defined(_WIN64)
    #include <direct.h>
    #define GetCurrentDir _getcwd
#else
    #include <unistd.h>
    #define GetCurrentDir getcwd
#endif

string obtenerDirectorioActual() {
    char buffer[1024];
    if (GetCurrentDir(buffer, sizeof(buffer)) != nullptr) {
        return string(buffer);
    }
    return "";
}

/**
 * @brief Función para encontrar las especies con nombre común no nulo
 * @param vEspecies VDinámico en el que hacer la búsqueda
 * @return VDinámico de punteros a especies en el VDinámico completo
 *          que no tienen nombre común nulo
 */
VDinamico<Especie*> getEspNComun(VDinamico<Especie>& vEspecies)
{
    VDinamico<Especie*> vectorEspNComun;

    for (int i=0; i<vEspecies.getLogico();i++) {
        if (vEspecies[i].get_nombre_comun() != "") {
            vectorEspNComun.insertar(&vEspecies[i]);
        }
    }

    return vectorEspNComun;
}

//Metodo Burbuja
void metodoBurbuja(VDinamico<Especie> &vEspecies) {
    if (vEspecies.getLogico()<1) {
        throw length_error("[main.cpp::metodoBurbuja]: El vector no se puede ordenar");
    }
    Especie aux;
    int n = vEspecies.getLogico();

    for (int i=0; i<n-1;i++) {
        for (int j=0; j < n - i - 1; j++) {
            if (vEspecies[j + 1] < vEspecies[j]) {
                aux = vEspecies[j];
                vEspecies[j] = vEspecies[j + 1];
                vEspecies[j + 1] = aux;
            }
        }
    }
}


//CONSTANTES
const string RUTA_FICHERO_ESPECIES = "data/arbolado-especies.csv";

int main()
{
    try
    {
        string ruta = obtenerDirectorioActual();
        if (!ruta.empty()) {
            cout << "Directorio actual: " << ruta << endl;
        } else {
            cerr << "Error al obtener el directorio." << endl;
        }


        //INSTANCIAR Y MOSTRAR EL VECTOR DE Especies
        LectorCSV lector_csv;
        VDinamico<Especie> vectorCompleto;
        if (!lector_csv.cargar(vectorCompleto, RUTA_FICHERO_ESPECIES))
        {
            cerr << "Error: no se pudo abrir el fichero '" << RUTA_FICHERO_ESPECIES << "'.\n";
            cerr << "Comprueba que ejecutas el programa desde la raiz del proyecto "
                         "(o revisa el Working Directory en la configuracion de ejecucion).\n";
            return 1;
        }
        cout << "Vector leido de fichero"<<endl;;

        //Mostrar los 50 primeros identificadores
        cout<<"==================================================="<<endl;
        cout << "Identificador de las primeras 50 especies:" << endl;
        for (int i = 0; i < 50; ++i)
        {
            cout<<to_string(i)<<": "<<vectorCompleto[i].get_codigo_especie()<<endl;
        }

        //Ordenación del vector
        cout<<"==================================================="<<endl;

        vectorCompleto.ordenar();

        cout << "Vector ordenado. Mostrar las primeras 50 especies" << endl;
        for (int i = 0; i < 50; i++)
        {
            cout<<to_string(i);
            vectorCompleto[i].mostrarInfo();
        }

        //Busqueda de posición de codigos de especies
        cout<<"==================================================="<<endl;
        Especie esp;
        cout << "Posición de códigos de especies: " << endl;
        int pos;
        esp.set_codigo_especie("CTA");
        pos = vectorCompleto.busquedaDicotomica(Especie("CTA", "","",""));
        cout << "   Posicion de CTA: " << pos << endl;
        pos = vectorCompleto.busquedaDicotomica(Especie("DMD", "","",""));
        cout << "   Posicion de DMD: " << pos << endl;
        pos = vectorCompleto.busquedaDicotomica(Especie("HCN", "","",""));
        cout << "   Posicion de HCN: " << pos << endl;
        pos = vectorCompleto. busquedaDicotomica(Especie("NDOF", "","",""));
        cout << "   Posicion de NDOF : " << pos << endl;
        pos = vectorCompleto.busquedaDicotomica(Especie("JAX", "","",""));
        cout << "   Posicion de JAX: " << pos << endl;

        //Búsqueda de Nombre común no nulo
        cout<<"==================================================="<<endl;
        cout << "Vector de especies con nombre comun no nulo" << endl;
        VDinamico<Especie*> vectorEspNComun = getEspNComun(vectorCompleto);
        cout<<"Numero de elementos no nulos: "<<vectorEspNComun.getLogico()<<endl;
        cout << "Mostrando las primeras 50 especies: " << endl;
        for (int i = 0; i < 50; i++)
        {
            cout<<to_string(i);
            vectorEspNComun[i]->mostrarInfo();
        }

        //Ordenamiento mediante el metodo Burbuja
        metodoBurbuja(vectorCompleto);
        cout << "Vector ordenado. Mostrando las primeras 50 especies en orden inverso" << endl;
        for (int i = vectorCompleto.getLogico() - 1; i > vectorCompleto.getLogico() - 50; i--)
        {
            cout<<to_string(i);
            vectorCompleto[i].mostrarInfo();
        }

    }
    catch (const exception& e)
    {
        cerr << endl << "main.cpp -> " << e.what() << endl;
        return 1;
    }
    return 0;
}
