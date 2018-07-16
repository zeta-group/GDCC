//-----------------------------------------------------------------------------
//
// Copyright (C) 2016-2018 David Hill
//
// See COPYING for license information.
//
//-----------------------------------------------------------------------------
//
// Archive exceptions.
//
//-----------------------------------------------------------------------------

#ifndef GDCC__AR__Exception_H__
#define GDCC__AR__Exception_H__

#include "../AR/Types.hpp"

#include "../Core/Exception.hpp"


//----------------------------------------------------------------------------|
// Types                                                                      |
//

namespace GDCC::AR
{
   //
   // ReadError
   //
   class ReadError : public Core::Exception
   {
   public:
      ReadError(char const *err_) noexcept : err{err_} {}

      virtual void genMsg() const;

   private:
      char const *err;
   };
}

#endif//GDCC__AR__Exception_H__

