
#ifndef VDINAMICO_H
#define VDINAMICO_H
#include <cmath>
#include <stdexcept>
#include <climits>
#include <algorithm>

using namespace std;

template<class T>
class VDinamico {

	T *v;
	long int tamlog;
	long int tamfis;

public:

	/**
	* @brief  Constructor por defecto, inicializa el vector, tamaño logico a 0 y tamaño fisico a 1
	*/
	VDinamico<T>();

	/**
	 * @brief  Constructor parametrizado. El tamaño fisico será potencia de 2
	* @param tamLog tamaño logico que tendrá el vector
	* @param dato elementos a introducir dentro del vector, la cantidad de elementos dentro del vector
	* será determinada por el parametro tamLog. El tamaño fiisco será la potencia de 2 igual o mayor
	* que el tamLog
	*/
	VDinamico<T>(unsigned int tamLog, T &dato);

	/**
	 * @brief  Constructor copia
	* @param origen
	*/
	VDinamico<T>(const VDinamico<T>& origen);

	/**
	 * @brief Constructor copia parcial, crea un vector de tamaño logico numElementos a partir de posicion inicial del vector origen
	* @param origen vector al que se le hará la copia
	* @param posicionInicial poicion donde comienza la copia del vector
	* @param numElementos cantidad de elementos a copiar
	* @cond tamaño fisico será potencia de 2
	*/
	VDinamico<T>(const VDinamico<T>& origen, const  unsigned int &posicionInicial, const unsigned int &numElementos);

	bool esPotenciaDeDos(int num);
	int potenciaDeDos(int num);

	/**
	* @brief operador asignación
	* @param arr vector al que se le realizará la "copia"
	* @return objeto this, el objeto copia
	*/
	VDinamico<T>& operator=(const VDinamico &arr);

	/**
	 * @brief operador []
	* @param i posicion a devolver
	* @return objeto en posicion i
	* @pre valor i debe ser intervalo [0-tamLog]
	*/
	VDinamico<T>& operator[](const int &i);

	/**
	* @brief inserta un dato en la posicion establecida en parametro
	* @param dato Elemento a insertar
	* @param pos posicion en la que se realiza la insercion. En caso de no ser especificada
	* toma el valor UINT_MAX, lo que significa que haremos la insercion al final del vector
	* @pre pos, en caso de ser especificada, estará en intervalo [0-tamLog]
	* @post valor tamLog incrementa en 1
	*/
	void insertar(const T& dato,  unsigned int pos = UINT_MAX);

	/**
	 * @brief elimina un elemento del vector de una posicion.O(n)
	* @param pos indice donde se hará la eliminación, En caso de no ser especificado se hará en la
	* última posición
	* @return devuelve el objeto eliminado
	*/
	T borrar (unsigned int pos = UINT_MAX);


	/**
	* @brief ordena el vector de menor a mayor
	*/
	void ordenar();

	/**
	 * @brief realiza la busqueda discotomica en el vector
	* @pre Se asume que el vector esta ordenado
	* @param dato dato a buscar dentro del vector
	* @return posicion donde se encuentra el dato
	*/
	int busquedaDicotomica(const T& dato);

	/**
	 *
	* @return devuelve el tamaño lógico del vector
	*/
	unsigned int getLogico() const;

	/**
	* @brief destructor del objeto
	*/
	~VDinamico();
};

template<typename T>
VDinamico<T>::VDinamico():tamfis(1),tamlog(0) {
	v = new T[tamfis];
}

template<typename T>
VDinamico<T>::VDinamico(unsigned int tamLog, T &dato) {
	tamfis=potenciaDeDos(tamLog);

	v = new T[tamfis];
	for (int i=0;i<tamLog;i++) {
		v[i]=dato;
	}
}

template <typename T>
VDinamico<T>::VDinamico(const VDinamico<T>& origen):
	tamfis(origen.tamfis),tamlog(origen.tamlog)
{
	v = new T[tamfis];
	for (int i=0;i<tamlog;i++) {
		v[i]=origen.v[i];
	}
}

