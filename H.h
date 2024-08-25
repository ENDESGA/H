/////// /////// /////// /////// /////// /////// ///////
///////
///////    H
///////
/////// (hydrogen) by @ENDESGA 2024 :::. MIT LICENCE

#pragma once
#define INCLUDED_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//

#define OS_LINUX 0
#define OS_WINDOWS 0
#define OS_MACOS 0
#define OS_OTHER 0

#if defined( __WIN32__ ) || defined( WIN32 ) || defined( _WIN32 ) || defined( __CYGWIN__ ) || defined( __MINGW32__ ) || defined( __WINDOWS__ ) || defined( _WIN64 )
	#undef OS_WINDOWS
	#define OS_WINDOWS 1
#elif defined( __LINUX__ ) || defined( linux ) || defined( __linux ) || defined( __linux__ )
	#undef OS_LINUX
	#define OS_LINUX 1
#elif defined( __MACOSX__ ) || defined( __APPLE__ )
	#undef OS_MACOS
	#define OS_MACOS 1
#else
	#undef OS_OTHER
	#define OS_OTHER 1
#endif

#define COMPILER_MSVC 0
#define COMPILER_TCC 0
#define COMPILER_CLANG 0
#define COMPILER_GCC 0
#define COMPILER_UNKNOWN 0

#if defined( _MSC_VER )
	#undef COMPILER_MSVC
	#define COMPILER_MSVC 1
	#define COMPILER_NAME "MSVC"
#elif defined( __TINYC__ )
	#undef COMPILER_TCC
	#define COMPILER_TCC 1
	#define COMPILER_NAME "TCC"
	#define typeof __typeof__
#elif defined( __clang__ )
	#undef COMPILER_CLANG
	#define COMPILER_CLANG 1
	#define COMPILER_NAME "CLANG"
#elif defined( __GNUC__ )
	#undef COMPILER_GCC
	#define COMPILER_GCC 1
	#define COMPILER_NAME "GCC"
#else
	#undef COMPILER_UNKNOWN
	#define COMPILER_UNKNOWN 1
	#define COMPILER_NAME "UNKNOWN"
#endif

//

#if OS_WINDOWS
	#define _CRT_SECURE_NO_WARNINGS
	#undef UNICODE
	#undef _UNICODE
	#define WIN32_LEAN_AND_MEAN
	#define VC_EXTRALEAN
	#define NOGDICAPMASKS
	#if COMPILER_MSVC
		#pragma pack( push, 8 )
	#endif
	#include <windows.h>
	#if COMPILER_MSVC
		#pragma pack( pop )
	#endif
#elif OS_LINUX
	#include <unistd.h>
	#include <pthread.h>
	#include <X11/Xlib.h>
	#include <X11/keysym.h>
	#include <X11/XKBlib.h>
	#include <X11/extensions/XShm.h>
	#include <X11/Xutil.h>
	#include <sys/ipc.h>
	#include <sys/shm.h>
#else
// macOS includes
#endif

//

/////// /////// /////// /////// /////// /////// ///////

//

#define EVAL( ... ) __VA_ARGS__

#define JOIN( a, ... ) a##__VA_ARGS__

#define GET_ARG0( ... )
#define GET_ARG1( a, ... ) a
#define GET_ARG2( a, b, ... ) b
#define GET_ARG3( a, b, c, ... ) c
#define GET_ARG4( a, b, c, d, ... ) d
#define GET_ARG5( a, b, c, d, e, ... ) e
#define GET_ARG6( a, b, c, d, e, f, ... ) f
#define GET_ARG7( a, b, c, d, e, f, g, ... ) g
#define GET_ARG8( a, b, c, d, e, f, g, h, ... ) h
#define GET_ARG9( a, b, c, d, e, f, g, h, i, ... ) i
#define GET_ARG10( a, b, c, d, e, f, g, h, i, j, ... ) j
#define GET_ARG11( a, b, c, d, e, f, g, h, i, j, k, ... ) k
#define GET_ARG12( a, b, c, d, e, f, g, h, i, j, k, l, ... ) l
#define GET_ARG13( a, b, c, d, e, f, g, h, i, j, k, l, m, ... ) m
#define GET_ARG14( a, b, c, d, e, f, g, h, i, j, k, l, m, n, ... ) n
#define GET_ARG15( a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, ... ) o
#define GET_ARG16( a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, ... ) p
#define GET_ARG17( a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, ... ) q

#define SKIP_ARG1( ARG, ... ) __VA_ARGS__

#define COMMA ,
#define COMMA_IF_ARGS( ... ) _COMMA_IF_ARGS( GET_ARG1( __VA_ARGS__ ) )
#define _COMMA_IF_ARGS( ... ) _COMMA_IF_ARGS_EVAL( GET_ARG1 __VA_ARGS__( COMMA ) )
#define _COMMA_IF_ARGS_EVAL( ... ) EVAL( GET_ARG2( __VA_ARGS__, COMMA ) )

#define COUNT_ARGS( ... ) _COUNT_ARGS_EVAL( __VA_ARGS__ COMMA_IF_ARGS( __VA_ARGS__ ) )
#define _COUNT_ARGS_EVAL( ... ) EVAL( GET_ARG17( __VA_ARGS__ 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 ) )

//

#define DEFAULTS( DEFS, ... ) _DEFAULTS_MAKE( COUNT_ARGS DEFS, DEFS, __VA_ARGS__ )
#define _DEFAULTS_MAKE( COUNT, DEFS, ... ) JOIN( _DEFAULTS_, COUNT )( DEFS, __VA_ARGS__ )
#define _DEFAULTS_PARAM( DEFS, ... ) _DEFAULTS_PARAM_EVAL( GET_ARG1 DEFS, _ COMMA_IF_ARGS( __VA_ARGS__ ) __VA_ARGS__ )
#define _DEFAULTS_PARAM_EVAL( DEF, ... ) GET_ARG2( __VA_ARGS__, DEF )
#define _DEFAULTS_0( DEFS, ... )
#define _DEFAULTS_1( DEFS, ... ) _DEFAULTS_PARAM( DEFS, __VA_ARGS__ )
#define _DEFAULTS_2( DEFS, ... ) _DEFAULTS_PARAM( DEFS, __VA_ARGS__ ), _DEFAULTS_1( ( SKIP_ARG1 DEFS ), SKIP_ARG1( __VA_ARGS__ ) )
#define _DEFAULTS_3( DEFS, ... ) _DEFAULTS_PARAM( DEFS, __VA_ARGS__ ), _DEFAULTS_2( ( SKIP_ARG1 DEFS ), SKIP_ARG1( __VA_ARGS__ ) )
#define _DEFAULTS_4( DEFS, ... ) _DEFAULTS_PARAM( DEFS, __VA_ARGS__ ), _DEFAULTS_3( ( SKIP_ARG1 DEFS ), SKIP_ARG1( __VA_ARGS__ ) )
#define _DEFAULTS_5( DEFS, ... ) _DEFAULTS_PARAM( DEFS, __VA_ARGS__ ), _DEFAULTS_4( ( SKIP_ARG1 DEFS ), SKIP_ARG1( __VA_ARGS__ ) )
#define _DEFAULTS_6( DEFS, ... ) _DEFAULTS_PARAM( DEFS, __VA_ARGS__ ), _DEFAULTS_5( ( SKIP_ARG1 DEFS ), SKIP_ARG1( __VA_ARGS__ ) )
#define _DEFAULTS_7( DEFS, ... ) _DEFAULTS_PARAM( DEFS, __VA_ARGS__ ), _DEFAULTS_6( ( SKIP_ARG1 DEFS ), SKIP_ARG1( __VA_ARGS__ ) )
#define _DEFAULTS_8( DEFS, ... ) _DEFAULTS_PARAM( DEFS, __VA_ARGS__ ), _DEFAULTS_7( ( SKIP_ARG1 DEFS ), SKIP_ARG1( __VA_ARGS__ ) )
#define _DEFAULTS_9( DEFS, ... ) _DEFAULTS_PARAM( DEFS, __VA_ARGS__ ), _DEFAULTS_8( ( SKIP_ARG1 DEFS ), SKIP_ARG1( __VA_ARGS__ ) )
#define _DEFAULTS_10( DEFS, ... ) _DEFAULTS_PARAM( DEFS, __VA_ARGS__ ), _DEFAULTS_9( ( SKIP_ARG1 DEFS ), SKIP_ARG1( __VA_ARGS__ ) )
#define _DEFAULTS_11( DEFS, ... ) _DEFAULTS_PARAM( DEFS, __VA_ARGS__ ), _DEFAULTS_10( ( SKIP_ARG1 DEFS ), SKIP_ARG1( __VA_ARGS__ ) )
#define _DEFAULTS_12( DEFS, ... ) _DEFAULTS_PARAM( DEFS, __VA_ARGS__ ), _DEFAULTS_11( ( SKIP_ARG1 DEFS ), SKIP_ARG1( __VA_ARGS__ ) )
#define _DEFAULTS_13( DEFS, ... ) _DEFAULTS_PARAM( DEFS, __VA_ARGS__ ), _DEFAULTS_12( ( SKIP_ARG1 DEFS ), SKIP_ARG1( __VA_ARGS__ ) )
#define _DEFAULTS_14( DEFS, ... ) _DEFAULTS_PARAM( DEFS, __VA_ARGS__ ), _DEFAULTS_13( ( SKIP_ARG1 DEFS ), SKIP_ARG1( __VA_ARGS__ ) )
#define _DEFAULTS_15( DEFS, ... ) _DEFAULTS_PARAM( DEFS, __VA_ARGS__ ), _DEFAULTS_14( ( SKIP_ARG1 DEFS ), SKIP_ARG1( __VA_ARGS__ ) )
#define _DEFAULTS_16( DEFS, ... ) _DEFAULTS_PARAM( DEFS, __VA_ARGS__ ), _DEFAULTS_15( ( SKIP_ARG1 DEFS ), SKIP_ARG1( __VA_ARGS__ ) )

//

