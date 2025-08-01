#include "Utilidades.h"

void Utilidades::limpiarPantalla() {
    // Comando especifico para limpiar la pantalla 
    system("cls");
}

/**
 * @brief Valida una cadena de texto ingresada por el usuario para asegurar que solo contenga letras.
 *
 * @param mensajeImpreso El mensaje que solicita al usuario la entrada.
 * @return std::string La cadena de texto ingresada por el usuario si es valida.
 */
std::string Utilidades::validarString(const std::string& mensajeImpreso) {
    std::string strIngresada; 

    while (true) { // Bucle para solicitar la entrada hasta que sea valida
        std::cout << "\n\t\033[3;93m" << mensajeImpreso << " \t\t\t\033[91m";
        std::getline(std::cin, strIngresada);
        std::cout << "\033[0m"; 

        // Verifica si la entrada contiene solo letras
        // Devuelve la cadena si es valida
        if (std::regex_match(strIngresada, std::regex("[a-zA-Z]+"))) { 
            return strIngresada; 
        }

        //manejo de errores: impresion, tiempo para ver el error, borrar lineas para un formato consistente
        std::cout << "\n\t\033[1;3;95m" << "La entrada debe de ser una cadena de texto" << "\033[0m" << std::endl; 
        _getch(); 
        Utilidades::borrarLinea(3); 
    }
}


/**
 * @brief Valida una direccion ingresada por el usuario para asegurar que tenga una longitud valida.
 *
 * @param mensajeImpreso El mensaje que solicita al usuario la entrada.
 * @return std::string La direccion ingresada por el usuario si es valida.
 */
std::string Utilidades::validarDireccion(const std::string& mensajeImpreso) {
    std::string strIngresada;

    while (true) { // Bucle para solicitar la entrada hasta que sea valida
        std::cout << "\n\t\033[3;93m" << mensajeImpreso << " (max 55):" << "\t\033[91m";
        std::getline(std::cin, strIngresada);
        std::cout << "\033[0m";

        // Verifica si la entrada no esta vacia y tiene una longitud valida
        // Devuelve la direccion si es valida
        if (!strIngresada.empty() && strIngresada.length() <= 55) {
            return strIngresada;
        }

        // Manejo de errores: impresion, tiempo para ver el error, borrar lineas para un formato consistente
        std::cout << "\n\t\033[1;3;95m" << "La direccion ingresada debe de contener menos de 55 caracteres" << "\033[0m" << std::endl;
        _getch();
        Utilidades::borrarLinea(3);
    }
}


/**
 * @brief Valida un nombre o apellido ingresado por el usuario y ofrece la opcion de agregar otro.
 *
 * @param mensajeImpreso El mensaje que solicita al usuario la entrada del nombre o apellido.
 * @return std::string El nombre o apellido ingresado por el usuario si es valido, o una cadena vacia si no se desea agregar otro.
 */
std::string Utilidades::validarOtroNombreApellido(const std::string& mensajeImpreso) {
    std::string opcionIngresada = " ";
    std::string nombreApellidoExtra = " ";

    while (true) { // Bucle para solicitar la entrada hasta que se decida no agregar mas nombres o apellidos
        std::cout << "\n\t\033[3;93m" << "Desea agregar otro nombre/apellido (S/N):" << "\t\033[91m";
        std::getline(std::cin, opcionIngresada);
        std::cout << "\033[0m";

        opcionIngresada = Utilidades::convertirStrMinuscula(opcionIngresada);

        if (opcionIngresada == "s") { // Si se desea agregar otro nombre o apellido
            Utilidades::borrarLinea(1);

            while (true) { // Bucle para solicitar el nombre o apellido adicional
                std::cout << "\n\t\033[3;93m" << mensajeImpreso << " \t\t\t\033[91m";
                std::getline(std::cin, nombreApellidoExtra);
                std::cout << "\033[0m";

                // Verifica si la entrada contiene solo letras y espacios
                // Devuelve el nombre o apellido adicional si es valido
                if (std::regex_match(nombreApellidoExtra, std::regex("[a-zA-Z ]+"))) {
                    return nombreApellidoExtra;
                }

                // Manejo de errores: impresion, tiempo para ver el error, borrar lineas para un formato consistente
                std::cout << "\n\t\033[1;3;95m" << "La entrada debe de ser una cadena de texto" << "\033[0m" << std::endl;
                _getch();
                Utilidades::borrarLinea(3);
            }
        }
        else if (opcionIngresada == "n") { // Si no se desea agregar otro nombre o apellido
            Utilidades::borrarLinea(1);
            break;
        }
        else { // Si la entrada no es valida
            std::cout << "\n\t\033[1;3;95m" << "Debe ingresar S o N para proseguir" << "\033[0m" << std::endl;
            _getch();
            Utilidades::borrarLinea(3);
        }
    }
}


