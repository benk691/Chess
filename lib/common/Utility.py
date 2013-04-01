#! /dsw/Python-2.6.1-2/bin/python
import sys, os, re, inspect, optparse
import Summarizer

def ListClasses(module):
    """ Provides a list of all the classes that use Summarizer as a
        base class.
    """
    ret_list = []
    
    ListClasses_r(module, dict(), module.__name__, ret_list)
    
    return ret_list


def ListClasses_r(module, dict, toplevel_name, ret_list):
    """ Recursively seaarches modules to find all the classes
        that use Summarizer as a base class.
    """
    dict[module.__name__] = True
    
    for item in dir(module):
        item_obj = getattr(module, item)
        
        if inspect.isclass(item_obj):
            if issubclass(item_obj, Summarizer.Summarizer):
                ret_list.append(item_obj)
    
    for item in dir(module):
        item_obj = getattr(module, item)
        
        if inspect.ismodule(item_obj):
            if item_obj.__name__.find(toplevel_name) > -1:
                if item_obj.__name__ not in dict:
                    ListClasses_r(item_obj, dict, toplevel_name, ret_list)


def SummarySearch():
    """ Searches for modules and imports them for program use."""
    summary_class_list = []
    module_path = "summary.modules"
    
    __import__(module_path)
    summary_module = sys.modules[ module_path ]
    
    module_class_list = ListClasses(summary_module)
    
    for module_class in module_class_list:
        summary_class_list.append(module_class)
    
    return summary_class_list


def ProgramParser():
    """ Creates the program parser that creates options based
        on information provided in Summarizer base classes.
    """
    summary_class_list = SummarySearch()
    summary_obj_list = []
    usage = "./fixbuslog.py [-h] [-q] [-t] [-g]"
    
    for summary_class in summary_class_list:
        summary_obj = summary_class()
        summary_obj_list.append(summary_obj)
        
        if summary_obj.sh_opt_str != None or summary_obj.long_opt_str != None:
            usage += " ["
            
            if summary_obj.sh_opt_str != None and summary_obj.long_opt_str != None:
                usage += summary_obj.sh_opt_str + "|" + summary_obj.long_opt_str
            
            elif summary_obj.long_opt_str != None:
                usage += summary_obj.long_opt_str
            
            else:
                usage += summary_obj.sh_opt_str
            
            usage += "]"
        
        else:
            sys.stderr.write("\nError: The class %s must specify at least one of the option string variables sh_opt_str or long_opt_str.\n" % summary_class.__name__)
            sys.exit(-1)
        
    usage += " [input bus log file(s)] [-o [output bus log file(s)]] [-s [output summary file(s)]]"
    
    parser = optparse.OptionParser(usage)
    
    parser.add_option("-q", action="store_true", dest="quiet_mode", default=False, help="If specified the program will be put into quiet mode and the summary will not be produced, but result files can still be produced.")
    parser.add_option("-t", action="store_false", dest="fix_mode", default=True, help="If specified the program will be put into check mode and will only generate a summary of the incorrect timestamps in the log. Otherwise the program will be put into check and fix mode where a summary is produced and will fix the buslog and output it to another file.")
    parser.add_option("-g", action="store_true", dest="generate_mode", default=False, help="If specified the program will be put into generate mode, which allows generated lines to be passed in instead of file paths.")
    
    for summary_obj in summary_obj_list:
        if summary_obj.sh_opt_str != None or summary_obj.long_opt_str != None:
            if summary_obj.sh_opt_str != None and summary_obj.long_opt_str != None:
                parser.add_option(summary_obj.sh_opt_str, summary_obj.long_opt_str, action="callback", callback=summary_obj.callback, help=summary_obj.help_msg)
            
            elif summary_obj.long_opt_str != None:
                parser.add_option(summary_obj.long_opt_str, action="callback", callback=summary_obj.callback, help=summary_obj.help_msg)
            
            else:
                parser.add_option(summary_obj.sh_opt_str, action="callback", callback=summary_obj.callback, help=summary_obj.help_msg)
    
    parser.add_option("-o", nargs=1, dest="output_filename_list", default="", help="specifies the list of output files, please put this list of files in double quotation marks. The number of output files specified should equal the number of input files specified.")
    parser.add_option("-s", nargs=1, dest="summary_filename_list", default="", help="specifies the list of summary files, please put this list of files in double quotation marks. The number of summary files specified should equal the number of input files specified.")
    
    return parser, summary_obj_list


