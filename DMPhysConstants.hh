/***************************+
 * Maria Martinez 22-02-03hh
 * DMPhysConstants.h
 * Contain some physical constants an another magnitudes
 *****************************/

#ifndef __DMPhysConstants__h__
#define __DMPhysConstants__h__

#define speedOfLight 299792458
#define speedOfLight2 8.987551E16
#define hBarra 1.054571E-34
#define earthSpeed 29.8 // Vel of the earh orbit in km/s
#define earthSpeed2 888.04 // earthSpeed^2

#define RADTODAY 58.0915542 
#define DAYTORAD 0.01721421

#define RADTOYEAR 0.159154943092
#define YEARTORAD 6.283185307179

// Masses in GeV
#define mNucleon 0.9315

// h_ * c in MeV*femto
#define h_c 197.2

// day in seconds
//#define day 86400

// Useful constants
#define PI         3.1415926
#define TWOPI      6.2831853 
#define PI2        9.8696044
#define SQRTPI     1.772454
#define SQRT_3_2   1.22474
#define SQRT_2_3   0.816496581
#define _1_SQRT2PI 0.398942
#define _1_3       0.333333
#define _1_6       0.166667
#define _5_18      0.277778

// Conversion constants in k m s system
// (Not used by now)
//#define femto 1E-15
//#define pico  1E-12
//#define nano  1E-9
//#define micro 1E-6
//#define mili  1E-3
//#define kilo  1E3
//#define mega  1E6
//#define giga  1E9
//#define tera  1E12
#define eV    1.602176E-19
#define keV    1.602176E-16
#define MeV    1.602176E-13
#define GeV    1.602176E-10
#define TeV    1.602176E-7
#define cm    1E-2
#define Km    1E3
#define barn 1E-28

//#define BYTE     char
//#define WORD     unsigned short int
//#define DWORD    unsigned long int
//#define DOUBLE   double

// EARTH ORBIT. UNIT VECTORS
// MARIA 022822. Follow [2105.00599]
#define earthE1_0 -0.0504
#define earthE1_1  0.4946
#define earthE1_2 -0.8677

#define earthE2_0 -0.9941
#define earthE2_1 -0.1088
#define earthE2_2 -0.0042

// Phase of the orbit in years
#define earthT0 0.218 

// SUN PECULIAR VELOCITY (km/s)
#define sunPeculiar_0 11.1
#define sunPeculiar_1 12.2
#define sunPeculiar_2 7.3

#endif