/**
 * @brief Valida un codigo ID ingresado por el usuario, asegurandose de que tenga exactamente 8 digitos.
 *
 * @parameter El mensjae que solicita el ID del empleado
 * @return int El codigo ID validado con exactamente 8 digitos.
 */
int Utilidades::validarIdOchoDigitos(const std::string& mensajeImpreso) {
    std::string numIngresado;

    while (true) { // Bucle para solicitar la entrada hasta que sea valida
        std::cout << "\n\t\033[3;93m" << mensajeImpreso << ":\t\t\033[91m";
        std::getline(std::cin, numIngresado);
        std::cout << "\033[0m";

        // Verificar que la entrada sea un numero entero con exactamente 8 digitos
        if (std::regex_match(numIngresado, std::regex("\\d{8}"))) {
            return std::stoi(numIngresado);
        }

        // Mostrar mensaje de error si la entrada no es valida
        std::cout << "\n\t\033[1;3;95m" << "La entrada debe ser un numero entero con exactamente 8 digitos" << "\033[0m" << std::endl;
        _getch();
        Utilidades::borrarLinea(3);
    }
}

/**
 * @brief Valida un numero de telefono ingresado por el usuario, asegurandose de que tenga exactamente 8 digitos.
 *
 * @return int El numero de telefono validado con exactamente 8 digitos.
 */
int Utilidades::validarNumeroTelefono() {
    std::string numIngresado;

    while (true) { // Bucle para solicitar la entrada hasta que sea valida
        std::cout << "\n\t\033[3;93m" << "Ingresa el numero de telefono:" << "\t\t\t\033[91m";
        std::getline(std::cin, numIngresado);
        std::cout << "\033[0m";

        // Verificar que la entrada sea un numero entero con exactamente 8 digitos
        if (std::regex_match(numIngresado, std::regex("\\d{8}"))) {
            return std::stoi(numIngresado);
        }

        // Mostrar mensaje de error si la entrada no es valida
        std::cout << "\n\t\033[1;3;95m" << "La entrada debe ser un numero entero con exactamente 8 digitos" << "\033[0m" << std::endl;
        _getch();
        Utilidades::borrarLinea(3);
    }
}


/**
 * @brief Oculta la contraseña ingresada por el usuario mientras se escribe.
 *
 * @return std::string La contraseña ingresada por el usuario.
 */
std::string Utilidades::ocultarContrasena() {
    std::string contrasena;
    char caracter;
    while ((caracter = _getch()) != '\r') { // '\r' es el caracter de retorno de carro (Enter)
        std::cout << '*'; // Mostrar asteriscos en lugar de los caracteres reales
        contrasena += caracter; // Almacenar la contraseña sin mostrarla
    }
    return contrasena;
}

/**
 * @brief Valida si la contraseña cumple con los requisitos minimos de seguridad.
 *
 * @param contrasena La contraseña a validar.
 * @return bool True si la contraseña cumple con los requisitos minimos de seguridad, false en caso contrario.
 */
bool Utilidades::validarContrasena(std::string& contrasena) {
    // Verificar la longitud minima de la contraseña
    if (contrasena.length() < 8) return false;

    // Definir expresiones regulares para verificar la presencia de mayusculas, minusculas, numeros y caracteres especiales
    std::regex mayuscula("[A-Z]");
    std::regex minuscula("[a-z]");
    std::regex numero("[0-9]");
    std::regex caracterEspecial("[^a-zA-Z0-9]");

    // Verificar si la contraseña contiene al menos una mayuscula, una minuscula, un numero y un caracter especial
    return std::regex_search(contrasena, mayuscula) &&
        std::regex_search(contrasena, minuscula) &&
        std::regex_search(contrasena, numero) &&
        std::regex_search(contrasena, caracterEspecial);
}

