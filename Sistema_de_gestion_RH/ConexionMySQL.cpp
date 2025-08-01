#include "ConexionMySQL.h"

//CONSTRUCTOR: inicializacion a la base de datos con los parametros necesarios
ConexionMySQL::ConexionMySQL(const char* host, const char* usuario, const char* contrasena, const char* base_datos, int puerto) {
    // Inicializar la conexión MySQL
    conexion = mysql_init(0);
    // Establecer la conexión con la base de datos
    conexion = mysql_real_connect(conexion, host, usuario, contrasena, base_datos, puerto, NULL, 0);
}

//DESCONSTRUCTOR: Cerrar la conexion
ConexionMySQL::~ConexionMySQL() {
    // Cerrar la conexión MySQL
    mysql_close(conexion);
}

//Verificar el estado de la conexion
bool ConexionMySQL::estaConectado() {
    // Verificar si la conexión está establecida
    return (conexion != NULL);
}
/**
 * @brief Realiza la confirmación de una transacción en la base de datos.
 *
 * Este método confirma una transacción previamente realizada en la base de datos.
 * Si ocurre algún error durante el proceso de confirmación, se imprime un mensaje de error.
 *
 * @return true si la confirmación se realizó correctamente, false en caso contrario.
 */
bool ConexionMySQL::commit() {
    if (mysql_commit(conexion)) {
        // Si mysql_commit devuelve un valor distinto de cero, indica un error en el commit.
        // Se imprime un mensaje de error junto con la descripción del error obtenida con mysql_error.
        std::cout << "\n\t\033[1;3;95m" << "Error al realizar commit: " << mysql_error(conexion) << "\033[0m" << std::endl;
        return false;
    }
    return true;
}

/**
 * @brief Obtiene el estado actual del autocommit en la conexión a la base de datos.
 *
 * Este método devuelve el estado actual del autocommit en la conexión a la base de datos.
 * Si el autocommit está habilitado, retorna true; de lo contrario, retorna false.
 *
 * @return true si el autocommit está habilitado, false si está deshabilitado.
 */
bool ConexionMySQL::getAutocommit() {
    int autocommit;
    // La función mysql_autocommit devuelve 0 si el autocommit está habilitado.
    if (mysql_autocommit(conexion, TRUE) == 0) {
        autocommit = true;
    }
    else {
        autocommit = false;
    }
    return autocommit;
}

/*
* Método para ejecutar una consulta SQL en la base de datos.
* Recibe como argumento la consulta a ejecutar.
*
* argumento consulta La consulta SQL a ejecutar.
* @return Un puntero a una estructura MYSQL_RES que contiene los resultados de la consulta, o nullptr si hay un error.
*/
MYSQL_RES* ConexionMySQL::obtenerResultadoConsulta(const std::string& consulta) {

    // Verifica si la conexión con la base de datos está establecida
    if (!estaConectado()) {
        // Si no hay conexión, muestra un mensaje de error y retorna un puntero nulo
        std::cout << "\n\t\033[1;3;95m" << "Error: No se pudo conectar a la base de datos" << "\033[0m" << std::endl;
        return nullptr;
    }

    // Intenta ejecutar la consulta SQL en la base de datos
    if (mysql_query(conexion, consulta.c_str())) {
        // Si hay un error al ejecutar la consulta, muestra un mensaje de error con detalles específicos
        std::cout << "\n\t\033[1;3;95m" << "Error al ejecutar la consulta: " << mysql_error(conexion) << "\033[0m" << std::endl;
        // Retorna un puntero nulo indicando que no se pudieron obtener resultados
        return nullptr;
    }

    // Si la consulta se ejecuta con éxito, se obtienen los resultados y se almacenan en una estructura MYSQL_RES
    MYSQL_RES* resultados = mysql_store_result(conexion);
    // Se retorna un puntero a la estructura MYSQL_RES que contiene los resultados de la consulta
    return resultados; 
}


/**
    * Ejecuta una consulta de inserción en la base de datos y gestiona la transacción.
    *
    * @param consulta La consulta de inserción SQL a ejecutar.
    * @return true si la consulta de inserción se ejecuta correctamente y se confirma la transacción,
    *         false en caso de error.
    */
