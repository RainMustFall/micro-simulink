#include "latex_display_widget.h"

#include <QDebug>
#include <QPalette>

#include "exceptions.h"
#include "klfbackend.h"
#include "mainwindow.h"

LatexDisplayWidget::LatexDisplayWidget(GraphController *controller,
                                       QWidget *parent)
    : QWidget(parent), controller(controller) {
  input.mathmode = "\\[ ... \\]";
  input.dpi = 150;
  input.bg_color = qRgba(0, 0, 0, 0);
  input.fg_color = QApplication::palette()
                       .color(QPalette::Active, QPalette::WindowText)
                       .rgb();

  label = new QLabel();
  label->setMinimumHeight(input.dpi / 2);

  m_layout = new QVBoxLayout(this);
  m_layout->addWidget(label);
  m_layout->setAlignment(Qt::AlignCenter);
  setLayout(m_layout);

  input.preamble = QString("\\usepackage{amssymb,amsmath,mathrsfs}");

  if (!KLFBackend::detectSettings(&settings)) {
    label->setWordWrap(true);
    label->setText(getMissingComponentText());
    return;
  }

  // setup variables:
  mPreviewBuilderThread = new KLFPreviewBuilderThread(this, input, settings);

  connect(mPreviewBuilderThread, SIGNAL(previewAvailable(const QImage &, bool)),
          this, SLOT(showRealTimePreview(const QImage &, bool)),
          Qt::QueuedConnection);

  controller->SubscribeForUpdates(this);
}

QString LatexDisplayWidget::getMissingComponentText() {
  if (settings.latexexec.isEmpty()) {
    return qtTrId("latex-not-found");
  } else if (settings.gsexec.isEmpty()) {
    return qtTrId("ghostscript-not-found");
  } else if (settings.dvipsexec.isEmpty()) {
    return qtTrId("dvipsexec-not-found");
  } else if (settings.epstopdfexec.isEmpty()) {
    return qtTrId("epstopdfexec-not-found");
  }

  return qtTrId("unknown-latex-issue");
}

LatexDisplayWidget::~LatexDisplayWidget() { delete mPreviewBuilderThread; }

void LatexDisplayWidget::Notify() {
  input.preamble = QString("\\usepackage{amssymb,amsmath}");

  try {
    input.latex = QString::fromStdString(controller->GetLatex());
  } catch (GraphIsIncomplete &) {
    // Graph is incomplete, that's fine
  }

  if (mPreviewBuilderThread->inputChanged(input)) {
    qDebug() << "input changed. Render...";
    mPreviewBuilderThread->start();
  }
}

void LatexDisplayWidget::showRealTimePreview(const QImage &preview,
                                             bool latexerror) {
  if (!latexerror) {
    pixmap = QPixmap::fromImage(preview);
    label->setPixmap(pixmap);
  }
}