/**
 * @brief Obtiene y valida una contraseña ingresada por el usuario.
 *
 * Muestra un mensaje indicando los requisitos minimos de la contraseña y solicita al usuario que ingrese una contraseña nueva.
 * Luego, solicita al usuario que ingrese la misma contraseña nuevamente para confirmarla.
 *
 * @param contrasena1 La primera contraseña ingresada por el usuario.
 * @param contrasena2 La segunda contraseña ingresada por el usuario para confirmarla.
 * @return std::string La contraseña validada por el usuario.
 */
std::string Utilidades::obtenerContrasenaValidada(std::string& contrasena1, std::string& contrasena2) {
    bool sonContrasenasIguales = false;

    // Mostrar requisitos minimos de la contraseña
    std::cout << "\n\t\033[1;3;38;5;122m" << "La contraseña debe tener una longitud minima de 8 caracteres e incluir al menos:" << std::endl;
    std::cout << "\n\t\033[1;3;38;5;122m" << "- (1) Caracteres especiales (@, !, $)" << std::endl;
    std::cout << "\n\t\033[1;3;38;5;122m" << "- (1) Mayusculas" << std::endl;
    std::cout << "\n\t\033[1;3;38;5;122m" << "- (1) Minusculas" << std::endl;
    std::cout << "\n\t\033[1;3;38;5;122m" << "- (1) Numeros" << "\t\t\033[91m" << std::endl;

    // Solicitar la primera contraseña y validarla
    while (!sonContrasenasIguales) {
        do {
            std::cout << "\n\t\033[3;93m" << "Ingrese la contrasena nueva:" << "\t\t\033[91m";
            contrasena1 = Utilidades::ocultarContrasena();

            // Validar la primera contraseña ingresada por el usuario
            if (!Utilidades::validarContrasena(contrasena1)) {
                std::cout << "\n\n\t\033[1;3;95m" << "La contrasena no cumple con los requisitos. Intente nuevamente." << "\033[0m" << std::endl;
                _getch();
                Utilidades::borrarLinea(3);
            }

        } while (!Utilidades::validarContrasena(contrasena1));

        // Solicitar la segunda contraseña para confirmarla
        std::cout << "\n\n\t\033[3;93m" << "Ingrese de nuevo su contrasena:" << "\t\t\033[91m";
        contrasena2 = Utilidades::ocultarContrasena();
        std::cout << std::endl;

        // Verificar si las contraseñas ingresadas son iguales
        if (contrasena1 == contrasena2) {
            sonContrasenasIguales = true;
        }
        else {
            std::cout << "\n\t\033[1;3;95m" << "Las contraseñas no coinciden. Intente nuevamente." << "\033[0m" << std::endl;
            _getch();
            Utilidades::borrarLinea(3);
        }

    }
    return contrasena1;
}


/**
 * @brief Crea una direccion de correo electronico utilizando el nombre y apellido dados.
 *
 * Esta funcion toma el primer caracter del nombre y lo combina con el apellido y el dominio "@gmail.com" para crear una direccion de correo electronico.
 *
 * @param nombre El nombre del usuario.
 * @param apellido El apellido del usuario.
 * @return std::string La direccion de correo electronico creada.
 */
std::string Utilidades::crearCorreo(std::string nombre, std::string apellido) {
    // Obtener la primera letra del nombre
    char inicialNombre = nombre[0];

    // Crear el correo electronico combinando el nombre, apellido y dominio
    std::string correo = std::string(1, inicialNombre) + apellido + "@gmail.com";

    // Convertir el correo a minusculas (opcional, si se desea)
    for (char& c : correo) {
        c = std::tolower(c);
    }
    return correo;
}

/**
 * @brief Valida un numero identificador ingresado por el usuario.
 *
 * Esta funcion solicita al usuario un numero identificador y verifica si es valido, es decir, si tiene 1 o 2 digitos.
 *
 * @param mensajeImpreso El mensaje que solicita al usuario la entrada.
 * @return int El numero identificador validado.
 */
