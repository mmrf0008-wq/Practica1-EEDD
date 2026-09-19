//
// Created by Maitena on 19/9/2026.
//

#ifndef VDINAMICO_H
#define VDINAMICO_H


template<class T>
class VDinamico {

	T *v;
	long int tamlog;
	long int tam;

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

	/**
	* @brief operador asignación
	* @param arr vector al que se le realizará la "copia"
	* @return objeto this, el objeto copia
	*/
	VDinamico& operator=(VDinamico &arr);

	/**
	 * @brief operador []
	* @param i posicion a devolver
	* @return objeto en posicion i
	* @pre valor i debe ser intervalo [0-tamLog]
	*/
	VDinamico& operator[](const int &i);

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
	 * @brief operador <
	* @param arr elemento con el que se realiza la comparativa
	* @return elemento menor entre ambos
	*/
	VDinamico& operator<(VDinamico &arr);

	/**
	 * @brief operador == . Verifica si ambos elementos son iguales
	* @param arr elemento con el que se realiza la comparativa
	* @return true si ambos objetos (this y arr) son iguales . False si no lo son
	*/
	bool operator==(VDinamico &arr);

	/**
	 * @brief realiza la busqueda discotomica en el vector
	* @param dato dato a buscar dentro del vector
	* @return posicion donde se encuentra el dato
	*/
	int busquedaDicotomica(const T& dato);

	/**
	 *
	* @return devuelve el tamaño lógico del vector
	*/
	unsigned int gettLogico();

	/**
	* @brief destructor del objeto
	*/
	~VDinamico();
};



#endif //VDINAMICO_H
