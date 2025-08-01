#pragma once
#include <iostream>
#include <map>
#include <string>
#include <regex>

#include "Utilidades.h"
#include "CodigoCui.h"


int munisPorDepto[23] = { 0,
    /* 01 - Guatemala tiene:      */ 17 /* municipios. */, /* 02 - El Progreso tiene:    */  8 /* municipios. */, /* 03 - Sacatepéquez tiene:   */ 16 /* municipios. */,
    /* 04 - Chimaltenango tiene:  */ 16 /* municipios. */, /* 05 - Escuintla tiene:      */ 13 /* municipios. */, /* 06 - Santa Rosa tiene:     */ 14 /* municipios. */,
    /* 07 - Sololá tiene:         */ 19 /* municipios. */, /* 08 - Totonicapán tiene:    */  8 /* municipios. */, /* 09 - Quetzaltenango tiene: */ 24 /* municipios. */,
    /* 10 - Suchitepéquez tiene:  */ 21 /* municipios. */, /* 11 - Retalhuleu tiene:     */  9 /* municipios. */, /* 12 - San Marcos tiene:     */ 30 /* municipios. */,
    /* 13 - Huehuetenango tiene:  */ 32 /* municipios. */, /* 14 - Quiché tiene:         */ 21 /* municipios. */, /* 15 - Baja Verapaz tiene:   */  8 /* municipios. */,
    /* 16 - Alta Verapaz tiene:   */ 17 /* municipios. */, /* 17 - Petén tiene:          */ 14 /* municipios. */, /* 18 - Izabal tiene:         */  5 /* municipios. */,
    /* 19 - Zacapa tiene:         */ 11 /* municipios. */, /* 20 - Chiquimula tiene:     */ 11 /* municipios. */, /* 21 - Jalapa tiene:         */  7 /* municipios. */,
    /* 22 - Jutiapa tiene:        */ 17 /* municipios. */
};

/* Depas */	std::string departamentosGuatemala[22] = { "Guatemala", "El Progreso", "Sacatepequez", "Chimaltenango", "Escuintla", "Santa Rosa", "Solola", "Totonicapan", "Quetzaltenango", "Suchitepequez", "Retalhuleu", "San Marcos", "Huehuetenango", "El Quiche", "Baja Verapaz", "Alta Verapaz", "El Peten", "Izabal", "Zacapa", "Chiquimula", "Jalapa", "Jutiapa" };

