#include "Utilidades.h"
#include "ConexionMySQL.h"
#include "Empleado.h"

class Nomina {
protected:
	ConexionMySQL* conexion;
public:
	Nomina(ConexionMySQL* conexionBD);
	bool calcularGuardarNominaDetalle(double salarioBase, int ID_empleado, int ID_tipo_puesto, int ID_tipo_departamento, int ID_nomina);
	double calcularBonificaciones(double salarioBase);
	double calcularDeducciones(double salarioBase);
	double calcularIGSS(double salarioBase);
	double calcularISR(double salarioBase);
	double calcularIntecap(double salarioBase);
	double calcularIrtra(double salarioBase);
	double calcularIncentivo();
};