int Utilidades::validarIdTipoIngresado(const std::string& mensajeImpreso) {
    // Variable para almacenar el numero identificador ingresado
    std::string numeroId = " ";

    // Bucle para validar continuamente la entrada del usuario
    while (true) {
        // Imprimir mensaje de solicitud con formato
        std::cout << "\n\t\033[3;93m" << mensajeImpreso << ":\t\t\033[91m";

        // Leer la entrada del usuario
        getline(std::cin, numeroId);

        // Restablecer el color de la salida
        std::cout << "\033[0m";

        // Verificar si la entrada coincide con un numero de 1 o 2 digitos
        if (std::regex_match(numeroId, std::regex("\\d{1,2}"))) {
            // Convertir la entrada a un entero y devolverla
            return std::stoi(numeroId);
        }

        // Mostrar un mensaje de error si la entrada no es valida
        std::cout << "\n\t\033[1;3;95m" << "Debe ingresar el numero identificador asociado" << "\033[0m";

        // Pausar el sistema para que el usuario pueda ver el mensaje
        system("pause");

        // Borrar la linea de la consola
        Utilidades::borrarLinea(3);
    }
}



/**
 * @brief Obtiene la fecha y hora actual en formato de cadena de caracteres.
 *
 * Esta funcion obtiene la fecha y hora actuales del sistema y las devuelve en formato de cadena de caracteres con el siguiente formato: "YYYY-MM-DD HH:MM:SS".
 *
 * @return std::string La fecha y hora actual en formato de cadena de caracteres.
 */
std::string Utilidades::obtenerFechaHoraActual() {
    // Almacenar el tiempo actual en segundos desde el epoch en la variable 't'
    time_t t = time(nullptr);

    // Estructura tm que almacenara el tiempo descompuesto en componentes
    tm now;

    /* Convertir el tiempo a la estructura tm de forma segura
     * int tm_sec;   // segundos despues del minuto - [0, 60] (incluye el segundo intercalar)
     * int tm_min;   // minutos despues de la hora - [0, 59]
     * int tm_hour;  // horas desde medianoche - [0, 23]
     * int tm_mday;  // dia del mes - [1, 31]
     * int tm_mon;   // meses desde enero - [0, 11]
     * int tm_year;  // años desde 1900 */
    localtime_s(&now, &t);

    // Formatear la fecha y hora en un string utilizando ostringstream
    // Se rellena con ceros a la izquierda si el numero tiene un solo digito
    std::ostringstream fechaHoraActual;
    fechaHoraActual << (now.tm_year + 1900) << '-'          // Año
        << std::setw(2) << std::setfill('0')    // Rellenar con ceros a la izquierda si es necesario
        << (now.tm_mon + 1) << '-'             // Mes (se suma 1 porque en la estructura tm, enero es 0)
        << std::setw(2) << std::setfill('0')    // Rellenar con ceros a la izquierda si es necesario
        << now.tm_mday << ' '                  // Dia del mes
        << std::setw(2) << std::setfill('0')    // Rellenar con ceros a la izquierda si es necesario
        << now.tm_hour << ':'                  // Hora
        << std::setw(2) << std::setfill('0')    // Rellenar con ceros a la izquierda si es necesario
        << now.tm_min << ':'                   // Minuto
        << std::setw(2) << std::setfill('0')    // Rellenar con ceros a la izquierda si es necesario
        << now.tm_sec;                         // Segundo

    // Convertir la cadena de caracteres de flujo de salida en un string y devolverlo
    return fechaHoraActual.str();
}


/**
 * @brief Genera un ID de empleado unico basado en la fecha y hora actual.
 *
 * Esta funcion genera un ID de empleado unico utilizando la fecha y hora actual en formato YYYYMMDDHHMMSS.
 *
 * @return int El ID de empleado generado.
 *             Si ocurre un error al obtener la fecha y hora actual, devuelve -1 como indicador de error.
 */

int Utilidades::generarIdEmpleado() {
    // Obtener la fecha y hora actual
    std::string fechaHora = Utilidades::obtenerFechaHoraActual();

    // Eliminar los caracteres no deseados de la fecha y hora
    fechaHora.erase(std::remove(fechaHora.begin(), fechaHora.end(), '-'), fechaHora.end());
    fechaHora.erase(std::remove(fechaHora.begin(), fechaHora.end(), ' '), fechaHora.end());
    fechaHora.erase(std::remove(fechaHora.begin(), fechaHora.end(), ':'), fechaHora.end());

    // Asegurar que la cadena tenga al menos 14 caracteres (YYYYMMDDHHMMSS)
    if (fechaHora.length() < 14) {
        // Si es menor, devolver -1 como indicador de error
        return -1;
        std::cout << fechaHora;
        _getch();
    }

    // Tomar los primeros 8 caracteres para formar el ID
    std::string idEmpleadoStr = fechaHora.substr(7, 7);
    std::string primerDigito = fechaHora.substr(6, 1);

    if (primerDigito == "0") {
        idEmpleadoStr = "1" + idEmpleadoStr;
        return stoi(idEmpleadoStr);
    }
    else {
        return stoi(idEmpleadoStr);
    }
}
/**
 * @brief Obtiene la fecha actual en formato YYYY-MM-DD.
 *
 * Esta funcion obtiene la fecha actual del sistema en formato YYYY-MM-DD.
 *
 * @return std::string La fecha actual en formato YYYY-MM-DD.
 */