/*Este mapa contiene todos los departamentos de Guatemala identificados con el numero
* de clave que tiene cada Departamento en Guatemala y el valor que contiene este mapa
* es otro mapa el cual contiene los municipios correspondientes al departamento elegido
* este segundo mapa contiene como clave el numero del municipio (en el orden en que
* estan registrados en Guatemala) y contiene como valor el nombre del municipio
* Ejemplos: 1 Guatemala 2 Santa catarina Pinula
*/
std::map<int, std::map<int, std::string>> departamentosMunicipios = {
        {1, { {1, "Guatemala"}, {2, "Santa Catarina Pinula"}, {3, "San Jose Pinula"}, {4, "San Jose Del Golfo"}, {5, "Palencia"}, {6, "Chinautla"}, {7, "San Pedro Ayampuc"}, {8, "Mixco"}, {9, "San Pedro Sacatepequez"}, {10, "San Juan Sacatepequez"}, {11, "San Raymundo"}, {12, "Chuarrancho"}, {13, "Fraijanes"}, {14, "Amatitlan"}, {15, "Villa Nueva"}, {16, "Villa Canales"}, {17, "San Miguel Petapa"} } },
        {2, { {1, "Guastatoya"}, {2, "Morazan"}, {3, "San Agustin Acasaguastlan"}, {4, "San Cristobal Acasaguastlan"}, {5, "El Jicaro"}, {6, "Sansare"}, {7, "Sanarate"}, {8, "San Antonio La Paz"} } },
        {3, { {1, "Antigua"}, {2, "Jocotenango"}, {3, "Pastores"}, {4, "Sumpango"}, {5, "Santo Domingo Xenacoj"}, {6, "Santiago Sacatepequez"}, {7, "San Bartolome Milpas Altas"}, {8, "San Lucas Sacatepequez"}, {9, "Santa Lucia Milpas Altas"}, {10, "Magdalena Milpas Altas"}, {11, "Santa Maria de Jesus"}, {12, "Ciudad Vieja"}, {13, "San Miguel Duenas"}, {14, "Alotenango"}, {15, "San Antonio Aguas Calientes"}, {16, "Santa Catarina Barahona"} } },
        {4, { {1, "Chimaltenango"}, {2, "San Jose Poaquil"}, {3, "San Martin Jilotepeque"}, {4, "San Juan Comalapa"}, {5, "Santa Apolonia"}, {6, "Tecpan Guatemala"}, {7, "Patzun"}, {8, "San Miguel Pochuta"}, {9, "Patzicia"}, {10, "Santa Cruz Balanya"}, {11, "Acatenango"}, {12, "San Pedro Yepocapa"}, {13, "San Andres Itzapa"}, {14, "Parramos"}, {15, "Zaragoza"}, {16, "El Tejar"} } },
        {5, { {1, "Escuintla"}, {2, "Santa Lucia Cotzumalguapa"}, {3, "La Democracia"}, {4, "Siquinala"}, {5, "Masagua"}, {6, "Tiquisate"}, {7, "La Gomera"}, {8, "Guanagazapa"}, {9, "San Jose"}, {10, "Iztapa"}, {11, "Palin"}, {12, "San Vicente Pacaya"}, {13, "Nueva Concepcion"} } },
        {6, { {1, "Cuilapa"}, {2, "Barberena"}, {3, "Santa Rosa de Lima"}, {4, "Casillas"}, {5, "San Rafael Las Flores"}, {6, "Oratorio"}, {7, "San Juan Tecuaco"}, {8, "Chiquimulilla"}, {9, "Taxisco"}, {10, "Santa Maria Ixhuatan"}, {11, "Guazacapan"}, {12, "Santa Cruz Naranjo"}, {13, "Pueblo Nuevo Vinas"}, {14, "Nueva Santa Rosa"} } },
        {7, { {1, "Solola"}, {2, "San Jose Chacaya"}, {3, "Santa Maria Visitacion"}, {4, "Santa Lucia Utatlan"}, {5, "Nahuala"}, {6, "Santa Catarina Ixtahuacan"}, {7, "Santa Clara La Laguna"}, {8, "Concepcion"}, {9, "San Andres Semetabaj"}, {10, "Panajachel"}, {11, "Santa Catarina Palopo"}, {12, "San Antonio Palopo"}, {13, "San Lucas Toliman"}, {14, "Santa Cruz La Laguna"}, {15, "San Pablo La Laguna"}, {16, "San Marcos La Laguna"}, {17, "San Juan La Laguna"}, {18, "San Pedro La Laguna"}, {19, "Santiago Atitlan"} } },
        {8, { {1, "Totonicapan"}, {2, "San Cristobal Totonicapan"}, {3, "San Francisco El Alto"}, {4, "San Andres Xecul"}, {5, "Momostenango"}, {6, "Santa Maria Chiquimula"}, {7, "Santa Lucia La Reforma"}, {8, "San Bartolo Aguas Calientes"} } },
        {9, { {1, "Quetzaltenango"}, {2, "Salcaja"}, {3, "Olintepeque"}, {4, "San Carlos Sija"}, {5, "Sibilia"}, {6, "Cabrican"}, {7, "Cajola"}, {8, "San Miguel Siguila"}, {9, "San Juan Ostuncalco"}, {10, "San Mateo"}, {11, "Concepcion Chiquirichapa"}, {12, "San Martin Sacatepequez"}, {13, "Almolonga"}, {14, "Cantel"}, {15, "Huitan"}, {16, "Zunil"}, {17, "Colomba Costa Cuca"}, {18, "San Francisco La Union"}, {19, "El Palmar"}, {20, "Coatepeque"}, {21, "Genova Costa Cuca"}, {22, "Flores Costa Cuca"}, {23, "La Esperanza"}, {24, "Palestina de los Altos"} } },
        {10, { {1, "Mazatenango"}, {2, "Cuyotenango"}, {3, "San Francisco Zapotitlan"}, {4, "San Bernardino"}, {5, "San Jose El Idolo"}, {6, "Santo Domingo Suchitepequez"}, {7, "San Lorenzo"}, {8, "Samayac"}, {9, "San Pablo Jocopilas"}, {10, "San Antonio Suchitepequez"}, {11, "San Miguel Panam"}, {12, "San Gabriel"}, {13, "Chicacao"}, {14, "Patulul"}, {15, "Santa Barbara"}, {16, "San Juan Bautista"}, {17, "Santo Tomas La Union"}, {18, "Zunilito"}, {19, "Pueblo Nuevo"}, {20, "Rio Bravo"} } },
        {11, { {1, "Retalhuleu"}, {2, "San Sebastian"}, {3, "Santa Cruz Mulua"}, {4, "San Martin Zapotitlan"}, {5, "San Felipe"}, {6, "San Andres Villa Seca"}, {7, "Champerico"}, {8, "Nuevo San Carlos"}, {9, "El Asintal"} } },
        {12, { {1, "San Marcos"}, {2, "San Pedro Sacatepequez"}, {3, "San Antonio Sacatepequez"}, {4, "Comitancillo"}, {5, "San Miguel Ixtahuacan"}, {6, "Concepcion Tutuapa"}, {7, "Tacana"}, {8, "Sibinal"}, {9, "Tajumulco"}, {10, "Tejutla"}, {11, "San Rafael Pie de la Cuesta"}, {12, "Nuevo Progreso"}, {13, "El Tumbador"}, {14, "San Jose El Rodeo"}, {15, "Malacatan"}, {16, "Catarina"}, {17, "Ayutla (Tecun Uman)"}, {18, "Ocos"}, {19, "San Pablo"}, {20, "El Quetzal"}, {21, "La Reforma"}, {22, "Pajapita"}, {23, "Ixchiguan"}, {24, "San Jose Ojetenan"}, {25, "San Cristobal Cucho"}, {26, "Sipacapa"}, {27, "Esquipulas Palo Gordo"}, {28, "Rio Blanco"}, {29, "San Lorenzo"} } },
        {13, { {1, "Huehuetenango"}, {2, "Chiantla"}, {3, "Malacatancito"}, {4, "Cuilco"}, {5, "Nenton"}, {6, "San Pedro Necta"}, {7, "Jacaltenango"}, {8, "San Pedro Soloma"}, {9, "San Ildefonso Ixtahuacan"}, {10, "Santa Barbara"}, {11, "La Libertad"}, {12, "La Democracia"}, {13, "San Miguel Acatan"}, {14, "San Rafael La Independencia"}, {15, "Todos Santos Cuchumatan"}, {16, "San Juan Atitan"}, {17, "Santa Eulalia"}, {18, "San Mateo Ixtatan"}, {19, "Colotenango"}, {20, "San Sebastian Huehuetenango"}, {21, "Tectitan"}, {22, "Concepcion Huista"}, {23, "San Juan Ixcoy"}, {24, "San Antonio Huista"}, {25, "San Sebastian Coatán"}, {26, "Santa Cruz Barillas"}, {27, "Aguacatan"}, {28, "San Rafael Petzal"}, {29, "San Gaspar Ixchil"}, {30, "Santiago Chimaltenango"}, {31, "Santa Ana Huista"}, {32, "Unión Cantinil"} } },
        {14, { {1, "Santa Cruz del Quiche"}, {2, "Chiche"}, {3, "Chinique"}, {4, "Zacualpa"}, {5, "Chajul"}, {6, "Sto Tomas Chichicastenango"}, {7, "Patzite"}, {8, "San Antonio Ilotenango"}, {9, "San Pedro Jocopilas"}, {10, "Cunen"}, {11, "San Juan Cotzal"}, {12, "Joyabaj"}, {13, "Nebaj"}, {14, "San Andres Sajcabaja"}, {15, "San Miguel Uspantan"}, {16, "Sacapulas"}, {17, "San Bartolome Jocotenango"}, {18, "Canilla"}, {19, "Chicaman"}, {20, "Ixcan"}, {21, "Pachalun"}, {22, "Playa Grande"} } },
        {15, { {1, "Salama"}, {2, "San Miguel Chicaj"}, {3, "Rabinal"}, {4, "Cubulco"}, {5, "Granados"}, {6, "Santa Cruz El Chol"}, {7, "San Jeronimo"}, {8, "Purulha"} } },
        {16, { {1, "Coban"}, {2, "Santa Cruz Verapaz"}, {3, "San Cristobal Verapaz"}, {4, "Tactic"}, {5, "Tamahu"}, {6, "San Miguel Tucuru"}, {7, "Panzos"}, {8, "Senahu"}, {9, "San Pedro Carcha"}, {10, "San Juan Chamelco"}, {11, "Lanquin"}, {12, "Santa Maria Cahabon"}, {13, "Chisec"}, {14, "Chahal"}, {15, "Fray Bartolome de las Casas"}, {16, "La Tinta"}, {17, "Raxruha"} } },
        {17, { {1, "Flores"}, {2, "San Jose"}, {3, "San Benito"}, {4, "San Andres"}, {5, "La Libertad"}, {6, "San Francisco"}, {7, "Santa Ana"}, {8, "Dolores"}, {9, "San Luis"}, {10, "Sayaxche"}, {11, "Melchor de Mencos"}, {12, "Poptun"} } },
        {18, { {1, "Puerto Barrios"}, {2, "Livingston"}, {3, "El Estor"}, {4, "Morales"}, {5, "Los Amates"} } },
        {19, { {1, "Zacapa"}, {2, "Estanzuela"}, {3, "Rio Hondo"}, {4, "Gualan"}, {5, "Teculutan"}, {6, "Usumatlan"}, {7, "Cabanas"}, {8, "San Diego"}, {9, "La Union"}, {10, "Huite"} } },
        {20, { {1, "Chiquimula"}, {2, "San Jose La Arada"}, {3, "San Juan La Ermita"}, {4, "Jocotan"}, {5, "Camotan"}, {6, "Olopa"}, {7, "Esquipulas"}, {8, "Concepcion Las Minas"}, {9, "Quezaltepeque"}, {10, "San Jacinto"}, {11, "Ipala"} } },
        {21, { {1, "Jalapa"}, {2, "San Pedro Pinula"}, {3, "San Luis Jilotepeque"}, {4, "San Manuel Chaparron"}, {5, "San Carlos Alzatate"}, {6, "Monjas"}, {7, "Mataquescuintla"} } },
        {22, { {1, "Jutiapa"}, {2, "El Progreso"}, {3, "Santa Catarina Mita"}, {4, "Agua Blanca"}, {5, "Asuncion Mita"}, {6, "Yupiltepeque"}, {7, "Atescatempa"}, {8, "Jerez"}, {9, "El Adelanto"}, {10, "Zapotitlan"}, {11, "Comapa"}, {12, "Jalpatagua"}, {13, "Conguaco"}, {14, "Moyuta"}, {15, "Pasaco"}, {16, "San Jose Acatempa"}, {17, "Quesada"} } }
};


    /*METODO: este metodo se encaraga de verificar que la entrada del numero de CUI sea un
    * numero entero, con 13 digitos exactos. Si esta condicion no se cumple se volvera a
    * solicitar el numero al usuario. Posterior a ello divide el numeroCUI en subcadenas
    * y realiza las respectivas validaciones con el fin de verificar la falidez de este
    * ARGUMENTO: el substd::string 10 y 11 para el noDepartamento y 13 y 13 para el noMunicipio*/

