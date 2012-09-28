#!/usr/bin/env /tps/bin/python

import sys, os, re, copy, inspect, subprocess, xml, xml.dom, xml.dom.minidom
import general
import CodeProcessor

###############################################################
# TODO: 
#       - Idea is that when you go through the modules,
#   using the code in the Utility.py file, the module, or
#   class name is used as the code_type and each plug-in
#   class will overwrite the processCode function.
#       - Should have some way to define the attributes
#   and how to obtain their values when creating code nodes.
###############################################################


class LineNumber(CodeProcessor.CodeProcessor):
    def __init__(self, code_type, file_name):
        super(LineNumber, self).__init__(code_type, )
        
        #! Contains only one element, line number mapping to content at that line number
        self.line_map = dict()
    
    
    def processCode(self):
        yield



