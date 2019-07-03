#include "CString.h"

//! Function: String Inititalizer
/*!
  Initialize a String.
  \param spString is a string_t pointer.
  \param ui16MaxSize is a 16-Bit integer. This parameter refers to the max size of spString.
  \return Returns ERROR_STRING_NOT_INITIALIZED, ERROR_NO_SPACE_ON_DATABANK or STRING_INITIALIZED.
*/
uint8_t ui8StringInit(string_t* spString, uint16_t ui16MaxSize){
  if (spString == NULL || ui16MaxSize < 2 || spString->cpString != NULL){
    return ERROR_STRING_NOT_INITIALIZED;
  }
  spString->ui16MaxSize = ui16MaxSize;
  spString->cpString = (char*) vpDBAlloc(sizeof(char), ui16MaxSize + 1);
  if (spString->cpString == NULL){
    return ERROR_NO_SPACE_ON_DATABANK;
  }
  memset(spString->cpString, 0, sizeof(char)*(spString->ui16MaxSize + 1));
  spString->ui16StringSize = 0;
  return STRING_INITIALIZED;
}

//! Function: String Deleter
/*!
  Delete a String.
  \param spString is a string_t pointer.
  \return Returns ERROR_STRING_NOT_INITIALIZED, ERROR_STRING_NOT_DEALLOCATED or DELETED_STRING.
*/
uint8_t ui8StringDelete(string_t* spString){
  if (spString == NULL || spString->cpString == NULL){
    return ERROR_STRING_NOT_INITIALIZED;
  }
  vDBFree(&(spString->cpString), sizeof(char), spString->ui16MaxSize + 1);
  if (spString->cpString == NULL){
    return ERROR_STRING_NOT_DEALLOCATED;
  }
  spString->ui16MaxSize = 0;
  spString->ui16StringSize = 0;
  return DELETED_STRING;
}

//! Function: String Data Attacher
/*!
  Put a data into String. Is similar to "+" in C++.
  \param spString is a string_t pointer.
  \param iAmountOfArguments is a int type argument. You must be ignore this argument. See the examples.
  \param ... is anything. You must be use csIntType(), csFloatType(), csCharType(), csOctalType() or csHexType() in these arguments.
  \return Returns ERROR_STRING_NOT_INITIALIZED, ERROR_NO_SPACE_IN_STRING, ERROR_TRUNCATED_STRING or ALL_DATA_ADDED.
*/
uint8_t (ui8StringAdd)(string_t* spString, int iAmountOfArguments, ...){
  if (spString == NULL || spString->cpString == NULL){
    return ERROR_STRING_NOT_INITIALIZED;
  }
  va_list vaMyArguments;
  va_start(vaMyArguments, iAmountOfArguments);
  int iType = 0;
  while (iAmountOfArguments--){
    while(spString->cpString[spString->ui16StringSize] != 0){
      if (spString->ui16StringSize == spString->ui16MaxSize){
        return ERROR_NO_SPACE_IN_STRING;
      }
      spString->ui16StringSize++;
    }
    iType = va_arg(vaMyArguments, int);
    switch (iType){
      case INT_TYPE:
        if (snprintf((char*) (spString->cpString + spString->ui16StringSize), spString->ui16MaxSize - spString->ui16StringSize + 1, "%d", va_arg(vaMyArguments, int)) < 0){
          return ERROR_TRUNCATED_STRING;
        }
        break;
      case OCTAL_TYPE:
        if (snprintf((char*) (spString->cpString + spString->ui16StringSize), spString->ui16MaxSize - spString->ui16StringSize + 1, "%o", va_arg(vaMyArguments, int)) < 0){
          return ERROR_TRUNCATED_STRING;
        }
        break;
      case HEX_TYPE:
        if (snprintf((char*) (spString->cpString + spString->ui16StringSize), spString->ui16MaxSize - spString->ui16StringSize + 1, "%x", va_arg(vaMyArguments, int)) < 0){
          return ERROR_TRUNCATED_STRING;
        }
        break;
      case CHAR_TYPE:
        if (snprintf((char*) (spString->cpString + spString->ui16StringSize), spString->ui16MaxSize - spString->ui16StringSize + 1, "%s", va_arg(vaMyArguments, char*)) < 0){
          return ERROR_TRUNCATED_STRING;
        }
        break;
      case FLOAT_TYPE:
        if (snprintf((char*) (spString->cpString + spString->ui16StringSize), spString->ui16MaxSize - spString->ui16StringSize + 1, "%.2f", va_arg(vaMyArguments, double)) < 0){
          return ERROR_TRUNCATED_STRING;
        }
        break;
    }
  }
  while(spString->cpString[spString->ui16StringSize] != 0){
    spString->ui16StringSize++;
  }
  va_end(vaMyArguments);
  return ALL_DATA_ADDED;
}

