#ifndef LATEX_DISPLAY_WIDGET_H
#define LATEX_DISPLAY_WIDGET_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>

#include "graph_controller.h"
#include "klfbackend.h"
#include "klfpreviewbuilderthread.h"

class LatexDisplayWidget : public QWidget, GraphUpdateSubscriber {
  Q_OBJECT

 public:
  explicit LatexDisplayWidget(GraphController *controller,
                              QWidget *parent = nullptr);
  ~LatexDisplayWidget();

 public slots:
  void updatePreviewBuilderThreadInput();

  void Notify() override;

 private slots:
  void showRealTimePreview(const QImage &preview, bool latexerror);

 private:
  KLFPreviewBuilderThread *mPreviewBuilderThread;
  KLFBackend::klfInput input;
  KLFBackend::klfSettings settings;
  KLFBackend::klfOutput output;
  QClipboard *clipboard;
  QPixmap pixmap;
  QLabel *label;
  QVBoxLayout *m_layout;
  GraphController *controller;
};

#endif  // MAINWINDOW_H

#endif  // LATEX_DISPLAY_WIDGET_H
