#include "Empleado.h"
#include "ConexionMySQL.h"
#include "Utilidades.h"
#include "CodigoCui.h"
#include "Nomina.h"

// Constructor solo con la conexion a la base de datos
Empleado::Empleado(ConexionMySQL* conexionBD) : conexion(conexionBD) {}

bool Empleado::validarCredenciales(int idEmpleado, const std::string& contrasena) {

    //Verifica la conexion con la base de datos accediendo al metodo mediante un puntero
    if (!conexion->estaConectado()) {
        std::cout << "Error: No se pudo conectar a la base de datos." << std::endl;
        return false;
    }

    bool estado = true;
    // Construccion de la consulta SQL para verificar si existen las credenciales
    std::string consulta = "SELECT * FROM Empleado WHERE ID_empleado = " + std::to_string(idEmpleado) + " AND Contrasena = '" + contrasena + "' AND estado = '" + std::to_string(estado) + "'";

    //Se envia la consulta realizada haciendo uso del puntero conexion que apunta a un metodo mediante ->
    MYSQL_RES* resultado = conexion->obtenerResultadoConsulta(consulta);

    if (!resultado) {
        return false;
    }

    // verifica si alguna fila coincide con el id y la contrasena ingresada
    if (mysql_num_rows(resultado) > 0) {
        mysql_free_result(resultado);
        return true;
    }
    else {
        // El usuario y/o la contraseña son invalidos
        mysql_free_result(resultado);
        return false;
    }
}

bool Empleado::obtenerTipoRol(int ID_empleado) {

    if (!conexion->estaConectado()) {
        std::cout << "Error: No se pudo conectar a la base de datos." << std::endl;
        return false;
    }

    // Consulta para obtener el tipo de rol del empleado
    std::string consulta = "SELECT ID_tipo_rol FROM Empleado WHERE ID_empleado = " + std::to_string(ID_empleado);

    // Obtener el resultado de la consulta
    MYSQL_RES* resultado = conexion->obtenerResultadoConsulta(consulta);

    if (!resultado) {
        return false;
    }

    // Verificar si se encontro algun resultado
    if (mysql_num_rows(resultado) > 0) {
        MYSQL_ROW fila = mysql_fetch_row(resultado);
        int ID_tipo_rol = atoi(fila[0]); // Convertir el ID del tipo de rol a entero

        // Verificar si el empleado es administrador (ID_tipo_puesto = 1)
        if (ID_tipo_rol == 1) {
            // Liberar el resultado de la consulta
            mysql_free_result(resultado);
            return true;
        }
    }

    // Liberar el resultado de la consulta
    mysql_free_result(resultado);
    return false; // El empleado no es administrador
}

// Metodo para obtener los datos basicos de un empleado a partir de su ID.
// Parametros:
//   - ID_empleado: El ID del empleado del cual se desean obtener los datos.
//   - primerNombre: Variable de salida donde se almacenara el primer nombre del empleado.
//   - primerApellido: Variable de salida donde se almacenara el primer apellido del empleado.
//   - ID_departamento: Variable de salida donde se almacenara el ID del departamento al que pertenece el empleado.
// Devuelve:
//   true si se obtuvieron los datos correctamente, false en caso contrario.
bool Empleado::obtenerDatosBasicosEmpleado(const int ID_empleado, std::string& primerNombre, std::string& primerApellido, int& ID_departamento) {
    // Verificar si la conexion esta establecida.
    if (!conexion->estaConectado()) {
        std::cout << "Error: No se pudo conectar a la base de datos." << std::endl;
        return false;
    }

    // Consulta SQL para obtener los datos basicos del empleado.
    std::string consultaSelect = "SELECT primerNombre, primerApellido, ID_tipo_departamento FROM empleado WHERE ID_empleado = " + std::to_string(ID_empleado);

    // Ejecutar la consulta y obtener el resultado.
    MYSQL_RES* resultado = conexion->obtenerResultadoConsulta(consultaSelect);

    // Verificar si se obtuvo un resultado valido.
    if (!resultado) {
        return false;
    }

    // Verificar si se encontraron datos en el resultado.
    if (mysql_num_rows(resultado) > 0) {
        // Obtener la primera fila de resultados.
        MYSQL_ROW fila = mysql_fetch_row(resultado);
        // Asignar los valores de la fila a las variables de salida.
        primerNombre = fila[0];
        primerApellido = fila[1];
        ID_departamento = std::stoi(fila[2]);
        // Liberar la memoria utilizada por el resultado.
        mysql_free_result(resultado);
        // Devolver true indicando que se obtuvieron los datos correctamente.
        return true;
    }

    // Liberar la memoria utilizada por el resultado.
    mysql_free_result(resultado);
    // Devolver false indicando que no se encontraron datos para el ID proporcionado.
    return false;
}



// Metodo para obtener el detalle de la nomina de un empleado para una fecha especifica.
// Parametros:
//   - ID_empleado: El ID del empleado del cual se desea obtener el detalle de la nomina.
//   - fechaInicio: La fecha de inicio de la nomina para la cual se desea obtener el detalle.
// Devuelve:
//   true si se obtuvo el detalle de la nomina correctamente, false en caso contrario.
bool Empleado::obtenerNominaDetalle(const int ID_empleado, const std::string fechaInicio) {

    // Consulta SQL para obtener el detalle de la nomina del empleado para la fecha especificada.
    std::string consultaSelect =
        "SELECT emp.ID_empleado, emp.primerNombre, emp.segundoNombre, emp.nombresAdicionales, "
        "emp.primerApellido, emp.segundoApellido, emp.apellidosAdicionales, "
        "puesto.nombrePuesto, dept.nombreDepartamento, "
        "nomDet.ID_nomina_detalle, nomDet.ID_nomina, nomDet.salarioBase, nomDet.bonificaciones, "
        "nomDet.deducciones, nomDet.IGSS, nomDet.ISR, nomDet.Intecap, nomDet.Irtra, nomDet.incentivo, "
        "nomDet.total_egresos, nomDet.liquido_recibir, " // Agregado una coma al final de la linea
        "nom.fechaInicio " // Agregado espacio antes de "nom.fechaInicio"
        "FROM empleado emp "
        "JOIN nomina_detalle nomDet ON emp.ID_empleado = nomDet.ID_empleado "
        "JOIN nomina nom ON nom.ID_nomina = nomDet.ID_nomina "
        "JOIN tipo_puesto puesto ON emp.ID_tipo_puesto = puesto.ID_tipo_puesto "
        "JOIN departamento dept ON emp.ID_tipo_departamento = dept.ID_tipo_departamento "
        "WHERE nomDet.ID_empleado = " + std::to_string(ID_empleado) + " AND nom.fechaInicio = '" + fechaInicio + "';";

    // Obtener el resultado de la consulta.
    MYSQL_RES* resultado = conexion->obtenerResultadoConsulta(consultaSelect);

    // Verificar si se obtuvo un resultado valido.
    if (!resultado) {
        std::cout << "\n\t\033[1;3;95m" << "Error: No se pudieron obtener resultados" << "\033[0m" << std::endl;
        return false;
    }

    // Verificar si no hay filas en el resultado.
    if (mysql_num_rows(resultado) == 0) {
        std::cout << "\n\t\033[1;3;95m" << "No se encontraron coincidencias" << "\033[0m" << std::endl;
        Utilidades::imprimirLinea();
        mysql_free_result(resultado);
        return false;
    }

    // Iterar sobre las filas del resultado e imprimir el detalle de la nomina.
    MYSQL_ROW fila;
    while ((fila = mysql_fetch_row(resultado))) {
        std::cout << "\n\t\033[1;3;95m" << "ID Empleado:" << "\t\t\033[3;97m" << (fila[0] ? fila[0] : 0) << "\033[0m" << std::endl;
        std::cout << "\n\t\033[1;3;95m" << "Primer Nombre:" << "\t\t\033[3;97m" << (fila[1] ? fila[1] : "N/A") << "\033[0m" << std::endl;
        std::cout << "\n\t\033[1;3;95m" << "Segundo Nombre:" << "\t\t\033[3;97m" << (fila[2] ? fila[2] : "N/A") << "\033[0m" << std::endl;
        std::cout << "\n\t\033[1;3;95m" << "Nombres Adicionales:" << "\t\033[3;97m" << (fila[3] ? fila[3] : "N/A") << "\033[0m" << std::endl;
        std::cout << "\n\t\033[1;3;95m" << "Primer Apellido:" << "\t\033[3;97m" << (fila[4] ? fila[4] : "N/A") << "\033[0m" << std::endl;
        std::cout << "\n\t\033[1;3;95m" << "Segundo Apellido:" << "\t\033[3;97m" << (fila[5] ? fila[5] : "N/A") << "\033[0m" << std::endl;
        std::cout << "\n\t\033[1;3;95m" << "Apellidos Adicionales:" << "\t\033[3;97m" << (fila[6] ? fila[6] : "N/A") << "\033[0m" << std::endl;
        std::cout << "\n\t\033[1;3;95m" << "Nombre Puesto:" << "\t\t\033[3;97m" << (fila[7] ? fila[7] : "N/A") << "\033[0m" << std::endl;
        std::cout << "\n\t\033[1;3;95m" << "Nombre Departamento:" << "\t\033[3;97m" << (fila[8] ? fila[8] : "N/A") << "\033[0m" << std::endl;
        std::cout << "\n\t\033[1;3;95m" << "ID Nomina Detalle:" << "\t\033[3;97m" << (fila[9] ? fila[9] : 0) << "\033[0m" << std::endl;
        std::cout << "\n\t\033[1;3;95m" << "ID Nomina:" << "\t\t\033[3;97m" << (fila[10] ? fila[10] : 0) << "\033[0m" << std::endl;
        std::cout << "\n\t\033[1;3;95m" << "Salario Base:" << "\t\t\033[3;97m" << "Q." << (fila[11] ? std::stod(fila[11]) : 0) << "\033[0m" << std::endl;
        std::cout << "\n\t\033[1;3;95m" << "Bonificaciones:" << "\t\t\033[3;97m" << "Q." << (fila[12] ? std::stod(fila[12]) : 0) << "\033[0m" << std::endl;
        std::cout << "\n\t\033[1;3;95m" << "Deducciones:" << "\t\t\033[3;97m" << "Q." << (fila[13] ? std::stod(fila[13]) : 0) << "\033[0m" << std::endl;
        std::cout << "\n\t\033[1;3;95m" << "IGGS:" << "\t\t\t\033[3;97m" << "Q." << (fila[14] ? std::stod(fila[14]) : 0) << "\033[0m" << std::endl;
        std::cout << "\n\t\033[1;3;95m" << "ISR:" << "\t\t\t\033[3;97m" << "Q." << (fila[15] ? std::stod(fila[15]) : 0) << "\033[0m" << std::endl;
        std::cout << "\n\t\033[1;3;95m" << "Intecap:" << "\t\t\033[3;97m" << "Q." << (fila[16] ? std::stod(fila[16]) : 0) << "\033[0m" << std::endl;
        std::cout << "\n\t\033[1;3;95m" << "Irtra:" << "\t\t\t\033[3;97m" << "Q." << (fila[17] ? std::stod(fila[17]) : 0) << "\033[0m" << std::endl;
        std::cout << "\n\t\033[1;3;95m" << "Incentivo:" << "\t\t\033[3;97m" << "Q." << (fila[18] ? std::stod(fila[18]) : 0) << "\033[0m" << std::endl;
        std::cout << "\n\t\033[1;3;95m" << "Total Egresos:" << "\t\t\033[3;97m" << "Q." << (fila[19] ? std::stod(fila[19]) : 0) << "\033[0m" << std::endl;
        std::cout << "\n\t\033[1;3;95m" << "Liquido a Recibir:" << "\t\033[53;38;5;122m" << "Q." << (fila[20] ? std::stod(fila[20]) : 0) << "\033[0m" << std::endl;
    }
    // Liberar el resultado de la consulta
    mysql_free_result(resultado);

    return true;
    
}

