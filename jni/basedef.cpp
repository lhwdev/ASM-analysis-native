#ifndef _BASEDEF
#define _BASEDEF



#ifndef __cplusplus
#error ASM module requires 'std=c++11'.
#endif

#include <stdint.h>


#ifndef nullptr
#define nullptr NULL
#endif

#define ASMNS ai
#define ASM_BEGIN_NAMESPACE namespace ASMNS {
#define ASM_END_NAMESPACE }

const class {
} __unsupport;

#define override
#define unsupported { throw __unsupport; }


typedef uint32_t flag_t;
typedef uint8_t byte;

#endif