std::string Utilidades::obtenerFechaActual() {
    // Almacenar el tiempo actual en segundos desde el epoch en la variable 't'
    time_t t = time(nullptr);

    // Estructura tm que almacenara el tiempo descompuesto en componentes
    tm now;

    // Convertir el tiempo a la estructura tm de forma segura
    localtime_s(&now, &t);

    // Formatear la fecha en un string utilizando ostringstream
    // Se rellena con ceros a la izquierda si el numero tiene un solo digito
    std::ostringstream fechaActual;
    fechaActual << (now.tm_year + 1900) << '-'          // Año
        << std::setw(2) << std::setfill('0')    // Rellenar con ceros a la izquierda si es necesario
        << (now.tm_mon + 1) << '-'             // Mes (se suma 1 porque en la estructura tm, enero es 0)
        << std::setw(2) << std::setfill('0')    // Rellenar con ceros a la izquierda si es necesario
        << now.tm_mday;                        // Dia del mes

    // Convertir la cadena de caracteres de flujo de salida en un string y devolverlo
    return fechaActual.str();
}


/**
 * @brief Valida el formato de una fecha ingresada por el usuario.
 *
 * Esta funcion solicita al usuario ingresar una fecha en el formato YYYY-MM-DD
 * y valida si la entrada cumple con ese formato.
 *
 * @param mensajeImpreso El mensaje que solicita al usuario la entrada.
 * @return std::string La fecha ingresada por el usuario si tiene el formato correcto.
 */
std::string Utilidades::validarFormatoFecha(const std::string mensajeImpreso) {
    tm tm = {}; // Estructura para almacenar la fecha.
    std::string fechaIngresada;

    // Ciclo para validar la entrada de fecha
    while (true) {
        // Solicitar al usuario que ingrese la fecha en el formato especificado
        std::cout << "\n\t\033[3;93m" << mensajeImpreso << ":   \t\033[91m";
        std::getline(std::cin, fechaIngresada);
        std::cout << "\033[0m";

        // Intentar leer la fecha ingresada en la estructura tm
        std::istringstream ss(fechaIngresada);
        ss >> std::get_time(&tm, "%Y-%m-%d");

        // Verificar si la lectura tuvo exito
        if (!ss.fail()) {
            // Convertir la estructura tm a un objeto de tipo time_t
            time_t t = std::mktime(&tm);

            // Verificar si la conversion fue exitosa
            if (t != -1) {
                return fechaIngresada; // Devolver la fecha ingresada como resultado
            }
        }

        // Mostrar un mensaje de error si el formato de fecha ingresado no es valido
        std::cout << "\n\t\033[1;3;95m" << "El formato de fecha ingresado no es valido" << "\033[0m" << std::endl;
        _getch();
        Utilidades::borrarLinea(3); // Limpia la pantalla para ingresar nuevamente la fecha
    }
}

/**
 * @brief Solicita al usuario que confirme la ejecucion de una consulta y valida la entrada.
 *
 * Esta funcion solicita al usuario que confirme si desea ejecutar una consulta.
 * El usuario debe ingresar 'S' para confirmar o 'N' para cancelar.
 *
 * @param mensajeImpreso El mensaje que solicita al usuario la confirmacion.
 * @return char 'S' si el usuario confirma la ejecucion, 'N' si cancela.
 */
