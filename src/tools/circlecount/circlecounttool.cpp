// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: 2017-2019 Alejandro Sirgo Rica & Contributors

#include "circlecounttool.h"
#include "colorutils.h"
#include <QPainter>
#include <QPainterPath>

namespace {
#define PADDING_VALUE 2
#define RADIUS 18
}

CircleCountTool::CircleCountTool(QObject* parent)
  : AbstractTwoPointTool(parent)
  , m_valid(false)
{}

QIcon CircleCountTool::icon(const QColor& background, bool inEditor) const
{
    Q_UNUSED(inEditor)
    return QIcon(iconPath(background) + "circlecount-outline.svg");
}

QString CircleCountTool::info()
{
    m_tempString = QString("%1 - %2").arg(name()).arg(count());
    return m_tempString;
}

bool CircleCountTool::isValid() const
{
    return m_valid;
}

QRect CircleCountTool::mousePreviewRect(const CaptureContext& context) const
{
    int width = RADIUS * 2;
    QRect rect(0, 0, width, width);
    rect.moveCenter(context.mousePos);
    return rect;
}


QString CircleCountTool::name() const
{
    return tr("Circle Counter");
}

CaptureTool::Type CircleCountTool::type() const
{
    return CaptureTool::TYPE_CIRCLECOUNT;
}

void CircleCountTool::copyParams(const CircleCountTool* from,
                                 CircleCountTool* to)
{
    AbstractTwoPointTool::copyParams(from, to);
    to->setCount(from->count());
    to->m_valid = from->m_valid;
}

QString CircleCountTool::description() const
{
    return tr("Add an autoincrementing counter bubble");
}

CaptureTool* CircleCountTool::copy(QObject* parent)
{
    auto* tool = new CircleCountTool(parent);
    copyParams(this, tool);
    return tool;
}

void CircleCountTool::process(QPainter& painter, const QPixmap& pixmap)
{
    Q_UNUSED(pixmap)
    // save current pen, brush, and font state
    auto orig_pen = painter.pen();
    auto orig_brush = painter.brush();
    auto orig_font = painter.font();

    QColor fontColor = ColorUtils::colorIsDark(color()) ? Qt::white : Qt::black;


    // 给圆圈加个边框(反色), 用于避免标注颜色跟截图色彩相近时不好区分
    painter.setPen(fontColor);
    painter.drawEllipse(
      points().first, RADIUS + 1, RADIUS + 1);

    painter.setBrush(color());
    painter.drawEllipse(points().first, RADIUS, RADIUS);
    QRect textRect = QRect(points().first.x() - RADIUS / 2,
                           points().first.y() - RADIUS / 2,
                           RADIUS,
                           RADIUS);
    auto new_font = orig_font;
    new_font.setPixelSize(RADIUS);
    new_font.setBold(true);
    painter.setFont(new_font);

    // Draw text
    painter.setPen(fontColor);
    painter.drawText(textRect, Qt::AlignCenter, QString::number(count()));
    // restore original font, brush, and pen
    painter.setFont(orig_font);
    painter.setBrush(orig_brush);
    painter.setPen(orig_pen);
}

void CircleCountTool::paintMousePreview(QPainter& painter,
                                        const CaptureContext& context)
{

    // Thickness for pen is *2 to range from radius to diameter to match the
    // ellipse draw function
    auto orig_pen = painter.pen();
    auto orig_opacity = painter.opacity();
    painter.setOpacity(0.35);
    painter.setPen(QPen(context.color,
                        RADIUS * 2,
                        Qt::SolidLine,
                        Qt::RoundCap));
    painter.drawLine(context.mousePos,
                     { context.mousePos.x() + 1, context.mousePos.y() + 1 });
    painter.setOpacity(orig_opacity);
    painter.setPen(orig_pen);
}

void CircleCountTool::drawStart(const CaptureContext& context)
{
    AbstractTwoPointTool::drawStart(context);
    m_valid = true;
}

void CircleCountTool::pressed(CaptureContext& context)
{
    Q_UNUSED(context)
}
