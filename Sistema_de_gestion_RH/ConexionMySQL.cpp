#include "ConexionMySQL.h"

//CONSTRUCTOR: inicializacion a la base de datos con los parametros necesarios
ConexionMySQL::ConexionMySQL(const char* host, const char* usuario, const char* contrasena, const char* base_datos, int puerto) {
    // Inicializar la conexi�n MySQL
    conexion = mysql_init(0);
    // Establecer la conexi�n con la base de datos
    conexion = mysql_real_connect(conexion, host, usuario, contrasena, base_datos, puerto, NULL, 0);
}

//DESCONSTRUCTOR: Cerrar la conexion
ConexionMySQL::~ConexionMySQL() {
    // Cerrar la conexi�n MySQL
    mysql_close(conexion);
}

//Verificar el estado de la conexion
bool ConexionMySQL::estaConectado() {
    // Verificar si la conexi�n est� establecida
    return (conexion != NULL);
}
/**
 * @brief Realiza la confirmaci�n de una transacci�n en la base de datos.
 *
 * Este m�todo confirma una transacci�n previamente realizada en la base de datos.
 * Si ocurre alg�n error durante el proceso de confirmaci�n, se imprime un mensaje de error.
 *
 * @return true si la confirmaci�n se realiz� correctamente, false en caso contrario.
 */
bool ConexionMySQL::commit() {
    if (mysql_commit(conexion)) {
        // Si mysql_commit devuelve un valor distinto de cero, indica un error en el commit.
        // Se imprime un mensaje de error junto con la descripci�n del error obtenida con mysql_error.
        std::cout << "\n\t\033[1;3;95m" << "Error al realizar commit: " << mysql_error(conexion) << "\033[0m" << std::endl;
        return false;
    }
    return true;
}

/**
 * @brief Obtiene el estado actual del autocommit en la conexi�n a la base de datos.
 *
 * Este m�todo devuelve el estado actual del autocommit en la conexi�n a la base de datos.
 * Si el autocommit est� habilitado, retorna true; de lo contrario, retorna false.
 *
 * @return true si el autocommit est� habilitado, false si est� deshabilitado.
 */
bool ConexionMySQL::getAutocommit() {
    int autocommit;
    // La funci�n mysql_autocommit devuelve 0 si el autocommit est� habilitado.
    if (mysql_autocommit(conexion, TRUE) == 0) {
        autocommit = true;
    }
    else {
        autocommit = false;
    }
    return autocommit;
}

/*
* M�todo para ejecutar una consulta SQL en la base de datos.
* Recibe como argumento la consulta a ejecutar.
*
* argumento consulta La consulta SQL a ejecutar.
* @return Un puntero a una estructura MYSQL_RES que contiene los resultados de la consulta, o nullptr si hay un error.
*/
MYSQL_RES* ConexionMySQL::obtenerResultadoConsulta(const std::string& consulta) {

    // Verifica si la conexi�n con la base de datos est� establecida
    if (!estaConectado()) {
        // Si no hay conexi�n, muestra un mensaje de error y retorna un puntero nulo
        std::cout << "\n\t\033[1;3;95m" << "Error: No se pudo conectar a la base de datos" << "\033[0m" << std::endl;
        return nullptr;
    }

    // Intenta ejecutar la consulta SQL en la base de datos
    if (mysql_query(conexion, consulta.c_str())) {
        // Si hay un error al ejecutar la consulta, muestra un mensaje de error con detalles espec�ficos
        std::cout << "\n\t\033[1;3;95m" << "Error al ejecutar la consulta: " << mysql_error(conexion) << "\033[0m" << std::endl;
        // Retorna un puntero nulo indicando que no se pudieron obtener resultados
        return nullptr;
    }

    // Si la consulta se ejecuta con �xito, se obtienen los resultados y se almacenan en una estructura MYSQL_RES
    MYSQL_RES* resultados = mysql_store_result(conexion);
    // Se retorna un puntero a la estructura MYSQL_RES que contiene los resultados de la consulta
    return resultados; 
}


/**
    * Ejecuta una consulta de inserci�n en la base de datos y gestiona la transacci�n.
    *
    * @param consulta La consulta de inserci�n SQL a ejecutar.
    * @return true si la consulta de inserci�n se ejecuta correctamente y se confirma la transacci�n,
    *         false en caso de error.
    */
