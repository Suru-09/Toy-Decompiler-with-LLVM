#ifndef REVERSE_ENGINEERING_TOOL_MYSYNTAXHIGHLIGHTERQT_H
#define REVERSE_ENGINEERING_TOOL_MYSYNTAXHIGHLIGHTERQT_H

#include <QSyntaxHighlighter>
#include <QRegularExpression>
#include <QTextCharFormat>

#include <iostream>

namespace frontend {

    class MySyntaxHighlighterQT : public QSyntaxHighlighter {
    Q_OBJECT
    public:
        explicit MySyntaxHighlighterQT(QTextDocument *parent=nullptr);

    protected:
        void highlightBlock(const QString &text);

    private:

        struct HighlightingRule
        {
            QRegularExpression pattern;
            QTextCharFormat format;
        };
        QVector<HighlightingRule> highlightingRules;
    };

}   // end of namespace frontend

#endif //REVERSE_ENGINEERING_TOOL_MYSYNTAXHIGHLIGHTERQT_H
