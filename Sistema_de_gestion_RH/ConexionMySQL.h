#pragma once

#include <mysql.h>
#include <string>
#include <iostream>

class ConexionMySQL {
private:
    MYSQL* conexion;
public:
    ConexionMySQL(const char* host, const char* usuario, const char* contrasena, const char* base_datos, int puerto);
    ~ConexionMySQL();
    bool commit();
    bool getAutocommit();
    bool estaConectado();
    MYSQL_RES* obtenerResultadoConsulta(const std::string& consulta);
    bool ejecutarInsert(const std::string& consulta);
    bool ejecutarDelete(const std::string& consulta);
    bool ejecutarUpdate(const std::string& consulta);
};
