//-----------------------------------------------------------------------------
//
// Copyright (C) 2013 David Hill
//
// See COPYING for license information.
//
//-----------------------------------------------------------------------------
//
// Intermediary Representation library import handling.
//
//-----------------------------------------------------------------------------

#ifndef GDCC__IR__Import_H__
#define GDCC__IR__Import_H__

#include "../String.hpp"
#include "../Utility.hpp"

#include <unordered_map>


//----------------------------------------------------------------------------|
// Types                                                                      |
//

namespace GDCC
{
   namespace IR
   {
      //
      // Import
      //
      class Import
      {
      public:
         explicit Import(String glyph);

         String glyph;


         static Import &Get(String glyph);
      };
   }
}


//----------------------------------------------------------------------------|
// Global Functions                                                           |
//

namespace GDCC
{
   namespace IR
   {
      OArchive &operator << (OArchive &out, Import const &in);

      IArchive &operator >> (IArchive &in, Import &out);

      Range<MemItr<std::unordered_map<String, Import>::iterator>> ImportRange();
   }
}

#endif//GDCC__IR__Import_H__

