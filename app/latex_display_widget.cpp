#include "latex_display_widget.h"

#include <QDebug>
#include <QPalette>

#include "klfbackend.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

LatexDisplayWidget::LatexDisplayWidget(GraphController* controller,
                                       QWidget* parent)
    : QWidget(parent), controller(controller) {
  timer = new QTimer(this);
  timer->setInterval(1000);
  connect(timer, SIGNAL(timeout()), this,
          SLOT(updatePreviewBuilderThreadInput()));
  timer->start();

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
    qDebug() << "unable to find LaTeX in default directories.";
  } else {
    qDebug() << "default settings working!";
  }

  // setup variables:
  mPreviewBuilderThread = new KLFPreviewBuilderThread(this, input, settings);

  connect(mPreviewBuilderThread, SIGNAL(previewAvailable(const QImage&, bool)),
          this, SLOT(showRealTimePreview(const QImage&, bool)),
          Qt::QueuedConnection);
}

LatexDisplayWidget::~LatexDisplayWidget() { delete mPreviewBuilderThread; }

void LatexDisplayWidget::updatePreviewBuilderThreadInput() {
  // in linux, I need to reinstate the preamble when rendering. No idea why.
  static int a = 0;
  input.preamble = QString("\\usepackage{amssymb,amsmath}");
  input.latex = "x \\left(\\int_0^1 dx \\right) " + QString::number(++a);
  if (mPreviewBuilderThread->inputChanged(input)) {
    qDebug() << "input changed. Render...";
    mPreviewBuilderThread->start();
  }
}

void LatexDisplayWidget::showRealTimePreview(const QImage& preview,
                                             bool latexerror) {
  if (latexerror) {
    // a
  } else {
    pixmap = QPixmap::fromImage(preview);
    label->setPixmap(pixmap);
  }
}