#define SYMBOL_CHAIN( BEFORE, MIDDLE, AFTER, ... ) _SYMBOL_MAKE( COUNT_ARGS( __VA_ARGS__ ) )( BEFORE, MIDDLE, AFTER, __VA_ARGS__ )
#define _SYMBOL_MAKE( COUNT ) JOIN( _SYMBOL_, COUNT )
#define _JOIN_SYMBOL( BEFORE, MIDDLE, AFTER, A, B ) _SYMBOL_1( BEFORE, MIDDLE, AFTER, A ) MIDDLE B
#define _SYMBOL_0( BEFORE, MIDDLE, AFTER, ... ) __VA_ARGS__
#define _SYMBOL_1( BEFORE, MIDDLE, AFTER, A ) BEFORE( A ) AFTER
#define _SYMBOL_2( BEFORE, MIDDLE, AFTER, A, ... ) _JOIN_SYMBOL( BEFORE, MIDDLE, AFTER, A, _SYMBOL_1( BEFORE, MIDDLE, AFTER, __VA_ARGS__ ) )
#define _SYMBOL_3( BEFORE, MIDDLE, AFTER, A, ... ) _JOIN_SYMBOL( BEFORE, MIDDLE, AFTER, A, _SYMBOL_2( BEFORE, MIDDLE, AFTER, __VA_ARGS__ ) )
#define _SYMBOL_4( BEFORE, MIDDLE, AFTER, A, ... ) _JOIN_SYMBOL( BEFORE, MIDDLE, AFTER, A, _SYMBOL_3( BEFORE, MIDDLE, AFTER, __VA_ARGS__ ) )
#define _SYMBOL_5( BEFORE, MIDDLE, AFTER, A, ... ) _JOIN_SYMBOL( BEFORE, MIDDLE, AFTER, A, _SYMBOL_4( BEFORE, MIDDLE, AFTER, __VA_ARGS__ ) )
#define _SYMBOL_6( BEFORE, MIDDLE, AFTER, A, ... ) _JOIN_SYMBOL( BEFORE, MIDDLE, AFTER, A, _SYMBOL_5( BEFORE, MIDDLE, AFTER, __VA_ARGS__ ) )
#define _SYMBOL_7( BEFORE, MIDDLE, AFTER, A, ... ) _JOIN_SYMBOL( BEFORE, MIDDLE, AFTER, A, _SYMBOL_6( BEFORE, MIDDLE, AFTER, __VA_ARGS__ ) )
#define _SYMBOL_8( BEFORE, MIDDLE, AFTER, A, ... ) _JOIN_SYMBOL( BEFORE, MIDDLE, AFTER, A, _SYMBOL_7( BEFORE, MIDDLE, AFTER, __VA_ARGS__ ) )
#define _SYMBOL_9( BEFORE, MIDDLE, AFTER, A, ... ) _JOIN_SYMBOL( BEFORE, MIDDLE, AFTER, A, _SYMBOL_8( BEFORE, MIDDLE, AFTER, __VA_ARGS__ ) )
#define _SYMBOL_10( BEFORE, MIDDLE, AFTER, A, ... ) _JOIN_SYMBOL( BEFORE, MIDDLE, AFTER, A, _SYMBOL_9( BEFORE, MIDDLE, AFTER, __VA_ARGS__ ) )
#define _SYMBOL_11( BEFORE, MIDDLE, AFTER, A, ... ) _JOIN_SYMBOL( BEFORE, MIDDLE, AFTER, A, _SYMBOL_10( BEFORE, MIDDLE, AFTER, __VA_ARGS__ ) )
#define _SYMBOL_12( BEFORE, MIDDLE, AFTER, A, ... ) _JOIN_SYMBOL( BEFORE, MIDDLE, AFTER, A, _SYMBOL_11( BEFORE, MIDDLE, AFTER, __VA_ARGS__ ) )
#define _SYMBOL_13( BEFORE, MIDDLE, AFTER, A, ... ) _JOIN_SYMBOL( BEFORE, MIDDLE, AFTER, A, _SYMBOL_12( BEFORE, MIDDLE, AFTER, __VA_ARGS__ ) )
#define _SYMBOL_14( BEFORE, MIDDLE, AFTER, A, ... ) _JOIN_SYMBOL( BEFORE, MIDDLE, AFTER, A, _SYMBOL_13( BEFORE, MIDDLE, AFTER, __VA_ARGS__ ) )
#define _SYMBOL_15( BEFORE, MIDDLE, AFTER, A, ... ) _JOIN_SYMBOL( BEFORE, MIDDLE, AFTER, A, _SYMBOL_14( BEFORE, MIDDLE, AFTER, __VA_ARGS__ ) )
#define _SYMBOL_16( BEFORE, MIDDLE, AFTER, A, ... ) _JOIN_SYMBOL( BEFORE, MIDDLE, AFTER, A, _SYMBOL_15( BEFORE, MIDDLE, AFTER, __VA_ARGS__ ) )

//

/////// /////// /////// /////// /////// /////// ///////

//

#undef near
#undef far
#undef min
#undef max

#define _require_semicolon \
	do { \
	} while( 0 )

//

#define ref *const __restrict
#define mutable_ref *

#define ref_of( ... ) ( &__VA_ARGS__ )
#define val_of( ... ) ( *__VA_ARGS__ )
#define size_of( ... ) to_u4( sizeof( __VA_ARGS__ ) )
#define type_of( ... ) typeof( __VA_ARGS__ )

#define type_from( ... ) typedef __VA_ARGS__

#define to( TYPE, ... ) ( TYPE )( __VA_ARGS__ )
#define cast( TYPE, ... ) val_of( to( TYPE mutable_ref, ref_of( __VA_ARGS__ ) ) )

#define set_ref( REF, NEW_REF ) cast( type_of( val_of( REF ) ) mutable_ref, REF ) = NEW_REF
#define set_new_ref( REF, ... ) cast( type_of( val_of( REF ) ) mutable_ref, REF ) = new_ref( type_of( val_of( REF ) ), __VA_ARGS__ )

#define temp register
#define perm static

#define embed perm inline
#define fn embed void
#define global perm
#define in const
#define out return

#define fn_ref( OUTPUT, NAME, ... ) OUTPUT val_of( NAME )( __VA_ARGS__ )
#define fn_type( OUTPUT, ... ) type_from( type_of( fn_ref( DEFAULTS( ( byte ), OUTPUT ), , __VA_ARGS__ ) ) )

#define fn_type_from( FN ) type_from( type_of( FN ) )

#define pick( IF_YES, THEN_THIS, ELSE_THIS ) ( ( IF_YES ) ? ( THEN_THIS ) : ( ELSE_THIS ) )

#define print( ... ) printf( __VA_ARGS__ )

//

#define not !
#define and &&
#define or ||
#define xor ^
#define mod %

#define is ==
#define isnt !=

//

#define null to( void ref, 0 )
#define print_ref( ... ) print( "%p", to( void ref, __VA_ARGS__ ) )

type_from( char ) byte;
#define to_byte( ... ) to_u1( __VA_ARGS__ )
#define byte_size( ... ) u1_size( __VA_ARGS__ )
#define byte_min u1_min
#define byte_max u1_max
#define print_byte( ... ) print_u1( __VA_ARGS__ )

//

#define MIN( A, B ) pick( ( A ) < ( B ), A, B )
#define MIN3( A, B, C ) MIN( A, MIN( B, C ) )
#define MIN4( A, B, C, D ) MIN3( A, B, MIN( C, D ) )
#define MIN5( A, B, C, D, E ) MIN4( A, B, C, MIN( D, E ) )

#define MAX( A, B ) pick( ( A ) > ( B ), A, B )
#define MAX3( A, B, C ) MAX( A, MAX( B, C ) )
#define MAX4( A, B, C, D ) MAX3( A, B, MAX( C, D ) )
#define MAX5( A, B, C, D, E ) MAX4( A, B, C, MAX( D, E ) )

#define MEDIAN( A, B, C ) pick( ( A ) > ( B ), pick( ( B ) > ( C ), B, MIN( A, C ) ), pick( ( A ) > ( C ), A, MIN( B, C ) ) )
#define MEDIAN4( A, B, C, D ) ( ( ( MIN( MAX( A, B ), MAX( C, D ) ) + MAX( MIN( A, B ), MIN( C, D ) ) ) ) / 2 )
#define MEDIAN4_BITWISE( A, B, C, D ) ( ( ( MIN( MAX( A, B ), MAX( C, D ) ) + MAX( MIN( A, B ), MIN( C, D ) ) ) ) >> 1 )
#define MEDIAN5( A, B, C, D, E ) ( ( A + B + C + D + E - MIN5( A, B, C, D, E ) - MAX5( A, B, C, D, E ) ) / 3 )

#define AVG( A, B ) ( ( ( A ) + ( B ) ) / 2 )
#define AVG_BITWISE( A, B ) ( ( ( A ) + ( B ) ) >> 1 )
#define AVG3( A, B, C ) ( ( ( A ) + ( B ) + ( C ) ) / 3 )
#define AVG4( A, B, C, D ) ( ( ( A ) + ( B ) + ( C ) + ( D ) ) / 4 )
#define AVG4_BITWISE( A, B, C, D ) ( ( ( A ) + ( B ) + ( C ) + ( D ) ) >> 2 )

#define CLAMP( V, MINIMUM, MAXIMUM ) MIN( MAX( ( V ), ( MINIMUM ) ), ( MAXIMUM ) )
#define SATURATE( V ) CLAMP( V, 0, 1 )
#define SQR( V ) ( ( V ) * ( V ) )
#define ABS( V ) pick( ( V ) < 0, -( V ), V )
#define SIGN( V ) pick( ( V ) >= 0, 1, -1 )
#define SIGN_ZERO( V ) pick( ( V ) > 0, 1, pick( ( V ) < 0, -1, 0 ) )
#define SNAP( V, MULTIPLES_OF ) ( ( V ) / ( MULTIPLES_OF ) ) * ( MULTIPLES_OF )
#define SNAP_f( N, V, MULTIPLES_OF ) trunc_f##N( ( V ) / ( MULTIPLES_OF ) ) * ( MULTIPLES_OF )
#define SNAP_BIT( V, BIT ) ( ( ( V ) >> ( BIT ) ) << ( BIT ) )

#define MIX( A, B, AMOUNT ) ( ( A ) + ( AMOUNT ) * ( ( B ) - ( A ) ) )
#define MAP( V, A, B, C, D ) ( ( V ) - ( A ) ) * ( ( D ) - ( C ) ) / ( ( B ) - ( A ) ) + ( C )
#define RANGE( V, LOWER, UPPER ) ( ( V - ( LOWER ) ) / ( ( UPPER ) - ( LOWER ) ) )

#define TRUNC_f( N, ... ) to_f##N( to_s##N( __VA_ARGS__ ) )
#define FLOOR_f( N, ... ) pick( __VA_ARGS__ >= 0, TRUNC_f( N, __VA_ARGS__ ), to_f##N( to_s##N( __VA_ARGS__ ) - 1 ) )
#define ROUND_f( N, ... ) TRUNC_f( N, __VA_ARGS__ + pick( __VA_ARGS__ >= 0, .5, -.5 ) )
#define CEIL_f( N, ... ) pick( __VA_ARGS__ > 0, to_f##N( to_s##N( __VA_ARGS__ ) + 1 ), TRUNC_f( N, __VA_ARGS__ ) )
#define MOD_f( N, V, MODULO ) ( ( V ) - ( MODULO ) * floor_f##N( ( V ) / ( MODULO ) ) )

//

