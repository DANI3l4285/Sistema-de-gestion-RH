-- MySQL dump 10.13  Distrib 8.0.34, for Win64 (x86_64)
--
-- Host: localhost    Database: human_resource_management
-- ------------------------------------------------------
-- Server version	8.0.34

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `anuncio`
--

DROP TABLE IF EXISTS `anuncio`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `anuncio` (
  `ID_anuncio` int NOT NULL AUTO_INCREMENT,
  `Titulo` varchar(100) NOT NULL,
  `Contenido` text NOT NULL,
  `Fecha_publicacion` date NOT NULL,
  `ID_departamento` int NOT NULL,
  PRIMARY KEY (`ID_anuncio`),
  KEY `ID_departamento` (`ID_departamento`),
  CONSTRAINT `anuncio_ibfk_1` FOREIGN KEY (`ID_departamento`) REFERENCES `departamento` (`ID_tipo_departamento`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `anuncio`
--

LOCK TABLES `anuncio` WRITE;
/*!40000 ALTER TABLE `anuncio` DISABLE KEYS */;
/*!40000 ALTER TABLE `anuncio` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `departamento`
--

DROP TABLE IF EXISTS `departamento`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `departamento` (
  `ID_tipo_departamento` int NOT NULL AUTO_INCREMENT,
  `NombreDepartamento` varchar(50) NOT NULL,
  PRIMARY KEY (`ID_tipo_departamento`)
) ENGINE=InnoDB AUTO_INCREMENT=7 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `departamento`
--

LOCK TABLES `departamento` WRITE;
/*!40000 ALTER TABLE `departamento` DISABLE KEYS */;
INSERT INTO `departamento` VALUES (1,'Recursos Humanos'),(2,'Tecnologia '),(3,'Mantenimiento'),(4,'Contabilidad'),(5,'Produccion'),(6,'Marketing y publicidad');
/*!40000 ALTER TABLE `departamento` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `empleado`
--

DROP TABLE IF EXISTS `empleado`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `empleado` (
  `ID_empleado` int NOT NULL,
  `fechaContratacion` date NOT NULL,
  `contrasena` varchar(20) NOT NULL,
  `primerNombre` varchar(15) NOT NULL,
  `segundoNombre` varchar(15) NOT NULL,
  `nombresAdicionales` varchar(30) DEFAULT NULL,
  `primerApellido` varchar(50) NOT NULL,
  `segundoApellido` varchar(15) NOT NULL,
  `apellidosAdicionales` varchar(30) DEFAULT NULL,
  `correo` varchar(100) NOT NULL,
  `numeroCui` varchar(13) NOT NULL,
  `departamentoNac` varchar(15) NOT NULL,
  `municipioNac` varchar(20) NOT NULL,
  `telefono` varchar(15) NOT NULL,
  `direccion` varchar(55) NOT NULL,
  `fechaNacimiento` date NOT NULL,
  `ID_tipo_genero` int NOT NULL,
  `ID_tipo_departamento` int NOT NULL,
  `ID_tipo_puesto` int NOT NULL,
  `ID_tipo_rol` int NOT NULL,
  `estado` tinyint NOT NULL DEFAULT '1',
  PRIMARY KEY (`ID_empleado`),
  KEY `fk_genero` (`ID_tipo_genero`),
  KEY `empleado_ibfk_1` (`ID_tipo_rol`),
  KEY `fk_empleado_tipo_puesto` (`ID_tipo_puesto`),
  KEY `empleado_ibfk_2` (`ID_tipo_departamento`),
  CONSTRAINT `empleado_ibfk_1` FOREIGN KEY (`ID_tipo_rol`) REFERENCES `tipo_rol` (`ID_tipo_rol`),
  CONSTRAINT `empleado_ibfk_2` FOREIGN KEY (`ID_tipo_departamento`) REFERENCES `departamento` (`ID_tipo_departamento`),
  CONSTRAINT `fk_empleado_tipo_puesto` FOREIGN KEY (`ID_tipo_puesto`) REFERENCES `tipo_puesto` (`ID_tipo_puesto`),
  CONSTRAINT `fk_genero` FOREIGN KEY (`ID_tipo_genero`) REFERENCES `tipo_genero` (`ID_tipo_genero`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `empleado`
--

LOCK TABLES `empleado` WRITE;
/*!40000 ALTER TABLE `empleado` DISABLE KEYS */;
INSERT INTO `empleado` VALUES (30111524,'2024-01-02','Daniel123!','Jorge','David','','Culajay','Mendez','','jaguilar@gmail.com','3584070010101','Guatemala','Guatemala','45678912','La brigada z19 mixco','2001-01-01',2,3,1,1,1),(30225003,'2024-05-30','30225003','Juan','Julian',' ','Hernandez','Cabrera',' ','jmendez@gmail.com','3584070010101','Guatemala','Guatemala','15975387','Belen zona 7 mixco 3ra avenida','2004-01-01',2,3,6,2,1),(30225103,'2024-05-30','Jorge123!','Pedro','Kevin',' ','Lopez','Cabrera',' ','jlopez@gmail.com','3584070010101','Guatemala','Guatemala','45685219','San ignacio zona 7 demixco 3ra calle 13-27','2003-08-09',2,3,3,2,0),(31211622,'2024-05-31','31211622','Manuel','Esteban',' ','Aguilar','Garcia',' ','jaguilar@gmail.com','3584070010101','Guatemala','Guatemala','15934567','47 Calle C 87-7 Zona 19 la brigada','2001-01-01',2,2,1,2,1),(31222016,'2024-05-31','Daniel123!','Ernesto','Felix','Daniel','Diaz','Carias',' ','cdiaz@gmail.com','3584070010101','Guatemala','Guatemala','45685247','Zona 1 6ta Avenida ciudad de Guatemala','2004-01-01',2,5,6,2,1);
/*!40000 ALTER TABLE `empleado` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `nomina`
--

DROP TABLE IF EXISTS `nomina`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `nomina` (
  `ID_nomina` int NOT NULL AUTO_INCREMENT,
  `fechaCreacion` datetime NOT NULL,
  `fechaInicio` date NOT NULL,
  `fechaCierre` date NOT NULL,
  `totalBonificaciones` decimal(10,2) NOT NULL,
  `totalDeducciones` decimal(10,2) NOT NULL,
  `totalIGSS` decimal(10,2) NOT NULL,
  `totalISR` decimal(10,2) NOT NULL,
  `totalIntecap` decimal(10,2) NOT NULL,
  `totalIrtra` decimal(10,2) NOT NULL,
  `totalIncentivos` decimal(10,2) NOT NULL,
  `totalLiquidoEmpleados` decimal(10,2) NOT NULL,
  `totalNeto` decimal(10,2) NOT NULL,
  PRIMARY KEY (`ID_nomina`)
) ENGINE=InnoDB AUTO_INCREMENT=4080 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `nomina`
--

LOCK TABLES `nomina` WRITE;
/*!40000 ALTER TABLE `nomina` DISABLE KEYS */;
/*!40000 ALTER TABLE `nomina` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `nomina_detalle`
--

DROP TABLE IF EXISTS `nomina_detalle`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `nomina_detalle` (
  `ID_nomina_detalle` int NOT NULL AUTO_INCREMENT,
  `ID_nomina` int NOT NULL,
  `ID_empleado` int NOT NULL,
  `salarioBase` decimal(10,2) NOT NULL,
  `bonificaciones` decimal(10,2) NOT NULL,
  `deducciones` decimal(10,2) NOT NULL,
  `IGSS` decimal(10,2) NOT NULL,
  `ISR` decimal(10,2) NOT NULL,
  `Intecap` decimal(10,2) NOT NULL,
  `Irtra` decimal(10,2) NOT NULL,
  `incentivo` decimal(10,2) NOT NULL,
  `total_egresos` decimal(10,2) NOT NULL,
  `liquido_recibir` decimal(10,2) NOT NULL,
  `ID_tipo_puesto` int NOT NULL,
  `ID_tipo_departamento` int NOT NULL,
  PRIMARY KEY (`ID_nomina_detalle`),
  KEY `nomina_detalle_ibfk_1` (`ID_nomina`),
  KEY `nomina_detalle_ibfk_2` (`ID_empleado`),
  KEY `nomina_detalle_ibfk_3` (`ID_tipo_puesto`),
  KEY `nomina_detalle_ibfk_4` (`ID_tipo_departamento`),
  CONSTRAINT `nomina_detalle_ibfk_1` FOREIGN KEY (`ID_nomina`) REFERENCES `nomina` (`ID_nomina`),
  CONSTRAINT `nomina_detalle_ibfk_2` FOREIGN KEY (`ID_empleado`) REFERENCES `empleado` (`ID_empleado`),
  CONSTRAINT `nomina_detalle_ibfk_3` FOREIGN KEY (`ID_tipo_puesto`) REFERENCES `tipo_puesto` (`ID_tipo_puesto`),
  CONSTRAINT `nomina_detalle_ibfk_4` FOREIGN KEY (`ID_tipo_departamento`) REFERENCES `departamento` (`ID_tipo_departamento`)
) ENGINE=InnoDB AUTO_INCREMENT=69 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `nomina_detalle`
--

LOCK TABLES `nomina_detalle` WRITE;
/*!40000 ALTER TABLE `nomina_detalle` DISABLE KEYS */;
/*!40000 ALTER TABLE `nomina_detalle` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tipo_genero`
--

DROP TABLE IF EXISTS `tipo_genero`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `tipo_genero` (
  `ID_tipo_genero` int NOT NULL,
  `Tipo_genero` varchar(10) DEFAULT NULL,
  PRIMARY KEY (`ID_tipo_genero`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tipo_genero`
--

LOCK TABLES `tipo_genero` WRITE;
/*!40000 ALTER TABLE `tipo_genero` DISABLE KEYS */;
INSERT INTO `tipo_genero` VALUES (1,'Femenino'),(2,'Masculino');
/*!40000 ALTER TABLE `tipo_genero` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tipo_puesto`
--

DROP TABLE IF EXISTS `tipo_puesto`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `tipo_puesto` (
  `ID_tipo_puesto` int NOT NULL AUTO_INCREMENT,
  `nombrePuesto` varchar(255) NOT NULL,
  `salarioBase` double NOT NULL,
  PRIMARY KEY (`ID_tipo_puesto`)
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tipo_puesto`
--

LOCK TABLES `tipo_puesto` WRITE;
/*!40000 ALTER TABLE `tipo_puesto` DISABLE KEYS */;
INSERT INTO `tipo_puesto` VALUES (1,'Programador Junior',3500),(2,'Programador Senior',5000),(3,'Jefe inmediato',7000),(4,'Gerente general',1000),(5,'Limpieza',3200),(6,'Telecomunicaciones',5400),(7,'Ingeniero',12000);
/*!40000 ALTER TABLE `tipo_puesto` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tipo_rol`
--

DROP TABLE IF EXISTS `tipo_rol`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `tipo_rol` (
  `ID_tipo_rol` int NOT NULL,
  `Nombre_rol` varchar(50) NOT NULL,
  PRIMARY KEY (`ID_tipo_rol`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tipo_rol`
--

LOCK TABLES `tipo_rol` WRITE;
/*!40000 ALTER TABLE `tipo_rol` DISABLE KEYS */;
INSERT INTO `tipo_rol` VALUES (1,'Administrador'),(2,'Usuario');
/*!40000 ALTER TABLE `tipo_rol` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2024-06-01  1:29:09
