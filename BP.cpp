// BP.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

// BP - Boilerplate Project Creator
/*
This C++ Project, creates your own C++ Project with a single command.
*/

#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>

// Turn off _CRT_SECURE_NO_WARNINGS, to not get `unsafe` warning
#pragma warning(disable : 4996)

void printCover();
void createFolder(std::string path);
void createFile(std::string path, std::string content);
std::string getFileContents(std::string path);

int main(int argc, char **argv)
{
	printCover();
	std::string projectName;
	if (argc > 1)
	{
		projectName = argv[1];
	}
	else
	{
		printf("Please enter the name of your project : ");
		std::cin >> projectName;
	}

	// Get current working directory
	char cwd[1024];
	GetCurrentDirectoryA(1024, cwd);
	std::string path = cwd;

	printf("Creating Project %s", projectName.c_str());

	// Create folders
	createFolder(projectName);
	createFolder(projectName + "/src");

	// Create files
	std::string contentMain = "#include <iostream>\n\nint main(int argc, char** argv)\n{\n\tstd::cout << \"Hello World!\" << std::endl;\n\treturn 0;\n}";
	createFile(projectName + "/src/main.cpp", contentMain);

	std::string contentReadMe = "# " + projectName + "\n\nBootstrapped by [BP](https://github.com/FujiwaraChoki/BP/)";
	createFile(projectName + "/README.md", contentReadMe);

	std::string contentGitIgnore = getFileContents("gitignore.txt");
	createFile(projectName + "/.gitignore", contentGitIgnore);

	std::string contentCMakeLists = "cmake_minimum_required(VERSION 3.17)\nproject(" + projectName + ")\n\nset(CMAKE_CXX_STANDARD 20)\n\nadd_executable(" + projectName + " src/main.cpp)";
	createFile(projectName + "/CMakeLists.txt", contentCMakeLists);

	// Done creating files and project Boilerplate
	printf("Project created successfully!\n");
	printf("Press any key to exit...\n");
	std::cin.get();

	// Print cover before program ends
	printCover();

	return 0;
}

void printCover()
{
	// Set background color to black, and text color to purple
	system("Color 05");
	printf("\n**** BP - Boilerplate Project Creator ****\n");
}

void createFolder(std::string path)
{
	// Check if path includes /src
	std::string command;
	if (path.find("src") != std::string::npos)
	{
		// Remove src from path and cd into it, then create src directory
		command = "cd " + path.substr(0, path.find("src")) + " && mkdir src";
	}
	else
	{
		// Create folder
		command = "mkdir " + path;
	}
	system(command.c_str());
}

void createFile(std::string path, std::string content)
{
	std::ofstream file;
	file.open(path);
	file << content;
	file.close();
}

std::string getFileContents(std::string path)
{
	std::ifstream file;
	file.open(path);
	std::string content;
	std::string line;
	while (std::getline(file, line))
	{
		content += line + "\n";
	}
	file.close();
	return content;
}
