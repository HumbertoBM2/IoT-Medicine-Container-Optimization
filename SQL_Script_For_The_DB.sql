/* DB used to store the data gathered from monitoring the containers */
/* Crear base de datos */
create database Unidad_de_Monitoreo;

/* Use the DB*/
/* Usar base de datos */
use Unidad_de_Monitoreo;

/* Create the entities as tables */
/* Crear entidades como tablas */

/* This table stores everything related with the transport trucks */
create table camion (
	id_camion int primary key auto_increment,
	chofer varchar (30) not null, 
	matricula varchar (12) not null
);

/* This table stores erevything related with the sensors */
create table sensor(
	id_sensor int primary key auto_increment,
	tipo varchar(12),
	id_camion int not null,
	foreign key (`id_camion`) references `camion`(`id_camion`)
);

/* This table handles sensor readings */
create table lectura (
	id_lectura int primary key auto_increment,
	valor float not null,
	unidad varchar(5) not null,
	status varchar(20) not null,
	fecha timestamp not null,
	id_sensor int not null, 
	foreign key (`id_sensor`) references `sensor`(`id_sensor`)
);

/* This table is used to filter the readings by trip */
create table viaje(
	id_viaje int primary key auto_increment,
	id_camion int not null, 
	fecha_inicio timestamp not null, 
	fecha_final timestamp not null,
	foreign key (`id_camion`) references `camion`(`id_camion`)
);

/* Test INSERTS*/
/* Inserts de prueba */
insert into camion 
	(chofer, matricula)
	values ('Arturo Dix', '893-TVZ');


insert into camion 
	(chofer, matricula)
	values ('Erick', '888-YYZ');

select * from camion;


insert into sensor 
	(tipo, id_camion)
	values ('CO2', 1);


insert into sensor 
	(tipo, id_camion)
	values ('Temperatura', 1);

insert into sensor 
	(tipo, id_camion)
	values ('Humedad', 1);

insert into sensor 
	(tipo, id_camion)
	values ('Movimiento', 1);

insert into sensor 
	(tipo, id_camion)
	values ('Ultrasonico', 1);


insert into sensor 
	(tipo, id_camion)
	values ('CO2', 2);

select * from sensor;


insert into lectura 
	(valor, unidad, status, fecha, id_sensor)
	values (555, 'ppm', 'Regular', now(), 1);

insert into lectura 
	(valor, unidad, status, fecha, id_sensor)
	values (900, 'ppm', 'Irregular', now(), 6);

insert into lectura 
	(valor, unidad, status, fecha, id_sensor)
	values (1, 'N/A', 'Irregular', now(), 4);

select * from lectura;

insert into viaje 
	(id_camion, fecha_inicio, fecha_final)
	values (1, '2023-11-05 00:00:00', '2023-11-05 14:00:00');


select * from viaje;






