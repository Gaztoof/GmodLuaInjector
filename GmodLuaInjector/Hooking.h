#pragma once
#include <Windows.h>
#include <stdint.h>

PVOID VMTHook(PVOID** src, PVOID dst, int index);