std::string CodigoCui::obtenerNoCui(int& noDepartamento, int& noMunicipio) {
    std::string numeroCui;

    while (true) {
        std::cout << "\n\t\033[3;93m" << "Ingresa tu numero de Cui: " << " \t\t\t\033[91m";
        getline(std::cin, numeroCui);
        std::cout << "\033[0m";

        // Verificar si la entrada es un número válido con exactamente 13 dígitos
        if (regex_match(numeroCui, std::regex("\\d{13}"))) {

            // Convertir subcadenas a enteros directamente
            std::string numeros = numeroCui.substr(0, 8);            //numeros
            int verificador = stoi(numeroCui.substr(8, 1));     //digito validador
            noDepartamento = stoi(numeroCui.substr(9, 2));      //digitos departamento  
            noMunicipio = stoi(numeroCui.substr(11, 2));        //digitos municipio

            int total = 0;

            for (int i = 0; i < numeros.length(); i++) {
                total += numeros[i] * (i + 2);
            }
            int modulo = (total % 11);

            auto& municipios = departamentosMunicipios[noDepartamento];
            int maxMunicipios = municipios.size();

            bool hayErrores = false;

            if (noDepartamento <= 0 || noMunicipio <= 0) {
                hayErrores = true;
                std::cout << "\n\t\033[1;3;95m" << "Cui con numeros de departamento y municipio incorrectos (digitos 10-11-12-13)" << "\033[0m" << std::endl;
                _getch();
                Utilidades::borrarLinea(3);
            }
            else if (noDepartamento <= 0 || noDepartamento > 22) {
                hayErrores = true;
                std::cout << "\n\t\033[1;3;95m" << "Cui con digitos de departamento incorrectos (digitos 10-11)" << "\033[0m" << std::endl;
                _getch();
                Utilidades::borrarLinea(3);
            }
            else if (noMunicipio <= 0 || noMunicipio > maxMunicipios) {
                hayErrores = true;
                std::cout << "\n\t\033[1;3;95m" << "Cui con digitos de municipio incorrectos (digitos 12-13)" << "\033[0m" << std::endl;
                _getch();
                Utilidades::borrarLinea(3);
            }

            if (modulo != verificador) {
                hayErrores = true;
                std::cout << "\n\t\033[1;3;95m" << "Cui con digito validador incorrecto(digito 9)" << "\033[0m" << std::endl;
                _getch();
                Utilidades::borrarLinea(3);
            }

            if (!hayErrores) {
                return numeroCui;
            }
        }
        else {
            std::cout << "\n\t\033[1;3;95m" << "La entrada debe ser 13 digitos numerico" << "\033[0m"<< std::endl;
            _getch();
            Utilidades::borrarLinea(3);
        }
    }
}

