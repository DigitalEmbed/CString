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

#include <MemoryManager.h>
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
    Creating Strings.
  */
  xStringCreate(sString);
  xStringCreate(sCopyString);

  /*!
    Initializing Strings.
  */
  if (ui8StringInit(&sString, 30) != STRING_INITIALIZED || ui8StringInit(&sCopyString, 26)  != STRING_INITIALIZED){
    return 2;
  }

  /*!
    Editing sString.
  */
  uint8_t ui8Sensor = 236;
  if (ui8StringAdd(&sString, sCharType("Sensor: "), sIntType(ui8Sensor), sCharType("\nSetPoint: "), sIntType(122)) != ALL_DATA_ADDED){
    return 3;
  }

  /*!
    Making a copy of sString.
  */
  if (ui8CopyString(&sCopyString, &sString) != COPIED_STRING){
    return 4;
  }

  /*!
    Comparing the two Strings.
  */
  if (ui8CompareStrings(&sString, &sCopyString) == IDENTICAL_STRINGS){
    printf("%s", cpStringToCharArray(&sCopyString));
    printf("\n\nString max size: %d\nString size: %d\nString free space: %d", ui16GetStringMaxSize(&sString), ui16GetStringSize(&sString), ui16GetStringFreeSpace(&sString));
  }

  return 0;
}
