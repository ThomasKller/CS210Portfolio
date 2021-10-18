/*
* Thomas Keller
* 10/11/21
* CSE 210
* Corner Grocer
*/
#include <Python.h>
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <cmath>
#include <string>

using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyRun_SimpleString("import sys");
	PyRun_SimpleString("sys.path.append(\".\")");
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	PyRun_SimpleString("import sys");
	PyRun_SimpleString("sys.path.append(\".\")");
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	PyRun_SimpleString("import sys");
	PyRun_SimpleString("sys.path.append(\".\")");
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}

//Main Menu Function- Displays menu and takes user input then runs appropriate program
void mainMenu()
{
	//neccessary variables to store user and file input 
	unsigned int i = 0;
	int userIn = 0;
	int freq = 0;
	ifstream freqFS;
	string item;

	//stays in menu loop until quit is input
	while (userIn != 4)
	{
		cout << "\t Corner Grocer Items" << endl;
		cout << "1- Item frequencies" << endl;
		cout << "2- Specific item frequency" << endl;
		cout << "3- Histogram of purchased items" << endl;
		cout << "4- Quit" << endl;

		cin >> userIn;

		//uses user input to select function
		switch (userIn) {

		//Prints a list of all items and frequencies
		case 1:
			CallProcedure("PrintAllItems");
			break;

		//Prints a specific item and frequency
		case 2:
			cout << "Which item would you like to search?" << endl;
			cin >> item;
			freq = callIntFunc("FindItem", item);
			cout << "There were " << freq << " " << item << " bought today" << endl;
			break;


		//Prints a Histogram of purchases
		case 3:
			CallProcedure("Histogram");
			freqFS.open("frequency.dat");

			//checks if file is open
			if (!freqFS.is_open()) {
				cout << "Could not open file frequency.dat." << endl;
				break;
			}
			//gets first input
			freqFS >> item;

			
			//reads until nothing is left
			while (!freqFS.fail())
			{
				cout << item << " ";

				freqFS >> freq;
				for (i = 0; i < freq; i++)
				{
					cout << "*";
				}
				cout << endl;
				freqFS >> item;
			}
			
			break;
		// quit case
		case 4:
			break;

		//in case of foriegn entities
		default:
			cout << "Input invalid. Please try again" << endl << endl;
			break;
		}
	}
	
	

}

void main()
{
	mainMenu();
}