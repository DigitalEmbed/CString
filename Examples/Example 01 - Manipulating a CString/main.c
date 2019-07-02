//! Example 01 - Manipulating a CString
/*!
  This simply example demonstrates how to manipulate CStrings.

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
    Creating CStrings.
  */
  xCStringCreate(csString);

  /*!
    Initializing CStrings.
  */
  uint8_t ui8StatusString = ui8CStringInit(&csString,           //Address of csString
                                          50);                  //Max size of csString

  if (ui8StatusString != STRING_INITIALIZED){
    return 2;
  }

  /*!
    Editing csString.
  */
  uint8_t ui8SensorA = 236;
  uint8_t ui8SensorB = 178;
  if (ui8CStringPutData(&csString, csCharType("SensorA: "), csIntType(ui8SensorA)) != ALL_DATA_ADDED){
    return 3;
  }
  if (ui8CStringPutData(&csString, csCharType("SensorB: "), csIntType(ui8SensorB)) != ALL_DATA_ADDED){
    return 4;
  }
  if (ui8CStringPutData(&csString, csCharType("\nSetPoint: "), csIntType(122)) != ALL_DATA_ADDED){
    return 5;
  }

  /*!
    Printing csString.
  */
  printf("%s", cpCStringToCharArray(&csString));
  printf("\n\nString max size: %d\nString size: %d\nString free space: %d", ui16GetCStringMaxSize(&csString), ui16GetCStringSize(&csString), ui16GetCStringFreeSpace(&csString));
  return 0;
}
