#pragma once

#include <iostream>
#include <regex>
#include <string>
#include <mysql.h>
#include <iomanip>
#include <stdlib.h>
#include <conio.h>
#include <chrono>
#include <ctime>
#include <sstream> 
#include <limits> // Para std::numeric_limits
#include <cctype>  


class Utilidades {
public:
	static void limpiarPantalla();
	static std::string validarString(const std::string& mensajeImpreso);
	static std::string validarDireccion(const std::string& mensajeImpreso);
	static std::string validarOtroNombreApellido(const std::string& mensajeImpreso);
	static int validarIdOchoDigitos(const std::string& mensajeImpreso);
	static int validarNumeroTelefono();
	static std::string ocultarContrasena();
	static std::string crearCorreo(std::string nombre, std::string apellido);
	static int validarIdTipoIngresado(const std::string& mensajeImpreso);
	static std::string obtenerFechaHoraActual();
	static int generarIdEmpleado();
	static std::string validarFormatoFecha(const std::string mensajeImpreso);
	static char confirmarEjecutarQuery(const std::string& mensajeImpreso);
	static void imprimirTitulo(const std::string& titulo);
	static void imprimirLinea();
	static int validarOpcionIngresada();
	static void borrarLinea(int cantLineas);
	static std::string convertirStrMinuscula(const std::string& str);
	static int validarIdNomina();
	static double validarNumeroFlotante(const std::string mensajeImpreso);
	static std::string validarStringConEspacios(const std::string& mensajeImpreso);
	static std::string obtenerFechaActual();
	static bool validarContrasena(std::string& contrasena);
	static std::string validarCuerpoDelAnuncio();
	static std::string obtenerContrasenaValidada(std::string& contrasena1, std::string& contrasena2);


};

class Menu {
public:
	static void menuOpcionUpdate();
	static void mostrarMenuUsuario();
	static void mostrarMenuAdministrador();
};



