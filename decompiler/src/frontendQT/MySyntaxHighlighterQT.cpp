#include "frontendQT/MySyntaxHighlighterQT.h"

frontend::MySyntaxHighlighterQT::MySyntaxHighlighterQT(QTextDocument *parent)
: QSyntaxHighlighter(parent)
{
    HighlightingRule rule;

    // Rule for digits
    rule.pattern = QRegularExpression("\\b\\d+\\b");
    rule.format.setForeground(QColor("#E5C07B"));
    highlightingRules.append(rule);

    // Rule for true and false
    rule.pattern = QRegularExpression("\\btrue\\b|\\bfalse\\b");
    rule.format.setForeground(QColor("#E5C07B"));
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
    << "\\bvoid\\b" << "\\bvolatile\\b" << "\\bfn\\b"
    << "\\breturn\\b" << "\\bif\\b" << "\\belse\\b"
    << "\\bwhile\\b" << "\\bfor\\b" << "\\bdo\\b"
    << "\\bbool\\b" << "\\bi32\\b" << "\\bi64\\b"
    << "\\bu32\\b" << "\\bu64\\b" << "\\bf32\\b"
    << "\\bf64\\b";

    for (const QString &pattern : keywordPatterns) {
        rule.pattern = QRegularExpression(pattern);
        rule.format.setFontWeight(QFont::Bold);
        rule.format.setForeground(QColor("#C678DD"));
        highlightingRules.append(rule);
    }

    // Rule for the word "error"
    rule.pattern = QRegularExpression("\\berror\\b", QRegularExpression::CaseInsensitiveOption);
    rule.format.setForeground(Qt::red);
    highlightingRules.append(rule);

    // Rule for comments
    auto qDoubleQuote = QRegularExpression("//[^\n]*");
    rule.pattern = qDoubleQuote;
    rule.format.setForeground(Qt::green);
    highlightingRules.append(rule);

    QTextCharFormat quotationFormat;
    quotationFormat.setForeground(QColor("#98c379"));
    rule.pattern = QRegularExpression("\".*\"");
    rule.format = quotationFormat;
    highlightingRules.append(rule);

    // quotation (single quote)
    auto qSingleQuote = QRegularExpression("\'.*\'");
    rule.pattern = qSingleQuote;
    rule.format = quotationFormat;
    highlightingRules.append(rule);

    QTextCharFormat variableFormat;
    variableFormat.setForeground(QColor("#61AFEF"));

    HighlightingRule variableRule;
    variableRule.pattern = QRegularExpression("\\blvar_[0-9]+\\b");
    variableRule.format = variableFormat;
    highlightingRules.append(variableRule);
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
