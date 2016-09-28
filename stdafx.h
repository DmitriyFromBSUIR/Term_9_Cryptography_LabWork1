// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>



// TODO: reference additional headers your program requires here
#include <iostream>
#include <iomanip>
#include <conio.h>
#include <vector>
#include <map>
#include <algorithm>
#include <bitset>
#include <ctime>
#include <time.h>
#include <fstream>
#include <Windows.h>
#include <malloc.h>
#include <type_traits>
#include <typeinfo>
#include <exception>
#include <string>
#include <tuple>
#include <omp.h>

using namespace std;


#define NOMINMAX	//windows.h -> define min,max

typedef long long int64_t;
typedef unsigned long long uint64_t;
typedef long int32_type;
//typedef unsigned long uint32_t;
typedef short int16_t;
typedef std::tuple< std::string, uint64_t, float, uint64_t, float > stat_row;

class Timer {
	std::string _label;
	int64_t _nano_stamp1;
	int64_t _nano_stamp2;
	int64_t _win_stamp1;
	int64_t _win_stamp2;
public:
	Timer(const char* label) : _label(label), _nano_stamp1(0), _nano_stamp2(0), _win_stamp1(0), _win_stamp2(0) {}
	static uint64_t nano_clock() {
		//rdtsc
		unsigned long int high_part = 0;
		unsigned long int low_part = 0;
		uint64_t time_stamp = 0;
		__asm {
			rdtsc
			mov low_part, eax
			mov high_part, edx
		}
		time_stamp = high_part;
		return (time_stamp <<= 32) |= low_part;
	}
	static uint64_t _nano_clock() { return __rdtsc(); }

	void nano_start() { _nano_stamp1 = __rdtsc(); }
	uint64_t nano_clock_diff() {
		_nano_stamp2 = __rdtsc();
		return	_nano_stamp2 - _nano_stamp1;
	}

	static uint64_t win_clock() {
		LARGE_INTEGER time_stamp;
		QueryPerformanceCounter(&time_stamp);
		return time_stamp.QuadPart;
	}

	void win_start() { _win_stamp1 = win_clock(); }

	uint64_t win_clock_diff() {
		_win_stamp2 = win_clock();
		return _win_stamp2 - _win_stamp1;
	}

	void start() {
		nano_start();
		win_start();
	}
	/*
	stat_row get_stat_row() {
		return std::make_tuple(_label, nano_clock_diff(), 0.0, win_clock_diff(), 0.0);
	}
	*/
	friend ostream& operator << (ostream& s, Timer& t) {
		s << "Time stamp -> nano: " << t.nano_clock_diff() << "  win: " << t.win_clock_diff() << endl;
		return s;
	}
};