bool CodigoCui::obtenerDeptMun(std::string& numeroCui, std::string& departamento, std::string& municipio) {

    CodigoCui validadorCui;

    int noDepartamento = 0;
    int noMunicipio = 0;
    numeroCui = validadorCui.obtenerNoCui(noDepartamento, noMunicipio);

    /*En la segunda linea municipios es el map secundario, para ingresar a este
    * usa la clave que seria noDepartamento del map principal que se llama departamentosMunicipios
    * En la cuarta linea municipios que es el map secundario consta de una clave int y un valor std::string
    * el valor in sera que recorra el map secundario con la clave noMunicipio y el valor que es
    * de tipo std::string se almacenara en municipio */

    if (departamentosMunicipios.find(noDepartamento) != departamentosMunicipios.end()) {
        auto& municipios = departamentosMunicipios[noDepartamento];
        if (municipios.find(noMunicipio) != municipios.end()) {
            departamento = departamentosGuatemala[noDepartamento - 1];
            municipio = municipios[noMunicipio];

            std::cout << "\n\t\033[1;3;95m" << "Departamento de nacimiento:" << "\t\t\t\033[3;97m" << departamento << std::endl;
            std::cout << "\n\t\033[1;3;95m" << "Municipio de nacimiento:" << "\t\t\t\033[3;97m" << municipio << std::endl;
            return true;
        }
    }


    //std::cout << "Error: Departamento o municipio no encontrado." << std::endl;
    return false;
}

