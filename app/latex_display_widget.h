#ifndef LATEX_DISPLAY_WIDGET_H
#define LATEX_DISPLAY_WIDGET_H

#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>

#include "graph_controller.h"
#include "klfbackend.h"
#include "klfpreviewbuilderthread.h"

/*!
 * @brief Qt widget responsible for rendering LaTeX representation of the graph
 */
class LatexDisplayWidget : public QWidget, GraphUpdateSubscriber {
  Q_OBJECT

 public:
  /*!
   * @brief LatexDisplayWidget constructor
   * @param controller - GraphController maintaining the graph model
   * @param parent - parent widget
   */
  explicit LatexDisplayWidget(GraphController *controller,
                              QWidget *parent = nullptr);

  /*!
   * @brief Process notification that graph has been updated
   *
   * Trigger LaTeX render
   */
  void Notify() override;

  ~LatexDisplayWidget();

 private slots:
  void showRealTimePreview(const QImage &preview, bool latexerror);

 private:
  KLFPreviewBuilderThread *mPreviewBuilderThread = nullptr;
  KLFBackend::klfInput input;
  KLFBackend::klfSettings settings;
  KLFBackend::klfOutput output;
  QClipboard *clipboard;
  QPixmap pixmap;
  QLabel *label;
  QVBoxLayout *m_layout;
  GraphController *controller;
  QString getMissingComponentText();
};

#endif  // LATEX_DISPLAY_WIDGET_H
