//-----------------------------------------------------------------------------
//
// Copyright (C) 2013-2014 David Hill
//
// See COPYING for license information.
//
//-----------------------------------------------------------------------------
//
// Platform information/selection.
//
//-----------------------------------------------------------------------------

#ifndef GDCC__Platform__Platform_H__
#define GDCC__Platform__Platform_H__


//----------------------------------------------------------------------------|
// Types                                                                      |
//

namespace GDCC
{
   namespace IR
   {
      enum class AddrBase;
      enum class CallType;
   }

   namespace Platform
   {
      //
      // Format
      //
      enum class Format
      {
         None,
         ACSE,
         MgC_NTS,
      };

      //
      // Target
      //
      enum class Target
      {
         None,
         MageCraft,
         ZDoom,
      };
   }
}


//----------------------------------------------------------------------------|
// Global Variables                                                           |
//

namespace GDCC
{
   namespace Platform
   {
      extern Format FormatCur;
      extern Target TargetCur;
   }
}


//----------------------------------------------------------------------------|
// Global Functions                                                           |
//

namespace GDCC
{
   namespace Platform
   {
      unsigned GetByteBitsI();
      unsigned GetWordAlign();
      unsigned GetWordBits();
      unsigned GetWordBytes();
      unsigned GetWordPoint();
      unsigned GetWordShift();

      // Does null have a zero representation?
      bool IsZeroNull_Funct(IR::CallType call);
      bool IsZeroNull_Point(IR::AddrBase addr);
      bool IsZeroNull_StrEn();
   }
}

#endif//GDCC__Platform__Platform_H__
