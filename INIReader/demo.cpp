//@file iniClass.h
//@Info Small easy to use INI reader class for C++
//@By Ben a.k.a DreamVB
#include <iostream>
#include "iniClass.h"

using namespace std;

int main(int argc, char *argv[]){

	TINIRead ini;

	if (argc != 2){
		std::cout << "Config file required." << std::endl;
		exit(EXIT_FAILURE);
	}
	//Open ini file.
	ini.Open(argv[1]);

	//Test if ini file was opened.
	if (!ini.IsOpen){
		std::cout << "Faild to open ini file." << std::endl;
		exit(EXIT_FAILURE);
	}

	//Display demo
	std::cout << "Selection1" << std::endl;
	std::cout << "Name    : " << ini.ReadString("selection1", "name") << std::endl;
	std::cout << "Age     : " << ini.ReadInteger("selection1", "age") << std::endl;
	std::cout << "PI      : " << ini.ReadFloat("selection1", "pi") << std::endl;
	std::cout << "Selection2" << std::endl;
	std::cout << "Color   : " << ini.ReadString("selection2", "color") << std::endl;

	return EXIT_SUCCESS;
}