// Metodo para obtener los datos de un empleado por su ID
// Parametros:
// - ID_empleado: El ID del empleado que se desea buscar
// Retorna:
// - Verdadero si se encontraron y mostraron los datos del empleado con exito, falso en caso contrario
bool Empleado::obtenerDatosEmpPorId(const int ID_empleado) {
    // Mostrar el titulo de la seccion
    std::cout << "\n\t\033[1;4;3;96m" << "La persona encontrada es:" << "\033[0m" << std::endl;

    // Construir la consulta SQL para obtener los datos del empleado por su ID
    std::string consultaSelect = "SELECT emp.ID_empleado, emp.primerNombre, emp.segundoNombre, emp.nombresAdicionales, emp.primerApellido, emp.segundoApellido, emp.apellidosAdicionales, "
        "puesto.nombrePuesto, dept.nombreDepartamento, emp.telefono, emp.direccion "
        "FROM empleado emp "
        "JOIN tipo_puesto puesto ON emp.ID_tipo_puesto = puesto.ID_tipo_puesto "
        "JOIN departamento dept ON emp.ID_tipo_departamento = dept.ID_tipo_departamento "
        "WHERE emp.ID_empleado = " + std::to_string(ID_empleado);

    // Obtener el resultado de la consulta
    MYSQL_RES* resultado = conexion->obtenerResultadoConsulta(consultaSelect);

    // Verificar si se obtuvo un resultado valido
    if (!resultado) {
        // Mostrar mensaje de error si no se pudieron obtener resultados
        std::cout << "\n\t\033[1;3;95m" << "Error: No se pudieron obtener resultados" << "\033[0m" << std::endl;
        return false;
    }

    // Verificar si no hay filas en el resultado
    if (mysql_num_rows(resultado) == 0) {
        // Mostrar mensaje informativo si no se encontraron coincidencias
        std::cout << "\n\t\033[1;3;95m" << "No se encontraron coincidencias" << "\033[0m" << std::endl;
        Utilidades::imprimirLinea();
        mysql_free_result(resultado);
        return false; // No es un error no encontrar coincidencias, pero no continuaremos con el flujo
    }

    // Procesar y mostrar los resultados
    MYSQL_ROW fila;
    while ((fila = mysql_fetch_row(resultado))) {
        // Recorrer cada fila y mostrar los datos
        std::cout << "\n\t\033[1;3;95m" << "ID_empleado:" << "\t\033[3;97m"
            << (fila[0] ? fila[0] : "N / A") << "\033[0m" << std::endl;

        // Mostrar nombres
        std::cout << "\t\033[1;3;95m" << "Nombres:" << "\t\033[3;97m"
            << (fila[1] ? fila[1] : "N / A") << " "
            << (fila[2] ? fila[2] : "N / A") << " "
            << (fila[3] ? fila[3] : "N / A") << "\033[0m" << std::endl;

        // Mostrar apellidos
        std::cout << "\t\033[1;3;95m" << "Apellidos:" << "\t\033[3;97m"
            << (fila[4] ? fila[4] : "N / A") << " "
            << (fila[5] ? fila[5] : "N / A") << " "
            << (fila[6] ? fila[6] : "N / A") << "\033[0m" << std::endl;

        // Mostrar puesto y departamento
        std::cout << "\t\033[1;3;95m" << "Puesto:" << "\t\t\033[3;97m"
            << (fila[7] ? fila[7] : "N / A") << "\033[0m" << std::endl;
        std::cout << "\t\033[1;3;95m" << "Departamento:" << "\t\033[3;97m"
            << (fila[8] ? fila[8] : "N / A") << "\033[0m" << std::endl;

        // Mostrar telefono y direccion
        std::cout << "\t\033[1;3;95m" << "Telefono:" << "\t\033[3;97m"
            << (fila[9] ? fila[9] : "N / A") << "\033[0m" << std::endl;
        std::cout << "\t\033[1;3;95m" << "Direccion:" << "\t\033[3;97m"
            << (fila[10] ? fila[10] : "N / A") << "\033[0m" << std::endl;
        Utilidades::imprimirLinea(); // Separador visual entre resultados
    }
    // Liberar el resultado de la consulta
    mysql_free_result(resultado);
    return true;
}


// Metodo para consultar la bandeja de entrada de anuncios para un departamento especifico
// Parametros:
// - ID_departamento: El ID del departamento para el cual se consultan los anuncios
// Retorna:
// - Verdadero si se obtuvieron y mostraron los anuncios con exito, falso en caso contrario
bool Empleado::consultarBandejaEntrada(const int ID_departamento) {
    // Construir la consulta SQL para obtener los anuncios del departamento
    std::string consultaSelect = "SELECT Titulo, Contenido, Fecha_publicacion FROM anuncio WHERE ID_departamento = '" + std::to_string(ID_departamento) + "'";

    // Obtener el resultado de la consulta
    MYSQL_RES* resultado = conexion->obtenerResultadoConsulta(consultaSelect);

    // Verificar si se obtuvo un resultado valido
    if (!resultado) {
        // Mostrar mensaje de error si no se pudieron obtener resultados
        std::cout << "\n\t\033[1;3;95m" << "Error: No se pudieron obtener resultados" << "\033[0m" << std::endl;
        return false;
    }

    // Verificar si no hay filas en el resultado
    if (mysql_num_rows(resultado) == 0) {
        // Mostrar mensaje informativo si no hay anuncios en la bandeja de entrada
        std::cout << "\n\t\033[1;3;95m" << "Ningun anuncio por el momento" << "\033[0m" << std::endl;
        Utilidades::imprimirLinea();
        mysql_free_result(resultado);
        return false;
    }

    // Instanciar un objeto de la clase Nomina para poder usar sus metodos
    Nomina nomina(conexion);

    // Procesar y mostrar los resultados
    MYSQL_ROW fila;
    while ((fila = mysql_fetch_row(resultado))) {
        // Mostrar el titulo del anuncio
        std::cout << "\n\t\033[1;3;95m" << "Titulo:" << " \033[3;97m"
            << (fila[0] ? fila[0] : "N / A") << "\033[0m" << std::endl;

        // Mostrar el contenido del anuncio
        std::cout << "\n\t\033[1;3;95m" << "Mensaje:" << " \033[3;97m"
            << (fila[1] ? fila[1] : "N / A") << "\033[0m" << std::endl;

        // Mostrar la fecha de publicacion del anuncio
        std::cout << "\n\t\033[1;3;95m" << "Fecha de publicacion:" << " \033[3;97m"
            << (fila[2] ? fila[2] : "N / A") << "\033[0m" << std::endl;

        Utilidades::imprimirLinea(); // Separador visual entre anuncios
    }

    // Liberar el resultado de la consulta
    mysql_free_result(resultado);

    return true;
}

