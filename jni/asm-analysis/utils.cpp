#ifndef _ASM_UTILS
#define _ASM_UTILS


#include "basedef.cpp"
#include "utils.h"


ASM_BEGIN_NAMESPACE

// StringBuilder

StringBuilder::StringBuilder() 
		: StringBuilder(16) {}

StringBuilder::StringBuilder(size_t capacity)
		: mLen(0),
		mCapacity(capacity),
		mText(new char[capacity]) {}

StringBuilder::StringBuilder(const char* text)
		: mLen(strlen(text)),
		mCapacity(mLen + 1),
		mText(new char[mCapacity]) {
	strcpy(mText, text);
}

StringBuilder::~StringBuilder() {
	delete [] mText;
}


void StringBuilder::ensureCapacity(size_t minCapacity) {
	if(mCapacity < minCapacity) {
		mCapacity = (size_t) ((float) minCapacity * 1.4);
		char* lastText = mText;
		mText = new char[mCapacity];
		memcpy(mText, lastText, mLen + 1);
	}
}

StringBuilder& StringBuilder::append(const char* text, size_t len) {
	if(len == 0)
		return *this;
	
	const size_t newLen = mLen + len;
	ensureCapacity(newLen);
	
	memcpy(mText + mLen, text, len);
	mText[newLen] = '\0';
	mLen = newLen;
	return *this;
}

StringBuilder& StringBuilder::insert(off_t where, const char* text, size_t len) {
	if(len == 0)
		return *this;
	
	const size_t newLen = mLen + len;
	char* start = mText + where;
	char* end = mText + where + len;
	
	ensureCapacity(newLen);
	
	memmove(end, start, mLen - where); // include null char
	memcpy(start, text, len);
	
	mLen = newLen;
	return *this;
}

StringBuilder& StringBuilder::remove(off_t start, off_t end) {
	if(start == end)
		return *this;
	
	memcpy(mText + start, mText + end, mLen - end);
	mLen -= (end - start);
	return *this;
}

ASM_END_NAMESPACE


#endif
