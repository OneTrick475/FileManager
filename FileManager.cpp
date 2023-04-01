#include "FileManager.h"
#include <iostream>
#pragma warning(disable : 4996)

void FileManager::copyFrom(const FileManager& other) {
	files = new File[other.filesLen];
	filesLen = other.filesLen;
	numOfFiles = other.numOfFiles;

	for(unsigned i = 0; i < numOfFiles; i++) 
		files[i] = other.files[i];
}

int FileManager::getFileIndex(const char* fileName) const {
	for (int i = 0; i < numOfFiles; i++) {
		if (strcmp(fileName, files[i].getName()) == 0)
			return i;
	}
	return -1;
}

FileManager::FileManager(unsigned filesLen) : filesLen(filesLen) {
	files = new File[filesLen];
}

FileManager::FileManager(const FileManager& other) {
	copyFrom(other);
}	

FileManager& FileManager::operator=(const FileManager& other) {
	if (this != &other) {
		delete[] files;
		copyFrom(other);
	}
	return *this;
}

FileManager::~FileManager() {
	delete[] files;
}

void FileManager::addFile(const char* name, unsigned seconds, unsigned minutes, unsigned hours,
	unsigned day, unsigned month, unsigned year, const char* accessModifiers) {

	if(getFileIndex(name) != -1) {
		std::cout << "File already exists\n";
		return;
	}

	if (numOfFiles == filesLen) {
		std::cout << "You've reached the maximum number of files\n";
		return;
	}

	DateTime dateTime(seconds, minutes, hours, day, month, year);

	File file(name, "", dateTime, dateTime, accessModifiers);

	files[numOfFiles++] = file;
}

void FileManager::editFile(const char* name, const char* content, unsigned seconds, unsigned minutes, unsigned hours,
	unsigned day, unsigned month, unsigned year, char userType) {

	int fileIndex = getFileIndex(name);

	if(fileIndex == -1) {
		std::cout << "file does not exist\n";
		return;
	}

	if(userType == 'u') {
		if(files[fileIndex].getAccessModifiers()[1] != 'w') {
			std::cout << "You dont have permission to write in this file\n";
			return;
		}
		files[fileIndex].setContent(content);
	}
	if (userType == 'g') {
		if (files[fileIndex].getAccessModifiers()[4] != 'w') {
			std::cout << "You dont have permission to write in this file\n";
			return;
		}
		files[fileIndex].setContent(content);
	}
	if (userType == 'o') {
		if (files[fileIndex].getAccessModifiers()[7] != 'w') {
			std::cout << "You dont have permission to write in this file\n";
			return;
		}
		files[fileIndex].setContent(content);
	}

	DateTime dateTime(seconds, minutes, hours, day, month, year);

	files[fileIndex].setLastModification(dateTime);
}

void FileManager::addInFile(const char* name, const char* content, unsigned seconds, unsigned minutes, unsigned hours,
	unsigned day, unsigned month, unsigned year, char userType) {

	int fileIndex = getFileIndex(name);

	char newContent[contentLen + 1];

	if(strlen(content) + strlen(files[fileIndex].getContent()) > contentLen) {
		std::cout << "Content cant be longer than: " << contentLen << std::endl;
		return;
	}

	strcpy(newContent, files[fileIndex].getContent());
	//could add a \n here but then we lose the ability to add smth directly after the prev content so it would be better to pass the \n in the parameter str if needed
	strcat(newContent, content);

	if (fileIndex == -1) {
		std::cout << "file does not exist\n";
		return;
	}

	if (userType == 'u') {
		if (files[fileIndex].getAccessModifiers()[1] != 'w') {
			std::cout << "You dont have permission to write in this file\n";
			return;
		}
		files[fileIndex].setContent(newContent);
	}
	if (userType == 'g') {
		if (files[fileIndex].getAccessModifiers()[4] != 'w') {
			std::cout << "You dont have permission to write in this file\n";
			return;
		}
		files[fileIndex].setContent(newContent);
	}
	if (userType == '0') {
		if (files[fileIndex].getAccessModifiers()[7] != 'w') {
			std::cout << "You dont have permission to write in this file\n";
			return;
		}
		files[fileIndex].setContent(newContent);
	}

	DateTime dateTime(seconds, minutes, hours, day, month, year);

	files[fileIndex].setLastModification(dateTime);
}

void FileManager::deleteFile(unsigned index) {
	for (unsigned i = index; i < numOfFiles - 1; i++)
		files[i] = files[i + 1];

	numOfFiles--;
}

unsigned FileManager::getIndexOfSmallest(unsigned startIndex, SortOptions compareOption) const {
	unsigned current = startIndex;

	for (unsigned i = startIndex + 1; i < numOfFiles; i++)
		current = fileCmp( files[current], files[i], compareOption) > 0 ? i : current;

	return current;
}

