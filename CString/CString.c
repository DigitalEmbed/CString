#include "CString.h"

//! Function: CString Inititalizer
/*!
  Initialize a CString.
  \param cspString is a cstring_t pointer.
  \param ui16MaxSize is a 16-Bit integer. This parameter refers to the max size of cspString.
  \return Returns ERROR_STRING_NOT_CREATED, ERROR_NO_SPACE_ON_DATABANK or STRING_CREATED.
*/
uint8_t ui8CStringInit(cstring_t* cspString, uint16_t ui16MaxSize){
  if (cspString == NULL || ui16MaxSize < 2 || cspString->cpString != NULL){
    return ERROR_STRING_NOT_CREATED;
  }
  cspString->ui16MaxSize = ui16MaxSize;
  cspString->cpString = (char*) vpDBAlloc(sizeof(char), ui16MaxSize + 1);
  if (cspString->cpString == NULL){
    return ERROR_NO_SPACE_ON_DATABANK;
  }
  memset(cspString->cpString, 0, sizeof(char)*(cspString->ui16MaxSize + 1));
  cspString->ui16ActualPosition = 0;
  cspString->ui16StringSize = 0;
  return STRING_CREATED;
}

//! Function: CString Deleter
/*!
  Delete a CString.
  \param cspString is a cstring_t pointer.
  \return Returns ERROR_STRING_NOT_CREATED, ERROR_STRING_NOT_DEALLOCATED or DELETED_STRING.
*/
uint8_t ui8CStringDelete(cstring_t* cspString){
  if (cspString == NULL || cspString->cpString == NULL){
    return ERROR_STRING_NOT_CREATED;
  }
  vDBFree(&(cspString->cpString), sizeof(char), cspString->ui16MaxSize + 1);
  if (cspString->cpString == NULL){
    return ERROR_STRING_NOT_DEALLOCATED;
  }
  cspString->ui16ActualPosition = 0;
  cspString->ui16MaxSize = 0;
  cspString->ui16StringSize = 0;
  return DELETED_STRING;
}

//! Function: CString Data Attacher
/*!
  Put a data into CString.
  \param cspString is a cstring_t pointer.
  \param iAmountOfArguments is a int type argument. You must be ignore this argument. See the examples.
  \param ... is anything. You must be use csIntType(), csFloatType(), csCharType(), csOctalType() or csHexType() in these arguments.
  \return Returns ERROR_STRING_NOT_CREATED, ERROR_NO_SPACE_IN_STRING, ERROR_TRUNCATED_STRING or ALL_DATA_ADDED.
*/
uint8_t (ui8CStringPutData)(cstring_t* cspString, int iAmountOfArguments, ...){
  if (cspString == NULL || cspString->cpString == NULL){
    return ERROR_STRING_NOT_CREATED;
  }
  va_list vaMyArguments;
  va_start(vaMyArguments, iAmountOfArguments);
  int iType = 0;
  while (iAmountOfArguments--){
    while(cspString->cpString[cspString->ui16ActualPosition] != 0){
      if (cspString->ui16ActualPosition == cspString->ui16MaxSize){
        return ERROR_NO_SPACE_IN_STRING;
      }
      cspString->ui16ActualPosition++;
    }
    iType = va_arg(vaMyArguments, int);
    switch (iType){
      case INT_TYPE:
        if (snprintf((char*) (cspString->cpString + cspString->ui16ActualPosition), cspString->ui16MaxSize - cspString->ui16ActualPosition + 1, "%d", va_arg(vaMyArguments, int)) < 0){
          return ERROR_TRUNCATED_STRING;
        }
        break;
      case OCTAL_TYPE:
        if (snprintf((char*) (cspString->cpString + cspString->ui16ActualPosition), cspString->ui16MaxSize - cspString->ui16ActualPosition + 1, "%o", va_arg(vaMyArguments, int)) < 0){
          return ERROR_TRUNCATED_STRING;
        }
        break;
      case HEX_TYPE:
        if (snprintf((char*) (cspString->cpString + cspString->ui16ActualPosition), cspString->ui16MaxSize - cspString->ui16ActualPosition + 1, "%x", va_arg(vaMyArguments, int)) < 0){
          return ERROR_TRUNCATED_STRING;
        }
        break;
      case CHAR_TYPE:
        if (snprintf((char*) (cspString->cpString + cspString->ui16ActualPosition), cspString->ui16MaxSize - cspString->ui16ActualPosition + 1, "%s", va_arg(vaMyArguments, char*)) < 0){
          return ERROR_TRUNCATED_STRING;
        }
        break;
      case FLOAT_TYPE:
        if (snprintf((char*) (cspString->cpString + cspString->ui16ActualPosition), cspString->ui16MaxSize - cspString->ui16ActualPosition + 1, "%.2f", va_arg(vaMyArguments, double)) < 0){
          return ERROR_TRUNCATED_STRING;
        }
        break;
    }
  }
  while(cspString->cpString[cspString->ui16ActualPosition] != 0){
    cspString->ui16ActualPosition++;
  }
  cspString->ui16StringSize = cspString->ui16ActualPosition;
  va_end(vaMyArguments);
  return ALL_DATA_ADDED;
}

