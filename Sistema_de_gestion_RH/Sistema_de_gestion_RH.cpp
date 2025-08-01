#include <iostream>
#include <string>
#include <iomanip>
#include <stdlib.h>
#include <conio.h>
#include <cctype>  
#include "Utilidades.h"
#include "ConexionMySQL.h"
#include "Empleado.h"
#include "Nomina.h"

int main() {
    system("Title: Gestion de Recursos Humanos");    //TITULO DE LA CONSOLA
    bool continuarPrograma = true;

    // Ciclo principal del programa mientras siga en true se ejecutara el menu interactivo
    while (continuarPrograma) {
        Utilidades::limpiarPantalla();

        Utilidades::imprimirTitulo("- - - H U M A N - R E S O U R S E - M A N A G E M E N T - - -");
        std::cout << "\n\t\033[3;95m" << "1." << "\033[93m" << " Incion de sesion" << "\033[0m";
        std::cout << "\n\t\033[3;95m" << "2." << "\033[93m" << " Salir del programa" << "\033[0m";

        //Despues de mostrar el menu validamos la opcion que ingerso el usuario
        int opcion = Utilidades::validarOpcionIngresada();
        Utilidades::imprimirLinea();

        switch (opcion) {
        case 1:
        {
            // Se crea una instancia de ConexionMySQL en la funcion main()
            // Esta instancia se pasa como argumento al constructor de las clases,
            // donde se asigna al atributo conexion. A partir de este momento, cualquier
            // instancia de una clase creada con esta conexion tendra acceso a los metodos
            // y funcionalidades proporcionados por la clase ConexionMySQL.

            ConexionMySQL* conexion = new ConexionMySQL("localhost", "root", "1234", "human_resource_management", 3306);

            //banderas para realizar validaciones
            bool credencialesValidas = false;
            bool obtenerNombreCompleto = false;
            bool esAdministrador = false;

            //variables que serviran como parametros para querys
            int ID_empleado_login = 0;
            int ID_departamento_login = 0;
            std::string primerNombreLogin, primerApellidoLogin;

            //mientras las credenciales no sean validas volvera a solicitarlas
            while (!credencialesValidas) {
                Utilidades::limpiarPantalla();
                Utilidades::imprimirTitulo("- - - L O G I N - - - ");

                ID_empleado_login = Utilidades::validarIdOchoDigitos("Ingrese su codigo ID");
                std::cout << "\n\t\033[3;93m" << "Ingrese su contrasena:" << "\t\t\033[91m";
                std::string contrasena = Utilidades::ocultarContrasena();
                std::cout << std::endl;

                Utilidades::imprimirLinea();

                // Validar las credenciales ingresadas por el usuario mediante una consulta a la base de datos
                //adicional en el metodo se verifica el estado del empleado que no se haya dado de baja
                Empleado empleado(conexion);
                credencialesValidas = empleado.validarCredenciales(ID_empleado_login, contrasena);

                //despues que verifique que el empleado esta registrado verifica el rol que tiene
                if (credencialesValidas == true) {
                    Empleado empleado(conexion);
                    esAdministrador = empleado.obtenerTipoRol(ID_empleado_login);
                }
                else {
                    std::cout << "\n\t\033[1;3;95m" << "Credenciales incorrectas, intente de nuevo" << "\033[0m" << std::endl;
                    _getch();
                }
            }

            if (esAdministrador) {
                std::cout << "\n\t\033[1;3;38;5;122m" << "Inicio de sesion exitoso (adminstrador)" << std::endl;

                bool continuar = true;  // Controla el bucle del submenu

                while (continuar) {
                    std::cin.ignore(1000, '\n');
                    Utilidades::limpiarPantalla();

                    //instancia para obtener los datos basicos y dar la bienvenida
                    //adicional los demas datos serviran para hacer querys 
                    Empleado empleado(conexion);
                    empleado.obtenerDatosBasicosEmpleado(ID_empleado_login, primerNombreLogin, primerApellidoLogin, ID_departamento_login);
                    Utilidades::imprimirTitulo("Bienvenido " + primerNombreLogin + " " + primerApellidoLogin);

                    Menu::mostrarMenuAdministrador(); // Muestra el menu de opciones del administrador
                    opcion = Utilidades::validarOpcionIngresada();  // Verifica que la opcion ingresada sea un numero entero
                    Utilidades::imprimirLinea();

                    switch (opcion)
                    {
                    case 1:
                        Utilidades::limpiarPantalla();
                        Utilidades::imprimirTitulo(" - - - A N A D I R - U N - N U E V O - E M P L E A D O - - - ");
                        std::cout << "\n\t\033[1;3;38;5;122m" << "Antes de ingresar un dato verificar que sea correcto ya que no se permite repetir la entrada" << std::endl;
                        Utilidades::imprimirLinea();
                        {
                            Administrador admin(conexion);
                            admin.anadirEmpleado();
                        }
                        break;
                    case 2:
                        Utilidades::limpiarPantalla();
                        Utilidades::imprimirTitulo(" - - - V I S U A L I Z A R - E M P L E A D O - - - ");
                        {
                            Administrador admin(conexion);
                            admin.consultarEmpleados();
                        }
                        break;
                    case 3:
                        Utilidades::limpiarPantalla();
                        Utilidades::imprimirTitulo(" - - - A C T U A L I Z A R - D A T O S - D E - E M P L E A D O- - - ");
                        {
                            Administrador admin(conexion);
                            admin.actualizarDatosEmpleado();
                        }
                        break;
                    case 4:
                        Utilidades::limpiarPantalla();
                        Utilidades::imprimirTitulo(" - - - D A R - D E - B A J A - - - ");
                        {
                            Administrador admin(conexion);
                            admin.darDeBajaEmpleado();
                        }
                        break;
                    case 5:
                        Utilidades::limpiarPantalla();
                        Utilidades::imprimirTitulo(" - - -  G E N E R A R - N O M I N A - - - ");
                        std::cout << "\n\t\033[1;3;38;5;122m" << "Antes de ingresar un dato verificar que sea correcto ya que no se permite repetir la entrada" << std::endl;
                        {
                            std::string fechaCreacion = Utilidades::obtenerFechaHoraActual();
                            std::cout << "\n\t" << "La fecha de la creacion de la nomina es: " << fechaCreacion << std::endl;
                            std::string fechaInicio = Utilidades::validarFormatoFecha("Ingrese la fecha de comienzo de la nomina (YYYY-MM--DD)");
                            std::string fechaCierre = Utilidades::validarFormatoFecha("Ingrese la fecha de cierre de la nomina (YYYY-MM--DD)");

                            //Este bloque indica una secuencia de if anidados donde si falla en alguno arrojara un mensaje
                            //de error y no se podra continuar con el siguiente
                            Administrador admin(conexion);
                            if (admin.crearNomina(fechaCreacion, fechaInicio, fechaCierre)) {
                                Utilidades::imprimirLinea();
                                int ID_nomina = admin.consultarNomina(fechaInicio);
                                std::string ID_nominaStr = std::to_string(ID_nomina);
                                if (ID_nominaStr.length() == 4) {
                                    Utilidades::imprimirLinea();
                                    if (admin.crearNominaDetalle(ID_nomina)) {
                                        if (admin.actualizarNomina(ID_nomina)) {
                                            std::cout << "\n\t\033[1;3;38;5;122m" << "Proceso terminado correctamente!" << std::endl;
                                        }
                                        else {
                                            std::cout << "\n\t\033[1;3;95m" << "Error al actualizar nomina" << "\033[0m" << std::endl;
                                        }
                                    }
                                    else {
                                        std::cout << "\n\t\033[1;3;95m" << "Error al intentar calcular las nominas detalle" << "\033[0m" << std::endl;
                                    }
                                }
                                else {
                                    std::cout << "\n\t\033[1;3;95m" << "Error al consultar el ID de la nomina" << "\033[0m" << std::endl;
                                }
                            }
                            else {
                                std::cout << "\n\t\033[1;3;95m" << "Error al intentar crear una nomina" << "\033[0m" << std::endl;
                            }
                        }
                        break;
                    case 6:
                        Utilidades::limpiarPantalla();
                        Utilidades::imprimirTitulo(" - - -  C O N S U L T A R - N O M I N A - - - ");
                        {
                            std::string fechaInicio = Utilidades::validarFormatoFecha("Ingresa la fecha de inicio de la nomina (YYYY-MM-DD)");
                            Administrador admin(conexion);
                            admin.consultarNomina(fechaInicio);
                        }
                        break;
                    case 7:
                        Utilidades::limpiarPantalla();
                        Utilidades::imprimirTitulo(" - - - A N A D I R - N U E V O - D E P A R T A M E N T O - - - ");
                        {
                            Administrador admin(conexion);
                            std::string nombreNuevoDepto = Utilidades::validarStringConEspacios("Ingresa el nombre del nuevo departamento:");
                            admin.anadirNuevoDepartamento(nombreNuevoDepto);
                        }
                        break;
                    case 8:
                        Utilidades::limpiarPantalla();
                        Utilidades::imprimirTitulo(" - - - A N A D I R - N U E V O - P U E S T O - - - ");
                        {
                            Administrador admin(conexion);
                            std::string nombreNuevoPuesto = Utilidades::validarStringConEspacios("Ingresa el nombre del nuevo puesto");
                            double nuevoSalarioBase = Utilidades::validarNumeroFlotante("Ingrese el monto del salario Base (0.00)");
                            admin.anadirNuevoPuesto(nombreNuevoPuesto, nuevoSalarioBase);
                        }
                        break;
                    case 9:
                        Utilidades::limpiarPantalla();
                        Utilidades::imprimirTitulo(" - - - C A R G A R - U N - A N U N C I O - - - ");
                        {
                           Administrador admin(conexion);
                            admin.obtenerDepartamentos();
                            int ID_departamento = Utilidades::validarIdTipoIngresado("Ingresa el ID del departamento a cargar el anuncio");
                            admin.cargarUnAnuncio(ID_departamento);
                        }
                        break;
                    case 10:
                        //para volver a la pantalla principal unicamente cambiamos la bandera del ciclo while
                        continuar = false;  // Salir del submenu
                        break;
                    default:
                        //manejo de error en caso de una opcion no valida
                        std::cout << "\n\t\033[1;3;95m" << "Opcion no valida por favor intentelo de nuevo" << "\033[0m" << std::endl;
                        break;
                    }
                }
            }
            //En dado caso el usuario no sea administrador entramos a este else que contiene las opciones de usuario normal
            else {
                std::cout << "\n\t\033[1;3;38;5;122m" << "Inicio de sesion exitoso (usuario)" << std::endl;

                bool continuar = true;  // Controla el bucle del submenu

                while (continuar) {
                    std::cin.ignore(1000, '\n');
                    Utilidades::limpiarPantalla();

                    Empleado empleado(conexion);
                    empleado.obtenerDatosBasicosEmpleado(ID_empleado_login, primerNombreLogin, primerApellidoLogin, ID_departamento_login);
                    Utilidades::imprimirTitulo("Bienvenido " + primerNombreLogin + " " + primerApellidoLogin);

                    Menu::mostrarMenuUsuario(); // Muestra el menu de opciones del usuario
                    opcion = Utilidades::validarOpcionIngresada();  // Verifica que la opcion ingresada sea un numero entero
                    Utilidades::imprimirLinea();
                    
                    switch (opcion) {
                    case 1:
                        Utilidades::limpiarPantalla();
                        Utilidades::imprimirTitulo(" - - - V I S U A L I Z A R - M I - P E R F I L - - - ");
                        {
                            Empleado empleado(conexion);
                            empleado.obtenerDatosEmpPorId(ID_empleado_login);
                        }
                        break;
                    case 2:
                        Utilidades::limpiarPantalla();
                        Utilidades::imprimirTitulo(" - - - C A M B I A R - M I - C O N T R A S E N A - - - ");
                        {
                            Empleado empleado(conexion);
                            empleado.CambiarContrasena(ID_empleado_login);
                        }
                        break;
                    case 3:
                        Utilidades::limpiarPantalla();
                        Utilidades::imprimirTitulo(" - - - C O N S U L T A R - M I S - P A G O S - - - ");
                        {
                            Empleado empleado(conexion);
                            std::string fechaInicioNomina = Utilidades::validarFormatoFecha("Ingresa la fecha de inicio de la nomina");
                            empleado.obtenerNominaDetalle(ID_empleado_login, fechaInicioNomina);
                        }
                        break;
                    case 4:
                        Utilidades::limpiarPantalla();
                        Utilidades::imprimirTitulo(" - - - V I S U A L I Z A R - A N U N C I O S - - - ");
                        {
                            Administrador admin(conexion);
                            admin.consultarBandejaEntrada(ID_departamento_login);
                        }
                        break;
                    case 5:
                        //para volver al menu unicamente cambiamos el estado de la bandera del ciclo while
                        continuar = false;  // Salir del submenu
                        break;
                    default:
                        //manejo de errores en caso una opcion no exista
                        std::cout << "\n\t\033[1;3;95m" << "Opcion no valida por favor intentelo de nuevo" << "\033[0m" << std::endl;
                        break;
                    }
                }
            }
        }
        break;
        case 2:
            //Cerrar la ventana principal
            std::cout << "Saliendo del programa" << std::endl;
            continuarPrograma = false;
        break;
        default:
            //manejo de error por opcion no valida
            std::cout << "\n\t\033[1;3;95m" << "Opcion no valida por favor intentelo de nuevo" << "\033[0m" << std::endl;
            break;
        }
    }
    return 0;
}