// Metodo para cambiar la contraseña de un empleado
// Parametros:
// - ID_empleado: El ID del empleado cuya contraseña se desea cambiar
// Retorna:
// - Verdadero si la contraseña se actualizo correctamente, falso en caso contrario
bool Empleado::CambiarContrasena(const int ID_empleado) {
    std::string contrasena1;
    std::string contrasena2;

    // Limpiar la pantalla y mostrar el titulo para la accion de actualizar contraseña
    Utilidades::limpiarPantalla();
    Utilidades::imprimirTitulo(" - - - A C T U A L I Z A R - C O N T R A S E N A - - - ");

    // Obtener la nueva contraseña validada del usuario
    std::string contrasena = Utilidades::obtenerContrasenaValidada(contrasena1, contrasena2);

    // Construir la consulta SQL para actualizar la contraseña en la base de datos
    std::string consultaUpdate = "UPDATE empleado SET "
        "contrasena = '" + contrasena + "' "
        "WHERE ID_empleado = " + std::to_string(ID_empleado);

    // Ejecutar la consulta de actualizacion de la contraseña
    if (conexion->ejecutarUpdate(consultaUpdate)) {
        // Mostrar mensaje de exito si la contraseña se actualizo correctamente
        std::cout << "\n\t\033[1;3;38;5;122m" << "Contrasena actualizada correctamente!" << std::endl;
        return true;
    }
    else {
        // Mostrar mensaje de error si hubo un problema al actualizar la contraseña
        std::cout << "\n\t\033[1;3;95m" << "Error al actualizar la contrasena del empleado" << "\033[0m" << std::endl;
        _getch(); // Pausar para que el usuario pueda ver el mensaje antes de continuar
        return false;
    }
}

// Constructor de la clase Administrador que hereda de Empleado
// Parametros:
// - conexionBD: Puntero a la instancia de la clase ConexionMySQL para la conexion a la base de datos
Administrador::Administrador(ConexionMySQL* conexionBD) : Empleado(conexionBD) {}


// Metodo para obtener IDs disponibles segun una consulta dada
// Parametros:
// - consulta: Consulta SQL para obtener los IDs disponibles
// Retorna:
// - true si se obtuvieron los resultados correctamente, false si ocurrio un error
bool Administrador::obtenerIdDisponibles(const std::string consulta) {
    // Obtener el resultado de la consulta
    MYSQL_RES* resultado = conexion->obtenerResultadoConsulta(consulta);

    // Verificar si se obtuvo un resultado valido
    if (!resultado) {
        std::cout << "\n\t\033[1;3;95m" << "No se pudieron obtener resultados" << "\033[0m" << std::endl;
        return false;
    }

    // Procesar y mostrar los resultados
    MYSQL_ROW fila;
    while ((fila = mysql_fetch_row(resultado))) {
        // Recorrer cada fila y mostrar los datos
        std::cout << "\t\033[1;3;95m" << fila[0] << "\033[3;97m " << fila[1] << std::endl;
    }

    // Liberar el resultado de la consulta
    mysql_free_result(resultado);
    return true;
}


// Metodo para obtener los datos de un empleado por su primer nombre
// Parametros:
// - primerNombre: Primer nombre del empleado a buscar
// Retorna:
// - true si se encontraron datos del empleado, false si no se encontraron o ocurrio un error
bool Administrador::obtenerDatosEmpPorNombre(const std::string& primerNombre) {

    std::cout << "\n\t\033[1;4;3;96m" << "La persona encontrada es:" << "\033[0m" << std::endl;

    // Consulta SQL para obtener los datos del empleado por su primer nombre
    std::string consultaSelect = "SELECT emp.ID_empleado, emp.primerNombre, emp.segundoNombre, emp.nombresAdicionales, emp.primerApellido, emp.segundoApellido, emp.apellidosAdicionales, "
        "puesto.nombrePuesto, dept.nombreDepartamento, emp.telefono, emp.direccion "
        "FROM empleado emp "
        "JOIN tipo_puesto puesto ON emp.ID_tipo_puesto = puesto.ID_tipo_puesto "
        "JOIN departamento dept ON emp.ID_tipo_departamento = dept.ID_tipo_departamento "
        "WHERE emp.primerNombre = '" + primerNombre + "'";

    // Obtener el resultado de la consulta
    MYSQL_RES* resultado = conexion->obtenerResultadoConsulta(consultaSelect);

    // Verificar si se obtuvo un resultado valido
    if (!resultado) {
        std::cout << "\n\t\033[1;3;95m" << "Error: No se pudieron obtener resultados" << "\033[0m" << std::endl;
        return false;
    }

    // Verificar si no hay filas en el resultado
    if (mysql_num_rows(resultado) == 0) {
        std::cout << "\n\t\033[1;3;95m" << "No se encontraron coincidencias" << "\033[0m" << std::endl;
        Utilidades::imprimirLinea();
        mysql_free_result(resultado);
        return false; // No es un error no encontrar coincidencias, pero no continuaremos con el flujo
    }

    // Procesar y mostrar los resultados
    MYSQL_ROW fila;
    while ((fila = mysql_fetch_row(resultado))) {
        // Recorrer cada fila y mostrar los datos del empleado encontrado
        std::cout << "\n\t\033[1;3;95m" << "ID_empleado:" << "\t\033[3;97m"
            << (fila[0] ? fila[0] : "N / A") << "\033[0m" << std::endl;
        std::cout << "\t\033[1;3;95m" << "Nombres:" << "\t\033[3;97m"
            << (fila[1] ? fila[1] : "N / A") << " "
            << (fila[2] ? fila[2] : "N / A") << " "
            << (fila[3] ? fila[3] : "N / A") << "\033[0m" << std::endl;
        std::cout << "\t\033[1;3;95m" << "Apellidos:" << "\t\033[3;97m"
            << (fila[4] ? fila[4] : "N / A") << " "
            << (fila[5] ? fila[5] : "N / A") << " "
            << (fila[6] ? fila[6] : "N / A") << "\033[0m" << std::endl;
        std::cout << "\t\033[1;3;95m" << "Puesto:" << "\t\t\033[3;97m"
            << (fila[7] ? fila[7] : "N / A") << "\033[0m" << std::endl;
        std::cout << "\t\033[1;3;95m" << "Departamento:" << "\t\033[3;97m"
            << (fila[8] ? fila[8] : "N / A") << "\033[0m" << std::endl;
        std::cout << "\t\033[1;3;95m" << "Telefono:" << "\t\033[3;97m"
            << (fila[9] ? fila[9] : "N / A") << "\033[0m" << std::endl;
        std::cout << "\t\033[1;3;95m" << "Direccion:" << "\t\033[3;97m"
            << (fila[10] ? fila[10] : "N / A") << "\033[0m" << std::endl;
        Utilidades::imprimirLinea();
    }

    // Liberar el resultado de la consulta
    mysql_free_result(resultado);
    return true;
}


