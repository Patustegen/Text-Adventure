#include <iostream>
#include <string>
#include <locale>
#include "ConsoleControl.h"
#include <algorithm>

using namespace std;


struct Objectes {
	bool tinc;
	int hab;
	string nom;
	string desc;
};

void Inventari(Objectes obj) { //Funció et surt per pantalla el nom dels objectes que tens.
	if (obj.tinc == true) {
		ConsoleSetColor(GREEN, BLACK);
		cout << obj.nom << endl;
		ConsoleSetColor(WHITE, BLACK);
	}
}

void HayObj(Objectes obj, int habAct) { //Funció que et treu per pantalla la descripcio dels objectes que es troben a l'habitació.
	if (obj.tinc == false && obj.hab == habAct) {
		cout << obj.desc << endl;
	}
}

int Parser() {
	int nverb, nnom, CN;
	string accio, verb, nom;
	cout << "Que quieres hacer? \n"; //Demana acció
	ConsoleSetColor(MAGENTA, BLACK);
	getline(cin, accio);
	ConsoleSetColor(WHITE, BLACK);
	transform(accio.begin(), accio.end(), accio.begin(), ::toupper); //Posa a mayus
	nverb = accio.find_first_of(" "); //Busca primer espai per el verb
	nnom = accio.find_last_of(" "); //Busca ultim espai per el nom
	verb = accio.substr(0, nverb); //Retalla el verb
	nom = accio.substr(nnom + 1); //Retalla el nom
	if (verb == "COGER") CN = 100;
	else if (verb == "SOLTAR") CN = 200;
	else if (verb == "USAR") CN = 300;
	else if (verb == "ABRIR") CN = 400;
	else if (verb == "MIRAR") CN = 500;
	else if (verb == "HABLAR") CN = 600;
	else if (verb == "EMPUJAR") CN = 700;
	else if (verb == "DAR") CN = 800;
	else if (verb == "CERRAR") CN = 900;
	else if (verb == "IR") CN = 1000;
	else if (verb == "ENCENDER") CN = 1100;
	else if (verb == "APAGAR") CN = 1200;
	else if (verb == "LEER") CN = 1300;
	else if (verb == "PONER") CN = 1400;
	else if (verb == "QUITAR") CN = 1500;
	else if (verb == "INVENTARIO") CN = 0; //Si ha escrit INVENTARIO, retorna 0.
	else CN = -1; //Si no troba el verb, retorna -1
	if (CN == -1) CN = -1; //Si no ha trobat el verb, no mira el nom
	else if (CN == 0) CN = 0; //Igual amb el inventari
	else if (CN == 300) { // Si el verb era USAR, mira que utilitza
		nnom = accio.find(" ", nverb + 1); // Busca el segon espai per trobar el objecte a utilitzar
		verb = accio.substr(nverb +1, (nnom - nverb)-1); //Retalla el segon objecte i aprofit la variable verb
		if (verb == "LLAVE") { 
			CN += 2;
			if (nom == "PUERTA") CN += 10000; //Dono un valor molt gran perque no interfereixi
			else CN = -1; //LLAVE nomes es pot utilitzar amb PUERTA, aixi que si no es puerta, no t'entén
		} 
		else if (verb == "CERILLA") {
			CN += 4;
			if (nom == "DINAMITA") CN += 20000;
			else CN = -1;
		}
		else if (verb == "PALANCA") {
			CN += 3;
			if (nom == "ROJA") CN += 50000;
			else if (nom == "AZUL") CN += 60000;
			else if (nom == "VERDE") CN += 70000;
			else CN = -1;
		}
		else CN = -1;
	}
	else if (CN == 800) { //El mateix amb DAR
		nnom = accio.find(" ", nverb + 1);
		verb = accio.substr(nverb +1, (nnom - nverb)-1);
		if (verb == "PIEDRA") {
			CN += 7;
			if (nom == "PERSONA") CN += 30000;
			else CN = -1;
		}
		else if (verb == "PLATANO") {
			CN += 6;
			if (nom == "MONO") CN += 40000;
			else CN = -1;
		}
		else CN = -1;
	}
	else if (nom == "PUERTA") CN += 1;
	else if (nom == "LLAVE") CN += 2;
	else if (nom == "PALANCA") CN += 3;
	else if (nom == "CERILLA") CN += 4;
	else if (nom == "LINTERNA") CN += 5;
	else if (nom == "PLATANO") CN += 6;
	else if (nom == "PIEDRA") CN += 7;
	else if (nom == "NOTA") CN += 8;
	else if (nom == "ESTANTERIA") CN += 9;
	else if (nom == "NORTE") CN += 12;
	else if (nom == "SUR") CN += 13;
	else if (nom == "ESTE") CN += 14;
	else if (nom == "OESTE") CN += 15;
	else if(nom == "PERSONA") CN += 30000;
	else if (nom == "MONO") CN += 40000;
	else CN = -1;
	return CN;
}