char Utilidades::confirmarEjecutarQuery(const std::string& mensajeImpreso) {
    char respuesta;
    bool entradaValida = false;

    // Ciclo para asegurar una entrada valida ('S' o 'N')
    while (!entradaValida) {
        // Solicitar al usuario que confirme la ejecucion de la consulta
        std::cout << "\n\t\033[3;93m" << mensajeImpreso << ": \033[91m";
        std::string input;
        std::getline(std::cin, input);

        // Verificar si la entrada esta vacia
        if (input.empty()) {
            // Mostrar un mensaje de error si la entrada esta vacia
            std::cout << "\n\t\033[1;3;95m" << "Debe ingresar 'S' o 'N'. Por favor, intentelo de nuevo." << "\033[0m" << std::endl;
            _getch();
            Utilidades::borrarLinea(3);
        }
        else {
            respuesta = std::toupper(input[0]); // Convertir la entrada a mayusculas
            // Verificar si la entrada es valida ('S' o 'N')
            if (respuesta == 'S' || respuesta == 'N') {
                entradaValida = true;
            }
            else {
                // Mostrar un mensaje de error si la entrada no es valida
                std::cout << "\n\t\033[1;3;95m" << "Entrada no valida. Por favor, ingrese 'S' o 'N'." << "\033[0m" << std::endl;
                _getch();
                Utilidades::borrarLinea(3);
            }
        }
    }

    return respuesta; // Devolver la respuesta confirmada ('S' o 'N')
}

/**
 * @brief Convierte una cadena a minusculas.
 *
 * Esta funcion toma una cadena de texto y la convierte completamente a minusculas.
 *
 * @param str La cadena de texto que se va a convertir.
 * @return std::string La cadena de texto convertida a minusculas.
 */
std::string Utilidades::convertirStrMinuscula(const std::string& str) {
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(),
        [](unsigned char c) { return std::tolower(c); });
    return lowerStr;
}


/**
 * @brief Valida un ID de nomina ingresado por el usuario.
 *
 * Este metodo valida que el ID de nomina ingresado por el usuario sea un numero entero de exactamente 4 digitos.
 *
 * @return int El ID de nomina validado.
 */
int Utilidades::validarIdNomina() {
    // Metodo para realizar la validacion de entero con mensaje personalizable
    std::string ID_nominaIngresada;
    while (true) {

        std::cout << "\n\t\033[3;93m" << "Ingresa el ID de la nomina a actualizar:" << "\t\t\t\033[91m";
        std::getline(std::cin, ID_nominaIngresada);
        std::cout << "\033[0m";

        // Validar que la entrada sea un numero entero y tenga exactamente 4 digitos
        if (std::regex_match(ID_nominaIngresada, std::regex("\\d{4}"))) {
            return std::stoi(ID_nominaIngresada);
        }

        // Mostrar mensaje de error si la entrada no es un numero entero con exactamente 4 digitos
        std::cout << "\n\t\033[1;3;95m" << "El ID de la nomina debe de contener exactamente 5 digitos enteros" << "\033[0m" << std::endl;
        _getch();
        Utilidades::borrarLinea(3);
    }
}


/**
 * @brief Imprime un titulo en la consola con formato.
 *
 * Este metodo imprime un titulo en la consola con un diseño decorativo.
 *
 * @param titulo El titulo que se va a imprimir.
 */
void Utilidades::imprimirTitulo(const std::string& titulo) {
    int anchoPantalla = 120;
    std::cout << "\033[4;38;5;122m";
    for (int i = 1; i <= anchoPantalla; i++) std::cout << "*";
    std::cout << "\033[0m" << "\033[38;5;122m";
    int largoTexto = titulo.length();
    int espacios = ((anchoPantalla / 2) + largoTexto / 2);
    std::cout << "*" << std::setw(espacios) << std::right << titulo << std::setw((anchoPantalla - espacios) - 1) << "*" << std::endl;
    std::cout << "\033[53;38;5;122m";
    for (int i = 1; i <= anchoPantalla; i++) std::cout << "*";
    std::cout << "\033[0m" << std::endl;
}


/**
 * @brief Imprime una linea decorativa en la consola.
 *
 * Este metodo imprime una linea decorativa en la consola con un estilo subrayado y color verde.
 */
void Utilidades::imprimirLinea() {
    int intAnchoPantalla = 120; // Puedes ajustar este valor segun tus necesidades

    // Imprimir una linea decorativa en la consola
    std::cout << "\033[4;38;5;122m"; // Selecciona el estilo de texto para la linea (subrayado y color verde)
    std::cout << std::endl;
    for (int i = 1; i <= intAnchoPantalla; i++) {
        std::cout << "*"; // Imprime el caracter '*' para dibujar la linea
    }
    std::cout << "\033[0m" << std::endl; // Restaura el estilo de texto a su valor predeterminado
}

/**
 * @brief Borra una cierta cantidad de lineas en la consola.
 *
 * Este metodo borra una cierta cantidad de lineas en la consola moviendo el cursor hacia arriba y borrando la linea actual.
 *
 * @param cantLineas La cantidad de lineas que se van a borrar.
 */
