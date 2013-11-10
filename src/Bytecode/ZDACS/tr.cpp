//-----------------------------------------------------------------------------
//
// Copyright (C) 2013 David Hill
//
// See COPYING for license information.
//
//-----------------------------------------------------------------------------
//
// ZDoom ACS IR code translation.
//
//-----------------------------------------------------------------------------

#include "Info.hpp"

#include "GDCC/IR/Function.hpp"


//----------------------------------------------------------------------------|
// Global Functions                                                           |
//

namespace Bytecode
{
   namespace ZDACS
   {
      //
      // Info::trFunc
      //
      void Info::trFunc()
      {
         trBlock(func->block);

         if(func->defin) switch(func->ctype)
         {
         case GDCC::IR::CallType::Script:
            func->ctype = GDCC::IR::CallType::ScriptI;
            break;

         default: break;
         }
      }
   }
}

// EOF

