//-----------------------------------------------------------------------------
//
// Copyright (C) 2014-2018 David Hill
//
// See COPYING for license information.
//
//-----------------------------------------------------------------------------
//
// C soft boolean conversion expressions.
//
//-----------------------------------------------------------------------------

#include "CC/Exp/Convert/BoolSoft.hpp"

#include "CC/Type.hpp"

#include "Core/Exception.hpp"

#include "IR/Block.hpp"

#include "Platform/Platform.hpp"

#include "SR/Type.hpp"


//----------------------------------------------------------------------------|
// Extern Functions                                                           |
//

namespace GDCC::CC
{
   //
   // Exp_ConvertBoolSoft_Fixed::v_genStmnt
   //
   void Exp_ConvertBoolSoft_Fixed::v_genStmnt(SR::GenStmntCtx const &ctx,
      SR::Arg const &dst) const
   {
      if(GenStmntNul(this, ctx, dst)) return;

      exp->genStmntStk(ctx);

      ctx.block.setArgSize();

      for(auto n = exp->getType()->getSizeWords(); --n;)
         ctx.block.addStmnt(IR::Code::BOrI,
            IR::Block::Stk(), IR::Block::Stk(), IR::Block::Stk());

      // Move to destination.
      GenStmnt_MovePart(this, ctx, dst, false, true);
   }

   //
   // Exp_ConvertBoolSoft_Float::v_genStmnt
   //
   void Exp_ConvertBoolSoft_Float::v_genStmnt(SR::GenStmntCtx const &ctx,
      SR::Arg const &dst) const
   {
      if(GenStmntNul(this, ctx, dst)) return;

      exp->genStmntStk(ctx);

      auto expType = exp->getType();
      auto bitsIF = expType->getSizeBitsI() + expType->getSizeBitsF();

      ctx.block.setArgSize();

      ctx.block.addStmnt(IR::Code::BAnd,
         IR::Block::Stk(), IR::Block::Stk(),
         (Core::FastU(1) << (bitsIF % Platform::GetWordBits())) - 1);

      for(auto n = exp->getType()->getSizeWords(); --n;)
         ctx.block.addStmnt(IR::Code::BOrI,
            IR::Block::Stk(), IR::Block::Stk(), IR::Block::Stk());

      // Move to destination.
      GenStmnt_MovePart(this, ctx, dst, false, true);
   }

   //
   // Exp_ConvertBoolSoft_PtrInv::v_genStmnt
   //
   void Exp_ConvertBoolSoft_PtrInv::v_genStmnt(SR::GenStmntCtx const &ctx,
      SR::Arg const &dst) const
   {
      if(GenStmntNul(this, ctx, dst)) return;

      exp->genStmntStk(ctx);

      ctx.block.setArgSize();

      for(auto n = exp->getType()->getSizeWords(); --n;)
         ctx.block.addStmnt(IR::Code::BAnd,
            IR::Block::Stk(), IR::Block::Stk(), IR::Block::Stk());

      ctx.block.addStmnt(IR::Code::BNot,
         IR::Block::Stk(), IR::Block::Stk());

      // Move to destination.
      GenStmnt_MovePart(this, ctx, dst, false, true);
   }

   //
   // ExpConvert_BoolSoft
   //
   SR::Exp::CRef ExpConvert_BoolSoft(SR::Exp const *e, Core::Origin pos)
   {
      // TODO: Bitfield conversion with mask, but not shift.
      SR::Exp::CRef exp  = ExpPromo_LValue(e, pos);
      auto          type = exp->getType();

      if(type->isCTypeFixed() || type->isCTypeInteg())
      {
         if(type->getSizeWords() == 1)
            return exp;

         return Exp_ConvertBoolSoft_Fixed::Create(TypeBoolSoft, exp, pos);
      }

      if(type->isCTypeRealFlt())
         return Exp_ConvertBoolSoft_Float::Create(TypeBoolSoft, exp, pos);

      if(type->isTypePointer())
      {
         if(Platform::IsZeroNull_Point(type->getBaseType()->getQualAddr().base))
         {
            if(type->getSizeWords() == 1)
               return exp;

            return Exp_ConvertBoolSoft_Fixed::Create(TypeBoolSoft, exp, pos);
         }
         else
            return Exp_ConvertBoolSoft_PtrInv::Create(TypeBoolSoft, exp, pos);
      }

      Core::Error(pos, "soft bool stub");
   }
}

// EOF