void Utilidades::borrarLinea(int cantLineas) {
    // Borrar una cierta cantidad de lineas en la consola
    for (int i = 0; i <= cantLineas; i++) {
        std::cout << "\033[1A\033[2K"; // Mueve el cursor una linea hacia arriba y borra la linea actual
    }
}

/**
 * @brief Valida la opcion ingresada por el usuario.
 *
 * Este metodo solicita al usuario que ingrese una opcion y valida si es un numero entero de uno o dos digitos.
 *
 * @return int La opcion ingresada por el usuario.
 */
int Utilidades::validarOpcionIngresada() {
    std::string numIngresado;
    std::cout << std::endl;

    while (true) {
        // Solicitar al usuario que ingrese la opcion deseada
        std::cout << "\n\t\033[3;38;5;122m" << "Por favor ingresa la opcion deseada: " << "\033[91m";
        std::getline(std::cin, numIngresado);
        std::cout << "\033[0m";

        // Validar si la entrada es un numero entero de uno o dos digitos
        if (std::regex_match(numIngresado, std::regex("^\\d{1,2}$"))) {
            // Convertir la cadena a entero y devolverlo
            return std::stoi(numIngresado);
        }

        // Imprimir un mensaje de error si la entrada no es valida
        std::cout << "\n\t\033[1;3;95m" << "La opcion ingresada debe ser un entero de 1 o 2 digitos numericos" << "\033[0m" << std::endl;
        _getch(); // Esperar a que el usuario presione Enter
        Utilidades::borrarLinea(3); // Borrar la linea de error para mantener la consola limpia
    }
}


/**
 * @brief Valida un numero flotante ingresado por el usuario.
 *
 * Este metodo solicita al usuario que ingrese un numero flotante y valida si es no negativo y tiene hasta dos decimales.
 *
 * @param mensajeImpreso El mensaje que solicita al usuario la entrada del numero flotante.
 * @return double El numero flotante ingresado por el usuario si es valido.
 */
double Utilidades::validarNumeroFlotante(const std::string mensajeImpreso) {
    std::string numIngresado;
    while (true) {
        // Solicitar al usuario que ingrese el numero flotante
        std::cout << "\n\t\033[3;93m" << mensajeImpreso << "\t\t\033[91m";
        std::getline(std::cin, numIngresado);
        std::cout << "\033[0m";

        // Validar que la entrada sea un numero flotante no negativo con hasta dos decimales
        if (std::regex_match(numIngresado, std::regex(R"(^\d+(\.\d{1,2})?$)"))) {
            // Convertir la cadena a double y devolverlo
            return std::stod(numIngresado);
        }

        // Mostrar mensaje de error si la entrada no es un numero flotante valido
        std::cout << "\n\t\033[1;3;95m" << "La entrada debe ser un numero flotante no negativo con hasta dos decimales" << "\033[0m" << std::endl;
        _getch(); // Esperar a que el usuario presione una tecla
        Utilidades::borrarLinea(3); // Borrar la linea de error para mantener la consola limpia
    }
}

/**
 * @brief Valida una cadena de texto que puede contener espacios.
 *
 * Este metodo solicita al usuario que ingrese una cadena de texto que puede contener espacios y valida si cumple con ciertas condiciones.
 *
 * @param mensajeImpreso El mensaje que solicita al usuario la entrada de la cadena de texto.
 * @return std::string La cadena de texto ingresada por el usuario si cumple con las condiciones.
 */
std::string Utilidades::validarStringConEspacios(const std::string& mensajeImpreso) {
    std::string strIngresada;
    while (true) {
        std::cout << "\n\t\033[3;93m" << mensajeImpreso << " \t\t\t\033[91m";
        std::getline(std::cin, strIngresada);
        std::cout << "\033[0m";
        if (std::regex_match(strIngresada, std::regex("^[a-zA-Z ]{1,25}$"))) {
            return strIngresada;
        }
        std::cout << "\n\t\033[1;3;95m" << "La entrada debe ser una cadena de texto de no más de 25 caracteres alfabéticos y/o espacios" << "\033[0m" << std::endl;
        _getch();
        Utilidades::borrarLinea(3);
    }
}

