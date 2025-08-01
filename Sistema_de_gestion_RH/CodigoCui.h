#pragma once
#include <iostream>
#include <map>
#include <string>
#include <regex>

// Declaraciones de variables globales
extern int munisPorDepto[23];
extern std::string departamentosGuatemala[22];
extern std::map<int, std::map<int, std::string>> departamentosMunicipios;

class CodigoCui {
public:
    std::string obtenerNoCui(int& noDepartamento, int& noMunicipio);
    bool obtenerDeptMun(std::string& numeroCui, std::string& departamento, std::string& municipio);
};
