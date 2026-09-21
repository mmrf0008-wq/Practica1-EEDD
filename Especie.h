//
// Created by Maitena on 19/9/2026.
//

#ifndef ESPECIE_H
#define ESPECIE_H
#include <string>

using namespace std;

class Especie {
private:
	string codigoEspecie;
	string nombreComun;
	string nombreCientifico;
	string tipoPlanta;

public:

	string codigo_especie() const;
	void set_codigo_especie(const string &codigo_especie);

	string nombre_comun() const;
	void set_nombre_comun(const string &nombre_comun);

	string nombre_cientifico() const;
	void set_nombre_cientifico(const string &nombre_cientifico);

	string tipo_planta() const;
	void set_tipo_planta(const string &tipo_planta);

	bool operator==(const Especie &arr);
	bool operator<(const Especie &arr);



};



#endif //ESPECIE_H