/**
 * @brief Valida el cuerpo del anuncio.
 *
 * Este metodo solicita al usuario que ingrese el cuerpo del anuncio y valida si cumple con ciertas condiciones.
 *
 * @return std::string El cuerpo del anuncio ingresado por el usuario si cumple con las condiciones.
 */
std::string Utilidades::validarCuerpoDelAnuncio() {
    std::string strIngresada;
    while (true) {
        std::cout << "\n\t\033[3;93m" << "Ingresa el cuerpo del anuncio (max 200):" << "\033[91m";
        std::getline(std::cin, strIngresada);
        std::cout << "\033[0m";
        if (!strIngresada.empty() && strIngresada.length() <= 200) {
            return strIngresada;
        }
        std::cout << "\n\t\033[1;3;95m" << "El cuerpo del anuncio no puede estar vacio y debe contener menos de 200 caracteres" << "\033[0m" << std::endl;
        _getch();
        Utilidades::borrarLinea(3);
    }
}



void Menu::mostrarMenuAdministrador() {
    std::cout << "\n\t\033[1;4;3;96m" << "Opciones disponibles Administrador:" << "\033[0m" << std::endl;
    std::cout << "\n\t\033[3;95m" << "1." << "\033[93m" << " anadir un nuevo empleado" << "\033[0m";
    std::cout << "\n\t\033[3;95m" << "2." << "\033[93m" << " visualizar los empleado" << "\033[0m";
    std::cout << "\n\t\033[3;95m" << "3." << "\033[93m" << " Actualizar datos de un empleado" << "\033[0m";
    std::cout << "\n\t\033[3;95m" << "4." << "\033[93m" << " dar de baja un empleado" << "\033[0m";
    std::cout << "\n\t\033[3;95m" << "5." << "\033[93m" << " Crear una nomina nueva" << "\033[0m";
    std::cout << "\n\t\033[3;95m" << "6." << "\033[93m" << " Consultar nomina especifica" << "\033[0m";
    std::cout << "\n\t\033[3;95m" << "7." << "\033[93m" << " Anadir un nuevo departamento" << "\033[0m";
    std::cout << "\n\t\033[3;95m" << "8." << "\033[93m" << " Anadir un nuevo puesto" << "\033[0m";
    std::cout << "\n\t\033[3;95m" << "9." << "\033[93m" << " Cargar aviso a un area" << "\033[0m";
    std::cout << "\n\t\033[3;95m" << "10." << "\033[93m" << " Volver al Inicio" << "\033[0m";

}

void Menu::menuOpcionUpdate() {
    std::cout << "\n\t\033[1;4;3;96m" << "Campos que se pueden editar" << "\033[0m" << std::endl;
    std::cout << "\n\t\033[3;95m" << "1." << "\033[93m" << " Contrasena" << "\033[0m";
    std::cout << "\n\t\033[3;95m" << "2." << "\033[93m" << " Nombres" << "\033[0m";
    std::cout << "\n\t\033[3;95m" << "3." << "\033[93m" << " Apellidos" << "\033[0m";
    std::cout << "\n\t\033[3;95m" << "4." << "\033[93m" << " Telefono" << "\033[0m";
    std::cout << "\n\t\033[3;95m" << "5." << "\033[93m" << " Direccion" << "\033[0m";
    std::cout << "\n\t\033[3;95m" << "6." << "\033[93m" << " Departamento" << "\033[0]";
    std::cout << "\n\t\033[3;95m" << "7." << "\033[93m" << " Puesto" << "\033[0m";
    std::cout << "\n\t\033[3;95m" << "8." << "\033[93m" << " Rol" << "\033[0m";
}

void Menu::mostrarMenuUsuario() {
    std::cout << "\n\t\033[1;4;3;96m" << "Opciones disponibles Usuario" << "\033[0m" << std::endl;
    std::cout << "\n\t\033[3;95m" << "1." << "\033[93m" << " Visualizar mi perfil" << "\033[0m";
    std::cout << "\n\t\033[3;95m" << "2." << "\033[93m" << " Cambiar mi contrasena" << "\033[0m";
    std::cout << "\n\t\033[3;95m" << "3." << "\033[93m" << " Visualizar mi boleta de pago" << "\033[0m";
    std::cout << "\n\t\033[3;95m" << "4." << "\033[93m" << " Bandeja de entrada" << "\033[0m";
    std::cout << "\n\t\033[3;95m" << "5." << "\033[93m" << " Salir del programa" << "\033[0m";
}







