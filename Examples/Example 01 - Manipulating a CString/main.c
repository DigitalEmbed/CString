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
    Creating Strings.
  */
  xStringCreate(sString);

  /*!
    Initializing Strings.
  */
  uint8_t ui8StatusString = ui8StringInit(&sString,             //Address of sString
                                          50);                  //Max size of sString

  if (ui8StatusString != STRING_INITIALIZED){
    return 2;
  }

  /*!
    Editing sString.
  */
  uint8_t ui8SensorA = 236;
  uint8_t ui8SensorB = 178;
  uint8_t ui8SetPoint = 2*(ui8SensorA - ui8SensorB);

  /*!
    Adding data on sString like sprintf function...
  */
  if (ui8StringPrintf(&sString, "SensorA:  %d\nSensorB:  %d", ui8SensorA, ui8SensorB) != ALL_DATA_ADDED){
    return 3;
  }

  /*!
    Adding data on sString like C++ string function...
    (C++) sString = "\nSetPoint: " + ui8SetPoint;
  */
  if (ui8StringAdd(&sString, sCharType("\nSetPoint: "), sIntType(ui8SetPoint)) != ALL_DATA_ADDED){
    return 4;
  }

  /*!
    Printing sString.
  */
  printf("%s", cpStringToCharArray(&sString));
  printf("\n\nString max size: %d\nString size: %d\nString free space: %d", ui16GetStringMaxSize(&sString), ui16GetStringSize(&sString), ui16GetStringFreeSpace(&sString));
  return 0;
}
