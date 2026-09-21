//
// Created by Maitena on 19/9/2026.
//

#include "Especie.h"

/**
 * 
 * @return 
 */
string Especie::codigo_especie() const {
    return codigoEspecie;
}

/**
 * 
 * @param codigo_especie 
 */
void Especie::set_codigo_especie(const string &codigo_especie) {
    codigoEspecie = codigo_especie;
}

/**
 * 
 * @return 
 */
string Especie::nombre_comun() const {
    return nombreComun;
}

/**
 * 
 * @param nombre_comun 
 */
void Especie::set_nombre_comun(const string &nombre_comun) {
    nombreComun = nombre_comun;
}

/**
 * 
 * @return 
 */
string Especie::nombre_cientifico() const {
    return nombreCientifico;
}

/**
 * 
 * @param nombre_cientifico 
 */
void Especie::set_nombre_cientifico(const string &nombre_cientifico) {
    nombreCientifico = nombre_cientifico;
}

/**
 * 
 * @return 
 */
string Especie::tipo_planta() const {
    return tipoPlanta;
}


/**
 * 
 * @param tipo_planta 
 */
void Especie::set_tipo_planta(const string &tipo_planta) {
    tipoPlanta = tipo_planta;
}
