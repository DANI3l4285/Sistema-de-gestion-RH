#pragma once

#include "Utilidades.h"
#include "ConexionMySQL.h"

class Empleado {
private:

protected:
    ConexionMySQL* conexion;
public:
    Empleado(ConexionMySQL* conexionBD);
    bool obtenerTipoRol(int ID_empleado);
    bool validarCredenciales(int idEmpleado, const std::string& contrasena);
    bool obtenerDatosBasicosEmpleado(const int ID_empleado, std::string& primerNombre, std::string& primerApellido, int& ID_departamento);
    bool obtenerDatosEmpPorId(const int ID_empleado);
    bool consultarBandejaEntrada(const int ID_departamento);
    bool CambiarContrasena(const int ID_empleado);
    bool obtenerNominaDetalle(const int ID_empleado, const std::string fechaInicio);

};

class Administrador : public Empleado {
public:
    Administrador(ConexionMySQL* conexionBD);

    bool obtenerIdDisponibles(const std::string consulta);
    bool obtenerDatosEmpPorNombre(const std::string& primerNombre);
    bool obtenerTodosLosEmpleados();
    bool anadirEmpleado();
    bool darDeBajaEmpleado();
    bool actualizarDatosEmpleado();
    bool consultarEmpleados();
    bool crearNominaDetalle(int ID_nomina);
    bool crearNomina(const std::string& fechaNomina, const std::string& fechaInicio, const std::string& fechaCierre);
    int consultarNomina(const std::string& fechaInicio);
    bool actualizarNomina(const int ID_nomina);
    bool anadirNuevoDepartamento(const std::string nombreNuevoDepto);
    bool anadirNuevoPuesto(const std::string nombreNuevoPuesto, const double salarioBase);
    bool obtenerDepartamentos();
    bool cargarUnAnuncio(const int ID_departamento);

};
