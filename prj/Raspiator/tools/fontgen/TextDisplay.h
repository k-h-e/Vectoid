#ifndef FONTGEN_TEXTDISPLAY_H_
#define FONTGEN_TEXTDISPLAY_H_


#include <vector>
#include <QWidget>


class TextDisplay : public QWidget {
    Q_OBJECT

  public:
    TextDisplay();

  protected:
    void paintEvent(QPaintEvent *event);

  private:
    QFont                         font_;
    std::unique_ptr<QFontMetrics> metrics_;
    std::vector<QString>          glyphs_;
    int                           glyphWidth_,
                                  glyphHeight_;
    bool                          generateCode_;
};


#endif    // FONTGEN_TEXTDISPLAY_H_
