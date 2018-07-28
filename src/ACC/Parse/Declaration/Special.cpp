//-----------------------------------------------------------------------------
//
// Copyright (C) 2015-2018 David Hill
//
// See COPYING for license information.
//
//-----------------------------------------------------------------------------
//
// ACS special-declaration parsing.
//
//-----------------------------------------------------------------------------

#include "ACC/Parse.hpp"

#include "ACC/Scope.hpp"

#include "CC/Exp.hpp"
#include "CC/Scope/Global.hpp"
#include "CC/Type.hpp"

#include "Core/Exception.hpp"
#include "Core/TokenStream.hpp"

#include "IR/CallType.hpp"
#include "IR/Exp.hpp"
#include "IR/Linkage.hpp"

#include "SR/Attribute.hpp"
#include "SR/Function.hpp"
#include "SR/Statement.hpp"
#include "SR/Type.hpp"


//----------------------------------------------------------------------------|
// Static Functions                                                           |
//

namespace GDCC::ACC
{
   //
   // ParseAddress
   //
   static void ParseAddress(Parser &ctx, CC::Scope &scope, SR::Attribute &attr)
   {
      // special-address:
      //    integer-constant :
      //    - integer-constant :
      //    { integer-constant } :
      //    { integer-constant , integer-constant } :
      if(ctx.in.peek(Core::TOK_NumInt))
      {
         attr.callt = IR::CallType::Special;
         attr.addrI = ctx.getExp_Prim(scope)->getIRExp();
      }
      else if(ctx.in.drop(Core::TOK_Sub))
      {
         attr.callt = IR::CallType::Native;
         attr.addrI = ctx.getExp_Prim(scope)->getIRExp();
      }
      else if(ctx.in.drop(Core::TOK_BraceO))
      {
         attr.callt = IR::CallType::AsmFunc;

         if(!ctx.in.peek(Core::TOK_NumInt))
            Core::ErrorExpect("integer-constant", ctx.in.peek());

         attr.addrI = ctx.getExp_Prim(scope)->getIRExp();

         if(ctx.in.drop(Core::TOK_Comma))
         {
            if(!ctx.in.peek(Core::TOK_NumInt))
               Core::ErrorExpect("integer-constant", ctx.in.peek());

            attr.addrL = ctx.getExp_Prim(scope)->getIRExp();
         }

         ctx.expect(Core::TOK_BraceC);
      }
      else
         Core::ErrorExpect("special-address", ctx.in.peek());

      ctx.expect(Core::TOK_Colon);
   }

   //
   // ParseParameters
   //
   static void ParseParameters(Parser &ctx, CC::Scope &scope, SR::Attribute &attr)
   {
      // special-parameters:
      //    integer-constant
      //    integer-constant , integer-constant
      //    integer-constant , parameter-type-list
      //    parameter-type-list
      if(ctx.in.peek(Core::TOK_NumInt))
      {
         auto pos    = ctx.in.peek().pos;
         auto argMin = CC::ExpToFastU(ctx.getExp_Prim(scope));

         SR::TypeSet::CPtr types;
         if(ctx.in.drop(Core::TOK_Comma))
         {
            if(ctx.in.peek(Core::TOK_NumInt))
            {
               auto argMax = CC::ExpToFastU(ctx.getExp_Prim(scope));

               Core::Array<SR::Type::CRef> param{argMax, CC::TypeIntegPrS};

               types = SR::TypeSet::Get(param.data(), param.size(), false);
            }
            else
               types = std::get<0>(ctx.getTypeList(scope));
         }
         else
         {
            Core::Array<SR::Type::CRef> param{argMin, CC::TypeIntegPrS};

            types = SR::TypeSet::Get(param.data(), param.size(), false);
         }

         if(argMin > types->size())
            Core::Error(pos, "more minimum args than actual args");

         attr.type     = attr.type->getTypeFunction(types, attr.callt);
         attr.paramOpt = types->size() - argMin;
      }
      else
      {
         auto types = std::get<0>(ctx.getTypeList(scope));
         attr.type = attr.type->getTypeFunction(types, attr.callt);
      }
   }
}


//----------------------------------------------------------------------------|
// Extern Functions                                                           |
//

namespace GDCC::ACC
{
   //
   // Parser::getDecl_Special
   //
   SR::Statement::CRef Parser::getDecl_Special(Scope_Global &scope)
   {
      auto pos = expect(Core::TOK_KeyWrd, Core::STR_special).pos;

      // special-list:
      //    special-item
      //    special-list , special-item
      do
      {
         SR::Attribute attr;
         attr.linka = IR::Linkage::ExtACS;

         // special-item:
         //    type-name(opt) special-address identifier
         //       ( special-parameters )

         // type-name(opt)
         if(isType(scope))
         {
            attr.type = getType(scope);
         }
         else
         {
            attr.type = CC::TypeIntegPrS;
         }

         // special-address
         ParseAddress(*this, scope, attr);

         // identifier
         attr.setName(expectIdenti());

         // (
         expect(Core::TOK_ParenO);

         ParseParameters(*this, scope, attr);

         // )
         expect(Core::TOK_ParenC);

         // Check compatibility with existing symbol, if any.
         if(auto lookup = scope.find(attr.name))
         {
            if(lookup.res != CC::Lookup::Func)
               Core::Error(attr.namePos, "name redefined as different kind of symbol");

            if(lookup.resFunc->retrn != attr.type->getBaseType())
               Core::Error(attr.namePos, "function redeclared with different return type");
         }

         auto fn = scope.getFunction(attr);

         if(attr.addrI)
            fn->valueInt = attr.addrI;

         if(attr.addrL)
            fn->valueLit = attr.addrL;

         scope.add(attr.name, fn);
      }
      while(in.drop(Core::TOK_Comma));

      expect(Core::TOK_Semico);

      return SR::StatementCreate_Empty(pos);
   }
}

// EOF

