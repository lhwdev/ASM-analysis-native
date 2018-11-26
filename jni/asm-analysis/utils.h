#ifndef _ASM_UTILS_H
#define _ASM_UTILS_H


#include <strings.h>
#include "basedef.cpp"


ASM_BEGIN_NAMESPACE

inline char* newChar(int len) {
	char* text = new char[len + 1];
	text[len] = '\0';
	return text;
}


class StringBuilder
{
	private:
	size_t mLen;
	char* mText; // with null character
	size_t mCapacity;
	
	
	public:
	StringBuilder();
	StringBuilder(size_t capacity);
	StringBuilder(const char* text);
	
	virtual ~StringBuilder();
	
	
	StringBuilder& append(const char* text, size_t len);
	inline StringBuilder& append(const char* text) {
		return append(text, strlen(text));
	}
	
	StringBuilder& insert(off_t where, const char* text, size_t len);
	inline StringBuilder& insert(off_t where, const char* text) {
		return insert(where, text, strlen(text));
	}
	
	StringBuilder& remove(off_t start, off_t end);
	inline void setLength(size_t newlen) {
		mLen = newlen;
	}
	
	void ensureCapacity(size_t minCapacity);
	
	inline char* chars() {
		return mText;
	}
	
	inline size_t length() {
		return mLen;
	}
	
	char charAt(off_t pos) {
		return mText[pos];
	}
	
	StringBuilder& operator+=(const char* text) {
		return append(text);
	}
};


template<typename T>
class iterator
{
	public:
	iterator(T* start, T* end) : mStart(start), mEnd(end) {}
	
	T* start() {
		return mStart;
	}
	
	T* end() {
		return mEnd;
	}
	
	
	private:
	T* mStart;
	T* mEnd;
};


ASM_END_NAMESPACE


#endif
