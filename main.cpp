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

/**
 * Busca cuantas especies contienen una palabra especificada por parametro en la
 * primera palabra de su nombre cientifico
 * @param palabra cadena que se buscara en el nombre cientifico
 * @return vector de punteros de las especies que cumplen la condicion
 */
VDinamico<Especie*> buscaPalabraNC(const string &palabra,  VDinamico<Especie> &especies) {
	if(palabra.length() < 1) {
		throw invalid_argument("[buscaPalabraNC] palabra no válida");
	}
	VDinamico<Especie*> encontrados;
	string cadena;


	for(int i =0; i < especies.getLogico(); i++ ) {
		cadena = especies[i].get_nombre_cientifico();
		size_t sub = cadena.find(" ");
		if(cadena.substr(0, sub) == palabra) {
			encontrados.insertar(&especies[i]);
		}

	}
	return encontrados;
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


        //PUNTO 2:         INSTANCIAR Y MOSTRAR EL VECTOR DE Especies.
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

        //PUNTO 2 :         Mostrar los 50 primeros identificadores
        cout<<"==================================================="<<endl;
        cout << "Identificador de las primeras 50 especies:" << endl;
        for (int i = 0; i < 50; ++i)
        {
            cout<<to_string(i)<<": "<<vectorCompleto[i].get_codigo_especie()<<endl;
        }

        //Ordenación del vector
        cout<<"==================================================="<<endl;

        vectorCompleto.ordenar();


        //PUNTO 3 :  MOSTAR LOS PRIMEROS 50 ORDENADOS DE MENOR A MAYOR
        cout << "Vector ordenado. Mostrar las primeras 50 especies" << endl;
        for (int i = 0; i < 50; i++)
        {
            cout<<to_string(i);
            vectorCompleto[i].mostrarInfo();
        }

        //PUNTO 4:          Busqueda de posición de codigos de especies
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

        //PUNTO 5:          Búsqueda de Nombre común no nulo
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

        //PUNTO 6:          Ordenamiento mediante el metodo Burbuja
        metodoBurbuja(vectorCompleto);
    	cout<<"==================================================="<<endl;
        cout << "Vector ordenado. Mostrando las primeras 50 especies en orden inverso" << endl;
        for (int i = vectorCompleto.getLogico() - 1; i > vectorCompleto.getLogico() - 50; i--)
        {
            cout<<to_string(i);
            vectorCompleto[i].mostrarInfo();
        }

        //PUNTO 7:
    	VDinamico<Especie*> otroVectorEspecies;
    	string nombre = "Jasminum";
    	cout<<"==================================================="<<endl;
    	otroVectorEspecies = buscaPalabraNC(nombre,vectorCompleto);
    	cout << "Especies con el nombre "<<nombre<<": "<<otroVectorEspecies.getLogico() << endl;;
    	for (int i = 0; i < otroVectorEspecies.getLogico(); i++)
    	{
    		cout<<to_string(i);
    		otroVectorEspecies[i]->mostrarInfo();
    	}
    }
    catch (const exception& e)
    {
        cerr << endl << "main.cpp -> " << e.what() << endl;
        return 1;
    }
    return 0;
}