#define expect_val( TYPE, VALUE, EXPECTED ) \
	do { \
		if( VALUE is EXPECTED ) skip; \
		print( "%s :: EXPECTED: %s", #VALUE, #EXPECTED ); \
		print( ", got: " ); \
		print_##TYPE( VALUE ); \
		print( "\n" ); \
	} while( 0 )

#define FUNCTION_GROUP_BASE( T, N ) \
	embed T##N min_##T##N( in T##N a, in T##N b ) { out MIN( a, b ); } \
	embed T##N min3_##T##N( in T##N a, in T##N b, in T##N c ) { out MIN3( a, b, c ); } \
	embed T##N min4_##T##N( in T##N a, in T##N b, in T##N c, in T##N d ) { out MIN4( a, b, c, d ); } \
	embed T##N min5_##T##N( in T##N a, in T##N b, in T##N c, in T##N d, in T##N e ) { out MIN5( a, b, c, d, e ); } \
	embed T##N max_##T##N( in T##N a, in T##N b ) { out MAX( a, b ); } \
	embed T##N max3_##T##N( in T##N a, in T##N b, in T##N c ) { out MAX3( a, b, c ); } \
	embed T##N max4_##T##N( in T##N a, in T##N b, in T##N c, in T##N d ) { out MAX4( a, b, c, d ); } \
	embed T##N max5_##T##N( in T##N a, in T##N b, in T##N c, in T##N d, in T##N e ) { out MAX5( a, b, c, d, e ); } \
	embed T##N median_##T##N( in T##N a, in T##N b, in T##N c ) { out MEDIAN( a, b, c ); } \
	embed T##N median5_##T##N( in T##N a, in T##N b, in T##N c, in T##N d, in T##N e ) { out MEDIAN5( a, b, c, d, e ); } \
	embed T##N avg3_##T##N( in T##N a, in T##N b, in T##N c ) { out AVG3( a, b, c ); } \
	embed T##N clamp_##T##N( in T##N v, in T##N min, in T##N max ) { out CLAMP( v, min, max ); } \
	embed T##N saturate_##T##N( in T##N v ) { out SATURATE( v ); } \
	embed T##N sqr_##T##N( in T##N v ) { out SQR( v ); }

#define FUNCTION_GROUP_BASE_US( US, N ) \
	embed US##N median4_##US##N( in US##N a, in US##N b, in US##N c, in US##N d ) { out MEDIAN4_BITWISE( a, b, c, d ); } \
	embed US##N avg_##US##N( in US##N a, in US##N b ) { out AVG_BITWISE( a, b ); } \
	embed US##N avg4_##US##N( in US##N a, in US##N b, in US##N c, in US##N d ) { out AVG4_BITWISE( a, b, c, d ); } \
	embed US##N snap_##US##N( in US##N v, in US##N multiples_of ) { out SNAP( v, multiples_of ); } \
	embed US##N snap_bit_##US##N( in US##N v, in US##N bit ) { out SNAP_BIT( v, bit ); }

#define FUNCTION_GROUP_U( N ) \
	FUNCTION_GROUP_BASE( u, N ) \
	FUNCTION_GROUP_BASE_US( u, N )

#define FUNCTION_GROUP_S( N ) \
	FUNCTION_GROUP_BASE( s, N ) \
	FUNCTION_GROUP_BASE_US( s, N ) \
	embed s##N abs_s##N( in s##N v ) { out ABS( v ); } \
	embed s##N sign_s##N( in s##N v ) { out SIGN( v ); } \
	embed s##N sign_zero_s##N( in s##N v ) { out SIGN_ZERO( v ); }

#define FUNCTION_GROUP_F( N ) \
	FUNCTION_GROUP_BASE( f, N ) \
	embed f##N trunc_f##N( in f##N v ) { out TRUNC_f( N, v ); } \
	embed f##N floor_f##N( in f##N v ) { out FLOOR_f( N, v ); } \
	embed f##N round_f##N( in f##N v ) { out ROUND_f( N, v ); } \
	embed f##N ceil_f##N( in f##N v ) { out CEIL_f( N, v ); } \
	embed f##N mod_f##N( in f##N v, in f##N m ) { out MOD_f( N, v, m ); } \
	embed f##N median4_f##N( in f##N a, in f##N b, in f##N c, in f##N d ) { out MEDIAN4( a, b, c, d ); } \
	embed f##N avg_f##N( in f##N a, in f##N b ) { out AVG( a, b ); } \
	embed f##N avg4_f##N( in f##N a, in f##N b, in f##N c, in f##N d ) { out AVG4( a, b, c, d ); } \
	embed f##N abs_f##N( in f##N v ) { out ABS( v ); } \
	embed f##N sign_f##N( in f##N v ) { out SIGN( v ); } \
	embed f##N sign_zero_f##N( in f##N v ) { out SIGN_ZERO( v ); } \
	embed f##N snap_f##N( in f##N v, in f##N multiples_of ) { out SNAP_f( N, v, multiples_of ); } \
	embed f##N mix_f##N( in f##N a, in f##N b, in f##N amount ) { out MIX( a, b, amount ); } \
	embed f##N map_f##N( in f##N v, in f##N from_lower, in f##N from_upper, in f##N to_lower, in f##N to_upper ) { out MAP( v, from_lower, from_upper, to_lower, to_upper ); } \
	embed f##N range_f##N( in f##N v, in f##N lower, in f##N upper ) { out RANGE( v, lower, upper ); }

//

// 1 byte
type_from( byte ) u1;
#define to_u1( ... ) to( u1, __VA_ARGS__ )
#define u1_size ( size_of( u1 ) )
#define u1_min ( 0 )
#define u1_max ( 255 )
#define print_u1( ... ) print( "%u", to_u1( __VA_ARGS__ ) )
FUNCTION_GROUP_U( 1 )

type_from( signed char ) s1;
#define to_s1( ... ) to( s1, __VA_ARGS__ )
#define s1_size ( size_of( s1 ) )
#define s1_min ( -128 )
#define s1_max ( 127 )
#define print_s1( ... ) print( "%hhd", to_s1( __VA_ARGS__ ) )
FUNCTION_GROUP_S( 1 )

// 2 bytes
type_from( unsigned short ) u2;
#define to_u2( ... ) to( u2, __VA_ARGS__ )
#define u2_size ( size_of( u2 ) )
#define u2_min ( 0U )
#define u2_max ( 65535U )
#define print_u2( ... ) print( "%hu", to_u2( __VA_ARGS__ ) )
FUNCTION_GROUP_U( 2 )

type_from( signed short ) s2;
#define to_s2( ... ) to( s2, __VA_ARGS__ )
#define s2_size ( size_of( s2 ) )
#define s2_min ( -32768 )
#define s2_max ( 32767 )
#define print_s2( ... ) print( "%hd", to_s2( __VA_ARGS__ ) )
FUNCTION_GROUP_S( 2 )

// 4 bytes
type_from( unsigned int ) u4;
#define to_u4( ... ) to( u4, __VA_ARGS__ )
#define u4_size ( size_of( u4 ) )
#define u4_min ( 0U )
#define u4_max ( 4294967295U )
#define print_u4( ... ) print( "%u", to_u4( __VA_ARGS__ ) )
FUNCTION_GROUP_U( 4 )

type_from( signed int ) s4;
#define to_s4( ... ) to( s4, __VA_ARGS__ )
#define s4_size ( size_of( s4 ) )
#define s4_min ( -2147483648 )
#define s4_max ( 2147483647 )
#define print_s4( ... ) print( "%d", to_s4( __VA_ARGS__ ) )
FUNCTION_GROUP_S( 4 )

type_from( float ) f4;
#define to_f4( ... ) to( f4, __VA_ARGS__ )
#define f4_size ( size_of( f4 ) )
#define f4_min ( 1.175494351e-38f )
#define f4_max ( 3.402823466e+38f )
#define print_f4( ... ) print( "%f", to_f4( __VA_ARGS__ ) )
FUNCTION_GROUP_F( 4 )

// 8 bytes
type_from( unsigned long long ) u8;
#define to_u8( ... ) to( u8, __VA_ARGS__ )
#define u8_size ( size_of( u8 ) )
#define u8_min ( 0ULL )
#define u8_max ( 18446744073709551615ULL )
#define print_u8( ... ) print( "%llu", to_u8( __VA_ARGS__ ) )
FUNCTION_GROUP_U( 8 )

type_from( signed long long ) s8;
#define to_s8( ... ) to( s8, __VA_ARGS__ )
#define s8_size ( size_of( s8 ) )
#define s8_min ( to_s8( -9223372036854775808LL ) )
#define s8_max ( to_s8( 9223372036854775807LL ) )
#define print_s8( ... ) print( "%lld", to_s8( __VA_ARGS__ ) )
FUNCTION_GROUP_S( 8 )

type_from( double ) f8;
#define to_f8( ... ) to( f8, __VA_ARGS__ )
#define f8_size ( size_of( f8 ) )
#define f8_min ( 2.2250738585072014e-308 )
#define f8_max ( 1.7976931348623158e+308 )
#define print_f8( ... ) print( "%.16lf", to_f8( __VA_ARGS__ ) )
FUNCTION_GROUP_F( 8 )

//

type_from( s1 ) flag;
#define to_flag( ... ) ( to_s1( !!( __VA_ARGS__ ) ) )
#define flag_size ( size_of( flag ) )
#define print_flag( ... ) print_s1( __VA_ARGS__ )

#define yes 1
#define maybe -1
#define no 0

//

#define loop while( yes )

#define if_all( ... ) if( SYMBOL_CHAIN(, and, , __VA_ARGS__ ) )
#define if_any( ... ) if( SYMBOL_CHAIN(, or, , __VA_ARGS__ ) )
#define if_not_all( ... ) if( SYMBOL_CHAIN( not, and, , __VA_ARGS__ ) )
#define if_not_any( ... ) if( SYMBOL_CHAIN( not, or, , __VA_ARGS__ ) )
#define if_null( ... ) if( SYMBOL_CHAIN(, and, is null, __VA_ARGS__ ) )
#define if_not_null( ... ) if( SYMBOL_CHAIN(, and, isnt null, __VA_ARGS__ ) )
#define if_zero( ... ) if( SYMBOL_CHAIN(, and, is 0, __VA_ARGS__ ) )

#define elif( ... ) else if( __VA_ARGS__ )

#define while_any( ... ) while( SYMBOL_CHAIN(, or, , __VA_ARGS__ ) )
#define while_not( ... ) while( SYMBOL_CHAIN( not, and, , __VA_ARGS__ ) )
#define while_null( ... ) while( SYMBOL_CHAIN(, and, is null, __VA_ARGS__ ) )
#define while_not_null( ... ) while( SYMBOL_CHAIN(, and, isnt null, __VA_ARGS__ ) )
#define while( ... ) while( SYMBOL_CHAIN(, and, , __VA_ARGS__ ) )
#define elwhile( ... ) else while( __VA_ARGS__ )

//

#define leave break
#define skip continue

#define select( ... ) switch( __VA_ARGS__ )
#define with( ... ) SYMBOL_CHAIN( case, , :, __VA_ARGS__ )
#define with_other default:

//

#if COMPILER_MSVC
	#define PACKED
#else
	#define PACKED __attribute__( ( packed ) )
#endif

#define _struct( NAME, ... ) \
	type_from( struct PACKED NAME __VA_ARGS__ ) NAME; \
	struct PACKED NAME

#define struct( ... ) _struct( __VA_ARGS__ )
#define object( ... ) _struct( __VA_ARGS__, mutable_ref )

#define make( STRUCT, ... ) ( ( STRUCT ){ __VA_ARGS__ } )

#define enum( ... ) \
	type_from( enum __VA_ARGS__ ) __VA_ARGS__; \
	enum __VA_ARGS__

#define enum_ref( ... ) \
	type_from( enum __VA_ARGS__ ref ) __VA_ARGS__; \
	enum __VA_ARGS__

//

fn _expect( in byte ref got, in byte ref condition, in s4 line, in byte ref file )
{
	print( "%s EXPECTED \"%s\" in file: %s, at line %d\n", got, condition, file, line );
}
#define expect( ... ) if_not_all( __VA_ARGS__ ) _expect( to( byte ref, "" ), to( byte ref, #__VA_ARGS__ ), __LINE__, to( byte ref, __FILE__ ) )

//

#define _iter( VAR_NAME, SIZE, COUNTER ) \
	temp const s4 JOIN( _TO_, COUNTER ) = ( SIZE ); \
	if( JOIN( _TO_, COUNTER ) ) \
		for( temp s4 VAR_NAME = 0; VAR_NAME < JOIN( _TO_, COUNTER ); ++VAR_NAME )
#define iter( VAR_NAME, SIZE ) _iter( VAR_NAME, SIZE, __COUNTER__ )

#define _repeat( COUNTER, N_TIMES ) iter( JOIN( _REP_, COUNTER ), N_TIMES )
#define repeat( N_TIMES ) _repeat( __COUNTER__, N_TIMES )

//

/////// /////// /////// /////// /////// /////// ///////

//

#define copy_bytes( FROM, BYTES_SIZE, TO ) memcpy( TO, FROM, BYTES_SIZE )
#define move_bytes( FROM, BYTES_SIZE, TO ) memmove( TO, FROM, BYTES_SIZE )
#define clear_bytes( REF, BYTES_SIZE ) memset( REF, 0, BYTES_SIZE )
#define compare_bytes( A, B, BYTES_SIZE ) memcmp( A, B, BYTES_SIZE )

//

embed byte ref _construct_ref( in u4 type_size, in u8 size, in byte ref default_bytes )
{
	temp byte ref out_ref = to( byte ref, calloc( size, type_size ) );

	if( default_bytes isnt null ) copy_bytes( default_bytes, size * type_size, out_ref );

	out out_ref;
}
#define new_ref( TYPE, ... ) _new_ref_make( TYPE, DEFAULTS( ( 1, 0 ), __VA_ARGS__ ) )
#define new_object( TYPE, ... ) _new_ref_make( struct TYPE, DEFAULTS( ( 1, 0 ), __VA_ARGS__ ) )
#define _new_ref_make( TYPE, ... ) EVAL( _new_ref( TYPE, __VA_ARGS__ ) )
#define _new_ref( TYPE, SIZE, DEF ) ( to( TYPE ref, _construct_ref( size_of( TYPE ), SIZE, to( const byte ref, DEF ) ) ) )

#define measure_ref( ... ) strlen( to( const char mutable_ref, __VA_ARGS__ ) )

embed byte ref _resize_ref( in byte ref this_ref, in u8 in_new_size, in u8 in_type_size, in u8 in_old_size )
{
	temp const u8 old_size = in_old_size * in_type_size;
	temp const u8 new_size = in_new_size * in_type_size;

	temp byte ref out_ref = realloc( to( byte mutable_ref, this_ref ), new_size );

	if( new_size > old_size )
	{
		temp byte ref check_ptr = out_ref + old_size;
		temp const u8 check_size = new_size - old_size;
		temp u8 i = 0;
		repeat( check_size ) if( check_ptr[ i++ ] ) leave;

		if( i <= check_size )
			clear_bytes( check_ptr, check_size );
	}

	out out_ref;
}
#define resize_ref( REF, TYPE, OLD_SIZE, NEW_SIZE ) to( TYPE ref, _resize_ref( to( byte ref, REF ), NEW_SIZE, size_of( TYPE ), OLD_SIZE ) )

#define delete_ref( REF ) if_not_null( REF ) free( REF )

//

struct( canvas )
{
	byte mutable_ref data;
	u2 width;
	u2 height;
};

embed canvas new_canvas( in u2 width, in u2 height, in u1 bytes_per_pixel )
{
	out make( canvas, .data = new_ref( byte, ( width * height ) * bytes_per_pixel ), .width = width, .height = height );
}

struct( rgba2 )
{
	byte rg;
	byte ba;
};

struct( rgb3 )
{
	byte b;
	byte g;
	byte r;
};

struct( rgba4 )
{
	byte b;
	byte g;
	byte r;
	byte a;
};

//

object( list )
{
	byte ref bytes;
	u4 size;
	u4 capacity;
	u2 type_size;
};

embed list construct_list( in u4 size, in u4 capacity, in u4 type_size, byte ref bytes )
{
	list out_list = new_object( list );
	//
	set_ref( out_list->bytes, bytes );
	out_list->size = size;
	out_list->capacity = pick( capacity <= size, size + 1, capacity );
	out_list->type_size = type_size;
	//
	out out_list;
}

#define new_list_bytes_size( TYPE, SIZE, BYTES, BYTES_SIZE ) construct_list( SIZE, BYTES_SIZE, size_of( TYPE ), to( byte ref, BYTES ) )
#define new_list( TYPE, ... ) new_list_bytes_size( TYPE, 0, new_ref( TYPE, DEFAULTS( ( 1, null ), __VA_ARGS__ ) ), 1 )

fn delete_list( list in_list )
{
	if_null( in_list ) out;
	delete_ref( in_list->bytes );
	free( in_list );
}

embed list grow_list( in list this_list )
{
	if( this_list->capacity > this_list->size + 1 ) out this_list;
	temp u4 old_size = this_list->capacity;
	do {
		this_list->capacity = ( this_list->capacity + ( this_list->size << 1 ) + 1 ) >> 1;
	} while( this_list->capacity <= this_list->size );

	val_of( to( byte mutable_ref ref, ref_of( this_list->bytes ) ) ) = resize_ref(
		this_list->bytes,
		byte,
		old_size * this_list->type_size,
		this_list->capacity * this_list->type_size
	);

	out this_list;
}

embed list resize_list( in list this_list, in u4 in_size )
{
	this_list->size = in_size;
	grow_list( this_list );
	out this_list;
}

#define list_set( LIST, POS, VAL ) ( to( type_of( VAL ) ref, LIST->bytes ) )[ ( POS ) ] = ( VAL )
#define list_set_ref( LIST, POS, REF ) ( to( type_of( ref_of( val_of( VAL ) ) ) mutable_ref, LIST->bytes ) )[ ( POS ) ] = ( VAL )
#define list_get( LIST, TYPE, POS ) ( ( to( TYPE ref, LIST->bytes ) )[ ( POS ) ] )

#define empty_list( LIST, TYPE ) \
	LIST->size = 0; \
	list_set( LIST, 0, make( TYPE, 0 ) )

embed list list_move( in list this_list, in u4 in_pos, in u4 in_size, in s4 in_amount )
{
	move_bytes( this_list->bytes + ( in_pos * this_list->type_size ), in_size * this_list->type_size, this_list->bytes + ( ( in_pos + in_amount ) * this_list->type_size ) );
	out this_list;
}

embed list copy_list( in list from_list, in list to_list, in u4 at_pos )
{
	copy_bytes( from_list->bytes, from_list->size * from_list->type_size, to_list->bytes + ( at_pos * to_list->type_size ) );
	out to_list;
}

#define list_add( LIST, VAL ) \
	grow_list( LIST ); \
	list_set( LIST, LIST->size++, VAL )

#define list_insert( LIST, POS, VAL ) \
	grow_list( LIST ); \
	list_move( LIST, ( POS ), ( LIST->size++ ) - ( POS ), 1 ); \
	list_set( LIST, POS, VAL )

embed list list_add_bytes_size( in list this_list, byte ref in_bytes, in u4 in_size )
{
	temp const u4 old_size = this_list->size;
	resize_list( this_list, this_list->size + in_size );
	copy_bytes( in_bytes, in_size, this_list->bytes + ( old_size * this_list->type_size ) );
	out this_list;
}
#define list_add_bytes( LIST, BYTES ) list_add_bytes_size( LIST, to( byte ref, BYTES ), measure_ref( BYTES ) )

embed list list_insert_bytes_size( in list this_list, in u4 in_pos, byte ref in_bytes, in u4 in_size )
{
	temp const u4 old_size = this_list->size;
	temp const u4 pos = CLAMP( in_pos, 0, old_size );
	resize_list( this_list, this_list->size + in_size );
	list_move( this_list, pos, old_size - pos, to_s4( in_size ) );
	copy_bytes( in_bytes, in_size, this_list->bytes + ( pos * this_list->type_size ) );
	out this_list;
}
#define list_insert_bytes( LIST, POS, BYTES ) list_insert_bytes_size( LIST, POS, to( byte ref, BYTES ), measure_ref( BYTES ) )

embed list list_add_list( in list this_list, in list in_other )
{
	temp const u4 old_size = this_list->size;
	resize_list( this_list, this_list->size + in_other->size );
	copy_list( in_other, this_list, old_size );
	out this_list;
}

embed list list_insert_list( in list this_list, in u4 in_pos, in list in_other )
{
	temp const u4 old_size = this_list->size;
	temp const u4 pos = CLAMP( in_pos, 0, old_size );
	resize_list( this_list, this_list->size + in_other->size );
	list_move( this_list, pos, old_size - pos, to_s4( in_other->size ) );
	copy_list( in_other, this_list, pos );
	out this_list;
}

embed list list_replace_list( in list this_list, in u4 in_pos, in u4 in_size, in list in_other )
{
	temp const u4 old_size = this_list->size;
	temp const u4 pos = in_pos + in_size;
	resize_list( this_list, this_list->size - in_size + in_other->size );
	list_move( this_list, pos, old_size - pos, to_s4( this_list->size ) - old_size );
	copy_list( in_other, this_list, in_pos );
	out this_list;
}

#define list_delete( LIST, POS ) list_move( LIST, ( POS ) + 1, ( LIST->size-- ) - ( ( POS ) + 1 ), -1 )

#define list_remove_first( LIST, TYPE ) \
	list_get( LIST, TYPE, 0 ); \
	copy_bytes( LIST->bytes + LIST->type_size, ( --LIST->size ) * LIST->type_size, LIST->bytes )

#define list_remove_last( LIST, TYPE ) list_get( LIST, TYPE, ( --LIST->size ) )

#define iter_list( LIST, VAR_NAME ) \
	temp in list LIST_##VAR_NAME##_LIST = LIST; \
	iter( VAR_NAME, LIST->size )

#define get_list_iter( TYPE, VAR_NAME ) \
	temp const TYPE ref VAR_NAME##_iter_ref = ref_of( list_get( LIST_##VAR_NAME##_LIST, TYPE, VAR_NAME ) ); \
	temp const TYPE VAR_NAME##_iter = val_of( VAR_NAME##_iter_ref )

#define iter_list_fn( LIST, TYPE, FN ) _iter_list_fn_name( LIST, TYPE, FN, __COUNTER__ )
#define _iter_list_fn_name( LIST, TYPE, FN, COUNTER ) _iter_list_fn( LIST, TYPE, FN, JOIN( _FN_, COUNTER ) )
#define _iter_list_fn( LIST, TYPE, FN, NAME ) \
	iter_list( NAME, LIST ) \
	{ \
		get_list_iter( TYPE, NAME ); \
		FN( JOIN( NAME, _iter ) ); \
	}

//

type_from( list ) text;

#define new_text_size( BYTES, SIZE ) new_list_bytes_size( byte, SIZE, new_ref( byte, SIZE + 1, BYTES ), SIZE + 1 )

embed text new_text( byte ref in_bytes )
{
	if_null( in_bytes ) out new_list( byte );
	temp u4 size = measure_ref( in_bytes );
	out new_text_size( in_bytes, size );
}
#define new_text( ... ) new_text( to( byte ref, DEFAULTS( ( null ), __VA_ARGS__ ) ) )

#define delete_text( TEXT ) delete_list( TEXT )
#define resize_text( TEXT, SIZE ) resize_list( TEXT, SIZE )
#define text_set( TEXT, POS, CHAR ) list_set( TEXT, POS, to_byte( CHAR ) )
#define text_get( TEXT, POS ) list_get( TEXT, byte, POS )
#define empty_text( TEXT ) empty_list( TEXT, byte )
#define text_move( TEXT, POS, SIZE, AMOUNT ) list_move( TEXT, POS, SIZE, AMOUNT )
#define copy_text( FROM, TO, POS ) copy_list( FROM, TO, POS )
#define text_add( TEXT, CHAR ) list_add( TEXT, to_byte( CHAR ) )
#define text_insert( TEXT, POS, CHAR ) list_insert( TEXT, POS, to_byte( CHAR ) )
#define text_add_bytes_size( TEXT, BYTES, SIZE ) list_add_bytes_size( TEXT, to( byte ref, BYTES ), SIZE )
#define text_add_bytes( TEXT, BYTES ) list_add_bytes( TEXT, to( byte ref, BYTES ) )
#define text_insert_bytes_size( TEXT, POS, BYTES, SIZE ) list_insert_bytes_size( TEXT, POS, to( byte ref, BYTES ), SIZE )
#define text_insert_bytes( TEXT, POS, BYTES ) list_insert_bytes( TEXT, POS, to( byte ref, BYTES ) )
#define text_add_text( TEXT, OTHER ) list_add_list( TEXT, OTHER )
#define text_insert_text( TEXT, POS, OTHER ) list_insert_list( TEXT, POS, OTHER )
#define text_replace_text( TEXT, POS, SIZE, OTHER ) list_replace_list( TEXT, POS, SIZE, OTHER )
#define text_remove_first( TEXT ) list_remove_first( TEXT, byte )
#define text_remove_last( TEXT ) list_remove_last( TEXT, byte )
#define text_end( TEXT ) TEXT->bytes[ TEXT->size ] = '\0'
#define duplicate_text( TEXT ) new_text_size( TEXT->bytes, TEXT->size )
#define print_text( TEXT ) print_bytes( TEXT->bytes )

#define text_newline( TEXT ) text_add( TEXT, '\n' )

//

fn main_init()
{
	//
}

#define main_scope \
	fn main_fn(); \
	s4 main() \
	{ \
		main_init(); \
		main_fn(); \
	} \
	fn main_fn()

//

//

/////// UNIT TESTS

//

#define UNIT_TEST_BASE_U( T, N ) \
	expect_val( T##N, min_##T##N( 1, 2 ), 1 ); \
	expect_val( T##N, min_##T##N( 2, 1 ), 1 ); \
	expect_val( T##N, min3_##T##N( 1, 2, 3 ), 1 ); \
	expect_val( T##N, min3_##T##N( 3, 1, 2 ), 1 ); \
	expect_val( T##N, min3_##T##N( 2, 3, 1 ), 1 ); \
	expect_val( T##N, min4_##T##N( 1, 2, 3, 4 ), 1 ); \
	expect_val( T##N, min4_##T##N( 4, 1, 2, 3 ), 1 ); \
	expect_val( T##N, min4_##T##N( 3, 4, 1, 2 ), 1 ); \
	expect_val( T##N, min4_##T##N( 2, 3, 4, 1 ), 1 ); \
	expect_val( T##N, min5_##T##N( 1, 2, 3, 4, 5 ), 1 ); \
	expect_val( T##N, min5_##T##N( 5, 1, 2, 3, 4 ), 1 ); \
	expect_val( T##N, min5_##T##N( 4, 5, 1, 2, 3 ), 1 ); \
	expect_val( T##N, min5_##T##N( 3, 4, 5, 1, 2 ), 1 ); \
	expect_val( T##N, min5_##T##N( 2, 3, 4, 5, 1 ), 1 ); \
	expect_val( T##N, max_##T##N( 1, 2 ), 2 ); \
	expect_val( T##N, max_##T##N( 2, 1 ), 2 ); \
	expect_val( T##N, max3_##T##N( 1, 2, 3 ), 3 ); \
	expect_val( T##N, max3_##T##N( 3, 1, 2 ), 3 ); \
	expect_val( T##N, max3_##T##N( 2, 3, 1 ), 3 ); \
	expect_val( T##N, max4_##T##N( 1, 2, 3, 4 ), 4 ); \
	expect_val( T##N, max4_##T##N( 4, 1, 2, 3 ), 4 ); \
	expect_val( T##N, max4_##T##N( 3, 4, 1, 2 ), 4 ); \
	expect_val( T##N, max4_##T##N( 2, 3, 4, 1 ), 4 ); \
	expect_val( T##N, max5_##T##N( 1, 2, 3, 4, 5 ), 5 ); \
	expect_val( T##N, max5_##T##N( 5, 1, 2, 3, 4 ), 5 ); \
	expect_val( T##N, max5_##T##N( 4, 5, 1, 2, 3 ), 5 ); \
	expect_val( T##N, max5_##T##N( 3, 4, 5, 1, 2 ), 5 ); \
	expect_val( T##N, max5_##T##N( 2, 3, 4, 5, 1 ), 5 ); \
	expect_val( T##N, median_##T##N( 1, 2, 3 ), 2 ); \
	expect_val( T##N, median_##T##N( 3, 1, 2 ), 2 ); \
	expect_val( T##N, median_##T##N( 2, 3, 1 ), 2 ); \
	expect_val( T##N, median4_##T##N( 1, 2, 4, 5 ), 3 ); \
	expect_val( T##N, median4_##T##N( 5, 1, 2, 4 ), 3 ); \
	expect_val( T##N, median4_##T##N( 4, 5, 1, 2 ), 3 ); \
	expect_val( T##N, median4_##T##N( 2, 4, 5, 1 ), 3 ); \
	expect_val( T##N, median5_##T##N( 1, 2, 3, 4, 5 ), 3 ); \
	expect_val( T##N, median5_##T##N( 5, 1, 2, 3, 4 ), 3 ); \
	expect_val( T##N, median5_##T##N( 4, 5, 1, 2, 3 ), 3 ); \
	expect_val( T##N, median5_##T##N( 3, 4, 5, 1, 2 ), 3 ); \
	expect_val( T##N, median5_##T##N( 2, 3, 4, 5, 1 ), 3 ); \
	expect_val( T##N, avg_##T##N( 1, 3 ), 2 ); \
	expect_val( T##N, avg_##T##N( 3, 1 ), 2 ); \
	expect_val( T##N, avg3_##T##N( 1, 2, 3 ), 2 ); \
	expect_val( T##N, avg3_##T##N( 3, 1, 2 ), 2 ); \
	expect_val( T##N, avg3_##T##N( 2, 3, 1 ), 2 ); \
	expect_val( T##N, avg4_##T##N( 1, 2, 4, 5 ), 3 ); \
	expect_val( T##N, avg4_##T##N( 5, 1, 2, 4 ), 3 ); \
	expect_val( T##N, avg4_##T##N( 4, 5, 1, 2 ), 3 ); \
	expect_val( T##N, avg4_##T##N( 2, 4, 5, 1 ), 3 ); \
	expect_val( T##N, clamp_##T##N( 4, 1, 3 ), 3 ); \
	expect_val( T##N, clamp_##T##N( 2, 1, 3 ), 2 ); \
	expect_val( T##N, clamp_##T##N( 0, 1, 3 ), 1 ); \
	expect_val( T##N, saturate_##T##N( 0 ), 0 ); \
	expect_val( T##N, saturate_##T##N( 1 ), 1 ); \
	expect_val( T##N, saturate_##T##N( 2 ), 1 ); \
	expect_val( T##N, sqr_##T##N( 7 ), 49 ); \
	expect_val( T##N, snap_##T##N( 1, 2 ), 0 ); \
	expect_val( T##N, snap_##T##N( 2, 2 ), 2 ); \
	expect_val( T##N, snap_##T##N( 3, 2 ), 2 ); \
	expect_val( T##N, snap_##T##N( 4, 2 ), 4 ); \
	expect_val( T##N, snap_##T##N( 5, 2 ), 4 ); \
	expect_val( T##N, snap_##T##N( 2, 3 ), 0 ); \
	expect_val( T##N, snap_##T##N( 3, 3 ), 3 ); \
	expect_val( T##N, snap_##T##N( 4, 3 ), 3 ); \
	expect_val( T##N, snap_##T##N( 5, 3 ), 3 ); \
	expect_val( T##N, snap_##T##N( 6, 3 ), 6 )

#define UNIT_TEST_BASE_S( T, N ) \
	expect_val( T##N, min_##T##N( -1, -2 ), -2 ); \
	expect_val( T##N, min_##T##N( -2, -1 ), -2 ); \
	expect_val( T##N, min3_##T##N( -1, -2, -3 ), -3 ); \
	expect_val( T##N, min3_##T##N( -3, -1, -2 ), -3 ); \
	expect_val( T##N, min3_##T##N( -2, -3, -1 ), -3 ); \
	expect_val( T##N, min4_##T##N( -1, -2, -3, -4 ), -4 ); \
	expect_val( T##N, min4_##T##N( -4, -1, -2, -3 ), -4 ); \
	expect_val( T##N, min4_##T##N( -3, -4, -1, -2 ), -4 ); \
	expect_val( T##N, min4_##T##N( -2, -3, -4, -1 ), -4 ); \
	expect_val( T##N, min5_##T##N( -1, -2, -3, -4, -5 ), -5 ); \
	expect_val( T##N, min5_##T##N( -5, -1, -2, -3, -4 ), -5 ); \
	expect_val( T##N, min5_##T##N( -4, -5, -1, -2, -3 ), -5 ); \
	expect_val( T##N, min5_##T##N( -3, -4, -5, -1, -2 ), -5 ); \
	expect_val( T##N, min5_##T##N( -2, -3, -4, -5, -1 ), -5 ); \
	expect_val( T##N, max_##T##N( -1, -2 ), -1 ); \
	expect_val( T##N, max_##T##N( -2, -1 ), -1 ); \
	expect_val( T##N, max3_##T##N( -1, -2, -3 ), -1 ); \
	expect_val( T##N, max3_##T##N( -3, -1, -2 ), -1 ); \
	expect_val( T##N, max3_##T##N( -2, -3, -1 ), -1 ); \
	expect_val( T##N, max4_##T##N( -1, -2, -3, -4 ), -1 ); \
	expect_val( T##N, max4_##T##N( -4, -1, -2, -3 ), -1 ); \
	expect_val( T##N, max4_##T##N( -3, -4, -1, -2 ), -1 ); \
	expect_val( T##N, max4_##T##N( -2, -3, -4, -1 ), -1 ); \
	expect_val( T##N, max5_##T##N( -1, -2, -3, -4, -5 ), -1 ); \
	expect_val( T##N, max5_##T##N( -5, -1, -2, -3, -4 ), -1 ); \
	expect_val( T##N, max5_##T##N( -4, -5, -1, -2, -3 ), -1 ); \
	expect_val( T##N, max5_##T##N( -3, -4, -5, -1, -2 ), -1 ); \
	expect_val( T##N, max5_##T##N( -2, -3, -4, -5, -1 ), -1 ); \
	expect_val( T##N, median_##T##N( -1, -2, -3 ), -2 ); \
	expect_val( T##N, median_##T##N( -3, -1, -2 ), -2 ); \
	expect_val( T##N, median_##T##N( -2, -3, -1 ), -2 ); \
	expect_val( T##N, median4_##T##N( -1, -2, -4, -5 ), -3 ); \
	expect_val( T##N, median4_##T##N( -5, -1, -2, -4 ), -3 ); \
	expect_val( T##N, median4_##T##N( -4, -5, -1, -2 ), -3 ); \
	expect_val( T##N, median4_##T##N( -2, -4, -5, -1 ), -3 ); \
	expect_val( T##N, median5_##T##N( -1, -2, -3, -4, -5 ), -3 ); \
	expect_val( T##N, median5_##T##N( -5, -1, -2, -3, -4 ), -3 ); \
	expect_val( T##N, median5_##T##N( -4, -5, -1, -2, -3 ), -3 ); \
	expect_val( T##N, median5_##T##N( -3, -4, -5, -1, -2 ), -3 ); \
	expect_val( T##N, median5_##T##N( -2, -3, -4, -5, -1 ), -3 ); \
	expect_val( T##N, avg_##T##N( -1, -3 ), -2 ); \
	expect_val( T##N, avg_##T##N( -3, -1 ), -2 ); \
	expect_val( T##N, avg3_##T##N( -1, -2, -3 ), -2 ); \
	expect_val( T##N, avg3_##T##N( -3, -1, -2 ), -2 ); \
	expect_val( T##N, avg3_##T##N( -2, -3, -1 ), -2 ); \
	expect_val( T##N, avg4_##T##N( -1, -2, -4, -5 ), -3 ); \
	expect_val( T##N, avg4_##T##N( -5, -1, -2, -4 ), -3 ); \
	expect_val( T##N, avg4_##T##N( -4, -5, -1, -2 ), -3 ); \
	expect_val( T##N, avg4_##T##N( -2, -4, -5, -1 ), -3 ); \
	expect_val( T##N, clamp_##T##N( -4, 1, 3 ), 1 ); \
	expect_val( T##N, clamp_##T##N( -2, 1, 3 ), 1 ); \
	expect_val( T##N, clamp_##T##N( -4, -3, -1 ), -3 ); \
	expect_val( T##N, clamp_##T##N( -2, -3, -1 ), -2 ); \
	expect_val( T##N, clamp_##T##N( 0, -3, -1 ), -1 ); \
	expect_val( T##N, clamp_##T##N( 4, -3, -1 ), -1 ); \
	expect_val( T##N, clamp_##T##N( 2, -3, -1 ), -1 ); \
	expect_val( T##N, saturate_##T##N( -1 ), 0 ); \
	expect_val( T##N, sqr_##T##N( -3 ), 9 ); \
	expect_val( T##N, snap_##T##N( -1, 2 ), 0 ); \
	expect_val( T##N, snap_##T##N( -2, 2 ), -2 ); \
	expect_val( T##N, snap_##T##N( -3, 2 ), -2 ); \
	expect_val( T##N, snap_##T##N( -4, 2 ), -4 ); \
	expect_val( T##N, snap_##T##N( -5, 2 ), -4 ); \
	expect_val( T##N, snap_##T##N( -2, 3 ), -0 ); \
	expect_val( T##N, snap_##T##N( -3, 3 ), -3 ); \
	expect_val( T##N, snap_##T##N( -4, 3 ), -3 ); \
	expect_val( T##N, snap_##T##N( -5, 3 ), -3 ); \
	expect_val( T##N, snap_##T##N( -6, 3 ), -6 ); \
	expect_val( T##N, snap_##T##N( 1, -2 ), 0 ); \
	expect_val( T##N, snap_##T##N( 2, -2 ), 2 ); \
	expect_val( T##N, snap_##T##N( 3, -2 ), 2 ); \
	expect_val( T##N, snap_##T##N( 4, -2 ), 4 ); \
	expect_val( T##N, snap_##T##N( 5, -2 ), 4 ); \
	expect_val( T##N, snap_##T##N( 2, -3 ), 0 ); \
	expect_val( T##N, snap_##T##N( 3, -3 ), 3 ); \
	expect_val( T##N, snap_##T##N( 4, -3 ), 3 ); \
	expect_val( T##N, snap_##T##N( 5, -3 ), 3 ); \
	expect_val( T##N, snap_##T##N( 6, -3 ), 6 ); \
	expect_val( T##N, snap_##T##N( -1, -2 ), -0 ); \
	expect_val( T##N, snap_##T##N( -2, -2 ), -2 ); \
	expect_val( T##N, snap_##T##N( -3, -2 ), -2 ); \
	expect_val( T##N, snap_##T##N( -4, -2 ), -4 ); \
	expect_val( T##N, snap_##T##N( -5, -2 ), -4 ); \
	expect_val( T##N, snap_##T##N( -2, -3 ), -0 ); \
	expect_val( T##N, snap_##T##N( -3, -3 ), -3 ); \
	expect_val( T##N, snap_##T##N( -4, -3 ), -3 ); \
	expect_val( T##N, snap_##T##N( -5, -3 ), -3 ); \
	expect_val( T##N, snap_##T##N( -6, -3 ), -6 ); \
	expect_val( T##N, abs_##T##N( 2 ), 2 ); \
	expect_val( T##N, abs_##T##N( 1 ), 1 ); \
	expect_val( T##N, abs_##T##N( 0 ), 0 ); \
	expect_val( T##N, abs_##T##N( -1 ), 1 ); \
	expect_val( T##N, abs_##T##N( -2 ), 2 ); \
	expect_val( T##N, sign_##T##N( 2 ), 1 ); \
	expect_val( T##N, sign_##T##N( 1 ), 1 ); \
	expect_val( T##N, sign_##T##N( 0 ), 1 ); \
	expect_val( T##N, sign_##T##N( -1 ), -1 ); \
	expect_val( T##N, sign_##T##N( -2 ), -1 ); \
	expect_val( T##N, sign_zero_##T##N( 2 ), 1 ); \
	expect_val( T##N, sign_zero_##T##N( 1 ), 1 ); \
	expect_val( T##N, sign_zero_##T##N( 0 ), 0 ); \
	expect_val( T##N, sign_zero_##T##N( -1 ), -1 ); \
	expect_val( T##N, sign_zero_##T##N( -2 ), -1 )

#define UNIT_TEST_BASE_US( US, N ) \
	expect_val( US##N, snap_bit_##US##N( 1, 1 ), 0 ); \
	expect_val( US##N, snap_bit_##US##N( 3, 1 ), 2 ); \
	expect_val( US##N, snap_bit_##US##N( 5, 1 ), 4 ); \
	expect_val( US##N, snap_bit_##US##N( 7, 1 ), 6 ); \
	expect_val( US##N, snap_bit_##US##N( 9, 1 ), 8 ); \
	expect_val( US##N, snap_bit_##US##N( 1, 2 ), 0 ); \
	expect_val( US##N, snap_bit_##US##N( 3, 2 ), 0 ); \
	expect_val( US##N, snap_bit_##US##N( 5, 2 ), 4 ); \
	expect_val( US##N, snap_bit_##US##N( 7, 2 ), 4 ); \
	expect_val( US##N, snap_bit_##US##N( 9, 2 ), 8 ); \
	expect_val( US##N, snap_bit_##US##N( 1, 3 ), 0 ); \
	expect_val( US##N, snap_bit_##US##N( 3, 3 ), 0 ); \
	expect_val( US##N, snap_bit_##US##N( 5, 3 ), 0 ); \
	expect_val( US##N, snap_bit_##US##N( 7, 3 ), 0 ); \
	expect_val( US##N, snap_bit_##US##N( 9, 3 ), 8 )

#define UNIT_TEST_U( N ) \
	UNIT_TEST_BASE_U( u, N ); \
	UNIT_TEST_BASE_US( u, N )

#define UNIT_TEST_S( N ) \
	UNIT_TEST_BASE_U( s, N ); \
	UNIT_TEST_BASE_S( s, N ); \
	UNIT_TEST_BASE_US( s, N )

#define UNIT_TEST_F( N ) \
	UNIT_TEST_BASE_U( f, N ); \
	UNIT_TEST_BASE_S( f, N ); \
	expect_val( f##N, trunc_f##N( 3.7 ), 3. ); \
	expect_val( f##N, trunc_f##N( -3.7 ), -3. ); \
	expect_val( f##N, trunc_f##N( 0.1 ), 0. ); \
	expect_val( f##N, trunc_f##N( -0.1 ), 0. ); \
	expect_val( f##N, trunc_f##N( 1.999999 ), 1. ); \
	expect_val( f##N, trunc_f##N( -1.999999 ), -1. ); \
	expect_val( f##N, round_f##N( 3.2 ), 3. ); \
	expect_val( f##N, round_f##N( 3.8 ), 4. ); \
	expect_val( f##N, round_f##N( -3.2 ), -3. ); \
	expect_val( f##N, round_f##N( -3.8 ), -4. ); \
	expect_val( f##N, round_f##N( 0.5 ), 1. ); \
	expect_val( f##N, round_f##N( -0.5 ), -1. ); \
	expect_val( f##N, round_f##N( 0.49999 ), 0. ); \
	expect_val( f##N, round_f##N( -0.49999 ), 0. ); \
	expect_val( f##N, round_f##N( 0. ), 0. ); \
	expect_val( f##N, floor_f##N( 3.7 ), 3. ); \
	expect_val( f##N, floor_f##N( -3.7 ), -4. ); \
	expect_val( f##N, floor_f##N( 0.1 ), 0. ); \
	expect_val( f##N, floor_f##N( -0.1 ), -1. ); \
	expect_val( f##N, floor_f##N( 1.999999 ), 1. ); \
	expect_val( f##N, floor_f##N( -1.999999 ), -2. ); \
	expect_val( f##N, floor_f##N( 0. ), 0. ); \
	expect_val( f##N, ceil_f##N( 3.2 ), 4. ); \
	expect_val( f##N, ceil_f##N( -3.2 ), -3. ); \
	expect_val( f##N, ceil_f##N( 0.1 ), 1. ); \
	expect_val( f##N, ceil_f##N( -0.1 ), 0. ); \
	expect_val( f##N, ceil_f##N( 1.999999 ), 2. ); \
	expect_val( f##N, ceil_f##N( -1.999999 ), -1. ); \
	expect_val( f##N, ceil_f##N( 0. ), 0. ); \
	expect_val( f##N, mod_f##N( 5.5, 2. ), 1.5 ); \
	expect_val( f##N, mod_f##N( -5.5, 2. ), 0.5 ); \
	expect_val( f##N, mod_f##N( 5.5, -2. ), -0.5 ); \
	expect_val( f##N, mod_f##N( -5.5, -2. ), -1.5 ); \
	expect_val( f##N, mod_f##N( 0., 2. ), 0. ); \
	expect_val( f##N, mod_f##N( 2., 2. ), 0. ); \
	expect_val( f##N, mix_f##N( 1., 3., 0.5 ), 2. ); \
	expect_val( f##N, mix_f##N( 1., 3., 0. ), 1. ); \
	expect_val( f##N, mix_f##N( 1., 3., 1. ), 3. ); \
	expect_val( f##N, mix_f##N( -1., 1., 0.5 ), 0. ); \
	expect_val( f##N, mix_f##N( 1., -1., 0.5 ), 0. ); \
	expect_val( f##N, mix_f##N( 1., 3., 0.25 ), 1.5 ); \
	expect_val( f##N, mix_f##N( 1., 3., 0.75 ), 2.5 ); \
	expect_val( f##N, map_f##N( 2., 1., 3., 0., 10. ), 5. ); \
	expect_val( f##N, map_f##N( 1., 1., 3., 0., 10. ), 0. ); \
	expect_val( f##N, map_f##N( 3., 1., 3., 0., 10. ), 10. ); \
	expect_val( f##N, map_f##N( 2., 1., 3., 10., 0. ), 5. ); \
	expect_val( f##N, map_f##N( 0., -1., 1., 0., 10. ), 5. ); \
	expect_val( f##N, map_f##N( -1., -1., 1., 0., 10. ), 0. ); \
	expect_val( f##N, map_f##N( 1.5, 1., 2., 0., 1. ), 0.5 ); \
	expect_val( f##N, range_f##N( 2., 1., 3. ), 0.5 ); \
	expect_val( f##N, range_f##N( 1., 1., 3. ), 0. ); \
	expect_val( f##N, range_f##N( 3., 1., 3. ), 1. ); \
	expect_val( f##N, range_f##N( 2., 3., 1. ), 0.5 ); \
	expect_val( f##N, range_f##N( 0., -1., 1. ), 0.5 ); \
	expect_val( f##N, range_f##N( -1., -1., 1. ), 0. ); \
	expect_val( f##N, range_f##N( 1., -1., 1. ), 1. ); \
	expect_val( f##N, range_f##N( 1.5, 1., 2. ), 0.5 )

//

fn UNIT_TEST_CONSTRUCT_LIST()
{
	s4 data[] = { 1, 2, 3, 4, 5 };
	temp list test_list = construct_list( 5, 10, s4_size, to( byte ref, ref_of( data ) ) );

	expect_val( u4, test_list->size, 5 );
	expect_val( u4, test_list->capacity, 10 );
	expect_val( u2, test_list->type_size, s4_size );
	expect( compare_bytes( test_list->bytes, data, test_list->size * s4_size ) is 0 );

	cast( byte mutable_ref, test_list->bytes ) = null;
	delete_list( test_list );
}

fn UNIT_TEST_NEW_LIST()
{
	temp list test_list = new_list( s4 );

	expect_val( u4, test_list->size, 0 );
	expect_val( u4, test_list->capacity, 1 );
	expect_val( u2, test_list->type_size, s4_size );

	delete_list( test_list );
}

fn UNIT_TEST_GROW_LIST()
{
	temp list test_list = new_list( s4 );
	temp u4 initial_capacity = test_list->capacity;

	iter( i, initial_capacity + 1 )
	{
		list_add( test_list, i );
	}

	expect_val( u4, test_list->size, initial_capacity + 1 );
	expect( test_list->capacity > initial_capacity );
	expect_val( u2, test_list->type_size, s4_size );

	delete_list( test_list );
}

fn UNIT_TEST_RESIZE_LIST()
{
	temp list test_list = new_list( s4 );
	resize_list( test_list, 10 );

	expect_val( u4, test_list->size, 10 );
	expect( test_list->capacity > 10 );
	expect_val( u2, test_list->type_size, s4_size );

	delete_list( test_list );
}

fn UNIT_TEST_LIST_SET_GET()
{
	temp list test_list = new_list( s4 );
	resize_list( test_list, 5 );

	iter( i, 5 )
	{
		list_set( test_list, i, i * 10 );
	}

	iter( i, 5 )
	{
		expect_val( s4, list_get( test_list, s4, i ), i * 10 );
	}

	delete_list( test_list );
}

fn UNIT_TEST_EMPTY_LIST()
{
	list test_list = new_list( s4 );
	list_add( test_list, 42 );
	expect_val( u4, test_list->size, 1 );

	empty_list( test_list, s4 );
	expect_val( u4, test_list->size, 0 );
	expect_val( s4, list_get( test_list, s4, 0 ), 0 );

	delete_list( test_list );
}

fn UNIT_TEST_LIST_MOVE()
{
	list test_list = new_list( s4 );
	iter( i, 5 )
	{
		list_add( test_list, i );
	}

	list_move( test_list, 1, 3, 1 );

	expect_val( s4, list_get( test_list, s4, 0 ), 0 );
	expect_val( s4, list_get( test_list, s4, 1 ), 1 );
	expect_val( s4, list_get( test_list, s4, 2 ), 1 );
	expect_val( s4, list_get( test_list, s4, 3 ), 2 );
	expect_val( s4, list_get( test_list, s4, 4 ), 3 );

	delete_list( test_list );
}

fn UNIT_TEST_COPY_LIST()
{
	list source_list = new_list( s4 );
	list dest_list = new_list( s4 );

	iter( i, 5 )
	{
		list_add( source_list, i );
	}

	resize_list( dest_list, 10 );
	copy_list( source_list, dest_list, 2 );

	iter( i, 5 )
	{
		expect( list_get( dest_list, s4, i + 2 ) == i );
	}

	delete_list( source_list );
	delete_list( dest_list );
}

fn UNIT_TEST_LIST_ADD()
{
	list test_list = new_list( s4 );

	iter( i, 10 )
	{
		list_add( test_list, i );
		expect( test_list->size == i + 1 );
		expect( list_get( test_list, s4, i ) == i );
	}

	delete_list( test_list );
}

fn UNIT_TEST_LIST_INSERT()
{
	temp list test_list = new_list( s4 );

	iter( i, 5 )
	{
		list_add( test_list, i );
	}

	list_insert( test_list, 2, 7 );

	expect( test_list->size > 5 );
	expect_val( s4, list_get( test_list, s4, 2 ), 7 );
	expect_val( s4, list_get( test_list, s4, 3 ), 2 );

	delete_list( test_list );
}

fn UNIT_TEST_LIST_ADD_BYTES()
{
	list test_list = new_list( byte );
	byte ref test_string = "Hello, World!";

	list_add_bytes( test_list, test_string );

	expect( test_list->size == strlen( test_string ) );
	expect( compare_bytes( test_list->bytes, test_string, test_list->size ) == 0 );

	delete_list( test_list );
}

fn UNIT_TEST_LIST_INSERT_BYTES()
{
	list test_list = new_list( byte );
	byte ref initial_string = "Hello, World!";
	byte ref insert_string = "Beautiful ";

	list_add_bytes( test_list, initial_string );
	list_insert_bytes( test_list, 7, insert_string );

	expect( test_list->size == strlen( initial_string ) + strlen( insert_string ) );
	expect( compare_bytes( test_list->bytes, "Hello, Beautiful World!", test_list->size ) == 0 );

	delete_list( test_list );
}

fn UNIT_TEST_LIST_ADD_LIST()
{
	list list1 = new_list( s4 );
	list list2 = new_list( s4 );

	iter( i, 5 )
	{
		list_add( list1, i );
		list_add( list2, i + 5 );
	}

	list_add_list( list1, list2 );

	expect( list1->size == 10 );
	iter( i, 10 )
	{
		expect( list_get( list1, s4, i ) == i );
	}

	delete_list( list1 );
	delete_list( list2 );
}

fn UNIT_TEST_LIST_INSERT_LIST()
{
	temp list list1 = new_list( s4 );
	temp list list2 = new_list( s4 );

	iter( i, 5 )
	{
		list_add( list1, i );
		list_add( list2, i + 10 );
	}

	list_insert_list( list1, 2, list2 );

	expect( list1->size == 10 );
	expect( list_get( list1, s4, 1 ) == 1 );
	expect( list_get( list1, s4, 2 ) == 10 );
	expect( list_get( list1, s4, 6 ) == 14 );
	expect( list_get( list1, s4, 7 ) == 2 );

	delete_list( list1 );
	delete_list( list2 );
}

fn UNIT_TEST_LIST_REPLACE_LIST()
{
	list list1 = new_list( s4 );
	list list2 = new_list( s4 );

	iter( i, 10 )
	{
		list_add( list1, i );
	}

	iter( i, 3 )
	{
		list_add( list2, i + 100 );
	}

	list_replace_list( list1, 4, 2, list2 );

	expect( list1->size == 11 );
	expect( list_get( list1, s4, 3 ) == 3 );
	expect( list_get( list1, s4, 4 ) == 100 );
	expect( list_get( list1, s4, 6 ) == 102 );
	expect( list_get( list1, s4, 7 ) == 6 );

	delete_list( list1 );
	delete_list( list2 );
}

fn UNIT_TEST_LIST_DELETE()
{
	list test_list = new_list( s4 );

	iter( i, 5 )
	{
		list_add( test_list, to_s4( i ) );
	}

	list_delete( test_list, 2 );

	expect( test_list->size == 4 );
	expect( list_get( test_list, s4, 2 ) == 3 );

	delete_list( test_list );
}

fn UNIT_TEST_LIST_REMOVE_FIRST_LAST()
{
	list test_list = new_list( s4 );

	iter( i, 5 )
	{
		list_add( test_list, i );
	}

	s4 first = list_remove_first( test_list, s4 );
	expect( first == 0 );
	expect( test_list->size == 4 );
	expect( list_get( test_list, s4, 0 ) == 1 );

	s4 last = list_remove_last( test_list, s4 );
	expect( last == 4 );
	expect( test_list->size == 3 );
	expect( list_get( test_list, s4, 2 ) == 3 );

	delete_list( test_list );
}

fn UNIT_TEST_ITER_LIST()
{
	list test_list = new_list( s4 );

	iter( i, 5 )
	{
		list_add( test_list, i );
	}

	s4 sum = 0;
	iter_list( test_list, i )
	{
		get_list_iter( s4, i );
		sum += i_iter;
	}

	expect( sum == 10 );

	delete_list( test_list );
}

//

fn UNIT_TEST_NEW_TEXT()
{
	byte ref test_str = "Hello, World!";
	u2 test_str_length = measure_ref( test_str );
	text t1 = new_text_size( test_str, test_str_length );
	text t2 = new_text( test_str );

	expect( t1->size is test_str_length );
	expect( t2->size is test_str_length );
	expect( compare_bytes( t1->bytes, test_str, test_str_length ) == 0 );
	expect( compare_bytes( t2->bytes, test_str, test_str_length ) == 0 );

	delete_text( t1 );
	delete_text( t2 );

	text t3 = new_text( NULL );
	expect( t3->size == 0 );
	delete_text( t3 );
}

fn UNIT_TEST_RESIZE_TEXT()
{
	text t = new_text( "Hello" );
	resize_text( t, 10 );

	expect( t->size == 10 );
	expect( t->capacity >= 10 );

	delete_text( t );
}

fn UNIT_TEST_TEXT_SET_GET()
{
	temp text t = new_text( "Hello" );
	text_set( t, 0, 'a' );
	text_set( t, 1, 'b' );
	text_set( t, 2, 'c' );
	text_set( t, 3, 'd' );
	text_set( t, 4, 'e' );
	expect_val( byte, text_get( t, 0 ), 'a' );
	expect_val( byte, text_get( t, 1 ), 'b' );
	expect_val( byte, text_get( t, 2 ), 'c' );
	expect_val( byte, text_get( t, 3 ), 'd' );
	expect_val( byte, text_get( t, 4 ), 'e' );
	delete_text( t );
}

fn UNIT_TEST_EMPTY_TEXT()
{
	text t = new_text( "Hello" );
	empty_text( t );

	expect( t->size == 0 );
	expect( text_get( t, 0 ) == 0 );

	delete_text( t );
}

fn UNIT_TEST_TEXT_MOVE()
{
	text t = new_text( "Hello, World!" );
	text_move( t, 0, 5, 7 );

	expect( compare_bytes( t->bytes, "Hello, Hello!", t->size ) == 0 );

	delete_text( t );
}

fn UNIT_TEST_COPY_TEXT()
{
	text src = new_text( "Hello" );
	text dest = new_text( "World!" );

	copy_text( src, dest, 0 );

	expect( compare_bytes( dest->bytes, "Hello!", dest->size ) == 0 );

	delete_text( src );
	delete_text( dest );
}

fn UNIT_TEST_TEXT_ADD()
{
	text t = new_text( "Hello" );

	text_add( t, '!' );

	expect( compare_bytes( t->bytes, "Hello!", t->size ) == 0 );

	delete_text( t );
}

fn UNIT_TEST_TEXT_INSERT()
{
	text t = new_text( "Hello" );
	text_insert( t, 2, 'x' );
	expect( compare_bytes( t->bytes, "Hexllo", t->size ) == 0 );

	delete_text( t );
}

fn UNIT_TEST_TEXT_ADD_BYTES()
{
	text t = new_text( "Hello" );
	byte ref add_str = ", World!";

	text_add_bytes_size( t, add_str, strlen( add_str ) );
	expect( compare_bytes( t->bytes, "Hello, World!", t->size ) == 0 );

	text_add_bytes( t, "!!!" );
	expect( compare_bytes( t->bytes, "Hello, World!!!!", t->size ) == 0 );

	delete_text( t );
}

fn UNIT_TEST_TEXT_INSERT_BYTES()
{
	text t = new_text( "Hello World!" );
	byte ref insert_str = "Beautiful ";

	text_insert_bytes_size( t, 6, insert_str, strlen( insert_str ) );
	expect( compare_bytes( t->bytes, "Hello Beautiful World!", t->size ) == 0 );

	text_insert_bytes( t, 0, "Oh, " );
	expect( compare_bytes( t->bytes, "Oh, Hello Beautiful World!", t->size ) == 0 );

	delete_text( t );
}

fn UNIT_TEST_TEXT_ADD_TEXT()
{
	text t1 = new_text( "Hello" );
	text t2 = new_text( ", World!" );

	text_add_text( t1, t2 );
	expect( compare_bytes( t1->bytes, "Hello, World!", t1->size ) == 0 );

	delete_text( t1 );
	delete_text( t2 );
}

fn UNIT_TEST_TEXT_INSERT_TEXT()
{
	text t1 = new_text( "Hello World!" );
	text t2 = new_text( "Beautiful " );

	text_insert_text( t1, 6, t2 );
	expect( compare_bytes( t1->bytes, "Hello Beautiful World!", t1->size ) == 0 );

	delete_text( t1 );
	delete_text( t2 );
}

fn UNIT_TEST_TEXT_REPLACE_TEXT()
{
	text t1 = new_text( "Hello World!" );
	text t2 = new_text( "Beautiful" );

	text_replace_text( t1, 6, 5, t2 );
	expect( compare_bytes( t1->bytes, "Hello Beautiful!", t1->size ) == 0 );

	delete_text( t1 );
	delete_text( t2 );
}

fn UNIT_TEST_TEXT_REMOVE_FIRST_LAST()
{
	text t = new_text( "Hello" );

	byte first = text_remove_first( t );
	expect( first == 'H' );
	expect( compare_bytes( t->bytes, "ello", t->size ) == 0 );

	byte last = text_remove_last( t );
	expect( last == 'o' );
	expect( compare_bytes( t->bytes, "ell", t->size ) == 0 );

	delete_text( t );
}

fn UNIT_TEST_TEXT_END()
{
	text t = new_text( "Hello" );
	text_add_bytes( t, " World!" );
	text_end( t );

	expect( t->bytes[ t->size ] == '\0' );

	delete_text( t );
}

fn UNIT_TEST_DUPLICATE_TEXT()
{
	text original = new_text( "Hello" );
	text duplicate = duplicate_text( original );

	expect( compare_bytes( original->bytes, duplicate->bytes, original->size ) == 0 );
	expect( original->size == duplicate->size );

	delete_text( original );
	delete_text( duplicate );
}

fn UNIT_TEST_TEXT_NEWLINE()
{
	text t = new_text( "Hello" );
	text_newline( t );

	expect( t->bytes[ t->size - 1 ] == '\n' );
	expect( compare_bytes( t->bytes, "Hello\n", t->size ) == 0 );

	delete_text( t );
}

//

fn UNIT_TESTS()
{
	UNIT_TEST_U( 1 );
	UNIT_TEST_S( 1 );

	UNIT_TEST_U( 2 );
	UNIT_TEST_S( 2 );

	UNIT_TEST_U( 4 );
	UNIT_TEST_S( 4 );
	UNIT_TEST_F( 4 );

	UNIT_TEST_U( 8 );
	UNIT_TEST_S( 8 );
	UNIT_TEST_F( 8 );

	//

	UNIT_TEST_CONSTRUCT_LIST();
	UNIT_TEST_NEW_LIST();
	UNIT_TEST_GROW_LIST();
	UNIT_TEST_RESIZE_LIST();
	UNIT_TEST_LIST_SET_GET();
	UNIT_TEST_EMPTY_LIST();
	UNIT_TEST_CONSTRUCT_LIST();
	UNIT_TEST_NEW_LIST();
	UNIT_TEST_GROW_LIST();
	UNIT_TEST_RESIZE_LIST();
	UNIT_TEST_LIST_SET_GET();
	UNIT_TEST_EMPTY_LIST();
	UNIT_TEST_LIST_MOVE();
	UNIT_TEST_COPY_LIST();
	UNIT_TEST_LIST_ADD();
	UNIT_TEST_LIST_INSERT();
	UNIT_TEST_LIST_ADD_BYTES();
	UNIT_TEST_LIST_INSERT_BYTES();
	UNIT_TEST_LIST_ADD_LIST();
	UNIT_TEST_LIST_INSERT_LIST();
	UNIT_TEST_LIST_REPLACE_LIST();
	UNIT_TEST_LIST_DELETE();
	UNIT_TEST_LIST_REMOVE_FIRST_LAST();
	UNIT_TEST_ITER_LIST();

	UNIT_TEST_NEW_TEXT();
	UNIT_TEST_RESIZE_TEXT();
	UNIT_TEST_TEXT_SET_GET();
	UNIT_TEST_EMPTY_TEXT();
	UNIT_TEST_TEXT_MOVE();
	UNIT_TEST_COPY_TEXT();
	UNIT_TEST_TEXT_ADD();
	UNIT_TEST_TEXT_INSERT();
	UNIT_TEST_TEXT_ADD_BYTES();
	UNIT_TEST_TEXT_INSERT_BYTES();
	UNIT_TEST_TEXT_ADD_TEXT();
	UNIT_TEST_TEXT_INSERT_TEXT();
	UNIT_TEST_TEXT_REPLACE_TEXT();
	UNIT_TEST_TEXT_REMOVE_FIRST_LAST();
	UNIT_TEST_TEXT_END();
	UNIT_TEST_DUPLICATE_TEXT();
	UNIT_TEST_TEXT_NEWLINE();
}

//