// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: 2017-2019 Alejandro Sirgo Rica & Contributors

#include "toolfactory.h"
#include "accept/accepttool.h"
#include "arrow/arrowtool.h"
#include "circle/circletool.h"
#include "circlecount/circlecounttool.h"
#include "copy/copytool.h"
#include "exit/exittool.h"
#include "line/linetool.h"
#include "pencil/penciltool.h"
#include "pin/pintool.h"
#include "pixelate/pixelatetool.h"
#include "rectangle/rectangletool.h"
#include "save/savetool.h"
#include "selection/selectiontool.h"
#include "text/texttool.h"
#include "undo/undotool.h"

ToolFactory::ToolFactory(QObject* parent)
  : QObject(parent)
{}

CaptureTool* ToolFactory::CreateTool(CaptureTool::Type t, QObject* parent)
{
#define if_TYPE_return_TOOL(TYPE, TOOL)                                        \
    case CaptureTool::TYPE:                                                    \
        return new TOOL(parent)

    switch (t) {
        if_TYPE_return_TOOL(TYPE_PENCIL, PencilTool);
        if_TYPE_return_TOOL(TYPE_DRAWER, LineTool);
        if_TYPE_return_TOOL(TYPE_ARROW, ArrowTool);
        if_TYPE_return_TOOL(TYPE_SELECTION, SelectionTool);
        if_TYPE_return_TOOL(TYPE_RECTANGLE, RectangleTool);
        if_TYPE_return_TOOL(TYPE_CIRCLE, CircleTool);
        if_TYPE_return_TOOL(TYPE_UNDO, UndoTool);
        if_TYPE_return_TOOL(TYPE_COPY, CopyTool);
        if_TYPE_return_TOOL(TYPE_SAVE, SaveTool);
        if_TYPE_return_TOOL(TYPE_EXIT, ExitTool);
        if_TYPE_return_TOOL(TYPE_PIXELATE, PixelateTool);
        if_TYPE_return_TOOL(TYPE_PIN, PinTool);
        if_TYPE_return_TOOL(TYPE_TEXT, TextTool);
        if_TYPE_return_TOOL(TYPE_CIRCLECOUNT, CircleCountTool);
        if_TYPE_return_TOOL(TYPE_ACCEPT, AcceptTool);
        default:
            return nullptr;
    }
}
