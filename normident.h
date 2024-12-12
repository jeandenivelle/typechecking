
#ifndef NORMIDENT_
#define NORMIDENT_

#include "identifier.h"
#include "util/normalized.h"

using normident =
   util::normalized< identifier, identifier::hash, identifier::equal_to > ;

#endif

