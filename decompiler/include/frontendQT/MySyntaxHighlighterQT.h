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
    explicit MySyntaxHighlighterQT(QTextDocument *parent=nullptr)
            : QSyntaxHighlighter(parent)
    {
        HighlightingRule rule;

        // Rule for digits
        rule.pattern = QRegularExpression("\\b\\d+\\b");
        rule.format.setForeground(Qt::blue);
        highlightingRules.append(rule);

        // Rule for the word "error"
        rule.pattern = QRegularExpression("\\berror\\b", QRegularExpression::CaseInsensitiveOption);
        rule.format.setForeground(Qt::red);
        highlightingRules.append(rule);
    }

protected:
    void highlightBlock(const QString &text)
    {
        for (const HighlightingRule &rule : qAsConst(highlightingRules)) {
            QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
            while (matchIterator.hasNext()) {
                QRegularExpressionMatch match = matchIterator.next();
                setFormat(match.capturedStart(), match.capturedLength(), rule.format);
            }
        }
    }

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