// Metodo para obtener todos los empleados registrados
// Retorna:
// - true si se encontraron empleados registrados, false si no se encontraron o ocurrio un error
bool Administrador::obtenerTodosLosEmpleados() {

    // Consulta SQL para obtener los datos del empleado por su primer nombre
    std::string consultaSelect = "SELECT emp.ID_empleado, emp.primerNombre, emp.segundoNombre, emp.nombresAdicionales, emp.primerApellido, emp.segundoApellido, emp.apellidosAdicionales, "
        "puesto.nombrePuesto, dept.nombreDepartamento, emp.telefono, emp.direccion, emp.estado "
        "FROM empleado emp "
        "JOIN tipo_puesto puesto ON emp.ID_tipo_puesto = puesto.ID_tipo_puesto "
        "JOIN departamento dept ON emp.ID_tipo_departamento = dept.ID_tipo_departamento";

    // Obtener el resultado de la consulta
    MYSQL_RES* resultado = conexion->obtenerResultadoConsulta(consultaSelect);

    // Verificar si se obtuvo un resultado valido
    if (!resultado) {
        std::cout << "\n\t\033[1;3;95m" << "Error: No se pudieron obtener resultados" << "\033[0m" << std::endl;
        return false;
    }

    // Verificar si no hay filas en el resultado
    if (mysql_num_rows(resultado) == 0) {
        std::cout << "\n\t\033[1;3;95m" << "No se encontraron coincidencias" << "\033[0m" << std::endl;
        Utilidades::imprimirLinea();
        mysql_free_result(resultado);
        return false; // No es un error no encontrar coincidencias, pero no continuaremos con el flujo
    }

    // Procesar y mostrar los resultados
    MYSQL_ROW fila;
    while ((fila = mysql_fetch_row(resultado))) {
        // Declaración de variables para almacenar los valores
        std::string idEmpleado;
        std::string nombres;
        std::string apellidos;
        std::string puesto;
        std::string departamento;
        std::string telefono;
        std::string direccion;
        int estado;

        // Asignación de valores a las variables
        idEmpleado = fila[0] ? fila[0] : "N / A";
        nombres = std::string(fila[1] ? fila[1] : "N / A") + " " +
            std::string(fila[2] ? fila[2] : "N / A") + " " +
            std::string(fila[3] ? fila[3] : "N / A");
        apellidos = std::string(fila[4] ? fila[4] : "N / A") + " " +
            std::string(fila[5] ? fila[5] : "N / A") + " " +
            std::string(fila[6] ? fila[6] : "N / A");
        puesto = fila[7] ? fila[7] : "N / A";
        departamento = fila[8] ? fila[8] : "N / A";
        telefono = fila[9] ? fila[9] : "N / A";
        direccion = fila[10] ? fila[10] : "N / A";
        estado = fila[11] ? std::stoi(fila[11]) : 0;

        if (estado == 1) {
            // Ahora puedes usar las variables en lugar de imprimirlas directamente
            std::cout << "\n\t\033[1;3;95m" << "ID_empleado:" << "\t\033[3;97m" << idEmpleado << "\033[0m" << std::endl;
            std::cout << "\t\033[1;3;95m" << "Nombres:" << "\t\033[3;97m" << nombres << "\033[0m" << std::endl;
            std::cout << "\t\033[1;3;95m" << "Apellidos:" << "\t\033[3;97m" << apellidos << "\033[0m" << std::endl;
            std::cout << "\t\033[1;3;95m" << "Puesto:" << "\t\t\033[3;97m" << puesto << "\033[0m" << std::endl;
            std::cout << "\t\033[1;3;95m" << "Departamento:" << "\t\033[3;97m" << departamento << "\033[0m" << std::endl;
            std::cout << "\t\033[1;3;95m" << "Telefono:" << "\t\033[3;97m" << telefono << "\033[0m" << std::endl;
            std::cout << "\t\033[1;3;95m" << "Direccion:" << "\t\033[3;97m" << direccion << "\033[0m" << std::endl;
            Utilidades::imprimirLinea();

        }
    }

    // Liberar el resultado de la consulta
    mysql_free_result(resultado);
    return true;
}


// Metodo para añadir un nuevo empleado al sistema
// Retorna:
// - true si el empleado se añadio correctamente, false si no se pudo añadir o la operacion fue cancelada
bool Administrador::anadirEmpleado() {
    // Obtener la fecha actual para la fecha de contratacion
    std::string nuevaFechaContratacion = Utilidades::obtenerFechaActual();
    std::cout << "\n\t\033[3;93m" << "La fecha de contratacion es:" << "\t\033[91m" << nuevaFechaContratacion << "\033[0m" << std::endl;

    // Generar un nuevo ID de empleado
    int nuevoID_empleado = Utilidades::generarIdEmpleado();
    std::cout << "\n\t\033[3;93m" << "El ID asignado del empleado es:" << "\t\033[91m" << nuevoID_empleado << "\033[0m" << std::endl;

    // Asignar la contraseña inicial como el ID del empleado
    std::string nuevaContrasena = std::to_string(nuevoID_empleado);
    std::cout << "\n\t\033[3;93m" << "La contrasena del empleado es:" << "\t\033[91m" << nuevaContrasena << "\033[0m" << std::endl;

    // Solicitar y validar los datos del nuevo empleado
    std::string nuevoPrimerNombre = Utilidades::validarString("Ingresa el primer Nombre:");
    std::string nuevoSegundoNombre = Utilidades::validarString("Ingresa el segundo Nombre:");
    std::string nuevosNombresAdicionales = Utilidades::validarOtroNombreApellido("Ingrese los nombres extra:");
    std::string nuevoPrimerApellido = Utilidades::validarStringConEspacios("Ingresa el primer Apellido:");
    std::string nuevoSegundoApellido = Utilidades::validarStringConEspacios("Ingresa el segundo Apellido:");
    std::string nuevosApellidosAdicionales = Utilidades::validarOtroNombreApellido("Ingrese los apellidos extra:");
    std::string nuevoCorreo = Utilidades::crearCorreo(nuevoPrimerNombre, nuevoPrimerApellido);
    std::cout << "\n\t\033[3;93m" << "El correo electronico asignado es: \t\t\033[91m" << nuevoCorreo << "\033[0m" << std::endl;
    Utilidades::imprimirLinea();

    CodigoCui validadorCui;
    std::string nuevoNumeroCui = " ", nuevoDepartamentoNac = " ", nuevoMunicipioNac = " ";
    validadorCui.obtenerDeptMun(nuevoNumeroCui, nuevoDepartamentoNac, nuevoMunicipioNac);
    Utilidades::imprimirLinea();
    int nuevoTelefono = Utilidades::validarNumeroTelefono(); //verificacion de enteros y 8 digitos
    std::string nuevaDireccion = Utilidades::validarDireccion("Ingresa la direccion o domicilio");

    std::string nuevaFechaNac = Utilidades::validarFormatoFecha("Ingrese la fecha de nacimiento (yyyy-mm-dd)");
    Utilidades::imprimirLinea();

    // Mostrar los generos disponibles y solicitar al usuario que elija uno
    std::cout << "\n\t\033[1;4;3;96m" << "Generos disponibles:" << "\033[0m" << std::endl << std::endl;
    std::string consulta = "Select * from tipo_genero";
    Administrador genero(conexion);
    bool mostrarGeneros = genero.obtenerIdDisponibles(consulta);
    int ID_tipo_genero = Utilidades::validarIdTipoIngresado("Ingresa el numero de genero a asignar");
    Utilidades::imprimirLinea();

    // Mostrar los puestos disponibles y solicitar al usuario que elija uno
    std::cout << "\n\t\033[1;4;3;96m" << "Puestos disponibles:" << "\033[0m" << std::endl << std::endl;
    Administrador puesto(conexion);
    consulta = "Select * from tipo_puesto";
    bool mostrarPuestos = puesto.obtenerIdDisponibles(consulta);
    int ID_tipo_puesto = Utilidades::validarIdTipoIngresado("Ingresa el numero de puesto a asignar");
    Utilidades::imprimirLinea();

    // Mostrar los departamentos disponibles y solicitar al usuario que elija uno
    std::cout << "\n\t\033[1;4;3;96m" << "Departamentos disponibles:" << "\033[0m" << std::endl << std::endl;
    consulta = "Select * from departamento";
    Administrador departamento(conexion);
    bool mostrarDepartamentos = departamento.obtenerIdDisponibles(consulta);
    int ID_tipo_departamento = Utilidades::validarIdTipoIngresado("Ingresa el numero de depto a asignar:");
    Utilidades::imprimirLinea();

    // Mostrar los roles disponibles y solicitar al usuario que elija uno
    std::cout << "\n\t\033[1;4;3;96m" << "Roles disponibles:" << "\033[0m" << std::endl << std::endl;
    consulta = "Select * from tipo_rol";
    Administrador rol(conexion);
    bool mostrarRoles = rol.obtenerIdDisponibles(consulta);
    int ID_tipo_rol = Utilidades::validarIdTipoIngresado("Ingresa el numero de rol a asignar:");
    Utilidades::imprimirLinea();

    char respuesta = Utilidades::confirmarEjecutarQuery("Ingrese 'S' para realizar el insert o 'N' para cancelar");
    if (respuesta == 'S') {
        consulta = "INSERT INTO empleado (ID_empleado, fechaContratacion, contrasena, primerNombre, segundoNombre, nombresAdicionales, primerApellido, segundoApellido, apellidosAdicionales, correo, numeroCui, departamentoNac, municipioNac, telefono, direccion, fechaNacimiento, ID_tipo_genero, ID_tipo_departamento, ID_tipo_puesto, ID_tipo_rol) VALUES ('" + std::to_string(nuevoID_empleado) + "' , '" + nuevaFechaContratacion + "' , '" + nuevaContrasena + "' , '" + nuevoPrimerNombre + "' , '" + nuevoSegundoNombre + "' , '" + nuevosNombresAdicionales + "' , '" + nuevoPrimerApellido + "' , '" + nuevoSegundoApellido + "' , '" + nuevosApellidosAdicionales + "' , '" + nuevoCorreo + "' , '" + nuevoNumeroCui + "'  , '" + nuevoDepartamentoNac + "' , '" + nuevoMunicipioNac + "' , '" + std::to_string(nuevoTelefono) + "' , '" + nuevaDireccion + "' , '" + nuevaFechaNac + "' , '" + std::to_string(ID_tipo_genero) + "' , '" + std::to_string(ID_tipo_departamento) + "' , '" + std::to_string(ID_tipo_puesto) + "' , '" + std::to_string(ID_tipo_rol) + "')";
        if (conexion->ejecutarInsert(consulta)) {
            std::cout << "\n\t\033[1;3;38;5;122m" << "Empleado insertado correctamente!" << std::endl;
            _getch();
        }
        else {
            std::cout << "\n\t\033[1;3;95m" << "Error al insertar el empleado" << "\033[0m" << std::endl;
            _getch();
            return false;
        }
    }
    else {
        std::cout << "\n\t\033[1;3;95m" << "Operacion cancelada" << "\033[0m" << std::endl;
        _getch();
    }
}

