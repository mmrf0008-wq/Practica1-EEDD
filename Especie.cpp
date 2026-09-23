//
// Created by Maitena on 19/9/2026.
//

#include "Especie.h"

#include <iostream>


/**
 *
 * @return
 */
string Especie::get_codigo_especie() const { return this->codigoEspecie; }

/**
 *
 * @param codigo_especie
 */
void Especie::set_codigo_especie(const string &codigo_especie) {
     /* if(codigoEspecie.length() < 2) {
           throw invalid_argument("[Especie::set_codigo_especie]: codigo no valido");
      }*/
      this->codigoEspecie = codigo_especie;
}

/**
 *
 * @return
 */
string Especie::get_nombre_comun() const {return this->nombreComun;}

/**
 *
 * @param nombre_comun
 */
void Especie::set_nombre_comun(const string &nombre_comun) {

     this->nombreComun = nombre_comun;
}

/**
 *
 * @return
 */
string Especie::get_nombre_cientifico() const {return this->nombreCientifico;}

/**
 *
 * @param nombre_cientifico
 */
void Especie::set_nombre_cientifico(const string &nombre_cientifico) {
      this->nombreCientifico = nombre_cientifico;
}

/**
 *
 * @return
 */
string Especie::get_tipo_planta() const {return this->tipoPlanta;}

/**
 *
 * @param tipo_planta
 */
void Especie::set_tipo_planta(const string &tipo_planta) {

      this->tipoPlanta = tipo_planta;
}

/**
 *
 * @param arr
 * @return
 */
bool Especie::operator==(const Especie &arr) {
      if(this == &arr) { //son el mismo objeto
        return true;
      }
      if(this->codigoEspecie == arr.codigoEspecie
       && this->nombreComun == arr.nombreComun
       && this->nombreCientifico == arr.nombreCientifico
       && this->tipoPlanta == arr.tipoPlanta)
       {
          return true;
      }
       return false;
}

/**
 *
 * @param arr
 * @return
 */
bool Especie::operator<(const Especie &arr) {
      if(this->codigoEspecie < arr.codigoEspecie) {
            return true;
      }
      return false;
}

/**
 * 
 * @param cod 
 * @param nombreComun 
 * @param nombreCientifico 
 * @param tipoPlanta 
 */
Especie::Especie(const string &cod, const string &nombreComun, const string &nombreCientifico,
				 const string &tipoPlanta) {

           if(cod.length()< 2) {
           throw invalid_argument("[Especie:Especie()]: codigo no válido "  );
          }

          this->codigoEspecie = cod;
          this->nombreCientifico = nombreCientifico;
          this->nombreComun = nombreComun;
          this->tipoPlanta = tipoPlanta;

}

Especie::Especie() {
	this->codigoEspecie="";
	this->nombreCientifico="";
	this->nombreComun="";
}

void Especie::mostrarInfo() {
	cout << " -------------------------------" << endl;
	cout << "Codigo especie: " << this->codigoEspecie << endl;
	cout << "Nombre común: " << this->nombreComun << endl;
	cout << "Nombre cientifico: " << this->nombreCientifico << endl;
	cout << "Tipo planta: " << this->tipoPlanta << endl;
	cout << " -------------------------------" << endl;
}


