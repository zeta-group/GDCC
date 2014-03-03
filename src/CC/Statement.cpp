//-----------------------------------------------------------------------------
//
// Copyright (C) 2014 David Hill
//
// See COPYING for license information.
//
//-----------------------------------------------------------------------------
//
// C statements.
//
//-----------------------------------------------------------------------------

#include "CC/Statement.hpp"

#include "Core/Exception.hpp"


//----------------------------------------------------------------------------|
// Global Functions                                                           |
//

namespace GDCC
{
   namespace CC
   {
      // Stubs.

      AST::Statement::CRef StatementCreate_Break(
         Core::Array<Core::String> const &, Core::Origin pos,
         LocalScope *)
         {throw Core::ExceptStr(pos, "stub");}
      AST::Statement::CRef StatementCreate_Break(
         Core::Array<Core::String>      &&, Core::Origin pos,
         LocalScope *)
         {throw Core::ExceptStr(pos, "stub");}

      AST::Statement::CRef StatementCreate_Continue(
         Core::Array<Core::String> const &, Core::Origin pos,
         LocalScope *)
         {throw Core::ExceptStr(pos, "stub");}
      AST::Statement::CRef StatementCreate_Continue(
         Core::Array<Core::String>      &&, Core::Origin pos,
         LocalScope *)
         {throw Core::ExceptStr(pos, "stub");}

      AST::Statement::CRef StatementCreate_Decl(Core::Origin pos, Scope *)
         {throw Core::ExceptStr(pos, "stub");}

      AST::Statement::CRef StatementCreate_Do(
         Core::Array<Core::String> const &, Core::Origin pos,
         LocalScope *, AST::Statement const *, AST::Exp const *)
         {throw Core::ExceptStr(pos, "stub");}
      AST::Statement::CRef StatementCreate_Do(
         Core::Array<Core::String>      &&, Core::Origin pos,
         LocalScope *, AST::Statement const *, AST::Exp const *)
         {throw Core::ExceptStr(pos, "stub");}

      AST::Statement::CRef StatementCreate_For(
         Core::Array<Core::String> const &, Core::Origin pos,
         LocalScope *, AST::Statement const *, AST::Exp const *,
         AST::Statement const *, AST::Statement const *)
         {throw Core::ExceptStr(pos, "stub");}
      AST::Statement::CRef StatementCreate_For(
         Core::Array<Core::String>      &&, Core::Origin pos,
         LocalScope *, AST::Statement const *, AST::Exp const *,
         AST::Statement const *, AST::Statement const *)
         {throw Core::ExceptStr(pos, "stub");}

      AST::Statement::CRef StatementCreate_Goto(
         Core::Array<Core::String> const &, Core::Origin pos,
         LocalScope *, Core::String)
         {throw Core::ExceptStr(pos, "stub");}
      AST::Statement::CRef StatementCreate_Goto(
         Core::Array<Core::String>      &&, Core::Origin pos,
         LocalScope *, Core::String)
         {throw Core::ExceptStr(pos, "stub");}

      AST::Statement::CRef StatementCreate_If(
         Core::Array<Core::String> const &, Core::Origin pos,
         AST::Exp const *, AST::Statement const *)
         {throw Core::ExceptStr(pos, "stub");}
      AST::Statement::CRef StatementCreate_If(
         Core::Array<Core::String>      &&, Core::Origin pos,
         AST::Exp const *, AST::Statement const *)
         {throw Core::ExceptStr(pos, "stub");}

      AST::Statement::CRef StatementCreate_If(
         Core::Array<Core::String> const &, Core::Origin pos,
         AST::Exp const *, AST::Statement const *,
         AST::Statement const *)
         {throw Core::ExceptStr(pos, "stub");}
      AST::Statement::CRef StatementCreate_If(
         Core::Array<Core::String>      &&, Core::Origin pos,
         AST::Exp const *, AST::Statement const *,
         AST::Statement const *)
         {throw Core::ExceptStr(pos, "stub");}

      AST::Statement::CRef StatementCreate_Switch(
         Core::Array<Core::String> const &, Core::Origin pos,
         LocalScope *, AST::Exp const *, AST::Statement const *)
         {throw Core::ExceptStr(pos, "stub");}
      AST::Statement::CRef StatementCreate_Switch(
         Core::Array<Core::String>      &&, Core::Origin pos,
         LocalScope *, AST::Exp const *, AST::Statement const *)
         {throw Core::ExceptStr(pos, "stub");}

      AST::Statement::CRef StatementCreate_While(
         Core::Array<Core::String> const &, Core::Origin pos,
         LocalScope *, AST::Exp const *, AST::Statement const *)
         {throw Core::ExceptStr(pos, "stub");}
      AST::Statement::CRef StatementCreate_While(
         Core::Array<Core::String>      &&, Core::Origin pos,
         LocalScope *, AST::Exp const *, AST::Statement const *)
         {throw Core::ExceptStr(pos, "stub");}
   }
}

// EOF
