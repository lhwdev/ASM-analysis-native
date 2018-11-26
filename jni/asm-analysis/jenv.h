#ifndef _ASM_ANALYSIS_ENV_H
#define _ASM_ANALYSIS_ENV_H

#include "basedef.cpp"
#include "jdef-structure.h"


static const jrealptr jinvaildPtr = jrealptr();


ASM_BEGIN_NAMESPACE

using namespace ASMNS::jdef;


class jenv
{
	public:
	// class loading
	jclassptr& loadClass(char* name);
	jclassptr*& peekLoadedClass();
	jclassptr*& loadAllClass();
	iterator<jclassptr&> classes();
	
	jpackage&* getPackages();
	jpackage& getPackage(char* name);
	
};


ASM_END_NAMESPACE


#endif
