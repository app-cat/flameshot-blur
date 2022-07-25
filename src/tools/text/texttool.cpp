// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: 2017-2019 Alejandro Sirgo Rica & Contributors

#include "texttool.h"
// #include "src/utils/confighandler.h"
#include "textwidget.h"

#define MAX_INFO_LENGTH 24

TextTool::TextTool(QObject* parent)
  : CaptureTool(parent)
  , m_size(1)
{

}

TextTool::~TextTool()
{
    closeEditor();
}

void TextTool::copyParams(const TextTool* from, TextTool* to)
{
    CaptureTool::copyParams(from, to);
    to->m_font = from->m_font;
    to->m_text = from->m_text;
    to->m_size = from->m_size;
    to->m_color = from->m_color;
    to->m_textArea = from->m_textArea;
    to->m_currentPos = from->m_currentPos;
}

bool TextTool::isValid() const
{
    return !m_text.isEmpty();
}

bool TextTool::closeOnButtonPressed() const
{
    return false;
}

bool TextTool::isSelectable() const
{
    return true;
}

bool TextTool::showMousePreview() const
{
    return false;
}

QRect TextTool::boundingRect() const
{
    return m_textArea;
}

QIcon TextTool::icon(const QColor& background, bool inEditor) const
{
    Q_UNUSED(inEditor)
    return QIcon(iconPath(background) + "text.svg");
}

QString TextTool::name() const
{
    return tr("Text");
}

QString TextTool::info()
{
    if (m_text.length() > 0) {
        m_tempString = QString("%1 - %2").arg(name()).arg(m_text.trimmed());
        m_tempString = m_tempString.split("\n").at(0);
        if (m_tempString.length() > MAX_INFO_LENGTH) {
            m_tempString.truncate(MAX_INFO_LENGTH);
            m_tempString += "…";
        }
        return m_tempString;
    }
    return name();
}

CaptureTool::Type TextTool::type() const
{
    return CaptureTool::TYPE_TEXT;
}

QString TextTool::description() const
{
    return tr("Add text to your capture");
}

QWidget* TextTool::widget()
{
    closeEditor();
    m_widget = new TextWidget();
    m_widget->setTextColor(m_color);
    m_font.setPointSize(16);
    m_widget->setFont(m_font);
    connect(m_widget, &TextWidget::textUpdated, this, &TextTool::updateText);
    return m_widget;
}

void TextTool::closeEditor()
{
    if (!m_widget.isNull()) {
        m_widget->hide();
        delete m_widget;
        m_widget = nullptr;
    }
}


CaptureTool* TextTool::copy(QObject* parent)
{
    auto* textTool = new TextTool(parent);
    copyParams(this, textTool);
    return textTool;
}

void TextTool::process(QPainter& painter, const QPixmap& pixmap)
{
    Q_UNUSED(pixmap)
    if (m_text.isEmpty()) {
        return;
    }
    const int val = 5;
    QFont orig_font = painter.font();
    QPen orig_pen = painter.pen();
    QFontMetrics fm(m_font);
    QSize size(fm.boundingRect(QRect(), 0, m_text).size());
    size.setWidth(size.width() + val * 2);
    size.setHeight(size.height() + val * 2);
    m_textArea.setSize(size);
    // draw text
    painter.setFont(m_font);
    painter.setPen(m_color);
    if (!editMode()) {
        painter.drawText(
          m_textArea + QMargins(-val, -val, val, val), Qt::AlignLeft, m_text);
    }
    painter.setFont(orig_font);
    painter.setPen(orig_pen);
}

void TextTool::drawObjectSelection(QPainter& painter)
{
    if (m_text.isEmpty()) {
        return;
    }
    drawObjectSelectionRect(painter, boundingRect());
}

void TextTool::paintMousePreview(QPainter& painter,
                                 const CaptureContext& context)
{
    Q_UNUSED(painter)
    Q_UNUSED(context)
}

void TextTool::drawEnd(const QPoint& point)
{
    m_textArea.moveTo(point);
}

void TextTool::drawMove(const QPoint& point)
{
    m_widget->move(point);
}

void TextTool::drawStart(const CaptureContext& context)
{
    m_color = context.color;
    // m_size = 16;
    emit requestAction(REQ_ADD_CHILD_WIDGET);
}

void TextTool::pressed(CaptureContext& context)
{
    Q_UNUSED(context)
}

void TextTool::onColorChanged(const QColor& color)
{
    m_color = color;
    if (m_widget != nullptr) {
        m_widget->setTextColor(color);
    }
}


void TextTool::updateText(const QString& newText)
{
    m_text = newText;
}


void TextTool::move(const QPoint& pos)
{
    m_textArea.moveTo(pos);
}


const QPoint* TextTool::pos()
{
    m_currentPos = m_textArea.topLeft();
    return &m_currentPos;
}

void TextTool::setEditMode(bool editMode)
{
    if (editMode) {
        m_textOld = m_text;
    }
    CaptureTool::setEditMode(editMode);
}

bool TextTool::isChanged()
{
    return QString::compare(m_text, m_textOld, Qt::CaseInsensitive) != 0;
}
