//@file iniClass.h
//@Info Small easy to use INI reader class for C++
//@By Ben a.k.a DreamVB

#include <iostream>
#include <algorithm>
#include <cctype>
#include <string>
#include <fstream>
#include <map>

using namespace std;

class TINIRead{
private:
	using selections = map<std::string, std::string>;
	using inifile = map<std::string, selections>;
	//this holds all the ini data in the maps above
	inifile ini;
	//Filename for ini file
	std::string lzFilename;

	static inline void StrUpper(std::string &src){
		//Convert a string to uppercase
		std::transform(src.begin(), src.end(), src.begin(), ::toupper);
	}

	// trim left side of string
	static inline void ltrim(std::string &s) {
		s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
			return !std::isspace(ch);
		}));
	}

	// trim right end of string
	static inline void rtrim(std::string &s) {
		s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
			return !std::isspace(ch);
		}).base(), s.end());
	}

	// trim both sides of a string
	static inline void trim(std::string &s) {
		ltrim(s);
		rtrim(s);
	}

	std::string get_selection(std::string s){
		//Delete [ and ] from string
		std::string s0 = s;
		s0 = s.substr(1, s0.length() - 2);
		trim(s0);
		return s0;
	}
	//Return true if a string is included in []
	bool is_selection(std::string s){
		bool flag = false;
		//Check length
		if (s.length() > 0){
			//Check start and end of string
			if (s[0] == '[' && s[s.length() - 1] == ']'){
				flag = true;
			}
		}
		return flag;
	}

	// Main code for reading the ini file.
	bool ReadIni(void)
	{
		fstream cfg;
		std::string sLine;
		std::string key_value;
		std::string key_name;
		std::string selection;
		size_t pos;

		//Read ini filename
		cfg.open(lzFilename, std::ios::in);

		//Check if file was opened
		if (!cfg.is_open()){
			return false;
		}
		//Loop the file extracting the lines
		while (getline(cfg, sLine)){
			//Trim the line
			trim(sLine);

			if (sLine.length() > 0){
				//Skip comments
				if (sLine[0] != ';'){
					//Check if line is selection [selection]
					if (is_selection(sLine)){
						selection = get_selection(sLine);
					}
					//Check if line contains = must be a key pair
					pos = sLine.find_first_of("=");
					if (pos != string::npos){
						//Get key name
						key_name = sLine.substr(0, pos);
						//Get value
						key_value = sLine.substr(pos + 1);
						//Trim key name of spaces.
						trim(key_name);
						//Trim key value spaces
						trim(key_value);
						//Uppercase key name and selection
						StrUpper(key_name);
						StrUpper(selection);
						//Set map data
						ini[selection][key_name] = key_value;
					}
				}
			}
		}
		//Close ini file.
		cfg.close();

		//Clear up time
		sLine.clear();
		key_name.clear();
		key_value.clear();
		selection.clear();
		return true;
	}

public:
	//Lets us know if the ini file was opened.
	bool IsOpen;

	TINIRead(){

	}
	//Destroy the maps and class
	~TINIRead(){
		lzFilename.clear();
		ini.clear();
	}

	void Open(std::string filename){
		//Set ini filename
		this->lzFilename = filename;
		//Sets IsOpen to bool value
		this->IsOpen = this->ReadIni();
	}
	
	int ReadInteger(const std::string &selection, const std::string key){
		std::string s = selection;
		std::string k = key;
		//Uppercase args
		StrUpper(s);
		StrUpper(k);
		//Return data
		return std::stoi(ini[s][k]);
	}

	std::string ReadString(const std::string selection, const std::string &key){
		std::string s = selection;
		std::string k = key;
		//Uppercase args
		StrUpper(s);
		StrUpper(k);
		//Return data
		return ini[s][k];
	}

	float ReadFloat(const std::string selection, const std::string &key){
		std::string s = selection;
		std::string k = key;
		//Uppercase args
		StrUpper(s);
		StrUpper(k);
		//Return data
		return std::stof(ini[s][k]);
	}
};