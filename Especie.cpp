//
// Created by Maitena on 19/9/2026.
//

#include "Especie.h"


string Especie::codigo_especie() const {
    return codigoEspecie;
}

void Especie::set_codigo_especie(const string &codigo_especie) {
    codigoEspecie = codigo_especie;
}

string Especie::nombre_comun() const {
    return nombreComun;
}

void Especie::set_nombre_comun(const string &nombre_comun) {
    nombreComun = nombre_comun;
}

string Especie::nombre_cientifico() const {
    return nombreCientifico;
}

void Especie::set_nombre_cientifico(const string &nombre_cientifico) {
    nombreCientifico = nombre_cientifico;
}

string Especie::tipo_planta() const {
    return tipoPlanta;
}

void Especie::set_tipo_planta(const string &tipo_planta) {
    tipoPlanta = tipo_planta;
}
