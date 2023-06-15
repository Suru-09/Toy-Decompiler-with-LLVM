#include "frontendQT/MySyntaxHighlighterQT.h"

frontend::MySyntaxHighlighterQT::MySyntaxHighlighterQT(QTextDocument *parent)
: QSyntaxHighlighter(parent)
        {
                HighlightingRule rule;

        // Rule for digits
        rule.pattern = QRegularExpression("\\b\\d+\\b");
        rule.format.setForeground(Qt::blue);
        highlightingRules.append(rule);

        // Rule for keywords
        QStringList keywordPatterns;
        keywordPatterns << "\\bchar\\b" << "\\bclass\\b" << "\\bconst\\b"
        << "\\bdouble\\b" << "\\benum\\b" << "\\bexplicit\\b"
        << "\\bfriend\\b" << "\\binline\\b" << "\\bint\\b"
        << "\\blong\\b" << "\\bnamespace\\b" << "\\boperator\\b"
        << "\\bprivate\\b" << "\\bprotected\\b" << "\\bpublic\\b"
        << "\\bshort\\b" << "\\bsignals\\b" << "\\bsigned\\b"
        << "\\bslots\\b" << "\\bstatic\\b" << "\\bstruct\\b"
        << "\\btemplate\\b" << "\\btypedef\\b" << "\\btypename\\b"
        << "\\bunion\\b" << "\\bunsigned\\b" << "\\bvirtual\\b"
        << "\\bvoid\\b" << "\\bvolatile\\b" << "\\bFn\\b"
        << "\\breturn\\b" << "\\bif\\b" << "\\belse\\b"
        << "\\bwhile\\b" << "\\bfor\\b" << "\\bdo\\b"
        << "\\bbool\\b" << "\\btrue\\b" << "\\bfalse\\b"
        << "\\bi32\\b";

        for (const QString &pattern : keywordPatterns) {
            rule.pattern = QRegularExpression(pattern);
            rule.format.setFontWeight(QFont::Bold);
            rule.format.setForeground(Qt::darkBlue);
            highlightingRules.append(rule);
        }

        // Rule for the word "error"
        rule.pattern = QRegularExpression("\\berror\\b", QRegularExpression::CaseInsensitiveOption);
        rule.format.setForeground(Qt::red);
        highlightingRules.append(rule);

        // Rule for comments
        rule.pattern = QRegularExpression("//[^\n]*");
        rule.format.setForeground(Qt::red);
        highlightingRules.append(rule);
        }

void frontend::MySyntaxHighlighterQT::highlightBlock(const QString &text) {
    for (const HighlightingRule &rule : qAsConst(highlightingRules)) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }
}
