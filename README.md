# INIReader
A small class for reading data from INI files.

#Features

- Selections and Key names are no case sensitive.
- Single comments lines only are supported at the moment.
- Can read <b>Integer</b>, <b>Float</b> and <b>Strings</b>
- Only contains one header file making it easy to plug into your applications.

Easy to use example.

```cpp
	TINIRead ini;
  
	//Open ini file.
	ini.Open(argv[1]);

	//Test if ini file was opened.
	if (!ini.IsOpen){
		std::cout << "Faild to open ini file." << std::endl;
		exit(EXIT_FAILURE);
	}
  
	std::cout << ini.ReadString("selection", "key");
```