//! Function: String Data Attacher
/*!
  This function is similar to sprintf().
  \param spString is a string_t pointer.
  \param iAmountOfArguments is a int type argument. You must be ignore this argument. See the examples.
  \param ... is anything. You must be use csIntType(), csFloatType(), csCharType(), csOctalType() or csHexType() in these arguments.
  \return Returns ERROR_STRING_NOT_INITIALIZED, ERROR_NO_SPACE_IN_STRING, ERROR_TRUNCATED_STRING or ALL_DATA_ADDED.
*/
uint8_t ui8StringPrintf(string_t* spString, const char* cpCharArray, ...){
  if (spString == NULL || spString->cpString == NULL){
    return ERROR_STRING_NOT_INITIALIZED;
  }
  va_list vaMyArguments;
  va_start(vaMyArguments, cpCharArray);
  if (vsnprintf((char*) (spString->cpString + spString->ui16StringSize), spString->ui16MaxSize - spString->ui16StringSize + 1, cpCharArray, vaMyArguments) < 0){
    return ERROR_TRUNCATED_STRING;
  }
  while(spString->cpString[spString->ui16StringSize] != 0){
    spString->ui16StringSize++;
  }
  va_end(vaMyArguments);
  return ALL_DATA_ADDED;
}

//! Function: String Comparer
/*!
  Compare two strings.
  \param spStringA is a string_t pointer.
  \param spStringB is a string_t pointer.
  \return Returns ERROR_STRING_NOT_INITIALIZED, DIFFERENT_STRINGS or IDENTICAL_STRINGS.
*/
uint8_t ui8CompareStrings(string_t* spStringA, string_t* spStringB){
  if (spStringA == NULL || spStringB == NULL || spStringA->cpString == NULL || spStringB->cpString == NULL){
    return ERROR_STRING_NOT_INITIALIZED;
  }
  if (spStringA->ui16StringSize != spStringB->ui16StringSize){
    return DIFFERENT_STRINGS;
  }
  if (strncmp(spStringA->cpString, spStringB->cpString, spStringA->ui16StringSize) != 0){
    return DIFFERENT_STRINGS;
  }
  return IDENTICAL_STRINGS;
}

//! Function: String Size Copier
/*!
  Copy a String.
  \param spString is a string_t pointer.
  \return Returns ERROR_STRING_NOT_INITIALIZED, ERROR_NO_SPACE_IN_STRING or COPIED_STRING.
*/
uint8_t ui8CopyString(string_t* spDestinyString, string_t* spOriginString){
  if (spDestinyString == NULL || spOriginString == NULL  || spDestinyString->cpString == NULL  || spOriginString->cpString == NULL){
    return ERROR_STRING_NOT_INITIALIZED;
  }
  if (spOriginString->ui16MaxSize <= spDestinyString->ui16StringSize){
    return ERROR_NO_SPACE_IN_STRING;
  }
  memset(spDestinyString->cpString, 0, spDestinyString->ui16StringSize);
  memcpy(spDestinyString->cpString, spOriginString->cpString, spOriginString->ui16StringSize);
  spDestinyString->ui16StringSize = strlen(spDestinyString->cpString);
  return COPIED_STRING;
}

//! Function: String Size Eraser
/*!
  Erase a String.
  \param spString is a string_t pointer.
  \return Returns ERROR_STRING_NOT_INITIALIZED or ERASED_STRING.
*/
uint8_t ui8EraseString(string_t* spString){
  if (spString == NULL || spString->cpString == NULL){
    return ERROR_STRING_NOT_INITIALIZED;
  }
  memset(spString->cpString, 0, spString->ui16StringSize);
  spString->ui16StringSize = 0;
  return ERASED_STRING;
}

//! Function: String Free Space Getter
/*!
  Get String free scpace.
  \param spString is a string_t pointer.
  \return Returns the free space of String or ERROR_STRING_NOT_INITIALIZED.
*/
uint16_t ui16GetStringFreeSpace(string_t* spString){
  if (spString == NULL || spString->cpString == NULL){
    return ERROR_STRING_NOT_INITIALIZED;
  }
  return spString->ui16MaxSize - spString->ui16StringSize;
}

//! Function: String Max Space Getter
/*!
  Get String max scpace.
  \param spString is a string_t pointer.
  \return Returns the max space of String or ERROR_STRING_NOT_INITIALIZED.
*/
uint16_t ui16GetStringMaxSize(string_t* spString){
  if (spString == NULL || spString->cpString == NULL){
    return ERROR_STRING_NOT_INITIALIZED;
  }
  return spString->ui16MaxSize;
}

//! Function: String Size Getter
/*!
  Get String size.
  \param spString is a string_t pointer.
  \return Returns the size of String or ERROR_STRING_NOT_INITIALIZED.
*/
uint16_t ui16GetStringSize(string_t* spString){
  if (spString == NULL || spString->cpString == NULL){
    return ERROR_STRING_NOT_INITIALIZED;
  }
  return spString->ui16StringSize;
}

//! Function: String Converter (To char array)
/*!
  Convert a String to char array.
  \param spString is a string_t pointer.
  \return Returns the char array or NULL, case spString is NULL.
*/
char* cpStringToCharArray(string_t* spString){
  if (spString == NULL || spString->cpString == NULL){
    return NULL;
  }
  return spString->cpString;
}

//! Function: String Converter (To char)
/*!
  Get a String char.
  \param spString is a string_t pointer.
  \param ui16Position is a 16-Bit integer.
  \return Returns the char or 0 when errors occours.
*/
char cStringToChar(string_t* spString, uint16_t ui16Position){
  if (spString == NULL || spString->cpString == NULL){
    return ERROR_STRING_NOT_INITIALIZED;
  }
  if (ui16Position >= spString->ui16StringSize){
    return 0;
  }
  return spString->cpString[ui16Position];
}
