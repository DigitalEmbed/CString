/*!
  This code file was written by Jorge Henrique Moreira Santana and is under
  the GNU GPLv3 license. All legal rights are reserved.

  Permissions of this copyleft license are conditioned on making available
  complete source code of licensed works and modifications under the same
  license or the GNU GPLv3. Copyright and license notices must be preserved.
  Contributors provide an express grant of patent rights. However, a larger
  work using the licensed work through interfaces provided by the licensed
  work may be distributed under different terms and without source code for
  the larger work.

  * Permissions:
    -> Commercial use;
    -> Modification;
    -> Distribuition;
    -> Patent Use;
    -> Private Use;

  * Limitations:
    -> Liability;
    -> Warranty;

  * Conditions:
    -> License and copyright notice;
    -> Disclose source;
    -> State changes;
    -> Same license (library);

  For more informations, check the LICENSE document. If you want to use a
  commercial product without having to provide the source code, send an email
  to jorge_henrique_123@hotmail.com to talk.
*/

#ifndef CString_H
#define CString_H

#ifdef __cplusplus
  extern "C" {
#endif

#include <MemoryManager.h>
#include <stdint.h>
#include <stdarg.h>

//! Macro: String Status
/*!
  This macros are for facilitate the use of this library.
*/
#define STRING_INITIALIZED                      0
#define ALL_DATA_ADDED                          2
#define IDENTICAL_STRINGS                       4
#define DIFFERENT_STRINGS                       5
#define COPIED_STRING                           6
#define ERASED_STRING                           7
#define CONVERTED_STRING                        8
#define DELETED_STRING                          9

#define ERROR_STRING_NOT_INITIALIZED            100
#define ERROR_NO_SPACE_ON_DATABANK              101
#define ERROR_NO_SPACE_IN_STRING                102
#define ERROR_TRUNCATED_STRING                  103
#define ERROR_NOT_A_NUMERIC_STRING              108
#define ERROR_STRING_NOT_DEALLOCATED            109

//! Macro: Automation Macros
/*!
  This macros are for facilitate the use of this library.
*/
#define INT_TYPE                                1
#define OCTAL_TYPE                              2
#define HEX_TYPE                                3
#define CHAR_TYPE                               4
#define FLOAT_TYPE                              5

#define sIntType                                INT_TYPE,
#define sOctalType                              OCTAL_TYPE,
#define sHexType                                HEX_TYPE,
#define sCharType                               CHAR_TYPE, (int)
#define sFloatType                              FLOAT_TYPE, (int)

#define ui8StringAdd(cspString, ...)            ui8StringAdd(cspString, sizeof((int []) {__VA_ARGS__}) / sizeof(int), __VA_ARGS__)

#define xStringCreate(csName)                   string_t csName = {NULL, 0, 0}

//! Type Definition: String Struct.
/*!
  This struct creates a string "object".
*/
typedef struct{
  char* cpString;
  uint16_t ui16MaxSize;
  uint16_t ui16StringSize;
}string_t;

uint8_t ui8StringInit(string_t* cspString, uint16_t ui16MaxSize);                       /*!< 8-bits integer type function. */
uint8_t ui8StringDelete(string_t* cspString);                                           /*!< 8-bits integer type function. */
uint8_t (ui8StringAdd)(string_t* cspString, int iAmountOfArguments, ...);               /*!< 8-bits integer type function. */
uint8_t ui8StringPrintf(string_t* cspString, const char* cpCharArray, ...);             /*!< 8-bits integer type function. */
uint8_t ui8CompareStrings(string_t* cspStringA, string_t* cspStringB);                  /*!< 8-bits integer type function. */
uint8_t ui8CopyString(string_t* cspDestinyString, string_t* cspOriginString);           /*!< 8-bits integer type function. */
uint8_t ui8EraseString(string_t* cspString);                                            /*!< 8-bits integer type function. */
uint16_t ui16GetStringFreeSpace(string_t* cspString);                                   /*!< 16-bits integer type function. */
uint16_t ui16GetStringMaxSize(string_t* cspString);                                     /*!< 16-bits integer type function. */
uint16_t ui16GetStringSize(string_t* cspString);                                        /*!< 16-bits integer type function. */
char* cpStringToCharArray(string_t* cspString);                                         /*!< 8-bits integer type function. */
char cStringToChar(string_t* cspString, uint16_t ui16Position);                         /*!< 8-bits integer type function. */

#ifdef __cplusplus
  }
#endif

#endif
