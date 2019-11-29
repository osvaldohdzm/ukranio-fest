#include "Mensaje.h"
#include <string.h>
#include <iostream>

using namespace std;

Mensaje::Mensaje(){
	this->source = 0;
	this->dest = 0;
	this->opcode = 0;
	this->count = 0;
	this->offset = 0;
	this->extra1 = 0;
	this->extra2 = 0;
	this->result = 0;
	strcpy( this->name, "" );
	strcpy( this->data, "" );
}

Mensaje::Mensaje( long source, long dest, long opcode, long count, long offset, char *name, char *data){
	this->source = source;
	this->dest = dest;
	this->opcode = opcode;
	this->count = count;
	this->offset = offset;
	this->extra1 = 0;
	this->extra2 = 0;
	this->result = 0;
	strcpy( this->name, name );
	strcpy( this->data, data );
}

void Mensaje::setSource( long source ){ this->source = source; }
void Mensaje::setDest( long dest ){ this->dest = dest; }
void Mensaje::setOpcode( long opcode ){ this->opcode = opcode; }
void Mensaje::setCount( long count ){ this->count = count; }
void Mensaje::setOffset( long offset ){ this->offset = offset; }
void Mensaje::setExtra1( long extra1 ){ this->extra1 = extra1; }
void Mensaje::setExtra2( long extra2 ){ this->extra2 = extra2; }
void Mensaje::setResult( long result ){ this->result = result; }
void Mensaje::setName( char * name ){ strcpy(this->name, name); }
void Mensaje::setData( char * data ){ strcpy(this->data, data); }
long Mensaje::getSource(){ return source; }
long Mensaje::getDest(){ return dest; }
long Mensaje::getOpcode(){ return opcode; }
long Mensaje::getCount(){ return count; }
long Mensaje::getOffset(){ return offset; }
long Mensaje::getExtra1(){ return extra1; }
long Mensaje::getExtra2(){ return extra2; }
long Mensaje::getResult(){ return result; }
char *Mensaje::getName(){ return name; }
char *Mensaje::getData(){ return data; }
void Mensaje::imprimeMensaje(){
	cout << "-------------------------------" << endl;
	cout << "--- Informacion del mensaje ---" << endl;
	cout << "-------------------------------" << endl;
	cout << "--->Identidad del emisor: " << source << endl;
	cout << "--->Identidad del receptor: " << dest << endl;
	switch( opcode ){
		case 1:
			cout << "--->Operacion a realizar: CREATE" << endl;
		break;

		case 2:
			cout << "--->Operacion a realizar: READ" << endl;
		break;

		case 3:
			cout << "--->Operacion a realizar: WRITE" << endl;
		break;

		case 4:
			cout << "--->Operacion a realizar: DELETE" << endl;
		break;

		default:
			cout << "--->Operacion a realizar: DESCONOCIDA" << endl;
		break;
	}
	cout << "--->Numero de bytes por transmitir: " << count << endl;
	cout << "--->Lugar del archivo donde comienza la R/W: " << offset << endl;
	cout << "--->Campo adicional 1: " << extra1 << endl;
	cout << "--->Campo adicional 2: " << extra2 << endl;
	switch( result ){
		case 0:
			cout << "--->Resultado de la operacion: Operacion desarrollada en forma correcta" << endl;
		break;
		
		case -1:
			cout << "--->Resultado de la operacion: Solicitud de una operacion desconocida" << endl;
		break;

		case -2:
			cout << "--->Resultado de la operacion: Error en un parametro" << endl;
		break;

		case -3:
			cout << "--->Resultado de la operacion: Error en disco u error en E/S" << endl;
		break;

		case -4:
			cout << "--->Resultado de la operacion: Operacion desarrollada en forma incorrecta" << endl;
		break;

	}
	cout << "--->Nombre del archivo en el cual se opera: " << name << endl;
	cout << "--->Datos por leer o escribir: " << data << endl;

}