//! Function: CString Free Space Getter
/*!
  Get CString free scpace.
  \param cspString is a cstring_t pointer.
  \return Returns the free space of CString or ERROR_STRING_NOT_CREATED.
*/
uint8_t ui8GetCStringFreeSpace(cstring_t* cspString){
  if (cspString == NULL || cspString->cpString == NULL){
    return ERROR_STRING_NOT_CREATED;
  }
  return cspString->ui16MaxSize - cspString->ui16StringSize;
}

//! Function: CString Max Space Getter
/*!
  Get CString max scpace.
  \param cspString is a cstring_t pointer.
  \return Returns the max space of CString or ERROR_STRING_NOT_CREATED.
*/
uint8_t ui8GetCStringMaxSize(cstring_t* cspString){
  if (cspString == NULL || cspString->cpString == NULL){
    return ERROR_STRING_NOT_CREATED;
  }
  return cspString->ui16MaxSize;
}

//! Function: CString Size Getter
/*!
  Get CString size.
  \param cspString is a cstring_t pointer.
  \return Returns the size of CString or ERROR_STRING_NOT_CREATED.
*/
uint8_t ui8GetCStringSize(cstring_t* cspString){
  if (cspString == NULL || cspString->cpString == NULL){
    return ERROR_STRING_NOT_CREATED;
  }
  return cspString->ui16StringSize;
}

//! Function: CString Comparer
/*!
  Compare two strings.
  \param cspStringA is a cstring_t pointer.
  \param cspStringB is a cstring_t pointer.
  \return Returns ERROR_STRING_NOT_CREATED, DIFFERENT_STRINGS or IDENTICAL_STRINGS.
*/
uint8_t ui8CompareCStrings(cstring_t* cspStringA, cstring_t* cspStringB){
  if (cspStringA == NULL || cspStringB == NULL || cspStringA->cpString == NULL || cspStringB->cpString == NULL){
    return ERROR_STRING_NOT_CREATED;
  }
  if (cspStringA->ui16StringSize != cspStringB->ui16StringSize){
    return DIFFERENT_STRINGS;
  }
  if (strncmp(cspStringA->cpString, cspStringB->cpString, cspStringA->ui16StringSize) != 0){
    return DIFFERENT_STRINGS;
  }
  return IDENTICAL_STRINGS;
}

//! Function: CString Size Copier
/*!
  Copy a CString.
  \param cspString is a cstring_t pointer.
  \return Returns ERROR_STRING_NOT_CREATED, ERROR_NO_SPACE_IN_STRING or COPIED_STRING.
*/
uint8_t ui8CopyCString(cstring_t* cspDestinyString, cstring_t* cspOriginString){
  if (cspDestinyString == NULL || cspOriginString == NULL  || cspDestinyString->cpString == NULL  || cspOriginString->cpString == NULL){
    return ERROR_STRING_NOT_CREATED;
  }
  if (cspDestinyString->ui16MaxSize <= cspOriginString->ui16StringSize){
    return ERROR_NO_SPACE_IN_STRING;
  }
  memset(cspDestinyString->cpString, 0, cspDestinyString->ui16StringSize);
  memcpy(cspDestinyString->cpString, cspOriginString->cpString, cspOriginString->ui16StringSize);
  return COPIED_STRING;
}

//! Function: CString Size Eraser
/*!
  Erase a CString.
  \param cspString is a cstring_t pointer.
  \return Returns ERROR_STRING_NOT_CREATED or ERASED_STRING.
*/
uint8_t ui8EraseCString(cstring_t* cspString){
  if (cspString == NULL || cspString->cpString == NULL){
    return ERROR_STRING_NOT_CREATED;
  }
  memset(cspString->cpString, 0, cspString->ui16StringSize);
  cspString->ui16StringSize = 0;
  cspString->ui16ActualPosition = 0;
  return ERASED_STRING;
}

//! Function: CString Converter (To char array)
/*!
  Convert a CString to char array.
  \param cspString is a cstring_t pointer.
  \return Returns the char array or NULL, case cspString is NULL.
*/
char* cpCStringToCharArray(cstring_t* cspString){
  if (cspString == NULL || cspString->cpString == NULL){
    return NULL;
  }
  return cspString->cpString;
}

//! Function: CString Converter (To char)
/*!
  Get a CString char.
  \param cspString is a cstring_t pointer.
  \param ui16Position is a 16-Bit integer.
  \return Returns the char or 0 when errors occours.
*/
char cCStringToChar(cstring_t* cspString, uint16_t ui16Position){
  if (cspString == NULL || cspString->cpString == NULL){
    return ERROR_STRING_NOT_CREATED;
  }
  if (ui16Position >= cspString->ui16StringSize){
    return 0;
  }
  return cspString->cpString[ui16Position];
}