bool ConexionMySQL::ejecutarInsert(const std::string& consulta) {
    // Verificar si la conexi�n est� establecida
    if (!estaConectado()) {
        // Mostrar un mensaje de error si no se puede conectar a la base de datos y devolver false
        std::cout << "\n\t\033[1;3;95m" << "Error: No se pudo conectar a la base de datos" << "\033[0m" << std::endl;
        return false;
    }

    // Iniciar la transacci�n
    if (mysql_autocommit(conexion, 0) != 0) {
        // Mostrar un mensaje de error si falla al iniciar la transacci�n y devolver false
        std::cout << "\n\t\033[1;3;95m" << "Error al iniciar la transacci�n: " << mysql_error(conexion) << "\033[0m" << std::endl;
        return false;
    }

    // Ejecutar la consulta de inserci�n
    if (mysql_query(conexion, consulta.c_str())) {
        // Mostrar un mensaje de error si la consulta de inserci�n falla
        std::cout << "\n\t\033[1;3;95m" << "Error al ejecutar el insert: " << mysql_error(conexion) << "\033[0m" << std::endl;

        // Hacer rollback de la transacci�n y devolver false
        mysql_rollback(conexion);
        return false;
    }

    // Confirmar la transacci�n
    if (mysql_commit(conexion) != 0) {
        // Mostrar un mensaje de error si falla al confirmar la transacci�n
        std::cout << "\n\t\033[1;3;95m" << "Error al confirmar la transacci�n: " << mysql_error(conexion) << "\033[0m" << std::endl;

        // Hacer rollback de la transacci�n y devolver false
        mysql_rollback(conexion);
        return false;
    }

    // Imprimir un mensaje de �xito y devolver true si todo fue exitoso
    std::cout << "\n\t\033[1;3;38;5;122m" << "Datos insertados correctamente!" << "\033[0m" << std::endl;
    return true;
}


/**
    * M�todo para ejecutar una sentencia SQL de eliminaci�n en la base de datos.
    *
    * @param consulta La sentencia SQL de eliminaci�n a ejecutar.
    * @return true si la sentencia se ejecuta correctamente, false en caso de error.
    */

bool ConexionMySQL::ejecutarDelete(const std::string& consulta) {
    // Verificar si la conexi�n est� establecida
    if (!estaConectado()) {
        // Imprimir un mensaje indicando que no se pudo conectar a la base de datos y devolver false
        std::cout << "\n\t\033[1;3;95m" << "No se pudo conectar a la base de datos" << "\033[0m" << std::endl;
        return false;
    }

    // Ejecutar la consulta DELETE
    if (mysql_query(conexion, consulta.c_str())) {
        // Mostrar un mensaje de error si la consulta falla y devolver false
        std::cout << "\n\t\033[1;3;95m" << "Error al ejecutar la sentencia de eliminacion: " << mysql_error(conexion) << "\033[0m" << std::endl;
        return false;
    }

    // Si la consulta se ejecuta correctamente, imprimir un mensaje de �xito y devolver true
    std::cout << "\n\t\033[1;3;38;5;122m" << "Sentencia de eliminacion ejecutada correctamente!" << "\033[0m" << std::endl;
    return true;
}

/**
    * M�todo para ejecutar una sentencia SQL de actualizaci�n en la base de datos.
    * 
    * @param consulta La sentencia SQL de actualizaci�n a ejecutar.
    * @return true si la sentencia se ejecuta correctamente, false en caso de error.
    */
bool ConexionMySQL::ejecutarUpdate(const std::string& consulta) {
    if (!estaConectado()) {
        std::cout << "\n\t\033[1;3;95m" << "Error: No se pudo conectar a la base de datos." << "\033[0m" << std::endl;
        return false;
    }

    // Si la funci�n mysql_query devuelve un valor distinto de cero, indica un error al ejecutar la consulta.
    // Se imprime un mensaje de error junto con la descripci�n del error obtenida con mysql_error.
    if (mysql_query(conexion, consulta.c_str())) {
        std::cout << "\n\t\033[1;3;95m" << "Error al ejecutar la consulta: " << mysql_error(conexion) << "\033[0m" << std::endl;
        return false;
    }

    // Si mysql_affected_rows devuelve cero, indica que ninguna fila fue actualizada por la consulta.
    // Se imprime un mensaje indicando que no se actualizaron filas y se devuelve false.
    if (mysql_affected_rows(conexion) == 0) {
        std::cout << "\n\t\033[1;3;95m" << "No se actualizaron filas. Verifica la condici�n de la consulta." << "\033[0m" << std::endl;
        return false;
    }

    std::cout << "\n\t\033[1;3;38;5;122m" << "Datos actualizados correctamente" << "\033[0m" << std::endl;
    return true;
}