template<typename T>
VDinamico<T>::VDinamico(const VDinamico<T> &origen, const unsigned int &posicionInicial, const unsigned int &numElementos)
{
	if (posicionInicial+numElementos>origen.tamlog) {
		throw out_of_range("[VDinamico::VDinamico]: El numero de elementos supera el rango del vector.");
	}
	tamlog = numElementos;
	tamfis = potenciaDeDos(tamlog);
	v = new T[tamfis];

	for(int i=0;i<tamlog;i++) {
		v[i]=origen.v[i+posicionInicial];
	}
}


template<typename T>
bool VDinamico<T>::esPotenciaDeDos(int num) {
	if (num%2!=0) {
		return false;
	} else {
		int aux=2;
		for (int i=1;i<num;i++) {
			aux=pow(aux,i);
			if (aux==num) {
				return true;
			}
		}
		return false;
	}
}

template<typename T>
int VDinamico<T>::potenciaDeDos(int num) {
	int aux=2;
	int i=1;
	while (aux>num) {
		pow(aux,i);
		i++;
	}
	return aux;
}

template<typename T>				//vector=arr
VDinamico<T> & VDinamico<T>::operator=(const VDinamico &arr) {
	if (this != &arr) {
		delete [] v;					//Forma de eliminar un vector dinamico

		tamfis=arr.tamfis;
		tamlog=arr.tamlog;
		v = new T[tamfis];

		for (int i=0;i<tamlog;i++) {
			v[i]=arr.v[i];
		}
	}

	return *this;
}


template <typename T>
VDinamico<T>& VDinamico<T>::operator[](const int &i){
	if(i<0 || i > tamfis){
		throw new invalid_argument("[operator[]]: se ha intentado acceder a una dirección no válida");
	}
	return v[i];
}

template<typename T>
void VDinamico<T>::insertar(const T &dato, unsigned int pos) {
	if (pos > tamfis) {
		throw out_of_range("[VDinamico<T>::insertar]: La posicion dada no existe en el vector.");
	}
	if (tamfis==tamlog) {
		tamfis=potenciaDeDos(tamfis);
	}
	if (pos==UINT_MAX) {					//Insercion al final del vector
		v[tamlog]=dato;
		tamlog++;
	} else {								//Insercion en la posicion dada
		for (int i=tamlog-1;i>=pos;i--) {
			v[i+1]=v[i];
		}
		v[pos]=dato;
		tamlog++;
	}
}

template<typename T>
T VDinamico<T>::borrar(unsigned int pos) {
	if (pos > tamfis) {
		throw out_of_range("[VDinamico<T>::borrar]: La posicion dada no existe en el vector.");
	}

	if (pos == UINT_MAX) {				//Eliminar el ultimo dato del vector
		v[tamlog-1]=v[tamlog];
		tamlog--;
	} else {
		for (int i=pos;i<tamlog;i++) {	//Eliminar la posicion dada del vector
			v[i]=v[i+1];
		}
		tamlog--;
	}

	if (tamlog*3<tamfis) {				//Condicion para reducir el tamaño fisico del vector
		tamfis=tamfis/2;
	}
}

template<typename T>			//DEFINIR OBLIGATORIAMENTE LOS OPERADORES == Y < EN LA CLASE ESPECIE
void VDinamico<T>::ordenar() {	//NO HAY QUE HACERLOS EN ESTA CLASE
	sort(v,v + tamlog);
}

template<typename T>
int VDinamico<T>::busquedaDicotomica(const T &dato) {
	int inf = 0;
	int sup = tamlog-1;
	int aux;
	while (inf <= sup) {
		aux = (inf+sup)/2;
		if (v[aux]==dato) {
			return aux;
		} else if (v[aux]<dato) {
			inf = aux + 1;			//Se le suma uno pq la posicion aux ya esta comprobada, parte desde la siguiente
		} else {
			sup = aux - 1;			//Lo mismo que antes, pero al ser el limite de arriba, parte desde la posicion anterior
		}
	}
	return -1;					//Sirve para indicar que el elemento dado no existe dentro del vector
}

template<typename T>
unsigned int VDinamico<T>::getLogico() const {
	return tamlog;
}

template<typename T>
VDinamico<T>::~VDinamico() {
	delete [] v;
	v = nullptr;
}




#endif //VDINAMICO_H
