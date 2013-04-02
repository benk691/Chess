#/bin/python
import lib.ply.lex as lex

# List of token names. This is required
tokens = (
    'ROW',
    'COL',
    'CHECK',
    'CHECKMATE',
    'PROMOTION',
)

# Simple tokens
t_ROW       = r'[a-h]'
t_COL       = r'[1-8]'
t_CHECK     = r'\+'
t_CHECKMATE = r'#'
t_PROMOTION = r'='

# Rule so we can track line numbers
def t_newline(t):
    r'\n+'
    t.lexer.lineno += len(t.value)

# Ignored characters
t_ignore = '\t'

# Error handling rule
def t_error(t):
    print "Illegal character '%s'" % t.value[0]
    t.lexer.skip(1)
