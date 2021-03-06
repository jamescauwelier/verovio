/////////////////////////////////////////////////////////////////////////////
// Name:        accid.cpp
// Author:      Laurent Pugin
// Created:     2014
// Copyright (c) Authors and others. All rights reserved.
/////////////////////////////////////////////////////////////////////////////

#include "accid.h"

//----------------------------------------------------------------------------

#include <assert.h>

//----------------------------------------------------------------------------

#include "functorparams.h"
#include "note.h"

namespace vrv {

//----------------------------------------------------------------------------
// Accid
//----------------------------------------------------------------------------

Accid::Accid() : LayerElement("accid-"), PositionInterface(), AttAccidental(), AttAccidLog(), AttColor()
{

    RegisterInterface(PositionInterface::GetAttClasses(), PositionInterface::IsInterface());
    RegisterAttClass(ATT_ACCIDENTAL);
    RegisterAttClass(ATT_ACCIDLOG);
    RegisterAttClass(ATT_COLOR);

    Reset();
}

Accid::~Accid()
{
}

void Accid::Reset()
{
    LayerElement::Reset();
    PositionInterface::Reset();
    ResetAccidental();
    ResetAccidLog();
    ResetColor();
}

//----------------------------------------------------------------------------
// Functor methods
//----------------------------------------------------------------------------

int Accid::PreparePointersByLayer(FunctorParams *functorParams)
{
    Note *note = dynamic_cast<Note *>(this->GetFirstParent(NOTE, MAX_ACCID_DEPTH));
    if (!note) {
        return FUNCTOR_CONTINUE;
    }

    if (note->m_drawingAccid != NULL) {
        note->ResetDrawingAccid();
    }
    note->m_drawingAccid = this;

    return FUNCTOR_CONTINUE;
}

} // namespace vrv
