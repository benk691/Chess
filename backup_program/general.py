#!/usr/bin/env /tps/bin/python

######################### Constants (Do Not Change Values) ############################

# Identifies comments in the program source files
__COMMENT_ID__ = "comment"

# Identifies includes in the program source files
__INCLUDE_ID__ = "include"

# Identifies preprocessor directives in the program source files
__CPP_ID__ = "cpp"

# Identifies debugs in the program source files
__DEBUG_ID__ = "debug"

# Identifies functions in the program source files
__FUNCTION_ID__ = "function"

# Identifies structs in the program source files
__STRUCT_ID__ = "struct"

# Identifies class' in the program source files
__CLASS_ID__ = "class"

# Identifies variables in the program source files
__VARIABLE_ID__ = "variable"

# Identifies strings in the program source files
__STRING_ID__ = "string"

# Identifies new lines in the program source files
__NL_ID__ = "nl"

# Identifies the XML less than symbol
__AMP_ID__ = "amp"

# Identifies the XML less than symbol
__LT_ID__ = "lt"

# Identifies the XML greater than symbol
__GT_ID__ = "gt"

# Identifies the XML double quote symbol
__DBL_QUOTE_ID__ = "dbl_quote"

# Identifies the XML single quote symbol
__UNI_QUOTE_ID__ = "uni_quote"

# Identifies single-line comments
__SL_COMMENT_ID__ = "sl"

# Identifies multi-line comments
__ML_COMMENT_ID__ = "ml"

# Identifies the XML single quote symbol
__UNI_QUOTE_ID__ = "uni_quote"

# Identifies where the soruce file directory is
__SRC_DIR_NAME__ = "bin"

# The path the the current log file
__CURRENT_LOG_PATH__ = "bin/log.xml"

# Specfies that the code is mapped to the line number it is on in its file
__LINE_NUMB_ENCODING__ = "LN"

# Specfies that the code is a content block, and is not mapped to files or line numbers
__CONTENT_ENCODING__ = "C"

# Specifies the XML tag name for the Node that stores information about the code
__CODE_TAG_NAME__ = "code"

# The file name of the file that contains the next version number for backup storage
__VERSION_FILE_NAME__ = "version.txt"

# Code that was added from old version to new version
__ADDED__ = "added"

# Code that was modified from old version to new version
__MOD__ = "modified"

# Code that was deleted from old version to new version
__DELETED__ = "deleted"

# Produces the index for the last element
__END_INDEX__ = lambda seq: (len(seq) - 1)

#######################################################################################