void FileManager::deleteFile(const char* name) {
	int fileIndex = getFileIndex(name);

	if (fileIndex == -1) {
		std::cout << "file does not exist";
		return;
	}

	deleteFile(fileIndex);
}

void FileManager::changeRights(const char* name, char userType, char permission) const {
	int fileIndex = getFileIndex(name);

	if (fileIndex == -1) {
		std::cout << "file does not exist";
		return;
	}

	char accessModifiers[10];//10 cuz strcpy will add \0
	strcpy(accessModifiers, files[fileIndex].getAccessModifiers());

	if(userType == 'u') {
		if (permission == 'r')
			accessModifiers[0] = accessModifiers[0] == 'r' ? '-' : 'r';
		else if(permission == 'w')
			accessModifiers[1] = accessModifiers[1] == 'w' ? '-' : 'w';
		else if(permission == 'x')
			accessModifiers[2] = accessModifiers[2] == 'x' ? '-' : 'x';
	}
	else if (userType == 'g') {
		if (permission == 'r')
			accessModifiers[3] = accessModifiers[3] == 'r' ? '-' : 'r';
		else if (permission == 'w')
			accessModifiers[4] = accessModifiers[4] == 'w' ? '-' : 'w';
		else if (permission == 'x')
			accessModifiers[5] = accessModifiers[5] == 'x' ? '-' : 'x';
	}
	else if (userType == 'g') {
		if (permission == 'r')
			accessModifiers[6] = accessModifiers[6] == 'r' ? '-' : 'r';
		else if (permission == 'w')
			accessModifiers[7] = accessModifiers[7] == 'w' ? '-' : 'w';
		else if (permission == 'x')
			accessModifiers[8] = accessModifiers[8] == 'x' ? '-' : 'x';
	}

	files[fileIndex].setAccessModifiers(accessModifiers);
}

void FileManager::printFileInfo(const char* name) const {
	int fileIndex = getFileIndex(name);

	if (fileIndex == -1) {
		std::cout << "file does not exist\n";
		return;
	}

	File file = files[fileIndex];

	std::cout << "Name: " << file.getName() << "\nSize: " << file.getSize() << "\nCreated on: ";
	file.getDateCreated().printDateTime(); //we could override the << operator for DateTime but i dont know if we are allowed to
	std::cout << "\nLast modified on: ";
	file.getLastModification().printDateTime();
	std::cout << "\nRights: " << file.getAccessModifiers() << std::endl;
}

void FileManager::printFile(const char* name, char userType) const {
	int fileIndex = getFileIndex(name);

	if (fileIndex == -1) {
		std::cout << "file does not exist\n";
		return;
	}

	if (userType == 'u') {
		if (files[fileIndex].getAccessModifiers()[0] != 'w') {
			std::cout << "You dont have permission to to read this file\n";
			return;
		}
	}
	if (userType == 'g') {
		if (files[fileIndex].getAccessModifiers()[3] != 'w') {
			std::cout << "You dont have permission to read this file\n";
			return;
		}
	}
	if (userType == '0') {
		if (files[fileIndex].getAccessModifiers()[6] != 'w') {
			std::cout << "You dont have permission to read this file\n";
			return;
		}
	}

	std::cout << files[fileIndex].getContent() << '\n';
}

void FileManager::print() const {
	for (unsigned i = 0; i < numOfFiles; i++)
		std::cout << files[i].getName() << std::endl;
}

void FileManager::sort(SortOptions sortOption) const{   // not sure if it should be const. Technically it doesnt modify the object because files is a pointer
														// but this can also be misleading because the actual values in the array are reordered
	//will use selection sort to minimize swaps. Sorting will be in ascending order
	for(unsigned i = 0; i < numOfFiles - 1; i++) {
		unsigned indexOfSmallest = getIndexOfSmallest(i, sortOption);

		if(indexOfSmallest != i) {
			File file = files[i];
			files[i] = files[indexOfSmallest];
			files[indexOfSmallest] = file;
		}
	}
}

int fileCmp(const File& first, const File& second, SortOptions sortOption) {
	if (sortOption == SortOptions::name)
		return strcmp(first.getName(), second.getName());
	if (sortOption == SortOptions::creationTime)
		return first.getDateCreated().dateCompare(second.getDateCreated());
	if (sortOption == SortOptions::modificationTime)
		return first.getLastModification().dateCompare(second.getLastModification());
	if (sortOption == SortOptions::size)
		return first.getSize() > second.getSize();  //in this case if they are equal or second is bigger the result will be the same.
													//this is inconsistent with the other cmp functions but will not be a problem to the sorting algorithm
													//so i will leave it like this for now
	return 0;
}