// Metodo para dar de baja a un empleado
// Retorna:
// - Verdadero si se dio de baja al empleado con exito, falso si se cancelo la operacion o ocurrio un error
bool Administrador::darDeBajaEmpleado() {
    int ID_empleado = Utilidades::validarIdOchoDigitos("Ingrese el ID del empleado a dar de baja");

    // Obtener y mostrar los datos del empleado por su ID
    Administrador admin(conexion);
    bool mostrarEmpleado = admin.obtenerDatosEmpPorId(ID_empleado);

    // Si no se encontraron coincidencias, no continuamos con el flujo
    if (!mostrarEmpleado) {
        return false;
    }

    // Confirmar eliminacion
    char respuesta = Utilidades::confirmarEjecutarQuery("Ingrese 'S' para confirmar dar de baja o 'N' para cancelar");
    Utilidades::imprimirLinea();
    if (respuesta == 'S') {
        // Realizar la eliminacion
        std::string consultaUpdate = "UPDATE empleado SET estado = 0 "
            "WHERE ID_empleado = " + std::to_string(ID_empleado);
        if (conexion->ejecutarUpdate(consultaUpdate)) {
            std::cout << "\n\t\033[1;3;38;5;122m" << "Empleado dado de baja correctamente!" << std::endl;
            _getch();
            return true;
        }
        else {
            std::cout << "\n\t\033[1;3;95m" << "Error al dar de baja el empleado" << "\033[0m" << std::endl;
            _getch();
            return false;
        }
    }
    else {
        std::cout << "\n\t\033[1;3;95m" << "Operacion cancelada" << "\033[0m" << std::endl;
        _getch();
        return false;
    }
}