bool ConexionMySQL::ejecutarInsert(const std::string& consulta) {
    // Verificar si la conexión está establecida
    if (!estaConectado()) {
        // Mostrar un mensaje de error si no se puede conectar a la base de datos y devolver false
        std::cout << "\n\t\033[1;3;95m" << "Error: No se pudo conectar a la base de datos" << "\033[0m" << std::endl;
        return false;
    }

    // Iniciar la transacción
    if (mysql_autocommit(conexion, 0) != 0) {
        // Mostrar un mensaje de error si falla al iniciar la transacción y devolver false
        std::cout << "\n\t\033[1;3;95m" << "Error al iniciar la transacción: " << mysql_error(conexion) << "\033[0m" << std::endl;
        return false;
    }

    // Ejecutar la consulta de inserción
    if (mysql_query(conexion, consulta.c_str())) {
        // Mostrar un mensaje de error si la consulta de inserción falla
        std::cout << "\n\t\033[1;3;95m" << "Error al ejecutar el insert: " << mysql_error(conexion) << "\033[0m" << std::endl;

        // Hacer rollback de la transacción y devolver false
        mysql_rollback(conexion);
        return false;
    }

    // Confirmar la transacción
    if (mysql_commit(conexion) != 0) {
        // Mostrar un mensaje de error si falla al confirmar la transacción
        std::cout << "\n\t\033[1;3;95m" << "Error al confirmar la transacción: " << mysql_error(conexion) << "\033[0m" << std::endl;

        // Hacer rollback de la transacción y devolver false
        mysql_rollback(conexion);
        return false;
    }

    // Imprimir un mensaje de éxito y devolver true si todo fue exitoso
    std::cout << "\n\t\033[1;3;38;5;122m" << "Datos insertados correctamente!" << "\033[0m" << std::endl;
    return true;
}


/**
    * Método para ejecutar una sentencia SQL de eliminación en la base de datos.
    *
    * @param consulta La sentencia SQL de eliminación a ejecutar.
    * @return true si la sentencia se ejecuta correctamente, false en caso de error.
    */

bool ConexionMySQL::ejecutarDelete(const std::string& consulta) {
    // Verificar si la conexión está establecida
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

    // Si la consulta se ejecuta correctamente, imprimir un mensaje de éxito y devolver true
    std::cout << "\n\t\033[1;3;38;5;122m" << "Sentencia de eliminacion ejecutada correctamente!" << "\033[0m" << std::endl;
    return true;
}

/**
    * Método para ejecutar una sentencia SQL de actualización en la base de datos.
    * 
    * @param consulta La sentencia SQL de actualización a ejecutar.
    * @return true si la sentencia se ejecuta correctamente, false en caso de error.
    */
bool ConexionMySQL::ejecutarUpdate(const std::string& consulta) {
    if (!estaConectado()) {
        std::cout << "\n\t\033[1;3;95m" << "Error: No se pudo conectar a la base de datos." << "\033[0m" << std::endl;
        return false;
    }

    // Si la función mysql_query devuelve un valor distinto de cero, indica un error al ejecutar la consulta.
    // Se imprime un mensaje de error junto con la descripción del error obtenida con mysql_error.
    if (mysql_query(conexion, consulta.c_str())) {
        std::cout << "\n\t\033[1;3;95m" << "Error al ejecutar la consulta: " << mysql_error(conexion) << "\033[0m" << std::endl;
        return false;
    }

    // Si mysql_affected_rows devuelve cero, indica que ninguna fila fue actualizada por la consulta.
    // Se imprime un mensaje indicando que no se actualizaron filas y se devuelve false.
    if (mysql_affected_rows(conexion) == 0) {
        std::cout << "\n\t\033[1;3;95m" << "No se actualizaron filas. Verifica la condición de la consulta." << "\033[0m" << std::endl;
        return false;
    }

    std::cout << "\n\t\033[1;3;38;5;122m" << "Datos actualizados correctamente" << "\033[0m" << std::endl;
    return true;
}

