#include "Nomina.h"

// Constructor de la clase Nomina que recibe un puntero a una instancia de ConexionMySQL
Nomina::Nomina(ConexionMySQL* conexionBD) : conexion(conexionBD) {}

// Método para calcular y guardar los detalles de la nómina en la base de datos
bool Nomina::calcularGuardarNominaDetalle(double salarioBase, int ID_empleado, int ID_tipo_puesto, int ID_tipo_departamento, int ID_nomina) {

    // Realizar cálculos relacionados con la nómina
    double bonificaciones = calcularBonificaciones(salarioBase);
    double deducciones = calcularDeducciones(salarioBase);
    double IGSS = calcularIGSS(salarioBase);
    double ISR = calcularISR(salarioBase);
    double Intecap = calcularIntecap(salarioBase);
    double Irtra = calcularIrtra(salarioBase);
    double incentivo = calcularIncentivo();
    double totalEgresos = deducciones + IGSS + ISR + Intecap + Irtra;
    double liquidoARecibir = salarioBase + bonificaciones + incentivo - totalEgresos;

    // Imprimir resultados de los cálculos en la consola
    std::cout << "\n\t\033[1;4;3;96m" << "Resultados de los calculos:" << "\033[0m" << std::endl << std::endl;
    std::cout << "\t\033[1;3;95m" << "Salario Base:" << "\t\t\033[3;97m" << "Q." << salarioBase << "\033[0m" << std::endl;
    std::cout << "\t\033[1;3;95m" << "Bonificaciones:" << "\t\t\033[3;97m" << "Q." << bonificaciones << "\033[0m" << std::endl;
    std::cout << "\t\033[1;3;95m" << "Deducciones:" << "\t\t\033[3;97m" << "Q." << deducciones << "\033[0m" << std::endl;
    std::cout << "\t\033[1;3;95m" << "IGSS:" << "\t\t\t\033[3;97m" << "Q." << IGSS << "\033[0m" << std::endl;
    std::cout << "\t\033[1;3;95m" << "ISR:" << "\t\t\t\033[3;97m" << "Q." << ISR << "\033[0m" << std::endl;
    std::cout << "\t\033[1;3;95m" << "Intecap:" << "\t\t\033[3;97m" << "Q." << Intecap << "\033[0m" << std::endl;
    std::cout << "\t\033[1;3;95m" << "Irtra:" << "\t\t\t\033[3;97m" << "Q." << Irtra << "\033[0m" << std::endl;
    std::cout << "\t\033[1;3;95m" << "Incentivo:" << "\t\t\033[3;97m" << "Q." << incentivo << "\033[0m" << std::endl;
    std::cout << "\t\033[1;3;95m" << "Total Egresos:" << "\t\t\033[3;97m" << "Q." << totalEgresos << "\033[0m" << std::endl;
    std::cout << "\t\033[1;3;95m" << "Liquido recibir:" << "\t\033[3;97m" << "Q." << liquidoARecibir << "\033[0m" << std::endl;

    // Construir la consulta de inserción SQL para los detalles de la nómina
    std::string consultaInsert = "INSERT INTO nomina_detalle (ID_nomina, ID_empleado, salarioBase, bonificaciones, deducciones, IGSS, ISR, Intecap, Irtra, incentivo, total_egresos, liquido_recibir, ID_tipo_puesto, ID_tipo_departamento) VALUES (" + std::to_string(ID_nomina) + ", " + std::to_string(ID_empleado) + ", " + std::to_string(salarioBase) + ", " + std::to_string(bonificaciones) + ", " + std::to_string(deducciones) + ", " + std::to_string(IGSS) + ", " + std::to_string(ISR) + ", " + std::to_string(Intecap) + ", " + std::to_string(Irtra) + ", " + std::to_string(incentivo) + ", " + std::to_string(totalEgresos) + " , " + std::to_string(liquidoARecibir) + " , " + std::to_string(ID_tipo_puesto) + ", " + std::to_string(ID_tipo_departamento) + ")";

    // Ejecutar la consulta de inserción en la base de datos
    if (conexion->ejecutarInsert(consultaInsert)) {
        std::cout << "\n\t\033[1;3;38;5;122m" << "Detalle de la nómina creado exitosamente para el empleado con ID " << ID_empleado << std::endl;
        Utilidades::imprimirLinea();
        return true;

    }
    else {
        std::cout << "\n\t\033[1;3;95m" << "La entrada debe ser una cadena de texto de no mas de 11 caracteres alfabeticos y/o espacios" << "\033[0m" << std::endl;
        _getch();
        Utilidades::borrarLinea(3);
        return false;
    }
    return false;
}



double Nomina::calcularBonificaciones(double salarioBase) {
    // Lógica para calcular las bonificaciones del empleado
    double porcentajeBonificaciones = 0.10; // 10% del salario base como bonificación
    return salarioBase * porcentajeBonificaciones;
}
    
double Nomina::calcularDeducciones(double salarioBase) {
    // Lógica para calcular las deducciones del empleado
    // Por ejemplo, podríamos calcular el IGSS y el ISR
    double IGSS = calcularIGSS(salarioBase);
    double ISR = calcularISR(salarioBase);
    return IGSS + ISR;
}

double Nomina::calcularIGSS(double salarioBase) {
    // Lógica para calcular el IGSS basado en el salario base
    double porcentajeIGSS = 0.0483; // 4.83% del salario base
    return salarioBase * porcentajeIGSS;
}

double Nomina::calcularISR(double salarioBase) {
    double salarioAnual = salarioBase * 12;
    double isrAnual = 0.0;

    if (salarioAnual > 48000) {
        if (salarioAnual <= 300000) {
            isrAnual = (salarioAnual - 48000) * 0.05;
        }
        else {
            isrAnual = (300000 - 48000) * 0.05 + (salarioAnual - 300000) * 0.07;
        }
    }

    double isrMensual = isrAnual / 12;
    return isrMensual;
}

double Nomina::calcularIntecap(double salarioBase) {
    // Lógica para calcular el aporte al INTECAP basado en el salario base
    double porcentajeIntecap = 0.01; // 1% del salario base
    return salarioBase * porcentajeIntecap;
}

double Nomina::calcularIrtra(double salarioBase) {
    // Lógica para calcular el aporte al IRTRA basado en el salario base
    double porcentajeIrtra = 0.01; // 1% del salario base
    return salarioBase * porcentajeIrtra;
}

double Nomina::calcularIncentivo() {
    // Lógica para calcular el incentivo
    return 250.00; // Monto fijo de Q250.00
}
