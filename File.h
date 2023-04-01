#pragma once
#include "DateTime.h"

const unsigned nameLen = 64;
const unsigned contentLen = 512;
const unsigned accessModifiersLen = 9;

class File {
private:
	char name[nameLen + 1];
	char content[contentLen + 1];
	char accessModifiers[accessModifiersLen];
	DateTime dateCreated;
	DateTime lastModification;
	unsigned size;

	void setName(const char* name);

public:
	 File();
	 File(const char* name, const char* content, DateTime dateCreated, DateTime lastModification, const char* accessModifiers);

	 const char* getName() const;
	 const char* getContent() const;
	 const char* getAccessModifiers() const;
	 const DateTime& getDateCreated() const;
	 const DateTime& getLastModification() const;
	 unsigned getSize() const;

	 void setContent(const char* content);
	 void setLastModification(DateTime& lastModification); //Normally this would be a private method that is called by the other setters and use the current time
	//but since the task is to have the time passed from the outside, it will have to be public
	 void setAccessModifiers(const char* accessModifiers);
};