bool Administrador::actualizarDatosEmpleado() {

    int ID_empleado = Utilidades::validarIdOchoDigitos("Ingrese el ID del empleado a actualizar");
    Administrador admin(conexion);
    bool mostrarEmpleado = admin.obtenerDatosEmpPorId(ID_empleado);

    // Si no se encontraron coincidencias, no continuamos con el flujo
    if (!mostrarEmpleado) {
        return false;
    }
    char respuesta = Utilidades::confirmarEjecutarQuery("Ingrese 'S' para confirmar que es el usuario o 'N' para cancelar");

    if (respuesta == 'S') {
        Menu::menuOpcionUpdate();
        int opcion = Utilidades::validarOpcionIngresada();  
        switch (opcion) {


        case 1: 
        {
            std::string contrasena1;
            std::string contrasena2;

            Utilidades::limpiarPantalla();
            Utilidades::imprimirTitulo(" - - - A C T U A L I Z A R - C O N T R A S E N A - - - ");

            std::string contrasena = Utilidades::obtenerContrasenaValidada(contrasena1, contrasena2);

            std::string consultaUpdate = "UPDATE empleado SET "
                "contrasena = '" + contrasena + "' "
                "WHERE ID_empleado = " + std::to_string(ID_empleado);

            char respuesta = Utilidades::confirmarEjecutarQuery("Ingrese 'S' para confirmar que es el usuario o 'N' para cancelar");
            if (respuesta == 'S') {
                if (conexion->ejecutarUpdate(consultaUpdate)) {
                    std::cout << "\n\t\033[1;3;38;5;122m" << "Contrasena actualizada correctamente!" << std::endl;
                    return true;
                }
                else {
                    std::cout << "\n\t\033[1;3;95m" << "Error al actualizar la contrasena del empleado" << "\033[0m" << std::endl;
                    _getch();
                    return false;
                }
            }
            else {
                std::cout << "\n\t\033[1;3;95m" << "Operacion cancelada" << "\033[0m" << std::endl;
                _getch();
                return false;
            }
            
        }
              break;

        case 2: //nombres
        {
            Utilidades::limpiarPantalla();
            Utilidades::imprimirTitulo(" - - - A C T U A L I Z A R  - N O M B R E S - - - ");
            std::cout << "\n\t\033[1;4;3;96m" << "Si no desea actualizar un campo copielo igual al que se muestra arriba" << "\033[0m" << std::endl;
            Utilidades::imprimirLinea();
            admin.obtenerDatosEmpPorId(ID_empleado);
            std::string nuevoPrimerNombre = Utilidades::validarString("Ingresa el primer Nombre:");
            std::string nuevoSegundoNombre = Utilidades::validarString("Ingresa el segundo Nombre:");
            std::string nuevosNombresAdicionales = Utilidades::validarOtroNombreApellido("Ingrese los nombres extra:");

            std::string consultaUpdate = "UPDATE empleado SET "
                "primerNombre = '" + nuevoPrimerNombre + "', "
                "segundoNombre = '" + nuevoSegundoNombre + "', "
                "nombresAdicionales = '" + nuevosNombresAdicionales + "' "
                "WHERE ID_empleado = " + std::to_string(ID_empleado);

            char respuesta = Utilidades::confirmarEjecutarQuery("Ingrese 'S' para confirmar la actualizacion o 'N' para cancelar");
            if (respuesta == 'S') {
                if (conexion->ejecutarUpdate(consultaUpdate)) {
                    std::cout << "\n\t\033[1;3;38;5;122m" << "Nombres actualizados correctamente!" << std::endl;
                    return true;
                }
                else {
                    std::cout << "\n\t\033[1;3;95m" << "Error al actualizar los nombres del empleado" << "\033[0m" << std::endl;
                    return false;
                }
            }
            else {
                std::cout << "\n\t\033[1;3;95m" << "Operacion cancelada" << "\033[0m" << std::endl;
                _getch();
                return false;
            }
        }
        break;
        case 3:
        {
            Utilidades::limpiarPantalla();
            Utilidades::imprimirTitulo(" - - - A C T U A L I Z A R - A P E L L I D O S - - - ");
            std::cout << "\n\t\033[1;4;3;96m" << "Si no desea actualizar un campo copielo igual al que se muestra arriba" << "\033[0m" << std::endl;
            Utilidades::imprimirLinea();
            admin.obtenerDatosEmpPorId(ID_empleado);
            std::string nuevoPrimerApellido = Utilidades::validarString("Ingresa el primer Apellido:");
            std::string nuevoSegundoApellido = Utilidades::validarString("Ingresa el segundo Apellido:");
            std::string nuevosApellidosAdicionales = Utilidades::validarOtroNombreApellido("Ingrese los apellidos extra:");

            std::string consultaUpdate = "UPDATE empleado SET "
                "primerApellido = '" + nuevoPrimerApellido + "', "
                "segundoApellido = '" + nuevoSegundoApellido + "', "
                "apellidosAdicionales = '" + nuevosApellidosAdicionales + "' "
                "WHERE ID_empleado = " + std::to_string(ID_empleado);
            char respuesta = Utilidades::confirmarEjecutarQuery("Ingrese 'S' para confirmar la actualizacion o 'N' para cancelar");
            if (respuesta == 'S') {
                if (conexion->ejecutarUpdate(consultaUpdate)) {
                    std::cout << "\n\t\033[1;3;38;5;122m" << "Apellidos actualizados correctamente!" << std::endl;
                    return true;
                }
                else {
                    std::cout << "\n\t\033[1;3;95m" << "Error al actualizar los apellidos del empleado" << "\033[0m" << std::endl;
                    return false;
                }
            }
            else {
                std::cout << "\n\t\033[1;3;95m" << "Operacion cancelada" << "\033[0m" << std::endl;
                _getch();
                return false;
            }
        }
        break;
        case 4:
        {
            Utilidades::limpiarPantalla();
            Utilidades::imprimirTitulo(" - - - A C T U A L I Z A R  - T E L E F O N O - - - ");
            int nuevoTelefono = Utilidades::validarNumeroTelefono();

            std::string consultaUpdate = "UPDATE empleado SET "
                "telefono = '" + std::to_string(nuevoTelefono) + "' "
                "WHERE ID_empleado = " + std::to_string(ID_empleado);
            char respuesta = Utilidades::confirmarEjecutarQuery("Ingrese 'S' para confirmar la actualizacion o 'N' para cancelar");
            if (respuesta == 'S') {
                if (conexion->ejecutarUpdate(consultaUpdate)) {
                    std::cout << "\n\t\033[1;3;38;5;122m" << "Numero telefonico actualizado correctamente!" << std::endl;
                    return true;
                }
                else {
                    std::cout << "\n\t\033[1;3;95m" << "Error al actualizar el numero telefonico del empleado" << "\033[0m" << std::endl;
                    return false;
                }
            }
            else {
                std::cout << "\n\t\033[1;3;95m" << "Operacion cancelada" << "\033[0m" << std::endl;
                _getch();
                return false;
            }
        }
        break;
        case 5:
        {
            Utilidades::limpiarPantalla();
            Utilidades::imprimirTitulo(" - - - A C T U A L I Z A R  - D I R E C C I O N - - - ");

            std::string nuevaDireccion = Utilidades::validarDireccion("Ingresa la nueva direccion");

            std::string consultaUpdate = "UPDATE empleado SET "
                "direccion = '" + nuevaDireccion + "' "
                "WHERE ID_empleado = " + std::to_string(ID_empleado);

            char respuesta = Utilidades::confirmarEjecutarQuery("Ingrese 'S' para confirmar la actualizacion o 'N' para cancelar");
            if (respuesta == 'S') {
                if (conexion->ejecutarUpdate(consultaUpdate)) {
                    std::cout << "\n\t\033[1;3;38;5;122m" << "La direccion del usuario se ha actualizado correctamente!" << std::endl;
                    return true;
                }
                else {
                    std::cout << "\n\t\033[1;3;95m" << "Error al actualizar la direccion del usuario" << "\033[0m" << std::endl;
                    return false;
                }
            }
            else {
                std::cout << "\n\t\033[1;3;95m" << "Operacion cancelada" << "\033[0m" << std::endl;
                _getch();
                return false;
            }
        }
        break;
        case 6:
        {
            Utilidades::limpiarPantalla();
            Utilidades::imprimirTitulo(" - - - C A M B I A R - D E P A R T A M E N T O - - - ");
            std::cout << "\n\t\033[1;4;3;96m" << "Departamentos disponibles:" << "\033[0m" << std::endl << std::endl;
            std::string consultaSelect = "Select * from departamento";
            Administrador departamento(conexion);
            bool mostrarDepartamentos = departamento.obtenerIdDisponibles(consultaSelect);
            int ID_tipo_departamento = Utilidades::validarIdTipoIngresado("Ingresa el numero de departamento a asignar");

            Utilidades::imprimirLinea();

            std::string consultaUpdate = "UPDATE empleado SET "
                "ID_tipo_departamento = '" + std::to_string(ID_tipo_departamento) + "' "
                "WHERE ID_empleado = " + std::to_string(ID_empleado);

            char respuesta = Utilidades::confirmarEjecutarQuery("Ingrese 'S' para confirmar la actualizacion o 'N' para cancelar");
            if (respuesta == 'S') {
                if (conexion->ejecutarUpdate(consultaUpdate)) {
                    std::cout << "\n\t\033[1;3;38;5;122m" << "El departamento del usuario se ha actualizado correctamente!" << std::endl;
                    return true;
                }
                else {
                    std::cout << "\n\t\033[1;3;95m" << "Error al actualizar el departamento del usuario" << "\033[0m" << std::endl;
                    return false;
                }
            }
            else {
                std::cout << "\n\t\033[1;3;95m" << "Operacion cancelada" << "\033[0m" << std::endl;
                _getch();
                return false;
            }
        }
        break;
        case 7:
        {
            Utilidades::limpiarPantalla();
            Utilidades::imprimirTitulo(" - - - C A M B I A R - P U E S T O - - - ");
            std::cout << "\n\t\033[1;4;3;96m" << "Puestos disponibles:" << "\033[0m" << std::endl << std::endl;
            Administrador puesto(conexion);
            std::string consultaSelect = "Select * from tipo_puesto";
            bool mostrarPuestos = puesto.obtenerIdDisponibles(consultaSelect);
            int ID_tipo_puesto = Utilidades::validarIdTipoIngresado("Ingresa el numero de puesto a asignar");

            Utilidades::imprimirLinea();

            std::string consultaUpdate = "UPDATE empleado SET "
                "ID_tipo_puesto = '" + std::to_string(ID_tipo_puesto) + "' "
                "WHERE ID_empleado = " + std::to_string(ID_empleado);

            char respuesta = Utilidades::confirmarEjecutarQuery("Ingrese 'S' para confirmar la actualizacion o 'N' para cancelar");
            if (respuesta == 'S') {
                if (conexion->ejecutarUpdate(consultaUpdate)) {
                    std::cout << "\n\t\033[1;3;38;5;122m" << "El puesto del usuario se ha actualizado correctamente!" << std::endl;
                    return true;
                }
                else {
                    std::cout << "\n\t\033[1;3;95m" << "Error al actualizar el puesto del usuario" << "\033[0m" << std::endl;
                    return false;
                }
            }
            else {
                std::cout << "\n\t\033[1;3;95m" << "Operacion cancelada" << "\033[0m" << std::endl;
                _getch();
                return false;
            }
        }
        break;
        case 8:
        {
            Utilidades::limpiarPantalla();
            Utilidades::imprimirTitulo(" - - - A C T U A L I Z A R  - R O L - - - ");
            std::cout << "\n\t\033[1;4;3;96m" << "Roles disponibles:" << "\033[0m" << std::endl << std::endl;
            std::string consultaSelect = "Select * from tipo_rol";
            Administrador rol(conexion);
            bool mostrarRoles = rol.obtenerIdDisponibles(consultaSelect);   // Llama al metodo para obtener y mostrar los roles
            int ID_tipo_rol = Utilidades::validarIdTipoIngresado("Ingresa el numero de rol a asignar");

            Utilidades::imprimirLinea();

            std::string consultaUpdate = "UPDATE empleado SET "
                "ID_tipo_rol = '" + std::to_string(ID_tipo_rol) + "' "
                "WHERE ID_empleado = " + std::to_string(ID_empleado);

            char respuesta = Utilidades::confirmarEjecutarQuery("Ingrese 'S' para confirmar la actualizacion o 'N' para cancelar");
            if (respuesta == 'S') {
                if (conexion->ejecutarUpdate(consultaUpdate)) {
                    std::cout << "\n\t\033[1;3;38;5;122m" << "El rol del usuario se ha actualizado correctamente!" << std::endl;
                    return true;
                }
                else {
                    std::cout << "\n\t\033[1;3;95m" << "Error al rol el puesto del usuario" << "\033[0m" << std::endl;
                    return false;
                }
            }
            else {
                std::cout << "\n\t\033[1;3;95m" << "Operacion cancelada" << "\033[0m" << std::endl;
                _getch();
                return false;
            }
        }
        break;
        default:
            std::cout << "\n\t\033[1;3;95m" << "Opcion no valida" << "\033[0m" << std::endl;
            return false;
        }
    }
    else {
        std::cout << "\n\t\033[1;3;95m" << "Operacion cancelada" << "\033[0m" << std::endl;
        return false;
    }
}
// Metodo para consultar empleados
// Retorna:
// - Verdadero si se consultaron los empleados con exito, falso en caso contrario
bool Administrador::consultarEmpleados() {
    std::cout << "\n\t\033[3;95m" << "1." << "\033[97m" << " Todos los empleados" << "\033[0m";
    std::cout << "\n\t\033[3;95m" << "2." << "\033[97m" << " Empleado especifico" << "\033[0m";
    int opcion = Utilidades::validarOpcionIngresada();
    Utilidades::imprimirLinea();

    switch (opcion)
    {
    case 1: // Consultar todos los empleados
    {
        Administrador admin(conexion);
        bool mostrarEmpleados = admin.obtenerTodosLosEmpleados();
        return mostrarEmpleados;
    }
    break;
    case 2: // Buscar empleado especifico
    {
        std::cout << "\n\t\033[3;95m" << "1." << "\033[97m" << " Buscar por ID" << "\033[0m";
        std::cout << "\n\t\033[3;95m" << "2." << "\033[97m" << " Buscar por primer nombre" << "\033[0m";
        int opcion = Utilidades::validarOpcionIngresada();
        Utilidades::imprimirLinea();
        if (opcion == 1) {
            int ID_empleado = Utilidades::validarIdOchoDigitos("Ingrese el ID del empleado que busca");
            Administrador admin(conexion);
            bool mostrarEmpleado = admin.obtenerDatosEmpPorId(ID_empleado);
            return mostrarEmpleado;
        }
        else if (opcion == 2) {
            std::string primerNombre = Utilidades::validarString("Ingresa el primer nombre del empleado:");
            Administrador admin(conexion);
            bool mostrarEmpleado = admin.obtenerDatosEmpPorNombre(primerNombre);
            return mostrarEmpleado;
        }
        else {
            std::cout << "\n\t\033[1;3;95m" << "Error al consultar el empleado" << "\033[0m" << std::endl;
            return false;
        }
    }
    break;
    std::cout << "\n\t\033[1;3;95m" << "Opcion no valida, intente de nuevo" << "\033[0m" << std::endl;
    default:
        break;
    }
    return opcion;
}



