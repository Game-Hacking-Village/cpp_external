#pragma once
#include "std_headers.h"

#include <vector>
using std::vector;

typedef vector<unsigned int> PointerChain;

uintptr_t resolve_pointer_chain(HANDLE proc, uintptr_t base_addr, const PointerChain &chain);