#include <iostream>
#include "File.h"
#pragma warning(disable : 4996)

File::File() : name(""), content(""), size(0) {}

File::File(const char* name, const char* content, DateTime dateCreated, DateTime lastModification, const char* accessModifiers) :
dateCreated(dateCreated), lastModification(lastModification) {
	setName(name);
	setContent(content);
	setAccessModifiers(accessModifiers);
}

const char* File::getName() const {
	return name;
}

const char* File::getContent() const {
	return content;
}

const char* File::getAccessModifiers() const {
	return accessModifiers;
}

const DateTime& File::getDateCreated() const {
	return dateCreated;
}

const DateTime& File::getLastModification() const {
	return lastModification;
}

unsigned File::getSize() const {
	return size;
}

void File::setContent(const char* content) {
	if(strlen(content) <= contentLen) 
		strcpy(this->content, content);

	size = strlen(content);
}

void File::setLastModification(DateTime& lastModification) {
	this->lastModification = lastModification;
}

void File::setAccessModifiers(const char* accessModifiers) {
	if (strlen(accessModifiers) <= contentLen) 
		strcpy(this->accessModifiers, accessModifiers);
}

void File::setName(const char* name) {
	if (strlen(name) <= contentLen) 
		strcpy(this->name, name);
}