bool Administrador::crearNominaDetalle(int ID_nomina) {

    std::string consultaSelect =
        "SELECT emp.ID_empleado, emp.primerNombre, emp.segundoNombre, emp.nombresAdicionales, emp.primerApellido, emp.segundoApellido, emp.apellidosAdicionales, emp.ID_tipo_departamento, emp.ID_tipo_puesto, emp.estado, "
        "puesto.nombrePuesto, dep.nombreDepartamento, puesto.salarioBase "
        "FROM empleado emp "
        "JOIN departamento dep ON emp.ID_tipo_departamento = dep.ID_tipo_departamento "
        "JOIN tipo_puesto puesto ON emp.ID_tipo_puesto = puesto.ID_tipo_puesto";

    // Obtener el resultado de la consulta
    MYSQL_RES* resultado = conexion->obtenerResultadoConsulta(consultaSelect);

    // Verificar si se obtuvo un resultado valido
    if (!resultado) {
        std::cout << "\n\t\033[1;3;95m" << "Error: No se pudieron obtener resultados" << "\033[0m" << std::endl;
        return false;
    }

    // Verificar si no hay filas en el resultado
    if (mysql_num_rows(resultado) == 0) {
        std::cout << "\n\t\033[1;3;95m" << "No se encontraron coincidencias" << "\033[0m" << std::endl;
        mysql_free_result(resultado);
        return false;
    }
    
    int IdNomina = ID_nomina;
    int ID_empleado = 0;
    std::string nombreCompleto = " ";
    std::string nombrePuesto = " ";
    std::string nombreDepartamento = " ";
    int ID_tipo_puesto = 0;
    int ID_tipo_departamento = 0;
    double salarioBase = 0.0;
    int estado_empleado = 0;

    Nomina nomina(conexion);
    MYSQL_ROW fila;
    while ((fila = mysql_fetch_row(resultado))) {
     
        ID_empleado = std::stoi(fila[0] ? fila[0] : "N/A");

        nombreCompleto =
            std::string(fila[1] ? fila[1] : "N/A") + " " +
            std::string(fila[2] ? fila[2] : "N/A") + " " +
            std::string(fila[3] ? fila[3] : "N/A") + " " +
            std::string(fila[4] ? fila[4] : "N/A") + " " +
            std::string(fila[5] ? fila[5] : "N/A") + " " +
            std::string(fila[6] ? fila[6] : "N/A");

        ID_tipo_departamento = fila[7] ? std::stoi(fila[7]) : 0;
        ID_tipo_puesto = fila[8] ? std::stoi(fila[8]) : 0;
        estado_empleado = fila[9] ? std::stoi(fila[9]) : 0;
        nombrePuesto = fila[10] ? fila[10] : "N/A";
        nombreDepartamento = fila[11] ? fila[11] : "N/A";

        salarioBase = fila[12] ? std::stod(fila[12]) : 0.0;
        std::cout << "\n\t\033[1;4;3;96m" << "La siguente nomina pertenece a:" << "\033[0m" << std::endl;

        std::cout << std::endl;
        std::cout << "\t\033[3;93m" << "Nombre:" << "\t\033[91m" << nombreCompleto << std::endl;
        std::cout << "\t\033[3;93m" << "Nombre:" << "\t\033[91m" << nombreDepartamento << std::endl;
        std::cout << "\t\033[3;93m" << "Nombre:" << "\t\033[91m" << nombrePuesto << std::endl;

        if (estado_empleado == 1) {
            nomina.calcularGuardarNominaDetalle(salarioBase, ID_empleado, ID_tipo_puesto, ID_tipo_departamento, IdNomina);
        }
    }


    // Liberar el resultado de la consulta
    mysql_free_result(resultado);
    return true;
}



bool Administrador::crearNomina(const std::string& fechaCreacion, const std::string& fechaInicio, const std::string& fechaCierre) {

    double totalBonificaciones = 0.0;
    double totalDeducciones = 0.0;
    double totalIGSS = 0.0;
    double totalISR = 0.0;
    double totalIntecap = 0.0;
    double totalIrtra = 0.0;
    double totalIncentivos = 0.0;
    double totalNeto = 0.0;
    double totalLiquidoEmpleados = 0.0;

    std::string consultaInsert = "INSERT INTO nomina (fechaCreacion, fechaInicio, fechaCierre, totalBonificaciones, totalDeducciones, totalIGSS, totalISR, totalIntecap, totalIrtra, totalIncentivos, totalLiquidoEmpleados, totalNeto) "
        "VALUES ('" + fechaCreacion + "','" + fechaInicio + "', '" + fechaCierre + "' , " + std::to_string(totalBonificaciones) + ", " + std::to_string(totalDeducciones) + ", " + std::to_string(totalIGSS) + ", " + std::to_string(totalISR) + ", " + std::to_string(totalIntecap) + ", " + std::to_string(totalIrtra) + ", " + std::to_string(totalIncentivos) + ", " + std::to_string(totalLiquidoEmpleados) + ", " + std::to_string(totalNeto) + ")";

   
    if (conexion->ejecutarInsert(consultaInsert)) {
        std::cout << "\n\t\033[1;3;38;5;122m" << "Nomina creada correctamente!" << std::endl;
        _getch();
    }
    else {
        std::cout << "\n\t\033[1;3;95m" << "Error al intentar crear la nomina" << "\033[0m" << std::endl;
        _getch();
        return false;
    }
}


int Administrador::consultarNomina(const std::string& fechaInicio) {
    std::string consultaSelect = "SELECT * FROM nomina WHERE fechaInicio = '" + fechaInicio + "'";

    MYSQL_RES* resultado = conexion->obtenerResultadoConsulta(consultaSelect);

    // Verificar si se obtuvo un resultado valido
    if (!resultado) {
        std::cout << "\n\t\033[1;3;95m" << "Error: No se pudieron obtener resultados" << "\033[0m" << std::endl;
        return -1;
    }

    // Verificar si no hay filas en el resultado
    if (mysql_num_rows(resultado) == 0) {
        std::cout << "\n\t\033[1;3;95m" << "No se encontraron coincidencias" << "\033[0m" << std::endl;
        Utilidades::imprimirLinea();
        mysql_free_result(resultado);
        return -1;
    }
    int ID_nomina = 0;

    Nomina nomina(conexion);
    MYSQL_ROW fila;
    while ((fila = mysql_fetch_row(resultado))) {

        ID_nomina = fila[0] ? std::stoi(fila[0]) : 0;

        std::cout << "\n\t\033[1;3;95m" << "El ID de la nomina es:" << "\t\t\033[3;97m"
            << (fila[0] ? std::stoi(fila[0]) : 0) << "\033[0m" << std::endl;

        std::cout << "\n\t\033[1;3;95m" << "fecha Creacion:" << "\t\t\033[3;97m"
            << (fila[1] ? fila[1] : "N / A") << "\033[0m" << std::endl;

        std::cout << "\n\t\033[1;3;95m" << "fecha Inicio:" << "\t\t\033[3;97m"
            << (fila[2] ? fila[2] : "N / A") << "\033[0m" << std::endl;

        std::cout << "\n\t\033[1;3;95m" << "fecha Cierre:" << "\t\t\033[3;97m"
            << (fila[3] ? fila[3] : "N / A") << "\033[0m" << std::endl;

        std::cout << "\n\t\033[1;3;95m" << "Total bonificaciones:" << "\t\033[3;97m"
            << "Q." << (fila[4] ? std::stod(fila[4]) : 0) << "\033[0m" << std::endl;

        std::cout << "\n\t\033[1;3;95m" << "Total Deducciones:" << "\t\033[3;97m"
            << "Q." << (fila[5] ? std::stod(fila[5]) : 0) << "\033[0m" << std::endl;

        std::cout << "\n\t\033[1;3;95m" << "Total IGGS:" << "\t\t\033[3;97m"
            << "Q." << (fila[6] ? std::stod(fila[6]) : 0) << "\033[0m" << std::endl;

        std::cout << "\n\t\033[1;3;95m" << "Total ISR:" << "\t\t\033[3;97m"
            << "Q." << (fila[7] ? std::stod(fila[7]) : 0) << "\033[0m" << std::endl;

        std::cout << "\n\t\033[1;3;95m" << "Total Intecap:" << "\t\t\033[3;97m"
            << "Q." << (fila[8] ? std::stod(fila[8]) : 0) << "\033[0m" << std::endl;

        std::cout << "\n\t\033[1;3;95m" << "Total Irtra:" << "\t\t\033[3;97m"
            << "Q." << (fila[9] ? std::stod(fila[9]) : 0) << "\033[0m" << std::endl;

        std::cout << "\n\t\033[1;3;95m" << "Total Incentivo:" << "\t\033[3;97m"
            << "Q." << (fila[10] ? std::stod(fila[10]) : 0) << "\033[0m" << std::endl;

        std::cout << "\n\t\033[1;3;95m" << "Total Liquido:" << "\t\t\033[3;97m"
            << "Q." << (fila[11] ? std::stod(fila[11]) : 0) << "\033[0m" << std::endl;

        std::cout << "\n\t\033[1;3;95m" << "Total Neto:" << "\t\t\033[3;97m"
            << "Q." << (fila[12] ? std::stod(fila[12]) : 0) << "\033[0m" << std::endl;

    }
    // Liberar el resultado de la consulta
    mysql_free_result(resultado);

    return ID_nomina;
}