int main() {
	//Creació de variables
	
	int habActual = 0;
	int cn = 0;
	bool block[4]{ true, true, true, true };
	bool puerta[2]{ false, false };
	bool palanca[3]{ false, false, true };

	Objectes Inventario[10];

	Inventario[0].tinc = false;
	Inventario[0].hab = 1000;
	Inventario[0].nom = "LLAVE";
	Inventario[0].desc = "Hay una llave en el suelo.";
	Inventario[1].tinc = false;
	Inventario[1].hab = 10;
	Inventario[1].nom = "PALANCA";
	Inventario[1].desc = "Hay una palanca que parece ir en algun sitio.";
	Inventario[2].tinc = false;
	Inventario[2].hab = 1000;
	Inventario[2].nom = "CERILLA";
	Inventario[2].desc = "Hay una caja de cerillas medio usadas.";
	Inventario[3].tinc = false;
	Inventario[3].hab = 12;
	Inventario[3].nom = "LINTERNA";
	Inventario[3].desc = "Hay una linterna amarilla, parece que funciona.";
	Inventario[4].tinc = false;
	Inventario[4].hab = 1000;
	Inventario[4].nom = "PLATANO";
	Inventario[4].desc = "Hay un platano, tiene buena pinta.";
	Inventario[5].tinc = false;
	Inventario[5].hab = 1000;
	Inventario[5].nom = "PIEDRA BRILLANTE";
	Inventario[5].desc = "Hay una piedra que brilla con un tono rojo.";

	bool start = false;
	bool game = true;
	bool buit = true;
	
	cout << "Selecciona, 0(como jugar), 1(jugar): \n"; //Menu
	cin >> start;
	cin.clear();
	cin.ignore(256, '\n');

	while (start == false) { //Menu en un WHILE per si no t'ha quedat clar
		ConsoleClear();
		cout << "El objetivo del juego es escapar del templo. Se te va a presentar una situacion en cada sala con todos los objetos que hay en ella. \n Para interactuar, puedes escribir: VERBO OBJETO (PERSONA). Solo se interactua con un tercer objeto con los verbos DAR o USAR, de otra forma, el juego no te entendera. \n No importa minusculas o mayusculas o texto entre medio del verbo y el objeto. En qualquier momento puedes poner INVENTARIO para acceder a tu inventario. \n \n \n";
		cout << "Selecciona, 0(como jugar), 1(jugar): \n";
		cin >> start;
		cin.clear();
		cin.ignore(256, '\n');
	}
	ConsoleClear();
	while (game == true) { // Comença el bucle
		ConsoleSetColor(CYAN, BLACK);
		switch (habActual) { //Descripcio de cada habitacio amb variacions depenent del que passa
			case 0:
				cout << "Despiertas en una habitacion de un templo. Miras a tu alrededor y poco a poco recuerdas que estabas de exploracion cuando el suelo se volvio inestable y caiste. La habitacion parece estar vacia y hay una PUERTA al NORTE. \n";
				if (puerta[0] == false) cout << "La PUERTA esta cerrada, no parece tener candado. \n";
				else cout << "La PUERTA esta abierta, puedes IR hacia el NORTE. \n";
				break;
			case 9:
				cout << "En esta habitacion hay tres palancas de tres colores. \n";
				if (palanca[0] == false) cout << "La palanca roja apunta hacia arriba. \n";
				else cout << "La palanca roja apunta hacia abajo. \n";
				if (palanca[1] == false && Inventario[1].hab == 1000) cout << "La palanca azul apunta hacia abajo. \n";
				else if (palanca[1] == true && Inventario[1].hab == 1000) cout << "La palanca azul apunta hacia arriba. \n";
				else if (Inventario[1].tinc == true) cout << "Parece que puedo PONER mi PALANCA en el centro. \n";
				else cout << "En el centro parece que va una PALANCA. \n";
				if (palanca[2] == false) cout << "La palanca verde apunta hacia abajo. \n";
				else cout << "La palanca verde apunta hacia arriba. \n";
				break;
			case 10:
				cout << "Esta sala parece el hall del templo, puedo ver un pasillo largo y oscuro al NORTE, una sala abierta al ESTE y una sala no muy grande al OESTE. \n Al SUR esta la sala donde he caido. \n";
				break;
			case 11:
				cout << "Es una habitacion vacia y sin techo. \n Parece que hay una NOTA en una columna alta. Puedo MIRAR mas de cerca o intentar LEER la NOTA. \n";
				if (block[0] == true) cout << "Una piedra bloquea una posible habitacion al ESTE y al OESTE esta la sala principal. \n";
				else cout << "La piedra ya no bloquea la habitacion del ESTE y al OESTE esta la sala principal. \n";
				break;
			case 12:
				cout << "Hay mucho polvo, parece que hace tiempo que nadie entra aqui. \n";
				break;
			case 20:
				if (Inventario[3].tinc == true && block[1] == false) cout << "Con la luz de la linterna puedes ver una salida al NORTE y el pasillo del que vengo al SUR. \n";
				else if (Inventario[3].tinc == true && block[1] == true) cout << "No se ve nada en esta habitacion, deberias ENCENDER la LINTERNA. \n";
				else cout << "No ves nada en esta habitacion, deberias encontrar alguna manera de iluminarla. \n";
				break;
			case 30:
				if (Inventario[5].tinc == true) cout << "El MONO se esta comiendo el PLATANO tranquilamente. Deberia DAR la piedra a esa PERSONA. \n";
				else if (Inventario[2].tinc == true) cout << "El MONO se esta comiendo el PLATANO tranquilamente. \n";
				else cout << "Te encuentras a una PERSONA. No te ha visto porque esta ocupado intentando alcanzar un MONO que tiene una PIEDRA brillante entre sus manos. \n";
				cout << "Al SUR esta la habitacion oscura, al ESTE hay una habitacion de piedra y al OESTE hay una habitacion que parece ser un almacen. \n";
				break;
			case 29:
				cout << "Esta habitacion parece un almacen de objetos. \n";
				if (Inventario[4].tinc == false && Inventario[4].hab == 1000) cout << "Hay una ESTANTERIA con un PLATANO encima que parece estar inestable. Seguramente EMPUJANDO la ESTANTERIA se podria lograr que el PLATANO caiga. \n";
				cout << "Al ESTE esta la habitacion con la PERSONA y el MONO de la que vengo. \n";
				break;
			case 31:
				cout << "Es una habitacion hecha de piedra caliza. \n";
				if (block[2] == true) cout << "Al NORTE hay una PUERTA con un candado de hierro. Sin su LLAVE no podre avanzar. \n";
				else cout << "La PUERTA del NORTE ya no esta bloqueada. \n";
				cout << "Al ESTE hay un tunel excavado y al OESTE esta la habitacion del MONO y la persona. \n";
				break;
			case 32:
				if (Inventario[2].tinc == true) cout << "El tunel es largo y se pueden ver unas cargas de DINAMITA justo debajo de unas piedras que parecen bloquear parte del tunel. \n Puedo USAR una CERILLA con la DINAMITA para poder ver que hay detras. \n";
				else if (Inventario[2].tinc == false && Inventario[2].hab == 1000) cout << "El tunel es largo y se pueden ver unas cargas de DINAMITA justo debajo de unas piedras que parecen bloquear parte del tunel. \n Necesito algo para poder quemar la mecha de la DINAMITA. \n";
				else cout << "El tunel se aguanta por poco y la DINAMITA ha dejado un hueco grande en el suelo. \n";
				cout << "Al OESTE esta la sala anterior. \n";
				break;
			case 41:
				cout << "Sales por la puerta a lo que parece ser un altar de sacrificios. Te sigue la PERSONA de la sala del mono. \n";
				if (block[3] == true) {
					cout << "Al NORTE hay una calavera gigante con la boca cerrada, el ojo izquierdo de cristal rojo y en el derecho un hueco. \n";
					if (Inventario[5].tinc == true) cout << "Puedes probar de PONER la PIEDRA en el ojo de la calavera. \n";
					else cout << "Deberia HABLAR con la PERSONA para poder PONER la PIEDRA en el ojo de la calavera. \n";
				}
				else if (block[3] == false)  cout << "Al NORTE hay una calavera con dos ojos de PIEDRAs brillantes rojas y la boca abierta que parece llevar a una salida. \n";
				break;
			default:
				cout << "Has muerto \n";
		}
		ConsoleSetColor(WHITE, BLACK);
		for (int i = 0; i < 10; i++) { //Imprimeix els objectes que hi ha a la sala.
			ConsoleSetColor(GREEN, BLACK);
			HayObj(Inventario[i], habActual);
			ConsoleSetColor(WHITE, BLACK);
		}
		cn = Parser(); //Crides al parser
		ConsoleClear();
		switch (cn) { //Coses que poden passar al parser
			case 0:
				for (int i = 0; i < 6; i++) {
					if(Inventario[i].tinc == true) buit = false;
					Inventari(Inventario[i]);
					ConsoleSetColor(DARKRED, BLACK);
					if (i == 5 && buit == true) cout << "No tienes nada en el inventario. \n";
					ConsoleSetColor(WHITE, BLACK);
				}
				buit = true;
				break;
			case 101:
				cout << "No puedes coger una puerta! \n";
				break;
			case 201:
				cout << "No puedes soltar una puerta! \n";
				break;
			case 301:
				cout << "Para usar puertas, escribe IR \n";
				break;
			case 401:
				if ((habActual == 0 || habActual == 10) && puerta[0] == false) {
					puerta[0] = true;
					cout << "Has abierto la puerta. \n";
				}
				else if ((habActual == 0 || habActual == 10) && puerta[0] == true) cout << "Esta puerta ya esta abierta. \n";
				else if (habActual == 31 && block[2] == true) cout << "Primero tienes que abrir el candado. \n";
				else if ((habActual == 31 || habActual == 41) && puerta[1] == false) {
					puerta[1] = true;
					cout << "Has abierto la puerta. \n";
				}
				else if ((habActual == 31 || habActual == 41) && puerta[1] == true) cout << "Esta puerta ya esta abierta. \n";
				else cout << "No hay ninguna puerta. \n";
				break;
			case 501:
				if ((habActual == 31 || habActual == 41) && puerta[1] == true) cout << "Es una puerta abierta. \n";
				else if ((habActual == 31 || habActual == 41) && puerta[1] == false) cout << "Es una puerta cerrada. \n";
				else if ((habActual == 0 || habActual == 10) && puerta[0] == true) cout << "Es una puerta abierta. \n";
				else if ((habActual == 0 || habActual == 10) && puerta[0] == false) cout << "Es una puerta cerrada. \n";
				else cout << "No hay ninguna puerta. \n";
				break;
			case 701:
				if (habActual == 31 || habActual == 41) cout << "No se mueve. \n";
				else if (habActual == 0 || habActual == 10) cout << "No se mueve. \n";
				else cout << "No hay ninguna puerta. \n";
				break;
			case 901:
				if ((habActual == 0 || habActual == 10) && puerta[0] == true) {
					puerta[0] = false;
					cout << "Has cerrado la puerta. \n";
				}
				else if ((habActual == 0 || habActual == 10) && puerta[0] == false) cout << "Esta puerta ya esta cerrada";
				else if ((habActual == 31 || habActual == 41) && puerta[1] == true) {
					puerta[1] = false;
					cout << "Has cerrado la puerta. \n";
				}
				else if ((habActual == 31 || habActual == 41) && puerta[1] == false) cout << "Esta puerta ya esta cerrada";
				else cout << "No hay ninguna puerta. \n";
				break;
			case 102:
				if (Inventario[0].tinc == false && Inventario[0].hab == habActual) {
					Inventario[0].tinc = true;
					cout << "Has cogido la llave. \n";
				}
				else if (Inventario[0].tinc == true) cout << "Ya tienes esta llave. \n";
				else cout << "No hay ninguna llave. \n";
				break;
			case 202:
				if (Inventario[0].tinc == true) {
					Inventario[0].tinc = false;
					Inventario[0].hab = habActual;
					cout << "Has soltado la llave. \n";
				}
				else cout << "No tienes ninguna llave. \n";
				break;
			case 302:
				if (Inventario[0].tinc == true) cout << "Indica con que quieres usar esta llave. \n";
				else cout << "No tienes ninguna llave. \n";
				break;
			case 502:
				if (Inventario[0].tinc == true) cout << "Es una llave dorada brillante. \n";
				else cout << "No tienes ninguna llave. \n";
				break;
			case 802:
				if (Inventario[0].tinc == true) cout << "Necesitas a alguien para dar el objeto. \n";
				else cout << "No tienes ninguna llave. \n";
				break;
			case 1402:
				if (Inventario[0].tinc == true) cout << "Para utilizar una llave: USAR LLAVE en PUERTA. \n";
				else cout << "No tienes ninguna llave. \n";
				break;
			case 103:
				if (Inventario[1].tinc == false && Inventario[1].hab == habActual) {
					Inventario[1].tinc = true;
					cout << "Has cogido la palanca. \n";
				}
				else if (Inventario[1].tinc == true) cout << "Ya tienes la palanca. \n";
				else cout << "No hay ninguna palanca. \n";
				break;
			case 203:
				if (Inventario[1].tinc == true) {
					Inventario[1].tinc = false;
					Inventario[1].hab = habActual;
					cout << "Has soltado ninguna palanca. \n";
				}
				else cout << "No tienes esta palanca. \n";
				break;
			case 303:
				if (Inventario[1].tinc == true) cout << "No puedes usar la palanca con nada, prueba con PONER PALANCA. \n";
				else cout << "No tienes ninguna palanca. \n";
				break;
			case 503:
				if (Inventario[1].tinc == true) cout << "Es una palanca azul. \n";
				else cout << "No tienes ninguna palanca. \n";
				break;
			case 803:
				if (Inventario[1].tinc == true) cout << "Necesitas a alguien para dar el objeto. \n";
				else cout << "No tienes ninguna palanca. \n";
				break;
			case 1403:
				if (Inventario[1].tinc == true && habActual == 9) {
					Inventario[1].tinc = false;
					Inventario[1].hab = 1000;
					cout << "Has puesto la palanca azul en su sitio. \n";
				}
				else if (Inventario[1].tinc == true && habActual != 9) cout << "No puedes colocar la palanca aqui. \n";
				else cout << "No tienes ninguna palanca. \n";
				break;
			case 1503:
				if (Inventario[1].hab == 1000 && habActual == 9) {
					Inventario[1].tinc = true;
					Inventario[1].hab == habActual;
					cout << "Has quitado la palanca azul de su sitio. \n";
				}
				else if (Inventario[1].tinc == true) cout << "Ya tienes la palanca. \n";
				else cout << "No hay ninguna palanca. \n";
				break;
			case 104:
				if (Inventario[2].tinc == false && Inventario[2].hab == habActual) {
					Inventario[2].tinc = true;
					cout << "Has cogido las cerillas. \n";
				}
				else if (Inventario[2].tinc == true) cout << "Ya tienes las cerillas. \n";
				else cout << "No hay ninguna cerilla. \n";
				break;
			case 204:
				if (Inventario[2].tinc == true) {
					Inventario[2].tinc = false;
					Inventario[2].hab = habActual;
					cout << "Has soltado las cerillas. \n";
				}
				else cout << "No tienes las cerillas. \n";
				break;
			case 304:
				if (Inventario[2].tinc == true) cout << "Necesitas otro objeto para usar las cerillas, prueba con USAR CERILLA con... \n";
				else cout << "No tienes ninguna cerilla. \n";
				break;
			case 504:
				if (Inventario[2].tinc == true) cout << "Es una caja de cerillas medio usada. \n";
				else cout << "No tienes ninguna cerilla. \n";
				break;
			case 804:
				if (Inventario[2].tinc == true) cout << "Necesitas a alguien para dar el objeto. \n";
				else cout << "No tienes ninguna cerilla. \n";
				break;
			case 1104:
				if (Inventario[2].tinc == true) cout << "Asi no!! Para usar la cerilla prueba con USAR CERILLA con ... \n";
				else cout << "No tienes ninguna cerilla. \n";
				break;
			case 1404:
				if (Inventario[2].tinc == true) cout << "Para poner la cerilla en algun sitio prueba con SOLTAR o USAR. \n";
				else cout << "No tienes ninguna cerilla. \n";
				break;
			case 1504:
				if (Inventario[2].tinc == true) cout << "Para quitar la cerilla de algun sitio prueba con SOLTAR o USAR. \n";
				else cout << "No tienes ninguna cerilla. \n";
				break;
			case 105:
				if (Inventario[3].tinc == false && Inventario[3].hab == habActual) {
					Inventario[3].tinc = true;
					cout << "Has cogido la linterna. \n";
				}
				else if (Inventario[3].tinc == true) cout << "Ya tienes la linterna. \n";
				else cout << "No hay ninguna linterna. \n";
				break;
			case 205:
				if (Inventario[3].tinc == true) {
					Inventario[3].tinc = false;
					Inventario[3].hab = habActual;
					cout << "Has soltado la linterna. \n";
				}
				else cout << "No tienes la linterna. \n";
				break;
			case 305:
				if (Inventario[3].tinc == true) cout << "Para usar la linterna, prueba con ENCENDER/APAGAR LINTERNA. \n";
				else cout << "No tienes ninguna linterna. \n";
				break;
			case 505:
				if (Inventario[3].tinc == true) cout << "Es una linterna amarilla, funciona. \n";
				else cout << "No tienes ninguna linterna. \n";
				break;
			case 805:
				if (Inventario[3].tinc == true) cout << "Necesitas a alguien para dar el objeto. \n";
				else cout << "No tienes ninguna linterna. \n";
				break;
			case 1105:
				if (Inventario[3].tinc == true && block[1] == true) {
					block[1] = false;
					cout << "Has encendido la linterna. \n";
				}
				else if (Inventario[3].tinc == true && block[1] == false) cout << "La linterna ya esta encendida. \n";
				else cout << "No tienes ninguna linterna. \n";
				break;
			case 1205:
				if (Inventario[3].tinc == true && block[1] == false) {
					block[1] = true;
					cout << "Has apagado la linterna. \n";
				}
				else if (Inventario[3].tinc == true && block[1] == true) cout << "La linterna ya esta apagada. \n";
				else cout << "No tienes ninguna linterna. \n";
				break;
			case 1405:
				if (Inventario[3].tinc == true) cout << "Para poner la linterna en algun sitio prueba con SOLTAR o USAR. \n";
				else cout << "No tienes ninguna linterna. \n";
				break;
			case 1505:
				if (Inventario[3].tinc == true) cout << "Para quitar la linterna de algun sitio prueba con SOLTAR o USAR. \n";
				else cout << "No tienes ninguna linterna. \n";
				break;
			case 106:
				if (Inventario[4].tinc == false && Inventario[4].hab == habActual) {
					Inventario[4].tinc = true;
					cout << "Has cogido el platano. \n";
				}
				else if (Inventario[4].tinc == true) cout << "Ya tienes el platano. \n";
				else cout << "No hay ningun platano. \n";
				break;
			case 206:
				if (Inventario[4].tinc == true) {
					Inventario[4].tinc = false;
					Inventario[4].hab = habActual;
					cout << "Has soltado el platano. \n";
				}
				else cout << "No tienes el platano. \n";
				break;
			case 306:
				if (Inventario[4].tinc == true) cout << "No!! El platano lo podemos DAR al MONO. \n";
				else cout << "No tienes ningun platano. \n";
				break;
			case 506:
				if (Inventario[4].tinc == true) cout << "Es un platano en buen estado. \n";
				else cout << "No tienes ningun platano. \n";
				break;
			case 806:
				if (Inventario[4].tinc == true) cout << "Necesitas a alguien para dar el objeto. \n";
				else cout << "No tienes ningun platano. \n";
				break;
			case 1406:
				if (Inventario[4].tinc == true) cout << "Para poner el platano en algun sitio prueba con SOLTAR. \n";
				else cout << "No tienes ningun platano. \n";
				break;
			case 1506:
				if (Inventario[4].tinc == true) cout << "Para quitar el platano de algun sitio prueba con SOLTAR. \n";
				else cout << "No tienes ningun platano. \n";
				break;
			case 107:
				if (Inventario[5].tinc == false && Inventario[5].hab == habActual) {
					Inventario[5].tinc = true;
					cout << "Has cogido la piedra brillante. \n";
				}
				else if (Inventario[5].tinc == true) cout << "Ya tienes la piedra. \n";
				else cout << "No hay ninguna piedra. \n";
				break;
			case 207:
				if (Inventario[5].tinc == true) {
					Inventario[5].tinc = false;
					Inventario[5].hab = habActual;
					cout << "Has soltado la piedra brillante. \n";
				}
				else cout << "No tienes la piedra brillante. \n";
				break;
			case 307:
				if (Inventario[5].tinc == true && habActual == 41) cout << "No se puede usar la piedra, prueba con PONER PIEDRA. \n";
				else cout << "No tienes ninguna piedra. \n";
				break;
			case 507:
				if (Inventario[5].tinc == true) cout << "Es una piedra pesada y que brilla en un tono rojo. \n";
				else cout << "No tienes ninguna piedra. \n";
				break;
			case 807:
				if (Inventario[5].tinc == true) cout << "Necesitas a alguien para dar el objeto. \n";
				else cout << "No tienes ninguna piedra. \n";
				break;
			case 1407:
				if (Inventario[5].tinc == true && habActual == 41) {
					Inventario[5].tinc = false;
					Inventario[5].hab = 1;
					block[3] = false;
					cout << "Has puesto la piedra en el hueco del ojo de la calavera. El suelo retumba y ves como se abre la boca de la calavera. \n";
				}
				else if (Inventario[5].tinc == true && habActual != 41) cout << "No puedes poner la piedra en ningun sitio. \n";
				else cout << "No tienes ninguna piedra. \n";
				break;
			case 1507:
				if (habActual == 41 && Inventario[5].hab == 1) cout << "Intentas quitar la piedra pero parece que se ha quedado pegada. \n";
				else cout << "No hay ninguna piedra. \n";
				break;
			case 108:
				if (habActual == 11) cout << "No llegas a la nota, esta muy lejos. \n";
				else cout << "No hay ninguna nota. \n";
				break;
			case 208:
				cout << "No tienes ninguna nota. \n";
				break;
			case 508:
				if (habActual == 11) cout << "La nota dice: ROJO v, AZUL ^, VERDE ^. \n";
				else cout << "No hay ninguna nota. \n";
				break;
			case 1308:
				if (habActual == 11) cout << "La nota dice: ROJO v, AZUL ^, VERDE ^. \n";
				else cout << "No hay ninguna nota. \n";
				break;
			case 1508:
				if (habActual == 11) cout << "No llegas a la nota, esta muy lejos. \n";
				else cout << "No hay ninguna nota. \n";
				break;
			case 509:
				if (habActual == 29) cout << "Parece una columna bastante inestable. \n";
				else cout << "No hay ninguna estanteria. \n";
				break;
			case 709:
				if (habActual == 29) {
					Inventario[4].hab = habActual;
					cout << "La estanteria se ha movido y ha dejado caer el PLATANO. \n";
				}
				else cout << "No hay ninguna nota. \n";
				break;
			case 1012:
				if ((habActual == 31 && block[2] == false) || (habActual == 31 && puerta[1] == true) || (habActual == 41 && block[3] == false) || (habActual == 0 && puerta[0] == true) || (habActual == 20 && block[1] == false)) habActual += 10;
				else if (habActual == 10) habActual += 10;
				else cout << "No puedes ir hacia esa direccion. \n";
				break;
			case 1013:
				if ((habActual == 41 && puerta[1] == true) || (habActual == 10 && puerta[0] == true)) habActual -= 10;
				else if (habActual == 20 || habActual == 30) habActual -= 10;
				else cout << "No puedes ir hacia esa direccion. \n";
				break;
			case 1014:
				if (habActual == 11 && block[0] == false) habActual += 1;
				else if (habActual == 9 || habActual == 10 || habActual == 29 || habActual == 30 || habActual == 31) habActual += 1;
				else cout << "No puedes ir hacia esa direccion. \n";
				break;
			case 1015:
				if (habActual != 0 && habActual != 9 && habActual != 20 && habActual != 29 && habActual != 41) habActual -= 1;
				else cout << "No puedes ir hacia esa direccion. \n";
				break;
			case 10302:
				if (habActual == 31 && Inventario[0].tinc == true && block[2] == true) {
					block[2] = false;
					cout << "Has abierto el candado de la puerta. \n";
				}
				else if (habActual == 31 && Inventario[0].tinc == true && block[2] == false) cout << "El candado de la puerta ya esta abierto. \n";
				else if (habActual == 31 && Inventario[0].tinc == false) cout << "No tienes la llave. \n";
				else cout << "No puedes hacer eso aqui. \n";
				break;
			case 20304:
				if (habActual == 32 && Inventario[2].tinc == true && Inventario[0].hab == 1000) {
					Inventario[0].hab = habActual;
					cout << "La dinamita ha explotado y distingues una LLAVE entre los escombros. \n";
				}
				else if (habActual == 32 && Inventario[2].tinc == true && Inventario[0].hab != 1000) cout << "La dinamita ya ha explotado. \n";
				else if (habActual == 32 && Inventario[2].tinc == false) cout << "No tienes cerillas. \n";
				else cout << "No puedes hacer eso aqui. \n";
				break;
			case 30807:
				if (habActual == 30 && Inventario[5].tinc == true) {
					Inventario[5].tinc = false;
					Inventario[2].tinc = true;
					Inventario[5].hab = 1;
					cout << "Le das la PIEDRA. \n";
					ConsoleSetColor(LIGHTGREY, BLACK);					
					cout << "\t Muchas gracias!! Toma, seguro que tu le daras mejor utilidad a esto. \n"
					ConsoleSetColor(WHITE, BLACK);
					cout << "Te ha dado unas CERILLAs \n";
				}
				else if (habActual == 30 && Inventario[5].tinc == false) cout << "No tienes la PIEDRA. \n";
				else cout << "No puedes hacer eso aqui. \n";
				break;
			case 30600:
				if (habActual == 30 && Inventario[5].tinc == false) {
					cout << "Te acercas a la persona \n";
					ConsoleSetColor(LIGHTGREY, BLACK);
					cout << "\t Ese maldito MONO me ha robado una PIEDRA muy importante!! Recuperala por mi y te recompensare. \n";
					ConsoleSetColor(WHITE, BLACK);
					cout << "Puedo intentar distraer al MONO, a lo mejor le puedo DAR algo que lo distraiga. \n";
				}
				else if (habActual == 41 && Inventario[5].hab == 1) {
					Inventario[5].tinc = true;
					Inventario[5].hab = habActual;
					cout << "Le pides la piedra. \n";
					ConsoleSetColor(LIGHTGREY, BLACK);
					cout << "\t La piedra?? De acuerdo, te la doy pero no la pierdas. \n";
					ConsoleSetColor(WHITE, BLACK);
					cout << "Has recibido la PIEDRA. \n";
				}
				else cout << "No puedes hacer eso aqui. \n";
				break;
			case 40806:
				if (habActual == 30 && Inventario[4].tinc == true) {
					Inventario[4].tinc = false;
					Inventario[5].tinc = true;
					Inventario[4].hab = 1;
					cout << "Le das el PLATANO al MONO, que rapidamente suelta la PIEDRA. Coges la PIEDRA en el aire. \n";
				}
				else if (habActual == 30 && Inventario[5].tinc == false) cout << "No tienes el PLATANO. \n";
				else cout << "No puedes hacer eso aqui. \n";
				break;
			case 40600:
				if (habActual == 30) {
					cout << "Saludas al mono. \n";
					ConsoleSetColor(DARKYELLOW, BLACK);
					cout << "\t Uh UH UH AHA AHH \n";
					ConsoleSetColor(WHITE, BLACK);
					cout << "Te ha respondido \n";
				}
				else cout << "No puedes hacer eso aqui. \n";
				break;
			case 50303:
				if (habActual == 9) {
					if (palanca[0] == true) {
						palanca[0] = false;
						cout << "Tiras la PALANCA ROJA hacia arriba. \n";
					}
					else if (palanca[0] == false) {
						palanca[0] = true;
						cout << "Tiras la PALANCA ROJA hacia abajo. \n";
					}
				}
				else cout << "No puedes hacer eso aqui. \n";
				if (palanca[0] == true && palanca[1] == true && palanca[2] == true) {
					block[0] = false;
					cout << "Escuchas el sonido de una roca levantandose. \n";
				}
				break;
			case 60303:
				if (habActual == 9) {
					if (palanca[1] == true && Inventario[1].hab == 1000) {
						palanca[1] = false;
						cout << "Tiras la PALANCA AZUL hacia abajo. \n";
					}
					else if (palanca[1] == false && Inventario[1].hab == 1000) {
						palanca[1] = true;
						cout << "Tiras la PALANCA AZUL hacia arriba. \n";
					}
					else if (Inventario[1].hab != 1000) cout << "No hay ninguna PALANCA. \n";
				}
				else cout << "No puedes hacer eso aqui. \n";
				if (palanca[0] == true && palanca[1] == true && palanca[2] == true) {
					block[0] = false;
					cout << "Escuchas el sonido de una roca levantandose. \n";
				}
				break;
			case 70303:
				if (habActual == 9) {
					if (palanca[2] == true) {
						palanca[2] = false;
						cout << "Tiras la PALANCA VERDE hacia abajo. \n";
					}
					else if (palanca[2] == false) {
						palanca[2] = true;
						cout << "Tiras la PALANCA VERDE hacia arriba. \n";
					}
				}
				else cout << "No puedes hacer eso aqui. \n";
				if (palanca[0] == true && palanca[1] == true && palanca[2] == true) {
					block[0] = false;
					cout << "Escuchas el sonido de una roca levantandose. \n";
				}
				break;
			default:
				cout << "No te entiendo, vuelve a escribir que quieres hacer \n";
		}
		if (habActual == 51) {
			cout << "ENORABUENA!! Has conseguido escapar! Cuando sales del templo, consigues ver un poblado al lado de un rio, puede ser tu salvacion. \n FIN \n";
			cout << "Quieres volver a jugar?, 0(salir), 1(volver a jugar): \n";
			cin >> game;
			cin.clear();
			cin.ignore(256, '\n');
			if (game == true) {
				Inventario[0].tinc = false;
				Inventario[0].hab = 1000;
				Inventario[1].tinc = false;
				Inventario[1].hab = 10;
				Inventario[2].tinc = false;
				Inventario[2].hab = 1000;
				Inventario[3].tinc = false;
				Inventario[3].hab = 12;
				Inventario[4].tinc = false;
				Inventario[4].hab = 1000;
				Inventario[5].tinc = false;
				Inventario[5].hab = 1000;
				habActual = 0;
				for (int i = 0; i < 4; i++) {
					block[i] = true;
				}
				puerta[0] = false;
				puerta[1] = false;
				palanca[0] = false;
				palanca[1] = false;
				palanca[2] = true;
			}
		}
	}

}

