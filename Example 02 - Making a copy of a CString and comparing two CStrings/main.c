//! Example 02 - Making a copy of a CString and comparing two CStrings
/*!
  This simply example demonstrates how to make a copy of CString and comparing
  two CStrings. 

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

#include <CString.h>

/*!
  Main function.
*/
int main(void){
  /*!
    Memory manager initialization.
  */
  if (ui8MemoryManagerInit() != MEMORY_MANAGER_INITIALIZED){
    return 1;
  }

  /*!
    Creating CStrings.
  */
  xCStringCreate(csString);
  xCStringCreate(csCopyString);

  /*!
    Initializing CStrings.
  */
  if (ui8CStringInit(&csString, 30) != STRING_CREATED || ui8CStringInit(&csCopyString, 26)  != STRING_CREATED){
    return 2;
  }

  /*!
    Editing csString.
  */
  uint8_t ui8Sensor = 236;
  if (ui8CStringPutData(&csString, csCharType("Sensor: "), csIntType(ui8Sensor), csCharType("\nSetPoint: "), csIntType(122)) != ALL_DATA_ADDED){
    return 3;
  }

  /*!
    Making a copy of csString.
  */
  if (ui8CopyCString(&csCopyString, &csString) != COPIED_STRING){
    return 4;
  }

  /*!
    Comparing the two CStrings.
  */
  if (ui8CompareCStrings(&csString, &csCopyString) == IDENTICAL_STRINGS){
    printf("%s", cpCStringToCharArray(&csString));
    printf("\n\nString size: %d", ui16GetCStringSize(&csString));
  }

  return 0;
}
