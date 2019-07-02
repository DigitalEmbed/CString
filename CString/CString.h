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
#include <stdarg.h>

//! Macro: String Status
/*!
  This macros are for facilitate the use of this library.
*/
#define STRING_CREATED                          0
#define ALL_DATA_ADDED                          2
#define IDENTICAL_STRINGS                       4
#define DIFFERENT_STRINGS                       5
#define COPIED_STRING                           6
#define ERASED_STRING                           7
#define CONVERTED_STRING                        8
#define DELETED_STRING                          9

#define ERROR_STRING_NOT_CREATED                100
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

#define csIntType                               INT_TYPE,
#define csOctalType                             OCTAL_TYPE,
#define csHexType                               HEX_TYPE,
#define csCharType                              CHAR_TYPE, (int)
#define csFloatType                             FLOAT_TYPE, (int)

#define ui8CStringPutData(cspString, ...)       ui8CStringPutData(cspString, sizeof((int []) {__VA_ARGS__}) / sizeof(int), __VA_ARGS__)

#define xCStringCreate(csName)                  cstring_t csName = {NULL, 0, 0, 0}

//! Type Definition: CString Struct.
/*!
  This struct creates a cstring "object".
*/
typedef struct{
  char* cpString;
  uint16_t ui16MaxSize;
  uint16_t ui16ActualPosition;
  uint16_t ui16StringSize;
}cstring_t;

uint8_t ui8CStringInit(cstring_t* cspString, uint16_t ui16MaxSize);                       /*!< 8-bits integer type function. */
uint8_t ui8CStringDelete(cstring_t* cspString);                                           /*!< 8-bits integer type function. */
uint8_t (ui8CStringPutData)(cstring_t* cspString, int iAmountOfArguments, ...);           /*!< 8-bits integer type function. */
uint8_t ui8GetCStringFreeSpace(cstring_t* cspString);                                     /*!< 8-bits integer type function. */
uint8_t ui8GetCStringMaxSize(cstring_t* cspString);                                       /*!< 8-bits integer type function. */
uint8_t ui8GetCStringSize(cstring_t* cspString);                                          /*!< 8-bits integer type function. */
uint8_t ui8CompareCStrings(cstring_t* cspStringA, cstring_t* cspStringB);                 /*!< 8-bits integer type function. */
uint8_t ui8CopyCString(cstring_t* cspDestinyString, cstring_t* cspOriginString);          /*!< 8-bits integer type function. */
uint8_t ui8EraseCString(cstring_t* cspString);                                            /*!< 8-bits integer type function. */
char* cpCStringToCharArray(cstring_t* cspString);                                         /*!< 8-bits integer type function. */
char cCStringToChar(cstring_t* cspString, uint16_t ui16Position);                         /*!< 8-bits integer type function. */

#ifdef __cplusplus
  }
#endif

#endif
