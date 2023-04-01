#pragma once
#include "File.h"

enum class SortOptions {
	name,
	creationTime,
	modificationTime,
	size
};

int fileCmp(const File& first, const File& second, SortOptions sortOption);

class FileManager {
private:
	File* files = nullptr;
	unsigned filesLen;
	unsigned numOfFiles = 0;

	void copyFrom(const FileManager& other);
	int getFileIndex(const char* fileName) const;
	void deleteFile(unsigned index);
	unsigned getIndexOfSmallest(unsigned startIndex, SortOptions compareOption) const;

public:
	FileManager() = delete; //we need the length of the files array
	FileManager(unsigned filesLen);
	FileManager(const FileManager& other);
	FileManager& operator=(const FileManager& other);
	//I think it would make more sense to delete the CC and = since it doesnt make much sense to use these operations on a filemanager
	~FileManager();

	void addFile(const char* name, unsigned seconds, unsigned minutes, unsigned hours, unsigned day, unsigned month, unsigned year,
		const char* accessModifiers);

	void editFile(const char* name, const char* content, unsigned seconds, unsigned minutes, unsigned hours, unsigned day, unsigned month, unsigned year,
		char userType);

	void addInFile(const char* name, const char* content, unsigned seconds, unsigned minutes, unsigned hours, unsigned day, unsigned month, unsigned year,
		char userType);

	void deleteFile(const char* name);

	void changeRights(const char* name, char userType, char permission) const;

	void printFileInfo(const char* name) const;

	void printFile(const char* name, char userType) const;

	void print() const;

	void sort(SortOptions sortOption) const;
};