bool Administrador::actualizarNomina(const int ID_nomina) {
    std::string consultaSelect = "SELECT ID_empleado, bonificaciones, deducciones, IGSS, ISR, Intecap, Irtra, incentivo, liquido_recibir FROM nomina_detalle WHERE ID_nomina = " + std::to_string(ID_nomina);

    // Obtener el resultado de la consulta
    MYSQL_RES* resultado = conexion->obtenerResultadoConsulta(consultaSelect);

    // Verificar si se obtuvo un resultado valido
    if (!resultado) {
        std::cout << "\n\t\033[1;3;95m" << "Error: No se pudieron obtener resultados" << "\033[0m" << std::endl;
        return false;
    }

    // Verificar si no hay filas en el resultado
    if (mysql_num_rows(resultado) == 0) {
        std::cout << "\n\t\033[1;3;95m" << "No se encontraron coincidencias" << "\033[0m" << std::endl;
        Utilidades::imprimirLinea();
        mysql_free_result(resultado);
        return false;
    }

    double totalBonificaciones = 0.0;
    double totalDeducciones = 0.0;
    double totalIGSS = 0.0;
    double totalISR = 0.0;
    double totalIntecap = 0.0;
    double totalIrtra = 0.0;
    double totalIncentivo = 0.0;
    double totalLiquidoEmpleado = 0.0;
    double totalNeto = 0.0;

    MYSQL_ROW fila;
    while ((fila = mysql_fetch_row(resultado))) {
        double bonificacionActual = fila[1] ? std::stod(fila[1]) : 0.0;
        double deduccionActual = fila[2] ? std::stod(fila[2]) : 0.0;
        double IGSSActual = fila[3] ? std::stod(fila[3]) : 0.0;
        double ISRActual = fila[4] ? std::stod(fila[4]) : 0.0;
        double IntecapActual = fila[5] ? std::stod(fila[5]) : 0.0;
        double IrtraActual = fila[6] ? std::stod(fila[6]) : 0.0;
        double incentivoActual = fila[7] ? std::stod(fila[7]) : 0.0;
        double liquidoEmpleadoActual = fila[8] ? std::stod(fila[8]) : 0.0;

        totalBonificaciones += bonificacionActual;
        totalDeducciones += deduccionActual;
        totalIGSS += IGSSActual;
        totalISR += ISRActual;
        totalIntecap += IntecapActual;
        totalIrtra += IrtraActual;
        totalIncentivo += incentivoActual;
        totalLiquidoEmpleado += liquidoEmpleadoActual;
    }

    totalNeto = totalBonificaciones + totalDeducciones + totalIGSS + totalISR + totalIntecap + totalIrtra + totalIncentivo + totalLiquidoEmpleado;

    std::cout << "\n\t\033[1;3;95m" << "Total Bonificaciones:" << "\t\t\033[3;97m" << "Q." << totalBonificaciones << "\033[0m" << std::endl;
    std::cout << "\n\t\033[1;3;95m" << "Total Deducciones:" << "\t\t\033[3;97m" << "Q." << totalDeducciones << "\033[0m" << std::endl;
    std::cout << "\n\t\033[1;3;95m" << "Total IGSS:" << "\t\t\t\033[3;97m" << "Q." << totalIGSS << "\033[0m" << std::endl;
    std::cout << "\n\t\033[1;3;95m" << "Total ISR:" << "\t\t\t\033[3;97m" << "Q." << totalISR << "\033[0m" << std::endl;
    std::cout << "\n\t\033[1;3;95m" << "Total Intecap:" << "\t\t\t\033[3;97m" << "Q." << totalIntecap << "\033[0m" << std::endl;
    std::cout << "\n\t\033[1;3;95m" << "Total Irtra:" << "\t\t\t\033[3;97m" << "Q." << totalIrtra << "\033[0m" << std::endl;
    std::cout << "\n\t\033[1;3;95m" << "Total Incentivo:" << "\t\t\033[3;97m" << "Q." << totalIncentivo << "\033[0m" << std::endl;
    std::cout << "\n\t\033[1;3;95m" << "Total Liquido Empleado:" << "\t\t\033[3;97m" << "Q." << totalLiquidoEmpleado << "\033[0m" << std::endl;
    std::cout << "\n\t\033[1;3;95m" << "Total Neto:" << "\t\t\t\033[3;97m" << "Q." << totalNeto << "\033[0m" << std::endl;

    std::string consultaUpdate = "UPDATE nomina "
        "SET totalBonificaciones = " + std::to_string(totalBonificaciones) +
        ", totalDeducciones = " + std::to_string(totalDeducciones) +
        ", totalIGSS = " + std::to_string(totalIGSS) +
        ", totalISR = " + std::to_string(totalISR) +
        ", totalIntecap = " + std::to_string(totalIntecap) +
        ", totalIrtra = " + std::to_string(totalIrtra) +
        ", totalIncentivos = " + std::to_string(totalIncentivo) +
        ", totalLiquidoEmpleados = " + std::to_string(totalLiquidoEmpleado) +
        ", totalNeto = " + std::to_string(totalNeto) +
        " WHERE ID_nomina = " + std::to_string(ID_nomina);

    if (conexion->ejecutarUpdate(consultaUpdate)) {
        std::cout << "\n\t\033[1;3;38;5;122m" << "Nomina " << ID_nomina << " actualizada correctamente!" << "\033[0m" << std::endl;

        // Confirmar la transacción si no está en modo autocommit
        if (!conexion->getAutocommit()) {
            conexion->commit();
        }

        mysql_free_result(resultado);
        return true;
    }
    else {
        std::cout << "\n\t\033[1;3;95m" << "Error al actualizar la nomina " << ID_nomina << "\033[0m" << std::endl;
        mysql_free_result(resultado);
        return false;
    }
}


// Metodo para añadir un nuevo departamento
// Parametros:
// - nombreNuevoDepto: El nombre del nuevo departamento a añadir
// Retorna:
// - Verdadero si se añadio el departamento correctamente, falso en caso contrario
bool Administrador::anadirNuevoDepartamento(const std::string nombreNuevoDepto) {

    std::string consultaInsert = "INSERT INTO departamento (NombreDepartamento) VALUES ('" + nombreNuevoDepto + "')";

    if (conexion->ejecutarInsert(consultaInsert)) {
        std::cout << "\n\t\033[1;3;38;5;122m" << "Departamento añadido correctamente!" << std::endl;
        _getch();
        return true;
    }
    else {
        std::cout << "\n\t\033[1;3;95m" << "Error al intentar añadir un nuevo departamento" << "\033[0m" << std::endl;
        _getch();
        return false;
    }
}

// Metodo para añadir un nuevo puesto
// Parametros:
// - nombreNuevoPuesto: El nombre del nuevo puesto a añadir
// - salarioBase: El salario base asociado al nuevo puesto
// Retorna:
// - Verdadero si se añadio el puesto correctamente, falso en caso contrario
bool Administrador::anadirNuevoPuesto(const std::string nombreNuevoPuesto, const double salarioBase) {
    // Consulta de insercion corregida
    std::string consultaInsert = "INSERT INTO tipo_puesto (nombrePuesto, salarioBase) VALUES ('" + nombreNuevoPuesto + "', " + std::to_string(salarioBase) + ")";

    if (conexion->ejecutarInsert(consultaInsert)) {
        std::cout << "\n\t\033[1;3;38;5;122m" << "Puesto añadido correctamente!" << std::endl;
        _getch();
        return true;  // No olvides retornar true en caso de exito
    }
    else {
        std::cout << "\n\t\033[1;3;95m" << "Error al intentar añadir un nuevo puesto" << "\033[0m" << std::endl;
        _getch();
        return false;
    }
}

// Metodo para cargar un nuevo anuncio
// Parametros:
// - ID_departamento: El ID del departamento al que se asociara el anuncio
// Retorna:
// - Verdadero si se cargo el anuncio correctamente, falso en caso contrario
bool Administrador::cargarUnAnuncio(const int ID_departamento) {

    std::string tituloAnuncio = Utilidades::validarStringConEspacios("Por favor ingresa el titulo del anuncio");
    std::string fechaDePublicacion = Utilidades::obtenerFechaActual();
    std::cout << "\n\t\033[1;3;38;5;122m" << "La fecha del anuncio es:" << "\t\t\t\t\t\033[1;3;95m"<<fechaDePublicacion << std::endl;
    std::string cuerpoAnuncio = Utilidades::validarCuerpoDelAnuncio();
    std::string consultaInsert = "INSERT INTO anuncio (Titulo, Contenido, fecha_publicacion, ID_departamento) VALUES ('" + tituloAnuncio + "', '" + cuerpoAnuncio + "','" + fechaDePublicacion + "', '" + std::to_string(ID_departamento) + "')";


    if (conexion->ejecutarInsert(consultaInsert)) {
        std::cout << "\n\t\033[1;3;38;5;122m" << "Anuncio cargado correctamente!" << std::endl;
        _getch();
        return true;
    }
    else {
        std::cout << "\n\t\033[1;3;95m" << "Error al intentar cargar el anuncio" << "\033[0m" << std::endl;
        _getch();
        return false;
    }
}


// Metodo para obtener la lista de departamentos
// Retorna:
// - Verdadero si se obtuvo la lista de departamentos correctamente, falso en caso contrario
bool Administrador::obtenerDepartamentos() {

    std::string consultaSelect = "SELECT * FROM departamento";
    // Obtener el resultado de la consulta
    MYSQL_RES* resultado = conexion->obtenerResultadoConsulta(consultaSelect);

    if (!resultado) {
        std::cout << "\n\t\033[1;3;95m" << "No se pudieron obtener resultados" << "\033[0m" << std::endl;
        return false;
    }

    std::cout << std::endl;
    // Procesar y mostrar los resultados
    MYSQL_ROW fila;
    while ((fila = mysql_fetch_row(resultado))) {
        // Recorrer cada fila y mostrar los datos

        std::cout << "\t\033[1;3;95m" << fila[0] << "\033[3;97m " << fila[1] << std::endl;
    }

    // Liberar el resultado de la consulta
    mysql_free_result(resultado);
    return true;
}





