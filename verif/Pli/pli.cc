/*
###############################################################################
#   Licensing information found at: 
#     https://github.com/matthamptonasic/Hardware/
#   In file LICENSING.md
###############################################################################
#
#   File          :   pli.cc 
#   Creator       :   Matt Hampton (matthamptonasic@gmail.com)
#   Owner         :   Matt Hampton (matthamptonasic@gmail.com)
#   Creation Date :   09/21/16
#   Description   :   
#
###############################################################################
*/

#include "pli.h"

// ====================================
// ===**  Private Static Members  **===
// ====================================


// ===============================
// ===**  Public Properties  **===
// ===============================


// ============================
// ===**  Public Methods  **===
// ============================
Vpi::SCALAR_VAL Pli::GetScalar(vpiHandle iHndl)
{
  Vpi::SCALAR_VAL retVal = Vpi::SCALAR_VAL::DONT_CARE;
  
  if(iHndl == NULL)
  {
    // TBD - log error message.
    return retVal;
  }
  Vpi::OBJECT type = GetType(iHndl);
  switch(type) {
    case Vpi::OBJECT::NET:
    case Vpi::OBJECT::NET_ARRAY:
    case Vpi::OBJECT::REG:
    case Vpi::OBJECT::REG_ARRAY:
    case Vpi::OBJECT::PART_SELECT:
    case Vpi::OBJECT::CONSTANT:
    case Vpi::OBJECT::INTEGER_VAR:
    case Vpi::OBJECT::TIME_VAR:
    case Vpi::OBJECT::REAL_VAR:
    case Vpi::OBJECT::FUNCTION:
    case Vpi::OBJECT::SYS_FUNC_CALL:
    case Vpi::OBJECT::MEMORY_WORD:
    case Vpi::OBJECT::VARIABLES:
      vpi_printf("Scalar type is %d.\n", type);
      break;
    default:
    // TBD - log error message.
    // Object type was not a value type.
      return retVal;
  }


  // void vpi_get_value(vpiHandle iHndl, p_vpi_value oValue);
  Vpi::p_vpi_value data = new Vpi::t_vpi_value();
  data->format = Vpi::VALUE_FORMAT::SCALAR;
  Vpi::vpi_get_value(iHndl, data);

  retVal = data->value.scalar;
  delete data;

  return retVal;
}

UInt32 Pli::GetVector(vpiHandle iHndl)
{
  UInt32 retVal = 0xffffffff;
  if(iHndl == NULL)
  {
    // TBD - log error message.
    return retVal;
  }

  Int32 vec_size = Vpi::vpi_get(Vpi::PROPERTY::SIZE, iHndl);
  if(vec_size <= 0)
  {
    // TBD - log error message.
    return retVal;
  }
  

  Vpi::p_vpi_value data = new Vpi::t_vpi_value();
  data->format = Vpi::VALUE_FORMAT::VECTOR;
  Vpi::vpi_get_value(iHndl, data);

  Int32 nbReads = (vec_size - 1) / 32 + 1;

  for(Int32 ii=0; ii<nbReads; ii++)
  {
    Int32 aVal = data->value.vector[ii].aval;
    Int32 bVal = data->value.vector[ii].bval;
    retVal = aVal; 
  }
  return retVal;
}

Vpi::OBJECT Pli::GetType(vpiHandle iHndl)
{
  if(iHndl == NULL)
  {
    return Vpi::OBJECT::UNKNOWN;
  }
  return (Vpi::OBJECT)Vpi::vpi_get(Vpi::PROPERTY::TYPE, iHndl);
}

vector<string> * Pli::GetCommandLineArgs()
{
  Vpi::p_vpi_vlog_info l_info = new Vpi::t_vpi_vlog_info();
  Vpi::vpi_get_vlog_info(l_info);
  UInt32 l_size = l_info->argc;
  vector<string> * retVal = new vector<string>(l_size, "");
  for(UInt32 ii=0; ii<l_size; ii++)
  {
    retVal->at(ii) = string(l_info->argv[ii]);
  }
  return retVal;
}

//
// =============================
// ===**  Private Methods  **===
// =============================

